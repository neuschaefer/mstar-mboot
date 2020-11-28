//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

#ifndef LIB_DRVHOSTLIB3__H
#define  LIB_DRVHOSTLIB3__H

typedef unsigned char   UINT8;     // 1 byte
/// data type unsigned short, data length 2 byte
typedef unsigned short  UINT16;    // 2 bytes
/// data type unsigned int, data length 4 byte
typedef unsigned int    UINT32;    // 4 bytes
/// data type signed char, data length 1 byte

#if 0
void memcpy (d, s, l)
unsigned char   *d;
unsigned char   *s;
unsigned int    l;
{
        while (l--) *d++ = *s++;
}
#endif
extern void USB_Write_REG32(UINT8 addr,UINT32 val);

#define USBDELAY(x)	    wait_ms(x)
//=================== 1.Condition Definition  ============================================================
//========================================================================================================

	#define Interrupt_No_FramList_Temp_Solution

    #define FUSBH200_HOST_ONLY


	#define Host20_Debug_Info	                   0x01
	#define IRQ_USB_Host20	                       40
	#define Host20_Set_Address	                   0x03

   //Host Configuration
	#define Host20_QHD_Nat_Counter                 0x00//Temp Solution from 15 to 0                //Bit28~31
	//#define Host20_EOF1Time                        0x00//For Full Speed Device
	#define Host20_EOF1Time                        0x03//For High Speed Device
#define Host20_Timeout                                  100
//=================== 2.Variable Definition  ============================================================
//========================================================================================================
    #define HOST20_OK                              0x00
    #define HOST20_FAIL                            0x01
    #define HOST20_FATAL                      0x02
    #define HOST20_DEVICE_STALL             0x03
   //****************************
   // Data Structure Allocation
   //****************************
   // 0x3000000~0x3001000  =>qHD
   // 0x3001000~0x3002000  =>qTD
   // 0x3002000~0x3003000  =>iTD
   //
   #define USB_BUFFER_START_ADR_4K_ALIGN   0



	#define Host20_STRUCTURE_BASE_ADDRESS	        0xf000//SDRAM start at 60K

//	#define Host20_STRUCTURE_qHD_BASE_ADDRESS	   ( Host20_DATA_PAGE_BASE_ADDRESS+Host20_Page_SIZE)//(DRAM=48M)
	#define Host20_qHD_SIZE	                        0x40//(48bytes), for alignment
	#define Host20_qHD_MAX	                        10//(10 )

	//#define Host20_STRUCTURE_qTD_BASE_ADDRESS	    (Host20_STRUCTURE_qHD_BASE_ADDRESS+Host20_qHD_SIZE*Host20_qHD_MAX)//(DRAM=48M)
	#define Host20_qTD_SIZE	                        0x20//(32bytes)
	#define Host20_qTD_MAX	                        0x10//(50 )





	#define Host20_MEM_TYPE_qTD               	        0x00
	#define Host20_MEM_TYPE_iTD               	        0x01
	#define Host20_MEM_TYPE_4K_BUFFER         	        0x02
	#define Host20_MEM_TYPE_siTD               	        0x03



	#define Host20_MEM_FREE         	            0x01
	#define Host20_MEM_USED         	            0x02

       #define BIT0			                 0x01
	#define BIT1			                 0x02
	#define BIT2			                 0x04
	#define BIT3			                 0x08
	#define BIT4			                 0x10
	#define BIT5			                 0x20
	#define BIT6			                 0x40
	#define BIT7			                 0x80

 #define OTGH_Dir_IN 	                         0x01
 #define OTGH_Dir_Out 	                         0x00
 #define OTGH_NULL			             0x00
 #define OTGH_ED_ISO 	                       0x01
 #define OTGH_ED_BULK 	                       0x02
 #define OTGH_ED_INT 	                       0x03
 #define OTGH_ED_Control	                   0x00
 #define OTGH_FARADAY_TEST_AP                  0x10237856
 #define OTGH_SRP_HNP_Enable                   0x03
 #define OTGH_Remote_Wake_UP                   0x00000400
 #define OTGH_Remote_Wake_UP_INT               0x00000008

unsigned char mwHost20Port3(int bOffset);
void mwHost20Portw3(int bOffset,int value);
void mwHost20Port_wr3(int bOffset, int value);
int  mwHost20Bit_Rd3(int bByte,int wBitNum);
void  mwHost20Bit_Set3(int bByte,int wBitNum);
void  mwHost20Bit_Clr3(int bByte,int wBitNum);

//=================== 2.Define Register Macro ================================================================
//========================================================================================================
	//<1>.Macro volatile
#if defined(CONFIG_URANUS4) || defined(CONFIG_KAISERIN)
	#define Host20_BASE_ADDRESS	                      0xbf220600
