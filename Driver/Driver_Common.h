//根据不同的平台进行配置，配置后可以移植到不同平台
#ifndef CONFIGH_H
#define CONFIGH_H

#include "OsekNM.h"

#define STM32F407  //不在STM32F407平台就将其注释掉
#ifdef STM32F407
#include "CAN.h"
#include "Timer.h"
#include "usart.h"
#include "delay.h"
#endif

/*平台无关的定义*/
typedef  int TimerOutFlag_t;

//网络管理报文的ID
#define NMID (0x0cffA019)

//设置默认节点源地址,节点地址不能为0
#define ADDR_SELF 0x19

//定义时间类型，未初始化(未调用InitDirectNMParams)这些参数就用下面定义的
#define NM_TIMETYPE_TTYP     100
#define NM_TIMETYPE_TMAX     260
#define NM_TIMETYPE_TERROR   1000
#define NM_TIMETYPE_TWBS     5000
//定义定时器类型
#define NM_TIMER_TTYP    0
#define NM_TIMER_TMAX    1
#define NM_TIMER_TERROR  2
#define NM_TIMER_TWBS    3
//返回值定义
#define E_OK     0
#define E_ERROR -1

//平台相关的定义
//#define OSEKOS //需要使用OSEKOS

//#define PRINT
char SetToFIFO(NMPDU_t* msg);
char GetFromFIFO(NMPDU_t* msg);
void ClearFIFO(void);
void InitPlatform(void);
void InitNMPDU(NMPDU_t* NMPDU);
NMTypeU8_t TX_CAN_Transmit(NMPDU_t* NMPDU);
TimerOutFlag_t GetTimerIsOut(NMTimerType_t TimerType);
void ClcTimerOutFlag(NMTimerType_t TimerType);
void Recv_EveryMessage(NMPDU_t* p_Msg);

//不使用OS的话，使用自定义的定时器函数
#ifndef OSEKOS
int SetAlarm(NMTimerType_t timer);
void CancelAlarm(NMTimerType_t timer);
#endif

//FIFO大小
#define FIFOMAX 20


//接受报文FIFO
typedef struct {
	NMPDU_t MSGs[FIFOMAX];//FIFO缓冲区
	char Total;//FIFO中的报文数量
	char Head;//指向队列头
	char Tail;//指向队尾
	char FullFlag;//缓冲区满
	char EmptyFlag;//缓冲区空
	char(*GetMsg) (NMPDU_t* msg); //从缓冲区获取报文
	char(*SetMsg) (NMPDU_t* smsg); //放入报文到缓冲区
	void(*ClearBuff)(void);//清空FIFO
}RecvFIFO_t;
//NM_xxx报文定义

#endif

