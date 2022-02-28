#include "menu.h"
#include "LED.h"
#include "pwm.h"
#include "ADC.h"
u8 Mode_flag=0;
u8 PA6_PULSE=10;
u8 PA7_PULSE=10;
float   Voltage;
void menu_init()
{
    key_init();
    show_data();
    show_data_s();
}
void menu_First()
{
    key key_v = no_key;
    show_data();
    show_data_s();
    while(1)
    {
        LED1();
        show_Voltage();
        key_v = key_scan();
        if(key_v==key1_on)
        {
            show_para();
            show_para_s();
            while (1)
            {
                LED1();
                Voltage=(3.3 * getADC2())/4096;
                key_v = key_scan();
                if(Mode_flag==0)
                {
                    show_para_s();
                }
                if(key_v==key1_on)
                {
                    show_data();
                    show_data_s();
                    break;
                }
                else if(key_v==key2_on)
                {
                    if(Mode_flag==1) {
                        PA6_PULSE += 10;
                        if (PA6_PULSE > 90) {
                            PA6_PULSE = 10;
                        }
                        show_para_s();
                    }
                }
                else if(key_v==key3_on)
                {
                    if(Mode_flag==1) {
                        PA7_PULSE += 10;
                        if (PA7_PULSE > 90) {
                            PA7_PULSE = 10;
                        }
                        show_para_s();
                    }
                }
                else if(key_v==key4_on)
                {
                    if(Mode_flag==0)
                    {
                        Mode_flag=1;
                    }
                    else if(Mode_flag==1)
                    {
                        Mode_flag=0;
                    }
                }
            }
        }

        else if(key_v==key4_on)
        {
            if(Mode_flag==0)
            {
                Mode_flag=1;
            }
            else if(Mode_flag==1)
            {
                Mode_flag=0;
            }
            show_data_s();
        }
    }

}
void show_data()
{
    LCD_Clear(Black);
    LCD_SetBackColor(Black);
    LCD_SetTextColor(White);
    LCD_DisplayStringLine(Line0,Column6,"Data");
    LCD_DisplayStringLine(Line2,Column4,"V:");
    LCD_DisplayStringLine(Line2,Column10,"V");
    LCD_DisplayStringLine(Line4,Column4,"Mode:");
}
void show_data_s()
{
    if(Mode_flag==0)
    {
        LCD_DisplayStringLine(Line4,Column9,"AUTO");
    }
    else if(Mode_flag==1)
    {
        LCD_DisplayStringLine(Line4,Column9,"MANU");
    }
}
void show_para()
{
    LCD_Clear(Black);
    LCD_SetBackColor(Black);
    LCD_SetTextColor(White);
    LCD_DisplayStringLine(Line0,Column6,"Para");
    LCD_DisplayStringLine(Line2,Column4,"PA6:");
    LCD_DisplayStringLine(Line2,Column10,"%");
    LCD_DisplayStringLine(Line4,Column4,"PA7:");
    LCD_DisplayStringLine(Line4,Column10,"%");

}
void show_para_s()
{
    int tim16_pulse,tim17_pulse;
    tim16_pulse=htim16.Init.Period/100;
    tim17_pulse=htim17.Init.Period/100;
    if(Mode_flag==1)
    {
        Set_TIM16_PWM1_Duty(tim16_pulse * PA6_PULSE);
        Set_TIM17_PWM1_Duty(tim17_pulse * PA7_PULSE);
        LCD_DispDecAt(Line2, Column8, PA6_PULSE, 2);
        LCD_DispDecAt(Line4, Column8, PA7_PULSE, 2);
    }
    else if(Mode_flag==0)
    {
        PA6_PULSE=(int)PA7_PULSE=Voltage/3.3*100;
        Set_TIM16_PWM1_Duty(tim16_pulse * PA6_PULSE);
        Set_TIM17_PWM1_Duty(tim17_pulse * PA7_PULSE);
        LCD_DispDecAt(Line2, Column8, PA6_PULSE, 2);
        LCD_DispDecAt(Line4, Column8, PA7_PULSE, 2);
    }
}
void show_Voltage(void)
{
    Voltage=(3.3 * getADC2())/4096;
    LCD_DispFolatAt(Line2,Column6,Voltage,2);
}
key key_scan()
{
    key key_value = no_key;

    if ((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) || (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET) ||
        (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET) || (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET))
    {
        HAL_Delay(20);
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
        {
            key_value = key1_on;
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET)
        {
            key_value = key2_on;
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET)
        {
            key_value = key3_on;
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
        {
            key_value = key4_on;
            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
    }
    return no_key;
}

/*
u8   CNBR_Num;
u8   VNBR_Num;
u8   IDLE_Num;
u8   ALL_Num;
u8   LED2_flag;
float    CNBR_Fee;
float    VNBR_Fee;
uint8_t show_flag=0;

void menu_init()
{
    CNBR_Num=0;
    VNBR_Num=0;
    IDLE_Num=8;
    ALL_Num=8;
    CNBR_Fee=3.50;
    VNBR_Fee=2.00;
    LED2_flag=0;
    key_init();

}

void menu_First()
{
    key key_v = no_key;
    show_data();
    show_data_s();
    while(1)
    {
        LED1();
        LED2();
        show_flag=1;
        key_v = key_scan();
        if(key_v==key1_on)
        {
            show_para();
            show_para_s();
            while (1)
            {
                LED1();
                LED2();
                show_flag=2;
                key_v = key_scan();
                if(key_v==key1_on)
                {
                    show_data();
                    show_data_s();
                    break;
                }
                else if(key_v==key2_on)
                {
                    CNBR_Fee+=0.5f;
                    VNBR_Fee+=0.5f;
                    show_para_s();
                }
                else if(key_v==key3_on)
                {
                    if(VNBR_Fee<0.5f)
                    {
                        continue;
                    }
                    CNBR_Fee-=0.5f;
                    VNBR_Fee-=0.5f;
                    show_para_s();
                }
                else if(key_v==key4_on)
                {
                    Pwm_Judge();
                }
            }
        }

        else if(key_v==key4_on)
        {
            Pwm_Judge();
        }
    }

}

void Pwm_Judge()
{
    if(LED2_flag==0)
    {
        Set_TIM2_PWM2_Duty(100);
        LED2_flag=1;
        return;
    }
    else if(LED2_flag==1)
    {
        Set_TIM2_PWM2_Duty(0);
        LED2_flag=0;
        return;
    }
}

key key_scan()
{
    key key_value = no_key;

    if ((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) || (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET) ||
        (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET) || (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET))
    {
        HAL_Delay(20);
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
        {
            key_value = key1_on;
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET)
        {
            key_value = key2_on;
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET)
        {
            key_value = key3_on;
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
        {
            key_value = key4_on;
            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
    }
    return no_key;
}

void show_data()
{
    LCD_Clear(Black);
    LCD_SetBackColor(Black);
    LCD_SetTextColor(White);
    LCD_DisplayStringLine(Line1,Column7,"Data");
    LCD_DisplayStringLine(Line3,Column3,"CNBR:");
    LCD_DisplayStringLine(Line5,Column3,"VNBR:");
    LCD_DisplayStringLine(Line7,Column3,"IDLE:");
}
void show_data_s()
{
    IDLE_Num=ALL_Num-CNBR_Num-VNBR_Num;
    LCD_DispDecAt(Line3,Column8,CNBR_Num,1);
    LCD_DispDecAt(Line5,Column8,VNBR_Num,1);
    LCD_DispDecAt(Line7,Column8,IDLE_Num,1);

}
void show_para()
{
    LCD_Clear(Black);
    LCD_SetBackColor(Black);
    LCD_SetTextColor(White);
    LCD_DisplayStringLine(Line1,Column7,"Para");
    LCD_DisplayStringLine(Line3,Column3,"CNBR:");
    LCD_DisplayStringLine(Line5,Column3,"VNBR:");

}
void show_para_s()
{
    LCD_DispFolatAt(Line3,Column8,CNBR_Fee,2);
    LCD_DispFolatAt(Line5,Column8,VNBR_Fee,2);
}
*/
