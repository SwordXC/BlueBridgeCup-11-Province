//
// Created by 张亮亮 on 2022/2/6.
//

#include "pwm.h"

TIM_HandleTypeDef htim17,htim16;
TIM_OC_InitTypeDef tim17_ch2_OC_Handle,tim16_ch2_OC_Handle;

void MX_TIM2_PWM2_Init(void)//PA1 TIM2_CH2 ,PA7 TIM17_CH1,PA6 TIM16_CH1
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_TIM17_CLK_ENABLE();
    __HAL_RCC_TIM16_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

    htim17.Instance = TIM17;
    htim17.Init.Prescaler = 80; //预分频系数80M/80=1MHz
    htim17.Init.CounterMode = TIM_COUNTERMODE_UP; //向上计数
    htim17.Init.Period = 5000; //PWM计数周期 1MHz/5000=200Hz
    htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; //时钟源1分频
    htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    htim17.Init.RepetitionCounter  = 0;
	HAL_TIM_Base_Init(&htim17);

	//引脚初始化，PA7用作TIM2 CH2
	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; //复用推挽输出
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM17; //复用功能
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// 定时器输出PWM初始化
    tim17_ch2_OC_Handle.OCMode = TIM_OCMODE_PWM1; // 模式选择PWM1
    tim17_ch2_OC_Handle.OCPolarity = TIM_OCPOLARITY_HIGH; // 输出比较极性为低
    tim17_ch2_OC_Handle.OCNPolarity = TIM_OCPOLARITY_HIGH;
    tim17_ch2_OC_Handle.OCFastMode = TIM_OCFAST_DISABLE;
    tim17_ch2_OC_Handle.Pulse = 100; //PWM定占空比
	HAL_TIM_PWM_ConfigChannel(&htim17, &tim17_ch2_OC_Handle, TIM_CHANNEL_1); // 配置PWM输出

	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1); // 开始PWM输出


    htim16.Instance = TIM16;
    htim16.Init.Prescaler = 80; //预分频系数80M/80=1MHz
    htim16.Init.CounterMode = TIM_COUNTERMODE_UP; //向上计数
    htim16.Init.Period = 10000; //PWM计数周期 1MHz/10000=100Hz
    htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; //时钟源1分频
    htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    htim16.Init.RepetitionCounter  = 0;
    HAL_TIM_Base_Init(&htim16);

    //引脚初始化，PA1用作TIM2 CH2
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; //复用推挽输出
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM16; //复用功能
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 定时器输出PWM初始化
    tim16_ch2_OC_Handle.OCMode = TIM_OCMODE_PWM1; // 模式选择PWM1
    tim16_ch2_OC_Handle.OCPolarity = TIM_OCPOLARITY_HIGH; // 输出比较极性为低
    tim16_ch2_OC_Handle.OCNPolarity = TIM_OCPOLARITY_HIGH;
    tim16_ch2_OC_Handle.OCFastMode = TIM_OCFAST_DISABLE;
    tim16_ch2_OC_Handle.Pulse = 100; //PWM定占空比
    HAL_TIM_PWM_ConfigChannel(&htim16, &tim16_ch2_OC_Handle, TIM_CHANNEL_1); // 配置PWM输出

    HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1); // 开始PWM输出
}

//设置TIM17 CH1 PWM的占空比
void Set_TIM17_PWM1_Duty(uint32_t duty)
{
	HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
	tim17_ch2_OC_Handle.Pulse = duty;
	HAL_TIM_PWM_ConfigChannel(&htim17, &tim17_ch2_OC_Handle, TIM_CHANNEL_1); // 配置PWM输出
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1); // 开始PWM输出
}
//设置TIM16 CH1 PWM的占空比
void Set_TIM16_PWM1_Duty(uint32_t duty)
{
    HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
    tim16_ch2_OC_Handle.Pulse = duty;
    HAL_TIM_PWM_ConfigChannel(&htim16, &tim16_ch2_OC_Handle, TIM_CHANNEL_1); // 配置PWM输出
    HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1); // 开始PWM输出
}
//设置TIM17 CH1 PWM的周期
void Set_TIM17_PWM1_Period(uint32_t period)
{
    htim17.Init.Period = period;
	HAL_TIM_Base_Init(&htim17);
}
//设置TIM16 CH1 PWM的周期
void Set_TIM16_PWM1_Period(uint32_t period)
{
    htim16.Init.Period = period;
    HAL_TIM_Base_Init(&htim16);
}
//同学们根据上文中的引脚复用表，自行思考如何使用其他定时器的其他引脚输出PWM
