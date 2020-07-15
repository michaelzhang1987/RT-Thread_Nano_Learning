
/*******************************************************************************
                                包含头文件
*******************************************************************************/
#include "Rail_Car_Master_Include.h"

/*******************************************************************************
                                全局变量
*******************************************************************************/
AUX_Struct AUX_Ctrl;
MGQ_UART AUX_UART_Ctrl;
SWITCH_INPUT MP3_Input,Voice_Input;

/*
********************************************************************************
* 函数名: void Set_mode_AUX(unsigned char option,unsigned char data)
* 说  明: 设置播放模式
* 注  意：模块上电1秒后方能发送，使用死循环发送
* 参  数: data = 0-4 =全盘、文件夹、单曲、随机、无循环
* 返回值:
* 设  计: MGQ
* 日  期: 20181017
* 修  改:
********************************************************************************
*/
void Set_mode_AUX(unsigned char option,unsigned char data)
{
  if(data>4)
    data = 4;

  AUX_Ctrl.buffer[0] = 0x7E;
  AUX_Ctrl.buffer[1] = 0x04;
  AUX_Ctrl.buffer[2] = 0x33;
  AUX_Ctrl.buffer[3] = 0x00;
  AUX_Ctrl.buffer[4] = 0x00;
  AUX_Ctrl.buffer[5] = 0xEF;

  AUX_Ctrl.buffer[3] =  data;
  AUX_Ctrl.buffer[4] = (AUX_Ctrl.buffer[1]^AUX_Ctrl.buffer[2]^AUX_Ctrl.buffer[3]);

  if(option == Option_MP3)
  {
    Choice_MP3();
    HAL_UART_Transmit(&AUX_UART,&AUX_Ctrl.buffer[0],6,100);
  }
  else
  {
    Choice_Voice();
    HAL_UART_Transmit(&AUX_UART,&AUX_Ctrl.buffer[0],6,100);
  }
}

/*
********************************************************************************
* 函数名: void Set_VOL_AUX(unsigned char option,unsigned char data)
* 说  明: 设置音量
* 注  意：模块上电1秒后方能发送，使用死循环发送
* 参  数: data = 0-30
* 返回值:
* 设  计: MGQ
* 日  期: 20181017
* 修  改:
********************************************************************************
*/
void Set_VOL_AUX(unsigned char option,unsigned char data)
{
  if(data>30)
    data = 30;

  AUX_Ctrl.buffer[0] = 0x7E;
  AUX_Ctrl.buffer[1] = 0x04;
  AUX_Ctrl.buffer[2] = 0x31;
  AUX_Ctrl.buffer[3] = 0x00;
  AUX_Ctrl.buffer[4] = 0x00;
  AUX_Ctrl.buffer[5] = 0xEF;

  AUX_Ctrl.buffer[3] = data;
  AUX_Ctrl.buffer[4] = (AUX_Ctrl.buffer[1]^AUX_Ctrl.buffer[2]^AUX_Ctrl.buffer[3]);

  if(option == Option_MP3)
  {
    Choice_MP3();
    HAL_UART_Transmit(&AUX_UART,&AUX_Ctrl.buffer[0],6,100);
  }
  else
  {
    Choice_Voice();
    HAL_UART_Transmit(&AUX_UART,&AUX_Ctrl.buffer[0],6,100);
  }
}

