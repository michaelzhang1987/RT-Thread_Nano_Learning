/*******************************************************************************
                                包含头文件
*******************************************************************************/
#include "Rail_Car_Master_Include.h"

/*******************************************************************************
                                全局变量
*******************************************************************************/
MGQ_UART Reader_Card_UART_Ctrl;
Reader_Card_Struct Reader_Card_Ctrl;


/*
*******************************************************************************
* 函数名: void Set_Reader_Card_Work_Pattern(void)
* 说  明: 设置读卡器工作模式
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20181019
* 修  改:
********************************************************************************
*/
void Set_Reader_Card_Work_Pattern(unsigned char mode,unsigned char Mode_Data)
{
  if(mode == ReaderCardID_AndUploading)
  {
    Reader_Card_UART_Ctrl.TX_Buffer[0] = 0x03;
    Reader_Card_UART_Ctrl.TX_Buffer[1] = 0x08;
    Reader_Card_UART_Ctrl.TX_Buffer[2] = 0xC1;
    Reader_Card_UART_Ctrl.TX_Buffer[3] = 0x20;
    Reader_Card_UART_Ctrl.TX_Buffer[4] = 0x02;
    Reader_Card_UART_Ctrl.TX_Buffer[5] = 0x00;
    Reader_Card_UART_Ctrl.TX_Buffer[6] = 0x00;
    Reader_Card_UART_Ctrl.TX_Buffer[7] = ComputedCheckSum(&Reader_Card_UART_Ctrl.TX_Buffer[0],7);
    HAL_UART_Transmit(&Reader_Card_UART,&Reader_Card_UART_Ctrl.TX_Buffer[0],8,200);
  }
  else if(mode == ReaderCardBlock_AndUploading)
  {
    Reader_Card_UART_Ctrl.TX_Buffer[0] = 0x03;
    Reader_Card_UART_Ctrl.TX_Buffer[1] = 0x08;
    Reader_Card_UART_Ctrl.TX_Buffer[2] = 0xC1;
    Reader_Card_UART_Ctrl.TX_Buffer[3] = 0x20;
    Reader_Card_UART_Ctrl.TX_Buffer[4] = 0x03;
    Reader_Card_UART_Ctrl.TX_Buffer[5] = Mode_Data;
    Reader_Card_UART_Ctrl.TX_Buffer[6] = 0x00;
    Reader_Card_UART_Ctrl.TX_Buffer[7] = ComputedCheckSum(&Reader_Card_UART_Ctrl.TX_Buffer[0],7);;
    HAL_UART_Transmit(&Reader_Card_UART,&Reader_Card_UART_Ctrl.TX_Buffer[0],8,200);
  }
}

/*
***************************************************************************************************
* 函数名: unsigned char ComputedCheckSum(unsigned char *pBuffer,unsigned char lenght)
* 说  明: 计算校验和
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20181019
* 修  改:
***************************************************************************************************
*/
unsigned char ComputedCheckSum(unsigned char *pBuffer,unsigned char lenght)
{
  unsigned char j=0;
  unsigned char i=0;
  for(i=0;i<lenght;i++)
  {
    j ^= *pBuffer;
    pBuffer++;
  }
  return ~j;
}

