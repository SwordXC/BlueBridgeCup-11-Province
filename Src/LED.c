//
// Created by 张亮亮 on 2022/1/27.
//

#include "LED.h"

void LED_init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_8
                             |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);

    /*Configure GPIO pins : PC13 PC14 PC15 PC8
                              PC9 PC10 PC11 PC12 */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pin : PD2 */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    LED_Close();


}

void LED1()
{
    if(Mode_flag==0)
    {
        led_on(1);
    }
    else if(Mode_flag==1)
    {
        led_off(1);
    }
}
/*void LED2()
{
    if(LED2_flag==1)
    {
        led_on(2);
    }
    else if(LED2_flag==0)
    {
        led_off(2);
    }
}
*/
void LED_Close()
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_All, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
}

uint16_t gpio = 0xff00; //高8位对应我们设置LED的状态
/*******************************************************************************
* Description    : open the led.
* Input          : led number (1-8)
* Return         : None
*******************************************************************************/
void led_on(uint8_t num)
{

    gpio = gpio & (~(0x80 << num));              //清零对应的位，不影响其他位
    GPIOC->ODR = gpio | ((GPIOC->ODR) & 0x00ff); //不影响低8位
    //更新到LED
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);


}
/*******************************************************************************
* Description    : close the led.
* Input          : led number (1-8)
* Return         : None
*******************************************************************************/
void led_off(uint8_t num)
{

    gpio = gpio | (0x80 << num);                 //置位应的位，不影响其他位
    GPIOC->ODR = gpio | ((GPIOC->ODR) & 0x00ff); //不影响低8位
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
    //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7 << num, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
}

/*******************************************************************************
* Description    : close all led.
* Input          : None
* Return         : None
*******************************************************************************/

void led_off_all(void)
{
    gpio = 0xff00;
    GPIOC->ODR = gpio | ((GPIOC->ODR) & 0x00ff); //不影响低8位

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
}