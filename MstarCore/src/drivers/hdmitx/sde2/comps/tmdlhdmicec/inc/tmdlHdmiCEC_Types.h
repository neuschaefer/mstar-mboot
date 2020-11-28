//=============================================================================
// Copyright (C) 2007 NXP N.V., All Rights Reserved.
// This source code and any compilation or derivative thereof is the proprietary
// information of NXP N.V. and is confidential in nature. Under no circumstances
// is this software to be  exposed to or placed under an Open Source License of
// any type without the expressed written permission of NXP N.V.
//=============================================================================
/*!
    \file    tmdlHdmiCEC_Types.h

	\version 1.0

	\date    04/07/2007

 	\brief   This provides interfaces description of CEC messages.

    \section refs  Reference Documents
             TDA998X Driver - tmdlHdmiTx - SCS.doc
    \note    None.
 
    HISTORY :
    \verbatim
     Date          Modified by CRPRNr  TASKNr  Maintenance description
     -------------|-----------|-------|-------|-----------------------------------
     04/07/2007   |  F.G      |       |       | Creation.
     -------------|-----------|-------|-------|-----------------------------------
    \endverbatim
*/
//==========================================================================

#ifndef TMDLHDMICEC_TYPES_H
#define TMDLHDMICEC_TYPES_H

/*============================================================================*/
/*                       INCLUDE FILES                                        */
/*============================================================================*/

#include "hdmitx/sde2/inc/tmNxTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*/
/*                       MACRO DEFINITIONS                                    */
/*============================================================================*/


/*============================================================================*/
/*                                DEFINES                                     */
/*============================================================================*/

/**< Error Codes */
#define TMDL_ERR_DLHDMICEC_BASE                      CID_DL_HDMICEC
#define TMDL_ERR_DLHDMICEC_COMPATIBILITY             (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_COMPATIBILITY)             /**< SW Interface compatibility   */
#define TMDL_ERR_DLHDMICEC_MAJOR_VERSION             (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_MAJOR_VERSION)             /**< SW Major Version error       */
#define TMDL_ERR_DLHDMICEC_COMP_VERSION              (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_COMP_VERSION)              /**< SW component version error   */
#define TMDL_ERR_DLHDMICEC_BAD_UNIT_NUMBER           (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_BAD_UNIT_NUMBER)           /**< Invalid device unit number   */
#define TMDL_ERR_DLHDMICEC_BAD_INSTANCE              (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_BAD_INSTANCE)              /**< Bad input instance value     */
#define TMDL_ERR_DLHDMICEC_BAD_HANDLE                (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_BAD_HANDLE)                /**< Bad input handle             */
#define TMDL_ERR_DLHDMICEC_BAD_PARAMETER             (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_BAD_PARAMETER)             /**< Invalid input parameter      */
#define TMDL_ERR_DLHDMICEC_NO_RESOURCES              (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_NO_RESOURCES)              /**< Resource is not available    */
#define TMDL_ERR_DLHDMICEC_RESOURCE_OWNED            (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_RESOURCE_OWNED)            /**< Resource is already in use   */
#define TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED        (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_RESOURCE_NOT_OWNED)        /**< Caller does not own resource */
#define TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS       (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_INCONSISTENT_PARAMS)       /**< Inconsistent input params    */
#define TMDL_ERR_DLHDMICEC_NOT_INITIALIZED           (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_NOT_INITIALIZED)           /**< Component is not initialized */
#define TMDL_ERR_DLHDMICEC_NOT_SUPPORTED             (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_NOT_SUPPORTED)             /**< Function is not supported    */
#define TMDL_ERR_DLHDMICEC_INIT_FAILED               (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_INIT_FAILED)               /**< Initialization failed        */
#define TMDL_ERR_DLHDMICEC_BUSY                      (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_BUSY)                      /**< Component is busy            */
#define TMDL_ERR_DLHDMICEC_I2C_READ                  (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_READ)                      /**< Read error                   */
#define TMDL_ERR_DLHDMICEC_I2C_WRITE                 (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_WRITE)                     /**< Write error                  */
#define TMDL_ERR_DLHDMICEC_FULL                      (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_FULL)                      /**< Queue is full                */
#define TMDL_ERR_DLHDMICEC_NOT_STARTED               (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_NOT_STARTED)               /**< Function is not started      */
#define TMDL_ERR_DLHDMICEC_ALREADY_STARTED           (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_ALREADY_STARTED)           /**< Function is already started  */
#define TMDL_ERR_DLHDMICEC_ASSERTION                 (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_ASSERTION)                 /**< Assertion failure            */
#define TMDL_ERR_DLHDMICEC_INVALID_STATE             (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_INVALID_STATE)             /**< Invalid state for function   */
#define TMDL_ERR_DLHDMICEC_OPERATION_NOT_PERMITTED   (TMDL_ERR_DLHDMICEC_BASE + TM_ERR_OPERATION_NOT_PERMITTED)   /**< corresponds to posix EPERM   */

/*============================================================================*/
/*                       ENUM OR TYPE DEFINITIONS                             */
/*============================================================================*/

/*!
	\enum  tmdlHdmiCECAbortReason_t
    \brief This enum indicates the reason for a <Feature Abort> response
*/
typedef enum
{
   CEC_ABORT_UNKNOWN_OPCODE      = 0, /*!< Unrecognized opcode */
   CEC_ABORT_INCORRECT_MODE      = 1, /*!< Not in correct mode to respond */
   CEC_ABORT_NO_SOURCE           = 2, /*!< cannot provide source */
   CEC_ABORT_INVALID_OPERAND     = 3, /*!< Invalid operand  */
   CEC_ABORT_REFUSED             = 4, /*!< Refused */
   CEC_ABORT_UNABLE_TO_DETERMINE = 5  /*!< Unable to Determine */
} tmdlHdmiCECAbortReason_t;

/*!
	\enum  tmdlHdmiCECAnalogueBroadcastType_t
    \brief This enum indicates the analogue broadcast type
*/
typedef enum
{
   CEC_BROADCAST_TYPE_CABLE       = 0x00, /*!< Cable */
   CEC_BROADCAST_TYPE_SATELLITE   = 0x01, /*!< Satellite*/
   CEC_BROADCAST_TYPE_TERRESTRIAL = 0x02 /*!< Terrestrial */
} tmdlHdmiCECAnalogueBroadcastType_t;

/*!
	\enum  _tmdlHdmiCECAnalogueFrequency
    \brief This enum specify the min and max frequency used by an analogue tuner
*/
enum _tmdlHdmiCECAnalogueFrequency
{
    CEC_ANALOG_FREQ_MIN = 0x0000, /*!< Min frequency used by analogue tuner */
    CEC_ANALOG_FREQ_MAX = 0xFFFF  /*!< Max frequency used by analogue tuner */
};

/*!
	\enum  _tmdlHdmiCECAsciiDigit
    \brief This enum represent the min and max of a printable digit character
*/
enum _tmdlHdmiCECAsciiDigit
{
    CEC_ASCII_DIGIT_MIN = 0x30, /*!< Min of a printable digit character */
    CEC_ASCII_DIGIT_MAX = 0x39  /*!< Max of a printable digit character */
};

/*!
	\enum  _tmdlHdmiCECAscii
    \brief This enum represent the min and max of a printable character
*/
enum _tmbsHdmiCECAscii
{
    CEC_ASCII_CHARACTER_MIN  = 0x20, /*!< Min of a printable character */
    CEC_ASCII_CHARACTER_MAX  = 0x7E  /*!< Max of a printable character */
};

/*!
    \enum  _tmdlHdmiCECAudioFormatCode
    \brief This enum represent the min and max of a Audio Format Code is defined
           in CEA-861-D for CEA Short Audio Descriptor
*/
enum _tmdlHdmiCECAudioFormatCode
{
    CEC_AUDIO_FORMAT_CODE_MIN = 0x01, /*!< Min of a Audio Format Code */
    CEC_AUDIO_FORMAT_CODE_MAX = 0x0F  /*!< Max of a Audio Format Code */
};

