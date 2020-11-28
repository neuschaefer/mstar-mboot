#ifndef _ASM_INC_
#define _ASM_INC_
#ifdef CONFIG_MSTAR_STR_MINISIZE
#define __MSTRT .section  ".text.mstr", "ax"
#define __FINIT .previous
#else
#define __MSTRT
#define __FINIT
#endif
#endif