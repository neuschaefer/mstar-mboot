
enum {
    MAPI_CMD_GFX_INIT           =0,
    MAPI_CMD_GFX_GET_INFO       ,
    MAPI_CMD_GFX_LINEDRAW       ,
    MAPI_CMD_GFX_RECTFILL       ,
    MAPI_CMD_GFX_BITBLT         ,
    MAPI_CMD_GFX_SET_ABL        ,
    MAPI_CMD_GFX_SET_CONFIG     ,
    MAPI_CMD_GFX_BITMAP         ,
    MAPI_CMD_GFX_FONT           ,
    MAPI_CMD_GFX_POWERSTATE     ,
    MAPI_CMD_GFX_CB             ,
    MAPI_CMD_GFX_MISC           ,
    MAPI_CMD_GFX_TWOSRCBITBLT   ,
    MAPI_CMD_GFX_TLB            ,
    MAPI_CMD_GFX_GET_CAPS       ,   
    MAPI_CMD_GFX_DRAW_OVAL      , 
} eGFXIoctlOpt;

typedef enum
{
    E_GFX_GET_BUFFERINFO        =0,
    E_GFX_GET_TAGID             ,
    E_GFX_GET_NEXTTAGID         ,
    E_GFX_GET_CLIP              ,
    E_GFX_GET_INTENSITY         ,
    E_GFX_GET_DBGINFO           ,
}EN_GFX_GET_CONFIG;

typedef enum
{
    E_GFX_SET_POWERON           =0,
    E_GFX_SET_FLUSHQUEUE        ,
    E_GFX_SET_TAGID             ,
    E_GFX_SET_NEXTTAGID         ,
    E_GFX_SET_WAITFORTAGID      ,
    E_GFX_SET_ONEPIXELMODE      ,
    E_GFX_SET_DITHER            ,   
    E_GFX_SET_VQ                ,
    E_GFX_SET_MIRROR            ,
    E_GFX_SET_DST_MIRROR        ,
    E_GFX_SET_ROTATE            ,
    E_GFX_SET_ITALIC            ,
    E_GFX_SET_NEARESTMODE       ,
    E_GFX_SET_PALETTEOPT        ,
    E_GFX_SET_CLIP              ,
    E_GFX_SET_WRITEPROTECT      ,
    E_GFX_SET_ALPHA_COMPARE     ,
    E_GFX_SET_SRCINFO           ,
    E_GFX_SET_DSTINFO           ,
    E_GFX_SET_CSC               ,
}EN_GFX_SET_CONFIG;

typedef enum
{
    E_GFX_SET_ABL               =0,
    E_GFX_SET_COLORKEY          ,
    E_GFX_SET_ROP               ,
    E_GFX_SET_DFB               ,
    E_GFX_SET_INTENSITY         ,
}EN_GFX_SET_ABL;

typedef enum
{
    E_SRC_COLORKEY              =0x1,
    E_DST_COLORKEY              =0x2,
}GFX_ColorKeyType;

typedef enum
{
    E_LOADTEXTOUT               =0x1,
    E_CHARACTEROUT              =0x2,
}GFX_TEXTTYPE;

typedef enum
{
    E_CB_GETFONT                =0x1,
    E_CB_GETBMP                 =0x2,
}EN_GFX_CB_MODE;

typedef enum
{
    E_MISC_EXIT                 =1,
    E_MISC_CLEAR_FRAME_BY_WORLD   ,
    E_MISC_CLEAR_FRAME            ,
    E_MISC_LINE_PATTERN_RESET     ,
    E_MISC_LINE_PATTERN           ,
    E_MISC_BEGINE_DRAW            ,
    E_MISC_END_DRAW               ,
    E_MISC_DEBUG_LEVEL            ,
    E_MISC_SET_HK                 ,
    E_MISC_GET_HK                 ,
    E_MISC_PATCH_MODE             ,
    E_MISC_STR_BLT_SCK_TYPE       ,
    E_MISC_SET_ALB_1555           ,
    E_MISC_GET_ALB_1555           ,
}EN_GFX_MISC_MODE;

typedef enum
{
    E_SET_PARA_0            =0x1,
    E_SET_PARA_1            =0x2,
    E_SET_PARA_2            =0x4,
    E_SET_PARA_3            =0x8,
    E_SET_PARA_4            =0x10,
}E_GFX_SET_PARA;
    
typedef struct
{
    GFX_BufferInfo*             pBufInfo;
    MS_U32                      u32OffsetByte;
}GFX_Src_BufferInfo, GFX_Dst_BufferInfo;

