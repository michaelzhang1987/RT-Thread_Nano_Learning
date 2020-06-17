// /*******************************************************************************
                                // 包含头文件
// *******************************************************************************/
// #include "RTT_Nano_Include.h"

// /*******************************************************************************
                                // 全局变量
// *******************************************************************************/
// SYS_Enum SYSTEM_STATE;                 //系统运行状态
// SYS_Ctrl_Struct SYSTEN_CTRL_PARAMETER; //系统控制参数
// SYS_Run_Struct SYSTEN_RUN_PARAMETER;   //系统运行参数
// SYS_Enum SYSTEM_STATE_Will;            //行走系统运行状态

// TaskHandle_t FREE_TASK_HANDLE;
// TaskHandle_t GJR_TASK_HANDLE; /* 任务句柄           */
// /*
// ********************************************************************************
// * 函数名: void Init_SYS_Ctrl_Struct(void)
// * 说  明: 初始化系统控制参数
// * 参  数: N/A
// * 返回值: N/A
// * 设  计: MGQ
// * 日  期: 20181020
// * 修  改:
// ********************************************************************************
// */
// void Init_SYS_Ctrl_Struct(void)
// {
  // unsigned char i = 0;
  // //音效模块音量
  // SYSTEN_CTRL_PARAMETER.VoiceVolume = Read_Short_Int_Data(SYS_CTRL_VoiceVolume);
  // if (SYSTEN_CTRL_PARAMETER.VoiceVolume > SYS_CTRL_VoiceVolume_Max)
  // {
    // SYSTEN_CTRL_PARAMETER.VoiceVolume = SYS_CTRL_VoiceVolume_DEF;
    // i++;
  // }
  
    // //靶标得分权重
  // SYSTEN_CTRL_PARAMETER.DroneScoreWeight = Read_Short_Int_Data(SYS_CTRL_DroneScoreWeight);
  // if (SYSTEN_CTRL_PARAMETER.DroneScoreWeight >= SYS_CTRL_DroneScoreWeight_Max)
  // {
    // SYSTEN_CTRL_PARAMETER.DroneScoreWeight = SYS_CTRL_DroneScoreWeight_DEF;
    // i++;
  // }
  
    // //彩票倍率
  // SYSTEN_CTRL_PARAMETER.LotteryRatio = Read_Short_Int_Data(SYS_CTRL_LotteryRatio);
  // if (SYSTEN_CTRL_PARAMETER.LotteryRatio >= SYS_CTRL_LotteryRatio_Max)
  // {
    // SYSTEN_CTRL_PARAMETER.LotteryRatio = SYS_CTRL_LotteryRatio_DEF;
    // i++;
  // }

  // //写入Flash
  // if (i)
  // {
    // Write_Short_SYS_Data(&SYSTEN_CTRL_PARAMETER.VoiceVolume, SYS_CTRL_NUMBER);
  // }
// }

// /*
// ********************************************************************************
// * 函数名: void Init_System_Work(void)
// * 说  明: 系统级别初始化
// * 参  数: N/A
// * 返回值: N/A
// * 设  计: MGQ
// * 日  期: 20181020
// * 修  改:
// ********************************************************************************
// */
// void Init_System_Work(void)
// {
  // /**********初始化系统控制参数*******/
  // Init_SYS_Ctrl_Struct();
  // //获取场景编号
  // SYSTEN_RUN_PARAMETER.Target_ID = READ_DIAL_ADDRESS();
  // if (SYSTEN_RUN_PARAMETER.Target_ID > 40 || SYSTEN_RUN_PARAMETER.Target_ID == 0)
  // {
    // SYSTEN_RUN_PARAMETER.Target_ID = 40;
    // SYSTEN_RUN_PARAMETER.ERR_Flag.Master_SWITCH_Dial = 1;
  // }

  // /*********初始化定时器6的1s中断***********/
  // HAL_TIM_Base_Start_IT(&htim6);

  // /***************初始化CAN***************/
  // MGQ_CAN_INIT();

  // /**********输入按键初始化结构体*******/
  // Init_InPut_Struct();

  // /*********Zigbee初始化*******/
  // Init_Zigbee_Struct();
  // Zigbee_Delay_TX_Init();
  // UART_Init_Data(&Zigbee_UART, &Zigbee_UART_Ctrl);
  // __HAL_UART_ENABLE_IT(&Zigbee_UART, UART_IT_RXNE);

  // /***********AUX初始化********/
  // UART_Init_Data(&AUX_UART, &AUX_UART_Ctrl);
  // __HAL_UART_ENABLE_IT(&AUX_UART, UART_IT_RXNE);
  // HAL_Delay(100);
  // Set_mode_AUX(Option_MP3, 4);
  // HAL_Delay(100);
  // Init_AUX_Struct();
  // PLAY_ONE_AUX(Option_MP3, 1);
  // //  /**********系统状态归零*******/
  // //  SYSTEN_RUN_PARAMETER.State_Time = 0;
  // //  SYSTEM_STATE_Will = SYS_IN_STATION;
  // CAN_Send_DroneControlCMD(1);//启动靶标
