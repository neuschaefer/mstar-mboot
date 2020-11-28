#include <common.h>
#include <stdio.h>
#include <linux/lzo.h>
#include <linux/crc32.h>
#include <command.h>
#include <watchdog.h>
#include <malloc.h>
#include <asm/byteorder.h>
#include <jffs2/jffs2.h>

#if defined(CONFIG_CMD_MTDPARTS)
#include <linux/mtd/mtd.h>
#endif

#if defined(CONFIG_NAND_FLASH) || defined(CONFIG_SPI_NAND_FLASH)
#include <nand.h>
#endif

#if CONFIG_MMC
#include <mmc.h>
#endif

typedef struct lx_mem_region_s{
    unsigned long start_addr;
    unsigned long length;
}lx_mem_region_t;

#define MAX_LX_MEM_REGION       3
static lx_mem_region_t lxmemarray[MAX_LX_MEM_REGION];

#define MAX_MEM_STR_LEN 512
static char msmem[MAX_MEM_STR_LEN];

#define LX_MEM0_START 0x80210000
static int fastbootmode;
static char fbpart[20];
static int bcheck_crc=0;
int fastboot_getconfig(void)
{
    char *p;
    int i;
    p=getenv("fastboot");
    if (!p) return -1;
    for (i=0; (*p)&&(i<(MAX_MEM_STR_LEN-1)); i++,p++){
        msmem[i]=((*p)==',')?' ':(*p);
    }
    msmem[i]=0;
    if(strncmp(msmem,"fastboot=",9))return -1;
    sscanf(msmem+9,"%d %*s %19s",&fastbootmode,fbpart);
    p=getenv("fastboot_checkcrc");
    if(p){
        sscanf(p,"%d",&bcheck_crc);
    }
    return 0;
}
static int fastboot_get_lxmem(void)
{
    // get from MS_MEM env
    static const char *brkchars=" ";
    char *p;
    int cnt=0;
    memset(lxmemarray, 0, sizeof(lxmemarray));
    p=getenv("bootargs");
    if (!p) return -1;
    strncpy(msmem, p, MAX_MEM_STR_LEN);
    p=strtok(msmem,brkchars);
    while(p&&cnt<MAX_LX_MEM_REGION){
        if(strncmp(p,"LX_MEM=", 7)==0){
            if( 1==sscanf(p+7,"0x%x",&lxmemarray[cnt].length)){
                lxmemarray[cnt].start_addr=LX_MEM0_START;
                cnt++;
            }
        }else if(strncmp(p,"LX_MEM2=", 8)==0 || strncmp(p,"LX_MEM3=", 8)==0){
            lxmemarray[cnt].start_addr=LX_MEM0_START;
            if(2==sscanf(p+8,"0x%x,0x%x",&lxmemarray[cnt].start_addr, &lxmemarray[cnt].length))
                cnt++;
        }
        p=strtok(NULL,brkchars);
    }
    return cnt;
}
#if defined(CONFIG_CMD_MTDPARTS)
/* partition handling routines */
int mtdparts_init(void);
int find_dev_and_part(const char *id, struct mtd_device **dev,
		      u8 *part_num, struct part_info **part);

#endif

