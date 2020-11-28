/*==========================================================================*/
/*     (Copyright (C) 2003 Koninklijke Philips Electronics N.V.             */
/*     All rights reserved.                                                 */
/*     This source code and any compilation or derivative thereof is the    */
/*     proprietary information of Koninklijke Philips Electronics N.V.      */
/*     and is confidential in nature.                                       */
/*     Under no circumstances is this software to be exposed to or placed   */
/*     under an Open Source License of any type without the expressed       */
/*     written permission of Koninklijke Philips Electronics N.V.           */
/*==========================================================================*/
//-----------------------------------------------------------------------------
// MoReUse - 2001-11-12  Continuus Version 16
//
// Added
//   CID_COMP_TRICK
//   CID_COMP_TODISK
//   CID_COMP_FROMDISK
// 
// Removed
// CID_COMP_RTC  Twice the same request - duplicate removed          
//
// (C) Copyright 2000-2001 Koninklijke Philips Electronics N.V.,
//     All rights reserved
//
// This source code and any compilation or derivative thereof is the sole
// property of Philips Corporation and is provided pursuant to a Software
// License Agreement.  This code is the proprietary information of Philips
// Corporation and is confidential in nature.  Its use and dissemination by
// any party other than Philips Corporation is strictly limited by the
// confidential information provisions of the Agreement referenced above.
//-----------------------------------------------------------------------------
// FILE NAME:    tmCompId.h
//
// DESCRIPTION:  This header file identifies the standard component identifiers
//               for DVP platforms.  The objective of DVP component IDs is to
//               enable unique identification of software components at all
//               classes, types, and layers.  In addition, standard status
//               values are also defined to make determination of typical error
//               cases much easier.  The component identifier bitfields are
//               four bit aligned to ease in reading the hexadecimal value.
//
//               The process to create a new component ID follows the sequence
//               of steps:
//
//               1) Select a component class:  The class is the most general
//                  component classification.  If none of the classifications
//                  match and the component can still be uniquely identified
//                  by its type/tag/layer combination, use CID_CLASS_NONE.
//                  For customers, the CID_CLASS_CUSTOMER value is defined.
//                  If that value is used in the CID_CLASS_BITMASK field,
//                  all other bits in the component ID are user defined.
//
//               2) Select a component type:   The component type is used to
//                  classify how a component processes data.  Components may
//                  have only output pins (source), only input pins (sink),
//                  input and output pins with or without data modifications
//                  (filter), control of data flow without input/output pins
//                  (control), data storage/access/retrieval (database),
//                  or component group (subsystem).  If the component does
//                  not fit into any type classification, use CID_TYPE_NONE.
//
//               3) Create a component ID:     The component ID is used to
//                  classify the specific type and/or attributes of a software
//                  component API interface.  The currently defined list should
//                  be scanned for a component match.  If no component match
//                  can be found, define a new component tag that descibes the
//                  component clearly.  Component name abbreviations/acronyms
//                  are generally used; build a name starting from left to
//                  right with the most general ('A' or 'AUD' for audio, 'V' or
//                  'VID' for video, etc.) to the most specific ('AC3' or 'MP3'
//                  as specific audio filter types) terms for the component.
//
//               NOTE: Component layer (CID_LAYER_XXX) and status (CID_ERR_XXX)
//                     values are defined within the software component APIs
//                     header files, not in this file.
//
// DOCUMENT REF: DVP Software Coding Guidelines specification
//               DVP/MoReUse Naming Conventions specification
//
// NOTES:        The 32 bit component identifier bitfields are defined in the
//               diagram below:
//
//           +-----------------------------------------  4 bit Component Class
//          /      +-----------------------------------  4 bit Component Type
//         /      /         +--------------------------  8 bit Component Tag
//        /      /         /         +-----------------  4 bit Component Layer
//       /      /         /         /            +----- 12 bit Component Status
//      /      /         /         /            /
//  |31  28|27  24|23        16|15  12|11               0| bit
//  +------+------+------------+------+------------------+
//  |Class | Type |ComponentTag|Layer |  Error/Progress  |
//  +------+------+------------+------+------------------+
//
//-----------------------------------------------------------------------------
//
#ifndef TMCOMPID_H //-------------------
#define TMCOMPID_H

//-----------------------------------------------------------------------------
// Standard include files:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// Project include files:
//-----------------------------------------------------------------------------
//