// }

// /*
// ********************************************************************************
// * 函数名: void SYS_START_TASK(void)
// * 说  明: 创建系统任务
// * 注  意：
// * 参  数:
// * 返回值:
// * 设  计: MGQ
// * 日  期: 20191012
// * 修  改:
// ********************************************************************************
// */

// void SYS_START_TASK(void)
// {
  // //  /* 创建Can发送队列 */
  // //  CAN_TX_Queue = xQueueCreate(CAN_TX_QUEUE_LENGTH,     /* 队列中有多少列      */
  // //                              CAN_TX_QUEUE_SIZE);      /* 每个列大小          */
  // //  /* 创建Uart发送队列 */
  // //  UART_TX_Queue = xQueueCreate(UART_TX_QUEUE_LENGTH,   /* 队列中有多少列      */
  // //                              UART_TX_QUEUE_SIZE);     /* 每个列大小          */
  // /* 输出控制任务 */
  // xTaskCreate((TaskFunction_t)OUTPUT_TASK_CTRL,   /* 任务函数            */
              // (const char *)"OutCtrl",            /* 任务名称            */
              // (uint16_t)OUT_TASK_STK_SIZE,        /* 任务堆栈            */
              // (void *)NULL,                       /* 传递给任务函数的参数*/
              // (UBaseType_t)OUT_TASK_PRIO,         /* 任务优先级          */
              // (TaskHandle_t *)&OUT_TASK_HANDLE);  /* 任务句柄            */
                                                  // /* 空闲任务 */
  // xTaskCreate((TaskFunction_t)FREE_TASK_CTRL,     /* 任务函数            */
              // (const char *)"SYS_FREE",           /* 任务名称            */
              // (uint16_t)FREE_TASK_STK_SIZE,       /* 任务堆栈            */
              // (void *)NULL,                       /* 传递给任务函数的参数*/
              // (UBaseType_t)FREE_TASK_PRIO,        /* 任务优先级          */
              // (TaskHandle_t *)&FREE_TASK_HANDLE); /* 任务句柄            */

  // switch (SYSTEN_RUN_PARAMETER.Target_ID)
  // {
  // /* 丛林大营救目标组 */
  // case 1:
    // xTaskCreate((TaskFunction_t)GJR_FACTORY_BOILERS_TASK_CTRL, /* 任务函数            */
                // (const char *)"GJR_FactoryBoilers",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,       /* 任务堆栈            */
                // (void *)NULL,                             /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,        /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);    /* 任务句柄            */
    // break;
  // case 2:
    // xTaskCreate((TaskFunction_t)GJR_LITTLE_HOME_TASK_CTRL, /* 任务函数            */
                // (const char *)"GJR_LittileHome",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,       /* 任务堆栈            */
                // (void *)NULL,                             /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,        /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);    /* 任务句柄            */
    // break;
  // case 3:
    // xTaskCreate((TaskFunction_t)GJR_TREE_HOUSE_TASK_CTRL, /* 任务函数            */
                // (const char *)"GJR_TreeHouse",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,         /* 任务堆栈            */
                // (void *)NULL,                               /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,          /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);      /* 任务句柄            */
    // break;
  // case 4:
    // xTaskCreate((TaskFunction_t)GJR_PULLBOW_RABBIT_TASK_CTRL, /* 任务函数            */
                // (const char *)"GJR_Pull-BowRabbit",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,         /* 任务堆栈            */
                // (void *)NULL,                               /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,          /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);      /* 任务句柄            */
    // break;
  // case 5:
    // xTaskCreate((TaskFunction_t)GJR_PELICAN_TASK_CTRL, /* 任务函数            */
                // (const char *)"GJR_Pelican",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,         /* 任务堆栈            */
                // (void *)NULL,                               /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,          /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);      /* 任务句柄            */
    // break;
  // case 6:
    // xTaskCreate((TaskFunction_t)GJR_WOLF_INVASION_TASK_CTRL, /* 任务函数            */
                // (const char *)"GJR_WolfInvasion",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,         /* 任务堆栈            */
                // (void *)NULL,                               /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,          /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);      /* 任务句柄            */
    // break;
  // case 7:
    // xTaskCreate((TaskFunction_t)GJR_BOSS_WOLF_TASK_CTRL, /* 任务函数            */
                // (const char *)"GJR_BossWolf",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,         /* 任务堆栈            */
                // (void *)NULL,                               /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,          /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);      /* 任务句柄            */
    // break;
  // case 8:
    // xTaskCreate((TaskFunction_t)GJR_THIEF_WOLF_TASK_CTRL, /* 任务函数            */
                // (const char *)"GJR_ThiefWolf",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,         /* 任务堆栈            */
                // (void *)NULL,                               /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,          /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);      /* 任务句柄            */
    // break;
  // case 9:
    // xTaskCreate((TaskFunction_t)GJR_SHAVED_WOLF_TASK_CTRL, /* 任务函数            */
                // (const char *)"GJR_ShavedWolf",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,           /* 任务堆栈            */
                // (void *)NULL,                                 /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,            /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);        /* 任务句柄            */
    // break;
  // case 10:
    // xTaskCreate((TaskFunction_t)GJR_FACTORY_WOLF_TASK_CTRL, /* 任务函数            */
                // (const char *)"GJR_FactoryWolf",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,           /* 任务堆栈            */
                // (void *)NULL,                                 /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,            /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);        /* 任务句柄            */
    // break;
  // case 11:
    // xTaskCreate((TaskFunction_t)GJR_UNLUCKY_WOLF_TASK_CTRL, /* 任务函数            */
                // (const char *)"GJR_UnluckyWolf",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,           /* 任务堆栈            */
                // (void *)NULL,                                 /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,            /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);        /* 任务句柄            */
    // break;
  // case 12:
    // xTaskCreate((TaskFunction_t)GJR_RETURN_VICTORY_TASK_CTRL, /* 任务函数            */
                // (const char *)"RturnVictory",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,           /* 任务堆栈            */
                // (void *)NULL,                                 /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,            /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);        /* 任务句柄            */
    // break;
  // case 13:
    // xTaskCreate((TaskFunction_t)GJR_FIGHT_OF_MIKE_TASK_CTRL, /* 任务函数            */
                // (const char *)"FightOfMike",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,           /* 任务堆栈            */
                // (void *)NULL,                                 /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,            /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);        /* 任务句柄            */
    // break;
  // case 14:
    // xTaskCreate((TaskFunction_t)GJR_RABBIT_GROUND_TASK_CTRL, /* 任务函数            */
                // (const char *)"RabbitGround",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,           /* 任务堆栈            */
                // (void *)NULL,                                 /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,            /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);        /* 任务句柄            */
    // break;
  // case 15:
    // xTaskCreate((TaskFunction_t)GJR_CRYSTAL_MINE_TASK_CTRL, /* 任务函数            */
                // (const char *)"CrystalMine",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,           /* 任务堆栈            */
                // (void *)NULL,                                 /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,            /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);        /* 任务句柄            */
    // break;
  // case 16:
    // xTaskCreate((TaskFunction_t)GJR_BOMB_WOLF_TASK_CTRL, /* 任务函数            */
                // (const char *)"BombWolf",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,           /* 任务堆栈            */
                // (void *)NULL,                                 /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,            /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);        /* 任务句柄            */
    // break;
  // case 17:
    // xTaskCreate((TaskFunction_t)GJR_PULLGATE_RABBIT_TASK_CTRL, /* 任务函数            */
                // (const char *)"Pull-GateRabbit",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,           /* 任务堆栈            */
                // (void *)NULL,                                 /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,            /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);        /* 任务句柄            */
    // break;
  // case 18:
    // xTaskCreate((TaskFunction_t)GJR_HOME_OF_MIKE_TASK_CTRL, /* 任务函数            */
                // (const char *)"HomeOfMike",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,           /* 任务堆栈            */
                // (void *)NULL,                                 /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,            /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);        /* 任务句柄            */
    // break;
  // case 19:
    // xTaskCreate((TaskFunction_t)GJR_AUTO_DOOR_TASK_CTRL, /* 任务函数            */
                // (const char *)"AutoDoor",           /* 任务名称            */
                // (uint16_t)GJR_TASK_STK_SIZE,           /* 任务堆栈            */
                // (void *)NULL,                                 /* 传递给任务函数的参数*/
                // (UBaseType_t)GJR_TASK_PRIO,            /* 任务优先级          */
                // (TaskHandle_t *)&GJR_TASK_HANDLE);        /* 任务句柄            */
    // break;
  // }

  // //  /* 音频控制任务 */
  // //  xTaskCreate((TaskFunction_t )AUDIO_TASK_CTRL,        /* 任务函数            */
  // //              (const char*    )"AudioCtrl",               /* 任务名称            */
  // //              (uint16_t       )AUDIO_TASK_STK_SIZE,       /* 任务堆栈            */
  // //              (void*          )NULL,                   /* 传递给任务函数的参数*/
  // //              (UBaseType_t    )AUDIO_TASK_PRIO,           /* 任务优先级          */
  // //              (TaskHandle_t*  )&AUDIO_TASK_HANDLE);       /* 任务句柄            */
  // //  /* can接收处理 */
  // //  xTaskCreate((TaskFunction_t )CAN_TASK_RX_CTRL,       /* 任务函数            */
  // //              (const char*    )"canrx",                /* 任务名称            */
  // //              (uint16_t       )CAN_TASK_RX_STK_SIZE,   /* 任务堆栈            */
  // //              (void*          )NULL,                   /* 传递给任务函数的参数*/
  // //              (UBaseType_t    )CAN_TASK_RX_PRIO,       /* 任务优先级          */
  // //              (TaskHandle_t*  )&CAN_TASK_RX_HANDLE);   /* 任务句柄            */
  // //  /* can发送处理 */
  // //  xTaskCreate((TaskFunction_t )CAN_TASK_TX_CTRL,       /* 任务函数            */
  // //              (const char*    )"canrx",                /* 任务名称            */
  // //              (uint16_t       )CAN_TASK_TX_STK_SIZE,   /* 任务堆栈            */
  // //              (void*          )NULL,                   /* 传递给任务函数的参数*/
  // //              (UBaseType_t    )CAN_TASK_TX_PRIO,       /* 任务优先级          */
  // //              (TaskHandle_t*  )&CAN_TASK_TX_HANDLE);   /* 任务句柄            */
  // //  /* UART发送处理 */
  // //  xTaskCreate((TaskFunction_t )UART_TASK_TX_CTRL,      /* 任务函数            */
  // //              (const char*    )"UARTTX",               /* 任务名称            */
  // //              (uint16_t       )UART_TASK_TX_STK_SIZE,  /* 任务堆栈            */
  // //              (void*          )NULL,                   /* 传递给任务函数的参数*/
  // //              (UBaseType_t    )UART_TASK_TX_PRIO,      /* 任务优先级          */
  // //              (TaskHandle_t*  )&UART_TASK_TX_HANDLE);  /* 任务句柄            */
  // //  /* UART接收处理 */
  // //  xTaskCreate((TaskFunction_t )UART_TASK_RX_CTRL,      /* 任务函数            */
  // //              (const char*    )"UARTRX",               /* 任务名称            */
  // //              (uint16_t       )UART_TASK_RX_STK_SIZE,  /* 任务堆栈            */
  // //              (void*          )NULL,                   /* 传递给任务函数的参数*/
  // //              (UBaseType_t    )UART_TASK_RX_PRIO,      /* 任务优先级          */
  // //              (TaskHandle_t*  )&UART_TASK_RX_HANDLE);  /* 任务句柄            */
