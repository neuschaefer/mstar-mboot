typedef unsigned char   U8;
typedef unsigned int   U16;
typedef unsigned long  U32;
#include <stdio.h>
#include "../src/version.h"

void printUsage(char *progName)
{
    printf("Usage:\n\t%s [path to sboot.bin]\n\n", progName);
}

int main(int argc, char **argv)
{
    U8 i, *ptr;
    FILE *fp;

    if(argc !=2)
    {
        printUsage(argv[0]);
        return 1;
    }
    ptr = (U8*)&_sbt_version.APP;
    fp = fopen(argv[1], "r+w");
    if(fp != NULL)
    {
        fseek(fp, 0x10000-sizeof(_sbt_version.APP), SEEK_SET); // (end of sboot.bin) - (length of version string)
        for(i=0; i<sizeof(_sbt_version.APP); i++)
        {
            if(ptr[i] != (U8)fputc((int)ptr[i], fp))
                printf("Err(%d)\n", i);
        }

        fclose(fp);
    }
    else
    {
        printf("fclose() failed on file '%s'\n", argv[1]);
    }
    return 0;
}
