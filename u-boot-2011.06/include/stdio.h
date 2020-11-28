#ifndef __CHAKRA_STDIO_H__
#define __CHAKRA_STDIO_H__

#include <stdarg.h>
//#include <stdlib.h>
#include <stddef.h>

#define PRINTF_CHAR_MAX     256

//typedef unsigned long   size_t;

#ifdef __cplusplus
extern "C" {
#endif

int vsnprintf(char *str, size_t size, const char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);
int snprintf(char *str, size_t size, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int vsscanf(const char * buf, const char * fmt, va_list args);
int sscanf(const char * buf, const char * fmt, ...);
#if !defined(CONFIG_JANUS) && !defined(CONFIG_MARIA10)
int printf(const char *format, ...);
#endif
int printk(const char *format, ...);
int putchar(int c);
#if !defined(CONFIG_JANUS) && !defined(CONFIG_MARIA10)
//cyber int puts(const char *s);
#endif
int getchar(void);

/* extension */
int kbhit(void);
unsigned int int_sqrt(unsigned int n);
void dump_backtrace(void);
void setconsole(int device_handle);

#ifdef __cplusplus
}
#endif

#endif /* __CHAKRA_STDIO_H__ */