typedef struct _GFX_GET_BUFFERINFO
{
    GFX_Src_BufferInfo*         pSrcbufInfo;
    GFX_Dst_BufferInfo*         pDstbufInfo;
}GFX_Get_BufferInfo;

typedef struct
{
    MS_BOOL                     bEnable;
    GFX_ColorKeyMode            eOpMode;
    GFX_Buffer_Format           eFmt;
    void*                       pS_color;
    void*                       pE_color;
}GFX_Set_Src_ColorKey, GFX_Set_Dst_ColorKey;

typedef struct
{
    GFX_StretchCKType type;
    GFX_RgbColor     color;
}GFX_SetStrBltSckType;

/*================================================================================================================= 
    GFX Init
=================================================================================================================*/
typedef struct
{
    MS_U32                          u32VCmdQSize;                       /// MIN:4K, MAX:512K, <MIN:Disable
    MS_PHYADDR                      u32VCmdQAddr;                       //  8-byte aligned
    MS_BOOL                         bIsHK;                              /// Running as HK or Co-processor
    MS_BOOL                         bIsCompt;                           /// Running as compatible mode. In compatible mode, the parameter checking loose for NOS APP compatibility.  TRUE=>compatible with 51/Chakra , FALSE=>linux OS style
}GFX_Init_Config;

/*================================================================================================================= 
    GFX GetInfo
=================================================================================================================*/
typedef struct
{
    MS_U32                      u32Id;
    MS_U32*                     pColor;
}GFX_Get_Intensity;

typedef struct
{
    EN_GFX_CAPS                 eCapType;
    MS_U32*                     pRet;
    MS_U32                      Ret_Size;
}GFX_Get_CAPS;

typedef struct
{
    MS_BOOL                     bStepTagBefore;
    MS_U16*                     pTagID;
}GFX_Get_NextTagID;

/*================================================================================================================= 
    GFX SetFunction
       *Rotate
       *ColorKey
=================================================================================================================*/
typedef struct
{
    MS_BOOL                     bEnable;
    GFX_BlendCoef               eABLCoef;
    GFX_AlphaSrcFrom            eDb_abl;
    MS_U8                       u8Alpha_Const;
}GFX_Set_ABL;

typedef struct _GFX_SET_COLORKEY
{
    MS_U32                      ColorKey_Type;
    GFX_Set_Src_ColorKey*       pSrcbufInfo;
    GFX_Set_Dst_ColorKey*       pDstbufInfo;
}GFX_Set_Colorkey;

typedef struct
{
    MS_BOOL                     bEnable;
    GFX_ROP2_Op                 eRopMode;
}GFX_Set_ROP;

typedef struct
{
    MS_BOOL                     bEnable;
    GFX_DFBBldOP                eSrcBldOP;
    GFX_DFBBldOP                eDstBldOP;
    GFX_RgbColor                sRGBColor;
    MS_U16                      u16DFBBldFlags;
}GFX_Set_DFB;

typedef struct
{
    MS_U32                      u32Id;
    GFX_Buffer_Format           eFmt;
    MS_U32*                     pColor;
}GFX_Set_Intensity;



/*================================================================================================================= 
    GFX SetConfig 
        *OnePixel
        *VQ
        *Clip
=================================================================================================================*/
typedef struct
{
    MS_BOOL                     bEnable;
    MS_PHYADDR                  u32Addr;
    GFX_VcmqBufSize             enBufSize;
    MS_U8                       u8R_Threshold;
    MS_U8                       u8W_Threshold;
}GFX_Set_VQ;

typedef struct
{
    MS_BOOL                     bMirrorX;
    MS_BOOL                     bMirrorY;
}GFX_Set_Mirror;

typedef struct
{
    MS_BOOL                     bEnable;
    MS_U8                       u8Ini_line;
    MS_U8                       u8Ini_dis;
    MS_U8                       u8Delta;
}GFX_Set_Italic;

typedef struct
{
    MS_U8                       u8Miu;
    MS_U32                      u32Addr_Low;
    MS_U32                      u32Addr_High;
    GFX_WPType                  eWPType;
}GFX_Set_WriteProtect;

typedef struct
{
    MS_BOOL enable;
    GFX_ACmpOp eMode;
}GFX_Set_AlphaCompare;

typedef struct
{
    GFX_PaletteEntry*           pPalArray;
    MS_U16                      u32PalStart;
    MS_U16                      u32PalEnd;
}GFX_Set_PaletteOpt;

typedef struct
{
    GFX_YUV_Rgb2Yuv mode;
    GFX_YUV_OutRange yuv_out_range;
    GFX_YUV_InRange uv_in_range;
    GFX_YUV_422 srcfmt;
    GFX_YUV_422 dstfmt;
}GFX_Set_CSC;

