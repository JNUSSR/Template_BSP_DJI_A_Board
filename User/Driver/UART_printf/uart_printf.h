//
// Created by chengfeng on 2025/10/30.
//

#ifndef IMU_MATLAB_UART_PRINTF_H
#define IMU_MATLAB_UART_PRINTF_H

#ifdef __cplusplus
extern "C"{
#endif

void vofa_printf(float *data,float num);
void uart_printf(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif // IMU_MATLAB_UART_PRINTF_H
