#ifndef __RTT_Tartget_OutPut_H
#define __RTT_Tartget_OutPut_H

#define OUT1_PWMON(pwm)                   __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,pwm);//设置通道2--PWM占空比
#define OUT1_OFF()                        __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,0);//设置通道2--PWM占空比
#define OUT2_PWMON(pwm)                   __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,pwm);//设置通道1--PWM占空比
#define OUT2_OFF()                        __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_1,0);//设置通道1--PWM占空比
#define OUT3_PWMON(pwm)                   __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,pwm);//设置通道4--PWM占空比
#define OUT3_OFF()                        __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,0);//设置通道4--PWM占空比
#define OUT4_PWMON(pwm)                   __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,pwm);//设置通道3--PWM占空比
#define OUT4_OFF()                        __HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,0);//设置通道3--PWM占空比
#define OUT5_PWMON(pwm)                   __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,pwm);//设置通道2--PWM占空比
#define OUT5_OFF()                        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);//设置通道2--PWM占空比
#define OUT6_PWMON(pwm)                   __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,pwm);//设置通道1--PWM占空比
#define OUT6_OFF()                        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);//设置通道1--PWM占空比
#define OUT7_PWMON(pwm)                   __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,pwm);//设置通道4--PWM占空比
#define OUT7_OFF()                        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);//设置通道4--PWM占空比
#define OUT8_PWMON(pwm)                   __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,pwm);//设置通道3--PWM占空比
#define OUT8_OFF()                        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,0);//设置通道3--PWM占空比

#define LED_ON()                          HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET)
#define LED_OFF()                         HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET)
#define LED_ROLLOVER()                    HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_15)

#define RELAY_ON()                          HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET)
#define RELAY_OFF()                         HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET)
/* 输出任务定义 */
//#define OUT_TASK_PRIO               8                   /* 任务优先级         */
//#define OUT_TASK_STK_SIZE           128                 /* 任务堆栈大小 字 4个字节 */
//extern TaskHandle_t                 OUT_TASK_HANDLE;    /* 任务句柄           */

//*****************结构体****************//
typedef struct
{

  union                          // 状态标志位
  {
    __IO uint8_t Byte;
    struct
    {
      uint8_t Enable           :1;   // 输出使能
      uint8_t Wheel_Light      :2;   // 车轮灯控制0=关闭1=常亮2=旋转
    };
  }Flag;
  uint8_t State;
  uint16_t PWM_ON;
}OUtPUT_Ctrl_Struct;

//******************声明外部变量******************//
extern OUtPUT_Ctrl_Struct OUtPUT_Ctrl;

//********************函数原型********************//
void Scan_Ctrl_RunLight(void);

void OUTPUT_TASK_CTRL(void *pvParameters);
#endif