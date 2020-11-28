@-------------------------------------------------------------------------------------------------
@ L2 cache setup
@-------------------------------------------------------------------------------------------------
L2_CACHE_ENABLE         = 1
L2_CACHE_WRITE_THROUGH  = 0
L2_CACHE_ALL_RQ_INTO_CACHE = 0
L2_CACHE_LINE_SIZE      = 128   @ other case = 64
L2_CACHE_UNCACHE_BUFFER = 0
L2_CACHE_MEMORY_PREFETCH = 0    @ if you want to use memory prefetch ,UNCACHE_BUFFER must set to 1
L2_CACHED_PREFETCH_BUF_LINE_SIZE = 64 @ other case = 32
L2_CACHE_HIGHWAY = 0


@-----------------------------------------
@ PL310 define
@-----------------------------------------

L2CC_PHYS = 0x15000000
L2CC_VIRT = 0xFB000000
L2CC_SIZE = 0x1000 


#[*] BootInitL2Cache
@-------------------------------------------------
@Macro: drv_pl310_init
@-------------------------------------------------
.macro drv_pl310_init
.endm