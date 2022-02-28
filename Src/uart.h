//
// Created by 张亮亮 on 2022/1/29.
//

#ifndef HAL_06_LCD_UART_H
#define HAL_06_LCD_UART_H
#include "main.h"

typedef struct
{
    uint8_t CarType[4];
    uint8_t CarName[4];
    uint8_t timYear;
    uint8_t timMonth;
    uint8_t timDay;
    uint8_t timHour;
    uint8_t timMin;
    uint8_t timSec;
}CarInformation;

void MX_UART1_Init(void);
void USART1_IRQHandler(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void UART1_SendByte(char c);
void UART1_SendData(char *p, int len);
void CarInInformation(void);
void CarInShow(void);
void CarOutInformation(void);
void CarOutShow(void);
void CarTypeJudge(void);
void FeeCompute(void);
void FeeShow(void);
void Clear_flag(void);
#endif //HAL_06_LCD_UART_H