/*!
	\enum  tmdlHdmiCECAudioRate_t
    \brief This enum indicates the audio range control
*/
typedef enum
{
   CEC_AUDIO_RATE_OFF                        = 0, /*!< Rate Control off */
   CEC_AUDIO_RATE_WIDE_RANGE_STANDARD_RATE   = 1, /*!< Standard rate : 100% rate */
   CEC_AUDIO_RATE_WIDE_RANGE_FAST_RATE       = 2, /*!< Fast rate : Max 101% rate */
   CEC_AUDIO_RATE_WIDE_RANGE_SLOW_RATE       = 3, /*!< Sloaw rate : 99% rate */
   CEC_AUDIO_RATE_NARROW_RANGE_STANDARD_RATE = 4, /*!< Standard rate : 100% rate */
   CEC_AUDIO_RATE_NARROW_RANGE_FAST_RATE     = 5, /*!< Fast rate : Max 101% rate */
   CEC_AUDIO_RATE_NARROW_RANGE_SLOW_RATE     = 6  /*!< Sloaw rate : 99% rate */                                          
} tmdlHdmiCECAudioRate_t;

/*!
	\enum  tmdlHdmiCECAudioMute_t
    \brief This enum indicates the audio current audio mute status
*/
typedef enum
{
   CEC_AUDIO_MUTE_OFF  = 0, /*!< Audio Mute off */
   CEC_AUDIO_MUTE_ON   = 1 /*!< Audio Mute on */
} tmdlHdmiCECAudioMute_t;


/*!
	\struct tmdlHdmiCECAudioStatus_t
    \brief  This union indicates the current audio status of a device
*/
typedef struct _tmdlHdmiCECAudioStatus_t
{
     tmdlHdmiCECAudioMute_t audioMuteStatus   ; /*!< Audio Mute Status */
     UInt8                  audioVolumeStatus ; /*!< Audio Volume Status  */
} tmdlHdmiCECAudioStatus_t, *ptmdlHdmiCECAudioStatus_t;


/*!
	\enum  tmdlHdmiCECBoolean_t
    \brief This enum indicates a Flag
*/
typedef enum
{
   CEC_FALSE  = 0, /*!< False */
   CEC_TRUE   = 1, /*!< True */
} tmdlHdmiCECBoolean_t;


/*!
	\enum  tmdlHdmiCECBroadcastSystem_t
    \brief This enum indicates information about the color system, the sound carrier and IF-frequency
*/
typedef enum
{                                         /*!< Sound  / Sound Modulation / Video Modulation / Vertical Frequency / Color sub-carier         */
   CEC_BROADCAST_SYSTEM_PAL_BG       = 0, /*!< 5.5MHZ / FM                 NEG                50HZ                 4.43 MHZ                 */
   CEC_BROADCAST_SYSTEM_PAL_SECAM_L  = 1, /*!< 6.5MHZ / AM                 POS                50HZ                 Fob 4.25MHz,For 4.406Mhz */
   CEC_BROADCAST_SYSTEM_PAL_M        = 2, /*!< 4.5MHZ / FM                 NEG                60HZ                 3.5756 MHZ               */
   CEC_BROADCAST_SYSTEM_NTSC_M       = 3, /*!< 4.5MHZ / FM                 NEG                60HZ                 3.5795 MHZ               */
   CEC_BROADCAST_SYSTEM_PAL_I        = 4, /*!< 6.0MHZ / FM                 NEG                50HZ                 4.43 MHZ                 */
   CEC_BROADCAST_SYSTEM_SECAM_DK     = 5, /*!< 6.5MHZ / FM                 NEG                50HZ                 Fob 4.25MHz,For 4.406Mhz */
   CEC_BROADCAST_SYSTEM_SECAM_BG     = 6, /*!< 5.5MHZ / FM                 NEG                50HZ                 Fob 4.25MHz,For 4.406Mhz */
   CEC_BROADCAST_SYSTEM_SECAM_L      = 7, /*!< 6.5MHZ / AM                 POS                50HZ                 Fob 4.25MHz,For 4.406Mhz */
   CEC_BROADCAST_SYSTEM_PAL_DK       = 8, /*!< 5.5MHZ / FM                 NEG                50HZ                 4.43MHZ                  */
   CEC_BROADCAST_SYSTEM_FUTURE_USE   = 9, /*!< Future Use   */
   CEC_BROADCAST_SYSTEM_OTHER_SYSTEM = 31 /*!< Other System */
} tmdlHdmiCECBroadcastSystem_t;

/*!
	\enum  tmdlHdmiCECVersion_t
    \brief This enum indicates the supported CEC version
*/
typedef enum
{
   CEC_VERSION_Reserved = 0x00, /*!< CEC Reserved */
   CEC_VERSION_Reserved1 = 0x01, /*!< CEC Reserved */
   CEC_VERSION_Reserved2 = 0x02, /*!< CEC Reserved */
   CEC_VERSION_Reserved3 = 0x03, /*!< CEC Reserved */
   CEC_VERSION_1_3a     = 0x04, /*!< CEC Version 1.3a */
   CEC_VERSION_1_4      = 0x05  /*!< CEC Version 1.4  */
} tmdlHdmiCECVersion_t;

/*!
	\enum  tmdlHdmiCECChanNumFormat_t
    \brief This enum indicates the Channel Format
*/
typedef enum
{
   CEC_FIRST_CHAN_NUMBER  = 0x01, /*!< 1-part channel number */
   CEC_SECOND_CHAN_NUMBER = 0x02  /*!< 2-part channel number */
} tmdlHdmiCECChanNumFormat_t;

/*!
	\struct tmdlHdmiCECChannelIdentifier_t
    \brief  This struct indicates a 1-part Logical or Virtual Channel Number or
            a 2-part Major and Minor channel combination
*/
typedef struct
{
     tmdlHdmiCECChanNumFormat_t ChanNumFormat   ; /*!< Channel Format */
     UInt16                      MajorChanNumber ; /*!< Major Channel Number (if channel is 2-part) */
     UInt16                      MinorChanNumber ; /*!< 1-part Channel Number ,or a Minor Channel Number (if channel is 2-part) */
} tmdlHdmiCECChannelIdentifier_t ;

/*!
	\enum  tmdlHdmiCECDayOfMonth_t
    \brief This enum indicates the day of the month
*/
typedef enum
{
   CEC_FIRST_DAY_OF_MONTH  = 1, /*!< First day of the month */
   CEC_LAST_DAY_OF_MONTH   = 31 /*!< Last day of the month */
} tmdlHdmiCECDayOfMonth_t;

/*!
	\enum  tmdlHdmiCECDecControlMode_t
    \brief This enum indicates command used for opcode <Deck Control>
*/
typedef enum
{
   CEC_DECK_CONTROL_WIND   = 1, /*!< Skip Forward / Wind   */
   CEC_DECK_CONTROL_REWIND = 2, /*!< Skip Reverse / Rewind */
   CEC_DECK_CONTROL_STOP   = 3, /*!< Stop                  */
   CEC_DECK_CONTROL_EJECT  = 4  /*!< Eject                 */
} tmdlHdmiCECDecControlMode_t;

/*!
	\enum  tmdlHdmiCECDecInfo_t
    \brief This enum indicates the current status of a tape or disk deck
*/
typedef enum
{
   CEC_DECK_INFO_PLAY              = 0x11, /*!< Play                  */
   CEC_DECK_INFO_RECORD            = 0x12, /*!< Record                */
   CEC_DECK_INFO_PLAY_REVERSE      = 0x13, /*!< Play Reverse          */
   CEC_DECK_INFO_STILL             = 0x14, /*!< Still                 */
   CEC_DECK_INFO_SLOW              = 0x15, /*!< Slow                  */
   CEC_DECK_INFO_SLOW_REVERSE      = 0x16, /*!< Slow Reverse          */
   CEC_DECK_INFO_FAST_FORWARD      = 0x17, /*!< Fast Forward          */
   CEC_DECK_INFO_FAST_REVERSE      = 0x18, /*!< Fast Reverse          */
   CEC_DECK_INFO_NO_MEDIA          = 0x19, /*!< No Media              */
   CEC_DECK_INFO_STOP              = 0x1A, /*!< Stop                  */
   CEC_DECK_INFO_WIND              = 0x1B, /*!< Skip Forward / Wind   */
   CEC_DECK_INFO_REWIND            = 0x1C, /*!< Skip Reverse / Rewind */
   CEC_DECK_INFO_ID_SEARCH_FORWARD = 0x1D, /*!< Index Search Forward  */
   CEC_DECK_INFO_ID_SEARCH_REVERSE = 0x1E, /*!< Index Search Forward  */
   CEC_DECK_INFO_OTHER_STATUS      = 0x1F  /*!< Other Status          */
} tmdlHdmiCECDecInfo_t;


