#include "drvVBI.h"
#include "drvDMX_TTX.h"

enum
{
    VBI_POOL_ID_VBI0 = 0,
    VBI_POOL_ID_VBI1 = 1,
} eVBIPoolID;

enum {
    MDrv_CMD_VBI_ObtainEng,  // 0
    MDrv_CMD_VBI_ReleaseEng,
    MDrv_CMD_VBI_QueryCap,
    MDrv_CMD_VBI_GetLibVer,
    MDrv_CMD_VBI_GetInfo,
    MDrv_CMD_VBI_GetStatus,
    MDrv_CMD_VBI_SetDbgLevel,
    MDrv_CMD_VBI_Init,
    MDrv_CMD_VBI_RegisterCB,
    MDrv_CMD_VBI_RingBuffer_Reset,
    MDrv_CMD_VBI_InitializeTTXSlicer, // 10
    MDrv_CMD_VBI_EnableTTXSlicer,
    MDrv_CMD_VBI_IsVPS_Ready,
    MDrv_CMD_VBI_IsTTX_Ready,
    MDrv_CMD_VBI_IsWSS_Ready,
    MDrv_CMD_VBI_GetWSS_Data,
    MDrv_CMD_VBI_GetVPS_Data,
    MDrv_CMD_VBI_SetVideoStandard,
    MDrv_CMD_VBI_TTX_PacketBufferIsEmpty,
    MDrv_CMD_VBI_TTX_CheckCircuitReady,
    MDrv_CMD_VBI_TTX_GetPacketCount,  // 20
    MDrv_CMD_VBI_TTX_GetPackets,
    MDrv_CMD_VBI_TTX_GetPacket,
    MDrv_CMD_VBI_TTX_PacketBufferIsOverflow,
    MDrv_CMD_VBI_TTX_PacketBufferGetNoOfOverflows,
    MDrv_CMD_VBI_TTX_EnableLine,
    MDrv_CMD_VBI_SyncMemory,
    MDrv_CMD_VBI_CC_InitSlicer,
    MDrv_CMD_VBI_CC_InitYPbYr,
    MDrv_CMD_VBI_CC_SetDataRate,
    MDrv_CMD_VBI_CC_GetInfo,  // 30
    MDrv_CMD_VBI_CC_SetFrameCnt,
    MDrv_CMD_VBI_CC_EnableSlicer,
    MDrv_CMD_VBI_CC_EnableLine,
    MDrv_CMD_VBI_WSS_SetVpsByteNum,
    
    MDrv_CMD_DMX_TTX_RingBuffer_Reset,  // 35
    MDrv_CMD_DMX_TTX_Init,
    MDrv_CMD_DMX_TTX_SetFilterID,
    MDrv_CMD_DMX_TTX_SetCB,
    MDrv_CMD_DMX_TTX_PacketBufferIsEmpty,
    MDrv_CMD_DMX_TTX_GetPackets,
    MDrv_CMD_DMX_TTX_GetPacket,
    MDrv_CMD_DMX_TTX_PacketBufferIsOverflow,
    MDrv_CMD_DMX_TTX_PacketBufferGetNoOfOverflows,

    MDrv_CMD_VBI_Exit,
    MDrv_CMD_DMX_TTX_Exit,
    
} eVBIIoctlOpt;

typedef struct _VBI_BOOL
{
    MS_BOOL bCheck;
} VBI_BOOL, *PVBI_BOOL;

typedef struct _VBI_GET_DATA
{
    MS_U16 data;
} VBI_GET_DATA, *PVBI_GET_DATA;

//-------------------------------------------------------------

typedef struct _VBI_GETLIBVER
{
    const MSIF_Version **ppVersion;
} VBI_GETLIBVER_PARAM, *PVBI_GETLIBVER;

typedef struct _VBI_GETINFO
{
    MS_U8 u8NoInfo;
} VBI_GETINFO_PARAM, *PVBI_GETINFO_PARAM;

typedef struct _GETSTATUS
{
    VBI_DrvStatus *pDrvStatus;
} VBI_GETSTATUS_PARAM, *PVBI_GETSTATUS;

typedef struct _VBI_SETDBGLEVEL
{
    MS_U16 u16DbgSwitch;
} VBI_SETDBGLEVEL_PARAM, *PVBI_SETDBGLEVEL;