/*
********************************************************************************
* 函数名: void Play_AUX(unsigned char option)
* 说  明: 播放
* 注  意：
* 参  数:
* 设  计: MGQ
* 日  期: 20181017
* 修  改:
********************************************************************************
*/
void Play_AUX(unsigned char option)
{
  if(AUX_Ctrl.Flag.Send)
  {
    AUX_Ctrl.pWrite->CMD[0]   = 0x7E;
    AUX_Ctrl.pWrite->CMD[1]   = 0x03;
    AUX_Ctrl.pWrite->CMD[2]   = 0x01;
    AUX_Ctrl.pWrite->CMD[3]   = 0x02;
    AUX_Ctrl.pWrite->CMD[4]   = 0xEF;
    AUX_Ctrl.pWrite->CMD_long = 5;
    AUX_Ctrl.pWrite->Option   = option;
    if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
      AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
  }
  else
  {
    AUX_Ctrl.buffer[0] = 0x7E;
    AUX_Ctrl.buffer[1] = 0x03;
    AUX_Ctrl.buffer[2] = 0x01;
    AUX_Ctrl.buffer[3] = 0x02;
    AUX_Ctrl.buffer[4] = 0xEF;
    if(option == Option_MP3)
    {
      Choice_MP3();
      if(HAL_OK != HAL_UART_Transmit_DMA(&AUX_UART,&AUX_Ctrl.buffer[0],5))
      {
        AUX_Ctrl.pWrite->CMD[0]   = AUX_Ctrl.buffer[0];
        AUX_Ctrl.pWrite->CMD[1]   = AUX_Ctrl.buffer[1];
        AUX_Ctrl.pWrite->CMD[2]   = AUX_Ctrl.buffer[2];
        AUX_Ctrl.pWrite->CMD[3]   = AUX_Ctrl.buffer[3];
        AUX_Ctrl.pWrite->CMD[4]   = AUX_Ctrl.buffer[4];
        AUX_Ctrl.pWrite->CMD_long = 5;
        AUX_Ctrl.pWrite->Option   = option;
        if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
          AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
      }
      else
      {
        AUX_Ctrl.Flag.Send        = 1;
        AUX_Ctrl.CMD_Interval_TIM = 8;
      }
    }
    else
    {
      Choice_Voice();
      if(HAL_OK != HAL_UART_Transmit_DMA(&AUX_UART,&AUX_Ctrl.buffer[0],5))
      {
        AUX_Ctrl.pWrite->CMD[0]   = AUX_Ctrl.buffer[0];
        AUX_Ctrl.pWrite->CMD[1]   = AUX_Ctrl.buffer[1];
        AUX_Ctrl.pWrite->CMD[2]   = AUX_Ctrl.buffer[2];
        AUX_Ctrl.pWrite->CMD[3]   = AUX_Ctrl.buffer[3];
        AUX_Ctrl.pWrite->CMD[4]   = AUX_Ctrl.buffer[4];
        AUX_Ctrl.pWrite->CMD_long = 5;
        AUX_Ctrl.pWrite->Option   = option;
        if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
          AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
      }
      else
      {
        AUX_Ctrl.Flag.Send        = 1;
        AUX_Ctrl.CMD_Interval_TIM = 8;
      }
    }
  }
}

