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

rt_mq_t can_mq = RT_NULL;
int RTT_CANInit(void)
{
  can_mq = rt_mq_create("can_mq",8,50,RT_IPC_FLAG_FIFO);
  return 0;
}
INIT_APP_EXPORT(RTT_CANInit);
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
    rt_mq_send(can_mq,aRxData,8);
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
  uint8_t recv[8];
void can_thread_recv_mq(void *para)
{
  static uint32_t cnt = 0;
  while(1)
  {
    if(rt_mq_recv(can_mq,&recv,8,100) == RT_EOK)//RT_WAITING_FOREVER
    {
      if(RxHeader.IDE==CAN_ID_STD && RxHeader.RTR == CAN_RTR_DATA)
      {
        if(RxHeader.StdId == 0x01)
        {
//            for(uint8_t i=0;i<8;i++)
//            {
//              rt_kprintf("%d ",recv[i]);
//            }
//            rt_kprintf("\n");
          if(recv[0] == 0x055)
          {
            if(recv[1] == 0xaa)
            {
              if(recv[2]==0x01)
              {
                  RELAY_ON();
                  cnt+=1;
                  rt_kprintf("cantest_count=%d\n",cnt);
              }
              else if(recv[2]==0x02)
              {
                  RELAY_OFF();
                  cnt+=1;
                  rt_kprintf("cantest_count=%d\n",cnt);
               }
            }
          }   
        }
      }
    }
  }
}

int CAN_test_Sample(void)
{
  rt_thread_t can_tid = rt_thread_create("can_thread",
                                      can_thread_recv_mq,
                                      RT_NULL,
                                      512,
                                      7,
                                      10);
  if(can_tid != RT_NULL){rt_thread_startup(can_tid);}

  return 0;
}
INIT_APP_EXPORT(CAN_test_Sample);
