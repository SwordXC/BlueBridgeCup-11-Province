//
// Created by 张亮亮 on 2022/1/29.
//

#include "uart.h"
#include "stdio.h"
#include "menu.h"
UART_HandleTypeDef huart1;
uint8_t uart_rx_buf[128];
uint8_t ScanNum=0;
uint8_t CharNum=0;
uint8_t uart_rx_flag=0;
uint8_t uart_tx_flag=0;
uint8_t CarJudge_flag=0;
uint8_t CNBR_flag=0;
uint8_t VNBR_flag=0;
uint8_t StopHour;
CarInformation CarIn;
CarInformation CarOut;
float Fee;
uint8_t months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
void MX_UART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit); //配置USART1外设的时钟
	
	__HAL_RCC_USART1_CLK_ENABLE(); //打开USART1的时钟
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600; //设置波特率
	huart1.Init.WordLength = UART_WORDLENGTH_8B; //设置数据位
	huart1.Init.StopBits = UART_STOPBITS_1; //设置停止位
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	
	HAL_MultiProcessor_Init(&huart1, 0, UART_WAKEUPMETHOD_IDLELINE);
	HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8);
	
	HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8);
	HAL_UARTEx_DisableFifoMode(&huart1);
	
	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD; //复用开漏输出
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;//复用功能
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); //初始化串口引脚PA9 PA10
	
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0); //设置串口中断优先级
	HAL_NVIC_EnableIRQ(USART1_IRQn); //打开串口中断
	
	HAL_UART_Receive_IT(&huart1, uart_rx_buf, 1); //设置串口中断缓冲区及中断阈值(当前为1)
}

//串口中断
void USART1_IRQHandler(void) //串口中断
{
	HAL_UART_IRQHandler(&huart1);
}

//串口中断回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
    /*
    if(IDLE_Num!=0)
    {
        ScanNum++;
        if (uart_rx_buf[0] == ':') {
            ScanNum = 0;
            CharNum++;
        }
        if (CharNum == 0 && ScanNum > 4) {
            HAL_UART_Transmit(&huart1, "ERROR", 5, 50);
        }
        CarOutInformation();
        //CarOutShow();
        CarInInformation();
        //CarInShow();
        if (CarJudge_flag == 0) {
            CarTypeJudge();
            if (show_flag == 1) {
                show_data_s();
            }
        }
        if (uart_rx_flag == 2) {
            FeeCompute();
            FeeShow();
            uart_rx_flag = 3;
        }
        if (uart_rx_flag == 3) {
            Clear_flag();
        }
    }
    else if(IDLE_Num==0)
    {
        printf("FULL");

    }*/
	HAL_UART_Receive_IT(&huart1, uart_rx_buf, 1); //设置串口中断缓冲区及中断阈值(当前为1)
}

//重定向printf函数为串口输出
int fputc(int ch,FILE *p)
{
	char c = ch;
	HAL_UART_Transmit(&huart1,(unsigned char *)&c, 1, 50);
	return ch;
}

//发送单个数据
void UART1_SendByte(char c)
{
	HAL_UART_Transmit(&huart1,(unsigned char *)&c, 1, 50);
}

//发送整个数组
void UART1_SendData(char *p, int len)
{
	HAL_UART_Transmit(&huart1,(unsigned char *)p, len, 50);
}

void CarInInformation()
{
    if(CharNum==0 && uart_rx_flag==0)
    {
        CarIn.CarType[ScanNum-1]=uart_rx_buf[0];
    }
    else if(CharNum==1 && uart_rx_buf[0]!=':' && uart_rx_flag==0)
    {
        CarIn.CarName[ScanNum-1]=uart_rx_buf[0];
    }
    else if(CharNum==2 && uart_rx_buf[0]!=':' && uart_rx_flag==0)
    {
        if(ScanNum<3)
        {
            CarIn.timYear=uart_rx_buf[0]-48+CarIn.timYear*10;
        }
        if(ScanNum>=3 && ScanNum<5)
        {
            CarIn.timMonth=uart_rx_buf[0]-48+CarIn.timMonth*10;
        }
        if(ScanNum>=5 && ScanNum<7)
        {
            CarIn.timDay=uart_rx_buf[0]-48+CarIn.timDay*10;
        }
        if(ScanNum>=7 && ScanNum<9)
        {
            CarIn.timHour=uart_rx_buf[0]-48+CarIn.timHour*10;
        }
        if(ScanNum>=9 && ScanNum<11)
        {
            CarIn.timMin=uart_rx_buf[0]-48+CarIn.timMin*10;
        }
        if(ScanNum>=11 && ScanNum<13)
        {
            CarIn.timSec=uart_rx_buf[0]-48+CarIn.timSec*10;
        }
        if(ScanNum>=13)
        {
            ScanNum=0;
            CharNum=0;
            uart_rx_flag=1;
        }
    }
}
void CarOutInformation()
{
    if(CharNum==0 && uart_rx_flag==1)
    {
        CarOut.CarType[ScanNum-1]=uart_rx_buf[0];
    }
    else if(CharNum==1 && uart_rx_buf[0]!=':' && uart_rx_flag==1)
    {
        CarOut.CarName[ScanNum-1]=uart_rx_buf[0];
    }
    else if(CharNum==2 && uart_rx_buf[0]!=':' && uart_rx_flag==1)
    {
        if(ScanNum<3)
        {
            CarOut.timYear=uart_rx_buf[0]-48+CarOut.timYear*10;
        }
        if(ScanNum>=3 && ScanNum<5)
        {
            CarOut.timMonth=uart_rx_buf[0]-48+CarOut.timMonth*10;
        }
        if(ScanNum>=5 && ScanNum<7)
        {
            CarOut.timDay=uart_rx_buf[0]-48+CarOut.timDay*10;
        }
        if(ScanNum>=7 && ScanNum<9)
        {
            CarOut.timHour=uart_rx_buf[0]-48+CarOut.timHour*10;
        }
        if(ScanNum>=9 && ScanNum<11)
        {
            CarOut.timMin=uart_rx_buf[0]-48+CarOut.timMin*10;
        }
        if(ScanNum>=11 && ScanNum<13)
        {
            CarOut.timSec=uart_rx_buf[0]-48+CarOut.timSec*10;
        }
        if(ScanNum>=13)
        {
            ScanNum=0;
            CharNum=0;
            uart_rx_flag=2;
        }
    }
}