#elif defined(__ARM__)
    #if (ENABLE_KAISER)
    #define Host20_BASE_ADDRESS	                      0x1f220600
    #else
	#define Host20_BASE_ADDRESS	                      0x1f227200
    #endif
#else
	#define Host20_BASE_ADDRESS	                      0xbf227200
#endif
	#define mwHost20_NumPorts_Rd()		              ((mwHost20Port3(0x04)&0x0000000F)

	//<4>.0x008(HCCPARAMS - Capability Parameters)
	#define mbHost20_ProgrammableFrameListFlag_Rd()		(mwHost20Bit_Rd3(0x08,BIT1)) 	//Bit 1


	#define mbHost20_USBCMD_ParkMode_CNT_Rd()       	      ((mwHost20Port3(0x10)>>8)&0x00000003)
	#define mbHost20_USBCMD_ParkMode_CNT_Set(bValue)     	  (mwHost20Port3(0x011)=(mwHost20Port3(0x011)&0xFC)|(( (UINT8) bValue )<<8)  )	//Bit 8~9

	#define mbHost20_USBCMD_InterruptOnAsync_Rd()       	  (mwHost20Bit_Rd3(0x10,BIT6)) 	//Bit 6
	#define mbHost20_USBCMD_InterruptOnAsync_Set()     	      (mwHost20Bit_Set3(0x10,BIT6))    //Bit 6
	#define mbHost20_USBCMD_InterruptOnAsync_Clr()	          (mwHost20Bit_Clr3(0x10,BIT6))	//Bit 6

	#define mbHost20_USBCMD_AsynchronousEnable_Rd()     	  (mwHost20Bit_Rd3(0x10,BIT5))     //Bit 5
	#define mbHost20_USBCMD_AsynchronousEnable_Set()     	  (mwHost20Bit_Set3(0x10,BIT5))    //Bit 5
	#define mbHost20_USBCMD_AsynchronousEnable_Clr()	      (mwHost20Bit_Clr3(0x10,BIT5))	//Bit 5


    #define HOST20_USBCMD_FrameListSize_1024                  0x00
    #define HOST20_USBCMD_FrameListSize_512                   0x01
    #define HOST20_USBCMD_FrameListSize_256                   0x02

	#define mbHost20_USBCMD_HCReset_Rd()	                  (mwHost20Bit_Rd3(0x10,BIT1))	   //Bit 1
	#define mbHost20_USBCMD_HCReset_Set()	                  (mwHost20Bit_Set3(0x10,BIT1))   //Bit 1

	#define mbHost20_USBCMD_RunStop_Rd()	                  (mwHost20Bit_Rd3(0x10,BIT0) )  //Bit 0
	#define mbHost20_USBCMD_RunStop_Set()	                  (mwHost20Bit_Set3(0x10,BIT0))  //Bit 0
	#define mbHost20_USBCMD_RunStop_Clr()	                  (mwHost20Bit_Clr3(0x10,BIT0))  //Bit 0


	#define HOST20_Enable                  0x01
	#define HOST20_Disable                 0x00




	//<5>.0x014(USBSTS - USB Status Register)
	#define mwHost20_USBSTS_Rd()		                      (mwHost20Port3(0x14))
	#define mwHost20_USBSTS_Set(wValue)		                  mwHost20Port_wr3(0x14,wValue)

	#define mwHost20_USBSTS_AsynchronousStatus_Rd()		      (mwHost20Bit_Rd3(0x15,BIT7)) 	//14->Bit 15



	#define mwHost20_USBSTS_SystemError_Rd()		          (mwHost20Bit_Rd3(0x14,BIT4) )	//Bit 4
	#define mwHost20_USBSTS_SystemError_Set()		          (mwHost20Bit_Set3(0x14,BIT4)) 	//Bit 4


	#define mwHost20_USBSTS_PortChangeDetect_Rd()		      (mwHost20Bit_Rd3(0x14,BIT2)) 	//Bit 2
	#define mwHost20_USBSTS_PortChangeDetect_Set()		      (mwHost20Bit_Set3(0x14,BIT2)) 	//Bit 2

	#define mwHost20_USBSTS_USBError_Rd()		              (mwHost20Bit_Rd3(0x14,BIT1)) 	//Bit 1
	#define mwHost20_USBSTS_USBError_Set()		              (mwHost20Bit_Set3(0x14,BIT1)) 	//Bit 1

	#define mwHost20_USBSTS_CompletionOfTransaction_Rd()	  (mwHost20Bit_Rd3(0x14,BIT0)) 	//Bit 0
	#define mwHost20_USBSTS_CompletionOfTransaction_Set()	  (mwHost20Bit_Set3(0x14,BIT0)) 	//Bit 0

	//<6>.0x018(USBINTR - USB Interrupt Enable Register)
	#define mwHost20_USBINTR_Rd()		                      (mwHost20Port3(0x18))
	#define mwHost20_USBINTR_Set(bValue)		              mwHost20Port_wr3(0x18,bValue)

	#define mwHost20_USBINTR_IntOnAsyncAdvance_Rd()		      (mwHost20Bit_Rd3(0x18,BIT5) )	//Bit 5
	#define mwHost20_USBINTR_IntOnAsyncAdvance_Set()		  (mwHost20Bit_Set3(0x18,BIT5)) 	//Bit 5
    #define mwHost20_USBINTR_IntOnAsyncAdvance_Clr()		  (mwHost20Bit_Clr3(0x18,BIT5)) 	//Bit 5

	#define mwHost20_USBINTR_SystemError_Rd()		          (mwHost20Bit_Rd3(0x18,BIT4)) 	//Bit 4
	#define mwHost20_USBINTR_SystemError_Set()		          (mwHost20Bit_Set3(0x18,BIT4)) 	//Bit 4
	#define mwHost20_USBINTR_SystemError_Clr()		          (mwHost20Bit_Clr3(0x18,BIT4)) 	//Bit 4


	#define mwHost20_USBINTR_PortChangeDetect_Rd()		      (mwHost20Bit_Rd3(0x18,BIT2) )	//Bit 2
	#define mwHost20_USBINTR_PortChangeDetect_Set()		      (mwHost20Bit_Set3(0x18,BIT2)) 	//Bit 2
	#define mwHost20_USBINTR_PortChangeDetect_Clr()		      (mwHost20Bit_Clr3(0x18,BIT2)) 	//Bit 2

	#define mwHost20_USBINTR_USBError_Rd()		              (mwHost20Bit_Rd3(0x18,BIT1) )	//Bit 1
	#define mwHost20_USBINTR_USBError_Set()		              (mwHost20Bit_Set3(0x18,BIT1)) 	//Bit 1
	#define mwHost20_USBINTR_USBError_Clr()		              (mwHost20Bit_Clr3(0x18,BIT1)) 	//Bit 1

	#define mwHost20_USBINTR_CompletionOfTransaction_Rd()	  (mwHost20Bit_Rd3(0x18,BIT0) )	//Bit 0
	#define mwHost20_USBINTR_CompletionOfTransaction_Set()	  (mwHost20Bit_Set3(0x18,BIT0)) 	//Bit 0
	#define mwHost20_USBINTR_CompletionOfTransaction_Clr()	  (mwHost20Bit_Clr3(0x18,BIT0)) 	//Bit 0

    #define HOST20_USBINTR_IntOnAsyncAdvance                  0x20
    #define HOST20_USBINTR_SystemError                        0x10
    #define HOST20_USBINTR_FrameRollover                      0x08
    #define HOST20_USBINTR_PortChangeDetect                   0x04
    #define HOST20_USBINTR_USBError                           0x02
    #define HOST20_USBINTR_CompletionOfTransaction            0x01
    #define USBWAITEVENTS   (HOST20_USBINTR_CompletionOfTransaction|HOST20_USBINTR_USBError|HOST20_USBINTR_PortChangeDetect|HOST20_USBINTR_SystemError)
	//<7>.0x01C(FRINDEX - Frame Index Register (Address = 01Ch))
	//#define mwHost20_FrameIndex_Rd()		                  (mwHost20Port3(0x1C)&0x00001FFF) 	//Only Read Bit0~Bit12(Skip Bit 13)
	//#define mwHost20_FrameIndex14Bit_Rd()                     (mwHost20Port3(0x1C)&0x00003FFF) 	//Only Read Bit0~Bit12(Skip Bit 13)
	//#define mwHost20_FrameIndex_Set(wValue)		              (mwHost20Port3(0x1C)=wValue)

	//<8>.0x024(PERIODICLISTBASE - Periodic Frame List Base Address Register (Address = 024h))
	//#define mwHost20_PeriodicBaseAddr_Rd()		              (mwHost20Port3(0x24))

	//<9>.0x028(ASYNCLISTADDR - Current Asynchronous List Address Register (Address = 028h))
	//#define mwHost20_CurrentAsynchronousAddr_Rd()		      (mwHost20Port3(0x28) )
	#define mwHost20_CurrentAsynchronousAddr_Set(wValue)	  mwHost20Portw3(0x28,wValue)

	//<10>.0x030(PORTSC - Port Status and Control Register(Address = 030h))
	#define mwHost20_PORTSC_Rd()		                      mwHost20Port3(0x30)

