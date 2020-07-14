#ifndef __RTT_Uart_Console_IT_H
#define __RTT_Uart_Console_IT_H

/******使用前请适配以下内容******/
#define FinshUartHandle huart3  //适配为使用的UART句柄
#define FinshUartIRQHandler  USART3_IRQHandler //相应的UART中断  两种中断处理函数格式 UART5_IRQHandler/USART3_IRQHandler
#define FinshUartRxBufLen 16  //适配为需要的缓存空间大小
/******用户适配结束******/


/*
 * @brief 初始化控制台IO
*/
void FinshIoInit(void);

/*
 * @brief 控制台获取字符接口（RTT标准）
 * @retn  返回字符
*/
char rt_hw_console_getchar(void);

/*
 * @brief 控制台输出字符接口（RTT标准）
 * @arg1  输出的字符串
*/
void rt_hw_console_output(const char *str);
void UART5_IRQHandler(void);
void FinshUartIRQHandler(void);
void UART5IoInit(void);
int uart_init(void);
void GEEK_UART_IRQHandler(UART_HandleTypeDef *huart);
#endif //RTT_Uart_Console_IT.h