/*!
	\enum  tmdlHdmiCECDeviceType_t
    \brief This enum indicates the device type
*/
typedef enum
{
   CEC_DEVICE_TYPE_TV               = 0, /*!< TV               */
   CEC_DEVICE_TYPE_REC_DEVICE       = 1, /*!< Recording Device */
   CEC_DEVICE_TYPE_RESERVED         = 2, /*!< Reserved         */
   CEC_DEVICE_TYPE_TUNER            = 3, /*!< Tuner            */
   CEC_DEVICE_TYPE_PLAYBACK_DEVICE  = 4, /*!< PlayBack Device  */
   CEC_DEVICE_TYPE_AUDIO_DEVICE     = 5, /*!< Audio System     */
   CEC_DEVICE_TYPE_PURE_CEC_SWITCTH = 6,  /*!< Pure CEC Switch  */
   CEC_DEVICE_TYPE_VIDEO_PROCESSOR  = 7  /*!< Video Processor  */
} tmdlHdmiCECDeviceType_t;

/*!
	\enum  tmdlHdmiCECServiceIdentMethod_t
    \brief This enum indicates a Service Indentification Method
*/
typedef enum
{
   CEC_SERVICE_DIGITAL  = 0, /*!< Service identified by digital IDs  */
   CEC_SERVICE_CHANNEL  = 1  /*!< Service identified by channel      */
} tmdlHdmiCECServiceIdentMethod_t;

/*!
	\enum  tmdlHdmiCECDigitalBroadcastSystem_t
    \brief This enum indicates the Digital Broadcast System of required service
*/
typedef enum
{
   CEC_DIGITAL_BROADCAST_SYSTEM_ARIB_GENERIC = 0x01, /*!< ARIB generic */
   CEC_DIGITAL_BROADCAST_SYSTEM_ATSC_GENERIC = 0x02, /*!< ATSC generic */
   CEC_DIGITAL_BROADCAST_SYSTEM_DVB_GENERIC  = 0x03, /*!< DVB generic  */
   CEC_DIGITAL_BROADCAST_SYSTEM_ARIB_BS      = 0x08, /*!< ARIB-BS      */
   CEC_DIGITAL_BROADCAST_SYSTEM_ARIB_CS      = 0x09, /*!< ARIB-CS      */
   CEC_DIGITAL_BROADCAST_SYSTEM_ARIB_T       = 0x0A, /*!< ARIB-T       */
   CEC_DIGITAL_BROADCAST_SYSTEM_CABLE        = 0x10, /*!< Cable        */
   CEC_DIGITAL_BROADCAST_SYSTEM_SATELLITE    = 0x11, /*!< Satellite    */
   CEC_DIGITAL_BROADCAST_SYSTEM_TERRESTRIAL  = 0x12, /*!< Terrestrial  */
   CEC_DIGITAL_BROADCAST_SYSTEM_DVB_C        = 0x18, /*!< DVB-C        */
   CEC_DIGITAL_BROADCAST_SYSTEM_DVB_S        = 0x19, /*!< DVB-S        */
   CEC_DIGITAL_BROADCAST_SYSTEM_DVB_S2       = 0x1A, /*!< DVB-S2       */
   CEC_DIGITAL_BROADCAST_SYSTEM_DVB_T        = 0x1B  /*!< DVB-T        */
} tmdlHdmiCECDigitalBroadcastSystem_t;

/*!
	\struct tmdlHdmiCECAribData_t
    \brief  This struct indicates the ARIB Data
*/
typedef struct
{
     UInt16 TransportStreamID ; /*!< Tansport_stream_id of the transport stream carrying the required service                  */
     UInt16 ServiceID         ; /*!< Service_ID of the required service                                                        */
     UInt16 OriginalNetworkID ; /*!< Original_network_ID of the network carrying the transport stream for the required service */
} tmdlHdmiCECAribData_t ;

/*!
	\struct tmdlHdmiCECAtscData_t
    \brief  This struct indicates the ATSC Data
*/
typedef struct
{
     UInt16 TransportStreamID ; /*!< Tansport_stream_id of the transport stream carrying the required service */
     UInt16 ProgramNumber     ; /*!< Program Number of the required service                                   */
     UInt16 Reserved          ; /*!< Reserved                                                                 */
} tmdlHdmiCECAtscData_t ; 

/*!
	\struct tmdlHdmiCECDvbData_t
    \brief  This struct indicates the DVB Data
*/
typedef struct
{
     UInt16 TransportStreamID ; /*!< Tansport_stream_id of the transport stream carrying the required service                  */
     UInt16 ServiceID         ; /*!< Service_ID of the required service                                                        */
     UInt16 OriginalNetworkID ; /*!< Original_network_ID of the network carrying the transport stream for the required service */
} tmdlHdmiCECDvbData_t ;

/*!
	\struct tmdlHdmiCECChannelData_t
    \brief  This struct indicates the Channel Data
*/
typedef struct
{
     tmdlHdmiCECChannelIdentifier_t ChannelIdentifier ; /*!< Logical or virtual channel number of a service */
     UInt16 Reserved                                  ; /*!< Reserved                                       */
} tmdlHdmiCECChannelData_t ;

/*!
	\struct tmdlHdmiCECDigitalServiceIdentification_t
    \brief  This struct indicates the Digital Broadcast System 
            and the parameters to identify a specific service
*/
typedef struct _tmdlHdmiCECDigitalServiceIdentification_t
{
     tmdlHdmiCECServiceIdentMethod_t     ServiceIdentificationMethod ; /*!< See tmdlHdmiCECServiceIdentMethod_t                                                                   */
     tmdlHdmiCECDigitalBroadcastSystem_t DigitalBroadcastSystem      ; /*!< See tmdlHdmiCECDigitalBroadcastSystem_t                                                               */
     void                                *pServiceIdentification     ; /*!< tmdlHdmiCECAribData_t or tmdlHdmiCECAtscData_t or tmdlHdmiCECDvbData_t or tmdlHdmiCECChannelData_t */
}tmdlHdmiCECDigitalServiceIdentification_t, *ptmdlHdmiCECDigitalServiceIdentification_t;

/*!
	\enum  tmdlHdmiCECDisplayControl_t
    \brief This enum indicates the display mode for an on screen display message
*/
typedef enum
{
   CEC_DISPLAY_CONTROL_DEFAULT_TIME           = 0  , /*!< Display for default time */
   CEC_DISPLAY_CONTROL_UNTIL_CLEARED          = 64 , /*!< Display until cleared     */
   CEC_DISPLAY_CONTROL_CLEAR_PREVIOUS_MESSAGE = 128, /*!< Clear previous message    */
   CEC_DISPLAY_CONTROL_RESERVED               = 192  /*!< Clear previous message    */
} tmdlHdmiCECDisplayControl_t;

/*!
	\struct tmdlHdmiCECDuration_t
    \brief  This struct indicates a duration in BCD format
*/
typedef struct
{
     UInt8 Hours  ; /*!< Duration hours in bcd format between 0 and 99 */
     UInt8 Minute ; /*!< Duration minute in bcd format between 0 and 59 */
} tmdlHdmiCECDuration_t ;

/*!
    \brief  This typedef indicates physical adress of device that is to be used as the source of a recording
*/
typedef UInt16 tmdlHdmiCECExternalPhysicalAddress_t ;

/*!
    \brief  This typedef indicates external plug number (1 to 255 )on the recording device
*/
typedef UInt8 tmdlHdmiCECExternalPlug_t;