// }

// /*
// ********************************************************************************
// * 函数名: void System_Free_Dispose(void)
// * 说  明: 系统空闲运行
// * 参  数: N/A
// * 返回值: N/A
// * 设  计: MGQ
// * 日  期: 20181020
// * 修  改:
// ********************************************************************************
// */
// uint8_t test[5] = {1, 2, 3, 4, 5};
// void FREE_TASK_CTRL(void *pvParameters)
// {
  // while (1)
  // {
// //    Zigbee_send(test, 5);
    // SCREEN_UartToRS485_send(test, 5);
    // vTaskDelay(500);
    // /********************************CAN处理*************************************/
    // //can接收处理
    // if (CAN_RxBuffer.pRead != CAN_RxBuffer.pWrite)
    // {
      // //标准帧-数据帧
      // if ((CAN_RxBuffer.pRead->IDE == CAN_ID_STD) && (CAN_RxBuffer.pRead->RTR == CAN_RTR_DATA))
      // {
        // CAN_COMM_Dispose(CAN_RxBuffer.pRead);
      // }
      // if (++CAN_RxBuffer.pRead == &CAN_RxBuffer.buffer[size_for_can_Rx])
        // CAN_RxBuffer.pRead = &CAN_RxBuffer.buffer[0];
    // }
    // //CAN发送缓存处理
    // if (CAN_TxBuffer.pRead != CAN_TxBuffer.pWrite)
    // {
      // hcan.pTxMsg = CAN_TxBuffer.pRead;
      // if (MGQ_CAN_Transmit(&hcan) == HAL_OK)
      // {
        // if (++CAN_TxBuffer.pRead == &CAN_TxBuffer.buffer[size_for_can_Tx])
          // CAN_TxBuffer.pRead = &CAN_TxBuffer.buffer[0];
      // }
    // }
    // /********************************Sys_Time处理********************************/
    // /*10ms标志处理*/
    // if (Sys_time.Flag.Flag_10ms)
    // {
      // Sys_time.Flag.Flag_10ms = 0;
      // /*扫描输入函数*/
      // Scan_InPut();
      // /*音乐扫描函数*/
      // Scan_AUX_Ctrl();
      // /*Zigbee接收数据超时处理*/
      // if (Zigbee_UART_Ctrl.VD_Timeout)
      // {
        // Zigbee_UART_Ctrl.VD_Timeout--;
      // }
      // //UartToUSB接收数据处理
      // if (UartToUSB_UART_Ctrl.VD_Timeout)
      // {
        // UartToUSB_UART_Ctrl.VD_Timeout--;
      // }
      // //UartToRS485接收数据处理
      // if (SCREEN_UartToRS485_UART_Ctrl.VD_Timeout)
      // {
        // SCREEN_UartToRS485_UART_Ctrl.VD_Timeout--;
      // }
    // }
    // //100ms标志处理
    // if (Sys_time.Flag.Flag_50ms)
    // {
      // Sys_time.Flag.Flag_50ms = 0;
      // /*Zigbee延时发送扫描*/
      // Zigbee_TX_Delay_Dispose();
    // }
    // //1s标志处理
    // if (Sys_time.Flag.Flag_1000ms)
    // {
      // Sys_time.Flag.Flag_1000ms = 0;
    // }

    // /************************串口通讯处理*************************************/
    // //AUX模块
    // if (AUX_UART_Ctrl.RX_Read != AUX_UART_Ctrl.RX_Write)
    // {
      // AUX_COMM_Dispose(*AUX_UART_Ctrl.RX_Read);
      // if (++AUX_UART_Ctrl.RX_Read == &AUX_UART_Ctrl.RX_Buffer[Size_For_UART_RX])
        // AUX_UART_Ctrl.RX_Read = &AUX_UART_Ctrl.RX_Buffer[0];
    // }
    // //Zigbee模块接收数据处理
    // if (Zigbee_UART_Ctrl.RX_Read != Zigbee_UART_Ctrl.RX_Write)
    // {
      // Zigbee_COMM_Dispose(*Zigbee_UART_Ctrl.RX_Read);
      // if (++Zigbee_UART_Ctrl.RX_Read == &Zigbee_UART_Ctrl.RX_Buffer[Size_For_UART_RX])
        // Zigbee_UART_Ctrl.RX_Read = &Zigbee_UART_Ctrl.RX_Buffer[0];
    // }

    // if (SYSTEN_RUN_PARAMETER.Flag.Write_Flash)
    // {
      // SYSTEN_RUN_PARAMETER.Flag.Write_Flash = 0;
      // Write_Short_SYS_Data(&SYSTEN_CTRL_PARAMETER.VoiceVolume, SYS_CTRL_NUMBER);
    // }
    // //Zigbee模块发送数据处理
    // if (Zigbee_TX_Buffer.pRead != Zigbee_TX_Buffer.pWrite)
    // {
      // if (HAL_OK == HAL_UART_Transmit_IT(&Zigbee_UART, &Zigbee_TX_Buffer.pRead->buffer[0], Zigbee_TX_Buffer.pRead->length))
      // {
        // if (++Zigbee_TX_Buffer.pRead == &Zigbee_TX_Buffer.buffer[size_for_zigbee_Rx])
          // Zigbee_TX_Buffer.pRead = &Zigbee_TX_Buffer.buffer[0];
      // }
    // }
    // //UartToUSB模块接收数据处理
    // if (UartToUSB_UART_Ctrl.RX_Read != UartToUSB_UART_Ctrl.RX_Write)
    // {
      // UartToUSB_COMM_Dispose(*UartToUSB_UART_Ctrl.RX_Read);
      // if (++UartToUSB_UART_Ctrl.RX_Read == &UartToUSB_UART_Ctrl.RX_Buffer[Size_For_UART_RX])
        // UartToUSB_UART_Ctrl.RX_Read = &UartToUSB_UART_Ctrl.RX_Buffer[0];
    // }
    // //UartToUSB模块发送处理
    // if (UartToUSB_RX_Buffer.pRead != UartToUSB_RX_Buffer.pWrite)
    // {
      // if (HAL_OK == HAL_UART_Transmit_IT(&UartToUSB_UART, &UartToUSB_RX_Buffer.pRead->buffer[0], UartToUSB_RX_Buffer.pRead->length))
      // {
        // if (++UartToUSB_RX_Buffer.pRead == &UartToUSB_RX_Buffer.buffer[size_for_UartToUSB_Rx])
          // UartToUSB_RX_Buffer.pRead = &UartToUSB_RX_Buffer.buffer[0];
      // }
    // }
    // //UartToRS485模块接收数据处理
    // if (SCREEN_UartToRS485_UART_Ctrl.RX_Read != SCREEN_UartToRS485_UART_Ctrl.RX_Write)
    // {
      // UartToUSB_COMM_Dispose(*SCREEN_UartToRS485_UART_Ctrl.RX_Read);
      // if (++SCREEN_UartToRS485_UART_Ctrl.RX_Read == &SCREEN_UartToRS485_UART_Ctrl.RX_Buffer[Size_For_UART_RX])
        // SCREEN_UartToRS485_UART_Ctrl.RX_Read = &SCREEN_UartToRS485_UART_Ctrl.RX_Buffer[0];
    // }
    // //UartToRS485模块发送处理
    // if (SCREEN_UartToRS485_RX_Buffer.pRead != SCREEN_UartToRS485_RX_Buffer.pWrite)
    // {
      // if (HAL_OK == HAL_UART_Transmit_IT(&UartToUSB_UART, &SCREEN_UartToRS485_RX_Buffer.pRead->buffer[0], SCREEN_UartToRS485_RX_Buffer.pRead->length))
      // {
        // if (++SCREEN_UartToRS485_RX_Buffer.pRead == &SCREEN_UartToRS485_RX_Buffer.buffer[size_for_UartToUSB_Rx])
          // SCREEN_UartToRS485_RX_Buffer.pRead = &SCREEN_UartToRS485_RX_Buffer.buffer[0];
      // }
    // }
  // }