/*
***************************************************************************************************
* 函数名: void SetTheReaderSensitivity(unsigned char data)
* 说  明: 设置读卡器灵敏度
* 参  数: data越小越灵敏
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20181019
* 修  改:
***************************************************************************************************
*/
void SetTheReaderSensitivity(unsigned char data)
{
  Reader_Card_UART_Ctrl.TX_Buffer[0] = 0x03;
  Reader_Card_UART_Ctrl.TX_Buffer[1] = 0x08;
  Reader_Card_UART_Ctrl.TX_Buffer[2] = 0xC6;
  Reader_Card_UART_Ctrl.TX_Buffer[3] = 0x20;
  Reader_Card_UART_Ctrl.TX_Buffer[4] = data;
  Reader_Card_UART_Ctrl.TX_Buffer[5] = 0x0A;
  Reader_Card_UART_Ctrl.TX_Buffer[6] = 0x00;
  Reader_Card_UART_Ctrl.TX_Buffer[7] = ComputedCheckSum(&Reader_Card_UART_Ctrl.TX_Buffer[0],7);
  HAL_UART_Transmit(&Reader_Card_UART,&Reader_Card_UART_Ctrl.TX_Buffer[0],8,200);
}
/*
***************************************************************************************************
* 函数名: void SetTheReaderBaudRate(uint8_t baud)
* 说  明: 设置读卡器波特率
* 参  数: 0x01:9600 0x07:115200
* 返回值: N/A
* 设  计: GEEK_MICHAEL
* 日  期: 20200410
* 修  改:此函数慎重使用
***************************************************************************************************
*/
void SetTheReaderBaudRate(uint8_t baud)
{
  Reader_Card_UART_Ctrl.TX_Buffer[0] = 0x03;
  Reader_Card_UART_Ctrl.TX_Buffer[1] = 0x08;
  Reader_Card_UART_Ctrl.TX_Buffer[2] = 0xC7;
  Reader_Card_UART_Ctrl.TX_Buffer[3] = 0x20;
  Reader_Card_UART_Ctrl.TX_Buffer[4] = baud;
  Reader_Card_UART_Ctrl.TX_Buffer[5] = 0x00;
  Reader_Card_UART_Ctrl.TX_Buffer[6] = 0x00;
  Reader_Card_UART_Ctrl.TX_Buffer[7] = ComputedCheckSum(&Reader_Card_UART_Ctrl.TX_Buffer[0],7);
  HAL_UART_Transmit(&Reader_Card_UART,&Reader_Card_UART_Ctrl.TX_Buffer[0],8,200);
}
/*
***************************************************************************************************
* 函数名: void SetTheReaderOnlyONE(unsigned char data)
* 说  明: 设置读卡器读一次
* 参  数:
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20181019
* 修  改:
***************************************************************************************************
*/
void SetTheReaderOnlyONE(void)
{
  Reader_Card_UART_Ctrl.TX_Buffer[0] = 0x03;
  Reader_Card_UART_Ctrl.TX_Buffer[1] = 0x08;
  Reader_Card_UART_Ctrl.TX_Buffer[2] = 0xC8;
  Reader_Card_UART_Ctrl.TX_Buffer[3] = 0x20;
  Reader_Card_UART_Ctrl.TX_Buffer[4] = 0;
  Reader_Card_UART_Ctrl.TX_Buffer[5] = 0;
  Reader_Card_UART_Ctrl.TX_Buffer[6] = 0;
  Reader_Card_UART_Ctrl.TX_Buffer[7] = ComputedCheckSum(&Reader_Card_UART_Ctrl.TX_Buffer[0],7);
  HAL_UART_Transmit(&Reader_Card_UART,&Reader_Card_UART_Ctrl.TX_Buffer[0],8,200);
}
/*
***************************************************************************************************
* 函数名: void SetTheReaderONEbyONE(unsigned char data)
* 说  明: 设置读卡器一直读
* 参  数:
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20181019
* 修  改:
***************************************************************************************************
*/
void SetTheReaderONEbyONE(void)
{
  Reader_Card_UART_Ctrl.TX_Buffer[0] = 0x03;
  Reader_Card_UART_Ctrl.TX_Buffer[1] = 0x08;
  Reader_Card_UART_Ctrl.TX_Buffer[2] = 0xC8;
  Reader_Card_UART_Ctrl.TX_Buffer[3] = 0x20;
  Reader_Card_UART_Ctrl.TX_Buffer[4] = 1;
  Reader_Card_UART_Ctrl.TX_Buffer[5] = 0;
  Reader_Card_UART_Ctrl.TX_Buffer[6] = 0;
  Reader_Card_UART_Ctrl.TX_Buffer[7] = ComputedCheckSum(&Reader_Card_UART_Ctrl.TX_Buffer[0],7);
  HAL_UART_Transmit(&Reader_Card_UART,&Reader_Card_UART_Ctrl.TX_Buffer[0],8,200);
}
/*
***************************************************************************************************
* 函数名: void Read_Reader_Word_MODE(void)
* 说  明: 读取读卡器工作模式
* 参  数:
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20190424
* 修  改:
***************************************************************************************************
*/
void Read_Reader_Word_MODE(void)
{
  Reader_Card_UART_Ctrl.TX_Buffer[0] = 0x02;
  Reader_Card_UART_Ctrl.TX_Buffer[1] = 0x08;
  Reader_Card_UART_Ctrl.TX_Buffer[2] = 0xB1;
  Reader_Card_UART_Ctrl.TX_Buffer[3] = 0x20;
  Reader_Card_UART_Ctrl.TX_Buffer[4] = 0;
  Reader_Card_UART_Ctrl.TX_Buffer[5] = 0;
  Reader_Card_UART_Ctrl.TX_Buffer[6] = 0;
  Reader_Card_UART_Ctrl.TX_Buffer[7] = ComputedCheckSum(&Reader_Card_UART_Ctrl.TX_Buffer[0],7);
  HAL_UART_Transmit(&Reader_Card_UART,&Reader_Card_UART_Ctrl.TX_Buffer[0],8,200);
}
/*
***************************************************************************************************
* 函数名: void Init_Reader_Word_MODE(void)
* 说  明: 初始化读卡器工作模式
* 参  数:
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20190424
* 修  改:
***************************************************************************************************
*/
void Init_Reader_Word_MODE(void)
{
  static uint8_t count = 0;
  count++;
  if(count == 5)
  {
    /*设置读卡器工作模式 = 读取卡号*/
    Set_Reader_Card_Work_Pattern(ReaderCardID_AndUploading,0);
    count++;
  }
  if(count == 15)
  {
    /*设置读卡器灵敏度为最高*/
    SetTheReaderSensitivity(0);
    count++;
  }
  if(count == 25)
  {
    
    /*设置读卡器读一次*/
    SetTheReaderOnlyONE();
    count++;
//    Reader_Card_Ctrl.Flag.Need_InitMod = 0;
  }
  if(count > 25)
  {
    count = 0;
    SetTheReaderBaudRate(0x01);
    Reader_Card_Ctrl.Flag.Need_InitMod = 0;
  }
}

