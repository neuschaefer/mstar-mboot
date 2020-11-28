/**
 *
 * \file          tmdlHdmiTx_ExampleApplicationArm7.c
 *
 * \version       $Revision: 1 $
 *
 * \date          $Date: 19-May-2008$
 *
 * \Description   This source file provides an example of HDMI TX driver usage.
 *                Basically it demonstrates the required APIs calls in order to
 *                output an incoming 720x480@60Hz YUV422sp video.
 *                The choice of the video output format is based on display capabilities
 *                (read from EDID) and from HDMI TX IC possibilities (scaler or not).
 *                In this example application the "polling mode" is used.
 *
 *
 * \References    For further informations please refer to the
                  "Getting Started HDMI TX driver guide".
 *
*/


/*============================================================================*/
/*                   INCLUDE FILES                                            */
/*============================================================================*/

/* Infrastructure dependent header files */
#include <stdio.h>
//#include "I2C.h"
//#include <LPC21xx.H>

//#include "RTL.h"

/* Headers below shall be included in your application */
#include "hdmitx/sde2/inc/tmNxTypes.h"
#include "hdmitx/sde2/inc/tmNxCompId.h"
#include "hdmitx/sde2/comps/tmdlhdmitx/inc/tmdlHdmiTx.h"
#include "hdmitx/sde2/comps/tmdlhdmitx/cfg/tmdlHdmiTx_IW.h"
#include "hdmitx/sde2/inc/M_supply.h"

/*============================================================================*/
/*                    FUNCTIONS PROTOTYPES                                    */
/*============================================================================*/

/* This function is used to process events raised by the HDMI TX driver */
static void eventCallbackTx (tmdlHdmiTxEvent_t  event);



/* This function run the HDMI TX initialization sequence in order to be able to output a picture */
static void HdmiTx_Init(void);

/* This function retrieves the sink display capabilities */
static void sfGetVideoCapabilities(void);

/* According to sink display capabilities and HDMI TX IC capabilities
   this function choose to output a given video format */
static void sfChooseVideoOutput(void);


/* Functions declaration below are NOT part of the example, they are linked to our infrastructure */
//static void Infra_Init(void);
//static void Serial_Init(void);

/* Initialisation of the HDMI TX driver */
static void  HdmiTx_Init(void);



/*============================================================================*/
/*                   GLOBAL VARIABLES                                         */
/*============================================================================*/

/* Instance of the HDMI TX device library */
tmInstance_t gDlHdmiTxInstance;


/* Setup of the HDMI TX device library */
tmdlHdmiTxInstanceSetupInfo_t gDlHdmiTxSetupInfo;



/* Used to retrieve EDID data at application level if necessary */
/* EDID data are get automatically by the driver. However if some data,
   are needed at application level they can be retrieved by copying them
   in a buffer allocated by the application. */
#define EDID_BLOCK_COUNT    4
#define EDID_BLOCK_SIZE     128

static UInt32  gEdidBufferSize = EDID_BLOCK_COUNT * EDID_BLOCK_SIZE;
static UInt8   gEdidBuffer[EDID_BLOCK_COUNT * EDID_BLOCK_SIZE];

/* HDMI TX IC capabilities */
tmdlHdmiTxCapabilities_t gCapabilities;

/* HDMI TX video output configuration */
static tmdlHdmiTxVideoOutConfig_t gVideoOutConfig;

/* HDMI TX video input configuration */
static tmdlHdmiTxVideoInConfig_t  gVideoInConfig;

/* Display sink type */
static tmdlHdmiTxSinkType_t gSinkType;

/* HDMI X audio input configuration */
tmdlHdmiTxAudioInConfig_t  gAudioInConfig;

/* Boolean in order to enable or not HDCP handling  */
Bool                       gHDCPMode;

Bool                        b_edid_recived=FALSE;

/* Variables below are used to retrieve sink video capabilities */
#define EXAMPLE_MAX_SVD             30
static UInt                     gWrittenVideoFormats  = 0;
static tmdlHdmiTxShortVidDesc_t gVideoDesc[EXAMPLE_MAX_SVD];


