//根据不同的平台进行配置，配置后可以移植到不同平台,需要配置定时器、缓冲区
#ifndef WIN7_H
#define WIN7_H

//#define WIN7PC  //不在Windows平台运行注释此处
#ifdef WIN7PC
#include"../../OsekNM_core/OsekNM.h"
#include<stdio.h>
/*平台无关的定义*/
typedef unsigned char TimerOutFlag_t;
//定义时间类型，未初始化(未调用InitDirectNMParams)这些参数就用下面定义的
//网络管理报文的ID
#define NMID 0x18ffA019
//设置节点源地址,节点地址不能为0
#define ADDR_SELF 0x19
#define NM_TIMETYPE_TTYP     100
#define NM_TIMETYPE_TMAX     260
#define NM_TIMETYPE_TERROR   1000
#define NM_TIMETYPE_TWBS     5000
//定义定时器类型
#define NM_TIMER_TTYP    0
#define NM_TIMER_TMAX    1
#define NM_TIMER_TERROR  2
#define NM_TIMER_TWBS    3

//打印功能
//#define PRINT
//返回值定义
#define E_OK     0
#define E_ERROR -1
//平台相关的定义
//#define OSEKOS //需要使用OSEKOS

#pragma comment(lib, "Winmm.lib")
#include <stdio.h>
#include <Windows.h>
#include <Mmsystem.h>

char SetToFIFO(NMPDU_t* msg);
char GetFromFIFO(NMPDU_t* msg);
void ClearFIFO(void);
void InitPlatform();
void InitNMPDU();
NMTypeU8_t TX_CAN_Transmit(NMPDU_t* NMPDU);
int SetAlarm(NMTimerType_t timer);
void CancelAlarm(int TimerId);
TimerOutFlag_t GetTimerIsOut(NMTimerType_t TimerType);
void ClcTimerOutFlag(NMTimerType_t TimerType);

//定时器设置
void WINAPI SpyTmr_TimerTMax1(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
void WINAPI SpyTmr_TimerRing1(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
void WINAPI SpyTmr_TimerLimpHome1(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
void WINAPI SpyTmr_TimerWaitBusSleep(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);


//不使用OS的话，使用自定义的定时器函数
#ifndef OSEKOS
int SetAlarm(NMTimerType_t timer);
void CancelAlarm(int TimerId);
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
#endif
#endif
