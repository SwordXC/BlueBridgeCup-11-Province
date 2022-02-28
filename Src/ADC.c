//
// Created by 张亮亮 on 2022/2/27.
//

#include "ADC.h"
ADC_HandleTypeDef hadc1 , hadc2; //声明两个ADC结构体

uint16_t getADC1(void) // 获取PB12引脚的电压(对应R38电阻)
{
    uint16_t adc = 0;

    HAL_ADC_Start(&hadc1);
    adc = HAL_ADC_GetValue(&hadc1);

    return adc;
}

void MX_ADC1_Init(void) //ADC1_IN11初始化
{
    ADC_ChannelConfTypeDef sConfig = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC12;
    PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_SYSCLK;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit); //配置ADC12的时钟

    __HAL_RCC_ADC12_CLK_ENABLE(); //使能ADC12的时钟

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1; //分频系数
    hadc1.Init.Resolution = ADC_RESOLUTION_12B; //ADC数据位数
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT; //ADC数据对其
    hadc1.Init.GainCompensation = 0;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc1.Init.LowPowerAutoWait = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
    hadc1.Init.OversamplingMode = DISABLE;

    HAL_ADC_Init(&hadc1); //初始化ADC1

    sConfig.Channel = ADC_CHANNEL_11; //设置采样通道为 11(PB12引脚)
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_640CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;

    HAL_ADC_ConfigChannel(&hadc1, &sConfig); //初始化ADC采样通道

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); // 初始化PB12引脚为模拟模式
}


uint16_t getADC2(void) // 获取PB15引脚的电压(对应R37电阻)
{
    uint16_t adc = 0;

    HAL_ADC_Start(&hadc2);
    adc = HAL_ADC_GetValue(&hadc2);

    return adc;
}

void MX_ADC2_Init(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC12;
    PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_SYSCLK;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

    __HAL_RCC_ADC12_CLK_ENABLE();

    hadc2.Instance = ADC2;
    hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
    hadc2.Init.Resolution = ADC_RESOLUTION_12B;
    hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc2.Init.GainCompensation = 0;
    hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc2.Init.LowPowerAutoWait = DISABLE;
    hadc2.Init.ContinuousConvMode = DISABLE;
    hadc2.Init.NbrOfConversion = 1;
    hadc2.Init.DiscontinuousConvMode = DISABLE;
    hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc2.Init.DMAContinuousRequests = DISABLE;
    hadc2.Init.Overrun = ADC_OVR_DATA_PRESERVED;
    hadc2.Init.OversamplingMode = DISABLE;

    HAL_ADC_Init(&hadc2);

    sConfig.Channel = ADC_CHANNEL_15; //设置采样通道为 15(PB15引脚)
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_640CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;

    HAL_ADC_ConfigChannel(&hadc2, &sConfig);

    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); // 初始化PB12引脚为模拟模式
}

