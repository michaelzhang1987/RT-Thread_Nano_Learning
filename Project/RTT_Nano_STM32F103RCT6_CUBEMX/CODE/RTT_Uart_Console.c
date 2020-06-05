/*******************************************************************************
                                包含头文件
*******************************************************************************/
#include "RTT_Nano_Include.h"

/*******************************************************************************
                                全局变量
*******************************************************************************/

UART_HandleTypeDef UartHandle;

int uart_init(void)
{
    /* 初始化串口参数，如波特率、停止位等等 */
    huart3.Instance = USART3;
    huart3.Init.BaudRate   = 115200;
    huart3.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    huart3.Init.Mode       = UART_MODE_TX_RX;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits   = UART_STOPBITS_1;
    huart3.Init.Parity     = UART_PARITY_NONE;

    /* 初始化串口引脚等 */
    if (HAL_UART_Init(&huart3) != HAL_OK)
    {
        while(1);
    }

    return 0;
}

INIT_BOARD_EXPORT(uart_init);

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    __HAL_UNLOCK(&huart3);

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            HAL_UART_Transmit(&huart3, (uint8_t *)&a, 1, 1);
        }
        HAL_UART_Transmit(&huart3, (uint8_t *)(str + i), 1, 1);
    }
// HAL_UART_Transmit(&huart3,(uint8_t *)str,rt_strlen(str),0xff);

}

char rt_hw_console_getchar(void)
{
    int ch = -1;

    if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) != RESET)
    {
        ch = huart3.Instance->DR & 0xff;
    }
    else
    {
        if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_ORE) != RESET)
        {
            __HAL_UART_CLEAR_OREFLAG(&huart3);
        }
        rt_thread_mdelay(10);
    }
    return ch;
}