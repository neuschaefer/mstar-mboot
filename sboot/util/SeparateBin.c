#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// Convert binary file into HEX bytes for being included in a .c file.
int   str2hex(char*   pInput,   unsigned   char*   pOutput,   int*   len)
{
    char c1, c2;
    int i, length;
    
    length = strlen(pInput);
    if(length%2)
    {
        return 0;
    }
    
    for(i=0; i<length; i++)
    {
    	pInput[i] = toupper(pInput[i]);
    }
    
    for(i=0; i< length/2; i++)
    {
        c1 = pInput[2*i];
        c2 = pInput[2*i+1];
        if(c1<'0' || (c1 > '9' && c1 <'A') || c1 > 'F')
        {
            continue;
        }
        
        if(c2<'0' || (c2 > '9' && c2 <'A') || c2 > 'F')
        {
            continue;
        }
        
        c1 = c1>'9' ? c1-'A'+10 : c1 -'0';
        c2 = c2>'9' ? c2-'A'+10 : c2 -'0';
        pOutput[i] = c1<<4 | c2;
    }
    *len = i;
    return 1;
}

unsigned long str2int(char *str)
{
    unsigned char is_hex_type = 0;
    unsigned long out = 0;
    char c;
    int i, length;

    if (NULL == str)
    {
        return 0;
    }
    
    length = strlen(str);
    for(i=0; i<length; i++)
    {
    	str[i] = toupper(str[i]);
    }
    
    if (str[0] == '0' && str[1] == 'X')
    {
        is_hex_type = 1;
    }

    i = (is_hex_type) ? 2 : 0;
    for (;i<length;i++)
    {
        c = str[i];
        if (is_hex_type)
        {
            if (c<'0' || (c>'9' && c<'A') || c>'F')
            {
                return 0;
            }
            c = (c>'9') ? (c-'A'+10) : (c-'0');
            out = (16*out)+c;
        }
        else
        {
            if (c<'0' || c>'9')
            {
                return 0;
            }
            c = c-'0';
            out = (10*out)+c;
        }
    }
    return out;
}

int main(int argc, char* argv[])
{
	#define SOURCE_FILE argv[1]
	#define TARGET_FILE argv[2]
	#define OFFSET 	    argv[3]
	#define LEN 	    argv[4]
    FILE *fsR=NULL;
	FILE *fsW=NULL;
	unsigned int fileLen=0;
	unsigned int offset=0;
	char buf=0;
	unsigned int len;
	//printf("argv[1]=%s\n",SOURCE_FILE);
	//printf("argv[2]=%s\n",TARGET_FILE);
	//printf("argv[3]=%s\n",OFFSET);
	//printf("argv[4]=%s\n",LEN);
	//printf("argc=%d\n",argc);
	
	if(argc<4){
		printf("SeparateBin fail argc number <=4 !!\n");
		return -1;
	}
	
	fsR=fopen(SOURCE_FILE,"r");
	if(fsR==NULL){
		printf("SeparateBin fail %s !!\n", SOURCE_FILE);
		return -1;
	}
	
	fseek(fsR, 0, SEEK_END);
	fileLen=ftell(fsR);
	//printf("fileLen=%d\n",fileLen);
	fseek(fsR, 0, SEEK_SET);
	offset=str2int(OFFSET);
	//printf("offset=%d\n",offset);
	
	if(LEN==NULL){
		if(offset>fileLen){
			printf("SeparateBin fail offset is over file length !!\n");
			fclose(fsR);
			return -1;
		}
	}
	else{
		len=str2int(LEN);
		if((offset+len)>fileLen){
			printf("SeparateBin fail offset+len is over file length !!\n");
			fclose(fsR);
			return -1;
		}
	}
	
	fsW=fopen(TARGET_FILE,"wb");
	if(fsW==NULL){
		printf("SeparateBin fail open %s fail !!\n",TARGET_FILE);
		fclose(fsR);
		return -1;
	}
	
	fseek(fsR, offset, SEEK_SET);
	if(LEN==NULL)
		fileLen=fileLen-(offset+1);
	else
		fileLen=len;
		
	//printf("fileLen=%d\n",fileLen);
	while(fileLen){
		fread(&buf, 1, sizeof(char),fsR);
		fwrite(&buf, 1, sizeof(char),fsW);
		fileLen-=1;
	}
	fclose(fsR);
	fclose(fsW);
	
	
	
	
    printf("SeparateBin Done !!\n");
    return 0;
}