/* Possibles video output when video input is 720x480p @60Hz and IC is TDA9984*/
static Bool gVideoPossibleCombinationsTDA9984[32]= {False,False,True,True,True,True,False,False,False,False,False,False,False,False,False,False,True,
        False,False,False,False,False,False,False,False,False,False,False,False,False,False,False
                                                   };




/* Possibles video output when video input is 720x480p @60Hz and IC is TDA9989*/
static Bool gVideoPossibleCombinationsTDA9989[32]= {False,False,True,True,False,False,False,False,False,False,False,False,False,False,False,False,False,
        False,False,False,False,False,False,False,False,False,False,False,False,False,False,False
                                                   };


/* Possibles video output when video input is 720x480p @60Hz and IC is TDA9983*/
static Bool gVideoPossibleCombinationsTDA9983[32]= {False,False,True,True,True,True,False,False,False,False,False,False,False,False,False,False,False,
        False,False,False,False,False,False,False,False,False,False,False,False,False,False,False
                                                   };
char* hdmitx_env[] = {"hdmitx_active"};
extern 	void setenv (char *varname, char *varvalue);
extern 	int saveenv(void);
void _hdmitx_env_set(char * env,char * value)
{
	    setenv(env,value);
        saveenv();
}

static tmdlHdmiTxVidFmt_t NativeVFmt = TMDL_HDMITX_VFMT_NULL;
/*============================================================================*/
/*  MAIN                                                                      */
/*============================================================================*/
int msHdmitx_Init(void)
{
#if dbg_switch
    hdmi_test();
    return 0;
#endif

    /* Globlal variables initializatiion */

    gVideoOutConfig.mode = TMDL_HDMITX_VOUTMODE_RGB444;          /* We choose to output RGB */
    gVideoInConfig.mode = TMDL_HDMITX_VINMODE_YUV444;            /* YUV422sp is our video input */

    gVideoOutConfig.colorDepth = TMDL_HDMITX_COLORDEPTH_24;       /* We only support this depth currently */
    gVideoOutConfig.dviVqr = TMDL_HDMITX_VQR_DEFAULT;             /* Use HDMI rules for DVI output */

    /* The driver will determine by itself the type of the sinkType by reading the EDID content */
    gSinkType      = TMDL_HDMITX_SINK_HDMI;

    //gVideoOutConfig.format    = TMDL_HDMITX_VFMT_02_720x480p_60Hz; /* let's put this for the moment */
    //gVideoInConfig.format     = TMDL_HDMITX_VFMT_02_720x480p_60Hz; /* video format coming in */
    M_HDMI_GetRestoreResolution(&gVideoInConfig,&gVideoOutConfig);

    gVideoInConfig.pixelRate  = TMDL_HDMITX_PIXRATE_SINGLE;        /* pixel rate */
    gVideoInConfig.syncSource = TMDL_HDMITX_SYNCSRC_EXT_VS;        /* we use HS,VS as synchronisation source */

    gAudioInConfig.format            = TMDL_HDMITX_AFMT_I2S;         /* audio I2S is coming in */
    gAudioInConfig.rate              = TMDL_HDMITX_AFS_48K;          /* audio sampling rate */
    gAudioInConfig.i2sFormat         = TMDL_HDMITX_I2SFOR_PHILIPS_L; /* I2S format of the audio input */
    gAudioInConfig.i2sQualifier      = TMDL_HDMITX_I2SQ_32BITS;      /* we use a 32 bits bus */
    gAudioInConfig.dstRate           = TMDL_HDMITX_DSTRATE_SINGLE;   /* not relevant here */
    gAudioInConfig.channelAllocation = 0;                            /* audio channel allocation (Ref to CEA-861D p85) */
	gAudioInConfig.channelStatus.PcmIdentification = TMDL_HDMITX_AUDIO_DATA_PCM;
	gAudioInConfig.channelStatus.CopyrightInfo =	 TMDL_HDMITX_CSCOPYRIGHT_PROTECTED;
	gAudioInConfig.channelStatus.FormatInfo =		 TMDL_HDMITX_CSFI_PCM_2CHAN_NO_PRE;
	gAudioInConfig.channelStatus.categoryCode =	 0x00;
	gAudioInConfig.channelStatus.clockAccuracy =	 TMDL_HDMITX_CSCLK_LEVEL_II;
	gAudioInConfig.channelStatus.maxWordLength =	 TMDL_HDMITX_CSMAX_LENGTH_20;
	gAudioInConfig.channelStatus.wordLength =		 TMDL_HDMITX_CSWORD_DEFAULT;
	gAudioInConfig.channelStatus.origSampleFreq =	 TMDL_HDMITX_CSOFREQ_NOT_INDICATED;

    gHDCPMode = False;                                           /* To enable/disable the HDCP */

    gDlHdmiTxSetupInfo.edidBufferSize = gEdidBufferSize; /* Size of the application EDID buffer      */
    gDlHdmiTxSetupInfo.pEdidBuffer    = gEdidBuffer;     /* Buffer to store the application EDID data */

    gDlHdmiTxSetupInfo.repeaterEnable = False;           /* To Enable/disable repeater feature, nor relevant here */
    gDlHdmiTxSetupInfo.simplayHd      = False;           /* To enable/disable simplayHD feature: blue screen when not authenticated */


    /* Initialization of the infrastructure */
    // Infra_Init();
    //Serial_Init();
    // Init_i2c();

    /* HDMI TX initialization */
	_hdmitx_env_set(hdmitx_env[0],"0");
    HdmiTx_Init();

    /* HDMI TX polling */
    msHdmitx_Poll();

    return TM_OK;

} /* main */


