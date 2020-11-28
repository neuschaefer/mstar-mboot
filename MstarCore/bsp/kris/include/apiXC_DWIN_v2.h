#include "drvXC_IOPort.h"
#include "apiXC.h"
#include "apiXC_DWIN.h"

typedef enum {
    DIP_TRIG_OFF,
    DIP_TRIG_ON,
    DIP_TRIG_ONESHOT,
    DIP_TRIG_ONESHOTFAST,
    DIP_TRIG_RESET,
}eDipTriggerMode;

typedef enum {
    DIP_INTR_DISABLE,
    DIP_INTR_ENABLE,
    DIP_INTR_GET,
    DIP_INTR_CLEAR,
    DIP_INTR_ATTACH,
    DIP_INTR_DETACH,
}eDipInterruptAct;

typedef enum {
    DIP_PRO_NONE        = 0x000000000,
    DIP_PRO_SCANMODE    = 0x000000001,
    DIP_PRO_DATAFMT     = 0x000000002,
    DIP_PRO_R2Y         = 0x000000004,
    DIP_PRO_Y2R         = 0x000000008,
    DIP_PRO_SWAPUV      = 0x000000010,
    DIP_PRO_SWAPYC      = 0x000000020,
    DIP_PRO_SWAPRGB     = 0x000000040,
    DIP_PRO_INTERLACE_W = 0x000000080,
    DIP_PRO_ALPHA       = 0x000000100,
    DIP_PRO_FRC         = 0x000000200,
    DIP_PRO_OP_CAPTURE  = 0x000000400,
    DIP_PRO_MIRROR      = 0x000000800,
    DIP_PRO_PINPON      = 0x000001000,
    DIP_PRO_ROTATION    = 0x000002000,
}eDipPropertyflag;

typedef enum {
	MDrv_CMD_DIP_INIT,
    MDrv_CMD_DIP_GET_RESOURCE,
    MDrv_CMD_DIP_RELEASE_RESOURCE,    
    MDrv_CMD_DIP_QUERY_RESOURCE,
	MDrv_CMD_DIP_SET_INPUTSOURCE,
    MDrv_CMD_DIP_SET_WINDOW,
    MDrv_CMD_DIP_SET_WINPROPERTY,
    MDrv_CMD_DIP_SET_PROPERTY,
    MDrv_CMD_DIP_GET_BUFINFO,
    MDrv_CMD_DIP_INTERRUPT,
    MDrv_CMD_DIP_TRIGGER,
    MDrv_CMD_DIP_SET_DIPR_PROPERTY,
} eDipIoctlOpt;

typedef struct
{
    MS_BOOL bFrameRateCtrl;
    MS_U16 u16In;
    MS_U16 u16Out;
} ST_XC_DIP_FRC;

typedef struct
{
    MS_BOOL bSwap;
    EN_XC_DIP_RGB_SWAP_TYPE eSwapType;
} ST_XC_DIP_SWAPRGB;

typedef struct
{
    MS_BOOL bOpCapture;
    EN_XC_DIP_OP_CAPTURE eOpCapture;
} ST_XC_DIP_OP_CAPTURE;

typedef struct
{
    MS_BOOL bHMirror;
    MS_BOOL bVMirror;
} ST_XC_DIP_MIRROR;

typedef struct
{
    MS_BOOL bPinpon;
    MS_U32 u32PinponAddr;
} ST_XC_DIP_PINPON;

typedef struct
{
    MS_BOOL bRotation;
    EN_XC_DIP_ROTATION eRoDirection;
} ST_XC_DIP_ROTATION;

typedef struct
{
    EN_XC_DIP_SCAN_MODE eScanMode;
    EN_XC_DIP_DATA_FMT eDataFmt; 
    ST_XC_DIP_OP_CAPTURE stOpCapture; 
    ST_XC_DIP_SWAPRGB stSwapRGB;
    ST_XC_DIP_MIRROR stMirror;
    ST_XC_DIP_FRC stFrameRateControl;
    ST_XC_DIP_PINPON stPinpon;
    ST_XC_DIP_ROTATION stRotation;
    MS_BOOL bSwapUV;
    MS_BOOL bSwapYC;
    MS_BOOL bR2Y;
    MS_BOOL bY2R;
    MS_BOOL bInterlaceW;
    MS_U8 u8Alpha;
}ST_XC_DIP_PROPERTY;

typedef struct _DIP_RESOURCE
{
    SCALER_DIP_WIN eWindow;
}DIP_RESOURCE;

typedef struct _DIP_INPUT_SOURCE
{
    INPUT_SOURCE_TYPE_t SrcPath;
}DIP_INPUT_SOURCE;

typedef struct _DIP_SET_WINDOW
{
    MS_U32 u32DataLen;
    XC_SETWIN_INFO WinInfo;
	SCALER_DIP_WIN eWindow;
}DIP_SET_WINDOW;

typedef struct _DIP_SET_PROPERTY
{
    eDipPropertyflag eFlag;
    ST_XC_DIP_PROPERTY Property; 
	SCALER_DIP_WIN eWindow;
}DIP_SET_PROPERTY;

typedef struct _DIP_SET_WIN_PROPERTY
{
    ST_XC_DIP_WINPROPERTY WinProperty;
	SCALER_DIP_WIN eWindow;
}DIP_SET_WIN_PROPERTY;

typedef struct _DIP_BUF_INFO
{
    BUFFER_INFO BufInfo;
	SCALER_DIP_WIN eWindow;
}DIP_BUF_INFO;

typedef struct _DIP_INTER_STUS
{
    eDipInterruptAct eFlag;
    MS_U16 IntrStautus;
    InterruptCb pIntCb;
	SCALER_DIP_WIN eWindow;
}DIP_INTER_STUS;

typedef struct _DIP_TRIGGER_MODE
{
    eDipTriggerMode eTrigMode;
	SCALER_DIP_WIN eWindow;
}DIP_TRIGGER_MODE;

typedef struct _DIP_SET_DIPR_PROPERTY
{
    ST_XC_DIPR_PROPERTY DIPRProperty;
	SCALER_DIP_WIN eWindow;
}DIP_SET_DIPR_PROPERTY;

