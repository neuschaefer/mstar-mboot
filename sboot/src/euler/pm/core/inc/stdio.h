#ifndef __CHAKRA_STDIO_H__
#define __CHAKRA_STDIO_H__

#include <stdarg.h>
//#include <stdlib.h>

#define PRINTF_CHAR_MAX     256

typedef unsigned long   size_t;

#ifdef __cplusplus
extern "C" {
#endif

int vsnprintf(char *str, size_t size, const char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap) __attribute__ ((deprecated));
int snprintf(char *str, size_t size, const char *format, ...);
int sprintf(char *str, const char *format, ...) __attribute__ ((deprecated));
int printf(const char *format, ...);
int printk(const char *format, ...);
int putchar(int c);
int puts(const char *s);

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