/*============================================================================*/
/*  HDMITX_INIT                                                               */
/*============================================================================*/
static void  HdmiTx_Init(void)
{
    tmErrorCode_t ErrCode = TM_OK;


    /*Initialize HDMI Transmiter*/
    ErrCode = tmdlHdmiTxOpen(&gDlHdmiTxInstance);

    if (ErrCode == TM_OK)
    {
        /* Register the HDMI TX events callbacks */
        ErrCode = tmdlHdmiTxRegisterCallbacks(gDlHdmiTxInstance,(ptmdlHdmiTxCallback_t)eventCallbackTx );
    }


    /* EnableEvent, all by default */
    if (ErrCode == TM_OK)
    {
        ErrCode = tmdlHdmiTxEnableEvent(gDlHdmiTxInstance, TMDL_HDMITX_HDCP_ACTIVE);
    }
    if (ErrCode == TM_OK)
    {
        ErrCode = tmdlHdmiTxEnableEvent(gDlHdmiTxInstance, TMDL_HDMITX_HDCP_INACTIVE);
    }
    if (ErrCode == TM_OK)
    {
        ErrCode = tmdlHdmiTxEnableEvent(gDlHdmiTxInstance, TMDL_HDMITX_HPD_ACTIVE);
    }
    if (ErrCode == TM_OK)
    {
        ErrCode = tmdlHdmiTxEnableEvent(gDlHdmiTxInstance, TMDL_HDMITX_HPD_INACTIVE);
    }
    if (ErrCode == TM_OK)
    {
        ErrCode = tmdlHdmiTxEnableEvent(gDlHdmiTxInstance, TMDL_HDMITX_RX_KEYS_RECEIVED);
    }
    if (ErrCode == TM_OK)
    {
        ErrCode = tmdlHdmiTxEnableEvent(gDlHdmiTxInstance, TMDL_HDMITX_RX_DEVICE_ACTIVE);
    }
    if (ErrCode == TM_OK)
    {
        ErrCode = tmdlHdmiTxEnableEvent(gDlHdmiTxInstance, TMDL_HDMITX_RX_DEVICE_INACTIVE);
    }
    if (ErrCode == TM_OK)
    {
        ErrCode = tmdlHdmiTxEnableEvent(gDlHdmiTxInstance, TMDL_HDMITX_EDID_RECEIVED);
    }


    if (ErrCode == TM_OK)
    {
        /* Provides HDMI TX instance configuration */
        ErrCode = tmdlHdmiTxInstanceSetup(gDlHdmiTxInstance, &gDlHdmiTxSetupInfo);
    }


    if (ErrCode == TM_OK)
    {
        /* Power ON the HDMI TX instance */
        ErrCode = tmdlHdmiTxSetPowerState(gDlHdmiTxInstance, tmPowerOn);
    }

    if (ErrCode == TM_OK)
    {
        /* Get IC version */
        ErrCode = tmdlHdmiTxGetCapabilities(&gCapabilities);
    }

}  /* HdmiTx_Init */


