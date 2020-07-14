/*******************************************************************************
                                包含头文件
*******************************************************************************/
#include "RTT_Nano_Include.h"

/*******************************************************************************
                                 全局变量 
*******************************************************************************/

CAN_RX_BUFFER CAN_RxBuffer;
CAN_TX_BUFFER CAN_TxBuffer;
CanTxMsgTypeDef CANTxBuffer;

/*
***************************************************************************************************
* 函数名: void Can_Init_FIFO(void)
* 说  明: 初始化过滤器(全部接收到fifo0)
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20180623
* 修  改:
***************************************************************************************************
*/
void Can_Init_FIFO(void)
{
  CAN_FilterConfTypeDef CAN_FilterConfType;
  CAN_FilterConfType.FilterNumber = 0;
  CAN_FilterConfType.BankNumber = 0;
  CAN_FilterConfType.FilterMode = CAN_FILTERMODE_IDMASK;
  CAN_FilterConfType.FilterScale = CAN_FILTERSCALE_32BIT;
  CAN_FilterConfType.FilterIdHigh = 0;
  CAN_FilterConfType.FilterIdLow = 0;
  CAN_FilterConfType.FilterMaskIdHigh= 0;
  CAN_FilterConfType.FilterMaskIdLow = 0;
  CAN_FilterConfType.FilterFIFOAssignment = 0;
  CAN_FilterConfType.FilterActivation = ENABLE;
  CAN_FilterConfType.BankNumber = 1;
  /*
can_filter.BankNumber：作用是将过滤器组分成两个段，第一段为CAN1使用（范围是：0~BankNumber-1），
第二段为CAN2使用（范围是：BankNumber~27）。
也就是说当CAN1上收到消息，STM32会在0~BankNumer-1这些过滤器中依次查询是否通过过滤，
如果通过则将消息放入配置好的CAN1的FIFO里面等待使用，否则就丢弃。
当CAN2上收到消息，STM32会在BankNumer~27这些过滤器中依次查询是否通过过滤，
如果通过则将消息放入配置好的CAN2的FIFO里面等待使用，否则就丢弃
当BankNumber=0时对于CAN1生效的过滤器段0，对于CAN2生效的过滤器段0-27  */
  HAL_CAN_ConfigFilter(&hcan,&CAN_FilterConfType);
}

/*
***************************************************************************************************
* 函数名: void Can_Init_Data(void)
* 说  明: 初始化结构体指针
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20180623
* 修  改:
***************************************************************************************************
*/
void Can_Init_Data(void)
{
  //接收环形数组
  CAN_RxBuffer.pRead  = &CAN_RxBuffer.buffer[0];
  CAN_RxBuffer.pWrite = &CAN_RxBuffer.buffer[0];
  hcan.pRxMsg         = CAN_RxBuffer.pWrite;
  
  //发送环形数据
  CAN_TxBuffer.pRead  = &CAN_TxBuffer.buffer[0];
  CAN_TxBuffer.pWrite = &CAN_TxBuffer.buffer[0];
  hcan.pTxMsg         = CAN_TxBuffer.pRead;
  
}

/*
***************************************************************************************************
* 函数名: void Can_Init_Interrupts(void)
* 说  明: 初始化中断使能
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20180623
* 修  改:
***************************************************************************************************
*/
void Can_Init_Interrupts(void)
{
  //打开can接收fifo0中断
  __HAL_CAN_ENABLE_IT(&hcan,CAN_IT_FMP0);
}

/*
***************************************************************************************************
* 函数名: void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
* 说  明: 接收中断回掉函数
* 参  数: hcan，结构体指针
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20180623
* 修  改:
***************************************************************************************************
*/
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{
  if(++CAN_RxBuffer.pWrite == &CAN_RxBuffer.buffer[size_for_can_Rx])
  {
     CAN_RxBuffer.pWrite = &CAN_RxBuffer.buffer[0];
  }
  hcan->pRxMsg = CAN_RxBuffer.pWrite;
  Can_Init_Interrupts();
  
}
/*
***************************************************************************************************
* 函数名: void MGQ_CAN_SEND(CanTxMsgTypeDef *CanTxMsg)
* 说  明: can发送函数（发送至环形缓冲数组内）
* 参  数: CanTxMsg，发送结构体指针
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20180623
* 修  改:
***************************************************************************************************
*/
void MGQ_CAN_SEND(CanTxMsgTypeDef *CanTxMsg)
{
  HAL_StatusTypeDef CAN_Send;
  
  //帧的类型CAN_RTR_DATA=数据帧\CAN_RTR_REMOTE=远程帧
  CANTxBuffer.RTR=CAN_RTR_DATA;
  //标识符的类型CAN_ID_STD=标准帧ID\CAN_ID_EXT=扩展帧ID
  CANTxBuffer.IDE=CAN_ID_STD;
  
  
  //如果有空闲邮箱就直接发送  
  hcan.pTxMsg = CanTxMsg;
  CAN_Send = MGQ_CAN_Transmit(&hcan);
  //如果没有空闲邮箱就放在缓存中等待发送
  if(CAN_Send != HAL_OK)
  {
    memcpy(CAN_TxBuffer.pWrite,CanTxMsg,sizeof(CANTxBuffer));
    if(++CAN_TxBuffer.pWrite == &CAN_TxBuffer.buffer[size_for_can_Tx])
      CAN_TxBuffer.pWrite = &CAN_TxBuffer.buffer[0];
  }
}