//	#define mwHost20_PORTSC_LineStatus_Rd()		              ((mwHost20Port3(0x30)>>10)&0x00000003)

	#define mwHost20_PORTSC_PortReset_Rd()		              mwHost20Bit_Rd3(0x31,BIT0)
	#define mwHost20_PORTSC_PortReset_Set()		              mwHost20Bit_Set3(0x31,BIT0)
	#define mwHost20_PORTSC_PortReset_Clr()		              mwHost20Bit_Clr3(0x31,BIT0)

	#define mwHost20_PORTSC_ForceSuspend_Rd()		          mwHost20Bit_Rd3(0x30,BIT7)
	#define mwHost20_PORTSC_ForceSuspend_Set()		          mwHost20Bit_Set3(0x30,BIT7)

	#define mwHost20_PORTSC_ForceResume_Rd()		          mwHost20Bit_Rd3(0x30,BIT6)
	#define mwHost20_PORTSC_ForceResume_Set()		          mwHost20Bit_Set3(0x30,BIT6)
	#define mwHost20_PORTSC_ForceResume_Clr()		          mwHost20Bit_Clr3(0x30,BIT6)

	#define mwHost20_PORTSC_EnableDisableChange_Rd()		  mwHost20Bit_Rd3(0x30,BIT3)
	#define mwHost20_PORTSC_EnableDisableChange_Set()		  mwHost20Bit_Set3(0x30,BIT3)

	#define mwHost20_PORTSC_EnableDisable_Rd()		          mwHost20Bit_Rd3(0x30,BIT2)
	#define mwHost20_PORTSC_EnableDisable_Set()		          mwHost20Bit_Set3(0x30,BIT2)
	#define mwHost20_PORTSC_EnableDisable_Clr()		          mwHost20Bit_Clr3(0x30,BIT2)


	#define mwHost20_PORTSC_ConnectChange_Rd()		          mwHost20Bit_Rd3(0x30,BIT1)
	#define mwHost20_PORTSC_ConnectChange_Set()		          mwHost20Bit_Set3(0x30,BIT1)

	#define mwHost20_PORTSC_ConnectStatus_Rd()		          mwHost20Bit_Rd3(0x30,BIT0)



	//<10>.0x034(Misc. Register(Address = 034h))
	#define mwHost20_Misc_EOF1Time_Set(bValue)		          mwHost20Port_wr3(0x34, ((mwHost20Port3(0x34)&0xF3)|(((UINT8)(bValue))<<2)) )
    // (mwHost20Port(0x34)=((mwHost20Port(0x34)&0xF3)|(((UINT8)(bValue))<<2)))	//Bit 2~3

	//<10>.0x034(Misc. Register(Address = 40h))
	#define mwHost20_Control_LineStatus_Rd()		       (mwHost20Port3(0x40)& BIT11)
	#define mwHost20_Control_LineStatus_Set()	           (mwHost20Bit_Set3(0x40,BIT11))
	#define mwHost20_Control_LineStatus_Clr()	           (mwHost20Bit_Clr3(0x40,BIT11))

	#define mwOTG20_Control_HOST_SPD_TYP_Rd()		          ((mwHost20Port3(0x41)>>1)&0x03)

	#define mwHost20_Control_ForceFullSpeed_Rd()		       (mwHost20Port3(0x40)& BIT7)
	#define mwHost20_Control_ForceFullSpeed_Set()	           (mwHost20Bit_Set3(0x40,BIT7))
	#define mwHost20_Control_ForceFullSpeed_Clr()	           (mwHost20Bit_Clr3(0x40,BIT7))

	#define mwHost20_Control_ForceHighSpeed_Rd()		       (mwHost20Port3(0x40)& BIT6)
	#define mwHost20_Control_ForceHighSpeed_Set()	           (mwHost20Bit_Set3(0x40,BIT6))
	#define mwHost20_Control_ForceHighSpeed_Clr()	           (mwHost20Bit_Clr3(0x40,BIT6))

	#define mwOTG20_Control_Phy_Reset_Set()		               (mwHost20Bit_Set3(0x40,BIT5))
	#define mwOTG20_Control_Phy_Reset_Clr()		               (mwHost20Bit_Clr3(0x40,BIT5))

       #define mwOTG20_Control_Half_Speed()                                 (mwHost20Bit_Set3(0x40,BIT2))
       #define mwOTG20_Control_Int_Polarity_Hi()                                 (mwHost20Bit_Set3(0x40,BIT3))