/*============================================================================*/
/*  POLLING FUNCTION                                                          */
/*============================================================================*/
void  msHdmitx_Poll(void)
{
    tmErrorCode_t   ErrCode;
    int i=0;	
    while(!b_edid_recived&&i<20)
    {
        /* Polling mode is used */
        ErrCode = tmdlHdmiTxHandleInterrupt(gDlHdmiTxInstance);
	i++;	
        if (ErrCode != TM_OK)
        {
            HDMI_TRACE("tmdlHdmiTxHandleInterrupt fail");
            break;
            /* add code to manage error code */
        }
    }

}



/*============================================================================*/
/*  TX EVENTS HANDLER                                                         */
/*============================================================================*/
static void eventCallbackTx (tmdlHdmiTxEvent_t  event)
{
    UInt8				   edidBlkCnt = 0;
    tmErrorCode_t		   ErrCode	  = TM_OK;
    tmdlHdmiTxHdcpCheck_t  hdcpStatus;
    tmdlHdmiTxEdidStatus_t edidStatus;


    switch (event)
    {

        /**< HDCP encryption status switched to active */
    case TMDL_HDMITX_HDCP_ACTIVE :
        HDMI_TRACE("Event callback Tx : HDCP ACTIVE\n");
        break;

        /**< HDCP encryption status switched to inactive */
    case TMDL_HDMITX_HDCP_INACTIVE :
        HDMI_TRACE("Event callback Tx : HDCP INACTIVE\n");
        break;

        /**< Hotplug status switched to active */
    case TMDL_HDMITX_HPD_ACTIVE :		
        HDMI_TRACE("Event callback Tx : Hot-plug status stwitched to ACTIVE\n");
        break;

        /**< Hotplug status switched to inactive */
    case TMDL_HDMITX_HPD_INACTIVE :
		
		_hdmitx_env_set(hdmitx_env[0],"0");
	    b_edid_recived =FALSE;				
        HDMI_TRACE("Event callback : Hot-plug status stwitched to INACTIVE\n");
        break;

        /**< Receiver(s) key(s) received */
    case TMDL_HDMITX_RX_KEYS_RECEIVED :
        HDMI_TRACE("Event callback Tx : RX KEYS RECEIVED\n");
        break;

        /**< Rx device is connected and active */
    case TMDL_HDMITX_RX_DEVICE_ACTIVE :
        HDMI_TRACE("Event callback Tx : RX DEVICE ACTIVE\n");

        ErrCode = tmdlHdmiTxGetHdcpState(gDlHdmiTxInstance, &hdcpStatus);
        if (ErrCode == TM_OK)
        {
            /* add code to manage error code */
        }

        ErrCode = tmdlHdmiTxGetEdidStatus(gDlHdmiTxInstance, &edidStatus, &edidBlkCnt);
        if (ErrCode == TM_OK)
        {
            /* add code to manage error code */
        }

        if((gHDCPMode)
                && (hdcpStatus == TMDL_HDMITX_HDCP_CHECK_NOT_STARTED)
                && (edidStatus == TMDL_HDMITX_EDID_READ)
          )
        {


            ErrCode = tmdlHdmiTxSetInputOutput (gDlHdmiTxInstance,
                                                gVideoInConfig,
                                                gVideoOutConfig,
                                                gAudioInConfig,
                                                gSinkType);


            /* Enable HDCP */
            ErrCode = tmdlHdmiTxSetHdcp(gDlHdmiTxInstance,True);
            if (ErrCode == TM_OK)
            {
                /* add code to manage error code */
            }
        }


        break;

        /**< Rx device is connected but inactive (standby) */
    case TMDL_HDMITX_RX_DEVICE_INACTIVE :
        HDMI_TRACE("Event callback Tx : RX DEVICE INACTIVE\n");
        break;

        /**< EDID has been received */
    case TMDL_HDMITX_EDID_RECEIVED :
        HDMI_TRACE("Event callback Tx : EDID RECEIVED");
        /* Retrieve EDID status, some errors may have occured */
        ErrCode = tmdlHdmiTxGetEdidStatus(gDlHdmiTxInstance, &edidStatus, &edidBlkCnt);
        if (ErrCode == TM_OK)
        {
            /* add code to manage error code */
        }
        switch (edidStatus)
        {
        case TMDL_HDMITX_EDID_READ:
            /* All blocks read */
            HDMI_TRACE(" (All blocks are read, nb of block : %d)\n", edidBlkCnt);
            /* Retrieve sink video capabilities */
            sfGetVideoCapabilities();
            /* Choose video output */
            sfChooseVideoOutput();
            ErrCode = tmdlHdmiTxSetInputOutput(gDlHdmiTxInstance,gVideoInConfig,gVideoOutConfig,
                                               gAudioInConfig,gSinkType);
            if (ErrCode == TM_OK)
            {
                /* add code to manage error code */
            }
            if(gHDCPMode)
            {
                ErrCode = tmdlHdmiTxSetHdcp(gDlHdmiTxInstance,True);
                if (ErrCode == TM_OK)
                {
                    /* add code to manage error code */
                }
            }
            b_edid_recived =TRUE;
			_hdmitx_env_set(hdmitx_env[0],"1");
            break;
        case TMDL_HDMITX_EDID_ERROR_CHK_BLOCK_0:
            HDMI_TRACE(" (Checksum error in block 0, nb of block : %d)\n", edidBlkCnt);
            HDMI_TRACE("force set output timming 720p(audio disabled)")
            gVideoOutConfig.mode = TMDL_HDMITX_VOUTMODE_RGB444;
            gSinkType			 = TMDL_HDMITX_SINK_DVI;
            ErrCode = tmdlHdmiTxSetInputOutput(gDlHdmiTxInstance,gVideoInConfig,gVideoOutConfig,
                                               gAudioInConfig,gSinkType);
            if (ErrCode != TM_OK)
            {

                HDMI_TRACE("tmdlHdmiTxSetInputOutput: ErrCode==%ld",ErrCode);

            }
            /* Checksum error in block 0 */
            break;
        case TMDL_HDMITX_EDID_ERROR_CHK:
            HDMI_TRACE(" (Checksum error in block other than block 0, nb of block : %d)\n", edidBlkCnt);
            HDMI_TRACE("force set output timming 720p(audio disabled)")
            gVideoOutConfig.mode = TMDL_HDMITX_VOUTMODE_RGB444;
            gSinkType			 = TMDL_HDMITX_SINK_DVI;
            ErrCode = tmdlHdmiTxSetInputOutput(gDlHdmiTxInstance,gVideoInConfig,gVideoOutConfig,
                                               gAudioInConfig,gSinkType);
            if (ErrCode != TM_OK)
            {
                HDMI_TRACE("tmdlHdmiTxSetInputOutput: ErrCode==%ld",ErrCode);

            }
            /* Checksum error in block other than block 0 */
            break;
        default:
            /* Invalid edid status for this state*/
            HDMI_TRACE(" (Invalid edid status for this state, nb of block : %d)\n", edidBlkCnt);
            break;
        }
        break;

    default:
        /* erroneous event Tx for standard event callback */
        break;
    }
}






