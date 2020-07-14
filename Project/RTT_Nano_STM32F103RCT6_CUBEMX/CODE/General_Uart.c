/*******************************************************************************
                                包含头文件
*******************************************************************************/
#include "RTT_Nano_Include.h"

/*******************************************************************************
                                 全局变量
*******************************************************************************/

uint8_t              UartBuffer[8];

/*
********************************************************************************
* 函数名: void MGQ_UART_IRQHandler(UART_HandleTypeDef *huart)
* 说  明: 串口中断服务函数
* 说  明：实在受不了库本身自带的中断服务函数
* 注  意：
* 参  数: huart：串口句柄结构体
* 返回值: 
* 设  计: MGQ
* 日  期: 20180624
* 修  改:
********************************************************************************
*/
void MGQ_UART_IRQHandler(UART_HandleTypeDef *huart)
{
  
  uint32_t isrflags   = READ_REG(huart->Instance->SR);
  uint32_t cr1its     = READ_REG(huart->Instance->CR1);
  uint32_t cr3its     = READ_REG(huart->Instance->CR3);
  
  /* UART in mode Receiver -------------------------------------------------*/
  if(((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
  {
    *huart->pRxBuffPtr++ = (uint8_t)(huart->Instance->DR & (uint8_t)0x00FF);
    HAL_UART_RxCpltCallback(huart);
    return;
  }
  
  /* UART in mode Transmitter ------------------------------------------------*/
  if(((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
  {
    huart->Instance->DR = (uint8_t)(*huart->pTxBuffPtr++ & (uint8_t)0x00FF);
    if(--huart->TxXferCount == 0U)
    {
      /* Disable the UART Transmit Complete Interrupt */
      __HAL_UART_DISABLE_IT(huart, UART_IT_TXE);
      /* Enable the UART Transmit Complete Interrupt */    
      __HAL_UART_ENABLE_IT(huart, UART_IT_TC);
      huart->gState = HAL_UART_STATE_READY;//必有否则中断、DMA发送不了
    }
    return;
  }
  
  /* UART in mode Transmitter end --------------------------------------------*/
  if(((isrflags & USART_SR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
  {
    __HAL_UART_DISABLE_IT(huart, UART_IT_TC);
    HAL_UART_TxCpltCallback(huart);
    return;
  }
  
  //清除过载错误(必须得有开串口接收中断时这个中断同时被开启)
  if(__HAL_UART_GET_FLAG(huart,UART_FLAG_ORE) != RESET)
  {
    __HAL_UART_CLEAR_OREFLAG(huart);
  }

}
/*
********************************************************************************
* 函数名: void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
* 说  明: 串口发送完成回掉函数
* 说  明：DMA\中断发送都调用
* 注  意：
* 参  数: huart串口句柄结构体
* 返回值: 
* 设  计: MGQ
* 日  期: 20180624
* 修  改:
********************************************************************************
*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
//  BaseType_t pxHigherPriorityTaskWoken = pdFALSE; 
//  if(huart == &WIFI_UART)
//  {
//    vTaskNotifyGiveFromISR(UART_WIFI_TX_HANDLE,&pxHigherPriorityTaskWoken);
//  }
//  else if(huart == &Reader_UART)
//  {
//    vTaskNotifyGiveFromISR(UART_Reader_TX_HANDLE,&pxHigherPriorityTaskWoken);
//  } 
//  else if(huart == &AUX_UART)
//  {
//    vTaskNotifyGiveFromISR(UART_AUX_TX_HANDLE,&pxHigherPriorityTaskWoken);
//  } 
//  
//  portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
//  huart->gState = HAL_UART_STATE_READY;//必有否则中断、DMA发送不了
}

/*
********************************************************************************
* 函数名: void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
* 说  明: 串口接收完成回掉函数
* 说  明：huart串口句柄结构体
* 注  意：
* 参  数: 
* 返回值: 
* 设  计: MGQ
* 日  期: 20180624
* 修  改:
********************************************************************************
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart == &huart5)
  {
    huart->pRxBuffPtr = &UartBuffer[3];
    rt_mq_send(uart5_mq,&UartBuffer[3],1);
  }
  else if(huart == &huart4)
  {
    huart->pRxBuffPtr = &UartBuffer[4];
    rt_mq_send(uart4_mq,&UartBuffer[4],1);
  }
//  BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
//  if(huart == &WIFI_UART)
//  {
//    huart->pRxBuffPtr = &UartBuffer[3];
//    xQueueSendFromISR(WIFI_RX_Queue,&UartBuffer[3],&pxHigherPriorityTaskWoken);
//  }
//  else if(huart == &Reader_UART)
//  {
//    huart->pRxBuffPtr = &UartBuffer[5];
//    xQueueSendFromISR(Reader_RX_Queue,&UartBuffer[5],&pxHigherPriorityTaskWoken);
//  }
//  else if(huart == &AUX_UART)
//  {
//    huart->pRxBuffPtr = &UartBuffer[1];
//    xQueueSendFromISR(AUX_RX_Queue,&UartBuffer[1],&pxHigherPriorityTaskWoken);
//  }
//  else if(huart == &Radar_UART)
//  {
//    huart->pRxBuffPtr = &UartBuffer[2];
//    xQueueSendFromISR(Radar_RX_Queue,&UartBuffer[2],&pxHigherPriorityTaskWoken);
//  }
//  else if(huart == &Modbus_Master_UART)
//  {
//    huart->pRxBuffPtr = &UartBuffer[4];
//  }
//  
//  portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
  huart->RxState = HAL_UART_STATE_READY;//必有:超时接收时不至状态位
}


/*
********************************************************************************
* 函数名: uint8_t Computed_Checksum(uint8_t *pdata,uint8_t lenght)
* 说  明: 计算校验和
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20191015
* 修  改:
********************************************************************************
*/
uint8_t Computed_Checksum(uint8_t *pdata,uint8_t lenght)
{
  uint8_t Return_Value = 0;
  uint8_t i;
  for(i=0;i<lenght;i++)
  {
    Return_Value += *pdata;
    pdata++;
  }
  return Return_Value;
}

/*
********************************************************************************
* 函数名: uint8_t Exclusive_or_inspection(uint8_t *pdata,uint8_t lenght)
* 说  明: 计算异或校验
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20191011
* 修  改:
********************************************************************************
*/
uint8_t Exclusive_or_inspection(uint8_t *pdata,uint8_t lenght)
{
  uint8_t i;
  uint8_t Sum=0;
  for(i=0;i<lenght;i++)
  {
    Sum ^= *pdata;
    pdata++;
  }
  return Sum;
}

/*
********************************************************************************
* 函数名: void Init_Uart_RX_Struct(MGQ_UART *pStruct)
* 说  明: 初始化串口接收结构体
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20191015
* 修  改:
********************************************************************************
*/
void Init_Uart_RX_Struct(MGQ_UART *pStruct)
{
  pStruct->VD_Flag  = 0;
  pStruct->VD_State = 0;
}

/*
********************************************************************************
* 函数名: uint8_t ASCII_HEX(uint8_t data)
* 说  明: 将ASC码转16进制数
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20191015
* 修  改:
********************************************************************************
*/

uint8_t ASCII_HEX(uint8_t data)
{
  uint8_t return_Val = 0xFF;
  if((data > 0x29)&&(data < 0x3A))
  {
    return_Val = data-0x30;
  }
  else if((data > 0x40)&&(data < 0x47))
  {
    return_Val = data - 0x37;
  }
  else if((data > 0x60)&&(data < 0x67))
  {
    return_Val = data - 0x57;
  }
  return return_Val;
}


/*
***************************************************************************************************
* 函数名: uint8_t Exclusive_or_invert(uint8_t *pBuffer,uint8_t lenght)
* 说  明: 计算异或取反校验和
* 参  数: N/A
* 返回值: N/A
* 设  计: MGQ
* 日  期: 20181019
* 修  改:
***************************************************************************************************
*/
uint8_t Exclusive_or_invert(uint8_t *pBuffer,uint8_t lenght)
{
  uint8_t j=0;
  uint8_t i=0;
  for(i=0;i<lenght;i++)
  {
    j ^= *pBuffer;
    pBuffer++;
  }
  return ~j;
}

rt_mq_t uart5_mq = RT_NULL;
rt_mq_t uart4_mq = RT_NULL;
rt_mq_t uart2_mq = RT_NULL;
int RTT_UartInit(void)
{
  uart5_mq = rt_mq_create("uart5_mq",1,50,RT_IPC_FLAG_FIFO);
  uart4_mq = rt_mq_create("uart4_mq",1,50,RT_IPC_FLAG_FIFO);
  uart2_mq = rt_mq_create("uart2_mq",1,50,RT_IPC_FLAG_FIFO);
  return 0;
}
INIT_APP_EXPORT(RTT_UartInit);