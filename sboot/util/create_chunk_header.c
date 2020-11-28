#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

unsigned int  _atoi(char *str)
{
	
	unsigned int  value=0;

       if(*str=='\0') return  value;

	if((str[0]=='0')&&((str[1]=='x')||(str[1]=='X'))){   
	// 16Hex

		str+=2;
		while(1){

		   if(*str>=0x61)
		   	*str-=0x27;
		   else if(*str>=0x41)
		   	*str-=0x07;
		   
		   value|=(*str-'0');
		   str++;
		   //i++;
	          if(*str=='\0') break;
		   value=value<<4;	  
	      }
	}
	else{
	// 10 Dec

	       unsigned int  len,tmp=1;;	
		len=strlen(str);
		
		while(len){
			if(*str>'9') return 0;
			
			value+=((str[len-1]-'0')*tmp);

			len--;
			tmp=tmp*10;
	       }
	}
	return value;
	
}
int main(int argc, char* argv[])
{
	#define OUTPUT_FILE_NAME argv[1]
	#define OUTPUT_FILZE_MAX_SIZE argv[2]
	FILE *fswrite=NULL;
	
	unsigned int totalParamNum=0;
	unsigned int index=0;
	unsigned int tempValue;
	unsigned int currSize=0;
	unsigned int spareSize=0;
	unsigned int maxSize=0;
	
	if(argc<4)
	{
		printf("Error usage\n");
		printf("SYNOPSIS: ./create_chunk_header [OUTPUT FILE NAME] [OUTPUT FILE MAX SIZE] [DATA1] [DATA2] [DATA3] .....\n");
		return -1;
	}
	fswrite=fopen(OUTPUT_FILE_NAME, "wb");
	if(fswrite==NULL)
	{
		printf("[Error] open $s fail\n",OUTPUT_FILE_NAME);
		return -1;
	}
	totalParamNum=argc-3;
	index+=3;
	while(totalParamNum!=0)
	{
		//printf("argv[%d]=%s ",index, argv[index]);
		tempValue=_atoi(argv[index]);
		//printf("tempValue=%x\n",tempValue);
		if(fwrite(&tempValue,1,sizeof(int),fswrite)!=sizeof(int))
		{
			fclose(fswrite);
			printf("[Error] create chunk header fail\n");
			return -1;
		}
		
		totalParamNum-=1;
		index++;
	}
	
	currSize=ftell(fswrite);
	maxSize=_atoi(OUTPUT_FILZE_MAX_SIZE);
	spareSize=maxSize-currSize;
	//printf("maxSize size =%x\n",maxSize);
	//printf("spare size =%x\n",spareSize);
	//printf("currSize size =%x\n",currSize);
	tempValue=0xFFFFFFFF;
	while(spareSize!=0)
	{
		if(fwrite(&tempValue,1,sizeof(char),fswrite)!=sizeof(char))
		{
			fclose(fswrite);
			printf("[Error] create chunk header fail\n");
			return -1;
		}
		spareSize--;
	}
	
	fclose(fswrite);
    return 0;
}
