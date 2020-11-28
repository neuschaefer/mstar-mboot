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
    FILE *t_fpin_s, *t_fpin_d;
    int gap, src_len, dest_len;
    unsigned long append_addr;
    unsigned char *pBuf, *pSBuf;

    if (4 != argc)
    {
        printf("Usage: %s <source path> <destination path> <append address> \n", argv[0]);
        return 0;
    }

    if (NULL == (t_fpin_s = fopen(argv[1], "rb")))
    {
        printf("[Error]cannot open %s\n", argv[1]);
        return -1;
    }

    if (NULL == (t_fpin_d = fopen(argv[2], "ab+")))
    {
        printf("[Error]cannot open %s\n", argv[2]);
        return -1;
    }

		append_addr = str2int(argv[3]);
		
    fseek(t_fpin_s, 0, SEEK_END);
    src_len = ftell(t_fpin_s);
    fseek(t_fpin_s, 0, SEEK_SET);

    fseek(t_fpin_d, 0, SEEK_END);
    dest_len = ftell(t_fpin_d);
    fseek(t_fpin_d, 0, SEEK_SET);
    
			gap = append_addr - dest_len;
			//printf("append_addr = 0x%x, dest_len = 0x%X, gap = 0x%X\n", append_addr, dest_len, gap);

			if(append_addr == 0)
		  {
				gap = 0;
			}
					
			if(gap<0)
		  {
	    	pBuf = (unsigned char *)malloc(dest_len + src_len);
	    	memset(pBuf, 0, dest_len + src_len);

	      fseek(t_fpin_d, 0, SEEK_SET);
				fread(&pBuf[0], 1, dest_len, t_fpin_d);
					    	
	      fread(&pBuf[append_addr], 1, src_len, t_fpin_s);
	      
	      fclose(t_fpin_d);

		    if (NULL == (t_fpin_d = fopen(argv[2], "wb")))
		    {
		        printf("[Error]cannot open %s\n", argv[2]);
		        return -1;
		    }
		    
	    	fwrite(&pBuf[0], sizeof(unsigned char), (append_addr + src_len), t_fpin_d);
	    	free(pBuf);
	    }
	    else
	    {
	    	pBuf = (unsigned char *)malloc(dest_len + gap + src_len);
				memset(pBuf, 0, dest_len + gap + src_len);

	      fseek(t_fpin_d, 0, SEEK_SET);
				fread(&pBuf[0], 1, dest_len, t_fpin_d);
					      				
				fread(&pBuf[dest_len + gap], 1, src_len, t_fpin_s);
				
	      fclose(t_fpin_d);

		    if (NULL == (t_fpin_d = fopen(argv[2], "wb")))
		    {
		        printf("[Error]cannot open %s\n", argv[2]);
		        return -1;
		    }
		    
	    	fwrite(&pBuf[0], sizeof(unsigned char), (dest_len + gap + src_len), t_fpin_d);
	    	free(pBuf);
	    }
		
    fclose(t_fpin_s);
    fclose(t_fpin_d);
    printf("MergeBin Done !!\n");
    return 0;
}
