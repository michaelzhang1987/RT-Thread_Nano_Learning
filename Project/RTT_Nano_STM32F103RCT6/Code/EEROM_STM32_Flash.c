/*******************************************************************************
                                包含头文件
*******************************************************************************/
#include "RTT_Nano_Include.h"


/*******************************************************************************
                                全局变量
*******************************************************************************/


/*
********************************************************************************
* 函数名: unsigned short int Read_Short_Int_Data(unsigned int Addr)
* 说  明: 读取指定地址的16位数据
* 注  意：
* 参  数:
* 返回值:
* 设  计: MGQ
* 日  期: 20181022
* 修  改:
********************************************************************************
*/
unsigned short int Read_Short_Int_Data(unsigned int Addr)
{
  unsigned short int data = 0;
  data = *(volatile unsigned short*)Addr;
  return data;
}

/*
********************************************************************************
* 函数名: void Write_Short_SYS_Data(void)
* 说  明: 写入系统参数
* 注  意：length不能大于50
* 参  数:
* 返回值:
* 设  计: MGQ
* 日  期: 20181022
* 修  改:
********************************************************************************
*/
void Write_Short_SYS_Data(unsigned short int *pData,unsigned short int length)
{
  FLASH_EraseInitTypeDef EraseInitStruct;               //擦除结构体
  unsigned short int i=0;
  unsigned char time=0;
  unsigned int PageError;
  unsigned short int buffer[50];
  for(i=0;i<length;i++)
  {
    buffer[i] = *pData;
    pData++;
  }
  while(time<5)
  {
    //解锁flash写
    HAL_FLASH_Unlock();
    //擦除扇区
    EraseInitStruct.TypeErase     = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress   = FLSASH_BASE;
    EraseInitStruct.NbPages       = 1;
    HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
    //写入一个扇区的数据
    for(i=0;i<length;i++)
    {
      HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLSASH_BASE+(i<<1),buffer[i]);
    }
    //锁定flash
    HAL_FLASH_Lock();
    //写入校验
    for(i=0;i<length;i++)
    {
      if(buffer[i]!=Read_Short_Int_Data(FLSASH_BASE+(i<<1)))
      {
        break;
      }
    }
    //校验成功
    if(i == length)
    {
      time = 5;
    }
    else
    {
      time++;
    }
  }
}