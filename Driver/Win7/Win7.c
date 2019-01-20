#include "win7.h"
#ifdef WIN7PC
//与WIN7平台相关的代码在这里实现，包括NM报文缓冲区、定时器

//定时器设置
static MMRESULT TidTTyp;
static MMRESULT TidTMax;
static MMRESULT TidTError;
static MMRESULT TidTLimpHome;
static MMRESULT TidTWBS;
//报文缓冲区定义
static RecvFIFO_t RecvFIFO;

//定时器超时标志
static TimerOutFlag_t TimerOutFlag_TTYP = 0;
static TimerOutFlag_t TimerOutFlag_TMAX = 0;
static TimerOutFlag_t TimerOutFlag_TERROR = 0;
static TimerOutFlag_t TimerOutFlag_TWBS = 0;


//NMPDU初始化，保留位置1
void InitNMPDU(NMPDU_t* NMPDU)
{
	int i = 0;
	NMPDU->MsgCtl = 0xc8;
	//NMPDU->MsgID = ((NMID << 8) | ADDR_SELF);
	//NMPDU->MsgDA = ADDR_SELF;

	for (; i < 6; i++)
	{
		NMPDU->MsgData[i] = 0xff;
	}
}

//返回定时器是否超时 -1:错误
TimerOutFlag_t GetTimerIsOut(NMTimerType_t TimerType)
{
	switch (TimerType)
	{
	case NM_TIMER_TTYP:
		return TimerOutFlag_TTYP;
	case NM_TIMER_TMAX:
		return TimerOutFlag_TMAX;
	case NM_TIMER_TERROR:
		return TimerOutFlag_TERROR;
	case NM_TIMER_TWBS:
		return TimerOutFlag_TWBS;
	}
	return -1;
}

//清除定时器超时标志
void ClcTimerOutFlag(NMTimerType_t TimerType)
{
	switch (TimerType)
	{
	case NM_TIMER_TTYP:
		TimerOutFlag_TTYP = 0;
		break;
	case NM_TIMER_TMAX:
		TimerOutFlag_TMAX = 0;
		break;
	case NM_TIMER_TERROR:
		TimerOutFlag_TERROR = 0;
		break;
	case NM_TIMER_TWBS:
		TimerOutFlag_TWBS = 0;
		break;
	}
}


//FIFO相关的函数
/*说明：SetFIFO，将收到的报文放入FIFO,并调整FIFO
* 参数：GenericMessage* msg，报文指针
* 返回值：0:成功放入报文到FIFO，1：放入失败
*/
char SetToFIFO(NMPDU_t* msg)
{
	if (RecvFIFO.FullFlag == 1)//先判断缓冲区满否
		return 1;
	/*放入报文到缓冲区*/
	RecvFIFO.MSGs[RecvFIFO.Tail% FIFOMAX] = *msg;
	RecvFIFO.Tail = (RecvFIFO.Tail + 1) % FIFOMAX;
	/*清除空标识*/
	RecvFIFO.EmptyFlag = 0;
	if ((RecvFIFO.Tail + 1) == RecvFIFO.Head)//缓冲区满
		RecvFIFO.FullFlag = 1;
	return 0;
}
/*说明：GetFIFO，从FIFO取出报文,并调整FIFO
* 参数：GenericMessage* msg，报文指针
* 返回值：1:成功取出报文，0：取出失败
*/
char GetFromFIFO(NMPDU_t* msg)
{
	int i = 2;
	if (RecvFIFO.EmptyFlag == 1)//先判断缓冲区空否
		return 0;
	/*从缓冲区取出报文*/
	msg->MsgDA = RecvFIFO.MSGs[RecvFIFO.Head% FIFOMAX].MsgDA;
	msg->MsgCtl = RecvFIFO.MSGs[RecvFIFO.Head% FIFOMAX].MsgCtl;
	msg->MsgID = RecvFIFO.MSGs[RecvFIFO.Head% FIFOMAX].MsgID;
	//数据域直接复制
	for (; i < DLC; i++)
	{
		msg->MsgData[i] = RecvFIFO.MSGs[RecvFIFO.Head% FIFOMAX].MsgData[i];
	}
	RecvFIFO.Head = (RecvFIFO.Head + 1) % FIFOMAX;
	/*清除满标识*/
	RecvFIFO.FullFlag = 0;
	if ((RecvFIFO.Tail) == RecvFIFO.Head)//缓冲区空
		RecvFIFO.EmptyFlag = 1;
	return 1;
}
/*说明：ClearFIFO，清空整个FIFO
* 参数：void
* 返回值：void
*/
void ClearFIFO(void)
{
	RecvFIFO.Total = 0;
	RecvFIFO.Head = 0;
	RecvFIFO.Tail = 0;
	RecvFIFO.FullFlag = 0;
	RecvFIFO.EmptyFlag = 1;
}
/*定时器*/