/*
********************************************************************************
* 函数名: void STOP_AUX(unsigned char option)
* 说  明: 停止
* 注  意：
* 参  数:
* 返回值:
* 设  计: MGQ
* 日  期: 20181017
* 修  改:
********************************************************************************
*/
void STOP_AUX(unsigned char option)
{
  if(AUX_Ctrl.Flag.Send)
  {
    AUX_Ctrl.pWrite->CMD[0]   = 0x7E;
    AUX_Ctrl.pWrite->CMD[1]   = 0x03;
    AUX_Ctrl.pWrite->CMD[2]   = 0x0E;
    AUX_Ctrl.pWrite->CMD[3]   = 0x0D;
    AUX_Ctrl.pWrite->CMD[4]   = 0xEF;
    AUX_Ctrl.pWrite->CMD_long = 5;
    AUX_Ctrl.pWrite->Option   = option;
    if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
      AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
  }
  else
  {
    AUX_Ctrl.buffer[0] = 0x7E;
    AUX_Ctrl.buffer[1] = 0x03;
    AUX_Ctrl.buffer[2] = 0x0E;
    AUX_Ctrl.buffer[3] = 0x0D;
    AUX_Ctrl.buffer[4] = 0xEF;
    if(option == Option_MP3)
    {
      Choice_MP3();
      if(HAL_OK != HAL_UART_Transmit_DMA(&AUX_UART,&AUX_Ctrl.buffer[0],5))
      {
        AUX_Ctrl.pWrite->CMD[0]   = AUX_Ctrl.buffer[0];
        AUX_Ctrl.pWrite->CMD[1]   = AUX_Ctrl.buffer[1];
        AUX_Ctrl.pWrite->CMD[2]   = AUX_Ctrl.buffer[2];
        AUX_Ctrl.pWrite->CMD[3]   = AUX_Ctrl.buffer[3];
        AUX_Ctrl.pWrite->CMD[4]   = AUX_Ctrl.buffer[4];
        AUX_Ctrl.pWrite->CMD_long = 5;
        AUX_Ctrl.pWrite->Option   = option;
        if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
          AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
      }
      else
      {
        AUX_Ctrl.Flag.Send        = 1;
        AUX_Ctrl.CMD_Interval_TIM = Tow_CMD_Interval_Time;
      }
    }
    else
    {
      Choice_Voice();
      if(HAL_OK != HAL_UART_Transmit_DMA(&AUX_UART,&AUX_Ctrl.buffer[0],5))
      {
        AUX_Ctrl.pWrite->CMD[0]   = AUX_Ctrl.buffer[0];
        AUX_Ctrl.pWrite->CMD[1]   = AUX_Ctrl.buffer[1];
        AUX_Ctrl.pWrite->CMD[2]   = AUX_Ctrl.buffer[2];
        AUX_Ctrl.pWrite->CMD[3]   = AUX_Ctrl.buffer[3];
        AUX_Ctrl.pWrite->CMD[4]   = AUX_Ctrl.buffer[4];
        AUX_Ctrl.pWrite->CMD_long = 5;
        AUX_Ctrl.pWrite->Option   = option;
        if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
          AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
      }
      else
      {
        AUX_Ctrl.Flag.Send        = 1;
        AUX_Ctrl.CMD_Interval_TIM = Tow_CMD_Interval_Time;
      }
    }
  }
}

/*
********************************************************************************
* 函数名: void PAUSE_AUX(unsigned char option)
* 说  明: 暂停
* 注  意：
* 参  数:
* 返回值:
* 设  计: GEEK_MICHAEL
* 日  期: 20200111
* 修  改:
********************************************************************************
*/
void PAUSE_AUX(unsigned char option)
{
  if(AUX_Ctrl.Flag.Send)
  {
    AUX_Ctrl.pWrite->CMD[0]   = 0x7E;
    AUX_Ctrl.pWrite->CMD[1]   = 0x03;
    AUX_Ctrl.pWrite->CMD[2]   = 0x02;
    AUX_Ctrl.pWrite->CMD[3]   = 0x01;
    AUX_Ctrl.pWrite->CMD[4]   = 0xEF;
    AUX_Ctrl.pWrite->CMD_long = 5;
    AUX_Ctrl.pWrite->Option   = option;
    if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
      AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
  }
  else
  {
    AUX_Ctrl.buffer[0] = 0x7E;
    AUX_Ctrl.buffer[1] = 0x03;
    AUX_Ctrl.buffer[2] = 0x02;
    AUX_Ctrl.buffer[3] = 0x01;
    AUX_Ctrl.buffer[4] = 0xEF;
    if(option == Option_MP3)
    {
      Choice_MP3();
      if(HAL_OK != HAL_UART_Transmit_DMA(&AUX_UART,&AUX_Ctrl.buffer[0],5))
      {
        AUX_Ctrl.pWrite->CMD[0]   = AUX_Ctrl.buffer[0];
        AUX_Ctrl.pWrite->CMD[1]   = AUX_Ctrl.buffer[1];
        AUX_Ctrl.pWrite->CMD[2]   = AUX_Ctrl.buffer[2];
        AUX_Ctrl.pWrite->CMD[3]   = AUX_Ctrl.buffer[3];
        AUX_Ctrl.pWrite->CMD[4]   = AUX_Ctrl.buffer[4];
        AUX_Ctrl.pWrite->CMD_long = 5;
        AUX_Ctrl.pWrite->Option   = option;
        if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
          AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
      }
      else
      {
        AUX_Ctrl.Flag.Send        = 1;
        AUX_Ctrl.CMD_Interval_TIM = Tow_CMD_Interval_Time;
      }
    }
    else
    {
      Choice_Voice();
      if(HAL_OK != HAL_UART_Transmit_DMA(&AUX_UART,&AUX_Ctrl.buffer[0],5))
      {
        AUX_Ctrl.pWrite->CMD[0]   = AUX_Ctrl.buffer[0];
        AUX_Ctrl.pWrite->CMD[1]   = AUX_Ctrl.buffer[1];
        AUX_Ctrl.pWrite->CMD[2]   = AUX_Ctrl.buffer[2];
        AUX_Ctrl.pWrite->CMD[3]   = AUX_Ctrl.buffer[3];
        AUX_Ctrl.pWrite->CMD[4]   = AUX_Ctrl.buffer[4];
        AUX_Ctrl.pWrite->CMD_long = 5;
        AUX_Ctrl.pWrite->Option   = option;
        if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
          AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
      }
      else
      {
        AUX_Ctrl.Flag.Send        = 1;
        AUX_Ctrl.CMD_Interval_TIM = Tow_CMD_Interval_Time;
      }
    }
  }
}

