#ifndef __Rail_Car_Master_MP3_H
#define __Rail_Car_Master_MP3_H


//播放器使用串口号
#define  AUX_UART           huart1

//播放器发送缓冲大小
#define  AUX_Buffer_szie    10

//播放器通信IO控制口
#define  MP3_SWITCH1_ON     HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_SET)
#define  MP3_SWITCH1_Off    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_RESET)
#define  MP3_SWITCH2_ON     HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_SET)
#define  MP3_SWITCH2_Off    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_RESET)
#define  Choice_MP3()       {MP3_SWITCH1_ON;MP3_SWITCH2_Off;}
#define  Choice_Voice()     {MP3_SWITCH1_Off;MP3_SWITCH2_Off;}

//播放器状态IO口
#define  MP3_State          HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)
#define  Voice_State        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)

//选择音频模块
#define  Option_MP3         1
#define  Option_Voice       0


//两次命令间隔时间(基于10ms定时器)
#define  Tow_CMD_Interval_Time   10   //原为8 发送间隔时间不够 扩大到15

//*********************************结构体************************************//
typedef struct
{
  unsigned  char CMD[10];        //命令
  unsigned char CMD_long;        //命令长度
  unsigned char Option;          //模块选择
}CMD_AUX_Struct;


typedef struct
{
  union                          // 状态标志位
  {
    volatile unsigned char Byte;
    struct
    {
      unsigned char MP3_AllReady     :1;   // MP3模块正常状态
      unsigned char Voice_AllReady   :1;   // 语音模块正常状态
      unsigned char Send             :1;   // 串口数据发送完成状态
      unsigned char OK               :1;   // 串口接到OK指令
    };
  }Flag;

  union                          // 错误标志位
  {
    volatile unsigned char Byte;
    struct
    {
      unsigned char MP3_NO_TF       :1;   // MP3模块没有检测到TF卡
      unsigned char MP3_COMM_ERR    :1;   // MP3模块通讯异常
      unsigned char Voice_COMM_ERR  :1;   // 语音模块通讯异常
    };
  }ERR;

  unsigned char buffer[10];               //中间缓冲区
  unsigned char CMD_Interval_TIM;         //命令间隔时间
  unsigned char CMD_Send_Counter;         //发送名称超时计数
  CMD_AUX_Struct *pRead;
  CMD_AUX_Struct *pWrite;
  CMD_AUX_Struct CMD_Buffer[AUX_Buffer_szie];

}AUX_Struct;

//******************声明外部变量******************//
extern AUX_Struct AUX_Ctrl;
extern MGQ_UART AUX_UART_Ctrl;
extern SWITCH_INPUT MP3_Input,Voice_Input;

//********************函数原型********************//
void Set_mode_AUX(unsigned char option,unsigned char data);
void Set_VOL_AUX(unsigned char option,unsigned char data);
void Play_AUX(unsigned char option);
void STOP_AUX(unsigned char option);
void PAUSE_AUX(unsigned char option);
void Query_Play_Status(unsigned char option);
void PLAY_ONE_AUX(unsigned char option,unsigned short int data);
void Scan_AUX_Ctrl(void);
void Init_AUX_Struct(void);
void AUX_COMM_Dispose(unsigned char data);

#endif //Battery_Car_MP3.h