/*!
	\enum  tmdlHdmiCECExternalSourceSpecifier_t
    \brief This enum indicates External source specifier 
*/
typedef enum
{
   CEC_EXTERNAL_PLUG             = 4  , /*!< Display for default time */
   CEC_EXTERNAL_PHYSICAL_ADDRESS = 5    /*!< Display until cleared     */
} tmdlHdmiCECExternalSourceSpecifier_t;

/*!
    \brief  This typedef indicates External Source is specified bey exeternal plug number on the recording device
            or by the External physical Adress of the required source
*/
typedef UInt8 ExternalSourceSpecifier;


/*!
	\enum  tmdlHdmiCECFeatureOpcode_t
    \brief This enum defines command to be performed
*/
typedef enum
{
   CEC_OPCODE_FEATURE_ABORT                 = 0x00, /*!< */
   CEC_OPCODE_IMAGE_VIEW_ON                 = 0x04, /*!< */
   CEC_OPCODE_TUNER_STEP_INCREMENT          = 0x05, /*!< */
   CEC_OPCODE_TUNER_STEP_DECREMENT          = 0x06, /*!< */
   CEC_OPCODE_TUNER_DEVICE_STATUS           = 0x07, /*!< */
   CEC_OPCODE_GIVE_TUNER_DEVICE_STATUS      = 0x08, /*!< */
   CEC_OPCODE_RECORD_ON                     = 0x09, /*!< */
   CEC_OPCODE_RECORD_STATUS                 = 0x0A, /*!< */
   CEC_OPCODE_RECORD_OFF                    = 0x0B, /*!< */
   CEC_OPCODE_TEXT_VIEW_ON                  = 0x0D, /*!< */
   CEC_OPCODE_RECORD_TV_SCREEN              = 0x0F, /*!< */
   CEC_OPCODE_GIVE_DECK_STATUS              = 0x1A, /*!< */
   CEC_OPCODE_DECK_STATUS                   = 0x1B, /*!< */
   CEC_OPCODE_SET_MENU_LANGUAGE             = 0x32, /*!< */
   CEC_OPCODE_CLEAR_ANALOGUE_TIMER          = 0x33, /*!< */
   CEC_OPCODE_SET_ANALOGUE_TIMER            = 0x34, /*!< */
   CEC_OPCODE_TIMER_STATUS                  = 0x35, /*!< */
   CEC_OPCODE_STANDBY                       = 0x36, /*!< */
   CEC_OPCODE_PLAY                          = 0x41, /*!< */
   CEC_OPCODE_DESCK_CONTROL                 = 0x42, /*!< */
   CEC_OPCODE_TIMER_CLEARED_STATUS          = 0x43, /*!< */
   CEC_OPCODE_USER_CONTROL_PRESSED          = 0x44, /*!< */
   CEC_OPCODE_USER_CONTROL_RELEASED         = 0x45, /*!< */
   CEC_OPCODE_GIVE_OSD_NAME                 = 0x46, /*!< */
   CEC_OPCODE_SET_OSD_NAME                  = 0x47, /*!< */
   CEC_OPCODE_SET_OSD_STRING                = 0x64, /*!< */
   CEC_OPCODE_SET_TIMER_PROGRAM_TITLE       = 0x67, /*!< */
   CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST     = 0x70, /*!< */
   CEC_OPCODE_GIVE_AUDIO_STATUS             = 0x71, /*!< */
   CEC_OPCODE_SET_SYSTEM_AUDIO_MODE         = 0x72, /*!< */
   CEC_OPCODE_REPORT_AUDIO_STATUS           = 0x7A, /*!< */
   CEC_OPCODE_GIVE_SYSTEM_AUDIO_MODE_STATUS = 0x7D, /*!< */
   CEC_OPCODE_SYSTEM_AUDIO_MODE_STATUS      = 0x7E, /*!< */
   CEC_OPCODE_ROUTING_CHANGE                = 0x80, /*!< */
   CEC_OPCODE_ROUTING_INFORMATION           = 0x81, /*!< */
   CEC_OPCODE_ACTIVE_SOURCE                 = 0x82, /*!< */
   CEC_OPCODE_GIVE_PHYSICAL_ADDRESS         = 0x83, /*!< */
   CEC_OPCODE_REPORT_PHYSICAL_ADDRESS       = 0x84, /*!< */
   CEC_OPCODE_REQUEST_ACTIVE_SOURCE         = 0x85, /*!< */
   CEC_OPCODE_SET_STREAM_PATH               = 0x86, /*!< */
   CEC_OPCODE_DEVICE_VENDOR_ID		    = 0x87, /*!< */
   CEC_OPCODE_VENDOR_COMMAND                = 0x89, /*!< */
   CEC_OPCODE_VENDOR_REMOTE_BUTTON_DOWN     = 0x8A, /*!< */
   CEC_OPCODE_VENDOR_REMOTE_BUTTON_UP       = 0x8B, /*!< */
   CEC_OPCODE_GIVE_DEVICE_VENDOR_ID         = 0x8C, /*!< */
   CEC_OPCODE_MENU_REQUEST                  = 0x8D, /*!< */
   CEC_OPCODE_MENU_STATUS                   = 0x8E, /*!< */
   CEC_OPCODE_GIVE_DEVICE_POWER_STATUS      = 0x8F, /*!< */
   CEC_OPCODE_REPORT_POWER_STATUS           = 0x90, /*!< */
   CEC_OPCODE_GET_MENU_LANGUAGE             = 0x91, /*!< */
   CEC_OPCODE_SET_ANALOGUE_SERVICE          = 0x92, /*!< */
   CEC_OPCODE_SET_DIGITAL_SERVICE           = 0x93, /*!< */
   CEC_OPCODE_SET_DIGITAL_TIMER             = 0x97, /*!< */
   CEC_OPCODE_CLEAR_DIGITAL_TIMER           = 0x99, /*!< */
   CEC_OPCODE_SET_AUDIO_RATE                = 0x9A, /*!< */
   CEC_OPCODE_INACTIVE_SOURCE               = 0x9D, /*!< */
   CEC_OPCODE_CEC_VERSION                   = 0x9E, /*!< */
   CEC_OPCODE_GET_CEC_VERSION               = 0x9F, /*!< */
   CEC_OPCODE_VENDOR_COMMAND_WITH_ID        = 0xA0, /*!< */
   CEC_OPCODE_CLEAR_EXTERNAL_TIMER          = 0xA1, /*!< */
   CEC_OPCODE_SET_EXTERNAL_TIMER            = 0xA2, /*!< */
   CEC_OPCODE_REPORT_SHORT_AUDIO_DESCRIPTOR = 0xA3, /*!< */
   CEC_OPCODE_REQUEST_SHORT_AUDIO_DESCRIPTOR = 0xA4, /*!< */
   CEC_OPCODE_INITATE_ARC                   = 0xC0, /*!< */
   CEC_OPCODE_REPORT_ARC_INITIATED          = 0xC1, /*!< */
   CEC_OPCODE_REPORT_ARC_TERMINATED         = 0xC2, /*!< */
   CEC_OPCODE_REPORT_ARC_INITIATION         = 0xC3, /*!< */
   CEC_OPCODE_REPORT_ARC_TERMINATION        = 0xC4, /*!< */
   CEC_OPCODE_TERMINATE_ARC                 = 0xC5, /*!< */
   CEC_OPCODE_ABORT_MESSAGE                 = 0xFF  /*!< This message is reserved for testing*/
} tmdlHdmiCECFeatureOpcode_t;


/*!
	\enum  tmdlHdmiCECMenuRequestType_t
    \brief This enum specifies wether to activate or desactivate a devices menu or
           simply query its current menu status
*/
typedef enum
{
   CEC_MENU_TYPE_ACTIVATE        = 0 , /*!< Activate   */
   CEC_MENU_TYPE_DEACTIVATE      = 1 , /*!< Deactivate */
   CEC_MENU_TYPE_QUERY           = 2   /*!< Query      */
} tmdlHdmiCECMenuRequestType_t;