//	#define mwHost20_Control_711MA_FS_Issue_Solve()	            (mwHost20Bit_Set3(0x40,BIT12)) //0x40 Bit-12

#define flib_Host20_Allocate_QHD_Macro(x,y,z,w,u,v)                 \
   {  x->bType=y;                                       \
       x->bDeviceAddress=z;                         \
       x->bHeadOfReclamationListFlag=w;         \
       x->bEdNumber=u;                                 \
       x->bMaxPacketSize=v;          }
//=================== 3.Structure Definition =============================================================
//========================================================================================================

 //<3.1>iTD Structure Definition****************************************

//<3.2>qTD Structure Definition****************************************
typedef struct  _BufferPointer
{
        UINT8      Byte0;
        UINT8      Byte1;
        UINT8      Byte2;
        UINT8      Byte3;
}BufferPointer_Struct;

 #define Host20_Preiodic_Frame_List_MAX	                        1024//(1024\)

 typedef struct   {

     //<1>.Next_Link_Pointer Word
      UINT32   bTerminal:1;             //Bit11~0
      UINT32   bType:2;             //Bit11~0
      UINT32   bReserved:2;          //Bit14~12
      UINT32   bLinkPointer:27; //Bit15

 } Periodic_Frame_List_Cell_Structure;

 typedef struct  {

     Periodic_Frame_List_Cell_Structure   sCell[Host20_Preiodic_Frame_List_MAX];

} Periodic_Frame_List_Structure;
  typedef struct _qTD {

      UINT32   bTerminate:1;
      UINT32   bReserve_1:4;
      UINT32   bNextQTDPointer:27;

     //<2>.Alternate Next qTD Word
      UINT32   bAlternateTerminate:1;
      UINT32   bReserve_2:4;
      UINT32   bAlternateQTDPointer:27;

     //<3>.Status Word
      UINT32   bStatus_PingState:1;
      UINT32   bStatus_SplitState:1;
      UINT32   bStatus_MissMicroFrame:1;
      UINT32   bStatus_Transaction_Err:1;
      UINT32   bStatus_Babble:1;
      UINT32   bStatus_Buffer_Err:1;
      UINT32   bStatus_Halted:1;
      UINT32   bStatus_Active:1;

      UINT32   bPID:2;
      UINT32   bErrorCounter:2;
      UINT32   CurrentPage:3;
      UINT32   bInterruptOnComplete:1;
      UINT32   bTotalBytes:15;
      UINT32   bDataToggle:1;


     //<4>.Buffer Pointer Word Array
     UINT32   ArrayBufferPointer_Word[5];


 } qTD_Structure;

    #define HOST20_qTD_PID_OUT                  0x00
    #define HOST20_qTD_PID_IN                   0x01
    #define HOST20_qTD_PID_SETUP                0x02


    #define HOST20_qTD_STATUS_Active            0x80
    #define HOST20_qTD_STATUS_Halted            0x40
    #define HOST20_qTD_STATUS_BufferError       0x20
    #define HOST20_qTD_STATUS_Babble            0x10
    #define HOST20_qTD_STATUS_TransactionError  0x08
    #define HOST20_qTD_STATUS_MissMicroFrame    0x04
    #define HOST20_qTD_STATUS_Split             0x02
    #define HOST20_qTD_STATUS_Ping              0x01


 typedef struct _qHD {

     //<1>.Next_qHD_Pointer Word
      UINT32   bTerminate:1;
      UINT32   bType:2;
      UINT32   bReserve_1:2;
      UINT32   bNextQHDPointer:27;

     //<2>.qHD_2 Word
      UINT32   bDeviceAddress:7;
      UINT32   bInactiveOnNextTransaction:1;
      UINT32   bEdNumber:4;
      UINT32   bEdSpeed:2;
      UINT32   bDataToggleControl:1;
      UINT32   bHeadOfReclamationListFlag:1;
      UINT32   bMaxPacketSize:11;
      UINT32   bControlEdFlag:1;
      UINT32   bNakCounter:4;

     //<3>.qHD_3 Word
      UINT32   bInterruptScheduleMask:8;
      UINT32   bSplitTransactionMask:8;
      UINT32   bHubAddr:7;
      UINT32   bPortNumber:7;
      UINT32   bHighBandwidth:2;

     //<4>.Overlay_CurrentqTD
      UINT32   bOverlay_CurrentqTD;

     //<5>.Overlay_NextqTD
      UINT32   bOverlay_NextTerminate:1;
      UINT32   bOverlay_Reserve2:4;
      UINT32   bOverlay_NextqTD:27;

     //<6>.Overlay_AlternateNextqTD
      UINT32   bOverlay_AlternateNextTerminate:1;
      UINT32   bOverlay_NanCnt:4;
      UINT32   bOverlay_AlternateqTD:27;

     //<7>.Overlay_TotalBytes
      UINT32   bOverlay_Status:8;
      UINT32   bOverlay_PID:2;
      UINT32   bOverlay_ErrorCounter:2;
      UINT32   bOverlay_C_Page:3;
      UINT32   bOverlay_InterruptOnComplete:1;
      UINT32   bOverlay_TotalBytes:15;
      UINT32   bOverlay_Direction:1;

     //<8>.Overlay_BufferPointer0
      UINT32   bOverlay_CurrentOffset:12;
      UINT32   bOverlay_BufferPointer_0:20;

     //<9>.Overlay_BufferPointer1
      UINT32   bOverlay_C_Prog_Mask:8;
      UINT32   bOverlay_Reserve3:4;
      UINT32   bOverlay_BufferPointer_1:20;

     //<10>.Overlay_BufferPointer2
      UINT32   bOverlay_FrameTag:5;
      UINT32   bOverlay_S_Bytes:7;
      UINT32   bOverlay_BufferPointer_2:20;

     //<11>.Overlay_BufferPointer3
      UINT32   bOverlay_Reserve4:12;
      UINT32   bOverlay_BufferPointer_3:20;

     //<12>.Overlay_BufferPointer4
      UINT32   bOverlay_Reserve5:12;
      UINT32   bOverlay_BufferPointer_4:20;

 } qHD_Structure;

    #define HOST20_HD_Type_iTD                  0x00
    #define HOST20_HD_Type_QH                   0x01
    #define HOST20_HD_Type_siTD                 0x02
    #define HOST20_HD_Type_FSTN                 0x03

