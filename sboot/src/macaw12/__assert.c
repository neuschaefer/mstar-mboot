#include <stdio.h>

extern const char g_str_assert[];

void __assert(const char *file, int line, const char *expr __attribute__((unused)))
{
    // please care about the stack size in printf()
    printf(g_str_assert, file, line);
    dump_backtrace();
    while(1);
}
