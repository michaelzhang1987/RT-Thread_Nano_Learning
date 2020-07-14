#ifndef __General_Uart_H
#define __General_Uart_H



#define Size_For_UART_VD       100

typedef struct
{
  uint8_t VD_Flag;                       //接收到一帧数据 
  uint8_t VD_State;                      //接收数据处理状态
  uint8_t VD_Counter;                    //接收数据处理计数
  uint8_t VD_Verify;                     //接收数据处理校验和                  
  uint8_t VD_Buffer[Size_For_UART_VD];   //VD=valid data有效数据     
}MGQ_UART;





void MGQ_UART_IRQHandler(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
uint8_t Computed_Checksum(uint8_t *pdata,uint8_t lenght);
uint8_t Exclusive_or_inspection(uint8_t *pdata,uint8_t lenght);
void Init_Uart_RX_Struct(MGQ_UART *pStruct);
uint8_t ASCII_HEX(uint8_t data);
uint8_t Exclusive_or_invert(uint8_t *pBuffer,uint8_t lenght);
int RTT_UartInit(void);

extern uint8_t              UartBuffer[8];

extern rt_mq_t uart5_mq;
extern rt_mq_t uart4_mq;
extern rt_mq_t uart2_mq;


#endif /* General_Uart.h */