//<3.4>.Test Condition Definition****************************************


 typedef struct {

      UINT8   bStructureEnable; //Enable = 0x66  Disable=>Others
      UINT8   bInterruptThreshod;  //01,02,04,08,10,20,40
      UINT8   bAsynchronousParkMode; //00=>Disable,01=>Enable
      UINT8   bAsynchronousParkModeCounter; //01,02,03
      UINT8   bFrameSize; //00,01,02

 } Host20_Init_Condition_Structure;


    #define HOST20_FrameSize_1024                  0x00
    #define HOST20_FrameSize_512                   0x01
    #define HOST20_FrameSize_256                   0x02


//<3.5>.Host20's Attach Device Info Structure****************************************

//OTGHost Device Structure
 typedef struct
 {
	UINT8 bDEVICE_LENGTH;					// bLength
	UINT8 bDT_DEVICE;						// bDescriptorType
	UINT8 bVerLowByte;			            // bcdUSB
	UINT8 bVerHighByte;

	UINT8 bDeviceClass;			            // bDeviceClass
	UINT8 bDeviceSubClass;			        // bDeviceSubClas;
	UINT8 bDeviceProtocol;			        // bDeviceProtocol
	UINT8 bEP0MAXPACKETSIZE;				// bMaxPacketSize0

	UINT8 bVIDLowByte;			            // idVendor
	UINT8 bVIDHighByte;
	UINT8 bPIDLowByte;			            // idProduct
	UINT8 bPIDHighByte;
	UINT8 bRNumLowByte;	                    // bcdDeviceReleaseNumber
	UINT8 bRNumHighByte;

	UINT8 bManufacturer;			        // iManufacturer
	UINT8 bProduct;				            // iProduct
	UINT8 bSerialNumber; 			        // iSerialNumber
	UINT8 bCONFIGURATION_NUMBER;			// bNumConfigurations
 }OTGH_Descriptor_Device_Struct;


