
#include "eMMC.h"


// return in MB
U32 eMMC_get_WPGropuSize(void)
{
    return g_eMMCDrv.u8_ECSD224_HCEraseGRPSize * 
        g_eMMCDrv.u8_ECSD221_HCWpGRPSize / 2;
}


U32 eMMC_get_UserWPStatus(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
	U32 u32_err;

    u32_err = eMMC_CMD31_MIU(u32_eMMCBlkAddr, pu8_DataBuf);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL, 1, "eMMC Err: CMD31 fail: %Xh \n", u32_err);
        return u32_err;
    }
    
    // -------------------------------
    //eMMC_dump_mem((U8*)pu8_DataBuf, 0x10);
    switch(pu8_DataBuf[7]&3)
    {
        case 0:  eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC: blk %Xh not-protected.\n", u32_eMMCBlkAddr);
            break;
        case 1:  eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC: blk %Xh temp-protected.\n", u32_eMMCBlkAddr);
            break;
        case 2:  eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC: blk %Xh PwrOn-protected.\n", u32_eMMCBlkAddr);
            break;
        case 3:  eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC: blk %Xh Perm-protected.\n", u32_eMMCBlkAddr);
            break;
    }
	return u32_err;

}


U32 eMMC_set_UserWP(U32 u32_eMMCBlkAddr, u16 u16_Flag)
{
	U32 u32_err;
    U8 u8_ECSD171=0;

    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_SetBit, 175, 1);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: set ERASE_GROUP_DEF fail: %Xh \n", u32_err);
        return u32_err;
    }
    
    switch(u16_Flag)
    {
        case USER_TEMP: u8_ECSD171 = 0;  break;
        case USER_PWR:  u8_ECSD171 = PWR_WP_EN;  break;
        case USER_PERM: u8_ECSD171 = PERM_WP_EN; break;
        
        default:
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: unknown flag: %Xh \n", u16_Flag);
            return eMMC_ST_ERR_INVALID_PARAM;
    }

    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 171, u8_ECSD171);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: set USER_WP fail: %Xh \n", u32_err);
        return u32_err;
    }
    
    u32_err = eMMC_CMD28(u32_eMMCBlkAddr);
    if(eMMC_ST_SUCCESS != u32_err)
        eMMC_debug(eMMC_DEBUG_LEVEL, 1, "eMMC Err: CMD28 fail: %Xh \n", u32_err);

    return u32_err;
}


U32 eMMC_set_BootWP(U16 u16_Flag)
{
    static U8 u8_IfSet=0;
    U8 u8_ECSD173=0;
    U32 u32_err;

    if(u8_IfSet)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: BOOT_WP already set \n");
        eMMC_get_BootWPStatus();
        return eMMC_ST_ERR_WP_BOOT_PWR_FAIL;
    }

    switch(u16_Flag)
    {
        case BOOT1_PWR:
            u8_ECSD173 = SEC_WP_SEL|PWR_WP_EN;
            break;
        case BOOT2_PWR:
            u8_ECSD173 = SEC_WP_SEL|PWR_WP_SEL|PWR_WP_EN;
            break;
        case BOTH_PWR:
            u8_ECSD173 = PWR_WP_EN;
            break;
        case BOOT1_PERM:
            u8_ECSD173 = SEC_WP_SEL|PERM_WP_EN;
            break;
        case BOOT2_PERM:
            u8_ECSD173 = SEC_WP_SEL|PERM_WP_SEL|PERM_WP_EN;
            break;
        case BOTH_PERM:
            u8_ECSD173 = PERM_WP_EN;
            break;
        default:
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: unknown flag: %Xh \n", u16_Flag);
            return eMMC_ST_ERR_INVALID_PARAM;
    }

    u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_SetBit, 173, u8_ECSD173);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: set BOOT_WP fail: %Xh, %Xh \n", u32_err, u8_ECSD173);
        eMMC_get_BootWPStatus();
        return u32_err;
    }

    u8_IfSet=1;
    return eMMC_ST_SUCCESS;
}