/*!
	\enum  tmdlHdmiCECMenuState_t
    \brief This enum pecifies state of the device menu
*/
typedef enum
{
   CEC_MENU_STATE_ACTIVATE        = 0 , /*!< Activate   */
   CEC_MENU_STATE_DEACTIVATE      = 1   /*!< Deactivate */
} tmdlHdmiCECMenuState_t;

/*!
	\enum  tmdlHdmiCECPlayMode_t
    \brief This enum indicates in which mode to play media
*/
typedef enum
{
   CEC_MODE_PLAY_FORWARD              = 0x24 ,
   CEC_MODE_PLAY_REVERSE              = 0x20 ,
   CEC_MODE_FAST_FORWARD_MIN_SPEED    = 0x05 ,
   CEC_MODE_FAST_FORWARD_MEDIUM_SPEED = 0x06 ,
   CEC_MODE_FAST_FORWARD_MAX_SPEED    = 0x07 ,
   CEC_MODE_FAST_REVERSE_MIN_SPEED    = 0x09 ,
   CEC_MODE_FAST_REVERSE_MEDIUM_SPEED = 0x0A ,
   CEC_MODE_FAST_REVERSE_MAX_SPEED    = 0x0B ,
   CEC_MODE_SLOW_FORWARD_MIN_SPEED    = 0x15 ,
   CEC_MODE_SLOW_FORWARD_MEDIUM_SPEED = 0x16 ,
   CEC_MODE_SLOW_FORWARD_MAX_SPEED    = 0x17 ,
   CEC_MODE_SLOW_REVERSE_MIN_SPEED    = 0x19 ,
   CEC_MODE_SLOW_REVERSE_MEDIUM_SPEED = 0x1A ,
   CEC_MODE_SLOW_REVERSE_MAX_SPEED    = 0x1B  
} tmdlHdmiCECPlayMode_t;

/*!
	\enum  tmdlHdmiCECPowerStatus_t
    \brief This enum indicates the current power status of a device
*/
typedef enum
{
   CEC_POWER_STATUS_ON                       = 0x00 , /*!< On                          */
   CEC_POWER_STATUS_STANDBY                  = 0x01 , /*!< Standby                     */
   CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON = 0x02 , /*!< In Transition Standby to On */
   CEC_POWER_STATUS_TRANSITION_ON_TO_STANDBY = 0x03   /*!< In Transition On to StandBy */
} tmdlHdmiCECPowerStatus_t;

/*!
	\enum  tmdlHdmiCECRecordSourceType_t
    \brief This enum allows the record source to be specified for a recording
*/
typedef enum
{
   CEC_RECORD_SOURCE_OWN_SOURCE                = 1 , /*!< Own Source                */
   CEC_RECORD_SOURCE_DIGITAL_SERVICE           = 2 , /*!< Digital Service           */
   CEC_RECORD_SOURCE_ANALOGUE_SERVICE          = 3 , /*!< Analogue Service          */
   CEC_RECORD_SOURCE_EXTERNAL_PLUG             = 4 , /*!< External Plug             */
   CEC_RECORD_SOURCE_EXTERNAL_PHYSICAL_ADDRESS = 5   /*!< External Physical Address */
} tmdlHdmiCECRecordSourceType_t;

/*!
	\enum  tmdlHdmiCECRecordStatusInfo_t
    \brief This enum indicates the status of a recording
*/
typedef enum
{
   CEC_RECORD_STATUS_INFO_RECORDING_CURRENTLY_SELECTED_SOURCE       = 1 , /*!< */
   CEC_RECORD_STATUS_INFO_RECORDING_DIGITAL_SERVICE                 = 2 , /*!< */
   CEC_RECORD_STATUS_INFO_RECORDING_ANALOGUE_SERVCICE               = 3 , /*!< */
   CEC_RECORD_STATUS_INFO_RECORDING_EXTERNAL_INPUT                  = 4 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_UNABLE_TO_RECORD_DIGITAL_SERVICE   = 5 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_UNABLE_TO_RECORD_ANALOGUE_SERVICE  = 6 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_UNABLE_TO_SELECT_REQUIRED_SERVICE  = 7 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_INVALID_EXTERNAL_PLUG_NUMBER       = 9 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_INVALID_EXTERNAL_PHYSICAL_ADDRESS  = 10 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_CA_SYSTEM_NOT_SUPPORTED            = 11 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_NO_OR_INSUFFICIENT_CA_ENTITLEMENTS = 12 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_NOT_ALLOWED_TO_COPY_SOURCE         = 13 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_NO_FURTHER_COPY_ALLOWED            = 14 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_NO_MEDIA                           = 16 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_PLAYING                            = 17 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_ALREADY_RECORDING                  = 18 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_MEDIA_PROTECTED                    = 19 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_NO_SOURCE_SIGNAL                   = 20 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_MEDIA_PROBLEM                      = 21 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_NOT_ENOUGH_SPACE_AVAILABLE         = 22 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_REC_PARENTAL_LOCK_ON                   = 23 , /*!< */
   CEC_RECORD_STATUS_INFO_RECORDING_TERMINATED_NORMALLY             = 26 , /*!< */
   CEC_RECORD_STATUS_INFO_RECORDING_HAS_ALREADY_TERMINATED          = 27 , /*!< */
   CEC_RECORD_STATUS_INFO_NO_RECORDING_OTHER_REASON                 = 31 /*!< */
} tmdlHdmiCECRecordStatusInfo_t;


/*!
	\enum  tmdlHdmiCECRecordingSequence_t
    \brief This enum indicates the status of a recording
*/
typedef enum
{
   CEC_RECORDING_SEQUENCE_ONCE_ONLY = 0 , /*!< */
   CEC_RECORDING_SEQUENCE_SYNDAY    = 1 , /*!< */
   CEC_RECORDING_SEQUENCE_MONDAY    = 2 , /*!< */
   CEC_RECORDING_SEQUENCE_TUESDAY   = 4 , /*!< */
   CEC_RECORDING_SEQUENCE_WEDNESDAY = 8 , /*!< */
   CEC_RECORDING_SEQUENCE_THURSDAY  = 16, /*!< */
   CEC_RECORDING_SEQUENCE_FRIDAY    = 32, /*!< */
   CEC_RECORDING_SEQUENCE_SATURDAY  = 64  /*!< */
} tmdlHdmiCECRecordingSequence_t;

/*!
	\enum  tmdlHdmiCECStatusRequest_t
    \brief This enum contains the status request mode which can be report once or
           on all future state changes or reporting off.
*/
typedef enum
{
   CEC_STATUS_REQUEST_ON   = 1 , /*!< Status Request ON   */
   CEC_STATUS_REQUEST_OFF  = 2 , /*!< Status Request OFF  */
   CEC_STATUS_REQUEST_ONCE = 3   /*!< Status Request ONCE */
} tmdlHdmiCECStatusRequest_t;

/*!
	\enum  tmdlHdmiCECSystemAudioStatus_t
    \brief This enum indicates if the system audio Mode is On or Off
*/
typedef enum
{
   CEC_SYSTEM_AUDIO_STATUS_OFF  = 0 ,   /*!< Status Request OFF  */   
   CEC_SYSTEM_AUDIO_STATUS_ON   = 1  /*!< Status Request ON   */
} tmdlHdmiCECSystemAudioStatus_t;

/*!
	\enum  tmdlHdmiCECTimerClearedStatusData_t
    \brief This enum indicates status in <Timer Cleared Status> message
*/
typedef enum
{
   CEC_TIMER_STATUS_TIMER_NOT_CLEARED_RECORDING          = 0,  /*!< */
   CEC_TIMER_STATUS_TIMER_NOT_CLEARED_NO_MATCHING        = 1,  /*!< */
   CEC_TIMER_STATUS_TIMER_NOT_CLEARED_NO_INFO_AVAILABLE  = 2,  /*!< */
   CEC_TIMER_STATUS_TIMER_NOT_TIMER_CLEARED              = 128 /*!< */
} tmdlHdmiCECTimerClearedStatusData_t;