#if CONFIG_MMC
static struct block_dev_desc *_fastboot_mmc=NULL;
#endif
static int fastboot_setdev(int dev)
{
#if defined(CONFIG_NAND_FLASH) || defined(CONFIG_SPI_NAND_FLASH)
	if (dev < 0 || dev >= CONFIG_SYS_MAX_NAND_DEVICE ||
	    !nand_info[dev].name) {
		puts("No such device\n");
		return -1;
	}

	if (nand_curr_device == dev)
		return 0;

	printf("Device %d: %s", dev, nand_info[dev].name);
	puts("... is now current device\n");
	nand_curr_device = dev;

#ifdef CONFIG_SYS_NAND_SELECT_DEVICE
	board_nand_select_device(nand_info[dev].priv, dev);
#endif
#endif //#if CONFIG_NAND_FLASH

	return 0;
}
static int fastboot_get_part(const char *partname, int *idx, loff_t *off, loff_t *size)
{
#ifdef CONFIG_CMD_MTDPARTS
	struct mtd_device *dev;
	struct part_info *part;
	u8 pnum;
	int ret;

	ret = mtdparts_init();
	if (ret)
		return ret;

	ret = find_dev_and_part(partname, &dev, &pnum, &part);
	if (ret)
		return ret;

	if (dev->id->type != MTD_DEV_TYPE_NAND) {
		puts("not a NAND device\n");
		return -1;
	}

	*off = part->offset;
	*size = part->size;
	*idx = dev->id->num;

	ret = fastboot_setdev(*idx);
	if (ret)
		return ret;

	return 0;
#elif CONFIG_MMC
    block_dev_desc_t *mmc_dev;
    disk_partition_t dpt;
    struct mmc *mmc;
    int partnum=1;
    _fastboot_mmc=NULL;
    mmc = find_mmc_device(0);
    if(!mmc){
        printf("fastboot:get mmc device fail\n");
    }
    if(!(mmc->has_init)){
        printf("fastboot:Do mmc init first!\n");
        mmc_init(mmc);
        mmc->has_init = 1;
    }
    mmc_dev = &mmc->block_dev;
    if(mmc_dev->type == DEV_TYPE_UNKNOWN){
        printf("fastboot:unknow mmc device type\n");
    }
    for(;;){
        if(get_partition_info_emmc(mmc_dev, partnum, &dpt))
            break;
        if(!strcmp(partname, (const char *)dpt.name)){
            *off = dpt.start*512;
            *size= dpt.size*512;
            *idx = 0;//dummy
            _fastboot_mmc=mmc_dev;
            return 0;
        }
        partnum++;
    }
    printf("fastboot: cat't get emmc partition-%s\n",partname);
    return -1;
#else
	puts("unknow storage\n");
	return -1;
#endif
}
static int fastboot_read_diskdata(unsigned long off, unsigned long len, void *buf)
{
#if defined(CONFIG_NAND_FLASH) || defined(CONFIG_SPI_NAND_FLASH)
    int dev = nand_curr_device;
    nand_info_t *nand=&nand_info[dev];
    int ret;
    size_t rwsize=len;
    //snprintf(msmem,MAX_MEM_STR_LEN,"nand read.e %x %x 0x%x",buf ,off, len);
    ret=nand_read_skip_bad(nand, off, &rwsize,
							 (u_char *)buf);
    if(ret==0 && rwsize==len){
        return len;
    }
    return -1;
#elif CONFIG_MMC
    unsigned long rd;
    if(!_fastboot_mmc)
        return -1;
    if(off%512 || len%512)
        return -1;
    rd=_fastboot_mmc->block_read(0, off/512, len/512, buf);
    if(rd==0)
        return -1;
    return (rd*512);
#else
    puts("unknow storage\n");
	return -1;
#endif
}
#define FB_TM_STRLEN 40
struct fastboot_info{
    char sig[8];
    u32 version;
    u32 pagecount;
    u32 datapagecnt;
    u32 metapagecnt;
    u32 datasize;
    u32 phyent;
    u32 fmt;
    u32 crc;
    char tm[FB_TM_STRLEN];
};
#define PAGE_SIZE 4096
#define PFN_PHY(x) (x*PAGE_SIZE)
#if CONFIG_MCU_MIPS32
#define MIU0_VIRTBASE1   0x80000000
#define MIU1_BASE_ADDR1  0x60000000
#define MIU1_BASE_ADDR2  0x70000000
#define MIU1_VIRTBASE1   0x00000000
#define MIU1_VIRTBASE2   0x20000000
#define _PHY_TO_VIRT(x) ((x<MIU1_BASE_ADDR1)?(x+MIU0_VIRTBASE1):    \
                          ((x<MIU1_BASE_ADDR2)?(x-MIU1_BASE_ADDR1+MIU1_VIRTBASE1):(x-MIU1_BASE_ADDR2+MIU1_VIRTBASE2)) )
#elif CONFIG_MCU_ARM
#define M512M (512*1024*1024)
#define _PHY_TO_VIRT(x) ( (((x)>=(CONFIG_MIU0_BUSADDR)&&(x)<(CONFIG_MIU0_BUSADDR+M512M)) \
                            ||((x)>=(CONFIG_MIU1_BUSADDR)&&(x)<(CONFIG_MIU1_BUSADDR+M512M)))? \
                            (x):(0) )
#else
#define _PHY_TO_VIRT(x) (x)
#endif
#define PHY_TO_VIRT(x) _PHY_TO_VIRT((unsigned long)(x))

#define need_cpy(last,curr) ((curr)!=((last)+1) || ((curr)&0x000f0000)!=((last)&0x000f0000))

#define FASTBOOT_INTER_BUF_START     (CONFIG_MSTAR_FASTBOOT_BUFADR)
#define FASTBOOT_INTER_BUF_LEN       (CONFIG_MSTAR_FASTBOOT_BUFLEN*1024*1024)

