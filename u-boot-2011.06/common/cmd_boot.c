/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <net.h>

//#include <msboot.h>

#if CONFIG_MINIUBOOT
#undef CONFIG_CMD_GO
#endif
#ifdef CONFIG_CMD_GO

/* Allow ports to override the default behavior */
__attribute__((weak))
unsigned long do_go_exec (ulong (*entry)(int, char * const []), int argc, char * const argv[])
{
	return entry (argc, argv);
}

static ulong auto_search_kernel_entry( unsigned int s ){
    int i ;
    int len = 0x100000 ;
    unsigned int* p = (unsigned int*)s ;

#if !defined(CONFIG_JANUS) && !defined(CONFIG_MARIA10)
    for( i=0; i<len; i++ )
    {
        if( p[i]==0x3c08bf20 && p[i+1]==0x2409029f )
            return( (ulong)&(p[i]) ) ;
    }
#else
    for( i=0; i<len; i++ )
    {
        if( p[i]==0x3c08bf80 && p[i+1]==0x2409029f )
            return( (ulong)&(p[i]) ) ;
    }
#endif

    return( 0 ) ;
}


int do_go (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong	addr, rc;
	int     rcode = 0;

#if defined(CONFIG_KENYA)
    disable_interrupts();
    printf("disable interrupts\n");
#endif
    if( argv[1][0]=='.' )
    {
        extern void boot_rw_test(int argc, char * const argv[]);
        boot_rw_test(argc, argv);
        return 1;
    }

	if (argc < 2)
//        return cmd_usage(cmdtp);
    {
        printf ("Usage:\n%s\n", cmdtp->usage);
        addr = auto_search_kernel_entry(0x80880000) ;
        if( 0==addr )
            addr = auto_search_kernel_entry(0x80780000) ;
        if( 0==addr )
            addr = auto_search_kernel_entry(0x80980000) ;
        if( 0==addr )
            addr = auto_search_kernel_entry(0x80680000) ;
        if( 0==addr )
            addr = auto_search_kernel_entry(0x80A80000) ;
        if( 0==addr )
            addr = auto_search_kernel_entry(0x80B80000) ;
        if( 0==addr )
            addr = auto_search_kernel_entry(0x80C80000) ;
        if( 0==addr )
            addr = auto_search_kernel_entry(0x80580000) ;
        if( 0==addr )
            addr = auto_search_kernel_entry(0x80480000) ;
        if( 0==addr )
            addr = auto_search_kernel_entry(0x80D80000) ;
        if( 0==addr )
            return cmd_usage(cmdtp);
            //return 1 ;
        printf( "Auto Search Kernel_Entry: 0x%08luX\n", addr ) ;
    }else
        addr = simple_strtoul(argv[1], NULL, 16);

	printf ("## Starting application at 0x%08lX ...\n", addr);

	/*
	 * pass address parameter as argv[0] (aka command name),
	 * and all remaining args
	 */
	rc = do_go_exec ((void *)addr, argc - 1, argv + 1);
	if (rc != 0) rcode = 1;

	printf ("## Application terminated, rc = 0x%lX\n", rc);
	return rcode;
}

/* -------------------------------------------------------------------- */

#if CONFIG_MINIUBOOT
#else
U_BOOT_CMD(
	go, CONFIG_SYS_MAXARGS, 1,	do_go,
	"start application at address 'addr'",
	"addr [arg ...]\n    - start application at address 'addr'\n"
	"      passing 'arg' as arguments"
);
#endif
#endif

U_BOOT_CMD(
	reset, 1, 0,	do_reset,
	"Perform RESET of the CPU",
	""
);