// return a status
U32 eMMC_get_BootWPStatus(void)
{
    U32 u32_err, u32_ret=0;
    U8  u8_status, u8_stop=0;

	u32_err = eMMC_CMD8(gau8_eMMC_SectorBuf);
	if(eMMC_ST_SUCCESS != u32_err)
	{
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: CMD8 fail: %Xh\n", u32_err);
		return u32_err;
	}

    //-------------------------------
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"ECSD[174]: %Xh  ECSD[173]: %Xh  %uKB\n", 
        gau8_eMMC_SectorBuf[174], gau8_eMMC_SectorBuf[173], g_eMMCDrv.u8_BOOT_SIZE_MULT*0x80);

    u8_status = gau8_eMMC_SectorBuf[174] & (BIT1|BIT0);
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"Boot1: ");
    
    LABEL_SHOW_SATUS:
    switch(u8_status)
    {
        case 0: 
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"not protected. \n"); 
            u32_ret+=0;
            break;
        case 1: 
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"Power-On protected. \n"); 
            u32_ret+=1;
            break;
        case 2: 
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"Permanently protected. \n"); 
            u32_ret+=2;
            break;
        default: 
            eMMC_debug(eMMC_DEBUG_LEVEL,0,"unknown ! \n");
            u32_ret+=3;
    }

    if(u8_stop)
        return u32_ret;
    
    u8_status = (gau8_eMMC_SectorBuf[174] & (BIT3|BIT2))>>2;
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"Boot2: ");
    u8_stop = 1;
    goto LABEL_SHOW_SATUS;

    return u32_ret;
}


// ===========================================================
// for test
// ===========================================================
// write/read/checksum
#define USER_WP_TEST_DATA_BYTECNT   0x400
U32 eMMC_verify_UserWP_WRC(U32 u32_eMMCBlkAddr)
{
    U32 u32_err, u32_i, u32_ChkSum, u32_tmp;

    u32_err = eMMC_get_UserWPStatus(u32_eMMCBlkAddr, gau8_eMMC_SectorBuf);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Err: get_UserWPStatus fail.1: %Xh \n", u32_err);
        return u32_err;
    }
    
    // -----------------------------
    // write & check data
    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "\neMMC: write & check %Xh data @ %Xh blk\n", 
        USER_WP_TEST_DATA_BYTECNT, u32_eMMCBlkAddr);
    
    for(u32_i=0; u32_i<USER_WP_TEST_DATA_BYTECNT; u32_i++)
        gau8_eMMC_SectorBuf[u32_i] = u32_i+1;
    
    u32_ChkSum = eMMC_ChkSum(gau8_eMMC_SectorBuf, USER_WP_TEST_DATA_BYTECNT);
    
    u32_err = eMMC_WriteData(gau8_eMMC_SectorBuf, USER_WP_TEST_DATA_BYTECNT, u32_eMMCBlkAddr);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Err: WriteData fail.1: %Xh \n", u32_err);
        return u32_err;
    }
    u32_err = eMMC_ReadData(gau8_eMMC_SectorBuf, USER_WP_TEST_DATA_BYTECNT, u32_eMMCBlkAddr);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Err: ReadData fail.1: %Xh \n", u32_err);
        return u32_err;
    }

    u32_tmp = eMMC_ChkSum(gau8_eMMC_SectorBuf, USER_WP_TEST_DATA_BYTECNT);
    if(u32_ChkSum != u32_tmp)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Err: ChkSum fail.1: %Xh %Xh\n", u32_ChkSum, u32_tmp);
        return eMMC_ST_ERR_CHKSUM;
    }
    
    // -----------------------------
    // set config
    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "eMMC: set WP \n");
    u32_err = eMMC_set_UserWP(u32_eMMCBlkAddr, USER_PERM);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Err: set_UserWP fail: %Xh \n", u32_err);
        return u32_err;
    }
    u32_err = eMMC_get_UserWPStatus(u32_eMMCBlkAddr, gau8_eMMC_SectorBuf);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Err: get_UserWPStatus fail.2: %Xh \n", u32_err);
        return u32_err;
    }

    // -----------------------------
    // write & check data again
    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "eMMC: test WP \n");
    eMMC_DISABLE_RETRY(1);
    eMMC_DISABLE_LOG(1);
    u32_err = eMMC_WriteData(gau8_eMMC_SectorBuf, USER_WP_TEST_DATA_BYTECNT, u32_eMMCBlkAddr);
    if(eMMC_ST_SUCCESS == u32_err)
    {
        eMMC_DISABLE_RETRY(0);
        eMMC_DISABLE_LOG(0);
        eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Err: WriteData OK - fail.2: %Xh \n", u32_err);
        return u32_err;
    }
    u32_err = eMMC_ReadData(gau8_eMMC_SectorBuf, USER_WP_TEST_DATA_BYTECNT, u32_eMMCBlkAddr);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_DISABLE_RETRY(0);
        eMMC_DISABLE_LOG(0);
        eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Err: ReadData fail.2: %Xh \n", u32_err);
        return u32_err;
    }

    u32_tmp = eMMC_ChkSum(gau8_eMMC_SectorBuf, USER_WP_TEST_DATA_BYTECNT);
    if(u32_ChkSum != u32_tmp)
    {
        eMMC_DISABLE_RETRY(0);
        eMMC_DISABLE_LOG(0);
        eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Err: ChkSum fail.2: %Xh %Xh\n", u32_ChkSum, u32_tmp);
        return eMMC_ST_ERR_CHKSUM;
    }

    eMMC_DISABLE_RETRY(0);
    eMMC_DISABLE_LOG(0);
    eMMC_debug(eMMC_DEBUG_LEVEL, 0, "\n test OK \n\n");
    return u32_err;
}


