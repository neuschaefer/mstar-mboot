#ifndef _UTOPIA_DRIVER_ID_H_
#define _UTOPIA_DRIVER_ID_H_


extern __attribute__((weak)) MS_U32 BDMAOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 AESDMAOpen(void** pInstantTmp, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 PCMCIAOpen(void** pInstantTmp, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 GOPOpen(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 GFXOpen(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 TVENCODEROpen(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 XCOpenFull(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 XCOpenMinimum(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 MBXOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 DIPOpen(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 PNLOpen(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 VBIOpen(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 ACEOpen(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 DLCOpen(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 IROpen(void** pInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 SAROpen(void** pInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 PWSOpen(void** pInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 FLASHOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 SEALOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 CMDQOpen(void** pInstance, void* pAttribute);
extern __attribute__((weak)) MS_U32 SEMOpen(void** pInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 SYSOpen(void** pInstance, void* pAttribute);
extern __attribute__((weak)) MS_U32 VDEC_EX_V2_Open(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 MVOPOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32  DMXOpen(void** pInstance, void* pAttribute);
extern __attribute__((weak)) MS_U32 RTCOpen(void** pInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 UARTOpen(void** pInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 PWMOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 JPEGOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 GPDOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 MFEOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 CPUOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 JPEG_Open(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 MSPIOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 DSCMBOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 DACOpen(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 CH34Open(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 GOPSCDOpen(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 ACPOpen(void** ppInstance, const void* const pAttribute);
extern __attribute__((weak)) MS_U32 AVDOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);
extern __attribute__((weak)) MS_U32 MIUOpen(void** ppInstance, MS_U32 u32ModuleVersion, void* pAttribute);

#define MODULE_TYPE_UTOPIA_FULL 1
#define MODULE_TYPE_BDMA_FULL BDMAOpen
#define MODULE_TYPE_AESDMA_FULL AESDMAOpen
#define MODULE_TYPE_DSCMB_FULL DSCMBOpen
#define MODULE_TYPE_CI_FULL PCMCIAOpen
#define MODULE_TYPE_GOP_FULL GOPOpen
#define MODULE_TYPE_GFX_FULL GFXOpen
#define MODULE_TYPE_TVENCODER_FULL TVENCODEROpen
#define MODULE_TYPE_XC_FULL     XCOpenFull
#define MODULE_TYPE_XC_MINIMUM  XCOpenMinimum
#define MODULE_TYPE_MBX_FULL MBXOpen
#define MODULE_TYPE_TSP_FULL NULL
#define MODULE_TYPE_DIP_FULL DIPOpen
#define MODULE_TYPE_PNL_FULL PNLOpen
#define MODULE_TYPE_VBI_FULL VBIOpen
#define MODULE_TYPE_ACE_FULL ACEOpen
#define MODULE_TYPE_DLC_FULL DLCOpen
#define MODULE_TYPE_IR_FULL IROpen
#define MODULE_TYPE_SAR_FULL SAROpen
#define MODULE_TYPE_MIU_FULL MIUOpen
#define MODULE_TYPE_PWS_FULL PWSOpen
#define MODULE_TYPE_FLASH_FULL FLASHOpen
#define MODULE_TYPE_SEAL_FULL NULL
#define MODULE_TYPE_CMDQ_FULL NULL
#define MODULE_TYPE_MMFI_FULL NULL
#define MODULE_TYPE_SEM_FULL SEMOpen
#define MODULE_TYPE_SYS_FULL SYSOpen
#define MODULE_TYPE_VDEC_EX_FULL VDEC_EX_V2_Open
#define MODULE_TYPE_MVOP_FULL MVOPOpen
#define MODULE_TYPE_AVD_FULL AVDOpen
#define MODULE_TYPE_DMX_FULL DMXOpen
#define MODULE_TYPE_RTC_FULL RTCOpen
#define MODULE_TYPE_HWI2C_FULL NULL
#define MODULE_TYPE_VDEC_FULL NULL
#define MODULE_TYPE_UART_FULL UARTOpen
#define MODULE_TYPE_PWM_FULL PWMOpen
#define MODULE_TYPE_NJPEG_EX_FULL JPEGOpen
#define MODULE_TYPE_GPD_FULL GPDOpen
#define MODULE_TYPE_MFE_FULL MFEOpen
#define MODULE_TYPE_CPU_FULL CPUOpen
#define MODULE_TYPE_JPEG_EX_FULL JPEGOpen
#define MODULE_TYPE_JPEG_FULL NULL
#define MODULE_TYPE_MSPI_FULL MSPIOpen
#define MODULE_TYPE_DAC_FULL DACOpen
#define MODULE_TYPE_CH34_FULL CH34Open
#define MODULE_TYPE_GOPSCD_FULL GOPSCDOpen
#define MODULE_TYPE_ACP_FULL ACPOpen

// add new module here
#define _INCLUDED_MODULE \
    PREFIX(BDMA) \
    PREFIX(AESDMA) \
    PREFIX(DSCMB) \
    PREFIX(CI) \
    PREFIX(GOP) \
    PREFIX(GFX) \
    PREFIX(TVENCODER) \
    PREFIX(XC) \
    PREFIX(MBX) \
    PREFIX(TSP) \
    PREFIX(DIP) \
    PREFIX(PNL) \
    PREFIX(VBI) \
    PREFIX(ACE) \
    PREFIX(DLC) \
    PREFIX(IR) \
    PREFIX(SAR) \
    PREFIX(MIU) \
    PREFIX(PWS) \
    PREFIX(FLASH) \
    PREFIX(SEAL) \
    PREFIX(CMDQ) \
    PREFIX(MMFI) \
    PREFIX(SEM) \
    PREFIX(SYS) \
    PREFIX(VDEC_EX) \
    PREFIX(MVOP)    \
    PREFIX(AVD)    \
    PREFIX(DMX) \
    PREFIX(RTC) \
    PREFIX(HWI2C) \
    PREFIX(VDEC) \
    PREFIX(UART) \
    PREFIX(PWM) \
    PREFIX(NJPEG_EX) \
    PREFIX(GPD) \
    PREFIX(MFE) \
    PREFIX(CPU) \
    PREFIX(JPEG_EX) \
    PREFIX(JPEG) \
    PREFIX(MSPI) \
    PREFIX(DAC) \
    PREFIX(CH34) \
    PREFIX(GOPSCD) \
    PREFIX(ACP) \


#define INCLUDED_MODULE \
    PREFIX(UTOPIA) \
    _INCLUDED_MODULE

#if defined(CONFIG_UTOPIA_FRAMEWORK_KERNEL_DRIVER)
typedef enum{
#define PREFIX(MODULE) MODULE_##MODULE,
    INCLUDED_MODULE
#undef PREFIX
}eMsModule;

//************************Kernel Module Define********************************//
//Please Don't Change Code Order.
typedef enum{
#define PREFIX(MODULE)  CONFIG_API_##MODULE##_MODULE=0,
    INCLUDED_MODULE
#undef PREFIX
}eCONFIG_API_MODULE;

typedef enum{
#define PREFIX(MODULE)  CONFIG_DRV_##MODULE##_MODULE=0,
    INCLUDED_MODULE
#undef PREFIX
}eCONFIG_DRV_MODULE;

#include <autoconf.h>

#define PREFIX(MODULE) extern MS_U32 MODULE_##MODULE##_OPEN;
INCLUDED_MODULE
#undef PREFIX
//*************************************************************************//

#else

enum eMsModule {
#define PREFIX(MODULE) MODULE_##MODULE,
    INCLUDED_MODULE
#undef PREFIX
};

#endif //defined(UTOPIA_FRAMEWORK_KERNEL_DRIVER)
#endif
