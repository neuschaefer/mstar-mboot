#ifndef M_supply_cpp
#define M_supply_cpp
#include "M_supply.h"
#include "hdmitx/sde2/inc/tmNxCompId.h"
#include "hdmitx/sde2/comps/tmdlhdmitx/inc/tmdlHdmiTx_Types.h"
#include "hdmitx/sde2/comps/tmbsltda9989/src/tmbslTDA9989_local.h"
#include <apiSWI2C.h>
#include "../../../sboot/inc/amber3/board/BD_MST029B_BOX_A3.h"
#if 1
#ifdef  HDMI_TRACE
#undef   HDMI_TRACE
#define  HDMI_TRACE(fmt,args...)  {}
#endif
#endif
#define BUSLAVE(slaveaddr)  (((UInt16) 0 << 8) | slaveaddr)


tmErrorCode_t i2cWrite(int reg , tmbslHdmiTxSysArgs_t *pSysArgs)
{

    HDMI_TRACE("--");
    /* Variable declarations */
    tmErrorCode_t err = TM_FAIL;
    UInt8 addr[1];
    UInt16 salvebus = BUSLAVE(pSysArgs->slaveAddr);
    addr[0] = pSysArgs->firstRegister;
    if(MApi_SWI2C_WriteBytes(salvebus,sizeof(UInt8),addr, pSysArgs->lenData, pSysArgs->pData) ==FALSE)
    {
        HDMI_TRACE("addr[0] = %x val = %x ",pSysArgs->slaveAddr,pSysArgs->pData[0]);
        HDMI_TRACE("IIC write fail");
    }
    else
    {
        HDMI_TRACE("IIC write succ");
        err = TM_OK;
    }
    HDMI_TRACE("++");
    return err;
}

tmErrorCode_t i2cRead(int reg , tmbslHdmiTxSysArgs_t *pSysArgs)
{
    HDMI_TRACE("--");
    /* Variable declarations */
    tmErrorCode_t err = TM_FAIL;
    UInt16 salvebus = BUSLAVE(pSysArgs->slaveAddr);
    UInt8 addr[1];
    addr[0] = pSysArgs->firstRegister;
    if(MApi_SWI2C_ReadBytes(salvebus,sizeof(UInt8),addr, pSysArgs->lenData, pSysArgs->pData) == FALSE)
    {
        HDMI_TRACE("addr[0] = %x val = %x ",pSysArgs->slaveAddr,pSysArgs->pData[0]);
        HDMI_TRACE("IIC read  fail");
    }
    else
    {
        HDMI_TRACE("IIC read succ");
        err = TM_OK;
    }
    HDMI_TRACE("++");
    return err;
}
MS_BOOL M_HDMI_GetRestoreResolution(tmdlHdmiTxVideoInConfig_t* in,tmdlHdmiTxVideoOutConfig_t* out)
{
    tmdlHdmiTxVidFmt_t res;
    extern char *getenv(char *name);
    extern	long simple_strtol(const char *cp,char **endp,unsigned int base);
    int resolution_index = 5;
    char * p_str = getenv("resolution");
    if(p_str != NULL)
    {
        resolution_index = (int)simple_strtol(p_str, NULL, 10);
    }
    else
    {
        printf("##HDMI##    RestoreResolution = NULL\n");
    }
    printf("##HDMI##    RestoreResolution = %d\n",resolution_index);
    switch(resolution_index)
    {
    case 0:
        res = TMDL_HDMITX_VFMT_02_720x480p_60Hz;
        break;
    case 1:
        res = TMDL_HDMITX_VFMT_17_720x576p_50Hz;
        break;
    case 2:
        res = TMDL_HDMITX_VFMT_19_1280x720p_50Hz;
        break;
    case 3:
        res = TMDL_HDMITX_VFMT_04_1280x720p_60Hz;
        break;
    case 4:
        res = TMDL_HDMITX_VFMT_31_1920x1080p_50Hz;
        break;
    case 5:
        res = TMDL_HDMITX_VFMT_16_1920x1080p_60Hz;
        break;
    case 6:
        res = TMDL_HDMITX_VFMT_06_720x480i_60Hz;
        break;
    case 7:
        res = TMDL_HDMITX_VFMT_21_720x576i_50Hz;
        break;
    case 8:
        res = TMDL_HDMITX_VFMT_05_1920x1080i_60Hz;
        break;
    case 9:
        res = TMDL_HDMITX_VFMT_20_1920x1080i_50Hz;
        break;
    default:
    {
        HDMI_TRACE("default res to TMDL_HDMITX_VFMT_16_1920x1080p_60Hz");
        res = TMDL_HDMITX_VFMT_16_1920x1080p_60Hz;
        break;
    }
    }
    in->format = out->format  =res;
    return TRUE;
}

int hdmi_test(void)
{
    int ret = -1;
    int i;
    tmbslHdmiTxSysArgs_t SysArgs;
    UInt8 pdata[5]= {0x87,0x00,0x06,0x80,0x00};
    UInt8 reg[5]= {0xff,0xff,0xa0,0xe4,0xf0};
    UInt8 slave[5] = {0x68,0xe0,0xe0,0xe0,0xe0};
    SysArgs.lenData=1;
    
        for(i=0; i<5; i++)
        {
            SysArgs.firstRegister=reg[i];
            SysArgs.pData = pdata+i;
            SysArgs.slaveAddr = slave[i];
            if(i2cWrite(0,&SysArgs)!=TM_OK)
                HDMI_TRACE("TEST REG[%d] FAIL",i);
        }
    
    HDMI_TRACE("HDMI TEST SUCC");

    return ret;
}

#endif