U32 eMMC_verify_BootPartition_WP(void)
{
    U32 u32_err;

    #if 0
    u32_err = eMMC_verify_BootWP_Config(CFG_PWR);
    if(u32_err != eMMC_ST_SUCCESS)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: BOOT_WP config test fail ! \n");
        return u32_err;
    }
    #endif

    #if 1
    u32_err = eMMC_verify_BootWP_WRC(BOTH_PWR);
    if(u32_err != eMMC_ST_SUCCESS)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: BOOT_WP test fail ! \n");
        return u32_err;
    }
    #endif

    return eMMC_ST_SUCCESS;
}


// write/read/checksum
U32 eMMC_verify_BootWP_WRC(U16 u16_Flag)
{
    U32 u32_err, u32_i, u32_ChkSum1=0, u32_ChkSum2=0, u32_temp;

    for(u32_i=0; u32_i<0x20000; u32_i++)
        gau8_WBuf[u32_i] = u32_i+1;

    eMMC_ResetReadyFlag();
    u32_err = eMMC_Init();
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: init fail: %Xh \n", u32_err);
        return u32_err;
    }

    eMMC_get_BootWPStatus();

    // --------------------------------------------------
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"write Boot Partitions... \n");
    for(u32_i=0; u32_i<g_eMMCDrv.u8_BOOT_SIZE_MULT; u32_i++)
    {
        u32_err = eMMC_WriteBootPart(gau8_WBuf, 0x20000, u32_i*0x20000/0x200, 1);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: write BootPart 1 fail: %Xh, %Xh \n", u32_err, u32_i);
            return u32_err;
        }
        
        u32_err = eMMC_WriteBootPart(gau8_WBuf, 0x20000, u32_i*0x20000/0x200, 2);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: write BootPart 2 fail: %Xh, %Xh \n", u32_err, u32_i);
            return u32_err;
        }
    }

    eMMC_debug(eMMC_DEBUG_LEVEL,0,"read Boot Partitions... \n");
    for(u32_i=0; u32_i<g_eMMCDrv.u8_BOOT_SIZE_MULT-1; u32_i++)
    {
        u32_err = eMMC_ReadBootPart(gau8_RBuf, 0x20000, u32_i*0x20000/0x200, 1);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: read BootPart 1 fail: %Xh, %Xh \n", u32_err, u32_i);
            return u32_err;
        }
        u32_ChkSum1 += eMMC_ChkSum(gau8_RBuf, 0x20000);

        u32_err = eMMC_ReadBootPart(gau8_RBuf, 0x20000, u32_i*0x20000/0x200, 2);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: read BootPart 2 fail: %Xh, %Xh \n", u32_err, u32_i);
            return u32_err;
        }
        u32_ChkSum2 += eMMC_ChkSum(gau8_RBuf, 0x20000);
    }

    // --------------------------------------------------
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"set WP \n");
    u32_err = eMMC_set_BootWP(u16_Flag);
    if(eMMC_ST_SUCCESS != u32_err)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: BOOT_WP fail: %Xh \n", u32_err);
        return u32_err;
    }
    eMMC_get_BootWPStatus();

    if(BOTH_PWR==u16_Flag || BOOT1_PWR==u16_Flag)
    {
        eMMC_ModifyExtCSD(eMMC_ExtCSD_SetBit, 173, SEC_WP_SEL|PWR_WP_SEL);
        eMMC_get_BootWPStatus();
    }
    else if(BOTH_PERM==u16_Flag || BOOT1_PERM==u16_Flag)
    {
        eMMC_ModifyExtCSD(eMMC_ExtCSD_SetBit, 173, SEC_WP_SEL|PERM_WP_SEL);
        eMMC_get_BootWPStatus();
    }
    // --------------------------------------------------
    //LABEL_CHECK_WP:
    eMMC_DISABLE_RETRY(1);
    eMMC_DISABLE_LOG(1);

    eMMC_ModifyExtCSD(eMMC_ExtCSD_ClrBit, 173, PWR_WP_EN|PERM_WP_EN);
    eMMC_ModifyExtCSD(eMMC_ExtCSD_SetBit, 173, PWR_WP_DIS|PERM_WP_DIS);

    for(u32_i=0; u32_i<g_eMMCDrv.u8_BOOT_SIZE_MULT; u32_i++)
    {
        u32_err = eMMC_WriteBootPart(gau8_WBuf, 0x20000, u32_i*0x20000/0x200, 1);
        if(eMMC_ST_SUCCESS == u32_err)
        {
            eMMC_DISABLE_RETRY(0);
            eMMC_DISABLE_LOG(0);
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: write BootPart 1 OK \n");
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: PwrOn WP BootPart 1 fail, %Xh \n", u32_i);
            return u32_err;
        }

        #if 1
        u32_err = eMMC_WriteBootPart(gau8_WBuf, 0x20000, u32_i*0x20000/0x200, 2);
        if(eMMC_ST_SUCCESS == u32_err)
        {
            eMMC_DISABLE_RETRY(0);
            eMMC_DISABLE_LOG(0);
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: write BootPart 2 OK \n");
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: PwrOn WP BootPart 2 fail, %Xh \n", u32_i);
            return u32_err;
        }
        #endif
    }
    eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);
    
    eMMC_DISABLE_RETRY(0);
    eMMC_DISABLE_LOG(0);
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"read WP Boot Partitions... \n");
    u32_temp = 0;
    for(u32_i=0; u32_i<g_eMMCDrv.u8_BOOT_SIZE_MULT-1; u32_i++)
    {
        u32_err = eMMC_ReadBootPart(gau8_RBuf, 0x20000, u32_i*0x20000/0x200, 1);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: read BootPart 1 fail: %Xh, %Xh \n", u32_err, u32_i);
            return u32_err;
        }
        u32_temp += eMMC_ChkSum(gau8_RBuf, 0x20000);
    }
    if(u32_temp != u32_ChkSum1)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: PwrOn WP BootPart 1 fail \n");
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: PwrOn WP ChkSum: %Xh %Xh \n", u32_ChkSum1, u32_temp);
    }

    u32_temp = 0;
    for(u32_i=0; u32_i<g_eMMCDrv.u8_BOOT_SIZE_MULT-1; u32_i++)
    {
        u32_err = eMMC_ReadBootPart(gau8_RBuf, 0x20000, u32_i*0x20000/0x200, 2);
        if(eMMC_ST_SUCCESS != u32_err)
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: read BootPart 2 fail: %Xh, %Xh \n", u32_err, u32_i);
            return u32_err;
        }
        u32_temp += eMMC_ChkSum(gau8_RBuf, 0x20000);
    }
    if(u32_temp != u32_ChkSum2)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: PwrOn WP BootPart 2 fail \n");
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: PwrOn WP ChkSum: %Xh %Xh \n", u32_ChkSum2, u32_temp);
    }

    eMMC_debug(eMMC_DEBUG_LEVEL,0,"\n test OK \n\n");
    return eMMC_ST_SUCCESS;    
}


