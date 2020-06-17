/*******************************************************************************
                                包含头文件
*******************************************************************************/
#include "RTT_Nano_Include.h"

/*******************************************************************************
                                全局变量
*******************************************************************************/

/*
***************************************************************************************************
* 函数名: void Scan_Ctrl_RunLight(void)
* 说  明: 运行指示灯控制
* 参  数:
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20181030
* 修  改:
***************************************************************************************************
*/
//void Scan_Ctrl_RunLight(void)
//{
//  switch (SYSTEM_STATE)
//  {
//  case SYS_Power_ON:
//    LED_ON();
//    break;
//  case SYS_IN_STATION:
//    if (Sys_time.Flag.RunLight_SYS_IN_STATION)
//    {
//      Sys_time.Flag.RunLight_SYS_IN_STATION = 0;
//      LED_ROLLOVER();
//    }
//    break;
//  case SYS_RUN_IDLE:
//    if (Sys_time.Flag.RunLight_SYS_RUN_IDLE)
//    {
//      Sys_time.Flag.RunLight_SYS_RUN_IDLE = 0;
//      LED_ROLLOVER();
//    }
//    break;
//  case SYS_RUN:
//    if (Sys_time.Flag.RunLight_SYS_RUN)
//    {
//      Sys_time.Flag.RunLight_SYS_RUN = 0;
//      LED_ROLLOVER();
//    }
//    break;
//  }
//}

void OUTPUT_TASK_CTRL(void *pvParameters)
{
//  HAL_TIM_Base_Start(&htim8);
//  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, 0); //设置通道1--PWM占空比
//  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, 0); //设置通道2--PWM占空比
//  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 0); //设置通道3--PWM占空比
//  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, 0); //设置通道4--PWM占空比
//  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);        //启动通道3
//  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);        //启动通道4
//  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);        //启动通道3
//  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);        //启动通道4
//
//  HAL_TIM_Base_Start(&htim1);
//  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0); //设置通道1--PWM占空比
//  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0); //设置通道2--PWM占空比
//  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0); //设置通道3--PWM占空比
//  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0); //设置通道4--PWM占空比
//  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);        //启动通道3
//  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);        //启动通道4
//  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);        //启动通道3
//  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);        //启动通道4
  while (1)
  {
    LED_ON();

    LED_OFF();

  }
}
