//=============================================================================
// Copyright (C) 2007 NXP N.V., All Rights Reserved.
// This source code and any compilation or derivative thereof is the proprietary
// information of NXP N.V. and is confidential in nature. Under no circumstances
// is this software to be  exposed to or placed under an Open Source License of
// any type without the expressed written permission of NXP N.V.
//=============================================================================
/*!
    \file    tmdlHdmiCEC_Functions.h

	\version 1.0

	\date    04/07/2007

 	\brief   This provides interfaces description of CEC messages.

    \section refs  Reference Documents
             TDA998X Driver - tmdlHdmiCec - SCS.doc
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

#ifndef TMDLHDMICEC_FUNCTIONS_H
#define TMDLHDMICEC_FUNCTIONS_H

/*============================================================================*/
/*                       INCLUDE FILES                                        */
/*============================================================================*/

#include "hdmitx/sde2/inc/tmNxTypes.h"
#ifdef __cplusplus
extern "C" {
#endif


/*============================================================================*/
/*                       PUBLIC FUNCTION DECLARATION                          */
/*============================================================================*/

//==========================================================================
/*!
    \brief This message is reserved for testing purposes

    \param tmInstance_t Instance \n
           Instance identifier. \n

	\param UInt8 ReceiverLogicalAddress\n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecAbortMessage
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is used by a new source to indicate that it has started
           to transmit a stream OR used in reponse to a <Request Active Source>

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt16 PhysicalAddress \n
           Physical address of the device.\n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecActiveSource
(
   tmInstance_t   Instance,
   UInt16         PhysicalAddress
);

//==========================================================================
/*!
    \brief This message is used to indicate the supported CEC version in response
           to a <Get CEC Version>

    \param tmInstance_t Instance \n
           Instance identifier. \n
		 
	\param UInt8 ReceiverLogicalAddress\n
           Address of message receiver. \n

    \param tmdlHdmiCECVersion_t CECVersion \n
           Supported CEC Version.\n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecVersion
(
   tmInstance_t         Instance,
   UInt8                ReceiverLogicalAddress,
   tmdlHdmiCECVersion_t CECVersion
);

//==========================================================================
/*!
    \brief This message is used to clear an Analogue timer block of a device

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n
           
    \param UInt8  DayOfMonth \n
           Day of the month.\n
    
    \param UInt8  MonthOfYear \n
           Month of the year.\n
           
    \param UInt16 StartTime \n
           Start time for a timer based recording.\n
           
    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n
    
    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n
    
    \param tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType \n
           "Cable,Sattellite,Terrestrial".\n 
           
    \param UInt16 AnalogueFrequency \n
           Specify frequency used by analogue tuner (0x0000<=N<=0xFFFF).\n
    
    \param tmdlHdmiCECBroadcastSystem_t BroadcastSystem \n
           Specify information about the colour system, the sound carrier and
           the IF-frequency.\n
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecClearAnalogueTimer
(
   tmInstance_t                        Instance,
   UInt8                               ReceiverLogicalAddress,
   UInt8                               DayOfMonth,
   UInt8                               MonthOfYear,
   UInt16                              StartTime,
   tmdlHdmiCECDuration_t              *pDuration,
   UInt8                               RecordingSequence,
   tmdlHdmiCECAnalogueBroadcastType_t  AnalogueBroadcastType,
   UInt16                              AnalogueFrequency,
   tmdlHdmiCECBroadcastSystem_t        BroadcastSystem
);


//==========================================================================
/*!
    \brief This message is used to clear a digital timer block of a device

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n
           
    \param UInt8  DayOfMonth \n
           Day of the month.\n
    
    \param UInt8  MonthOfYear \n
           Month of the year.\n
           
    \param UInt16 StartTime \n
           Start time for a timer based recording.\n
           
    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n
    
    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n
    
    \param tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification \n
           Pointer to the structure Digital Service Identification

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecClearDigitalTimer
(
   tmInstance_t                               Instance,
   UInt8                                      ReceiverLogicalAddress,
   UInt8                                      DayOfMonth,
   UInt8                                      MonthOfYear,
   UInt16                                     StartTime,
   tmdlHdmiCECDuration_t                     *pDuration,
   UInt8                                      RecordingSequence,
   tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification
);

//==========================================================================
/*!
    \brief This message is used to clear a digital timer block of a device

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n
           
    \param UInt8  DayOfMonth \n
           Day of the month.\n
    
    \param UInt8  MonthOfYear \n
           Month of the year.\n
           
    \param UInt16 StartTime \n
           Start time for a timer based recording.\n
           
    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n
    
    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n
    
    \param tmdlHdmiCECExternalPlug_t  ExternalPlug \n
           indicates external plug number (1 to 255 )on the recording device.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecClearExternalTimerWithExternalPlug
(
   tmInstance_t                Instance,
   UInt8                       ReceiverLogicalAddress,
   UInt8                       DayOfMonth,
   UInt8                       MonthOfYear,
   UInt16                      StartTime,
   tmdlHdmiCECDuration_t      *pDuration,
   UInt8                       RecordingSequence,
   tmdlHdmiCECExternalPlug_t  ExternalPlug
);

//==========================================================================
/*!
    \brief This message is used to clear a digital timer block of a device

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n
           
    \param UInt8  DayOfMonth \n
           Day of the month.\n
    
    \param UInt8  MonthOfYear \n
           Month of the year.\n
           
    \param UInt16 StartTime \n
           Start time for a timer based recording.\n
           
    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n
    
    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n
    
    \param tmdlHdmiCECExternalPhysicalAddress_t  PhysicalAddress \n
           Defines the path between the TV an a device-thus giving it a physical
           address within the cluster.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecClearExternalTimerWithPhysicalAddress
(
   tmInstance_t                           Instance,
   UInt8                                  ReceiverLogicalAddress,
   UInt8                                  DayOfMonth,
   UInt8                                  MonthOfYear,
   UInt16                                 StartTime,
   tmdlHdmiCECDuration_t                 *pDuration,
   UInt8                                  RecordingSequence,
   tmdlHdmiCECExternalPhysicalAddress_t  ExternalPhysicalAddress
);

//==========================================================================
/*!
    \brief This message is used to conrol a device's media functions

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECDecControlMode_t DeckControlMode \n
           Used in message <Deck Control>\n
    
    \note  The "Skip Forward / Wind" and "Skip Reverse / Rewind" values are
           used for example in a DVD as next xhapter and previous chapter and
           in a VCR as wind and rewind. \n
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecDeckControl
(
   tmInstance_t                Instance,
   UInt8                       ReceiverLogicalAddress,
   tmdlHdmiCECDecControlMode_t DeckControlMode
);

//==========================================================================
/*!
    \brief This message is used to provide a deck's status to the initiator
           of the <Give Deck Status> message 

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECDecInfo_t DeckInfo \n
           Information on the device's current status \n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecDeckStatus
(
   tmInstance_t         Instance,
   UInt8                ReceiverLogicalAddress,
   tmdlHdmiCECDecInfo_t DeckInfo
);

//==========================================================================
/*!
    \brief This message report the vendor ID of this device

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt32 VendorID \n
           Indentifier for a specific Vendor \n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecDeviceVendorID
(
   tmInstance_t Instance,
   UInt32       VendorID
);

//==========================================================================
/*!
    \brief This message is used as a reponse to indicate that the device does
           not support the requested message type, or that it cannot execute it
           at the present time.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECFeatureOpcode_t FeatureOpcode \n
           Opcode of the aborted message. \n
    
    \param tmdlHdmiCECAbortReason_t   AbortReason \n
           The reason why message cannot respond. \n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecFeatureAbort
(
   tmInstance_t               Instance,
   UInt8                      ReceiverLogicalAddress,
   tmdlHdmiCECFeatureOpcode_t FeatureOpcode,
   tmdlHdmiCECAbortReason_t   AbortReason
);

//==========================================================================
/*!
    \brief This message is used by a device to enquire which version of CEC
           the target supports

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetCecVersion
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is sent by a device capable of character generation
           (for OSD and Menus) to a TV in order to discover the currently selected
           Menu Language. Also used by a TV during installation to dicover the
           currently set menu language of other devices.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetMenuLanguage
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is requests an amplifier to send its volume and mute status

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveAudioStatus
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is used to request the status of a device regardless
           of whether or not it is the current active source.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECStatusRequest_t StatusRequest \n
           Allows the initiator to request the status once or on all future state
           change. Or to cancel a previous <Give Deck Status > ["On"] request. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveDeckStatus
(
   tmInstance_t               Instance,
   UInt8                      ReceiverLogicalAddress,
   tmdlHdmiCECStatusRequest_t StatusRequest
);

//==========================================================================
/*!
    \brief This message is used to determine the current power status of a 
           target device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveDevicePowerStatus
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is request the vendor ID from a device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveDeviceVendorID
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is used to request preferred OSD name of a device
           for use in menus associated with that device

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveOsdName
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is a request to a device to return its physical Address

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGivePhysicalAddress
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message request the status of the system audio mode

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveSystemAudioModeStatus
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is used to request the status of a tuner device
    
    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECStatusRequest_t StatusRequest \n
           Allows the initiator to request the status once or on all future state
           change. Or to cancel a previous <Give Tuner Device Status > ["On"] request. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGiveTunerDeviceStatus
(
   tmInstance_t               Instance,
   UInt8                      ReceiverLogicalAddress,
   tmdlHdmiCECStatusRequest_t StatusRequest
);

//==========================================================================
/*!
    \brief This message sent by a source device to the TV whenever it enters
           the active state

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receivers. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecImageViewOn
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is used by the currently active source to inform the
           TV that it has no video to be presented to the user, or is going
           into standby as the result of a lcoal user command on the device.
    
    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8 ReceiverLogicalAddress, \n
           Address of message receiver. \n
           
    \param tmdlHdmiCECExternalPhysicalAddress_t  PhysicalAddress \n
           Physical Address of the device. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecInactiveSource
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   tmdlHdmiCECExternalPhysicalAddress_t  PhysicalAddress
);

//==========================================================================
/*!
    \brief This message request from the TV for a device to show/remove a
           menu or to query if a device is currently showing a menu
    
    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECMenuRequestType_t  MenuRequestType \n
           Indicates if the menu request is to activate or deactivate the 
           devices menu or simply query the devices menu status. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecMenuRequest
(
   tmInstance_t                  Instance,
   UInt8                         ReceiverLogicalAddress,
   tmdlHdmiCECMenuRequestType_t  MenuRequestType
);

//==========================================================================
/*!
    \brief This message is used to indicate to the TV that the device is 
           showing/has removed a menu and requets the remote control keys to
           be passed though
    
    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECMenuState_t  MenuState \n
           Indicates if the device is in the 'Device Menu Active' state or
           'Device Menu Inactive' state. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecMenuStatus
(
   tmInstance_t            Instance,
   UInt8                   ReceiverLogicalAddress,
   tmdlHdmiCECMenuState_t  MenuState
);

//==========================================================================
/*!
    \brief This message is used to control the playback behaviour of a source
           device
    
    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECPlayMode_t  PlayMode \n
           In which mode to play media. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecPlay
(
   tmInstance_t           Instance,
   UInt8                  ReceiverLogicalAddress,
   tmdlHdmiCECPlayMode_t  PlayMode
);

//==========================================================================
/*!
    \brief This message is used by any device for device discovery - similar to
           ping in other protocols

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecPollingMessage
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message request a device to stop a recording

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOff
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message attempt to record analogue source

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType \n
           "Cable,Sattellite,Terrestrial".\n 
           
    \param UInt16 AnalogueFrequency \n
           Specify frequency used by analogue tuner (0x0000<=N<=0xFFFF).\n
    
    \param tmdlHdmiCECBroadcastSystem_t BroadcastSystem \n
           Specify information about the colour system, the sound carrier and
           the IF-frequency.\n       
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOnAnalogueService
(
   tmInstance_t                        Instance,
   UInt8                               ReceiverLogicalAddress,
   tmdlHdmiCECAnalogueBroadcastType_t  AnalogueBroadcastType,
   UInt16                              AnalogueFrequency,
   tmdlHdmiCECBroadcastSystem_t        BroadcastSystem
);

//==========================================================================
/*!
    \brief This message attempt to record digital source

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification \n
           Pointer to the structure Digital Service Identification
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOnDigitalService
(
   tmInstance_t                              Instance,
   UInt8                                     ReceiverLogicalAddress,
   tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification
);

//==========================================================================
/*!
    \brief This message attempt to record an external physical address source

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param tmdlHdmiCECExternalPhysicalAddress_t  PhysicalAddress \n
           Defines the path between the TV an a device-thus giving it a physical
           address within the cluster.\n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOnExternalPhysicalAddress
(
   tmInstance_t                         Instance,
   UInt8                                ReceiverLogicalAddress,
   tmdlHdmiCECExternalPhysicalAddress_t ExternalPhysicalAddress
);

//==========================================================================
/*!
    \brief This message attempt to record an external plug source

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param tmdlHdmiCECExternalPlug_t  ExternalPlug \n
           indicates external plug number (1 to 255 )on the recording device.\n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOnExternalPlug
(
   tmInstance_t                   Instance,
   UInt8                          ReceiverLogicalAddress,
   tmdlHdmiCECExternalPlug_t      ExternalPlug
);

//==========================================================================
/*!
    \brief This message attempt to record an external plug source

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordOnOwnSource
(
   tmInstance_t                   Instance,
   UInt8                          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is used by a recording device to inform the initiator
           of the message <Record On> about its status.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param tmdlHdmiCECRecordStatusInfo_t  RecordStatusInfo \n
           The recording status of the device.\n        
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordStatus
(
   tmInstance_t                   Instance,
   UInt8                          ReceiverLogicalAddress,
   tmdlHdmiCECRecordStatusInfo_t  RecordStatusInfo
);

//==========================================================================
/*!
    \brief This message request by the recording device to record the presently
           displayed source.

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRecordTvScreen
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message report an amplifier's volume and mute.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECAudioStatus_t AudioStatus \n
           Volume and mute status. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportAudioStatus
(
   tmInstance_t              Instance,
   UInt8                     ReceiverLogicalAddress,
   ptmdlHdmiCECAudioStatus_t pAudioStatus
);

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecReportShortAudioDescriptor( )
    \brief This message Report Audio Capability.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param UInt32 ShortAudioDecriptor \n
           Audio Descriptor. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportShortAudioDescriptor
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress,
   UInt32         ShortAudioDecriptor
);

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRequestShortAudioDescriptor( )
    \brief This message Request Audio Capability.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \param UInt8 AudioFormatID \n
	   
    \param UInt8 AudioFormatCode \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRequestShortAudioDescriptor
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress,
   UInt8          AudioFormatID,
   UInt8          AudioFormatCode
   
);

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecIniateARC( )
    \brief This message Used by an ARC RX device to activate the
           ARC functionality in an ARC TX device

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecIniateARC
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecReportArcInitiated( )
    \brief This message Used by an ARC TX device to indicate that
           its ARC functionality has been activated

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportArcInitiated
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecReportArcTerminated( )
    \brief This message Used by an ARC TX device to indicate that its ARC functionality
           has been deactivated.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportArcTerminated
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRequestArcInitiation( )
    \brief This message Used by an ARC TX device to request an ARC RX device to
           activate the ARC functionality in the ARC TX device.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRequestArcInitiation
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecRequestArcTerminiation( )
    \brief Used by an ARC TX device to request an ARC RX device to deactivate 
           the ARC functionality in the ARC TX device.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRequestArcTerminiation
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecTerminateARC( )
    \brief Used by an ARC TX device to request an ARC RX device to deactivate 
           the ARC functionality in the ARC TX device.

    \param tmInstance_t Instance \n
           Instance identifier. \n
	   
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTerminateARC
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is used to inform all other devices of the mapping
           between physical and logical address of the initiator.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt16 PhysicalAddress \n
           Device physical address within the cluster. \n
           
    \param tmdlHdmiCECDeviceType_t DeviceType \n
           Type of the device (TV, Playback, tuner,...). \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportPhysicalAddress
(
   tmInstance_t             Instance,
   UInt16                   PhysicalAddress,
   tmdlHdmiCECDeviceType_t  DeviceType
);

//==========================================================================
/*!
    \brief This message is used to inform a requesting device of the current
           power status.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECPowerStatus_t PowerStatus \n
           Current power status. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecReportPowerStatus
(
   tmInstance_t             Instance,
   UInt8                    ReceiverLogicalAddress,
   tmdlHdmiCECPowerStatus_t PowerStatus
);

//==========================================================================
/*!
    \brief This message is used by a new device to discover the status of
           the system.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRequestActiveSource
(
   tmInstance_t  Instance
);

//==========================================================================
/*!
    \brief This message is sent by a CEC switch when it is manually switched to 
           inform all other devices on the network that the active route below
           the switch has changed.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt16 OriginalAddress \n
           Previous address that the switch was switched to. \n
           
    \param UInt16 NewAddress \n
           The new address it has been moved to. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRoutingChange
(
   tmInstance_t  Instance,
   UInt16        OriginalAddress,
   UInt16        NewAddress
);

//==========================================================================
/*!
    \brief This message is sent by a CEC switch to indicate the active route
           below the switch.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt16 PhysicalAddress \n
           The current active route to the sink in the CEC switch. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRoutingInformation
(
   tmInstance_t  Instance,
   UInt16        PhysicalAddress
);

//==========================================================================
/*!
    \brief This message select directly an analogue TV Service.

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType \n
           "Cable,Sattellite,Terrestrial".\n 
           
    \param UInt16 AnalogueFrequency \n
           Specify frequency used by analogue tuner (0x0000<=N<=0xFFFF).\n
    
    \param tmdlHdmiCECBroadcastSystem_t BroadcastSystem \n
           Specify information about the colour system, the sound carrier and
           the IF-frequency.\n
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSelectAnalogueService
(
   tmInstance_t                       Instance,
   UInt8                              ReceiverLogicalAddress,
   tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType,
   UInt16                             AnalogueFrequency,
   tmdlHdmiCECBroadcastSystem_t       BroadcastSystem
);

//==========================================================================
/*!
    \brief This message select directly a digital TV, Radio or Data Broadcast
           Service.

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification \n
           Pointer to the structure Digital Service Identification
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSelectDigitalService
(
   tmInstance_t                                Instance,
   UInt8                                       ReceiverLogicalAddress,
   ptmdlHdmiCECDigitalServiceIdentification_t  pServiceIdentification
);

//==========================================================================
/*!
    \brief This message is used to set asingle timer block on an analogue 
           recording device.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n
           
    \param UInt8  DayOfMonth \n
           Day of the month.\n
    
    \param UInt8  MonthOfYear \n
           Month of the year.\n
           
    \param UInt16 StartTime \n
           Start time for a timer based recording.\n
           
    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n
    
    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n
    
    \param tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType \n
           "Cable,Sattellite,Terrestrial".\n 
           
    \param UInt16 AnalogueFrequency \n
           Specify frequency used by analogue tuner (0x0000<=N<=0xFFFF).\n
    
    \param tmdlHdmiCECBroadcastSystem_t BroadcastSystem \n
           Specify information about the colour system, the sound carrier and
           the IF-frequency.\n
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetAnalogueTimer
(
   tmInstance_t                        Instance,
   UInt8                               ReceiverLogicalAddress,
   UInt8                               DayOfMonth,
   UInt8                               MonthOfYear,
   UInt16                              StartTime,
   tmdlHdmiCECDuration_t              *pDuration,
   UInt8                               RecordingSequence,
   tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType,
   UInt16                              AnalogueFrequency,
   tmdlHdmiCECBroadcastSystem_t       BroadcastSystem
);

//==========================================================================
/*!
    \brief This message is used to control audio rate from Source device.

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param tmdlHdmiCECAudioRate_t AudioRate \n
           The audio rate requested. \n
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetAudioRate
(
   tmInstance_t           Instance,
   UInt8                  ReceiverLogicalAddress,
   tmdlHdmiCECAudioRate_t AudioRate
);

//==========================================================================
/*!
    \brief This message is used to set a digital timer block on a digital
           recording device

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8 ReceiverLogicalAddress \n
           Address of message receiver. \n
           
    \param UInt8  DayOfMonth \n
           Day of the month.\n
    
    \param UInt8  MonthOfYear \n
           Month of the year.\n
           
    \param UInt16 StartTime \n
           Start time for a timer based recording.\n
           
    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n
    
    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n
    
    \param tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification \n
           Pointer to the structure Digital Service Identification

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetDigitalTimer
(
   tmInstance_t                               Instance,
    UInt8                                     ReceiverLogicalAddress,
   UInt8                                      DayOfMonth,
   UInt8                                      MonthOfYear,
   UInt16                                     StartTime,
   tmdlHdmiCECDuration_t                     *pDuration,
   UInt8                                      RecordingSequence,
   tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification
);

//==========================================================================
/*!
    \brief This message is used to set a single timer block to record from an
           external device

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8  DayOfMonth \n
           Day of the month.\n
    
    \param UInt8  MonthOfYear \n
           Month of the year.\n
           
    \param UInt16 StartTime \n
           Start time for a timer based recording.\n
           
    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n
    
    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n
    
    \param tmdlHdmiCECExternalPlug_t  ExternalPlug \n
           indicates external plug number (1 to 255 )on the recording device.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetExternalTimerWithExternalPlug
(
   tmInstance_t                Instance,
   UInt8                       ReceiverLogicalAddress,
   UInt8                       DayOfMonth,
   UInt8                       MonthOfYear,
   UInt16                      StartTime,
   tmdlHdmiCECDuration_t      *pDuration,
   UInt8                       RecordingSequence,
   tmdlHdmiCECExternalPlug_t  ExternalPlug
);

//==========================================================================
/*!
    \brief This message is used to set a single timer block to record from an
           external device

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8  DayOfMonth \n
           Day of the month.\n
    
    \param UInt8  MonthOfYear \n
           Month of the year.\n
           
    \param UInt16 StartTime \n
           Start time for a timer based recording.\n
           
    \param UInt16 Duration \n
           Pointer to the structure tmdlHdmiCECDuration_t in BCD format.\n
    
    \param UInt8 Recording Sequence \n
           Indicates if recording is repeated and, if so, on which day
           For repeated recording the recording sequence value is the
           bitwise OR of the days when recordings are required
           Shall be set to 0x00 when recording is not repeated.\n
    
    \param tmdlHdmiCECExternalPhysicalAddress_t  PhysicalAddress \n
           Defines the path between the TV an a device-thus giving it a physical
           address within the cluster.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetExternalTimerWithPhysicalAddress
(
   tmInstance_t                           Instance,
   UInt8                                  ReceiverLogicalAddress,
   UInt8                                  DayOfMonth,
   UInt8                                  MonthOfYear,
   UInt16                                 StartTime,
   tmdlHdmiCECDuration_t                 *pDuration,
   UInt8                                  RecordingSequence,
   tmdlHdmiCECExternalPhysicalAddress_t  ExternalPhysicalAddress
);

//==========================================================================
/*!
    \brief This message is used by a TV or another device to indicate the menu
           Language.

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param const char *pLanguage \n
           Pointer on the user's menu language choice. \n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetMenuLanguage
(
   tmInstance_t Instance,
   const char   *pLanguage
);

//==========================================================================
/*!
    \brief This message is used to set the preferred OSD name of a device 
           for use in manus associated with that device.

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param const char *pOsdName \n
           Pointer on the preferred name of the device. \n
           
    \param UInt8    OsdNameLength \n
           Length of Osd Name String. \n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetOsdName
(
   tmInstance_t Instance,
   UInt8        ReceiverLogicalAddress,
   const char   *pOsdName,
   UInt8        OsdNameLength
);

//==========================================================================
/*!
    \brief This message is used to send a test message to output on a TV.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECDisplayControl_t DisplayControl \n
           Display timing. \n
    
    \param const char *pOsdString \n
           Pointer on the Text to display. \n
     
    \param UInt8    OsdStringLength \n
           Length of Osd String. \n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetOsdString
(
   tmInstance_t                 Instance,
   UInt8                        ReceiverLogicalAddress,
   tmdlHdmiCECDisplayControl_t  DisplayControl,
   const char                   *pOsdString,
   UInt8                        OsdStringLength
);

//==========================================================================
/*!
    \brief This message is used by a TV to request a streaming path from
           the specified physical address.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt16 PhysicalAddress \n
           Physical address of the device.\n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetStreamPath
(
   tmInstance_t  Instance,
   UInt16        PhysicalAddress
);

//==========================================================================
/*!
    \brief This message turn the system audio Mode ON or OFF.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECSystemAudioStatus_t SystemAudioStatus \n
           Specifies if the system audio mode is ON or OFF.\n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetSystemAudioMode
(
   tmInstance_t                   Instance,
   UInt8                          ReceiverLogicalAddress,
   tmdlHdmiCECSystemAudioStatus_t SystemAudioStatus
);

//==========================================================================
/*!
    \brief This message is used to set the name of a program associated
           with a timer block.Sent directly after sending a 
           <Set analogue Timer> or <Set Digital Timer> message. The name
           is then associated with that timer block.

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n
    
    \param const char *pProgramTitleString \n
           Pointer on the program title. \n
           
    \param UInt8    ProgramTitleLength \n
           Length of Program Title String. \n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetTimerProgramTitle
(
   tmInstance_t Instance,
   UInt8        ReceiverLogicalAddress,
   const char   *pProgramTitleString,
   UInt8        ProgramTitleLength
);

//==========================================================================
/*!
    \brief This message switches one or all devices into standby mode.Can be
           be used as a broadcast message o be addressed to a specific device.

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecStandby
(
   tmInstance_t Instance,
   UInt8        ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief A device implementing System Audio Control and which has volume
           control RC button(eg TV or STB) request to use System Audio Mode
           to the amplifier.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt16 PhysicalAddress \n
           Physical address of the device.\n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSystemAudioModeRequest
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress,
   UInt16        PhysicalAddress
);

//==========================================================================
/*!
    \brief Reports the current status of the System Audio Mode.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECSystemAudioStatus_t SystemAudioStatus \n
           Current system audio mode.\n
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSystemAudioModeStatus
(
   tmInstance_t                   Instance,
   UInt8                          ReceiverLogicalAddress,
   tmdlHdmiCECSystemAudioStatus_t SystemAudioStatus
);

//==========================================================================
/*!
    \brief This message as <Image View On>, but should also remove any text,
           menus and PIP windows from the TV's display

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8    ReceiverLogicalAddress \n
           Address of message receiver. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTextViewOn
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is used to give the status of a <Cleared Analogue Timer>,
           <Clear Digital Timer> or <Clear External Timer> message.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECTimerClearedStatusData_t TimerClearedStatusData \n
           Indicates if the timer was cleared successfully. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTimerClearedStatus
(
   tmInstance_t                        Instance,
   UInt8                               ReceiverLogicalAddress,
   tmdlHdmiCECTimerClearedStatusData_t TimerClearedStatusData
);

//==========================================================================
/*!
    \brief This message is used to send timer status to the initiator of a
           <Set Timer> message.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECTimerStatusData_t *pTimerStatusData \n
           Pointer on the Timer status. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTimerStatus
(
   tmInstance_t                 Instance,
   UInt8                        ReceiverLogicalAddress,
   tmdlHdmiCECTimerStatusData_t *pTimerStatusData
);

//==========================================================================
/*!
    \brief This message is used by a tuner device to provide its status to the
           initiator of the <Give Tuner Device Status> message.

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param tmdlHdmiCECRecordingFlag_t RecordingFlag \n
           Indicates if the tuner is being used as a source of a recording. \n
           
    \param tmdlHdmiCECTunerDisplayInfo_t TunerDisplayInfo \n
           Indicates if the the device is currently deplaying its tuner or not. \n
           
    \param tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType \n
           "Cable,Sattellite,Terrestrial".\n 
           
    \param UInt16 AnalogueFrequency \n
           Specify frequency used by analogue tuner (0x0000<=N<=0xFFFF).\n
    
    \param tmdlHdmiCECBroadcastSystem_t BroadcastSystem \n
           Specify information about the colour system, the sound carrier and
           the IF-frequency.\n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTunerDeviceStatusAnalogue
(
   tmInstance_t                       Instance,
   UInt8                              ReceiverLogicalAddress,
   tmdlHdmiCECRecordingFlag_t         RecordingFlag,
   tmdlHdmiCECTunerDisplayInfo_t      TunerDisplayInfo,
   tmdlHdmiCECAnalogueBroadcastType_t AnalogueBroadcastType,
   UInt16                             AnalogueFrequency,
   tmdlHdmiCECBroadcastSystem_t       BroadcastSystem
);

//==========================================================================
/*!
    \brief This message is used by a tuner device to provide its status to the
           initiator of the <Give Tuner Device Status> message.

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param tmdlHdmiCECRecordingFlag_t RecordingFlag \n
           Indicates if the tuner is being used as a source of a recording. \n
           
    \param tmdlHdmiCECTunerDisplayInfo_t TunerDisplayInfo \n
           Indicates if the the device is currently deplaying its tuner or not. \n
           
    \param tmdlHdmiCECDigitalServiceIdentification_t *pServiceIdentification \n
           Pointer to the structure Digital Service Identification

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTunerDeviceStatusDigital
(
   tmInstance_t                               Instance,
   UInt8                                      ReceiverLogicalAddress,
   tmdlHdmiCECRecordingFlag_t                 RecordingFlag,
   tmdlHdmiCECTunerDisplayInfo_t              TunerDisplayInfo,
   ptmdlHdmiCECDigitalServiceIdentification_t pServiceIdentification
);

//==========================================================================
/*!
    \brief This message is used to tune to next lowest service in a tuner's
           service list.Can be used for PIP.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTunerStepDecrement
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is used to tune to next highest service in a tuner's
           service list.Can be used for PIP.

    \param tmInstance_t Instance \n
           Instance identifier. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecTunerStepIncrement
(
   tmInstance_t   Instance,
   UInt8          ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECUserRemoteControlCommand_t UICommand \n
           Relevant UI command issued by user. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressed
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   tmdlHdmiCECUserRemoteControlCommand_t UICommand
);

//==========================================================================
/*!
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECPlayMode_t PlayMode \n
           In which mode to play media. \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressedPlay
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   tmdlHdmiCECPlayMode_t                 PlayMode
);

//==========================================================================
/*!
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8 SelectAudioInput \n
           Number of the Audio Input (Audio input number between 1 and 255). \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressedSelectAudioInput
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   UInt8                                 SelectAudioInput
);

//==========================================================================
/*!
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8 SelectAVInput \n
           Number of the A/V Input (A/V input number between 1 and 255). \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressedSelectAVInput
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   UInt8                                 SelectAVInput
);

//==========================================================================
/*!
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8 SelectMedia \n
           Number of Media (Media number between 1 and 255). \n

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressedSelectMedia
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   UInt8                                 SelectMedia
);

//==========================================================================
/*!
    \brief This message is used to indicate that the user pressed a remote button
           or switched from one remote control button to another.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param tmdlHdmiCECChannelIdentifier_t  *pChannelIdentifier \n
           Pointer to the structure of Major and Minor Channel number

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlPressedTune
(
   tmInstance_t                          Instance,
   UInt8                                 ReceiverLogicalAddress,
   tmdlHdmiCECChannelIdentifier_t        *pChannelIdentifier
);

//==========================================================================
/*!
    \brief This message is used to indicate that the user released a remote button
           The last one indicated by the <User Control Pressed> Message.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecUserControlReleased
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief This message is allows vendor specific commands to be sent between 
           two devices.

    \param tmInstance_t Instance \n
           Instance identifier. \n
    
    \param UInt8  *pVendorSpecificData \n
           Pointer to the Vendor Specific datas
           
    \param UInt8    VendorSpecificDataLength \n
           Length of VendorSpecificData. \n
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecVendorCommand
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress,
   UInt8         *pVendorSpecificData,
   UInt8         VendorSpecificDataLength
);

//==========================================================================
/*!
    \brief This message is allows vendor specific commands to be sent between 
           two devices or broadcast.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt32 VendorID \n
           Indentifier for a specific Vendor \n
    
    \param UInt8  *pVendorSpecificData \n
           Pointer to the Vendor Specific datas
           
    \param UInt8    VendorSpecificDataLength \n
           Length of VendorSpecificData. \n
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecVendorCommandWithID
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress,
   UInt32        VendorID,
   UInt8         *pVendorSpecificData,
   UInt8         VendorSpecificDataLength
);

//==========================================================================
/*!
    \brief This message indicates that a remote control button has been depressed.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \param UInt8  *pVendorSpecificRcCode \n
           Pointer to the Vendor Specific remote control code.
           its recommended t keep this to a minimum size.
           The maximum length shall not exceed 14 data blocks to avoid saturating bus
           
    \param UInt8    VendorSpecificRcCodeLength \n
           Length of VendorSpecificRcCode. \n
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecVendorRemoteButtonDown
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress,
   UInt8         *pVendorSpecificRcCode,
   UInt8         VendorSpecificRcCodeLength
);

//==========================================================================
/*!
    \brief This message indicates that a remote control button (the last button
           pressed indicated by the <Vendor remote button down > message) has 
           been released.

    \param tmInstance_t Instance \n
           Instance identifier. \n
           
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecVendorRemoteButtonUp
(
   tmInstance_t  Instance,
   UInt8         ReceiverLogicalAddress
);

//==========================================================================
/*!
    \brief Get the software version of the driver.
           This function is synchronous.
           This function is ISR friendly.

    \param pSWVersion Pointer to the version structure

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetSWVersion
(
    tmSWVersion_t  *pSWVersion
);

//==========================================================================
/*!
    \brief Get the number of available CEC devices in the system.
           A unit directly represents a physical device.
           This function is synchronous.
           This function is ISR friendly.

    \param pUnitCount Pointer to the number of available units.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetNumberOfUnits
(
    UInt32  *pUnitCount
);

//==========================================================================
/*!
    \brief Get the capabilities of unit 0. Capabilities are stored into a
           dedicated structure.
           This function is synchronous.
           This function is not ISR friendly.

    \param pCapabilities Pointer to the capabilities structure.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_UNIT_NUMBER: the unit number is wrong or
              the receiver instance is not initialised
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetCapabilities
(
    tmdlHdmiCecCapabilities_t *pCapabilities
);

//==========================================================================
/*!
    \brief Get the capabilities of a specific unit. Capabilities are stored
           into a dedicated structure 
           This function is synchronous.
           This function is not ISR friendly.

    \param unit          Unit to be probed.
    \param pCapabilities Pointer to the capabilities structure.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_UNIT_NUMBER: the unit number is wrong or
              the receiver instance is not initialised
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetCapabilitiesM
(
    tmUnitSelect_t            unit,
    tmdlHdmiCecCapabilities_t *pCapabilities
);

//==========================================================================
/*!
    \brief Open unit 0 of CEC driver and provides the instance number to
           the caller. Note that one unit of CEC represents one physical
           CEC device and that only one instance per unit can be opened.
           This function is synchronous.
           This function is not ISR friendly.

    \param pInstance Pointer to the variable that will receive the instance
                     identifier.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_UNIT_NUMBER: the unit number is wrong or
              the receiver instance is not initialised
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_OWNED: the resource is already in use
            - TMDL_ERR_DLHDMICEC_INIT_FAILED: the unit instance is already
              initialised or something wrong happened at lower level.
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
            - TMDL_ERR_DLHDMICEC_NO_RESOURCES: the resource is not available
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecOpen
(
    tmInstance_t   *pInstance
);

//==========================================================================
/*!
    \brief Open a specific unit of CEC driver and provides the instance
           number to the caller. Note that one unit of CEC represents one
           physical CEC device and that only one instance per unit can be
           opened.
           This function is synchronous.
           This function is not ISR friendly.

    \param pInstance Pointer to the structure that will receive the instance
                     identifier.
    \param unit      Unit number to be opened.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_UNIT_NUMBER: the unit number is wrong or
              the receiver instance is not initialised
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_OWNED: the resource is already in use
            - TMDL_ERR_DLHDMICEC_INIT_FAILED: the unit instance is already
              initialised or something wrong happened at lower level.
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
            - TMDL_ERR_DLHDMICEC_NO_RESOURCES: the resource is not available
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecOpenM
(
    tmInstance_t   *pInstance,
    tmUnitSelect_t  unit
);

//==========================================================================
/*!
    \brief Close an instance of CEC driver.
           This function is synchronous.
           This function is not ISR friendly.

    \param instance Instance identifier.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecClose
(
    tmInstance_t   instance
);

//==========================================================================
/*!
    \brief Set the power state of an instance of the CEC device. ON
           state corresponds to a fully supplied, up and running device. Other
           modes correspond to the powerdown state of the device.
           This function is synchronous.
           This function is not ISR friendly.


    \param instance   Instance identifier.
    \param powerState Power state to set.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetPowerState
(
    tmInstance_t   instance,
    tmPowerState_t powerState
);

//==========================================================================
/*!
    \brief Get the power state of an instance of the CEC device. ON
           state corresponds to a fully supplied, up and running device. Other
           modes correspond to the powerdown state of the device.
           This function is synchronous.
           This function is not ISR friendly.

    \param instance    Instance identifier.
    \param pPowerState Pointer to the power state.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetPowerState
(
    tmInstance_t    instance,
    tmPowerState_t *pPowerState
);

//==========================================================================
/*!
    \brief Set the configuration of instance attributes. This function is
           required by DVP architecture rules but actually does nothing in this
           driver
           This function is synchronous.
           This function is ISR friendly.

    \param instance    Instance identifier.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecInstanceConfig
(
    tmInstance_t    instance
);

//==========================================================================
/*!
    \brief Setup the instance with its configuration parameters. This function
           allows basic instance configuration like Logical Address or device
           state.
           This function is synchronous.
           This function is not ISR friendly.

    \param instance   Instance identifier.
    \param pSetupInfo Pointer to the structure containing all setup parameters

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecInstanceSetup
(
    tmInstance_t                instance,
    ptmdlHdmiCecInstanceSetup_t pSetupInfo
);

//==========================================================================
/*!
    \brief Get instance setup parameters.

    \param instance   Instance identifier.
    \param pSetupInfo Pointer to the structure that will receive setup
                      parameters
                      This function is synchronous.
                      This function is not ISR friendly.


    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_INCONSISTENT_PARAMS: an input parameter is
              inconsistent
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecGetInstanceSetup
(
    tmInstance_t                instance,
    ptmdlHdmiCecInstanceSetup_t pSetupInfo
);

//==========================================================================
/*!
    \brief Make device library handle an incoming interrupt. This function is
           used by application to tell the device library that the hardware
           sent an interrupt. It can also be used to poll the interrupt status
           of the device if the interrupt line is not physically connected to
           the CPU.
           This function is synchronous.
           This function is ISR friendly.


    \param instance   Instance identifier.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_HANDLE: the handle number is wrong
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_FULL: the queue is full
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecHandleInterrupt
(
    tmInstance_t    instance
);

//==========================================================================
/*!
    \brief Register event callbacks. Only one callback is registered through
           this API. This callback will received the type of event that
           occured throug a dedicated parameter and will be called as many
           times as there is pending events.
           This function is synchronous.
           This function is ISR friendly.

    \param instance   Instance identifier.
    \param pCallback  Pointer to the callback function that will handle events
                      from the devlib.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
            - TMDL_ERR_DLHDMICEC_INVALID_STATE: the state is invalid for
              the function
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecRegisterCallbacks
(
    tmInstance_t                instance,
    ptmdlHdmiCecCallbackFunc_t  pkCallback
);

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetLogicalAddress( )
    \brief Set Device Logical Address

    \param instance Instance identifier.
    \param LogicalAddress Logical Address value.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetLogicalAddress
(
    tmInstance_t   instance,
	tmdlHdmiCECLogicalAddress_t   LogicalAddress
);

//==========================================================================
/*!
    \fn tmErrorCode_t tmdlHdmiCecSetRetry( )
    \brief Change the number of retransmission

    \param instance Instance identifier.
    \param NbRetry Number of retry.

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSetRetry
(
    tmInstance_t   instance,
	UInt8   NbRetry
);


//==========================================================================
/*!
    \fn tmErrorCode_t getCecLastMessage( )
    \brief Return the Addresses and the Opcode of the last CEC
	       transmitted message

    \param pSaveMessage   Pointer to the CEC Save Message

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource

*/
//==========================================================================
tmErrorCode_t getCecLastMessage
(
    tmdlHdmiCecSaveMessage_t  *pSaveMessage
);


//==========================================================================
/*!
    \brief This function allows enabling a specific event of devlib.
           This function is synchronous.
           This function is not ISR friendly.

    \param instance Instance identifier.
    \param event    Event to enable

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecEnableEvent
(
    tmInstance_t      instance,
    tmdlHdmiCecEvent_t event
);

//==========================================================================
/*!
    \brief This function allows disabling a specific event of devlib.
           This function is synchronous.
           This function is not ISR friendly.

    \param instance Instance identifier.
    \param event    Event to disable

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecDisableEvent
(
    tmInstance_t      instance,
    tmdlHdmiCecEvent_t event
);


//==========================================================================
/*!
    \brief This function enables calibration depending on CEC clock source
           This function is synchronous.
           This function is not ISR friendly.

    \param instance          Instance identifier.
    \param cecClockSource    CEC clock source

    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_BAD_PARAMETER: a parameter is invalid or out
              of range
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecEnableCalibration
(
   tmInstance_t instance,
   tmdlHdmiCecClockSource_t cecClockSource
);


//==========================================================================
/*!
    \brief This function disable calibration depending on CEC clock source
           This function is synchronous.
           This function is not ISR friendly.

    \param instance          Instance identifier.
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecDisableCalibration(
   tmInstance_t instance
);

//==========================================================================
/*!
    \brief This function allow to send a generic CEC message
           This function has to be used when CEC messages are construct in 
	   the middleware

    \param instance  Instance identifier.
    
    \param *pData    Pointer to the CEC data buffer 
    
    \param lenData   Lenght of I2C data buffer
    
    \return The call result:
            - TM_OK: the call was successful
            - TMDL_ERR_DLHDMICEC_BAD_INSTANCE: the instance number is wrong or
              out of range
            - TMDL_ERR_DLHDMICEC_RESOURCE_NOT_OWNED: the caller does not own
              the resource
*/
//==========================================================================
tmErrorCode_t tmdlHdmiCecSendMessage(

   tmInstance_t instance,
   UInt8        *pData,
   UInt16       lenData
);

unsigned char tmdlHdmiCecGetRegister(tmInstance_t   instance, UInt32 offset);
tmErrorCode_t tmdlHdmiCecSetRegister(tmInstance_t  instance,UInt32 offset,UInt32 value);



#ifdef __cplusplus
}
#endif

#endif /* TMDLHDMICEC_FUNCTIONS_H */

/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/