//<3.6>.OTGHost Configuration Structure => Only Support 2 Configuration / 5 Interface / 1 Class / 5 Endpoint /1 OTG

    #define  HOST20_CONFIGURATION_NUM_MAX 0X02
    #define  HOST20_INTERFACE_NUM_MAX     0X05
    #define  HOST20_ENDPOINT_NUM_MAX      0X05
    #define  HOST20_CLASS_NUM_MAX         0x01


    #define  HOST20_CONFIGURATION_LENGTH  0X09
    #define  HOST20_INTERFACE_LENGTH      0X09
    #define  HOST20_ENDPOINT_LENGTHX      0X07
    #define  HOST20_CLASS_LENGTHX         0X09

 typedef struct
 {

      //<3>.Define for ED-OTG
                UINT8   bED_OTG_Length;
                UINT8   bED_OTG_bDescriptorType;
                UINT8   bED_OTG_bAttributes;


 }OTGH_Descriptor_OTG_Struct;

 typedef struct
 {
     //<3>.Define for ED-1
                UINT8   bED_Length;
                UINT8   bED_bDescriptorType;
                UINT8   bED_EndpointAddress;
                UINT8   bED_bmAttributes;
                UINT8   bED_wMaxPacketSizeLowByte;
                UINT8   bED_wMaxPacketSizeHighByte;
                UINT8   bED_Interval;

 }OTGH_Descriptor_EndPoint_Struct;


 typedef struct
 {

   UINT8   bClass_LENGTH;
   UINT8   bClaNumberss;
   UINT8   bClassVerLowByte;
   UINT8   bClassVerHighByte;
   UINT8   bCityNumber;
   UINT8   bFollowDescriptorNum;
   UINT8   bReport;
   UINT8   bLengthLowByte;
   UINT8   bLengthHighByte;

 }OTGH_Descriptor_Class_Struct;






 typedef struct
 {

     //<2>.Define for Interface-1
			UINT8 bINTERFACE_LENGTH;		// bLength
			UINT8 bDT_INTERFACE;			// bDescriptorType INTERFACE
			UINT8 bInterfaceNumber;         // bInterfaceNumber
			UINT8 bAlternateSetting;	    // bAlternateSetting
			UINT8 bEP_NUMBER;			    // bNumEndpoints(excluding endpoint zero)
			UINT8 bInterfaceClass;	        // bInterfaceClass
			UINT8 bInterfaceSubClass;       // bInterfaceSubClass
			UINT8 bInterfaceProtocol;       // bInterfaceProtocol
			UINT8 bInterface;		        // iInterface

            OTGH_Descriptor_Class_Struct      sClass[HOST20_CLASS_NUM_MAX];
            OTGH_Descriptor_EndPoint_Struct   sED[HOST20_ENDPOINT_NUM_MAX];



 }OTGH_Descriptor_Interface_Struct;



 typedef struct
 {

 	UINT8  bCONFIG_LENGTH;					// bLength
	UINT8  bDT_CONFIGURATION;				// bDescriptorType CONFIGURATION
	UINT8  bTotalLengthLowByte;	            // wTotalLength, include all descriptors
	UINT8  bTotalLengthHighByte;
	UINT8  bINTERFACE_NUMBER;			    // bNumInterface
	UINT8  bConfigurationValue;				// bConfigurationValue
	UINT8  bConfiguration;			        // iConfiguration
	UINT8  bAttribute;				        // bmAttribute
	UINT8  bMaxPower;				        // iMaxPower (2mA units)

    OTGH_Descriptor_Interface_Struct        sInterface[HOST20_INTERFACE_NUM_MAX];


 }OTGH_Descriptor_Configuration_Only_Struct;



 //Support Configuration x2
 //        Interface     x5
 //        EndPoint      x5
 //        OTG           X1

 typedef struct
 {



	//<2>.Descriptor Information
    OTGH_Descriptor_Device_Struct            sDD;
    OTGH_Descriptor_Configuration_Only_Struct   saCD[HOST20_CONFIGURATION_NUM_MAX];
    OTGH_Descriptor_OTG_Struct              sOTG;
   UINT8                                   bAdd;
    UINT8                                   bSpeed;  //0=>Low Speed / 1=>Full Speed / 2 => High Speed
    UINT8                                   bSendStatusError;

 //   UINT8                                   bReportDescriptor[0x74];
   // UINT8                                   bStringLanguage[10];
 //   UINT8                                   bStringManufacture[0xFF];
  //  UINT8                                   bStringProduct[0xFF];
   // UINT8                                   bStringSerialN[0xFF];
    //<3>.For ISO Information
   // UINT8                                   bISOTransferEnable;
   // UINT32                                  wISOiTDAddress[1024];

 }Host20_Attach_Device_Structure;

    #define HOST20_Attach_Device_Speed_Full                  0x00
    #define HOST20_Attach_Device_Speed_Low                   0x01
    #define HOST20_Attach_Device_Speed_High                  0x02

 //<3.7>.Control Command Structure
 typedef struct {

      UINT8   bmRequestType; //(In/Out),(Standard...),(Device/Interface...)
      UINT8   bRequest;      //GetStatus .....
      UINT8   wValueLow;     //Byte2
      UINT8   wValueHigh;    //Byte3
      UINT8   wIndexLow;     //Byte4
      UINT8   wIndexHigh;    //Byte5
      UINT8   wLengthLow;    //Byte6
      UINT8   wLengthHigh;   //Byte7


 } Host20_Control_Command_Structure;

  #define HOST20_CONTROL_GetStatus             0x00
  #define HOST20_CONTROL_ClearFeature          0x01
  #define HOST20_CONTROL_SetFeature            0x03
  #define HOST20_CONTROL_SetAddress            0x05
  #define HOST20_CONTROL_GetDescriptor         0x06
  #define HOST20_CONTROL_SetDescriptor         0x07
  #define HOST20_CONTROL_GetConfiguration      0x08
  #define HOST20_CONTROL_GetInterface          0x0A
  #define HOST20_CONTROL_SetInterface          0x0B
  #define HOST20_CONTROL_SyncFrame             0x0C


  #define HOST20_HID_GetReport                 0x01
  #define HOST20_HID_GetIdle                   0x02
  #define HOST20_HID_GetProtocol               0x03
  #define HOST20_HID_SetReport                 0x09
  #define HOST20_HID_SetIdle                   0x0A
  #define HOST20_HID_SetProtocol               0x0B


 //<3.8>.BufferPointerArray
  typedef struct {
      UINT32   BufferPointerArray[8];
 } Host20_BufferPointerArray_Structure;





