/*******************************************************************************
                                包含头文件
*******************************************************************************/
#include "RTT_Nano_Include.h"

/*******************************************************************************
                                 全局变量
*******************************************************************************/
CAN_TxHeaderTypeDef   TxHeader;
CAN_RxHeaderTypeDef   RxHeader;
/*
********************************************************************************
* 函数名: void RTT_CAN_INIT(void)
* 说  明: 初始化过滤器(全部接收到fifo0)
* 参  数: N/A
* 返回值: N/A
* 设  计: geek_michael
* 日  期: 20200714
* 修  改:
********************************************************************************
*/
int RTT_CAN_INIT(void)
{
  CAN_FilterTypeDef  sFilterConfig;
  
  /* Configure the CAN Filter */
  //初始化过滤器(全部接收到fifo0)
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 14;

  HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);
  
  HAL_CAN_Start(&hcan);
  
   //打开can接收fifo0中断
//  __HAL_CAN_ENABLE_IT(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING);
  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
  return 0;
}

INIT_APP_EXPORT(RTT_CAN_INIT);
/*
***************************************************************************************************
* 函数名: void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
* 说  明: 接收中断回掉函数
* 参  数: hcan，结构体指针
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20180623
* 修  改:
***************************************************************************************************
*/ uint8_t aRxData[8];
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *CanHandle)
{

  if(HAL_CAN_GetRxMessage(CanHandle, CAN_RX_FIFO0, &RxHeader, aRxData) == HAL_OK)
  {
  }
//  if(HAL_CAN_GetRxMessage(CanHandle, CAN_RX_FIFO0, &CAN_RxBuffer.pWrite->CAN_RxHeader, &CAN_RxBuffer.pWrite->Data[0]) != HAL_OK)
//  {
//    ;
//  }
//  else
//  {
//    if(++CAN_RxBuffer.pWrite == &CAN_RxBuffer.buffer[size_for_can_Rx])
//    {
//      CAN_RxBuffer.pWrite = &CAN_RxBuffer.buffer[0];
//    }
//  }
}

