#ifndef __RTT_Tartget_System_State_H
#define __RTT_Tartget_System_State_H

/* 空闲任务定义 */
#define FREE_TASK_PRIO 8              /* 任务优先级         */
#define FREE_TASK_STK_SIZE 128        /* 任务堆栈大小       */
//extern TaskHandle_t FREE_TASK_HANDLE; /* 任务句柄           */

/* 目标板任务定义 */
#define GJR_TASK_PRIO 7              /* 任务优先级         */
#define GJR_TASK_STK_SIZE 128        /* 任务堆栈大小       */
//extern TaskHandle_t GJR_TASK_HANDLE; /* 任务句柄           */

#define setbit(x,y) x |= (1<<y) //将X的第Y位置1
#define clrbit(x,y) x &= ~(1<<y) //将X的第Y位清0
//*****************结构体*******************************//
typedef enum //系统状态
{
  SYS_Power_ON = 1, //上电       1
  SYS_IN_STATION,   //进站       2
  SYS_RUN_IDLE,     //运行空闲   3
  SYS_RUN,          //运行       4
} SYS_Enum;
typedef struct
{
  uint16_t VoiceVolume;        //音效模块音量
  uint8_t  DroneScoreWeight;  //靶标得分权重
  uint8_t  LotteryRatio;         //彩票倍率

} SYS_Ctrl_Struct;

typedef struct
{
  uint8_t Target_ID; //目标ID
  
  /* 上报CVCS系统异常标志(1=异常) */
  union {
    __IO uint16_t Word;
    struct
    {
      __IO uint16_t Master_SWITCH_Dial : 1;       //主控拨码异常
      __IO uint16_t MP3 : 1;                      //MP3模块异常
      __IO uint16_t Drone_NO1 : 1;                //靶标1异常
      __IO uint16_t Drone_NO2 : 1;                //靶标2异常
      __IO uint16_t Drone_NO3 : 1;                //靶标3异常
      __IO uint16_t Drone_NO4 : 1;                //靶标4异常
      __IO uint16_t Drone_NO5 : 1;                //靶标5异常
      __IO uint16_t Drone_NO6 : 1;                //靶标6异常
      __IO uint16_t Drone_NO7 : 1;                //靶标7异常
      __IO uint16_t Drone_NO8 : 1;                //靶标8异常
    };
  } ERR_Flag;

  union {
    __IO uint32_t Word;
    struct
    {
      __IO uint32_t Write_Flash : 1; //写Flash标志
    };
  } Flag;

  uint32_t State_Time;              //系统状态时间
  uint8_t  TargetTestStart;         //目标测试开始
  uint8_t  TargetTestOver;          //目标测试结束
  uint8_t  TargetTest_State_Time;   //目标测试状态时间
  uint16_t ReactInteractionTime;    //感应互动时间
  uint8_t  ReactInteractionFlag;    //感应互动标志位
  
} SYS_Run_Struct;

//******************声明外部变量************************//
extern SYS_Enum SYSTEM_STATE;                 //系统运行状态
extern SYS_Ctrl_Struct SYSTEN_CTRL_PARAMETER; //系统控制参数
extern SYS_Run_Struct SYSTEN_RUN_PARAMETER;   //系统运行参数

//******************函数原型****************************//
void Init_SYS_Ctrl_Struct(void);
void Init_System_Work(void);
void System_Power_ON(void); //1

void FREE_TASK_CTRL(void *pvParameters);

void ResetLastTargetTest_Results(void);
#endif //Battery_Car_System_State.h