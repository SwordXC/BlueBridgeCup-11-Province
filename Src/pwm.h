//
// Created by 张亮亮 on 2022/2/6.
//

#ifndef HAL_06_LCD_PWM_H
#define HAL_06_LCD_PWM_H

#include "main.h"
extern TIM_HandleTypeDef htim17,htim16;
extern TIM_OC_InitTypeDef tim17_ch2_OC_Handle,tim16_ch2_OC_Handle;
void MX_TIM2_PWM2_Init(void);
void Set_TIM17_PWM1_Duty(uint32_t duty);
void Set_TIM16_PWM1_Duty(uint32_t duty);
void Set_TIM17_PWM1_Period(uint32_t period);
void Set_TIM16_PWM1_Period(uint32_t period);
#endif //HAL_06_LCD_PWM_H
