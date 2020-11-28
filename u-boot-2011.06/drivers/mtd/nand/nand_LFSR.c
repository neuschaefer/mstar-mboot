#include <common.h>
#include <linux/mtd/mtd.h>
#include <nand.h>

#define NAND_PAGE_SEEDCNT    0x80

#ifndef BIT0
#define BIT0    (1<<0)
#endif
#ifndef BIT1
#define BIT1    (1<<1)
#endif
#ifndef BIT2
#define BIT2    (1<<2)
#endif
#ifndef BIT3
#define BIT3    (1<<3)
#endif
#ifndef BIT4
#define BIT4    (1<<4)
#endif
#ifndef BIT5
#define BIT5    (1<<5)
#endif
#ifndef BIT6
#define BIT6    (1<<6)
#endif
#ifndef BIT7
#define BIT7    (1<<7)
#endif
#ifndef BIT8
#define BIT8    (1<<8)
#endif
#ifndef BIT9
#define BIT9    (1<<9)
#endif
#ifndef BIT10
#define BIT10   (1<<10)
#endif
#ifndef BIT11
#define BIT11   (1<<11)
#endif
#ifndef BIT12
#define BIT12   (1<<12)
#endif
#ifndef BIT13
#define BIT13   (1<<13)
#endif
#ifndef BIT14
#define BIT14   (1<<14)
#endif
#ifndef BIT15
#define BIT15   (1<<15)
#endif

unsigned short gau16_seeds[]={
#include "seeds_lfsr.txt"
};

#define SEC_LFSR_SHIFT0(u16_new, u16_old) \
    u16_new = ((u16_old&BIT14)>>14 ^ (u16_old&BIT0))  |\
              (u16_old&BIT13)<<1 | (u16_old&BIT12)<<1 |\
              (u16_old&BIT11)<<1 | (u16_old&BIT10)<<1 |\
              (u16_old&BIT9)<<1  | (u16_old&BIT8)<<1  |\
              (u16_old&BIT7)<<1  | (u16_old&BIT6)<<1  |\
              (u16_old&BIT5)<<1  | (u16_old&BIT4)<<1  |\
              (u16_old&BIT3)<<1  | (u16_old&BIT2)<<1  |\
              (u16_old&BIT1)<<1  | (u16_old&BIT0)<<1;
#define SEC_LFSR_SHIFT1(u16_new, u16_old) \
    u16_new = ((u16_old&BIT14)>>14 ^ (u16_old&BIT13)>>13) |\
              (u16_old&BIT13)<<1 | (u16_old&BIT12)<<1 |\
              (u16_old&BIT11)<<1 | (u16_old&BIT10)<<1 |\
              (u16_old&BIT9)<<1  | (u16_old&BIT8)<<1  |\
              (u16_old&BIT7)<<1  | (u16_old&BIT6)<<1  |\
              (u16_old&BIT5)<<1  | (u16_old&BIT4)<<1  |\
              (u16_old&BIT3)<<1  | (u16_old&BIT2)<<1  |\
              (u16_old&BIT1)<<1  | (u16_old&BIT0)<<1;

#define LFSR_TYPE0    SEC_LFSR_SHIFT0
#define LFSR_TYPE1    SEC_LFSR_SHIFT1 // A Sir chooses this one

//===========================================================
void LFSR1_16Lines_8IOs(unsigned short au16_DatIn[], unsigned short au16_BufOut[], unsigned int u32_ByteCnt, unsigned short u16_Page)
{
    unsigned short au16_LFSR_Value[2*16]; 
    unsigned short *pu16_LFSR_new[16], *pu16_LFSR_old[16];
    unsigned char  u8_data_src;
    unsigned short u16_bit, u16_byte, u16_i;
    unsigned char  *pu8_data_src, *pu8_data_dest;

    // pre-select 16 seeds
    for(u16_byte=0; u16_byte<16; u16_byte++)
    {
    	u16_i = u16_byte + u16_Page;
    	
    	while(u16_i >= NAND_PAGE_SEEDCNT)
    		u16_i -= NAND_PAGE_SEEDCNT;
    	
    	au16_LFSR_Value[u16_byte] = gau16_seeds[u16_i];
    }

    // scramble
    for(u16_byte=0; u16_byte<u32_ByteCnt; u16_byte++)
    {
    	pu8_data_src = (unsigned char*)(((unsigned char*)&au16_DatIn[u16_byte/2])+(u16_byte&1));
    	pu8_data_dest= (unsigned char*)(((unsigned char*)&au16_BufOut[u16_byte/2])+(u16_byte&1));
    	
    	u8_data_src = *pu8_data_src;
    	*pu8_data_dest = 0;

    	// setup 16 LFSRs
    	for(u16_i=0; u16_i<16; u16_i++)
    	{
            pu16_LFSR_old[u16_i] = &au16_LFSR_Value[16*(u16_byte&1)+u16_i];
            pu16_LFSR_new[u16_i] = &au16_LFSR_Value[16*(~(u16_byte&1)&BIT0)+u16_i];
            
            #if 0
            // printf seeds
            if(0 == u16_i)
                printf("\nword: %02X\n", u16_byte);
            
            printf("%04X ", *pu16_LFSR_old[u16_i]);
            #endif
    	}

    	//printf("%s: dat:%04X, lfsr:%04X \n", "LFSR_Scramble", u8_data_src, au16_LFSR_Value[0]);

        for(u16_bit=0; u16_bit<8; u16_bit++)
        {
            *pu8_data_dest |= ((u8_data_src&BIT0) ^ 
                ((*pu16_LFSR_old[u16_bit]&BIT14)>>14 ^ (*pu16_LFSR_old[u16_bit]&BIT13)>>13))<<u16_bit;
    	    u8_data_src >>= 1;
        }

    	for(u16_i=0; u16_i<16; u16_i++)
    	    LFSR_TYPE1(*pu16_LFSR_new[u16_i], *pu16_LFSR_old[u16_i]);
    }
	//printf("dat:%04X, lfsr:%04X \n", au16_BufOut[u16_byte-1], *pu16_LFSR_new);
}
