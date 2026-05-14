//
// Created by chengfeng on 2025/10/30.
//

#include "uart_printf.h"
#include <stdarg.h>
#include <stdio.h>
#include "usart.h"

#define UART_TX_HANDLE huart6

/*
* @brief 对应VOFA+的JustFloat协议，发送一个float数组，末尾添加0x7f800000作为结束标志
*/
void vofa_printf(float *data,float num) {
    HAL_UART_Transmit(&UART_TX_HANDLE, (uint8_t *) data, sizeof(float) * num, HAL_MAX_DELAY);
    uint8_t tail[4] = {0x00, 0x00, 0x80, 0x7f};
    HAL_UART_Transmit(&UART_TX_HANDLE, (uint8_t *) tail, sizeof(uint8_t) * 4, HAL_MAX_DELAY);
}

/*
* @brief 串口打印函数
*/
void uart_printf(const char *format, ...)
{
    char buffer[128];
    va_list args;
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    HAL_UART_Transmit(&UART_TX_HANDLE, (uint8_t *) buffer, len, HAL_MAX_DELAY);
}
