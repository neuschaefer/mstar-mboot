/*****************************************************************************************
 *
 * FILE NAME          : MxL608_OEM_Drv.c
 * 
 * AUTHOR             : Mahendra Kondur
 *
 * DATE CREATED       : 12/23/2011  
 *
 * DESCRIPTION        : This file contains I2C driver and Sleep functins that 
 *                      OEM should implement for MxL608 APIs
 *                             
 *****************************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ****************************************************************************************/

#include "MxL608_OEM_Drv.h"
#include "MsCommon.h"
#include "MsOS.h"
#include "Board.h"
#include "drvHWI2C.h"

#if (FRONTEND_TUNER_TYPE == TUNER_MXL608)

extern MS_BOOL MDrv_IIC_Write(MS_U8 u8SlaveID, MS_U8 *pu8Addr, MS_U8 u8AddrSize, MS_U8 *pu8Buf, MS_U32 u32BufSize);
extern MS_BOOL MDrv_IIC_Read(MS_U8 u8SlaveID, MS_U8 *pu8Addr, MS_U8 u8AddrSize, MS_U8 *pu8Buf, MS_U32 u32BufSize);
extern MS_BOOL MDrv_IIC1_Write(MS_U8 u8SlaveID, MS_U8 *pu8Addr, MS_U8 u8AddrSize, MS_U8 *pu8Buf, MS_U32 u32BufSize);
extern MS_BOOL MDrv_IIC1_Read(MS_U8 u8SlaveID, MS_U8 *pu8Addr, MS_U8 u8AddrSize, MS_U8 *pu8Buf, MS_U32 u32BufSize);

typedef MS_BOOL (*IIC_WriteFuncPT)(MS_U8 u8SlaveID, MS_U8 *pu8Addr, MS_U8 u8AddrSize, MS_U8 *pu8Buf, MS_U32 u32BufSize);
typedef MS_BOOL (*IIC_ReadFuncPT)(MS_U8 u8SlaveID, MS_U8 *pu8Addr, MS_U8 u8AddrSize, MS_U8 *pu8Buf, MS_U32 u32BufSize);

static IIC_WriteFuncPT IIC_WRITE = MDrv_IIC_Write;
static IIC_ReadFuncPT IIC_READ = MDrv_IIC_Read;


MXL_STATUS MxLWare608_OEM_Init(void)
{
    if(FRONTEND_TUNER_PORT == E_HWI2C_PORT0_1)
    {
        IIC_WRITE = MDrv_IIC_Write;
        IIC_READ = MDrv_IIC_Read;
    }
    else if(FRONTEND_TUNER_PORT == E_HWI2C_PORT1_1)
    {
        IIC_WRITE = MDrv_IIC1_Write;
        IIC_READ = MDrv_IIC1_Read;
    }
    else
    {
        printf("[%s][%d] Unknown I2C port config.\n", __FUNCTION__, __LINE__);
        return MXL_FALSE;
    }

    return MXL_TRUE;
}

