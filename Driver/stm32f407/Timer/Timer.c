
#include "Timer.h"
extern void Timer10(void);
/*配置STM32的定时器，用来实现OSEKNM需要的定时器*/
//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz（84MHZ）
//这里使用的是定时器3,10ms中断一次!

void Stm32Timer3Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/*1.时钟使能*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
	/*2.timer寄存器配置*/
	/*10ms中断一次*/
	TIM_TimeBaseInitStructure.TIM_Period = (1000-1); 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=(840-1);  //定时器分频100KHZ,通用定时器的时钟是APB1总线倍频而来(2倍)
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	/*4.中断配置*/
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Stm32Timer3ShutDown()
{
/*1.时钟关闭*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,DISABLE);  ///关闭TIM3时钟
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		Timer10();
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}