//=================== 4.Extern Function Definition =======================================================
//========================================================================================================

  extern UINT8 flib_OTGH_Init3(UINT8 wForDevice_B, UINT16 wDelay);
  extern UINT8 flib_Host20_Close3(UINT8 bForDeviceB);

  //extern UINT8 flib_Host20_ISR(void);
  extern UINT8 flib_Host20_PortBusReset3(void);
  extern UINT8 flib_Host20_Suspend3(void);
  extern UINT8 flib_Host20_Issue_Control3(UINT8 bEdNum,UINT8* pbCmd,UINT16 hwDataSize,UINT8* pbData);
  extern UINT8  flib_Host20_Issue_Bulk3(UINT8 bArrayListNum,UINT16 hwSize,UINT32 pwBufferArray,UINT8 bDirection);

//  extern void flib_Host20_TimerEnable(UINT32 wTime_ms);
  extern void flib_Host20_InitStructure3(void);
  extern qTD_Structure *flib_Host20_GetStructure3(UINT8 Type);
  extern void flib_Host20_ReleaseStructure3(UINT8 Type,UINT32 pwAddress);
  extern void flib_Host20_QHD_Control_Init3(void);
  extern UINT8 flib_Host20_Send_qTD3(qTD_Structure *spHeadqTD ,qHD_Structure *spTempqHD,int wTimeOutSec);