/*
********************************************************************************
* 函数名: void Query_Play_Status(unsigned char option)
* 说  明: 查询播放状态
* 注  意：
* 参  数:
* 返回值:
* 设  计: MGQ
* 日  期: 20181017
* 修  改:
********************************************************************************
*/
void Query_Play_Status(unsigned char option)
{
  if(AUX_Ctrl.Flag.Send)
  {
    AUX_Ctrl.pWrite->CMD[0]   = 0x7E;
    AUX_Ctrl.pWrite->CMD[1]   = 0x03;
    AUX_Ctrl.pWrite->CMD[2]   = 0x0E;
    AUX_Ctrl.pWrite->CMD[3]   = 0x0D;
    AUX_Ctrl.pWrite->CMD[4]   = 0xEF;
    AUX_Ctrl.pWrite->CMD_long = 5;
    AUX_Ctrl.pWrite->Option   = option;
    if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
      AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
  }
  else
  {
    AUX_Ctrl.buffer[0] = 0x7E;
    AUX_Ctrl.buffer[1] = 0x03;
    AUX_Ctrl.buffer[2] = 0x0E;
    AUX_Ctrl.buffer[3] = 0x0D;
    AUX_Ctrl.buffer[4] = 0xEF;
    if(option == Option_MP3)
    {
      Choice_MP3();
      if(HAL_OK != HAL_UART_Transmit_DMA(&AUX_UART,&AUX_Ctrl.buffer[0],5))
      {
        AUX_Ctrl.pWrite->CMD[0]   = AUX_Ctrl.buffer[0];
        AUX_Ctrl.pWrite->CMD[1]   = AUX_Ctrl.buffer[1];
        AUX_Ctrl.pWrite->CMD[2]   = AUX_Ctrl.buffer[2];
        AUX_Ctrl.pWrite->CMD[3]   = AUX_Ctrl.buffer[3];
        AUX_Ctrl.pWrite->CMD[4]   = AUX_Ctrl.buffer[4];
        AUX_Ctrl.pWrite->CMD_long = 5;
        AUX_Ctrl.pWrite->Option   = option;
        if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
          AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
      }
      else
      {
        AUX_Ctrl.Flag.Send        = 1;
        AUX_Ctrl.CMD_Interval_TIM = Tow_CMD_Interval_Time;
      }
    }
    else
    {
      Choice_Voice();
      if(HAL_OK != HAL_UART_Transmit_DMA(&AUX_UART,&AUX_Ctrl.buffer[0],5))
      {
        AUX_Ctrl.pWrite->CMD[0]   = AUX_Ctrl.buffer[0];
        AUX_Ctrl.pWrite->CMD[1]   = AUX_Ctrl.buffer[1];
        AUX_Ctrl.pWrite->CMD[2]   = AUX_Ctrl.buffer[2];
        AUX_Ctrl.pWrite->CMD[3]   = AUX_Ctrl.buffer[3];
        AUX_Ctrl.pWrite->CMD[4]   = AUX_Ctrl.buffer[4];
        AUX_Ctrl.pWrite->CMD_long = 5;
        AUX_Ctrl.pWrite->Option   = option;
        if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
          AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
      }
      else
      {
        AUX_Ctrl.Flag.Send        = 1;
        AUX_Ctrl.CMD_Interval_TIM = Tow_CMD_Interval_Time;
      }
    }
  }
}