void CarInShow()
{
    if(uart_rx_flag==1 && uart_tx_flag==0)
    {
        uint8_t i=0;
        for(i=0;i<4;i++)
        {
            printf("%c",CarIn.CarType[i]);
        }
        printf(":");
        for(i=0;i<4;i++)
        {
            printf("%c",CarIn.CarName[i]);
        }
        printf(":");
        if(CarIn.timYear<10) printf("0");
        printf("%d",CarIn.timYear);
        if(CarIn.timMonth<10) printf("0");
        printf("%d",CarIn.timMonth);
        if(CarIn.timDay<10) printf("0");
        printf("%d",CarIn.timDay);
        if(CarIn.timHour<10) printf("0");
        printf("%d",CarIn.timHour);
        if(CarIn.timMin<10) printf("0");
        printf("%d",CarIn.timMin);
        if(CarIn.timSec<10) printf("0");
        printf("%d",CarIn.timSec);
        uart_tx_flag=1;
    }
}
void CarOutShow()
{
    if(uart_rx_flag==2)
    {
        uint8_t i=0;
        for(i=0;i<4;i++)
        {
            printf("%c",CarOut.CarType[i]);
        }
        printf(":");
        for(i=0;i<4;i++)
        {
            printf("%c",CarOut.CarName[i]);
        }
        printf(":");
        if(CarOut.timYear<10) printf("0");
        printf("%d",CarOut.timYear);
        if(CarOut.timMonth<10) printf("0");
        printf("%d",CarOut.timMonth);
        if(CarOut.timDay<10) printf("0");
        printf("%d",CarOut.timDay);
        if(CarOut.timHour<10) printf("0");
        printf("%d",CarOut.timHour);
        if(CarOut.timMin<10) printf("0");
        printf("%d",CarOut.timMin);
        if(CarOut.timSec<10) printf("0");
        printf("%d",CarOut.timSec);
    }
}
/*
void CarTypeJudge()
{
    if(CarIn.CarType[0]=='V')
    {
        if(CarIn.CarType[1]=='N')
        {
            if(CarIn.CarType[2]=='B')
            {
                if(CarIn.CarType[3]=='R')
                {
                    VNBR_Num++;
                    CarJudge_flag=1;
                    VNBR_flag=1;
                }
            }
        }
    }
    else if(CarIn.CarType[0]=='C')
    {
        if(CarIn.CarType[1]=='N')
        {
            if(CarIn.CarType[2]=='B')
            {
                if(CarIn.CarType[3]=='R')
                {
                    CNBR_Num++;
                    CarJudge_flag=1;
                    CNBR_flag=1;
                }
            }
        }
    }

}

void FeeCompute()//费用计算，涉及到闰年会计算错误,目前计算方法是换算成分钟换算成小时再进行费用乘积
{
    int HourIn,HourOut,AllMin;
    HourIn=((months[CarIn.timMonth-1]*CarIn.timMonth+CarIn.timDay)*24+CarIn.timHour)*60+CarIn.timMin;
    HourOut=((months[CarOut.timMonth-1]*CarOut.timMonth+CarOut.timDay)*24+CarOut.timHour)*60+CarOut.timMin;
    AllMin=HourOut-HourIn;
    if(AllMin%60==0)
    {
        StopHour=AllMin/60;
    }
    else if(AllMin%60!=0)
    {
        StopHour=AllMin/60+1;
    }
    if(CNBR_flag==1)
    {
        Fee=StopHour*CNBR_Fee;
    }
    else if(VNBR_flag==1)
    {
        Fee=StopHour*VNBR_Fee;
    }

}

void FeeShow()
{
    uint8_t i=0;
    printf("\n");
    for(i=0;i<4;i++)
    {
        printf("%c",CarOut.CarType[i]);
    }
    printf(":");
    for(i=0;i<4;i++)
    {
        printf("%c",CarOut.CarName[i]);
    }
    printf(":");
    printf("%d",StopHour);
    printf(":");
    printf("%.2f",Fee);
}

void Clear_flag()
{
    ScanNum=0;
    CharNum=0;
    uart_rx_flag=0;
    uart_tx_flag=0;
    CarJudge_flag=0;
    CNBR_flag=0;
    VNBR_flag=0;
    CarIn.timYear=0;
    CarIn.timMonth=0;
    CarIn.timDay=0;
    CarIn.timHour=0;
    CarIn.timMin=0;
    CarIn.timSec=0;
    CarOut.timYear=0;
    CarOut.timMonth=0;
    CarOut.timDay=0;
    CarOut.timHour=0;
    CarOut.timMin=0;
    CarOut.timSec=0;
}
*/