/*函数名：TX_CAN_Transmit
*参数：NMPDU
*返回值：成功 1
*说明：平台自己的报文发送函数的实现
*/
NMTypeU8_t TX_CAN_Transmit(NMPDU_t* NMPDU)
{
	int i;
	printf("ID: %x Data: ",NMPDU->MsgID);
	printf("%x ", NMPDU->MsgDA);
	printf("%x ", NMPDU->MsgCtl);
	for (i = 0; i < 6; i++)
	{
		printf("%x ",NMPDU->MsgData[i]);
	}
	printf("\n");
	return 1;
}
//平台相关的初始化
void InitPlatform()
{
	/*缓冲区初始化*/
	RecvFIFO.GetMsg = GetFromFIFO;
	RecvFIFO.SetMsg = SetToFIFO;
	RecvFIFO.ClearBuff = ClearFIFO;
	RecvFIFO.ClearBuff();
}

//定时器超时函数
/*LimpHome定时器*/
static void WINAPI TimerTError(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	TimerOutFlag_TERROR = 1;
#ifdef PRINT
	printf("TError out\n");
#endif
}

/*TMax超时定时器*/
static void WINAPI TimerTMax(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	TimerOutFlag_TMAX = 1;
#ifdef PRINT
	printf("TError out\n");
#endif
}

/*TTYP定时器*/
static void WINAPI TimerTTYP(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	TimerOutFlag_TTYP = 1;
#ifdef PRINT
	printf("TTyp out\n");
#endif
}
/*WaitBusSleep定时器*/
static void WINAPI  TimerTWBS(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	TimerOutFlag_TWBS = 1;
#ifdef PRINT
	printf("TWBS out\n");
#endif
}
/*
*自定义定时器函数：SetAlarm
参数：定时器类型
说明：根据定时器类型，自动绑定定时器超时时间
*/
int SetAlarm(NMTimerType_t timer)
{
	int Tid = 0;
	switch (timer)
	{
	case NM_TIMER_TTYP:
		TidTTyp = timeSetEvent(NM_TIMETYPE_TTYP, 1, (LPTIMECALLBACK)TimerTTYP, 1, TIME_ONESHOT);
		Tid = TidTTyp;
		break;
	case NM_TIMER_TMAX:
		TidTMax = timeSetEvent(NM_TIMETYPE_TMAX, 1, (LPTIMECALLBACK)TimerTMax, 1, TIME_ONESHOT);
		Tid = TidTMax;
		break;
	case NM_TIMER_TERROR:
		TidTError = timeSetEvent(NM_TIMETYPE_TERROR, 1, (LPTIMECALLBACK)TimerTError, 1, TIME_ONESHOT);
		Tid = TidTError;
		break;
	case NM_TIMER_TWBS:
		TidTWBS = timeSetEvent(NM_TIMETYPE_TWBS, 1, (LPTIMECALLBACK)TimerTWBS, 1, TIME_ONESHOT);
		Tid = TidTWBS;
		break;
	}
	return Tid;
}
/*
*自定义定时器函数：CancelAlarm
参数：定时器ID
说明：删除已经存在的定时器
*/
void CancelAlarm(int TimerId)
{
	timeKillEvent(TimerId);
}
#endif