/*
***************************************************************************************************
* 函数名: HAL_StatusTypeDef MGQ_CAN_Transmit(CAN_HandleTypeDef* hcan)
* 说  明: can发送函数（发送环形缓冲调用）
          在hal库的发送函数改过来取消等待发送完成；
* 参  数: hcan，结构体指针
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20180623
* 修  改:
***************************************************************************************************
*/
HAL_StatusTypeDef MGQ_CAN_Transmit(CAN_HandleTypeDef* hcan)
{
  uint32_t transmitmailbox = CAN_TXSTATUS_NOMAILBOX;

  if(((hcan->Instance->TSR&CAN_TSR_TME0) == CAN_TSR_TME0) || \
     ((hcan->Instance->TSR&CAN_TSR_TME1) == CAN_TSR_TME1) || \
     ((hcan->Instance->TSR&CAN_TSR_TME2) == CAN_TSR_TME2))
  {
   
    /* Select one empty transmit mailbox */
    if (HAL_IS_BIT_SET(hcan->Instance->TSR, CAN_TSR_TME0))
    {
      transmitmailbox = CAN_TXMAILBOX_0;
    }
    else if (HAL_IS_BIT_SET(hcan->Instance->TSR, CAN_TSR_TME1))
    {
      transmitmailbox = CAN_TXMAILBOX_1;
    }
    else
    {
      transmitmailbox = CAN_TXMAILBOX_2;
    }

    /* Set up the Id */
    hcan->Instance->sTxMailBox[transmitmailbox].TIR &= CAN_TI0R_TXRQ;
    if (hcan->pTxMsg->IDE == CAN_ID_STD)
    {
      assert_param(IS_CAN_STDID(hcan->pTxMsg->StdId));  
      hcan->Instance->sTxMailBox[transmitmailbox].TIR |= ((hcan->pTxMsg->StdId << CAN_TI0R_STID_Pos) |
                                                           hcan->pTxMsg->RTR);
    }
    else
    {
      assert_param(IS_CAN_EXTID(hcan->pTxMsg->ExtId));
      hcan->Instance->sTxMailBox[transmitmailbox].TIR |= ((hcan->pTxMsg->ExtId << CAN_TI0R_EXID_Pos) |
                                                           hcan->pTxMsg->IDE |
                                                           hcan->pTxMsg->RTR);
    }

    /* Set up the DLC */
    hcan->pTxMsg->DLC &= (uint8_t)0x0000000F;
    hcan->Instance->sTxMailBox[transmitmailbox].TDTR &= 0xFFFFFFF0U;
    hcan->Instance->sTxMailBox[transmitmailbox].TDTR |= hcan->pTxMsg->DLC;

    /* Set up the data field */
    WRITE_REG(hcan->Instance->sTxMailBox[transmitmailbox].TDLR, ((uint32_t)hcan->pTxMsg->Data[3] << CAN_TDL0R_DATA3_Pos) | 
                                                                ((uint32_t)hcan->pTxMsg->Data[2] << CAN_TDL0R_DATA2_Pos) |
                                                                ((uint32_t)hcan->pTxMsg->Data[1] << CAN_TDL0R_DATA1_Pos) | 
                                                                ((uint32_t)hcan->pTxMsg->Data[0] << CAN_TDL0R_DATA0_Pos));
    WRITE_REG(hcan->Instance->sTxMailBox[transmitmailbox].TDHR, ((uint32_t)hcan->pTxMsg->Data[7] << CAN_TDL0R_DATA3_Pos) | 
                                                                ((uint32_t)hcan->pTxMsg->Data[6] << CAN_TDL0R_DATA2_Pos) |
                                                                ((uint32_t)hcan->pTxMsg->Data[5] << CAN_TDL0R_DATA1_Pos) |
                                                                ((uint32_t)hcan->pTxMsg->Data[4] << CAN_TDL0R_DATA0_Pos));
    /* Request transmission */
    SET_BIT(hcan->Instance->sTxMailBox[transmitmailbox].TIR, CAN_TI0R_TXRQ);
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Return function status */
    return HAL_ERROR;
  }
}
/*
***************************************************************************************************
* 函数名: void MGQ_CAN_INIT(void)
* 说  明: can总体初始化
* 参  数: CanTxMsg，发送结构体指针
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20180623
* 修  改:
***************************************************************************************************
*/
void MGQ_CAN_INIT(void)
{
  Can_Init_FIFO();   
  Can_Init_Data(); 
  Can_Init_Interrupts();
}