/*!
	\enum  tmdlHdmiCECTimerOverlapWarning_t
    \brief This enum indicates if there is another timer block already set which
           overlaps with this new recording request
*/
typedef enum
{
   CEC_TIMER_OVERLAP_WARNING_NO_OVERLAP            = 0, /*!< No Overlap   */
   CEC_TIMER_OVERLAP_WARNING_TIMER_BLOCKS_OVERLAP  = 1  /*!< Timer blocks overlap  */
} tmdlHdmiCECTimerOverlapWarning_t;

/*!
	\enum  tmdlHdmiCECMediaInfo_t
    \brief This enum indicates if removable media is present and its write protect state
*/
typedef enum
{
   CEC_MEDIA_INFO_MEDIA_PRESENT_AND_NOT_PROTECTED   = 0, /*!< Media present and not protected */
   CEC_MEDIA_INFO_MEDIA_PRESENT_BUT_PROTECTED       = 1, /*!< Media present but protected     */
   CEC_MEDIA_INFO_MEDIA_NOT_PRESENT                 = 2, /*!< Media not present               */
   CEC_MEDIA_INFO_FUTURE_USE                        = 3  /*!< Future use                      */
} tmdlHdmiCECMediaInfo_t;


/*!
	\enum  tmdlHdmiCECProgrammedIndicator_t
    \brief This enum indicates a selector for [Timer Programmed Info]
*/
typedef enum
{
   CEC_PROGRAM_INDICATOR_NOT_PROGRAMMED = 0, /*!< */
   CEC_PROGRAM_INDICATOR_PROGRAMMED     = 1  /*!< */
} tmdlHdmiCECProgrammedIndicator_t;

/*!
	\enum  tmdlHdmiCECProgrammedInfo_t
    \brief This enum indicates any non-fatal issues with the programming request
*/
typedef enum
{
   CEC_PROGRAM_INFO_ENOUGHT_SPACE_AVAILABLE_FOR_RECORDING     = 8, /*!< */
   CEC_PROGRAM_INFO_NOT_ENOUGHT_SPACE_AVAILABLE_FOR_RECORDING = 9, /*!< */
   CEC_PROGRAM_INFO_NO_MEDIA_INFO_AVAILABLE                   = 10,/*!< */
   CEC_PROGRAM_INFO_MAY_NOT_BE_ENOUGH_SPACE_AVAILABLE         = 11 /*!< */
} tmdlHdmiCECProgrammedInfo_t;


/*!
	\enum  tmdlHdmiCECNotProgrammedErrorInfo_t
    \brief This enum indicates reason for programming failure
*/
typedef enum
{
   CEC_PROGRAM_ERROR_INFO_FUTURE_USE                        = 0,  /*!< */
   CEC_PROGRAM_ERROR_INFO_NO_FREE_TIMER_AVAILABLE           = 1,  /*!< */
   CEC_PROGRAM_ERROR_INFO_DATE_OUT_OF_RANGE                 = 2,  /*!< */
   CEC_PROGRAM_ERROR_INFO_RECORDING_SEQUENCE_ERROR          = 3,  /*!< */
   CEC_PROGRAM_ERROR_INFO_INVALID_EXTERNAL_PLUG_NUMBER      = 4,  /*!< */
   CEC_PROGRAM_ERROR_INFO_INVALID_EXTERNAL_PHYSICAL_ADDRESS = 5,  /*!< */
   CEC_PROGRAM_ERROR_INFO_CA_SYSTEM_NOT_SUPPORTED           = 6,  /*!< */
   CEC_PROGRAM_ERROR_INFO_NO_OR_INSUFFICIENT_CA_ENTITLMENTS = 7,  /*!< */
   CEC_PROGRAM_ERROR_INFO_DOES_NOT_SUPPORT_RESOLUTION       = 8,  /*!< Tuner or recorder does not support HD */
   CEC_PROGRAM_ERROR_INFO_PARENTAL_LOCK_ON                  = 9,  /*!< */
   CEC_PROGRAM_ERROR_INFO_CLOCK_FAILURE                     = 10, /*!< */
   CEC_PROGRAM_ERROR_INFO_DUPLICATE_ALREADY_PROGRAMMED      = 14  /*!< A timer block with identical details has already been programmed*/
} tmdlHdmiCECNotProgrammedErrorInfo_t;

/*!
	\struct tmdlHdmiCECTimerProgrammedInfo_t
    \brief  This struct 
*/
typedef struct
{
  tmdlHdmiCECProgrammedIndicator_t SelectProgramInfo ; /*!< tmdlHdmiCECProgrammedIndicator_t */
  UInt8                             ProgramInfo;        /*!< tmdlHdmiCECProgrammedInfo_t or tmdlHdmiCECNotProgrammedErrorInfo_t*/
  UInt16                            DurationAvailable ; /*!< Optional paramter : If [Programmed Info] is "Not enough space available" */
} tmdlHdmiCECTimerProgrammedInfo_t ;                   /*!<  If [Not Programmed Info] is "Duplicate : already programmed" */

/*!
	\struct tmdlHdmiCECTimerStatusData_t
    \brief  This struct is used by recording device to respond to the initiator
            of a <Set Timer> message
*/
typedef struct
{
  tmdlHdmiCECTimerOverlapWarning_t TimerOverlapWarning ; /*!< Indicates if there is another timer block already set which overlaps with this bew recording request*/
  tmdlHdmiCECMediaInfo_t           MediaInfo           ; /*!< Indicate if removable media is present and its write protect state */
  tmdlHdmiCECTimerProgrammedInfo_t TimerProgrammedInfo ; /*!< Give information about how and if the programming request has been done */
} tmdlHdmiCECTimerStatusData_t ;


/*!
	\enum  tmdlHdmiCECRecordingFlag_t
    \brief This enum indicates if the tuner is being used as a source of a recording
*/
typedef enum
{
   CEC_RECORDING_FLAG_NOT_BEING_USED_FOR_RECORDING = 0, /*!< Not Being used for recording  */
   CEC_RECORDING_FLAG_BEING_USED_FOR_RECORDING     = 1  /*!< Being used for recording      */
} tmdlHdmiCECRecordingFlag_t;

/*!
	\enum  tmdlHdmiCECTunerDisplayInfo_t
    \brief This enum indicates if the device is currently displaying its tuner or not.
           (it may for example be displaying an external source or media)
*/
typedef enum
{
   CEC_TUNER_DISPLAY_MEDIA_DISPLAYING_DIGITAL_TUNER  = 0, /*!< Displaying Digital Tuner */
   CEC_TUNER_DISPLAY_MEDIA_NOT_DISPLAYING_TUNER      = 1, /*!< Not Displaying Tuner */
   CEC_TUNER_DISPLAY_MEDIA_DISPLAYING_ANALOGUE_TUNER = 2  /*!< Not Displaying Tuner */
} tmdlHdmiCECTunerDisplayInfo_t;

/*!
    \enum  tmdlHdmiCECUiBroadcastType_t
    \brief This enum indicates type of broadcast
*/
typedef enum
{
   CEC_UI_BROADCAST_TYPE_ALL_AVAILABLE           = 0x00 , /*!< */
   CEC_UI_BROADCAST_TYPE_DIGITAL_ANALOGUE_TOGGLE = 0x01 , /*!< */
   CEC_UI_BROADCAST_TYPE_ANALOGUE                = 0x10 , /*!< */
   CEC_UI_BROADCAST_TYPE_ANALOGUE_TERRESTRIAL    = 0x20 , /*!< */
   CEC_UI_BROADCAST_TYPE_ANALOGUE_CABLE          = 0x30 , /*!< */
   CEC_UI_BROADCAST_TYPE_ANALOGUE_SATELLITE      = 0x40 , /*!< */
   CEC_UI_BROADCAST_TYPE_DIGITAL                 = 0x50 , /*!< */
   CEC_UI_BROADCAST_TYPE_DIGITAL_TERRESTRIAL     = 0x60 , /*!< */
   CEC_UI_BROADCAST_TYPE_DIGITAL_CABLE           = 0x70 , /*!< */
   CEC_UI_BROADCAST_TYPE_DIGITAL_SATELLITE       = 0x80 , /*!< */
   CEC_UI_BROADCAST_TYPE_DIGITAL_COM_SATELLITE   = 0x90 , /*!< */
   CEC_UI_BROADCAST_TYPE_DIGITAL_COM_SATELLITE_2 = 0x91 , /*!< */
   CEC_UI_BROADCAST_TYPE_IP                      = 0xA0   /*!< */
} tmdlHdmiCECUiBroadcastType_t;

