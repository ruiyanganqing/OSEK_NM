#include "configVspy.h"
#include "../../../Log/Log.h"
#ifdef VSPY
//与VSPY平台相关的代码在这里实现，包括NM报文缓冲区、定时器

//NM_AC报文定义
static TX_NM_AC_HS_CAN vNMAC;

//定时器设置
static char SetAlarm_TTYP = 0;
static char SetAlarm_TMAX = 0;
static char SetAlarm_TERROR = 0;
static char SetAlarm_TWBS = 0;
//定时器计数器
static int TTYP_Count = 0;
static int TMAX_Count = 0;
static int TERROR_Count = 0;
static int TWBS_Count = 0;
MMRESULT TidTimer = 0;
//报文缓冲区定义
static RecvFIFO_t RecvFIFO;

//定时器超时标志
static TimerOutFlag_t TimerOutFlag_TTYP = 0;
static TimerOutFlag_t TimerOutFlag_TMAX = 0;
static TimerOutFlag_t TimerOutFlag_TERROR = 0;
static TimerOutFlag_t TimerOutFlag_TWBS = 0;

//节点当前状态
extern NMStateType_t NMCurrentState;
//节点当前子状态
extern NMStateType_t NMCurrentSubState;
//节点上一个状态
extern NMStateType_t  NMPreState;
extern NMNodeCfg_t NodeCfg;
/*函数名：TX_CAN_Transmit
*参数：NMPDU
*返回值：成功 1
*说明：平台自己的报文发送函数的实现
*/
NMTypeU8_t TX_CAN_Transmit(NMPDU_t* NMPDU)
{
	int i;
	vNMAC.MessageData.btData[1] = NMPDU->MsgCtl;
	vNMAC.MessageData.btData[0] = NMPDU->MsgDA;
	for (i = 2; i < 8; i++)
	{
		vNMAC.MessageData.btData[i] = NMPDU->MsgData[i-2];
	}
	TX_NM_AC_HS_CAN_Transmit(&vNMAC);
	return 1;
}

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

