////////////////////////////////////////
// 应用程序，调用OSEK_NM的服务
////////////////////////////////////////
#include "OsekNM.h"
#include "Driver_Common.h" //平台相关的配置
#include "OsekNMServer.h"
#include "Timer.h"
#include "usart.h"
#include "CAN.h"
#include "delay.h"
#define PRINT
int main()
{
	/*平台初始化*/
	#ifdef STM32F407
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	uart_init(115200);	//初始化串口波特率为115200
	delay_init(168);    //初始化延时函数
	//Stm32Timer3Init();//10ms中断一次
	//STM32_CAN1_Init();
		/*5.使能LED0*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);  ///使能GPIOE时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//25MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化PE3
  GPIO_SetBits(GPIOE,GPIO_Pin_3);
	#ifdef PRINT
	printf("at main\n");
	#endif
	#endif
	StartNM();
}
