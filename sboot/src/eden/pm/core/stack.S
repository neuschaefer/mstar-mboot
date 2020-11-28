#include "./inc/risc32.inc"

.section ".text", "ax"

ENTRY(mhal_stack_init)
    l.or    sp,p0,p0

    ## Dummy frame for stack backtrace
    l.addi  sp,sp,-8
    l.sw    4(sp),r0        # LR
    l.sw    0(sp),r0        # FP
#ifdef __AEONR2__
    l.addi  fp,sp,8         # previous FP
    l.jr    lr
#else
    l.jr    lr
    l.addi  fp,sp,8         # previous FP
#endif