//返回定时器是否超时,-1 失败
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
* 返回值：1:成功放入报文到FIFO，0：放入失败
*/
char SetToFIFO(GenericMessage* msg)
{
	if (RecvFIFO.FullFlag == 1)//先判断缓冲区满否
		return 0;
	/*放入报文到缓冲区*/
	RecvFIFO.MSGs[RecvFIFO.Tail% FIFOMAX] = *msg;
	RecvFIFO.Tail = (RecvFIFO.Tail + 1) % FIFOMAX;
	/*清除空标识*/
	RecvFIFO.EmptyFlag = 0;
	if ((RecvFIFO.Tail + 1) == RecvFIFO.Head)//缓冲区满
		RecvFIFO.FullFlag = 1;
	return 1;
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
	msg->MsgDA = RecvFIFO.MSGs[RecvFIFO.Head% FIFOMAX].btData[0];
	msg->MsgCtl = RecvFIFO.MSGs[RecvFIFO.Head% FIFOMAX].btData[1];
	msg->MsgID = RecvFIFO.MSGs[RecvFIFO.Head% FIFOMAX].iID;
	//数据域直接复制
	for (; i < DLC; i++)
	{
		msg->MsgData[i] = RecvFIFO.MSGs[RecvFIFO.Head% FIFOMAX].btData[i];
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

//定时器超时函数
/*LimpHome定时器*/
static void TimerOutTERROR()
{
	TimerOutFlag_TERROR = 1;
#ifdef PRINT_LOG
	char buf[100];
	sprintf(buf, "TError out State:%d\n", NMCurrentState);
	LogOutPut(buf);
#endif
}

/*TMax超时定时器*/
static void TimerOutTMAX()
{
	TimerOutFlag_TMAX = 1;
#ifdef PRINT_LOG
	char buf[100];
	sprintf(buf, "TMAX out State:%d\n", NMCurrentState);
	LogOutPut(buf);
#endif
}

/*TTYP定时器*/
static void TimerOutTTYP()
{
	TimerOutFlag_TTYP = 1;
#ifdef PRINT_LOG
	char buf[100];
	sprintf(buf, "TTYP out State:%d\n", NMCurrentState);
	LogOutPut(buf);
#endif
}
/*WaitBusSleep定时器*/
static void TimerOutTWBS()
{
	TimerOutFlag_TWBS = 1;
#ifdef PRINT_LOG
	char buf[100];
	sprintf(buf, "TWBS out State:%d\n", NMCurrentState);
	LogOutPut(buf);
#endif
}

//10ms定时器
static void WINAPI Timer10(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	/*调用SetAlarm(xx)，定时器开始递增*/
	if (SetAlarm_TTYP)
	{
		TTYP_Count++;

		if (TTYP_Count >= 10)//TTYP=100ms
		{
			TTYP_Count = 0;//重新计数
			TimerOutTTYP();
			SetAlarm_TTYP = 0;//每次用完定时器都将其关闭,从而简化定时器管理
		}
	}
	else {
		TTYP_Count = 0;
	}
	if (SetAlarm_TMAX)
	{
		TMAX_Count++;
		if (TMAX_Count >= 26)//TMAX=260ms
		{
			TMAX_Count = 0;//重新计数
			TimerOutTMAX();
			SetAlarm_TMAX = 0;//每次用完定时器都将其关闭
		}
	}
	else {
		TMAX_Count = 0;
	}
	if (SetAlarm_TERROR)
	{
		TERROR_Count++;
		if (TERROR_Count >= 100)//TError=1000ms
		{
			TERROR_Count = 0;//重新计数
			TimerOutTERROR();
			SetAlarm_TERROR = 0;//每次用完定时器都将其关闭
		}
	}
	else {
		TERROR_Count = 0;
	}
	if (SetAlarm_TWBS)
	{
		TWBS_Count++;
		if (TWBS_Count >= 500)//TError=5000ms
		{
			TWBS_Count = 0;//重新计数
			TimerOutTWBS();
			SetAlarm_TWBS = 0;//每次用完定时器都将其关闭
		}
	}
	else {
		TWBS_Count = 0;
	}
	/*判断是否超时*/
}

//平台相关的初始化
void InitPlatform()
{
	/*缓冲区初始化*/
	RecvFIFO.GetMsg = GetFromFIFO;
	RecvFIFO.SetMsg = SetToFIFO;
	RecvFIFO.ClearBuff = ClearFIFO;
	RecvFIFO.ClearBuff();
	TX_NM_AC_HS_CAN_Init(&vNMAC);
	vNMAC.iDefaultPeriodMilliseconds = 0;
	vNMAC.MessageData.iID = NMID;
	vNMAC.MessageData.iNetwork = NET_HS_CAN;
	vNMAC.MessageData.iNumDataBytes = 8;
	/*定时器初始化*/
	/*不是首次初始化，需要关闭原来的定时器*/
	if (NMPreState == NM_BUSSLEEP)
	{
		timeKillEvent(TidTimer);
	}
	TidTimer = timeSetEvent(10, 1, (LPTIMECALLBACK)Timer10, 1, TIME_PERIODIC);
}


/*
*自定义定时器函数：SetAlarm
参数：定时器类型
说明：每次调用都使定时器重新从0开始
*返回值：定时器ID，用定时器类型ID代替定时器ID
*/
int SetAlarm(NMTimerType_t timer)
{
	int Tid = 0;
	switch (timer)
	{
	case NM_TIMER_TTYP:
		SetAlarm_TTYP = 1;
		TTYP_Count = 0;
		TimerOutFlag_TTYP = 0;//每次设置定时器前先清除标志位
		Tid = NM_TIMER_TTYP;
		break;
	case NM_TIMER_TMAX:
		TMAX_Count = 0;
		SetAlarm_TMAX = 1;
		TimerOutFlag_TMAX = 0;//每次设置定时器前先清除标志位
		Tid = NM_TIMER_TMAX;
		break;
	case NM_TIMER_TERROR:
		TERROR_Count = 0;
		SetAlarm_TERROR = 1;
		TimerOutFlag_TERROR = 0;//每次设置定时器前先清除标志位
		Tid = NM_TIMER_TERROR;
		break;
	case NM_TIMER_TWBS:
		TWBS_Count = 0;
		SetAlarm_TWBS = 1;
		TimerOutFlag_TWBS = 0;//每次设置定时器前先清除标志位
		Tid = NM_TIMER_TWBS;
		break;
	}
	return Tid;
}
/*
*自定义定时器函数：CancelAlarm
参数：定时器类型
说明：定时器清0，不再计数
*/
void CancelAlarm(NMTimerType_t timer)
{
	switch (timer)
	{
	case NM_TIMER_TTYP:
		TTYP_Count = 0;
		SetAlarm_TTYP = 0;
		TimerOutFlag_TTYP = 0;//每次关闭定时器先清除标志位
		break;
	case NM_TIMER_TMAX:
		TMAX_Count = 0;
		SetAlarm_TMAX = 0;
		TimerOutFlag_TMAX = 0;//每次关闭定时器先清除标志位
		break;
	case NM_TIMER_TERROR:
		TERROR_Count = 0;
		SetAlarm_TERROR = 0;
		TimerOutFlag_TERROR = 0;//每次关闭定时器先清除标志位
		break;
	case NM_TIMER_TWBS:
		TWBS_Count = 0;
		SetAlarm_TWBS = 0;
		TimerOutFlag_TWBS = 0;//每次关闭定时器先清除标志位
		break;
	}
}
void Spy_EveryMessage(GenericMessage * p_Msg)
{
	static i = 0;
	/*将所有收到的NM报文放入缓冲区FIFO*/
    /*Vspy有一个Bug，自己发出去的报文，也会被这里收到*/
	if (((p_Msg->iID) != NMID) && ((p_Msg->iID>>8) == (NMID>>8)))//过滤网络报文，不接收自己发出去的
	{
		i++;
		RecvFIFO.SetMsg(p_Msg);//暂时不处理返回值
		//printf("on msg :%d\n",i);
#ifdef PRINT_LOG
		char buf[100];
		sprintf(buf, "on msg-State:%d ID:%x DA:%x Ctr:%x\n", NMCurrentState, p_Msg->iID, p_Msg->btData[0], p_Msg->btData[1]);
		LogOutPut(buf);
#endif
		
	}
}
/*
void SpyAppSig_AS_NM_AC(double dNewValue)
{
	// TODO: Add Event Code
	if (dNewValue == 0.0)
		NMStart = 0;
	else if (dNewValue == 1.0)
		NMStart = 1;
	else if (dNewValue == 2.0)
		SleepFlag = 1;
	else if (dNewValue == 3.0)
		SleepFlag = 0;
	printf("NMStart:%d\n", NMStart);
	printf("SleepFlag:%d\n", SleepFlag);
}*/
#endif