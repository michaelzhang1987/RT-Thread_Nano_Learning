#ifndef __EEROM_STM32_Flash_H
#define __EEROM_STM32_Flash_H

//*****************Flash地址定义*******************************//
#define FLASH_SIZE           512

#if     FLASH_SIZE     ==    512
#define FLSASH_BASE          0x0807F800
#define FLSASH_PAGE          1024

#elif   FLASH_SIZE     ==    256
#define FLSASH_BASE          0x0803F800
#define FLSASH_PAGE          1024

#elif   FLASH_SIZE     ==    128
#define FLSASH_BASE          0x0801FC00
#define FLSASH_PAGE          512

#elif   FLASH_SIZE     ==    32
#define FLSASH_BASE          0x08007C00
#define FLSASH_PAGE          512
#endif

#define SYS_CTRL_NUMBER      3
//*****************系统参数地址定义*******************************//

#define  SYS_CTRL_VoiceVolume                FLSASH_BASE     //音效模块音量
#define  SYS_CTRL_DroneScoreWeight          (FLSASH_BASE+2)  //靶标得分权重
#define  SYS_CTRL_LotteryRatio              (FLSASH_BASE+4)  //彩票倍率

//*****************系统参数范围定义*******************************//
#define  SYS_CTRL_VoiceVolume_Max       30
#define  SYS_CTRL_VoiceVolume_DEF       20
#define  SYS_CTRL_VoiceVolume_Min       0

#define  SYS_CTRL_DroneScoreWeight_Max       255
#define  SYS_CTRL_DroneScoreWeight_DEF       10
#define  SYS_CTRL_DroneScoreWeight_Min       0

#define  SYS_CTRL_LotteryRatio_Max       255
#define  SYS_CTRL_LotteryRatio_DEF       20
#define  SYS_CTRL_LotteryRatio_Min       10

//******************函数原型****************************//
unsigned short int Read_Short_Int_Data(unsigned int Addr);
void Write_Short_SYS_Data(unsigned short int *pData,unsigned short int length);

#endif //EEROM_STM32_Flash.h