#ifndef _MENU_H_
#define _MENU_H_

#include "main.h"
#include "key.h"
typedef enum
{
    no_key,
    key1_on,
    key2_on,
    key3_on,
    key4_on
} key;
key key_scan(void);
void menu_init(void);
void menu_First(void);
void show_data(void);
void show_data_s(void);
void show_para(void);
void show_para_s(void);
void show_Voltage(void);
extern u8 Mode_flag;
void Pwm_Judge(void);
/*extern u8   CNBR_Num;
extern u8   VNBR_Num;
extern u8   IDLE_Num;
extern u8   ALL_Num;
extern u8   LED2_flag;
extern float    CNBR_Fee;
extern float    VNBR_Fee;
extern uint8_t show_flag;*/
#endif
