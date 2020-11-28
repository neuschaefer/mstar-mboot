/*
 * (C) Copyright 2000, 2001
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */

/*
 * Support for read and write access to EEPROM like memory devices. This
 * includes regular EEPROM as well as  FRAM (ferroelectic nonvolaile RAM).
 * FRAM devices read and write data at bus speed. In particular, there is no
 * write delay. Also, there is no limit imposed on the numer of bytes that can
 * be transferred with a single read or write.
 *
 * Use the following configuration options to ensure no unneeded performance
 * degradation (typical for EEPROM) is incured for FRAM memory:
 *
 * #define CONFIG_SYS_I2C_FRAM
 * #undef CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS
 *
 */

#include <common.h>
#include <command.h> 
#if defined(CONFIG_CMD_EEPROM) && (CONFIG_MSTARI2C == 1)
#include <exports.h>
#include <apiSWI2C.h>
#include <CusConfig.h>
#include <MsOS.h>
#include <MsDebug.h>
#include <ShareType.h>


#define EEPROM_PAGESIZE           0x10
#define HIBYTE(value)     ((MS_U8)((value) / 0x100))
#define LOBYTE(value)     ((MS_U8)(value))
int   addrnum = 0;
MS_U16 dev_addr = 0;

const char *const fmt = "\nEEPROM @0x%lX(%d) %s: addr %08lx  off %04lx  count %ld ... \n";

/* ------------------------------------------------------------------------- */
int eeprom_PageRead(MS_U16 offset, MS_U8 *pBuf, MS_U16 u16BufLen)
{
     int   addr_num_tmp = 0;
     MS_U16 dev_addr_tmp = 0;    
     int write_count=0;   
     MS_U8 pu8addr[2];
    
     while(u16BufLen>0)
     {       
        if (dev_addr == 0)    
        {
            dev_addr_tmp = EEPROM_ADDR;
            addr_num_tmp  = EEPROM_ADDR_NUM;
        }
        else
        {
            dev_addr_tmp = dev_addr;
            addr_num_tmp = addrnum;            
        }         
         UBOOT_DEBUG(fmt, dev_addr_tmp,addr_num_tmp,"read", pBuf,offset, u16BufLen);          
        if(addr_num_tmp == 1)
        {
            pu8addr[0] = LOBYTE(offset);
            dev_addr_tmp = dev_addr_tmp|((HIBYTE(offset)<<1));
        }
        else    
        {    
            pu8addr[0] = HIBYTE(offset);
            pu8addr[1] = LOBYTE(offset);                 
        }             
    
        if(u16BufLen >= EEPROM_PAGESIZE)
        {
            write_count = EEPROM_PAGESIZE;
            u16BufLen = u16BufLen - EEPROM_PAGESIZE;
        }
        else
        {
            write_count = u16BufLen;
            u16BufLen = 0;
        }                     
        if(MApi_SWI2C_ReadBytes((MS_U16)dev_addr_tmp, addr_num_tmp, (MS_U8*)pu8addr,(MS_U16)write_count, (MS_U8*)(pBuf)) != TRUE)
        {
            UBOOT_ERROR("MApi_SWI2C_ReadBytes FAIL!!\n");
            return -1;
        }           
        pBuf+=write_count;
        offset+=write_count;   
    }   
     return 0;

}

int eeprom_PageWrite(MS_U16 offset, MS_U8 *pBuf, MS_U16 u16BufLen)
{

    int   addr_num_tmp = 0;
    MS_U16 dev_addr_tmp = 0;    
    int write_count=0;   
    MS_U8 pu8addr[2];

    while(u16BufLen>0)
    {       
       if (dev_addr == 0)    
       {
           dev_addr_tmp = EEPROM_ADDR;
           addr_num_tmp  = EEPROM_ADDR_NUM;
       }
       else
       {
           dev_addr_tmp = dev_addr;
           addr_num_tmp = addrnum;            
       }         
        UBOOT_DEBUG(fmt, dev_addr_tmp,addr_num_tmp,"write", pBuf,offset, u16BufLen);         
       if(addr_num_tmp == 1)
       {
           pu8addr[0] = LOBYTE(offset);
           dev_addr_tmp = dev_addr_tmp|((HIBYTE(offset)<<1));
       }
       else    
       {    
           pu8addr[0] = HIBYTE(offset);
           pu8addr[1] = LOBYTE(offset);                 
       }             

       if(u16BufLen >= EEPROM_PAGESIZE)
       {
           write_count = EEPROM_PAGESIZE;
           u16BufLen = u16BufLen - EEPROM_PAGESIZE;
       }
       else
       {
           write_count = u16BufLen;
           u16BufLen = 0;
       }                     
       if(MApi_SWI2C_WriteBytes((MS_U16)dev_addr_tmp, addr_num_tmp, (MS_U8*)pu8addr,(MS_U16)write_count, (MS_U8*)(pBuf)) != TRUE)
       {
           UBOOT_ERROR("MApi_SWI2C_WriteBytes FAIL!!\n");
           return -1;
       }   
       MsOS_DelayTask(10);          
       pBuf+=write_count;
       offset+=write_count;   
   }   
    return 0;

}


