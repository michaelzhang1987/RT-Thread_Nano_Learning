//#ifndef __RTT_Can_Drv_H
//#define __RTT_Can_Drv_H
//
////***************can接收环形结构体****************//
//
////can接收环形数据大小
//#define size_for_can_Rx 50
//
//typedef struct
//{
//  CanRxMsgTypeDef *pWrite;
//  CanRxMsgTypeDef *pRead;
//  CanRxMsgTypeDef buffer[size_for_can_Rx];
//}CAN_RX_BUFFER;
//
////***************can发送环形结构体****************//
//
////can发送环形数据大小
//#define size_for_can_Tx 50
//
//typedef struct
//{
//  CanTxMsgTypeDef *pWrite;
//  CanTxMsgTypeDef *pRead;
//  CanTxMsgTypeDef buffer[size_for_can_Tx];
//}CAN_TX_BUFFER;
//
////******************声明外部变量******************//
//extern CAN_RX_BUFFER CAN_RxBuffer;
//extern CAN_TX_BUFFER CAN_TxBuffer;
//extern CanTxMsgTypeDef CANTxBuffer;
//
////********************函数原型********************//
////初始化FIFO
//void Can_Init_FIFO(void);
////初始化缓冲,将HAL库和缓冲数组关联
//void Can_Init_Data(void);
////开启中断
//void Can_Init_Interrupts(void);
////CAN发送函数
//HAL_StatusTypeDef MGQ_CAN_Transmit(CAN_HandleTypeDef* hcan);
////CAN接收回调函数
//void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan);
////CAN发送函数
//void MGQ_CAN_SEND(CanTxMsgTypeDef *CanTxMsg);
////自己写的发送函数(不开启任何错误中断)
//HAL_StatusTypeDef MGQ_CAN_Transmit(CAN_HandleTypeDef* hcan);
////CAN总初始化函数
//void MGQ_CAN_INIT(void);
//
//
//
//#endif /* RTT_Can_Drv.h */