/*!
    \enum  tmdlHdmiCECUiSoundPresentationControl_t
    \brief This enum indicates the selected command
*/
typedef enum
{
   CEC_UI_PRESENTATION_CONTROL_SOUND_MIX_DUAL_MONO        = 0x20 , /*!< "Sound Mixing Mode (Dual Mono)" */
   CEC_UI_PRESENTATION_CONTROL_SOUND_MIX_KARAOKE          = 0x30 , /*!< "Sound Mixing Mode (Karaoke)" */
   CEC_UI_PRESENTATION_CONTROL_SELECT_AUDIO_DOWNMIX       = 0x80 , /*!< "Select Audio Downmix Mode" */
   CEC_UI_PRESENTATION_CONTROL_SELECT_AUDIO_REVERBERATION = 0x90 , /*!< "Select Audio Reverberation Processing Mode" */
   CEC_UI_PRESENTATION_CONTROL_SELECT_AUDIO_EQUALIZER     = 0xA0 , /*!< "Select Audio Equalizer Mode" */
   CEC_UI_PRESENTATION_CONTROL_BASS_STEP_PLUS             = 0xB1 , /*!< "bass step + " */
   CEC_UI_PRESENTATION_CONTROL_BASS_NEUTRAL_POSITION      = 0xB2 , /*!< "bass neutral position" */
   CEC_UI_PRESENTATION_CONTROL_BASS_STEP_MINUS            = 0xB3 , /*!< "bass step - " */
   CEC_UI_PRESENTATION_CONTROL_TREBLE_STEP_PLUS           = 0xC1 , /*!< "Treble step + " */
   CEC_UI_PRESENTATION_CONTROL_TREBLE_NEUTRAL_POSITION    = 0xC2 , /*!< "Treble neutral position" */
   CEC_UI_PRESENTATION_CONTROL_TREBLE_STEP_MINUS          = 0xC3  /*!< "Treble step - " */
 
} tmdlHdmiCECUiSoundPresentationControl_t;

/*!
	\enum  tmdlHdmiCECUserRemoteControlCommand_t
    \brief This enum indicates the remote control button pressed
*/
typedef enum
{
   CEC_REMOTE_BUTTON_SELECT                       = 0, 
   CEC_REMOTE_BUTTON_UP                           = 1, 
   CEC_REMOTE_BUTTON_DOWN                         = 2,
   CEC_REMOTE_BUTTON_LEFT                         = 3,
   CEC_REMOTE_BUTTON_RIGHT                        = 4,
   CEC_REMOTE_BUTTON_RIGHT_UP                     = 5,
   CEC_REMOTE_BUTTON_RIGHT_DOWN                   = 6,
   CEC_REMOTE_BUTTON_LEFT_UP                      = 7,
   CEC_REMOTE_BUTTON_LEFT_DOWN                    = 8,
   CEC_REMOTE_BUTTON_ROOT_MENU                    = 9,
   CEC_REMOTE_BUTTON_SETUP_MENU                   = 10,
   CEC_REMOTE_BUTTON_CONTENTS_MENU                = 11,
   CEC_REMOTE_BUTTON_FAVORITE_MENU                = 12,
   CEC_REMOTE_BUTTON_EXIT                         = 13,
   CEC_REMOTE_BUTTON_MEDIA_TOP_MENU               = 16,
   CEC_REMOTE_BUTTON_MEDIA_CONTEXT                = 17,
   CEC_REMOTE_BUTTON_NUMBER_ENTRY_MODE            = 29,
   CEC_REMOTE_BUTTON_NUMBER_11                    = 30,
   CEC_REMOTE_BUTTON_NUMBER_12                    = 31,
   CEC_REMOTE_BUTTON_NUMBER_0_OR_NUMBER_10        = 32,
   CEC_REMOTE_BUTTON_NUMBER_1                     = 33,
   CEC_REMOTE_BUTTON_NUMBER_2                     = 34,
   CEC_REMOTE_BUTTON_NUMBER_3                     = 35,
   CEC_REMOTE_BUTTON_NUMBER_4                     = 36,
   CEC_REMOTE_BUTTON_NUMBER_5                     = 37,
   CEC_REMOTE_BUTTON_NUMBER_6                     = 38,
   CEC_REMOTE_BUTTON_NUMBER_7                     = 39,
   CEC_REMOTE_BUTTON_NUMBER_8                     = 40,
   CEC_REMOTE_BUTTON_NUMBER_9                     = 41,
   CEC_REMOTE_BUTTON_DOT                          = 42,
   CEC_REMOTE_BUTTON_ENTER                        = 43,
   CEC_REMOTE_BUTTON_CLEAR                        = 44,
   CEC_REMOTE_BUTTON_NEXT_FAVORITE                = 47,
   CEC_REMOTE_BUTTON_CHANNEL_UP                   = 48,
   CEC_REMOTE_BUTTON_CHANNEL_DOWN                 = 49,
   CEC_REMOTE_BUTTON_PREVIOUS_CHANNEL             = 50,
   CEC_REMOTE_BUTTON_SOUND_SELECT                 = 51,
   CEC_REMOTE_BUTTON_INPUT_SELECT                 = 52,
   CEC_REMOTE_BUTTON_DISPLAY_INFORMATION          = 53,
   CEC_REMOTE_BUTTON_HELP                         = 54,
   CEC_REMOTE_BUTTON_PAGE_UP                      = 55,
   CEC_REMOTE_BUTTON_PAGE_DOWN                    = 56,
   CEC_REMOTE_BUTTON_POWER                        = 64,
   CEC_REMOTE_BUTTON_VOLUME_UP                    = 65,
   CEC_REMOTE_BUTTON_VOLUME_DOWN                  = 66,
   CEC_REMOTE_BUTTON_MUTE                         = 67,
   CEC_REMOTE_BUTTON_PLAY                         = 68,
   CEC_REMOTE_BUTTON_STOP                         = 69,
   CEC_REMOTE_BUTTON_PAUSE                        = 70,
   CEC_REMOTE_BUTTON_RECORD                       = 71,
   CEC_REMOTE_BUTTON_REWIND                       = 72,
   CEC_REMOTE_BUTTON_FAST_FORWARD                 = 73,
   CEC_REMOTE_BUTTON_EJECT                        = 74,
   CEC_REMOTE_BUTTON_FORWARD                      = 75,
   CEC_REMOTE_BUTTON_BACKWARD                     = 76,
   CEC_REMOTE_BUTTON_STOP_RECORD                  = 77,
   CEC_REMOTE_BUTTON_PAUSE_RECORD                 = 78,
   CEC_REMOTE_BUTTON_ANGLE                        = 80,
   CEC_REMOTE_BUTTON_SUB_PICTURE                  = 81,
   CEC_REMOTE_BUTTON_VIDEO_ON_DEMAND              = 82,
   CEC_REMOTE_BUTTON_ELECTRONIC_PROGRAM_GUIDE     = 83,
   CEC_REMOTE_BUTTON_TIMER_PROGRAMMING            = 84,
   CEC_REMOTE_BUTTON_INITIAL_CONFIGURATION        = 85,
   CEC_REMOTE_BUTTON_SELECT_BROADCAST_TYPE        = 86,
   CEC_REMOTE_BUTTON_SELECT_SOUND_PRESENTATION    = 87,
   CEC_REMOTE_BUTTON_PLAY_FUNCTION                = 96,
   CEC_REMOTE_BUTTON_PAUSE_PLAY_FUNCTION          = 97,
   CEC_REMOTE_BUTTON_RECORD_FUNCTION              = 98,
   CEC_REMOTE_BUTTON_PAUSE_RECORD_FUNCTION        = 99,
   CEC_REMOTE_BUTTON_STOP_FUNCTION                = 100,
   CEC_REMOTE_BUTTON_MUTE_FUNCTION                = 101,
   CEC_REMOTE_BUTTON_RESTORE_VOLUME_FUNCTION      = 102,
   CEC_REMOTE_BUTTON_TUNE_FUNCTION                = 103,
   CEC_REMOTE_BUTTON_SELECT_MEDIA_FUNCTION        = 104,
   CEC_REMOTE_BUTTON_SELECT_AV_INPUT_FUNCTION     = 105,
   CEC_REMOTE_BUTTON_SELECT_AUDIO_INPUT_FUNCTION  = 106,
   CEC_REMOTE_BUTTON_POWER_TOGGLE_FUNCTION        = 107,
   CEC_REMOTE_BUTTON_POWER_OFF_FUNCTION           = 108,
   CEC_REMOTE_BUTTON_POWER_ON_FUNCTION            = 109,
   CEC_REMOTE_BUTTON_F1_BLUE                      = 113,
   CEC_REMOTE_BUTTON_F2_RED                       = 114,
   CEC_REMOTE_BUTTON_F3_GREEN                     = 115,
   CEC_REMOTE_BUTTON_F4_YELLOW                    = 116,
   CEC_REMOTE_BUTTON_F5                           = 117,
   CEC_REMOTE_BUTTON_DATA                         = 118
} tmdlHdmiCECUserRemoteControlCommand_t;