/* -------------------------------------------*/
/* sfGetVideoCapabilities                     */
/* This function retrieves video capabilities */
/* of the sink.                               */
/* -------------------------------------------*/
static void sfGetVideoCapabilities(void)
{
    tmErrorCode_t ErrCode;
    UInt8         VideoFlags;
    UInt16        i;


    ErrCode = tmdlHdmiTxGetEdidVideoCaps(gDlHdmiTxInstance,
                                         gVideoDesc,
                                         EXAMPLE_MAX_SVD,
                                         &gWrittenVideoFormats,
                                         &VideoFlags);

    if (ErrCode != TM_OK)
    {
        HDMI_TRACE("tmdlHdmiTxGetEdidVideoCaps failed %ld\n",ErrCode);
        return;
    }


    if (gWrittenVideoFormats <= EXAMPLE_MAX_SVD)
    {

        for(i=0; i<gWrittenVideoFormats; i++)
        {
            if(gVideoDesc[i].nativeVideoFormat)
                NativeVFmt = gVideoDesc[i].videoFormat;
            HDMI_TRACE("Video format %ld",gVideoDesc[i].videoFormat);
        }
    }
}


/* -------------------------------------------- */
/*  sfChooseVideoOutput                         */
/* Based on sink capabilities and on HDMI TX    */
/* IC capabilities we choose to output a format */
/* -------------------------------------------- */
static void sfChooseVideoOutput(void)
{
    UInt8         i;
    Bool          ValidCombinationFound      = False;
    Bool *        gVideoPossibleCombinations = NULL;
    char env_res;

    /* Based on the IC we use ...*/
    switch (gCapabilities.deviceVersion)
    {
    case TMDL_HDMITX_DEVICE_TDA9984:
        gVideoPossibleCombinations = gVideoPossibleCombinationsTDA9984;
        break;
    case TMDL_HDMITX_DEVICE_TDA9989:
        gVideoPossibleCombinations = gVideoPossibleCombinationsTDA9989;
        break;
    case TMDL_HDMITX_DEVICE_TDA9983:
        gVideoPossibleCombinations = gVideoPossibleCombinationsTDA9983;
        break;
    default:
        gVideoPossibleCombinations = gVideoPossibleCombinationsTDA9989;
        break;
    }

    extern char *getenv(char *name);
    extern	long simple_strtol(const char *cp,char **endp,unsigned int base);
    int auto_res = 0;
    char * p_str = getenv("hdmitx_auto_res");
    if(p_str != NULL)
    {
        auto_res = (int)simple_strtol(p_str, NULL, 10);
    }
    else
    {
        printf("##HDMI##    auto_res = NULL\n");
    }
    printf("##HDMI##    auto_res = %d\n",auto_res);
    if(auto_res&&NativeVFmt!=NULL)
    {
        gVideoInConfig.format= NativeVFmt;
        switch(NativeVFmt)
        {

            //4 //4589231706
        case TMDL_HDMITX_VFMT_31_1920x1080p_50Hz:
            env_res = '4';
            break;
        case TMDL_HDMITX_VFMT_16_1920x1080p_60Hz:
            env_res = '5';
            break;
        case TMDL_HDMITX_VFMT_20_1920x1080i_50Hz:
            env_res = '8';
            break;
        case TMDL_HDMITX_VFMT_05_1920x1080i_60Hz:
            env_res = '9';
            break;
        case TMDL_HDMITX_VFMT_19_1280x720p_50Hz:
            env_res = '2';
            break;
        case TMDL_HDMITX_VFMT_04_1280x720p_60Hz:
            env_res = '3';
            break;
        default:
            env_res = '5';
            break;
            _hdmitx_env_set("resolution",&env_res);
        }
    }
    /* first, check is input format is supported by the sink: if yes choose this format (path through)
    if (gWrittenVideoFormats <= EXAMPLE_MAX_SVD) */
    {

        for(i=0; i<gWrittenVideoFormats; i++)
        {

            if (gVideoDesc[i].videoFormat == gVideoInConfig.format)
            {
                ValidCombinationFound = True;
                HDMI_TRACE("Input video format supported %d \n",gVideoDesc[i].videoFormat);
                break;
            }
        }
    }

    /*if input format not supported check if we can up/downscale it to one of the supported video format*/
    /* video formats are assumed to be sorted by preference order*/
    if (ValidCombinationFound != True)
    {
        if (gWrittenVideoFormats <= EXAMPLE_MAX_SVD)
        {

            for(i=0; i<gWrittenVideoFormats; i++)
            {

                if (gVideoPossibleCombinations[gVideoDesc[i].videoFormat] == True)
                {
                    ValidCombinationFound = True;
                    break;
                }
            }
        }
    }



    if (ValidCombinationFound == True)
    {
        gVideoOutConfig.format = gVideoDesc[i].videoFormat;
        HDMI_TRACE("sfChooseVideoOutput choose format %d \n",gVideoDesc[i].videoFormat);
    }
    else
    {
        HDMI_TRACE("sfChooseVideoOutput failed \n");
    }


}