#ifdef __cplusplus
extern "C"
{
#endif

//-----------------------------------------------------------------------------
// Types and defines:
//-----------------------------------------------------------------------------
//

//-----------------------------------------------------------------------------
// TM_OK is the 32 bit global status value used by all DVP software components
//  to indicate successful function/operation status.  If a non-zero value is
//  returned as status, it should use the component ID formats defined.
//
#define TM_OK               0         // Global success return status


//
// NOTE: Component ID types are defined as unsigned 32 bit integers (UInt32).
//
//-----------------------------------------------------------------------------
// Component Class definitions (bits 31:28, 4 bits)
// NOTE: A class of 0x0 must not be defined to ensure that the overall 32 bit
//       component ID/status combination is always non-0 (no TM_OK conflict).
//
#define CID_CLASS_BITSHIFT  28                          // Component class bit shift
#define CID_CLASS_BITMASK   (0xF << CID_CLASS_BITSHIFT) // Class AND bitmsk
#define CID_GET_CLASS(compId)   ((compId & CID_CLASS_BITMASK) >> CID_CLASS_BITSHIFT)
//
#define CID_CLASS_NONE      (0x1 << CID_CLASS_BITSHIFT) // No class information
#define CID_CLASS_VIDEO     (0x2 << CID_CLASS_BITSHIFT) // Video data component
#define CID_CLASS_AUDIO     (0x3 << CID_CLASS_BITSHIFT) // Audio data component
#define CID_CLASS_GRAPHICS  (0x4 << CID_CLASS_BITSHIFT) // Graphics component
#define CID_CLASS_BUS       (0x5 << CID_CLASS_BITSHIFT) // In/out/control bus
#define CID_CLASS_INFRASTR  (0x6 << CID_CLASS_BITSHIFT) // Infrastructure comp.
                            // Up to 0xE = Philips reserved class IDs
#define CID_CLASS_CUSTOMER  (0xF << CID_CLASS_BITSHIFT) // Customer rsvd class


//-----------------------------------------------------------------------------
// Component Type definitions (bits 27:24, 4 bits)
//
#define CID_TYPE_BITSHIFT   24                          // Component type bit shift
#define CID_TYPE_BITMASK    (0xF << CID_TYPE_BITSHIFT)  // Type AND bitmask
#define CID_GET_TYPE(compId)    ((compId & CID_TYPE_BITMASK) >> CID_TYPE_BITSHIFT)
//
#define CID_TYPE_NONE       (0x0 << CID_TYPE_BITSHIFT)  // No data connections
#define CID_TYPE_SOURCE     (0x1 << CID_TYPE_BITSHIFT)  // Source, output pins
#define CID_TYPE_SINK       (0x2 << CID_TYPE_BITSHIFT)  // Sink,   input pins
#define CID_TYPE_ENCODER    (0x3 << CID_TYPE_BITSHIFT)  // Data encoder
#define CID_TYPE_DECODER    (0x4 << CID_TYPE_BITSHIFT)  // Data decoder
#define CID_TYPE_MUX        (0x5 << CID_TYPE_BITSHIFT)  // Data multiplexer
#define CID_TYPE_DEMUX      (0x6 << CID_TYPE_BITSHIFT)  // Data demultiplexer
#define CID_TYPE_DIGITIZER  (0x7 << CID_TYPE_BITSHIFT)  // Data digitizer
#define CID_TYPE_RENDERER   (0x8 << CID_TYPE_BITSHIFT)  // Data renderer
#define CID_TYPE_FILTER     (0x9 << CID_TYPE_BITSHIFT)  // Data filter/processr
#define CID_TYPE_CONTROL    (0xA << CID_TYPE_BITSHIFT)  // Data control/switch
#define CID_TYPE_DATABASE   (0xB << CID_TYPE_BITSHIFT)  // Data store/access
#define CID_TYPE_SUBSYSTEM  (0xC << CID_TYPE_BITSHIFT)  // MultiComp subsystem
#define CID_TYPE_CUSTOMER   (0xF << CID_TYPE_BITSHIFT)  // Customer Defined Type
                            // Up to 0xF = Philips reserved type IDs


//-----------------------------------------------------------------------------
// Component Tag definitions (bits 23:16, 8 bits)
// NOTE: Component tags are defined in groups, dependent on the class and type.
//
#define CID_TAG_BITSHIFT    16                          // Component tag bit shift
#define CID_TAG_BITMASK     (0xFF << CID_TAG_BITSHIFT)  // Comp tag AND bitmask
//
#define CID_TAG_NONE        (0x00 << CID_TAG_BITSHIFT)  // No tag information
                            // Up to 0xFF = Philips reserved component tags
#define CID_TAG_CUSTOMER    (0xE0 << CID_TAG_BITSHIFT)

#define TAG(number)         ((number) << CID_TAG_BITSHIFT) // Create tag from num

//-----------------------------------------------------------------------------
// Component Layer definitions (bits 15:12, 4 bits)
//
#define CID_LAYER_BITSHIFT  12                           // Component layer bit shift
#define CID_LAYER_BITMASK   (0xF << CID_LAYER_BITSHIFT)  // Layer AND bitmask
#define CID_GET_LAYER(compId)   ((compId & CID_LAYER_BITMASK) >> CID_LAYER_BITSHIFT)
//
#define CID_LAYER_NONE      (0x0 << CID_LAYER_BITSHIFT)  // No layer info
#define CID_LAYER_BTM       (0x1 << CID_LAYER_BITSHIFT)  // Boot manager layer
#define CID_LAYER_HWAPI     (0x2 << CID_LAYER_BITSHIFT)  // Hardware API layer
#define CID_LAYER_BSL       (0x3 << CID_LAYER_BITSHIFT)  // Board Supp. Lib lyr
#define CID_LAYER_DEVLIB    (0x4 << CID_LAYER_BITSHIFT)  // Device Library lyr
#define CID_LAYER_TMAL      (0x5 << CID_LAYER_BITSHIFT)  // Application layer
#define CID_LAYER_TMOL      (0x6 << CID_LAYER_BITSHIFT)  // OSDependent layer
#define CID_LAYER_CUSTOMER  (0xF << CID_LAYER_BITSHIFT)  // Customer Defined Layer
                            // Up to 0xF = Philips reserved layer IDs



//-----------------------------------------------------------------------------
// Component Identifier definitions (bits 31:12, 20 bits)
// NOTE: These DVP platform component identifiers are designed to be unique
//       within the system.  The component identifier encompasses the class
//       (CID_CLASS_XXX), type (CID_TYPE_XXX), tag, and layer (CID_LAYER_XXX)
//       fields to form the unique component identifier.  This allows any
//       error/progress status value to be identified as to its original
//       source, whether or not the source component's header file is present.
//       The standard error/progress status definitions should be used
//       whenever possible to ease status interpretation.  No layer
//       information is defined at this point; it should be OR'd into the API
//       status values defined in the API's header file.
//
#if     (CID_LAYER_NONE != 0)
#error  ERROR: DVP component identifiers require the layer type 'NONE' = 0 !
#endif

//
// Classless Types/Components (don't fit into other class categories)
//
#define CTYP_NOCLASS_NOTYPE     (CID_CLASS_NONE | CID_TYPE_NONE)
#define CTYP_NOCLASS_SOURCE     (CID_CLASS_NONE | CID_TYPE_SOURCE)
#define CTYP_NOCLASS_SINK       (CID_CLASS_NONE | CID_TYPE_SINK)
#define CTYP_NOCLASS_MUX        (CID_CLASS_NONE | CID_TYPE_MUX)
#define CTYP_NOCLASS_DEMUX      (CID_CLASS_NONE | CID_TYPE_DEMUX)
#define CTYP_NOCLASS_FILTER     (CID_CLASS_NONE | CID_TYPE_FILTER)
#define CTYP_NOCLASS_CONTROL    (CID_CLASS_NONE | CID_TYPE_CONTROL)
#define CTYP_NOCLASS_DATABASE   (CID_CLASS_NONE | CID_TYPE_DATABASE)
#define CTYP_NOCLASS_SUBSYS     (CID_CLASS_NONE | CID_TYPE_SUBSYSTEM)
//
#define CID_COMP_CLOCK          (TAG(0x01) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_DMA            (TAG(0x02) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_PIC            (TAG(0x03) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_NORFLASH       (TAG(0x04) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_NANDFLASH      (TAG(0x05) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_GPIO           (TAG(0x06) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_SMARTCARD      (TAG(0x07) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_UDMA           (TAG(0x08) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_DSP            (TAG(0x09) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_TIMER          (TAG(0x0A) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_TSDMA          (TAG(0x0B) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_MMIARB         (TAG(0x0C) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_EEPROM         (TAG(0x0D) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_PARPORT        (TAG(0x0E) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_VSS            (TAG(0x0F) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_TSIO           (TAG(0x10) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_DBG            (TAG(0x11) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_TTE            (TAG(0x12) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_AVPROP         (TAG(0x13) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_BLASTER        (TAG(0x14) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_CAPTURE        (TAG(0x15) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_STP            (TAG(0x16) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_SYN            (TAG(0x17) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_TTX            (TAG(0x18) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_MIU            (TAG(0x19) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_INTDRV         (TAG(0x1A) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_RESET          (TAG(0x1B) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_CONFIG         (TAG(0x1C) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_VCTRL          (TAG(0x1D) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_TUNER          (TAG(0x1E) | CTYP_NOCLASS_NOTYPE)
#define CID_COMP_DEMOD          (TAG(0x1F) | CTYP_NOCLASS_NOTYPE)


#define CID_COMP_FREAD          (TAG(0x01) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_CDRREAD        (TAG(0x02) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_VSB            (TAG(0x03) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_ANALOGTVTUNER  (TAG(0x04) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_TPINMPEG2      (TAG(0x05) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_DREAD          (TAG(0x06) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_TREAD          (TAG(0x07) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_RTC            (TAG(0x08) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_TOUCHC         (TAG(0x09) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_KEYPAD         (TAG(0x0A) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_ADC            (TAG(0x0B) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_READLIST       (TAG(0x0C) | CTYP_NOCLASS_SOURCE)
#define CID_COMP_FROMDISK       (TAG(0x0D) | CTYP_NOCLASS_SOURCE)

#define CID_COMP_FWRITE         (TAG(0x01) | CTYP_NOCLASS_SINK)
#define CID_COMP_CDWRITE        (TAG(0x02) | CTYP_NOCLASS_SINK)
#define CID_COMP_CHARLCD        (TAG(0x03) | CTYP_NOCLASS_SINK)
#define CID_COMP_PWM            (TAG(0x04) | CTYP_NOCLASS_SINK)
#define CID_COMP_DAC            (TAG(0x05) | CTYP_NOCLASS_SINK)
#define CID_COMP_TSDMAINJECTOR  (TAG(0x06) | CTYP_NOCLASS_SINK)
#define CID_COMP_TODISK         (TAG(0x07) | CTYP_NOCLASS_SINK)

#define CID_COMP_MUXMPEGPS      (TAG(0x01) | CTYP_NOCLASS_MUX)
#define CID_COMP_MUXMPEG        (TAG(0x02) | CTYP_NOCLASS_MUX)

#define CID_COMP_DEMUXMPEGTS    (TAG(0x01) | CTYP_NOCLASS_DEMUX)
#define CID_COMP_DEMUXMPEGPS    (TAG(0x02) | CTYP_NOCLASS_DEMUX)

#define CID_COMP_COPYIO         (TAG(0x01) | CTYP_NOCLASS_FILTER)
#define CID_COMP_COPYINPLACE    (TAG(0x02) | CTYP_NOCLASS_FILTER)
#define CID_COMP_UART           (TAG(0x03) | CTYP_NOCLASS_FILTER)
#define CID_COMP_SSI            (TAG(0x04) | CTYP_NOCLASS_FILTER)
#define CID_COMP_MODEMV34       (TAG(0x05) | CTYP_NOCLASS_FILTER)
#define CID_COMP_MODEMV42       (TAG(0x06) | CTYP_NOCLASS_FILTER)
#define CID_COMP_HTMLPARSER     (TAG(0x07) | CTYP_NOCLASS_FILTER)
#define CID_COMP_VMSP           (TAG(0x08) | CTYP_NOCLASS_FILTER)
#define CID_COMP_X              (TAG(0x09) | CTYP_NOCLASS_FILTER)
#define CID_COMP_TXTSUBTDECEBU  (TAG(0x0A) | CTYP_NOCLASS_FILTER)
#define CID_COMP_CPI            (TAG(0x0B) | CTYP_NOCLASS_FILTER)
#define CID_COMP_TRICK          (TAG(0x0C) | CTYP_NOCLASS_FILTER)

#define CID_COMP_REMCTL5        (TAG(0x01) | CTYP_NOCLASS_CONTROL)
#define CID_COMP_INFRARED       (TAG(0x02) | CTYP_NOCLASS_CONTROL)

#define CID_COMP_PSIP           (TAG(0x01) | CTYP_NOCLASS_DATABASE)
#define CID_COMP_IDE            (TAG(0x02) | CTYP_NOCLASS_DATABASE)
#define CID_COMP_DISKSCHED      (TAG(0x03) | CTYP_NOCLASS_DATABASE)
#define CID_COMP_AVFS           (TAG(0x04) | CTYP_NOCLASS_DATABASE)
#define CID_COMP_MDB            (TAG(0x05) | CTYP_NOCLASS_DATABASE)

#define CID_COMP_IRDMMPEG       (TAG(0x01) | CTYP_NOCLASS_SUBSYS)
#define CID_COMP_STORSYS        (TAG(0x02) | CTYP_NOCLASS_SUBSYS)

//
// Video Class Types/Components (video types handle video/graphics data)
//
#define CTYP_VIDEO_SINK         (CID_CLASS_VIDEO | CID_TYPE_SINK)
#define CTYP_VIDEO_SOURCE       (CID_CLASS_VIDEO | CID_TYPE_SOURCE)
#define CTYP_VIDEO_ENCODER      (CID_CLASS_VIDEO | CID_TYPE_ENCODER)
#define CTYP_VIDEO_DECODER      (CID_CLASS_VIDEO | CID_TYPE_DECODER)
#define CTYP_VIDEO_DIGITIZER    (CID_CLASS_VIDEO | CID_TYPE_DIGITIZER)
#define CTYP_VIDEO_RENDERER     (CID_CLASS_VIDEO | CID_TYPE_RENDERER)
#define CTYP_VIDEO_FILTER       (CID_CLASS_VIDEO | CID_TYPE_FILTER)
#define CTYP_VIDEO_SUBSYS       (CID_CLASS_VIDEO | CID_TYPE_SUBSYSTEM)
//
#define CID_COMP_LCD            (TAG(0x01) | CTYP_VIDEO_SINK)

#define CID_COMP_VCAPVI         (TAG(0x01) | CTYP_VIDEO_SOURCE)
#define CID_COMP_VIP            (TAG(0x02) | CTYP_VIDEO_SOURCE)
#define CID_COMP_VI             (TAG(0x03) | CTYP_VIDEO_SOURCE)
#define CID_COMP_VSLICER        (TAG(0x04) | CTYP_VIDEO_SOURCE)
#define CID_COMP_FBREAD         (TAG(0x05) | CTYP_VIDEO_SOURCE)
#define CID_COMP_QVI            (TAG(0x06) | CTYP_VIDEO_SOURCE)
#define CID_COMP_CAMERA         (TAG(0x07) | CTYP_VIDEO_SOURCE)

#define CID_COMP_VENCM1         (TAG(0x01) | CTYP_VIDEO_ENCODER)
#define CID_COMP_VENCM2         (TAG(0x02) | CTYP_VIDEO_ENCODER)
#define CID_COMP_VENCMJ         (TAG(0x03) | CTYP_VIDEO_ENCODER)
#define CID_COMP_VENCH263       (TAG(0x04) | CTYP_VIDEO_ENCODER)
#define CID_COMP_VENCH261       (TAG(0x05) | CTYP_VIDEO_ENCODER)

#define CID_COMP_VDECM1         (TAG(0x01) | CTYP_VIDEO_DECODER)
#define CID_COMP_VDECM2         (TAG(0x02) | CTYP_VIDEO_DECODER)
#define CID_COMP_VDECMPEG       (TAG(0x03) | CTYP_VIDEO_DECODER)
#define CID_COMP_VDECMJ         (TAG(0x04) | CTYP_VIDEO_DECODER)
#define CID_COMP_VDECSUBPICSVCD (TAG(0x05) | CTYP_VIDEO_DECODER)
#define CID_COMP_VDECH263       (TAG(0x06) | CTYP_VIDEO_DECODER)
#define CID_COMP_VDECH261       (TAG(0x07) | CTYP_VIDEO_DECODER)
#define CID_COMP_VDEC           (TAG(0x08) | CTYP_VIDEO_DECODER)
#define CID_COMP_VDECSUBPICDVD  (TAG(0x09) | CTYP_VIDEO_DECODER)
#define CID_COMP_VDECSUBPICBMPDVD  (TAG(0x0A) | CTYP_VIDEO_DECODER)
#define CID_COMP_VDECSUBPICRENDDVD (TAG(0x0B) | CTYP_VIDEO_DECODER)
#define CID_COMP_M4PP           (TAG(0x0C) | CTYP_VIDEO_DECODER)
#define CID_COMP_M4MC           (TAG(0x0D) | CTYP_VIDEO_DECODER)
#define CID_COMP_M4CSC          (TAG(0x0E) | CTYP_VIDEO_DECODER)

#define CID_COMP_VDIG           (TAG(0x01) | CTYP_VIDEO_DIGITIZER)
#define CID_COMP_VDIGVIRAW      (TAG(0x02) | CTYP_VIDEO_DIGITIZER)

#define CID_COMP_VREND          (TAG(0x01) | CTYP_VIDEO_RENDERER)
#define CID_COMP_HDVO           (TAG(0x02) | CTYP_VIDEO_RENDERER)
#define CID_COMP_VRENDGFXVO     (TAG(0x03) | CTYP_VIDEO_RENDERER)
#define CID_COMP_AICP           (TAG(0x04) | CTYP_VIDEO_RENDERER)
#define CID_COMP_VRENDVORAW     (TAG(0x05) | CTYP_VIDEO_RENDERER)
#define CID_COMP_VO             (TAG(0x06) | CTYP_VIDEO_RENDERER)
#define CID_COMP_QVO            (TAG(0x06) | CTYP_VIDEO_RENDERER)
#define CID_COMP_VRENDVOICP     (TAG(0x07) | CTYP_VIDEO_RENDERER)
#define CID_COMP_VMIX           (TAG(0x08) | CTYP_VIDEO_RENDERER)
#define CID_COMP_GFX           (TAG(0x09) | CTYP_VIDEO_RENDERER)

#define CID_COMP_MBS            (TAG(0x01) | CTYP_VIDEO_FILTER)
#define CID_COMP_VTRANS         (TAG(0x02) | CTYP_VIDEO_FILTER)
#define CID_COMP_QNM            (TAG(0x03) | CTYP_VIDEO_FILTER)
#define CID_COMP_ICP            (TAG(0x04) | CTYP_VIDEO_FILTER)
#define CID_COMP_VTRANSNM       (TAG(0x05) | CTYP_VIDEO_FILTER)
#define CID_COMP_QFD            (TAG(0x06) | CTYP_VIDEO_FILTER) // film detector
#define CID_COMP_VRENDDVDVO     (TAG(0x07) | CTYP_VIDEO_FILTER)
#define CID_COMP_VTRANSCRYSTAL  (TAG(0x08) | CTYP_VIDEO_FILTER)

#define CID_COMP_VSYSMT3        (TAG(0x01) | CTYP_VIDEO_SUBSYS) //obsolescent
#define CID_COMP_VSYSSTB        (TAG(0x01) | CTYP_VIDEO_SUBSYS)
#define CID_COMP_DVDVIDSYS      (TAG(0x02) | CTYP_VIDEO_SUBSYS)
#define CID_COMP_VDECUD         (TAG(0x03) | CTYP_VIDEO_SUBSYS)
#define CID_COMP_VIDSYS         (TAG(0x04) | CTYP_VIDEO_SUBSYS)
//
// Audio Class Types/Components (audio types primarily handle audio data)
//
#define CTYP_AUDIO_NONE         (CID_CLASS_AUDIO | CID_TYPE_NONE)
#define CTYP_AUDIO_SINK         (CID_CLASS_AUDIO | CID_TYPE_SINK)
#define CTYP_AUDIO_SOURCE       (CID_CLASS_AUDIO | CID_TYPE_SOURCE)
#define CTYP_AUDIO_ENCODER      (CID_CLASS_AUDIO | CID_TYPE_ENCODER)
#define CTYP_AUDIO_DECODER      (CID_CLASS_AUDIO | CID_TYPE_DECODER)
#define CTYP_AUDIO_DIGITIZER    (CID_CLASS_AUDIO | CID_TYPE_DIGITIZER)
#define CTYP_AUDIO_RENDERER     (CID_CLASS_AUDIO | CID_TYPE_RENDERER)
#define CTYP_AUDIO_FILTER       (CID_CLASS_AUDIO | CID_TYPE_FILTER)
#define CTYP_AUDIO_SUBSYS       (CID_CLASS_AUDIO | CID_TYPE_SUBSYSTEM)
//

#define CID_COMP_AI             (TAG(0x01) | CTYP_AUDIO_NONE)
#define CID_COMP_AO             (TAG(0x03) | CTYP_AUDIO_NONE)
#define CID_COMP_ADAI           (TAG(0x04) | CTYP_AUDIO_NONE)

#define CID_COMP_SDAC           (TAG(0x01) | CTYP_AUDIO_SINK)

#define CID_COMP_ADIGAI         (TAG(0x01) | CTYP_AUDIO_DIGITIZER)
#define CID_COMP_ADIGSPDIF      (TAG(0x02) | CTYP_AUDIO_DIGITIZER)

#define CID_COMP_ARENDAO        (TAG(0x01) | CTYP_AUDIO_RENDERER)
#define CID_COMP_ARENDSPDIF     (TAG(0x02) | CTYP_AUDIO_RENDERER)

#define CID_COMP_NOISESEQ       (TAG(0x03) | CTYP_AUDIO_SOURCE)

#define CID_COMP_AENCAC3        (TAG(0x01) | CTYP_AUDIO_ENCODER)
#define CID_COMP_AENCMPEG1      (TAG(0x02) | CTYP_AUDIO_ENCODER)
#define CID_COMP_AENCAAC        (TAG(0x03) | CTYP_AUDIO_ENCODER)
#define CID_COMP_AENCG723       (TAG(0x04) | CTYP_AUDIO_ENCODER)
#define CID_COMP_AENCG728       (TAG(0x05) | CTYP_AUDIO_ENCODER)
#define CID_COMP_AENCWMA        (TAG(0x06) | CTYP_AUDIO_ENCODER)

#define CID_COMP_ADECPROLOGIC   (TAG(0x01) | CTYP_AUDIO_DECODER)
#define CID_COMP_ADECAC3        (TAG(0x02) | CTYP_AUDIO_DECODER)
#define CID_COMP_ADECMPEG1      (TAG(0x03) | CTYP_AUDIO_DECODER)
#define CID_COMP_ADECMP3        (TAG(0x04) | CTYP_AUDIO_DECODER)
#define CID_COMP_ADECAAC        (TAG(0x05) | CTYP_AUDIO_DECODER)
#define CID_COMP_ADECG723       (TAG(0x06) | CTYP_AUDIO_DECODER)
#define CID_COMP_ADECG728       (TAG(0x07) | CTYP_AUDIO_DECODER)
#define CID_COMP_ADECWMA        (TAG(0x08) | CTYP_AUDIO_DECODER)
#define CID_COMP_ADECTHRU       (TAG(0x09) | CTYP_AUDIO_DECODER)
#define CID_COMP_ADEC           (TAG(0x0A) | CTYP_AUDIO_DECODER)

#define CID_COMP_ASPLIB         (TAG(0x01) | CTYP_AUDIO_FILTER)
#define CID_COMP_IIR            (TAG(0x02) | CTYP_AUDIO_FILTER)
#define CID_COMP_ASPEQ2         (TAG(0x03) | CTYP_AUDIO_FILTER)
#define CID_COMP_ASPEQ5         (TAG(0x04) | CTYP_AUDIO_FILTER)
#define CID_COMP_ASPBASSREDIR   (TAG(0x05) | CTYP_AUDIO_FILTER)
#define CID_COMP_ASPLAT2        (TAG(0x06) | CTYP_AUDIO_FILTER)
#define CID_COMP_ASPPLUGIN      (TAG(0x07) | CTYP_AUDIO_FILTER)
#define CID_COMP_AMIXDTV        (TAG(0x08) | CTYP_AUDIO_FILTER)
#define CID_COMP_AMIXSIMPLE     (TAG(0x09) | CTYP_AUDIO_FILTER)
#define CID_COMP_AMIXSTB        (TAG(0x0A) | CTYP_AUDIO_FILTER)
#define CID_COMP_ASPEQ          (TAG(0x0B) | CTYP_AUDIO_FILTER)
#define CID_COMP_ATESTSIG       (TAG(0x0C) | CTYP_AUDIO_FILTER)

#define CID_COMP_AUDSUBSYS      (TAG(0x01) | CTYP_AUDIO_SUBSYS)
#define CID_COMP_AUDSYSSTB      (TAG(0x02) | CTYP_AUDIO_SUBSYS)
#define CID_COMP_AUDSYSDVD      (TAG(0x03) | CTYP_AUDIO_SUBSYS)

//
// Graphics Class Types/Components
//
#define CTYP_GRAPHICS_RENDERER  (CID_CLASS_GRAPHICS | CID_TYPE_SINK)
//
#define CID_COMP_WM             (TAG(0x01) | CTYP_GRAPHICS_RENDERER)
#define CID_COMP_WIDGET         (TAG(0x02) | CTYP_GRAPHICS_RENDERER)
#define CID_COMP_OM             (TAG(0x03) | CTYP_GRAPHICS_RENDERER)
#define CID_COMP_HTMLRENDER     (TAG(0x04) | CTYP_GRAPHICS_RENDERER)
#define CID_COMP_VRENDEIA708    (TAG(0x05) | CTYP_GRAPHICS_RENDERER)
#define CID_COMP_VRENDEIA608    (TAG(0x06) | CTYP_GRAPHICS_RENDERER)
//
#define CTYP_GRAPHICS_DRAW      (CID_CLASS_GRAPHICS | CID_TYPE_NONE)
//
#define CID_COMP_DRAW           (TAG(0x10) | CTYP_GRAPHICS_DRAW)
#define CID_COMP_DRAW_UT        (TAG(0x11) | CTYP_GRAPHICS_DRAW)
#define CID_COMP_DRAW_DE        (TAG(0x12) | CTYP_GRAPHICS_DRAW)
#define CID_COMP_DRAW_REF       (TAG(0x13) | CTYP_GRAPHICS_DRAW)
#define CID_COMP_DRAW_TMH       (TAG(0x14) | CTYP_GRAPHICS_DRAW)
#define CID_COMP_DRAW_TMT       (TAG(0x15) | CTYP_GRAPHICS_DRAW)
#define CID_COMP_DRAW_TMTH      (TAG(0x16) | CTYP_GRAPHICS_DRAW)
//
#define CID_COMP_3D             (TAG(0x30) | CTYP_GRAPHICS_DRAW)
#define CID_COMP_JAWT           (TAG(0x31) | CTYP_GRAPHICS_DRAW)
#define CID_COMP_JINPUT         (TAG(0x32) | CTYP_GRAPHICS_DRAW)
#define CID_COMP_LWM            (TAG(0x33) | CTYP_GRAPHICS_DRAW)
#define CID_COMP_2D             (TAG(0x34) | CTYP_GRAPHICS_DRAW)


//
// Bus Class Types/Components (busses connect hardware components together)
//
#define CTYP_BUS_NOTYPE         (CID_CLASS_BUS | CID_TYPE_NONE)
//
#define CID_COMP_XIO            (TAG(0x01) | CTYP_BUS_NOTYPE)
#define CID_COMP_IIC            (TAG(0x02) | CTYP_BUS_NOTYPE)
#define CID_COMP_PCI            (TAG(0x03) | CTYP_BUS_NOTYPE)
#define CID_COMP_P1394          (TAG(0x04) | CTYP_BUS_NOTYPE)
#define CID_COMP_ENET           (TAG(0x05) | CTYP_BUS_NOTYPE)
#define CID_COMP_ATA            (TAG(0x06) | CTYP_BUS_NOTYPE)
#define CID_COMP_CAN            (TAG(0x07) | CTYP_BUS_NOTYPE)
#define CID_COMP_UCGDMA         (TAG(0x08) | CTYP_BUS_NOTYPE)
#define CID_COMP_I2S            (TAG(0x09) | CTYP_BUS_NOTYPE)
#define CID_COMP_SPI            (TAG(0x0A) | CTYP_BUS_NOTYPE)
#define CID_COMP_PCM            (TAG(0x0B) | CTYP_BUS_NOTYPE)
#define CID_COMP_L3             (TAG(0x0C) | CTYP_BUS_NOTYPE)

//
// Infrastructure Class Types/Components
#define CTYP_INFRASTR_NOTYPE    (CID_CLASS_INFRASTR | CID_TYPE_NONE)
//
#define CID_COMP_OSAL           (TAG(0x01) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_MML            (TAG(0x02) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_TSSA_DEFAULTS  (TAG(0x03) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_RPC            (TAG(0x04) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_THI            (TAG(0x05) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_REGISTRY       (TAG(0x06) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_TMMAN          (TAG(0x07) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_LDT            (TAG(0x08) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_CPUCONN        (TAG(0x09) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_COMMQUE        (TAG(0x0A) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_BSLMGR         (TAG(0x0B) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_CR             (TAG(0x0C) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_NODE           (TAG(0x0D) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_COM            (TAG(0x0E) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_UTIL           (TAG(0x0F) | CTYP_INFRASTR_NOTYPE)
#define CID_COMP_SGLIST         (TAG(0x10) | CTYP_INFRASTR_NOTYPE)

//-----------------------------------------------------------------------------
// Component Standard Error/Progress Status definitions (bits 11:0, 12 bits)
// NOTE: These status codes are OR'd with the component identifier to create
//       component unique 32 bit status values.  The component status values
//       should be defined in the header files where the APIs are defined.
//
#define CID_ERR_BITMASK                 0xFFF // Component error AND bitmask
#define CID_ERR_BITSHIFT                0     // Component error bit shift
#define CID_GET_ERROR(compId)   ((compId & CID_ERR_BITMASK) >> CID_ERR_BITSHIFT)
//
#define TM_ERR_COMPATIBILITY            0x001 // SW Interface compatibility
#define TM_ERR_MAJOR_VERSION            0x002 // SW Major Version error
#define TM_ERR_COMP_VERSION             0x003 // SW component version error
#define TM_ERR_BAD_MODULE_ID            0x004 // SW - HW module ID error
#ifndef TM_ERR_BAD_UNIT_NUMBER         
#define TM_ERR_BAD_UNIT_NUMBER          0x005 // Invalid device unit number
#endif
#define TM_ERR_BAD_INSTANCE             0x006 // Bad input instance value
#define TM_ERR_BAD_HANDLE               0x007 // Bad input handle
#define TM_ERR_BAD_INDEX                0x008 // Bad input index
#ifndef TM_ERR_BAD_PARAMETER           
#define TM_ERR_BAD_PARAMETER            0x009 // Invalid input parameter
#endif
#define TM_ERR_NO_INSTANCES             0x00A // No instances available
#define TM_ERR_NO_COMPONENT             0x00B // Component is not present
#define TM_ERR_NO_RESOURCES             0x00C // Resource is not available
#define TM_ERR_INSTANCE_IN_USE          0x00D // Instance is already in use
#define TM_ERR_RESOURCE_OWNED           0x00E // Resource is already in use
#define TM_ERR_RESOURCE_NOT_OWNED       0x00F // Caller does not own resource
#define TM_ERR_INCONSISTENT_PARAMS      0x010 // Inconsistent input params
#ifndef TM_ERR_NOT_INITIALIZED        
#define TM_ERR_NOT_INITIALIZED          0x011 // Component is not initialized
#endif
#define TM_ERR_NOT_ENABLED              0x012 // Component is not enabled
#ifndef TM_ERR_NOT_SUPPORTED         
#define TM_ERR_NOT_SUPPORTED            0x013 // Function is not supported
#endif
#define TM_ERR_INIT_FAILED              0x014 // Initialization failed
#define TM_ERR_BUSY                     0x015 // Component is busy
#define TM_ERR_NOT_BUSY                 0x016 // Component is not busy
#define TM_ERR_READ                     0x017 // Read error
#define TM_ERR_WRITE                    0x018 // Write error
#define TM_ERR_ERASE                    0x019 // Erase error
#define TM_ERR_LOCK                     0x01A // Lock error
#define TM_ERR_UNLOCK                   0x01B // Unlock error
#define TM_ERR_OUT_OF_MEMORY            0x01C // Memory allocation failed
#define TM_ERR_BAD_VIRT_ADDRESS         0x01D // Bad virtual address
#define TM_ERR_BAD_PHYS_ADDRESS         0x01E // Bad physical address
#define TM_ERR_TIMEOUT                  0x01F // Timeout error
#define TM_ERR_OVERFLOW                 0x020 // Data overflow/overrun error
#define TM_ERR_FULL                     0x021 // Queue (etc.) is full
#define TM_ERR_EMPTY                    0x022 // Queue (etc.) is empty
#define TM_ERR_NOT_STARTED              0x023 // Component stream not started
#define TM_ERR_ALREADY_STARTED          0x024 // Comp. stream already started
#define TM_ERR_NOT_STOPPED              0x025 // Component stream not stopped
#define TM_ERR_ALREADY_STOPPED          0x026 // Comp. stream already stopped
#define TM_ERR_ALREADY_SETUP            0x027 // Component already setup
#define TM_ERR_NULL_PARAMETER           0x028 // Null input parameter
#define TM_ERR_NULL_DATAINFUNC          0x029 // Null data input function
#define TM_ERR_NULL_DATAOUTFUNC         0x02A // Null data output function
#define TM_ERR_NULL_CONTROLFUNC         0x02B // Null control function
#define TM_ERR_NULL_COMPLETIONFUNC      0x02C // Null completion function
#define TM_ERR_NULL_PROGRESSFUNC        0x02D // Null progress function
#define TM_ERR_NULL_ERRORFUNC           0x02E // Null error handler function
#define TM_ERR_NULL_MEMALLOCFUNC        0x02F // Null memory alloc function
#define TM_ERR_NULL_MEMFREEFUNC         0x030 // Null memory free  function
#define TM_ERR_NULL_CONFIGFUNC          0x031 // Null configuration function
#define TM_ERR_NULL_PARENT              0x032 // Null parent data
#define TM_ERR_NULL_IODESC              0x033 // Null in/out descriptor
#define TM_ERR_NULL_CTRLDESC            0x034 // Null control descriptor
#define TM_ERR_UNSUPPORTED_DATACLASS    0x035 // Unsupported data class
#define TM_ERR_UNSUPPORTED_DATATYPE     0x036 // Unsupported data type
#define TM_ERR_UNSUPPORTED_DATASUBTYPE  0x037 // Unsupported data subtype
#define TM_ERR_FORMAT                   0x038 // Invalid/unsupported format
#define TM_ERR_INPUT_DESC_FLAGS         0x039 // Bad input  descriptor flags
#define TM_ERR_OUTPUT_DESC_FLAGS        0x03A // Bad output descriptor flags
#define TM_ERR_CAP_REQUIRED             0x03B // Capabilities required ???
#define TM_ERR_BAD_TMALFUNC_TABLE       0x03C // Bad TMAL function table
#define TM_ERR_INVALID_CHANNEL_ID       0x03D // Invalid channel identifier
#define TM_ERR_INVALID_COMMAND          0x03E // Invalid command/request
#define TM_ERR_STREAM_MODE_CONFUSION    0x03F // Stream mode config conflict
#define TM_ERR_UNDERRUN                 0x040 // Data underflow/underrun
#define TM_ERR_EMPTY_PACKET_RECVD       0x041 // Empty data packet received
#define TM_ERR_OTHER_DATAINOUT_ERR      0x042 // Other data input/output err
#define TM_ERR_STOP_REQUESTED           0x043 // Stop in progress
#define TM_ERR_PIN_NOT_STARTED          0x044 // Pin not started
#define TM_ERR_PIN_ALREADY_STARTED      0x045 // Pin already started
#define TM_ERR_PIN_NOT_STOPPED          0x046 // Pin not stopped
#define TM_ERR_PIN_ALREADY_STOPPED      0x047 // Pin already stopped
#define TM_ERR_STOP_PIN_REQUESTED       0x048 // Stop of a single pin is in progress (obsolescent)
#define TM_ERR_PAUSE_PIN_REQUESTED      0x048 // Stop of a single pin is in progress
#define TM_ERR_ASSERTION                0x049 // Assertion failure
#define TM_ERR_HIGHWAY_BANDWIDTH        0x04A // Highway bandwidth bus error
#define TM_ERR_HW_RESET_FAILED          0x04B // Hardware reset failed
#define TM_ERR_PIN_PAUSED               0x04C // Pin Paused

// Add new standard error/progress status codes here

#define TM_ERR_COMP_UNIQUE_START        0x800 // 0x800-0xDFF: Component unique

#define TM_ERR_CUSTOMER_START           0xC00  

// DVP Standard assert error code start offset
// NOTE: This define should be added to the component's base error value and
//       standard error code(s) to define assert error codes.  For example:
// #define TMBSL_ERR_MGR_ASSERT_BAD_PARAM 
//          (TMBSL_ERR_MGR_BASE + TM_ERR_ASSERT_START + TM_ERR_BAD_PARAMETER)
//
#define TM_ERR_ASSERT_START             0xE00 // 0xE00-0xEFF: Assert failures
#define TM_ERR_ASSERT_LAST              0xEFF // Last assert error range value
#define CID_IS_ASSERT_ERROR(compId)     \
    ((CID_GET_ERROR(compId) >= TM_ERR_ASSERT_START) && \
     (CID_GET_ERROR(compId) <= TM_ERR_ASSERT_LAST))

// DVP Standard fatal error code start offset
// NOTE: This define should be added to the component's base error value and
//       standard error code(s) to define fatal error codes.  For example:
// #define TMML_ERR_FATAL_OUT_OF_MEMORY  
//          (TMML_ERR_BASE + TM_ERR_FATAL_START + TM_ERR_OUT_OF_MEMORY)
//
#define TM_ERR_FATAL_START              0xF00 // 0xF00-0xFFF: Fatal failures
#define TM_ERR_FATAL_LAST               0xFFF // Last fatal error range value
#define CID_IS_FATAL_ERROR(compId)      \
    ((CID_GET_ERROR(compId) >= TM_ERR_FATAL_START) && \
     (CID_GET_ERROR(compId) <= TM_ERR_FATAL_LAST))


//-----------------------------------------------------------------------------
// DVP hardware module IDs
//
#define VMPG_100_MOD_ID         0x00000100
#define C1394_101_MOD_ID        0x00000101
#define FPBC_102_MOD_ID         0x00000102
#define JTAG_103_MOD_ID         0x00000103
#define EJTAG_104_MOD_ID        0x00000104
#define IIC_105_MOD_ID          0x00000105
#define SMCARD_106_MOD_ID       0x00000106
#define UART_107_MOD_ID         0x00000107
/* #define CLOCKS_108_MOD_ID       0x00000108 */
#define USB_109_MOD_ID          0x00000109
#define BOOT_10A_MOD_ID         0x0000010A
#define MPBC_10B_MOD_ID         0x0000010B
#define SSI_10C_MOD_ID          0x0000010C
#define AI_10D_MOD_ID           0x0000010D
#define VMSP_10E_MOD_ID         0x0000010E
#define GPIO_10F_MOD_ID         0x0000010F
#define SPDI_110_MOD_ID         0x00000110
#define AICP_111_MOD_ID         0x00000111
#define TPBC_112_MOD_ID         0x00000112
#define PCI_113_MOD_ID          0x00000113
#define MMI_114_MOD_ID          0x00000114
#define ORCA3_115_MOD_ID        0x00000115
#define DBG_116_MOD_ID          0x00000116
#define DE_117_MOD_ID           0x00000117
#define AICP_118_MOD_ID         0x00000118
#define MBS_119_MOD_ID          0x00000119
#define VIP_11A_MOD_ID          0x0000011A
#define PIMI_11B_MOD_ID         0x0000011B
#define PIB_11C_MOD_ID          0x0000011C
#define PIC_11D_MOD_ID          0x0000011D
#define TMDBG_11F_MOD_ID        0x0000011F
#define AO_120_MOD_ID           0x00000120
#define SPDO_121_MOD_ID         0x00000121
#define FPIMI_122_MOD_ID        0x00000122
#define RESET_123_MOD_ID        0x00000123
#define NULL_124_MOD_ID         0x00000124
#define TSDMA_125_MOD_ID        0x00000125
#define GLBREG_126_MOD_ID       0x00000126
#define TMDBG_127_MOD_ID        0x00000127
#define GLBREG_128_MOD_ID       0x00000128
#define DMA_130_MOD_ID          0x00000130
#define IR_131_MOD_ID           0x00000131
#define GFX2D_131_MOD_ID        0x00000132 // TODO: Remove after code corrected
#define GFX2D_132_MOD_ID        0x00000132
#define P1284_133_MOD_ID        0x00000133
#define QNM_134_MOD_ID          0x00000134
#define OSD_136_MOD_ID            0x00000136
#define MIX_137_MOD_ID            0x00000137
#define DENC_138_MOD_ID            0x00000138
#define SYN_13A_MOD_ID            0x0000013A
#define CLOCKS_13E_MOD_ID       0x0000013E
#define CONFIG_13F_MOD_ID       0x0000013F
#define MIU_A04C_MOD_ID            0x0000A04C
#define DISP_A04D_MOD_ID        0x0000A04D
#define VCTRL_A04E_MOD_ID       0x0000A04E


#define PR3930_2B10_MOD_ID      0x00002B10
#define PR3940_2B11_MOD_ID      0x00002B11

#define TM3218_2B80_MOD_ID      0x00002B80
#define TM64_2b81_MOD_ID        0x00002B81

#define QNM_A017_MOD_ID         0x0000A017

// There is no HW module ID for TS IO ROUTER.  We assign
// a SW module ID to this module, because it is needed by Clock 
// device and HWAPI libraries. Use 010Eh for lower word 
// (for lack of better reason ! because IO Router is closely
// associated with VMSP module)

#define IORT_1010E_MOD_ID       0x0001010E


#ifdef __cplusplus
}
#endif

#endif // TMCOMPID_H //-----------------

