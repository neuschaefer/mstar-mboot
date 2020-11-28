#include <stdio.h>
#include <stdlib.h>

unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base)
{
	unsigned long result = 0,value;

	if (*cp == '0') {
		cp++;
		if ((*cp == 'x') && isxdigit(cp[1])) {
			base = 16;
			cp++;
		}
		if (!base) {
			base = 8;
		}
	}
	if (!base) {
		base = 10;
	}
	while (isxdigit(*cp) && (value = isdigit(*cp) ? *cp-'0' : (islower(*cp)
	    ? toupper(*cp) : *cp)-'A'+10) < base) {
		result = result*base + value;
		cp++;
	}
	if (endp)
		*endp = (char *)cp;
	return result;
}

int main(int argc, const char *argv[])
{
    int ret = 1;
    FILE* pfSourceFile = NULL;
    FILE* pfReplaceFile = NULL;
    FILE* pfTargetFile = NULL;
    if(argc != 5)
    {
        printf("usage : merge [Mboot.bin] [CustomerInfo.bin] [Merge.bin] [Merge Position 0x(hex)] \n");
        goto file_handle;
    }
    const char* pSourceFile = argv[1];
    const char* pReplaceFile = argv[2];
    const char* pTargetFile = argv[3];
    ulong ulMergePosition = 0;

    pfTargetFile = fopen(pTargetFile,"w");
    if(NULL == pfTargetFile)
    {
        printf("open %s fail!!\r\n",pTargetFile);
        goto error_delete;
    }
    
    pfSourceFile = fopen(pSourceFile,"r");
    if(NULL == pfSourceFile)
    {
        printf("open %s fail!!\r\n",pSourceFile);
        goto error_delete;
    }
    pfReplaceFile = fopen(pReplaceFile,"r");
    if(NULL == pfReplaceFile)
    {
        printf("open %s fail!!\r\n",pReplaceFile);
        goto error_delete;
    }

    ulMergePosition = simple_strtoul(argv[4], NULL, 16);

    printf("[ Merge %s into %s at position 0x%lX ==> %s Start ]\r\n",pReplaceFile,pSourceFile,ulMergePosition,pTargetFile);
    unsigned char buffer = 0;
    // === cat source file
    unsigned long long index = 0;
    while(index<ulMergePosition)
    {
        if(1!=fread(&buffer,sizeof(buffer),1,pfSourceFile))
        {
            printf("Merge Interrupt, fread %s fail, ulMergePosition : %lu > filesize!!!\r\n",pSourceFile,ulMergePosition);
            goto error_delete;
        }
        else if(1!=fwrite(&buffer,sizeof(buffer),1,pfTargetFile))
        {
            printf("Merge Interrupt, fwrite %s fail!!!\r\n",pTargetFile);
            goto error_delete;
        }
        index++;
    }

    printf("===== [%s:%s:%d] insert start : 0x%llX=====\r\n",__FILE__,__FUNCTION__,__LINE__,index);

    // === cat replace file
    while( (!feof(pfReplaceFile)) )
    {
        if(1!=fread(&buffer,sizeof(buffer),1,pfReplaceFile))
        {
            break;
        }
        else if(1!=fwrite(&buffer,sizeof(buffer),1,pfTargetFile))
        {
            printf("Content Replace Interrupt, fwrite %s fail!!!\r\n",pTargetFile);
            goto error_delete;
        }
        index++;
    }

    printf("===== [%s:%s:%d] insert finished : 0x%llX=====\r\n",__FILE__,__FUNCTION__,__LINE__,index);
    
    if(0 != fseek( pfSourceFile , index , SEEK_SET ))
    {
        printf("seek %s offset 0x%llX fail!!\r\n",pSourceFile,index);
        goto error_delete;
    }

    // === cat replace file
    while( (!feof(pfSourceFile)) )
    {
        if(1!=fread(&buffer,sizeof(buffer),1,pfSourceFile))
        {
            break;
        }
        else if(1!=fwrite(&buffer,sizeof(buffer),1,pfTargetFile))
        {
            printf("Content Replace Interrupt, fwrite %s target file fail!!!\r\n",pTargetFile);
            goto error_delete;
        }
    }
    
    printf("[ Merge %s into %s at position 0x%lX ==> %s Done ]\r\n",pReplaceFile,pSourceFile,ulMergePosition,pTargetFile);
    ret = 0;
    goto file_handle;
error_delete:
    printf("=====   Delete %s !!!   =====\r\n",pTargetFile);
    if( remove( pTargetFile ) != 0 )
        perror( "Error deleting file" );
file_handle:
    if(NULL != pfTargetFile)
        fclose(pfTargetFile);
    if(NULL != pfReplaceFile)
        fclose(pfReplaceFile);
    if(NULL != pfSourceFile)
        fclose(pfSourceFile);
    return ret;
}