// }

// /*
// ********************************************************************************
// * 函数名: void System_Power_ON(void)
// * 说  明: 系统上电运行
// * 参  数: N/A
// * 返回值: N/A
// * 设  计: MGQ
// * 日  期: 20190408
// * 修  改:
// ********************************************************************************
// */
// void System_Power_ON(void)
// {
  // Zigbee_TX_Delay.Flag.PowerOn = 1;
  // Zigbee_TX_Delay.Send_counter = 3;

  // SYSTEM_STATE = SYSTEM_STATE_Will;
  // SYSTEN_RUN_PARAMETER.State_Time = 0;
// }

// /*
// ********************************************************************************
// * 函数名: void ResetLastTargetTest_Results(void)
// * 说  明: 清除上次测试模式结果
// * 参  数: N/A
// * 返回值: N/A
// * 设  计: GEEK_MICHAEL
// * 日  期: 20200405
// * 修  改:
// ********************************************************************************
// */
// void ResetLastTargetTest_Results(void)
// {
// //  Gun_Ctrl.ErrFlag.L_COMM = 0;
// //  Gun_Ctrl.ErrFlag.R_COMM = 0;
// //  Reader_Card_Ctrl.Err.COMM_OK = 0;
// //  Zigbee_RX_Buffer.Flag.COMM_OK = 0;
// //  Screen_RX_Buffer.Flag.COMM_OK = 0;
// //  AUX_Ctrl.Flag.OK = 0;
// //  AUX_Ctrl.Flag.MP3_AllReady = 0;
// //  AUX_Ctrl.Flag.Voice_AllReady = 0;
// }