typedef struct _VBI_CMD
{
    EN_VBI_CMD cmd;
} VBI_CMD, *PVBI_CMD;

typedef struct _VBI_INIT_TYPE
{
    EN_VBI_CMD cmd;
    VBI_INIT_TYPE type;
} VBI_INIT_TYPE_PARAM, *PVBI_INIT_TYPE;

typedef struct _DMX_TTX_CMD
{
    EN_VBI_CMD cmd;
} DMX_TTX_CMD, *PDMX_TTX_CMD;

typedef struct _VBI_REGISTER_CB
{
    VBI_CB_FN pFN;
    MS_PHYADDR bufferAddr;
    MS_U32 length;
} VBI_REGISTER_CB, *PVBI_REGISTER_CB;

typedef struct _VBI_INITIALIZER_TTX_SLICER
{
    EN_VBI_CMD cmd;
    MS_PHYADDR bufferAddr;
    MS_U16 packetCount;
} VBI_INITIALIZER_TTX_SLICER, *PVBI_INITIALIZER_TTX_SLICER;

typedef struct _VBI_ENABLE_TTX_SLICER
{
    MS_BOOL bEnable;
} VBI_ENABLE_TTX_SLICER, *PVBI_ENABLE_TTX_SLICER, VBI_CC_ENABLE_SLICER, *PVBI_CC_ENABLE_SLICER;

typedef struct _VBI_GET_VPS_DATA
{
    MS_U8 *lowerWord;
    MS_U8 *higherWord;
} VBI_GET_VPS_DATA, *PVBI_GET_VPS_DATA;

typedef struct _VBI_SET_VIDEO_STANDARD
{
    VBI_VIDEO_STANDARD eStandard;
} VBI_SET_VIDEO_STANDARD, *PVBI_SET_VIDEO_STANDARD;


typedef struct _VBI_TTX_GET_PACKETS
{
    MS_PHYADDR dataAddr;
    MS_U32 *length;
} VBI_TTX_GET_PACKETS, *PVBI_TTX_GET_PACKETS;

typedef struct _VBI_TTX_GET_PACKET
{
    MS_PHYADDR *packetAddress;
} VBI_TTX_GET_PACKET, *PVBI_TTX_GET_PACKET;

typedef struct _VBI_TTX_ENABLE_LINE
{
    MS_U16 StartLine;
    MS_U16 EndLine;
} VBI_TTX_ENABLE_LINE, *PVBI_TTX_ENABLE_LINE;

typedef struct _VBI_SYNC_MEMORY
{
    MS_U32 u32Start;
    MS_U32 u32Size;
} VBI_SYNC_MEMORY, *PVBI_SYNC_MEMORY;

typedef struct _VBI_CC_INIT_SLICER
{
    MS_U32 u32RiuAddr;
    MS_PHYADDR bufferAddr;
    MS_U16 packetCount;
} VBI_CC_INIT_SLICER, *PVBI_CC_INIT_SLICER;

typedef struct _VBI_CC_INIT_YPBYR
{
    MS_U8 cvbs_no;
} VBI_CC_INIT_YPBYR, *PVBI_CC_INIT_YPBYR;

typedef struct _VBI_CC_SETDATARATE
{
    MS_U8 *ptable;
} VBI_CC_SETDATARATE, *PVBI_CC_SETDATARATE;

typedef struct _VBI_CC_GETINFO
{
    MS_U32 selector;
    MS_U32 info;
} VBI_CC_GETINFO, *PVBI_CC_GETINFO;

typedef struct _VBI_CC_SET_FRAMECNT
{
    MS_U8 cnt;
} VBI_CC_SET_FRAMECNT, *PVBI_CC_SET_FRAMECNT, VBI_VBI_WSS_VPSBYTENUM, *PVBI_VBI_WSS_VPSBYTENUM;

typedef struct _VBI_CC_ENABLE_LINE
{
    MS_U16 StartLine;
    MS_U16 EndLine;
    MS_U8 mode;
} VBI_CC_ENABLE_LINE, *PVBI_CC_ENABLE_LINE;

typedef struct _DMX_TTX_SET_FILTERID
{
    MS_U8 fid;
} DMX_TTX_SET_FILTERID, *PDMX_TTX_SET_FILTERID;

typedef struct _DMX_TTX_SET_CB
{
    DMX_CB_FN fn;
} DMX_TTX_SET_CB, *PDMX_TTX_SET_CB;

