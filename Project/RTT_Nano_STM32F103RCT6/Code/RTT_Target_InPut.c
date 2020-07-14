/*******************************************************************************
                                包含头文件
*******************************************************************************/
#include "RTT_Nano_Include.h"

/*******************************************************************************
                                全局变量
*******************************************************************************/

SWITCH_INPUT Key1,Key2,Key3,Key4,Key5,Key6;


/*
********************************************************************************
* 函数名: void Init_InPut_Struct(void)
* 说  明: 初始化输入结构体
* 注  意：
* 参  数:
* 返回值:
* 设  计: MGQ
* 日  期: 20181016
* 修  改:
********************************************************************************
*/
void Init_InPut_Struct(void)
{
  Key1.FilterCounter = Filter_40ms_Time;
  Key1.Flag.Byte     = 0;
  Key2.FilterCounter = Filter_40ms_Time;
  Key2.Flag.Byte     = 0;
  Key3.FilterCounter = Filter_40ms_Time;
  Key3.Flag.Byte     = 0;
  Key4.FilterCounter = Filter_40ms_Time;
  Key4.Flag.Byte     = 0;
  Key5.FilterCounter = Filter_40ms_Time;
  Key5.Flag.Byte     = 0;
  Key6.FilterCounter = Filter_80ms_Time;
  Key6.Flag.Byte     = 0;
}