#define LZO_HEADER	(sizeof(unsigned long)+2*sizeof(unsigned long))
#define LZO_UNC_PAGES	32
#define LZO_UNC_SIZE	(LZO_UNC_PAGES * PAGE_SIZE)
#define LZO_CMP_PAGES	DIV_ROUND_UP(lzo1x_worst_compress(LZO_UNC_SIZE) + \
			             LZO_HEADER, PAGE_SIZE)
#define LZO_CMP_SIZE	(LZO_CMP_PAGES * PAGE_SIZE)

#define LZO_CMPBLK_SIZE(cmp) ((LZO_HEADER+cmp->cmp_size+PAGE_SIZE-1)/PAGE_SIZE*PAGE_SIZE)
#define LZO_CMPBLK_END(cmp) ((unsigned char*)cmp+LZO_CMPBLK_SIZE(cmp))

typedef struct cmp_hdr
{
    unsigned long cmp_size;
    unsigned long startpg;
    unsigned long endpg;
}cmp_hdr;

static unsigned char * fastboot_hdr=0;
static unsigned char * fastboot_databuf=0;
static long fastboot_databuflen=0;

int fastboot_prepare(void)
{
    printf("FASTBOOT use buf at %08x with len %d(MB)\n",
            FASTBOOT_INTER_BUF_START,
            FASTBOOT_INTER_BUF_LEN/(1024*1024));
    fastboot_hdr=(unsigned char *)FASTBOOT_INTER_BUF_START;
    fastboot_databuf=fastboot_hdr+PAGE_SIZE;
    fastboot_databuflen= FASTBOOT_INTER_BUF_LEN-PAGE_SIZE;
    if(fastboot_databuflen<=0)
        return -1;
    return 0;
}

struct fastboot_info *fastboot_getimghdr(int *pidx, loff_t *poff, loff_t *psize)
{
    int idx;
    loff_t off=0;
    loff_t size;
    struct fastboot_info* info;
    loff_t mtdrdptr,mtdrdendptr;

    info=(struct fastboot_info*)fastboot_hdr;
    if(0>fastboot_get_part(fbpart,&idx, &off,&size)){
        printf("fastboot get %s fail\n",fbpart);
        return NULL;
    }
    mtdrdptr = off;
    mtdrdendptr = mtdrdptr+size;
    if (PAGE_SIZE!=fastboot_read_diskdata(mtdrdptr, PAGE_SIZE, info)){
        printf("fastboot read image header fail\n");
        return NULL;
    }
    if(strncmp(info->sig,"msfbimg",7)){
        printf("Invalid partion data\n");
        return NULL;
    }
    if(pidx)*pidx=idx;
    if(poff)*poff=off;
    if(psize)*psize=size;
    return info;
}

int fastboot_lzo_decomp(cmp_hdr *pcmpblk)
{
    size_t unc_len;
    int error;
    unc_len = LZO_UNC_SIZE;
	error = lzo1x_decompress_safe((unsigned char*)(pcmpblk+1), pcmpblk->cmp_size,
	                              (unsigned char*)PHY_TO_VIRT(PFN_PHY(pcmpblk->startpg)),&unc_len);
	if (error < 0
        || unc_len!=((pcmpblk->endpg-pcmpblk->startpg+1)*PAGE_SIZE)) {
		return -1;
	}
    return 0;
}