/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare608_OEM_WriteRegister
--| 
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 7/30/2009
--|
--| DESCRIPTION   : This function does I2C write operation.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxLWare608_OEM_WriteRegister(UINT8 devId, UINT8 RegAddr, UINT8 RegData)
{
  // OEM should implement I2C write protocol that complies with MxL608 I2C
  // format.

  // 8 bit Register Write Protocol:
  // +------+-+-----+-+-+----------+-+----------+-+-+
  // |MASTER|S|SADDR|W| |RegAddr   | |RegData(L)| |P|
  // +------+-+-----+-+-+----------+-+----------+-+-+
  // |SLAVE |         |A|          |A|          |A| |
  // +------+---------+-+----------+-+----------+-+-+
  // Legends: SADDR (I2c slave address), S (Start condition), A (Ack), N(NACK), 
  // P(Stop condition)

  MXL_STATUS status = MXL_FALSE;
  

/* If OEM data is implemented, customer needs to use OEM data structure related operation 
   Following code should be used as a reference. 
   For more information refer to sections 2.5 & 2.6 of MxL608_mxLWare_API_UserGuide document.

  UINT8 i2cSlaveAddr;
  UINT8 i2c_bus;
  user_data_t * user_data = (user_data_t *) MxL608_OEM_DataPtr[devId];
 
  if (user_data)
  {
    i2cSlaveAddr = user_data->i2c_address;           // get device i2c address
    i2c_bus = user_data->i2c_bus;                   // get device i2c bus  
  
    sem_up(user_data->sem);                         // up semaphore if needed

    // I2C Write operation 
    status = USER_I2C_WRITE_FUNCTION(i2cSlaveAddr, i2c_bus, RegAddr, RegData);
    
    sem_down(user_data->sem);                       // down semaphore
    user_data->i2c_cnt++;                           // user statistics
  }

*/

  /* If OEM data is not required, customer should treat devId as I2C slave Address */

    MS_U8 pArray[6];

    pArray[0] = RegAddr;
    pArray[1] = RegData;
#if(FRONTEND_DEMOD_TYPE ==DEMOD_TC90517)
    MS_U8 paddr[1];
    MS_U8 u8SlaveID;
    u8SlaveID = 0x30;  //demod iic addr
    paddr[0] = 0xFE;
    pArray[0]= devId;
    pArray[1]= RegAddr;
    pArray[2]= RegData;
    if (IIC_WRITE(u8SlaveID, paddr, 1, pArray,3) != 0)
#else
    if (IIC_WRITE(devId, NULL, 0, pArray, 2) != 0)
#endif
    {
        MsOS_DelayTask(1);
        status = MXL_TRUE ;
    }
    else
    {
        printf("\ni2c write err\n");
        status = MXL_FALSE;
    }
  
  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare608_OEM_ReadRegister
--| 
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 7/30/2009
--|
--| DESCRIPTION   : This function does I2C read operation.
--|
--| RETURN VALUE  : True or False
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxLWare608_OEM_ReadRegister(UINT8 devId, UINT8 RegAddr, UINT8 *DataPtr)
{
  // OEM should implement I2C read protocol that complies with MxL608 I2C
  // format.

  // 8 bit Register Read Protocol:
  // +------+-+-----+-+-+----+-+----------+-+-+
  // |MASTER|S|SADDR|W| |0xFB| |RegAddr   | |P|
  // +------+-+-----+-+-+----+-+----------+-+-+
  // |SLAVE |         |A|    |A|          |A| |
  // +------+-+-----+-+-+----+-+----------+-+-+
  // +------+-+-----+-+-+-----+--+-+
  // |MASTER|S|SADDR|R| |     |MN|P|
  // +------+-+-----+-+-+-----+--+-+
  // |SLAVE |         |A|Data |  | |
  // +------+---------+-+-----+--+-+
  // Legends: SADDR(I2c slave address), S(Start condition), MA(Master Ack), MN(Master NACK), 
  // P(Stop condition)

  MXL_STATUS status = MXL_TRUE;

/* If OEM data is implemented, customer needs to use OEM data structure related operation 
   Following code should be used as a reference. 
   For more information refer to sections 2.5 & 2.6 of MxL608_mxLWare_API_UserGuide document.

  UINT8 i2cSlaveAddr;
  UINT8 i2c_bus;
  user_data_t * user_data = (user_data_t *) MxL608_OEM_DataPtr[devId];
 
  if (user_data)
  {
    i2cSlaveAddr = user_data->i2c_address;           // get device i2c address
    i2c_bus = user_data->i2c_bus;                   // get device i2c bus  
  
    sem_up(user_data->sem);                         // up semaphore if needed

    // I2C Write operation 
    status = USER_I2C_READ_FUNCTION(i2cSlaveAddr, i2c_bus, RegAddr, DataPtr);
    
    sem_down(user_data->sem);                       // down semaphore
    user_data->i2c_cnt++;                           // user statistics
  }

*/

  /* If OEM data is not required, customer should treat devId as I2C slave Address */


    UINT8 pArray[6];

    pArray[0] = 0xFB;
    pArray[1] = RegAddr;

#if(FRONTEND_DEMOD_TYPE ==DEMOD_TC90517)
    MS_U8 u8SlaveID;
    MS_U8 paddr[1];
    u8SlaveID = 0x30;    //demod iic addr
    paddr[0] = 0xFE;
    pArray[0] = devId;
    pArray[1] = 0xFB;
    pArray[2] = RegAddr;
    if( IIC_WRITE(u8SlaveID, paddr,1, pArray, 3) != 0)
#else

    if (IIC_READ( devId, pArray, 2, DataPtr, 1) != 0)
#endif
    {
#if(FRONTEND_DEMOD_TYPE ==DEMOD_TC90517)
    pArray[0] = 0xFE;
    pArray[1] = devId+1;
    if (IIC_READ( u8SlaveID, pArray, 2, DataPtr, 1) == 0)
    {
        printf("\ni2c read err 1\n");
        return status =MXL_FALSE;
    }
#endif
        return status =MXL_TRUE ;
    }
    else
    {
        printf("\ni2c read err\n");
        return status =MXL_FALSE;
    }
  
  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare608_OEM_Sleep
--| 
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 01/10/2010
--|
--| DESCRIPTION   : This function complete sleep operation. WaitTime is in ms unit
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

void MxLWare608_OEM_Sleep(UINT16 DelayTimeInMs)
{
  // OEM should implement sleep operation 
    MsOS_DelayTask(DelayTimeInMs);
  
}

#endif
