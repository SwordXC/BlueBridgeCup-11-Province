//
// Created by 张亮亮 on 2022/1/27.
//

#ifndef HAL_06_LCD_LED_H
#define HAL_06_LCD_LED_H
#include "main.h"
#include "menu.h"
void LED_init(void);
void LED1(void);
void LED2(void);
void LED_Close(void);

void led_on(uint8_t num);
void led_off_all(void);
void led_off(uint8_t num);
#endif //HAL_06_LCD_LED_H
