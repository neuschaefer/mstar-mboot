
#ifndef _INIPARSER_H
#define _INIPARSER_H

#define sizearray(a)    (sizeof(a) / sizeof((a)[0]))
extern char * strncpy(char * dest,const char *src,size_t count);

void Profile_Init(char *BufferAddr,unsigned int BufLen);
long Profile_GetInteger(const char *Section, const char *Key, long DefValue);
int Profile_GetString(const char *Section, const char *Key, const char *DefValue,char *Buffer, int BufferSize);
int Profile_GetBoolean(const char *Section, const char *Key, int DefValue);
#endif