/*!
	\enum  tmdlHdmiCECLogicalAddress_t
    \brief This enum indicates the logical address of the a device
*/
typedef enum
{
   CEC_LOGICAL_ADDRESS_TV                     = 0,  /*!< TV                    */
   CEC_LOGICAL_ADDRESS_RECORDING_DEVICE_1     = 1,  /*!< Recording Device 1    */
   CEC_LOGICAL_ADDRESS_RECORDING_DEVICE_2     = 2,  /*!< Recording Device 1    */
   CEC_LOGICAL_ADDRESS_TUNER_1                = 3,  /*!< Tuner 1               */
   CEC_LOGICAL_ADDRESS_PLAYBACK_DEVICE_1      = 4,  /*!< Playback Device 1     */
   CEC_LOGICAL_ADDRESS_AUDIO_SYSTEM           = 5,  /*!< Audio System          */
   CEC_LOGICAL_ADDRESS_TUNER_2                = 6,  /*!< Tuner 2               */
   CEC_LOGICAL_ADDRESS_TUNER_3                = 7,  /*!< Tuner 3               */
   CEC_LOGICAL_ADDRESS_PLAYBACK_DEVICE_2      = 8,  /*!< Playback Device 2     */
   CEC_LOGICAL_ADDRESS_RECORDING_DEVICE_3     = 9,  /*!< Recording Device 3    */
   CEC_LOGICAL_ADDRESS_TUNER_4                = 10, /*!< Tuner 4               */
   CEC_LOGICAL_ADDRESS_PLAYBACK_DEVICE_3      = 11, /*!< Playback Device 3     */
   CEC_LOGICAL_ADDRESS_RESERVED1              = 12, /*!< Reserved              */
   CEC_LOGICAL_ADDRESS_RESERVED2              = 13, /*!< Reserved              */
   CEC_LOGICAL_ADDRESS_SPECIFIC_USE           = 14, /*!< Specific Use          */
   CEC_LOGICAL_ADDRESS_UNREGISTRED_BROADCAST  = 15  /*!< Unregistred/Broadcast */
} tmdlHdmiCECLogicalAddress_t;


/*!
   \enum  tmdlHdmiCecEvent_t
   \brief Enum listing all events that can be signalled to application
 */
typedef enum
{
    TMDL_HDMICEC_CALLBACK_MESSAGE_AVAILABLE = 0,  /**< A message is available on CEC line */
    TMDL_HDMICEC_CALLBACK_STATUS = 1,             /**< Status of CEC line */
} tmdlHdmiCecEvent_t;

/*!
   \enum  tmdlHdmiCecEventStatus_t
   \brief Enum listing all available event status
 */
typedef enum
{
    TMDL_HDMICEC_EVENT_ENABLED,      /*!< Event is enabled  */
    TMDL_HDMICEC_EVENT_DISABLED      /*!< Event is disabled */
} tmdlHdmiCecEventStatus_t;

/**
 * \brief System function pointer type, to call user I2C read/write functions
 * \param slaveAddr     The I2C slave address
 * \param firstRegister The first device register address to read or write 
 * \param lenData       Length of data to read or write (i.e. no. of registers)
 * \param pData         Pointer to data to write, or to buffer to receive data
 * \return              The call result:
 *                      - TM_OK: the call was successful
 *                      - TMBSL_ERR_HDMI_I2C_WRITE: failed when writing
 *                      - TMBSL_ERR_HDMI_I2C_READ:  failed when reading
 */
typedef struct
{
    UInt8 slaveAddr;
    UInt8 firstRegister;
    UInt8 lenData;
    UInt8 *pData;
} tmdlHdmiCecSysArgs_t;
typedef tmErrorCode_t (*ptmdlHdmiCecSysFunc_t) (tmdlHdmiCecSysArgs_t *pSysArgs);


/*!
   \brief Timer function pointer type, to call an application timer
   \param Parameter ms: Delay in milliseconds required
 */
typedef Void (*ptmbslHdmiCecSysFuncTimer_t) (UInt16 ms);

/*!
   \brief Callback function pointer type, used to allow driver to callback
          application when activity status is changing at input.
   \param Event Identifier of the source event.
 */
typedef void (*ptmdlHdmiCecCallbackFunc_t) (tmdlHdmiCecEvent_t event,
                                               UInt8           *pdata,
                                               UInt8           size);

/*!
   \brief Enum listing all supported device versions
 */
 typedef enum
 {
     TMDL_HDMICEC_DEVICE_UNKNOWN, /*!< HW device is unknown   */
     TMDL_HDMICEC_DEVICE_TDA9950, /*!< HW device is a TDA9950 */
     TMDL_HDMICEC_DEVICE_TDA9989, /*!< HW device is a TDA9989 */
 } tmdlHdmiCecDeviceVersion_t;


/*!
   \brief Enum listing possible CEC clock source
 */
 typedef enum
 {
     TMDL_HDMICEC_CLOCK_XTAL,
     TMDL_HDMICEC_CLOCK_FRO,
     TMDL_HDMICEC_CLOCK_PCLK
 } tmdlHdmiCecClockSource_t;


/**
 * \brief Structure describing unit capabilities
 */
typedef struct
{
    tmdlHdmiCecDeviceVersion_t DeviceVersion;  /*!< HW device version                        */
    tmdlHdmiCECVersion_t       HdmiCecVersion; /*!< Supported HDMI CEC standard version      */
} tmdlHdmiCecCapabilities_t;

 
/*!
	\struct tmdlHdmiCECInstanceSetup_t
    \brief  This struct is used to setup CEC driver by application
            Application setup the device and state of the device.
*/

typedef struct _tmdlHdmiCecInstanceSetup_t
{
    tmdlHdmiCECLogicalAddress_t DeviceLogicalAddress;
    tmdlHdmiCecClockSource_t    cecClockSource;
//  tmdlHdmiCECDeviceState_t    DeviceState;
} tmdlHdmiCecInstanceSetup_t, *ptmdlHdmiCecInstanceSetup_t; 
 
 
/**
 * \brief The structure of a CEC Data Register Protocol
*/
typedef struct
{
  UInt8 AddressByte;
  Bool  MessageTypePolling;       /* Indicate if it's a poolling message "1" or a normal CEC message "0" */
  UInt8 Opcode;
}tmdlHdmiCecSaveMessage_t;

typedef struct
{
  UInt8 FrameByteCount;  
  UInt8 AddressByte;
  UInt8 DataBytes[15];
}tmdlHdmiCecFrameFormat_t;



#ifdef __cplusplus
}
#endif

#endif /* TMDLHDMICEC_TYPES_H */

/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/