/*
********************************************************************************
* 函数名: void Scan_InPut(void)
* 说  明: 扫描输入函数
* 注  意：
* 参  数:
* 返回值:
* 设  计: MGQ
* 日  期: 20181016
* 修  改:
********************************************************************************
*/
void Scan_InPut(void)
{
  //if KEY1按键扫描
  if(Valid_LEV_L == Key1_LEV)
  {
    if(!Key1.Flag.Filter)
    {
      Key1.FilterCounter <<= 1;
      if(Key1.FilterCounter == 0)
      {
        Key1.Flag.Filter = 1;
        Key1.Flag.Event = 1;
        Key1.Flag.Valid = 1;
      }
    }
    else
    {
      Key1.FilterCounter = Filter_40ms_Time;
    }
  }
  else
  {
    if(Key1.Flag.Filter)
    {
      Key1.FilterCounter <<= 1;
      if(Key1.FilterCounter == 0)
      {
        Key1.Flag.Filter = 0;
        Key1.Flag.Event = 1;
      }
    }
    else
    {
      Key1.FilterCounter = Filter_40ms_Time;
    }
  }
  //end KEY1按键扫描

  //if KEY2按键扫描
  if(Valid_LEV_L == Key2_LEV)
  {
    if(!Key2.Flag.Filter)
    {
      Key2.FilterCounter <<= 1;
      if(Key2.FilterCounter == 0)
      {
        Key2.Flag.Filter = 1;
        Key2.Flag.Event = 1;
        Key2.Flag.Valid = 1;
      }
    }
    else
    {
      Key2.FilterCounter = Filter_40ms_Time;
    }
  }
  else
  {
    if(Key2.Flag.Filter)
    {
      Key2.FilterCounter <<= 1;
      if(Key2.FilterCounter == 0)
      {
        Key2.Flag.Filter = 0;
        Key2.Flag.Event = 1;
      }
    }
    else
    {
      Key2.FilterCounter = Filter_40ms_Time;
    }
  }
  //end KEY2按键扫描

  //if KEY3按键扫描
  if(Valid_LEV_L == Key3_LEV)
  {
    if(!Key3.Flag.Filter)
    {
      Key3.FilterCounter <<= 1;
      if(Key3.FilterCounter == 0)
      {
        Key3.Flag.Filter = 1;
        Key3.Flag.Event = 1;
        Key3.Flag.Valid = 1;
      }
    }
    else
    {
      Key3.FilterCounter = Filter_40ms_Time;
    }
  }
  else
  {
    if(Key3.Flag.Filter)
    {
      Key3.FilterCounter <<= 1;
      if(Key3.FilterCounter == 0)
      {
        Key3.Flag.Filter = 0;
        Key3.Flag.Event = 1;
      }
    }
    else
    {
      Key3.FilterCounter = Filter_40ms_Time;
    }
  }
  //end KEY3按键扫描

  //if KEY4按键扫描
  if(Valid_LEV_L == Key4_LEV)
  {
    if(!Key4.Flag.Filter)
    {
      Key4.FilterCounter <<= 1;
      if(Key4.FilterCounter == 0)
      {
        Key4.Flag.Filter = 1;
        Key4.Flag.Event = 1;
        Key4.Flag.Valid = 1;
      }
    }
    else
    {
      Key4.FilterCounter = Filter_40ms_Time;
    }
  }
  else
  {
    if(Key4.Flag.Filter)
    {
      Key4.FilterCounter <<= 1;
      if(Key4.FilterCounter == 0)
      {
        Key4.Flag.Filter = 0;
        Key4.Flag.Event = 1;
      }
    }
    else
    {
      Key4.FilterCounter = Filter_40ms_Time;
    }
  }
  //end KEY4按键扫描

  //if KEY5按键扫描
  if(Valid_LEV_L == Key5_LEV)
  {
    if(!Key5.Flag.Filter)
    {
      Key5.FilterCounter <<= 1;
      if(Key5.FilterCounter == 0)
      {
        Key5.Flag.Filter = 1;
        Key5.Flag.Event = 1;
        Key5.Flag.Valid = 1;
      }
    }
    else
    {
      Key5.FilterCounter = Filter_40ms_Time;
    }
  }
  else
  {
    if(Key5.Flag.Filter)
    {
      Key5.FilterCounter <<= 1;
      if(Key5.FilterCounter == 0)
      {
        Key5.Flag.Filter = 0;
        Key5.Flag.Event = 1;
      }
    }
    else
    {
      Key5.FilterCounter = Filter_40ms_Time;
    }
  }
  //end KEY5按键扫描

  //if KEY6按键扫描
  if(Valid_LEV_L == Key6_LEV)
  {
    if(!Key6.Flag.Filter)
    {
      Key6.FilterCounter <<= 1;
      if(Key6.FilterCounter == 0)
      {
        Key6.Flag.Filter = 1;
        Key6.Flag.Event = 1;
        Key6.Flag.Valid = 1;
      }
    }
    else
    {
      Key6.FilterCounter = Filter_80ms_Time;
    }
  }
  else
  {
    if(Key6.Flag.Filter)
    {
      Key6.FilterCounter <<= 1;
      if(Key6.FilterCounter == 0)
      {
        Key6.Flag.Filter = 0;
        Key6.Flag.Event = 1;
      }
    }
    else
    {
      Key6.FilterCounter = Filter_80ms_Time;
    }
  }
  //end KEY6按键扫描
}

unsigned char READ_DIAL_ADDRESS(void)
{
  unsigned char i = 0;

  if(ADDRESS_DIAL_1 == Valid_LEV_L)
  {
    i |= 1;
  }
  if(ADDRESS_DIAL_2 == Valid_LEV_L)
  {
    i |= 2;
  }
  if(ADDRESS_DIAL_3 == Valid_LEV_L)
  {
    i |= 4;
  }
  if(ADDRESS_DIAL_4 == Valid_LEV_L)
  {
    i |= 8;
  }
  if(ADDRESS_DIAL_5 == Valid_LEV_L)
  {
    i |= 16;
  }
  if(ADDRESS_DIAL_6 == Valid_LEV_L)
  {
    i |= 32;
  }
  if(ADDRESS_DIAL_7 == Valid_LEV_L)
  {
    i |= 64;
  }
  if(ADDRESS_DIAL_8 == Valid_LEV_L)
  {
    i |= 128;
  }
  return i;
}

//读取座舱内部地址编码
unsigned char READ_CABIN_INTERADDR(void)
{
  unsigned char CabinID = 0;
  if(ADDRESS_DIAL_8 == Valid_LEV_L)
  {
    CabinID = 2; //A座舱
  }
  else
  {
    CabinID = 1; //B座舱
  }
  return CabinID;
}