typedef struct
{
   GFX_Point*                   pV0;
   GFX_Point*                   pV1;
}GFX_Set_Clip_Property, GFX_Get_Clip_Property;

typedef struct
{
    GFX_Dst_BufferInfo*         pDstbufInfo;
    GFX_RectFillInfo*           pRectFillInfo;
}GFX_Set_RectFillInfo;

typedef struct
{
    GFX_Src_BufferInfo*         pSrcbufInfo;            ///Width/Height/Pitch/Colofmt
    GFX_Dst_BufferInfo*         pDstbufInfo;
    GFX_DrawRect*               pDrawRect;              ///Position
    GFX_ScaleInfo*              pScaleInfo;             ///ScaleInfo    
    MS_U32                      u32DrawFlag;            
    void*                       pIntensity;             ///I1/I2/I4            
}GFX_BitBltInfo;

typedef struct
{
    GFX_Src_BufferInfo*         pSrcbufInfo_0;            ///Width/Height/Pitch/Colofmt
    GFX_Src_BufferInfo*         pSrcbufInfo_1;            ///Width/Height/Pitch/Colofmt
    GFX_Dst_BufferInfo*         pDstbufInfo;
    GFX_DrawTwoSourceRect*      pDrawTwoSrcRect;              ///Position
    MS_U32                      u32DrawFlag;
}GFX_TwoSrc_BitBltInfo;

typedef struct
{
    GFX_Src_BufferInfo*         pSrcbufInfo;            ///Width/Height/Pitch/Colofmt
    GFX_Dst_BufferInfo*         pDstbufInfo;
    MS_S32                      handle;
    GFX_DrawBmpInfo*            pBmpInfo;
}GFX_Bitmap;

typedef struct
{
    GFX_Src_BufferInfo*         pSrcbufInfo;            ///Width/Height/Pitch/Colofmt
    GFX_Dst_BufferInfo*         pDstbufInfo;
    MS_S32                      fHandle;
    MS_U32*                     pIndex;
    MS_U32                      u32StrWidth;
    GFX_TextOutInfo*            pTextInfo;
}GFX_TextOut;

typedef struct
{
    GFX_Src_BufferInfo*         pSrcbufInfo;            ///Width/Height/Pitch/Colofmt
    GFX_Dst_BufferInfo*         pDstbufInfo;
    GFX_CharInfo*               pChar;
    GFX_TextOutInfo*            pTextInfo;
}GFX_CharacterOut;

typedef struct
{
    MS_PHYADDR StrAddr;
    MS_U32 length;
    MS_U32 ClearValue;
}GFX_ClearFrameBuffer;

typedef struct
{
    MS_BOOL enable;
    MS_U8 linePattern;
    MS_U8 repeatFactor;
}GFX_SetLinePattern;

/*===================================================================================================================
     Input Strucure
====================================================================================================================*/
typedef enum
{
    E_GFX_INIT_VER0             =0,
}EN_GFX_INIT_VER;

typedef enum
{
    E_GFX_GET_INFO_VER0         =0,
}EN_GFX_GET_INFO_VER;

typedef enum
{
    E_GFX_GET_CAPS_VER0         =0,
}EN_GFX_GET_CAPS_VER;

typedef enum
{
    E_GFX_LINEDRAW_VER0         =0,
}EN_GFX_LINEDRAW_VER;

typedef enum
{
    E_GFX_RECTFILL_VER0         =0,
}EN_GFX_RECTFILL_VER;

typedef enum
{
    E_GFX_BITBLT_VER0           =0,
}EN_GFX_BITBLT_VER;

typedef enum
{
    E_GFX_ABL_VER0              =0,
}EN_GFX_ABL_VER;

typedef enum
{
    E_GFX_SET_CONFIG_VER0       =0,
}EN_GFX_SET_CONFIG_VER;

typedef enum
{
    E_GFX_BITMAP_VER0           =0,
}EN_GFX_BITMAP_VER;

typedef enum
{
    E_GFX_TEXT_VER0             =0,
}EN_GFX_TEXTOUT_VER;

typedef enum
{
    E_GFX_POWERSTATE_VER0       =0,
}EN_GFX_POWERSTATE_VER;

typedef enum
{
    E_GFX_CB_VER0               =0,
}EN_GFX_CB_VER;

typedef enum
{
    E_GFX_MISC_VER0             =0,
}EN_GFX_MISC_VER;

