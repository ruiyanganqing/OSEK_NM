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
	#ifdef PRINT
	printf("at main\n");
	#endif
	#endif
	StartNM();
}