int fastboot_nocmp(struct fastboot_info* info,
                            int idx,loff_t off,loff_t size,
                            unsigned char* databuf, long databuflen)
{
    unsigned char *metadata;
    long metadatalen;
    loff_t mtdrdptr,mtdrdendptr;
    unsigned long datahandled, datatord;
    unsigned long *ppage,lastpg,cpylen;
    unsigned char *srcdata,*dstdata,*p;
    unsigned long crcval=0;

    metadata = databuf;
    metadatalen = info->metapagecnt*PAGE_SIZE;
    databuf = metadata+metadatalen;
    databuflen = databuflen-metadatalen;
    if(metadatalen<=0 || databuflen<=0){
        printf("Not enough buf\n");
        return -1;
    }
    mtdrdptr = off+PAGE_SIZE;
    mtdrdendptr = off+size;
    if ( (mtdrdptr+info->datasize)>mtdrdendptr ){
        printf("fastboot not enough mtd space or error image\n");
        return -1;
    }
    datahandled = 0;
    datatord=fastboot_read_diskdata(mtdrdptr,metadatalen,metadata);
    if(datatord!=metadatalen){
        printf("fastboot read image data fail\n");
        return -1;
    }
    if(bcheck_crc)crcval=crc32(crcval, metadata, metadatalen);
    mtdrdptr+=metadatalen;
    datahandled+=metadatalen;
    ppage = (unsigned long*)metadata;
    while(datahandled<info->datasize){
        datatord = info->datasize-datahandled;
        if (datatord > databuflen)
            datatord = databuflen;
        if (datatord!=fastboot_read_diskdata(mtdrdptr, datatord, databuf)){
            printf("fastboot read image data fail\n");
            return -1;
        }
        if(bcheck_crc)crcval=crc32(crcval, databuf, datatord);
        mtdrdptr += datatord;

        srcdata = databuf;
        dstdata=(unsigned char*)(ppage[0]*PAGE_SIZE);
        dstdata=(unsigned char*)PHY_TO_VIRT(dstdata);
        lastpg=ppage[0];
        cpylen = PAGE_SIZE;
        ppage++;
        datahandled += PAGE_SIZE;

        for (p = srcdata+PAGE_SIZE;
             p<databuf+datatord;
             p+=PAGE_SIZE){
            if(need_cpy(lastpg,ppage[0])){
                memcpy(dstdata, srcdata, cpylen);
                srcdata = p;
                dstdata=(unsigned char*)(ppage[0]*PAGE_SIZE);
                dstdata=(unsigned char*)PHY_TO_VIRT(dstdata);
                cpylen = 0;
            }
            lastpg=ppage[0];
            ppage++;
            cpylen += PAGE_SIZE;
            datahandled += PAGE_SIZE;
        }
        if(cpylen){
            memcpy(dstdata, srcdata, cpylen);
        }
    }
    if(bcheck_crc){
        printf("fastboot CRC is %08lx, %s equal to %08x\n",
             crcval,(crcval==info->crc)?"":"not",info->crc);
    }
    return 0;
}
int fastboot_lzo(struct fastboot_info* info,
                        int idx,loff_t off,loff_t size,
                        unsigned char* databuf, long databuflen)
{
    unsigned char *cmpbuf;
    long cmpbuflen;
    loff_t mtdrdptr,mtdrdendptr;
    unsigned long datahandled, datatord;
    cmp_hdr *pcmpblk;
    unsigned char *pcmpbufend;
    unsigned long crcval=0;
    int error=0;

    cmpbuf=databuf;
    cmpbuflen=(databuflen-LZO_CMP_SIZE)/LZO_CMP_SIZE*LZO_CMP_SIZE;
    if (cmpbuflen<LZO_CMP_SIZE){
        printf("Not enough buf\n");
        return -1;
    }

    mtdrdptr = off+PAGE_SIZE;
    mtdrdendptr = off+size;

    if ( (mtdrdptr+info->datasize)>mtdrdendptr ){
        printf("fastboot not enough mtd space or error image\n");
        return -1;
    }
    datahandled = 0;
    while(datahandled<info->datasize){
        datatord = info->datasize-datahandled;
        if (datatord > cmpbuflen)
            datatord = cmpbuflen;
        if (datatord!=fastboot_read_diskdata(mtdrdptr, datatord, cmpbuf)){
            printf("fastboot read image data fail\n");
            return -1;
        }
        if(bcheck_crc)crcval=crc32(crcval, cmpbuf, datatord);
        mtdrdptr += datatord;

        pcmpbufend = cmpbuf+datatord;
        for (pcmpblk = (cmp_hdr *)cmpbuf;
             ((unsigned char*)pcmpblk<pcmpbufend)&&(LZO_CMPBLK_END(pcmpblk)<=pcmpbufend);
             pcmpblk = (cmp_hdr *)LZO_CMPBLK_END(pcmpblk)){
            // decompress
            if((!error)&&(fastboot_lzo_decomp(pcmpblk)<0)){
                printf("fastboot decmp fail\n");
                error=-1;
            }
            datahandled += LZO_CMPBLK_SIZE(pcmpblk);
        }
        if ((unsigned char*)pcmpblk<pcmpbufend){
            datatord = LZO_CMPBLK_END(pcmpblk)-pcmpbufend;
            if (datatord!=fastboot_read_diskdata(mtdrdptr, datatord, pcmpbufend)){
                printf("fastboot read image end of blk data fail\n");
                return -1;
            }
            if(bcheck_crc)crcval=crc32(crcval, pcmpbufend, datatord);
            mtdrdptr += datatord;
            // decompress
            if((!error)&&(fastboot_lzo_decomp(pcmpblk)<0)){
                printf("fastboot decmp fail\n");
                error=-1;
            }
            datahandled += LZO_CMPBLK_SIZE(pcmpblk);
        }
    }
    if(bcheck_crc){
        printf("fastboot CRC is %08lx, %s equal to %08x\n",
             crcval,(crcval==info->crc)?"":"not",info->crc);
    }
    return error;
}
int fastboot_common(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    int idx;
    loff_t off=0;
    loff_t size;
    void (*resume)(void)=NULL;
    int ret=0;

    struct fastboot_info* info=fastboot_getimghdr(&idx,&off,&size);
    if(!info)return -1;
    resume = (void *)PHY_TO_VIRT(info->phyent);
    if(info->fmt){
        ret=fastboot_lzo(info,idx,off,size,fastboot_databuf,fastboot_databuflen);
    }else{
        ret=fastboot_nocmp(info,idx,off,size,fastboot_databuf,fastboot_databuflen);
    }
    if(0==ret){
        flush_cache_all();
    if(resume){
        resume();
    }
    }
    return ret;
}
int fastboot_dumpinfo(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    int idx;
    loff_t off=0;
    loff_t size;
    struct fastboot_info* info;
    info=fastboot_getimghdr(&idx,&off,&size);
    if(!info)return -1;
    printf("version   : %08x\n",info->version);
    printf("imagesize : %08x(%08x)\n",info->datasize,(info->datapagecnt+info->metapagecnt)*PAGE_SIZE);
    printf("compressed: %s\n", (info->fmt)?"y":"n");
    printf("entry     : %08x\n", info->phyent);
    printf("crc       : %08x\n",info->crc);
    printf("createtime: %s\n",info->tm);
    printf("diskused  : [%08x,%08x]\n",(unsigned int)off, (unsigned int)off+info->datasize+PAGE_SIZE-1);
    return 0;
}
int fastboot_checkcrc(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    unsigned long crcval=0;
    unsigned char* databuf;
    long databuflen;
    loff_t mtdrdptr,mtdrdendptr;
    unsigned long datahandled, datatord;
    int idx;
    loff_t off=0;
    loff_t size;
    struct fastboot_info* info=fastboot_getimghdr(&idx,&off,&size);
    if(!info)return -1;

    databuf=fastboot_databuf;
    databuflen=fastboot_databuflen;
    mtdrdptr = off+PAGE_SIZE;
    mtdrdendptr = off+size;
    if ( (mtdrdptr+info->datasize)>mtdrdendptr ){
        printf("fastboot not enough mtd space or error image\n");
        return -1;
    }
    datahandled=0;
    while(datahandled<info->datasize){
        datatord = info->datasize-datahandled;
        if (datatord > databuflen)
            datatord = databuflen;
        if (datatord!=fastboot_read_diskdata(mtdrdptr, datatord, databuf)){
            printf("fastboot read image data fail\n");
            return -1;
        }
        mtdrdptr += datatord;
        datahandled += datatord;
        crcval=crc32(crcval, databuf, datatord);
    }
    printf("CRC is %08lx, %s equal to %08x\n",
             crcval,(crcval==info->crc)?"":"not",info->crc);
    return 0;
}
int do_fastboot(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    if(fastboot_getconfig()<0){
        printf("get fastboot config fail\n");
        return 0;
    }
    if (fastboot_prepare()<0){
        printf("prepare for load image fail\n");
        return 0;
    }
    if(argc >= 2 && strcmp(argv[1],"f")==0){
        return fastboot_common(cmdtp, flag, argc, argv);
    }
    if(argc >= 2 && strcmp(argv[1],"i")==0){
        return fastboot_dumpinfo(cmdtp, flag, argc, argv);
    }
    if(argc >= 2 && strcmp(argv[1],"c")==0){
        return fastboot_checkcrc(cmdtp, flag, argc, argv);
    }
    if(fastbootmode!=2){
        printf("fastbootmode=%d, return\n",fastbootmode);
        return 0;
    }
    return fastboot_common(cmdtp, flag, argc, argv);
}

U_BOOT_CMD(fastboot,CONFIG_SYS_MAXARGS, 1, do_fastboot,
    "check and do fastboot",
    "  - check and do fastboot\n"
    "fastboot f - force to do fastboot\n"
    "fastboot i - dump fastboot image info\n"
    "fastboot c - check crc\n");

