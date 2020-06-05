#ifndef __RTT_Uart_Console_H
#define __RTT_Uart_Console_H

//******************函数原型****************************//
int uart_init(void);
void rt_hw_console_output(const char *str);
char rt_hw_console_getchar(void);
#endif //RTT_Uart_Console.h