/*
***************************************************************************************************
* 函数名: void Init_Reader_Card_Struct(void)
* 说  明: 读卡器初始化结构体
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20181019
* 修  改:
***************************************************************************************************
*/
void Init_Reader_Card_Struct(void)
{
  Reader_Card_Ctrl.Err.Byte      = 0;
  Reader_Card_Ctrl.Flag.Byte     = 0;

  Reader_Card_Ctrl.Binding_CARD_ID[0] = 0x00;
  Reader_Card_Ctrl.Binding_CARD_ID[1] = 0x00;
  Reader_Card_Ctrl.Binding_CARD_ID[2] = 0x00;
  Reader_Card_Ctrl.Binding_CARD_ID[3] = 0x00;

  Reader_Card_Ctrl.Real_time_CARD_ID[0] = 0x00;
  Reader_Card_Ctrl.Real_time_CARD_ID[1] = 0x00;
  Reader_Card_Ctrl.Real_time_CARD_ID[2] = 0x00;
  Reader_Card_Ctrl.Real_time_CARD_ID[3] = 0x00;
}

/*
***************************************************************************************************
* 函数名: void Reader_Card_COMM_Dispose(unsigned char data)
* 说  明: 读卡器接收数据处理
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20181019
* 修  改:
***************************************************************************************************
*/
void Reader_Card_COMM_Dispose(unsigned char data)
{
  if(!Reader_Card_UART_Ctrl.VD_Timeout)
  {
    Reader_Card_UART_Ctrl.VD_State = 0;
  }
  if(Reader_Card_UART_Ctrl.VD_State == 0)
  {
    if(data == 0x04)
    {
      Reader_Card_UART_Ctrl.VD_Buffer[0] = data;
      Reader_Card_UART_Ctrl.VD_Counter = 1;
      Reader_Card_UART_Ctrl.VD_Timeout = 20;
      Reader_Card_UART_Ctrl.VD_State = 1;
    }
    else if(data == 0x02)
    {
      Reader_Card_UART_Ctrl.VD_Buffer[0] = data;
      Reader_Card_UART_Ctrl.VD_Counter = 1;
      Reader_Card_UART_Ctrl.VD_Timeout = 20;
      Reader_Card_UART_Ctrl.VD_State = 4;
    }
  }
  else if(Reader_Card_UART_Ctrl.VD_State == 1)
  {
    Reader_Card_UART_Ctrl.VD_Buffer[Reader_Card_UART_Ctrl.VD_Counter++] = data;
    Reader_Card_UART_Ctrl.VD_Timeout = 20;
    if(Reader_Card_UART_Ctrl.VD_Counter >= 3)
    {
      if(Reader_Card_UART_Ctrl.VD_Buffer[2] == 0x02&&Reader_Card_UART_Ctrl.VD_Buffer[1] == 0x0C)
      {
        Reader_Card_UART_Ctrl.VD_State = 2;
      }
      else if(Reader_Card_UART_Ctrl.VD_Buffer[2] == 0x03&&Reader_Card_UART_Ctrl.VD_Buffer[1] == 0x16)
      {
        Reader_Card_UART_Ctrl.VD_State = 3;
      }
      else
      {
        Reader_Card_UART_Ctrl.VD_State = 0;
      }
    }
  }
  else if(Reader_Card_UART_Ctrl.VD_State == 2)
  {
    Reader_Card_UART_Ctrl.VD_Buffer[Reader_Card_UART_Ctrl.VD_Counter++] = data;
    Reader_Card_UART_Ctrl.VD_Timeout = 20;
    if(Reader_Card_UART_Ctrl.VD_Counter >= Reader_Card_UART_Ctrl.VD_Buffer[1])
    {
      Reader_Card_Ctrl.Err.COMM_OK = 1;
      Reader_Card_UART_Ctrl.VD_State = 0;
      Reader_Card_UART_Ctrl.VD_Verify = ComputedCheckSum(&Reader_Card_UART_Ctrl.VD_Buffer[0],11);
      if(Reader_Card_UART_Ctrl.VD_Verify == Reader_Card_UART_Ctrl.VD_Buffer[11])
      {
        if(Reader_Card_Ctrl.Flag.Enable)
        {
          Reader_Card_Ctrl.Flag.slot_card = 1;
          Reader_Card_Ctrl.Real_time_CARD_ID[0] = Reader_Card_UART_Ctrl.VD_Buffer[7];
          Reader_Card_Ctrl.Real_time_CARD_ID[1] = Reader_Card_UART_Ctrl.VD_Buffer[8];
          Reader_Card_Ctrl.Real_time_CARD_ID[2] = Reader_Card_UART_Ctrl.VD_Buffer[9];
          Reader_Card_Ctrl.Real_time_CARD_ID[3] = Reader_Card_UART_Ctrl.VD_Buffer[10];
        }
      }
    }
  }
  else if(Reader_Card_UART_Ctrl.VD_State == 3)
  {
    Reader_Card_UART_Ctrl.VD_Buffer[Reader_Card_UART_Ctrl.VD_Counter++] = data;
    Reader_Card_UART_Ctrl.VD_Timeout = 20;
    if(Reader_Card_UART_Ctrl.VD_Counter >= Reader_Card_UART_Ctrl.VD_Buffer[1])
    {
      Reader_Card_UART_Ctrl.VD_State = 0;
      Reader_Card_Ctrl.Err.COMM_OK = 1;
      Reader_Card_UART_Ctrl.VD_Verify = ComputedCheckSum(&Reader_Card_UART_Ctrl.VD_Buffer[0],21);
      if(Reader_Card_UART_Ctrl.VD_Verify == Reader_Card_UART_Ctrl.VD_Buffer[Reader_Card_UART_Ctrl.VD_Buffer[1]-1])
      {
        if(Reader_Card_Ctrl.Flag.Enable)
        {
          Reader_Card_Ctrl.Flag.Block_Card = 1;
          Reader_Card_Ctrl.Block_Data[0] = Reader_Card_UART_Ctrl.VD_Buffer[5];
          Reader_Card_Ctrl.Block_Data[1] = Reader_Card_UART_Ctrl.VD_Buffer[6];
          Reader_Card_Ctrl.Block_Data[2] = Reader_Card_UART_Ctrl.VD_Buffer[7];
          Reader_Card_Ctrl.Block_Data[3] = Reader_Card_UART_Ctrl.VD_Buffer[8];
          Reader_Card_Ctrl.Block_Data[4] = Reader_Card_UART_Ctrl.VD_Buffer[9];
          Reader_Card_Ctrl.Block_Data[5] = Reader_Card_UART_Ctrl.VD_Buffer[10];
          Reader_Card_Ctrl.Block_Data[6] = Reader_Card_UART_Ctrl.VD_Buffer[11];
          Reader_Card_Ctrl.Block_Data[7] = Reader_Card_UART_Ctrl.VD_Buffer[12];
          Reader_Card_Ctrl.Block_Data[8] = Reader_Card_UART_Ctrl.VD_Buffer[13];
          Reader_Card_Ctrl.Block_Data[9] = Reader_Card_UART_Ctrl.VD_Buffer[14];
          Reader_Card_Ctrl.Block_Data[10] = Reader_Card_UART_Ctrl.VD_Buffer[15];
          Reader_Card_Ctrl.Block_Data[11] = Reader_Card_UART_Ctrl.VD_Buffer[16];
          Reader_Card_Ctrl.Block_Data[12] = Reader_Card_UART_Ctrl.VD_Buffer[17];
          Reader_Card_Ctrl.Block_Data[13] = Reader_Card_UART_Ctrl.VD_Buffer[18];
          Reader_Card_Ctrl.Block_Data[14] = Reader_Card_UART_Ctrl.VD_Buffer[19];
          Reader_Card_Ctrl.Block_Data[15] = Reader_Card_UART_Ctrl.VD_Buffer[20];
        }
      }
    }
  }
  else if(Reader_Card_UART_Ctrl.VD_State == 4)
  {
    Reader_Card_UART_Ctrl.VD_Buffer[Reader_Card_UART_Ctrl.VD_Counter++] = data;
    Reader_Card_UART_Ctrl.VD_Timeout = 20;
    if(Reader_Card_UART_Ctrl.VD_Counter >= Reader_Card_UART_Ctrl.VD_Buffer[1])
    {
      Reader_Card_UART_Ctrl.VD_State = 0;
      Reader_Card_Ctrl.Err.COMM_OK = 1;
      Reader_Card_UART_Ctrl.VD_Verify = ComputedCheckSum(&Reader_Card_UART_Ctrl.VD_Buffer[0],Reader_Card_UART_Ctrl.VD_Buffer[1]-1);
      if(Reader_Card_UART_Ctrl.VD_Verify == Reader_Card_UART_Ctrl.VD_Buffer[Reader_Card_UART_Ctrl.VD_Buffer[1]-1])
      {
        if(Reader_Card_UART_Ctrl.VD_Buffer[0] == 0x02&&Reader_Card_UART_Ctrl.VD_Buffer[2] == 0xB1)
        {
          if(Reader_Card_UART_Ctrl.VD_Buffer[5] != 2)//自动读卡号
          {
            Reader_Card_Ctrl.Flag.Need_InitMod = 1;
          }
          if(Reader_Card_UART_Ctrl.VD_Buffer[7] != 0)
          {
            Reader_Card_Ctrl.Flag.Need_InitMod = 1;
          }
        }
      }
    }
  }
}