int do_eeprom ( cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
    MS_U32 addr = 0;
    MS_U32 off = 0;
    MS_U16 cnt = 0;
    char * data = NULL;
    int ret = 0;
    char buffer[CMD_BUF]="\0";

    if (argc < 2) 
    {     
        return cmd_usage(cmdtp);
    }
    if (strncmp (argv[1], "wb", 2) == 0) 
    {
         off=simple_strtoul (argv[2], NULL, 16);
         addr=simple_strtoul (argv[3], NULL, 16);         
         ret = eeprom_PageWrite(off, (MS_U8 *)&addr, 1);

    }
    else if (strncmp (argv[1], "rb", 2) == 0) 
    {
		off  = simple_strtoul (argv[2], NULL, 16);        
        ret = eeprom_PageRead(off,(MS_U8 *)&addr,1);        
        UBOOT_INFO("0x%x\n",(unsigned int)addr);
    }
    else if (strncmp (argv[1], "ws", 2) == 0)
    {
		off = simple_strtoul (argv[2], NULL, 16);
		data = (char *)argv[3];       
        ret = eeprom_PageWrite(off,(MS_U8*)data,strlen(data));        
    }
	else if (strncmp (argv[1], "dump", 4) == 0) 
    {        
 		off  = simple_strtoul (argv[2], NULL, 16);
		cnt  = simple_strtoul (argv[3], NULL, 16);       
        data=(char *)malloc(cnt);
        if(data==NULL)
        {
            UBOOT_ERROR("memory allocate fail\n");
            return -1;
        }
        eeprom_PageRead(off,(MS_U8 *)data,cnt);
        snprintf(buffer,CMD_BUF,"md.b %x %x",data,cnt);
        run_command(buffer,0); 
    }    
	else if (strncmp (argv[1], "read", 4) == 0) 
    {        
		addr = simple_strtoul (argv[2], NULL, 16);
		off  = simple_strtoul (argv[3], NULL, 16);
		cnt  = simple_strtoul (argv[4], NULL, 16);
        ret = eeprom_PageRead(off,(MS_U8*)addr,cnt);
    }
    else if (strncmp (argv[1], "write", 5) == 0) 
    {        
		addr = simple_strtoul (argv[2], NULL, 16);
		off  = simple_strtoul (argv[3], NULL, 16);
		cnt  = simple_strtoul (argv[4], NULL, 16);
		ret = eeprom_PageWrite(off,(MS_U8*)addr,cnt);
	}
    else if (strncmp (argv[1], "erase", 5) == 0) 
    {
		cnt  = simple_strtoul (argv[2], NULL, 16);       
        data=(char *)malloc(cnt);
        memset((void *)data,0xFF,cnt);
        ret = eeprom_PageWrite(off,(MS_U8*)data,cnt);           
    }    
    else if (strncmp (argv[1], "switch", 5) == 0) 
    {
        dev_addr = simple_strtoul (argv[2], NULL, 16);
        addrnum  = simple_strtoul (argv[3], NULL, 16);
        printf("dev_addr : 0x%x\n",(unsigned int)dev_addr);
        printf("addrnum : %d\n",addrnum);    
    }

    else
    {
        cmd_usage(cmdtp);
    }

	return ret;
}


U_BOOT_CMD(
	eeprom,	5,	1,	do_eeprom,
	"EEPROM sub-system",
	"wb [eeprom offset] [value(byte)]\n"	
	"eepeom rb [eeprom offset]\n"
	"eeprom ws [eeprom offset] [string]\n"	
    "eeprom dump [eeprom offset] [cnt]\n"	
	"eeprom read [addr] [eeprom offset] [count]\n"
	"eeprom write [addr] [eeprom offset] [count]\n"
	"       - read/write `cnt' bytes from `devaddr` EEPROM at offset `off'\n"
	"eeprom erase [eeprom_size]\n"	
	"eeprom siwtch :[dev_addr] [dev_addr_num]"
);


#endif