extern void flib_Host20_Allocate_QHD3(qHD_Structure  *psQHTemp,UINT8 bNextType,UINT8 bAddress,UINT8 bHead,UINT8 bEndPt, UINT32 wMaxPacketSize);

  //extern void  flib_Host20_Interrupt_Init(struct usb_device *dev);

  extern void flib_Host20_Asynchronous_Enable3(void);
  extern void flib_Host20_Asynchronous_Disable3(void);

   extern void flib_Host20_StopRun_Setting3(UINT8 bOption);
   extern void flib_Host20_Asynchronous_Setting3(UINT8 bOption);

//=================== 5.Call Extern Function Definition =======================================================
//========================================================================================================



//=================== 6.Extern Variable Definition =======================================================
//========================================================================================================

 extern   UINT8 OTGH_GETDESCRIPTOR_DEVICE[];
 extern   UINT8 OTGH_GETDESCRIPTOR_CONFIG[];
 extern   UINT8 OTGH_SETADDRESS[];
 extern    UINT8 OTGH_SETCONFIGURATION[];
 extern    UINT8 OTGH_GETDESCRIPTOR_OTG[];
 extern   UINT8 OTGH_SET_FEATURE_OTG[];
 extern   UINT8 OTGH_SETDESCRIPTOR_DEVICE[];
  // extern volatile UINT32 wOTG_Timer_Counter;
//   extern qHD_Structure     *psHost20_qHD_List_Control[3];
//   extern qHD_Structure     *psHost20_qHD_List_Bulk[3];
extern  qHD_Structure  Host20_qHD_List_Control0;
extern  qHD_Structure  Host20_qHD_List_Bulk0;
extern  qHD_Structure  Host20_qHD_List_Control1;
extern  qHD_Structure  Host20_qHD_List_Bulk1;

   extern UINT8             Host20_qTD_Manage[Host20_qTD_MAX];  //1=>Free 2=>used
//   extern UINT8             Host20_iTD_Manage[Host20_iTD_MAX];  //1=>Free 2=>used
   //extern UINT8             Host20_DataPage_Manage[Host20_Page_MAX];  //1=>Free 2=>used

   extern Host20_Init_Condition_Structure sInitCondition;
  // extern  Host20_Attach_Device_Structure  sAttachDevice;
 //  extern volatile UINT32 wOTG_Timer_Counter;
//   extern Periodic_Frame_List_Structure  *psHost20_FramList;
//   extern  volatile UINT32 gwLastiTDSendOK;

//   extern   Host20_ISO_FixBufferMode_Structure sISOFixBufferMode;
  // extern   UINT8 bForceSpeed;//0=>All Clear 1=>Full Speed 2=>High Speed


  extern Host20_Attach_Device_Structure *psDevice_AP;
//  extern  UINT32 Host20_STRUCTURE_qHD_BASE_ADDRESS,Host20_STRUCTURE_qTD_BASE_ADDRESS;
 //extern UINT32 Host20_STRUCTURE_Preiodic_Frame_List_BASE_ADDRESS,Host20_STRUCTURE_iTD_BASE_ADDRESS;


#endif //LIB_DRVHOSTLIB3__H

