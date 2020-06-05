#ifndef __RTT_Uart_Console_IT_H
#define __RTT_Uart_Console_IT_H

//******************函数原型****************************//
void USART3_IRQHandler(void);
void rt_hw_console_output(const char *str);
char rt_hw_console_getchar(void);
int uart_init(void);


#endif //RTT_Uart_Console_IT.h