typedef enum
{
    E_GFX_TLB_VER0              =0,
}EN_GFX_TLB_VER;

typedef enum
{
    E_GFX_DRAW_OVAL_VER0              =0,
}EN_GFX_DRAW_OVAL_VER;

typedef struct
{
    EN_GFX_INIT_VER             eVerType;
    GFX_Init_Config*            pGFX_Init;  
    MS_U32                      u32Size;
}GFX_INIT_ARGS;  

typedef struct
{
    EN_GFX_GET_INFO_VER         eVerType;
    EN_GFX_GET_CONFIG           eGFX_GetConfig;
    void*                       pGFX_GetInfo;  
    MS_U32                      u32Size;
}GFX_GETINFO_ARGS;  

typedef struct
{
    EN_GFX_GET_CAPS_VER         eVerType;
    EN_GFX_CAPS                 eCaps;
    void*                       pGFX_GetCaps;  
    MS_U32                      u32Size;
}GFX_GETCAPS_ARGS;

typedef struct
{
    GFX_Dst_BufferInfo*         pDstbufInfo;
    GFX_DrawLineInfo*           pDrawLineInfo;
}GFX_Set_DrawLineInfo;


typedef struct
{
    EN_GFX_LINEDRAW_VER         eVerType;
    GFX_Set_DrawLineInfo*       pLineInfo;
    MS_U32                      u32Size;
}GFX_LINEDRAW_ARGS;

typedef struct
{    
    EN_GFX_RECTFILL_VER         eVerType;
    GFX_Set_RectFillInfo*       pFillBlock;
    MS_U32                      u32Size;
}GFX_RECTFILL_ARGS;

typedef struct
{
    EN_GFX_BITBLT_VER           eVerType;
    GFX_BitBltInfo*             pGFX_BitBlt;  
    MS_U32                      u32Size;
}GFX_BITBLT_ARGS;

typedef struct
{
    EN_GFX_BITBLT_VER           eVerType;
    GFX_TwoSrc_BitBltInfo*      pGFX_TwoSrc_BitBlt;
    MS_U32                      u32Size;
}GFX_TWOSRC_BITBLT_ARGS;

typedef struct
{
    EN_GFX_ABL_VER              eVerType;
    EN_GFX_SET_ABL              eGFX_SetABL;
    void*                       pGFX_ABL;  
    MS_U32                      u32Size;
}GFX_ABL_ARGS;

typedef struct
{
    EN_GFX_SET_CONFIG_VER       eVerType;
    EN_GFX_SET_CONFIG           eGFX_SetConfig;
    void*                       pGFX_ConfigInfo;  
    MS_U32                      u32Size;
}GFX_SETCONFIG_ARGS;

typedef struct
{
    EN_GFX_BITMAP_VER           eVerType;
    GFX_Bitmap*                 pGFX_Bitmap;  
    MS_U32                      u32Size;
}GFX_BITMAP_ARGS;

typedef struct
{
    EN_GFX_TEXTOUT_VER          eVerType;
    GFX_TEXTTYPE                eGFX_TextType;
    void*                       pGFX_TextOut;  
    MS_U32                      u32Size;
}GFX_TEXTOUT_ARGS;

typedef struct
{
    EN_GFX_POWERSTATE_VER       eVerType;
    EN_POWER_MODE               eGFX_PowerStateType;
    void*                       pGFX_PowerState;  
    MS_U32                      u32Size;
}GFX_POWERSTATE_ARGS;

typedef struct
{
    EN_GFX_CB_VER               eVerType;
    EN_GFX_CB_MODE              eGFX_CBType;
    void*                       pGFX_CBInfo;  
    MS_U32                      u32Size;
}GFX_CB_ARGS; 

typedef struct
{
    EN_GFX_MISC_VER             eVerType;
    EN_GFX_MISC_MODE            eGFX_MISCType;
    void*                       pGFX_Info;  
    MS_U32                      u32Size;
}GFX_MISC_ARGS;  

typedef enum
{
    E_GFX_TLB_SET_MODE,
}EN_GFX_TLB_CMD;

typedef struct _GFX_TLB_ARGS
{
    EN_GFX_TLB_CMD              en_cmd;
    EN_GFX_TLB_VER              eVerType;
    EN_GFX_TLB_Mode             TLB_mode;
    void*                       psetting;  
    MS_U32                      u32Size;
}GFX_TLB_ARGS, *PGFX_TLB_ARGS;

typedef struct
{
    EN_GFX_DRAW_OVAL_VER        eVerType;
    void*                       psetting;  
    MS_U32                      u32Size;
}GFX_DRAW_OVAL_ARGS;