/*
********************************************************************************
* 函数名: void PLAY_ONE_AUX(unsigned char option,unsigned short int data)
* 说  明: 播放指定歌曲
* 注  意：
* 参  数:
* 返回值:
* 设  计: MGQ
* 日  期: 20181018
* 修  改:
********************************************************************************
*/
void PLAY_ONE_AUX(unsigned char option,unsigned short int data)
{
  if(AUX_Ctrl.Flag.Send)
  {
    AUX_Ctrl.pWrite->CMD[0]   = 0x7E;
    AUX_Ctrl.pWrite->CMD[1]   = 0x05;
    AUX_Ctrl.pWrite->CMD[2]   = 0x41;
    AUX_Ctrl.pWrite->CMD[3]   = (unsigned char)(data>>8);
    AUX_Ctrl.pWrite->CMD[4]   = (unsigned char)(data>>0);
    AUX_Ctrl.pWrite->CMD[5]   = (AUX_Ctrl.pWrite->CMD[1]^AUX_Ctrl.pWrite->CMD[2]^AUX_Ctrl.pWrite->CMD[3]^AUX_Ctrl.pWrite->CMD[4]);
    AUX_Ctrl.pWrite->CMD[6]   = 0xEF;
    AUX_Ctrl.pWrite->CMD_long = 7;
    AUX_Ctrl.pWrite->Option   = option;
    if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
      AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
  }
  else
  {
    AUX_Ctrl.buffer[0] = 0x7E;
    AUX_Ctrl.buffer[1] = 0x05;
    AUX_Ctrl.buffer[2] = 0x41;
    AUX_Ctrl.buffer[3] = 0x00;
    AUX_Ctrl.buffer[4] = 0x00;
    AUX_Ctrl.buffer[5] = 0x00;
    AUX_Ctrl.buffer[6] = 0xEF;

    AUX_Ctrl.buffer[3] = (unsigned char)(data>>8);
    AUX_Ctrl.buffer[4] = (unsigned char)(data>>0);
    AUX_Ctrl.buffer[5] = (AUX_Ctrl.buffer[1]^AUX_Ctrl.buffer[2]^AUX_Ctrl.buffer[3]^AUX_Ctrl.buffer[4]);
    if(option == Option_MP3)
    {
      Choice_MP3();
      if(HAL_OK != HAL_UART_Transmit_DMA(&AUX_UART,&AUX_Ctrl.buffer[0],7))
      {
        AUX_Ctrl.pWrite->CMD[0]   = AUX_Ctrl.buffer[0];
        AUX_Ctrl.pWrite->CMD[1]   = AUX_Ctrl.buffer[1];
        AUX_Ctrl.pWrite->CMD[2]   = AUX_Ctrl.buffer[2];
        AUX_Ctrl.pWrite->CMD[3]   = AUX_Ctrl.buffer[3];
        AUX_Ctrl.pWrite->CMD[4]   = AUX_Ctrl.buffer[4];
        AUX_Ctrl.pWrite->CMD[5]   = AUX_Ctrl.buffer[5];
        AUX_Ctrl.pWrite->CMD[6]   = AUX_Ctrl.buffer[6];
        AUX_Ctrl.pWrite->CMD_long = 7;
        AUX_Ctrl.pWrite->Option   = option;
        if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
          AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
      }
      else
      {
        AUX_Ctrl.Flag.Send        = 1;
        AUX_Ctrl.CMD_Interval_TIM = Tow_CMD_Interval_Time;
      }
    }
    else
    {
      Choice_Voice();
      if(HAL_OK != HAL_UART_Transmit_IT(&AUX_UART,&AUX_Ctrl.buffer[0],7))
      {
        AUX_Ctrl.pWrite->CMD[0]   = AUX_Ctrl.buffer[0];
        AUX_Ctrl.pWrite->CMD[1]   = AUX_Ctrl.buffer[1];
        AUX_Ctrl.pWrite->CMD[2]   = AUX_Ctrl.buffer[2];
        AUX_Ctrl.pWrite->CMD[3]   = AUX_Ctrl.buffer[3];
        AUX_Ctrl.pWrite->CMD[4]   = AUX_Ctrl.buffer[4];
        AUX_Ctrl.pWrite->CMD[5]   = AUX_Ctrl.buffer[5];
        AUX_Ctrl.pWrite->CMD[6]   = AUX_Ctrl.buffer[6];
        AUX_Ctrl.pWrite->CMD_long = 7;
        AUX_Ctrl.pWrite->Option   = option;
        if(++AUX_Ctrl.pWrite == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
          AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
      }
      else
      {
        AUX_Ctrl.Flag.Send        = 1;
        AUX_Ctrl.CMD_Interval_TIM = Tow_CMD_Interval_Time;
      }
    }
  }
}




/*
********************************************************************************
* 函数名: void Scan_AUX_Ctrl(void)
* 说  明: 音乐扫描函数
* 注  意：
* 参  数:
* 返回值:
* 设  计: MGQ
* 日  期: 20181017
* 修  改:
********************************************************************************
*/
void Scan_AUX_Ctrl(void)
{
  //发送命令间隔时间
  if(AUX_Ctrl.CMD_Interval_TIM)
  {
    AUX_Ctrl.CMD_Interval_TIM--;
  }
  else
  {
    AUX_Ctrl.Flag.Send = 0;
  }
  //接收处理
  if(AUX_UART_Ctrl.VD_Timeout)
  {
    AUX_UART_Ctrl.VD_Timeout--;
  }

  //发送命令缓冲处理
  if(!AUX_Ctrl.Flag.Send)
  {
    if(AUX_Ctrl.pRead != AUX_Ctrl.pWrite)
    {
      if(AUX_Ctrl.pRead->Option)
      {
        Choice_MP3();
        if(HAL_OK == HAL_UART_Transmit_DMA(&AUX_UART,&AUX_Ctrl.pRead->CMD[0],AUX_Ctrl.pRead->CMD_long))
        {
          AUX_Ctrl.Flag.Send        = 1;
          AUX_Ctrl.CMD_Interval_TIM = Tow_CMD_Interval_Time;
          AUX_Ctrl.CMD_Send_Counter = 0;
          if(++AUX_Ctrl.pRead == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
            AUX_Ctrl.pRead = &AUX_Ctrl.CMD_Buffer[0];
        }
        else
        {
          AUX_Ctrl.CMD_Send_Counter++;
          if(AUX_Ctrl.CMD_Send_Counter >10)
          {
            AUX_Ctrl.CMD_Send_Counter = 0;
            AUX_Ctrl.ERR.MP3_COMM_ERR = 1;
            if(++AUX_Ctrl.pRead == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
              AUX_Ctrl.pRead = &AUX_Ctrl.CMD_Buffer[0];
          }
        }
      }
      else
      {
        Choice_Voice();
        if(HAL_OK == HAL_UART_Transmit_DMA(&AUX_UART,&AUX_Ctrl.pRead->CMD[0],AUX_Ctrl.pRead->CMD_long))
        {
          AUX_Ctrl.Flag.Send        = 1;
          AUX_Ctrl.CMD_Interval_TIM = Tow_CMD_Interval_Time;
          AUX_Ctrl.CMD_Send_Counter = 0;
          if(++AUX_Ctrl.pRead == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
            AUX_Ctrl.pRead = &AUX_Ctrl.CMD_Buffer[0];
        }
        else
        {
          AUX_Ctrl.CMD_Send_Counter++;
          if(AUX_Ctrl.CMD_Send_Counter >10)
          {
            AUX_Ctrl.CMD_Send_Counter = 0;
            AUX_Ctrl.ERR.Voice_COMM_ERR = 1;
            if(++AUX_Ctrl.pRead == &AUX_Ctrl.CMD_Buffer[AUX_Buffer_szie])
              AUX_Ctrl.pRead = &AUX_Ctrl.CMD_Buffer[0];
          }
        }
      }
    }
  }
  //播放状态IO扫描
  if(Valid_LEV_H == MP3_State)
  {
    if(!MP3_Input.Flag.Filter)
    {
      MP3_Input.FilterCounter <<= 1;
      if(MP3_Input.FilterCounter == 0)
      {
        MP3_Input.Flag.Filter = 1;
        MP3_Input.Flag.Event  = 1;
        MP3_Input.Flag.Valid  = 1;
      }
    }
    else
    {
      MP3_Input.FilterCounter = Filter_40ms_Time;
    }
  }
  else
  {
    if(MP3_Input.Flag.Filter)
    {
      MP3_Input.FilterCounter <<= 1;
      if(MP3_Input.FilterCounter == 0)
      {
        MP3_Input.Flag.Filter = 0;
        MP3_Input.Flag.Event  = 1;
      }
    }
    else
    {
      MP3_Input.FilterCounter = Filter_40ms_Time;
    }
  }

  if(Valid_LEV_H == Voice_State)
  {
    if(!Voice_Input.Flag.Filter)
    {
      Voice_Input.FilterCounter <<= 1;
      if(Voice_Input.FilterCounter == 0)
      {
        Voice_Input.Flag.Filter = 1;
        Voice_Input.Flag.Event  = 1;
        Voice_Input.Flag.Valid  = 1;
      }
    }
    else
    {
      Voice_Input.FilterCounter = Filter_40ms_Time;
    }
  }
  else
  {
    if(Voice_Input.Flag.Filter)
    {
      Voice_Input.FilterCounter <<= 1;
      if(Voice_Input.FilterCounter == 0)
      {
        Voice_Input.Flag.Filter = 0;
        Voice_Input.Flag.Event  = 1;
      }
    }
    else
    {
      Voice_Input.FilterCounter = Filter_40ms_Time;
    }
  }
}

/*
********************************************************************************
* 函数名: void Init_AUX_Struct(void)
* 说  明: 初始化音乐结构体
* 注  意：
* 参  数:
* 返回值:
* 设  计: MGQ
* 日  期: 20181018
* 修  改:
********************************************************************************
*/
void Init_AUX_Struct(void)
{
  AUX_Ctrl.pRead = &AUX_Ctrl.CMD_Buffer[0];
  AUX_Ctrl.pWrite = &AUX_Ctrl.CMD_Buffer[0];
  AUX_Ctrl.Flag.Byte = 0;
  AUX_Ctrl.ERR.Byte  = 0;
  AUX_Ctrl.CMD_Interval_TIM = 0;
  AUX_Ctrl.CMD_Send_Counter = 0;

  MP3_Input.FilterCounter   = 0xF0;
  MP3_Input.Flag.Byte       = 0x00;

  Voice_Input.FilterCounter = 0xF0;
  Voice_Input.Flag.Byte     = 0x00;

}

/*
********************************************************************************
* 函数名: void AUX_COMM_Dispose(unsigned char data)
* 说  明: 音乐通讯处理
* 注  意：等有时间在写
* 参  数:
* 返回值:
* 设  计: MGQ
* 日  期: 20181018
* 修  改:
********************************************************************************
*/
void AUX_COMM_Dispose(unsigned char data)
{
  if(!AUX_UART_Ctrl.VD_Timeout)
  {
    AUX_UART_Ctrl.VD_State = 0;
  }

  if(AUX_UART_Ctrl.VD_State == 0)
  {
    /*'o'*/
    if(data == 0x4F)
    {
      AUX_UART_Ctrl.VD_State = 1;
      AUX_UART_Ctrl.VD_Timeout = 10;
    }
  }
  else if(AUX_UART_Ctrl.VD_State == 1)
  {
    /*'k'*/
    if(data == 0x4B)
    {
      AUX_Ctrl.Flag.OK = 1;
    }
    AUX_UART_Ctrl.VD_State = 0;
  }
}