U32 eMMC_verify_BootWP_Config_Ex(U8 *au8_ECSD173, U8 u8_Cnt);
// 1: Permanent  2: Power-On
U32 eMMC_verify_BootWP_Config(U8 u8_Flag)
{
    U8  au8_ECSD173[5], u8_Cnt=0;

    if(CFG_PERM == u8_Flag)
    {
        au8_ECSD173[0]=PERM_WP_EN;
        au8_ECSD173[1]=PWR_WP_SEL;
        au8_ECSD173[2]=PERM_WP_SEL;
        au8_ECSD173[3]=SEC_WP_SEL;
        
        au8_ECSD173[4]=PERM_WP_DIS;
        u8_Cnt=5;
    }
    else if(CFG_PWR == u8_Flag)
    {
        au8_ECSD173[0]=PWR_WP_EN;
        au8_ECSD173[1]=PWR_WP_SEL;
        au8_ECSD173[2]=PERM_WP_SEL;
        au8_ECSD173[3]=SEC_WP_SEL;

        au8_ECSD173[4]=PWR_WP_DIS;
        u8_Cnt=5;
    }

    return eMMC_verify_BootWP_Config_Ex(au8_ECSD173, u8_Cnt);
}


U32 eMMC_verify_BootWP_Config_Ex(U8 *au8_ECSD173, U8 u8_Cnt)
{
    U32 u32_PwrWPSt=0xFFFFFFFF;
    U8  u8_i;
    
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"original status: \n");
    eMMC_get_BootWPStatus();
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"\n\n");

    eMMC_DISABLE_RETRY(1);

    // ================================
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"verify ECSD[173] config bits... \n\n");
    
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"first set \n");
    // first set
    for(u8_i=0; u8_i<u8_Cnt-1; u8_i++)
    {
        //eMMC_FCIE_ErrHandler_ReInit(); 
        eMMC_ModifyExtCSD(eMMC_ExtCSD_SetBit, 173, au8_ECSD173[u8_i]);
	    
        if(0xFFFFFFFF==u32_PwrWPSt)
            u32_PwrWPSt = eMMC_get_BootWPStatus();
        else
            if(u32_PwrWPSt != eMMC_get_BootWPStatus())
            {
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,0,"eMMC Err: fail.1 \n");
                return eMMC_ST_ERR_WP_BOOT_PWR_CFG;
            }
    }
    if(u8_i != u8_Cnt-1)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,0,"eMMC Err: fail.2, set:%Xh \n", au8_ECSD173[u8_i]);
        eMMC_get_BootWPStatus();
        return eMMC_ST_ERR_WP_BOOT_PWR_CFG;
    }
    
    // set again
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"\n\n");
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"set again \n");
    eMMC_DISABLE_LOG(1);
    //--------------------------------------
    for(u8_i=0; u8_i<u8_Cnt-1; u8_i++)
    {
        eMMC_ModifyExtCSD(eMMC_ExtCSD_ClrBit, 173, au8_ECSD173[u8_i]);
	    
        if(u32_PwrWPSt != eMMC_get_BootWPStatus())
        {
            eMMC_DISABLE_RETRY(0);
            eMMC_DISABLE_LOG(0);
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,0,"eMMC Err: fail.3 \n");
            return eMMC_ST_ERR_WP_BOOT_PWR_CFG;
        }
    }    
    if(u8_i != u8_Cnt-1)
    {
        eMMC_DISABLE_RETRY(0);
        eMMC_DISABLE_LOG(0);
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,0,"eMMC Err: fail.4, set:%Xh \n", au8_ECSD173[u8_i]);
        eMMC_get_BootWPStatus();
        return eMMC_ST_ERR_WP_BOOT_PWR_CFG;
    }

    // set DISABLE
    eMMC_ModifyExtCSD(eMMC_ExtCSD_ClrBit, 173, au8_ECSD173[u8_i]); 
    if(u32_PwrWPSt != eMMC_get_BootWPStatus())
    {
        eMMC_DISABLE_RETRY(0);
        eMMC_DISABLE_LOG(0);
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,0,"eMMC Err: fail.5 \n");
        return eMMC_ST_ERR_WP_BOOT_PWR_CFG;
    }
    
    eMMC_DISABLE_LOG(0);
    
    //--------------------------------------
    // re-init, 2nd set
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"\n");
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"reset \n");    
    eMMC_FCIE_ErrHandler_ReInit();    
    for(u8_i=0; u8_i<u8_Cnt-1; u8_i++)
    {
        eMMC_ModifyExtCSD(eMMC_ExtCSD_SetBit, 173, au8_ECSD173[u8_i]);

        if(u32_PwrWPSt != eMMC_get_BootWPStatus())
        {
            eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,0,"eMMC Err: fail.6 \n");
            return eMMC_ST_ERR_WP_BOOT_PWR_CFG;
        }
    }
    if(u8_i != u8_Cnt-1)
    {
        eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,0,"eMMC Err: fail.7, set:%Xh \n", au8_ECSD173[u8_i]);
        eMMC_get_BootWPStatus();
        return eMMC_ST_ERR_WP_BOOT_PWR_CFG;
    }

    eMMC_debug(eMMC_DEBUG_LEVEL,0,"\n ok \n\n");

    // ================================


    // ================================
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"current status: \n");
    eMMC_DISABLE_RETRY(0);
    eMMC_get_BootWPStatus();
    return eMMC_ST_SUCCESS;
}



