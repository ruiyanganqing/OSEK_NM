
/*
* 实现OSEK_NM各个状态下的逻辑
*/
//因为OSEKNM在编译时就应该确定在哪个平台使用，所以这里包含平台相关的头文件
#include "OsekNM.h"
#include "Driver_Common.h"
#define PRINT  //开启输出功能

//节点当前状态
NMStateType_t NMCurrentState = NM_OFF;
//节点当前子状态
NMStateType_t NMCurrentSubState = NM_OFF;
//节点上一个状态
NMStateType_t  NMPreState = NM_OFF;
//发送错误计数
static NMCountType_t NMTXCount = 0;
//接受错误计数
static NMCountType_t NMRXCount = 0;

//定时器ID
static NMTidType_t NMTidTTYP = 0;
static NMTidType_t NMTidTMAX = 0;
static NMTidType_t NMTidTError = 0;
static NMTidType_t NMTidTWBS = 0;
//GotoMode(xxx)调用标志，作为消息使用
NMTypeU8_t CalledGotoModeAwake = 0;
NMTypeU8_t CalledGotoModeBusSleep = 0;

//参数已经配置过
NMTypeU8_t ConfigedPara = 0;
//NMNodeCfg对象
NMNodeCfg_t NodeCfg;
//初始化配置参数
ConfPara_t ConfPara;

/*
*说明：处理NMInit状态的任务
* TXCount清零;
* RXCount清零;
*
*参数：无
*返回值:无
*/
static void NMInit()
{
	NMTypeU8_t i = 0;
#ifdef PRINT
	printf("NMInit\n");
#endif
	/*节点配置初始化*/
	NodeCfg.networkstatus.NMActive = 1;
	NodeCfg.Self = ConfigedPara ? ConfPara.NodeAddr : ADDR_SELF;
	NodeCfg.LogicSuccessor = ConfigedPara ? ConfPara.NodeAddr : ADDR_SELF;
	NodeCfg.LogicPre = ConfigedPara ? ConfPara.NodeAddr : ADDR_SELF;
	NodeCfg.networkstatus.BusSleep = 0;
	NodeCfg.nmpara.NMAddr = ConfigedPara ? ConfPara.NodeAddr : NMID;
	NodeCfg.nmpara.NMTtyp = ConfigedPara ? ConfPara.TTYP : NM_TIMETYPE_TTYP;
	NodeCfg.nmpara.NMTMax = ConfigedPara ? ConfPara.TMAX : NM_TIMETYPE_TMAX;
	NodeCfg.nmpara.NMTError = ConfigedPara ? ConfPara.TError : NM_TIMETYPE_TERROR;
	NodeCfg.nmpara.NMTWBS = ConfigedPara ? ConfPara.TWBS : NM_TIMETYPE_TWBS;
	//初始化硬件    
#ifdef OSEKOS
	D_Init();
#endif
	InitPlatform();
	/*向应用程序提交LimpHome配置*/
	for (i = 0; i < NM_LIMPHOMENUM; i++)
	{
		NodeCfg.config.LimpHome[i] = 0;
	}
	/*向应用程序提交Present配置*/
	for (i = 0; i < NM_PRESENTNUM; i++)
	{
		NodeCfg.config.Present[i] = 0;
	}
	NMCurrentState = NM_RESET;
	NMCurrentSubState = NM_INIT_RESET;
	NMPreState = NM_INIT;
}


/*
*说明：处理NMReset状态的任务
*      1.发送Alive报文
*      2.TXCount++
*      3.RXCount++
*参数：无
*返回值:无
*/
static void NMReset()
{
	NMTypeU8_t i = 0;
	NMPDU_t NMMsgTx;
	NMTypeU8_t NMTxFlag = 0;//作为报文发送标志
#ifdef PRINT
	printf("NMReset\n");
#endif
	/*NMInitReset子状态的任务*/
	if (NMCurrentSubState == NM_INIT_RESET)
	{    
       #ifdef OSEKOS
		//使能应用程序通信
		D_Online();
       #endif
		NMTXCount = 0;
		NMRXCount = 0;
	}
	/*单纯的NMReset的任务*/
	/*1.重置系统默认配置
	*重置逻辑后继和present为自身
	*/
	for (; i < NM_PRESENTNUM; i++)
	{
		NodeCfg.config.Present[i] = NodeCfg.Self;
	}
	NodeCfg.LogicSuccessor = NodeCfg.Self;

	/*2.NMRXCount++*/
	NMRXCount++;

	/*3.初始化NMPDU*/
	InitNMPDU(&NMMsgTx);
	//判断是否处于网络激活状态
	if (NodeCfg.networkstatus.NMActive){
		/*4.发送Alive报文,NMTXCOUNT++*/
		NMMsgTx.MsgID = NodeCfg.nmpara.NMAddr;
		NMMsgTx.MsgCtl |= NMMSGTYPE_ALIVE;
		NMMsgTx.MsgDA = NodeCfg.Self;
		TX_CAN_Transmit(&NMMsgTx);
	  NMTXCount++;
	}

	if ((NMTXCount <= TXLIMIT) && (NMRXCount <= RXLIMIT))
	{
		//设置TTYP定时器
		NMTidTTYP = SetAlarm(NM_TIMER_TTYP);
		//进入NMNormal状态
		NMCurrentState = NM_NORMAL;
		NMCurrentSubState = NM_NORMAL;
		NMPreState = NM_RESET;
	}
	//进入LimpHome状态
	else
	{
		NMTidTError = SetAlarm(NM_TIMER_TERROR);
		NMCurrentState = NM_LIMPHOME;
		NMCurrentSubState = NM_LIMPHOME;
		NMPreState = NM_RESET;
	}
}

/*
*说明：处理NMLimpHome状态的任务
*      按TError发送LimpHome报文
*      睡眠条件满足，发送SI=1的LimpHome报文，切换到PrepareSleep状态
*      睡眠条件满足且收到SA=1的报文，切换到NMTwbsNormal状态
*      LimpHome报文发送成功且收到其他节点的NM报文，进入NMReset状态。
*参数：无
*返回值:无
*/
static void NMLimpHome()
{
	NMPDU_t NMMsgRecv;
	NMPDU_t NMMsgTx;
	NMTypeU8_t NMTxFlag = 0;//作为报文发送标志
#ifdef PRINT
	printf("NMLimpHome\n");
#endif
	while (1)
	{
		//TERROR超时事件发生
		if (GetTimerIsOut(NM_TIMER_TERROR))
		{
#ifdef OSEKOS
			D_Online();
#endif
			ClcTimerOutFlag(NM_TIMER_TERROR);//清超时标志
			//满足睡眠条件
			if (NodeCfg.networkstatus.BusSleep){
				NMTidTMAX = SetAlarm(NM_TIMER_TMAX);
				if (NodeCfg.networkstatus.NMActive)
				{
					/*3.发送SI=1的LimpHome报文*/
					InitNMPDU(&NMMsgTx);
					NMMsgTx.MsgCtl |= (NMMSGTYPE_LIMPHOME | NMMSGTYPE_SI);
					NMMsgTx.MsgDA = NodeCfg.Self;
					NMMsgTx.MsgID = NodeCfg.nmpara.NMAddr;
					NMTxFlag = TX_CAN_Transmit(&NMMsgTx);
				}
				NMCurrentState = NM_LIMPHOME_PREPSLEEP;
				NMCurrentSubState = NM_LIMPHOME_PREPSLEEP;
				NMPreState = NM_LIMPHOME;
				CancelAlarm(NM_TIMER_TERROR);
				break;
			}
			//不满足睡眠条件
			else {
				NMTidTError = SetAlarm(NM_TIMER_TERROR);
				if (NodeCfg.networkstatus.NMActive)
				{
					/*3.发送LimpHome报文*/
					InitNMPDU(&NMMsgTx);
					NMMsgTx.MsgCtl |= NMMSGTYPE_LIMPHOME;
					NMMsgTx.MsgDA = NodeCfg.Self;
					NMMsgTx.MsgID =NodeCfg.nmpara.NMAddr;
					NMTxFlag = TX_CAN_Transmit(&NMMsgTx);
				}
				continue;
			}
		}
		//发送了任意的NM报文
		if (NMTxFlag)
		{
			NMTxFlag = 0;
			if (NMMsgTx.MsgCtl & NMMSGTYPE_LIMPHOME){
				NodeCfg.nmmarker.LimpHome = 1;
			}
			continue;
		}
		//收到任意的NM报文
		if (GetFromFIFO(&NMMsgRecv))
		{
			#ifdef PRINT
			printf("Id:%lx DA:%x\n", NMMsgRecv.MsgID, NMMsgRecv.MsgDA);
			#endif
			if (((NodeCfg.networkstatus.NMActive) && !(NodeCfg.nmmarker.LimpHome) && (!(NMMsgRecv.MsgCtl & NMMSGTYPE_SA))) ||
				((NodeCfg.networkstatus.NMActive) && (NodeCfg.nmmarker.LimpHome) && (NodeCfg.networkstatus.BusSleep) && (!(NMMsgRecv.MsgCtl & NMMSGTYPE_SA))) ||
				(!(NodeCfg.networkstatus.NMActive) && (NodeCfg.networkstatus.BusSleep) && (!(NMMsgRecv.MsgCtl & NMMSGTYPE_SA))) ||
				(!(NodeCfg.networkstatus.NMActive) && !(NodeCfg.networkstatus.BusSleep))||
				((NodeCfg.networkstatus.NMActive) && (NodeCfg.nmmarker.LimpHome) && !(NodeCfg.networkstatus.BusSleep)))
			{
				CancelAlarm(NMTidTError);
				NodeCfg.nmmarker.LimpHome = 0;			
				NMCurrentState = NM_RESET;
				NMCurrentSubState = NM_INIT_RESET;
				NMPreState = NM_LIMPHOME;
				break;

			}
			else if ((!(NodeCfg.networkstatus.NMActive) && (NodeCfg.networkstatus.BusSleep) && (NMMsgRecv.MsgCtl & NMMSGTYPE_SA)) ||
				((NodeCfg.networkstatus.NMActive) && (NodeCfg.nmmarker.LimpHome) && (NodeCfg.networkstatus.BusSleep) && (NMMsgRecv.MsgCtl & NMMSGTYPE_SA)) ||
				((NodeCfg.networkstatus.NMActive) && !(NodeCfg.nmmarker.LimpHome) && (NMMsgRecv.MsgCtl & NMMSGTYPE_SA)))
			{
#ifdef OSEKOS
				D_Offline();
#endif
				CancelAlarm(NMTidTError);
				NMTidTWBS = SetAlarm(NM_TIMER_TWBS);
				NMCurrentState = NM_TWBS_LIMPHOME;
				NMCurrentSubState = NM_TWBS_LIMPHOME;
				NMPreState = NM_LIMPHOME;
				break;
			}
		}
	}
}

/*
*说明：处理NMLimpHomePrepSleep状态的任务
*参数：无
*返回值:无
*/
static void NMLimpHomePrepSleep()
{
	NMPDU_t NMMsgRecv;
#ifdef PRINT
	printf("NMLimpHomePrepSleep\n");
#endif
	while (1)
	{
		//GotoMode(Awake)被调用
		if (CalledGotoModeAwake)
		{
			CalledGotoModeAwake = 0;
			NMCurrentState = NM_LIMPHOME;
			NMCurrentSubState = NM_LIMPHOME;
			NMPreState = NM_LIMPHOME_PREPSLEEP;
			NMTidTError = SetAlarm(NM_TIMER_TERROR);
			break;
		}
		//收到任意的NM报文
		if (GetFromFIFO(&NMMsgRecv)){
			//收到的报文的SI=0
			if (!(NMMsgRecv.MsgCtl & NMMSGTYPE_SI))
			{
				NMCurrentState = NM_LIMPHOME;
				NMCurrentSubState = NM_LIMPHOME;
				NMPreState = NM_LIMPHOME_PREPSLEEP;
				NMTidTError = SetAlarm(NM_TIMER_TERROR);
				break;
			}
			/*收到SA=1的报文*/
			//参考的SDL未专门处理
			else{
				continue;
			}
		}
		//TMAX超时
		if (GetTimerIsOut(NM_TIMER_TMAX))
		{
			ClcTimerOutFlag(NM_TIMER_TMAX);
#ifdef OSEKOS
			D_Offline();
#endif
			CancelAlarm(NM_TIMER_TMAX);
			NMTidTWBS = SetAlarm(NM_TIMER_TWBS);
			NMCurrentState = NM_TWBS_LIMPHOME;
			NMCurrentSubState = NM_TWBS_LIMPHOME;
			NMPreState = NM_LIMPHOME;
			break;
		}
	}
}

/*
*说明：处理NMTwbsLimpHome状态的任务
*参数：无
*返回值:无
*/
static void NMTwbsLimpHome()
{
	NMPDU_t NMMsgRecv;
#ifdef PRINT
	printf("NMTwbsLimpHome\n");
#endif
	while (1)
	{
		//GotoMode(Awake)被调用
		if (CalledGotoModeAwake)
		{
			CalledGotoModeAwake = 0;
			CancelAlarm(NMTidTWBS);
			NMTidTError = SetAlarm(NM_TIMER_TERROR);
			NMCurrentState = NM_LIMPHOME;
			NMCurrentSubState = NM_LIMPHOME;
			NMPreState = NM_TWBS_LIMPHOME;
			break;
		}
		//收到任意的NM报文
		if (GetFromFIFO(&NMMsgRecv)){
			//收到的报文的SI=0
			if (!(NMMsgRecv.MsgCtl & NMMSGTYPE_SI))
			{
				NMCurrentState = NM_LIMPHOME;
				NMCurrentSubState = NM_LIMPHOME;
				NMPreState = NM_TWBS_LIMPHOME;
				CancelAlarm(NMTidTWBS);
				NMTidTError = SetAlarm(NM_TIMER_TERROR);
				break;
			}
			else{
				continue;
			}
		}
		//TWBS超时
		if (GetTimerIsOut(NM_TIMER_TWBS))
		{
			NMCurrentState = NM_BUSSLEEP;
			NMCurrentSubState = NM_BUSSLEEP;
			NMPreState = NM_TWBS_LIMPHOME;
			CancelAlarm(NMTidTWBS);
#ifdef OSEKOS
			D_Offline();
#endif
			break;
		}
	}
}

/*
*说明：根据节点地址查找LimpHome中的指定的节点，同一网段的节点数不超过20
*
*参数：Node 节点地址
*返回值:节点在LimpHome中的位置 -1:错误
*/
static char FineLimpHomeNode(NMTypeU8_t Node)
{
	//遍历整个LimpHome数组
	NMTypeU8_t i;
	for (i = 0; (i < NM_PRESENTNUM); i++)
	{
		if (NodeCfg.config.LimpHome[i] == 0)
			return i;
		if (NodeCfg.config.LimpHome[i] == Node)
		{
			return i;
		}
	}
	return -1;
}

/*
*说明：根据节点地址查找Present中的指定的节点，同一网段的节点数不超过20
*      
*参数：Node 节点地址
*返回值:节点在Present中的位置,-1 失败
*/
static char FinePresentNode(NMTypeU8_t Node)
{
	//遍历整个Present数组
	NMTypeU8_t i;
	for (i = 0; (i < NM_PRESENTNUM); i++)
	{
		//找到第一个0就返回
		if (NodeCfg.config.Present[i] == 0)
			return i;
		//找到该节点已经存在
		if (NodeCfg.config.Present[i] == Node)
		{
			return i;
		}
	}
	return -1;
}
//更新逻辑后继
static void EnsureLogicSuccessor(NMPDU_t* NMMsg)
{
	NMTypeU8_t SA = ((NMMsg->MsgID) & 0xff);
	NMTypeU8_t LA = NodeCfg.LogicSuccessor;
	NMTypeU8_t RA = NodeCfg.Self;
	if ((LA == RA) || ((SA < LA) && (LA < RA)) || ((LA < RA) && (RA < SA)) || ((RA < SA) && (SA < LA)))
	{
		NodeCfg.LogicSuccessor = SA;
	}
}

//判断是否被跳过 1:跳过
static NMTypeU8_t IsSkiped(NMPDU_t* NMMsg)
{
	NMTypeU8_t DA = NMMsg->MsgDA;
	NMTypeU8_t SA = ((NMMsg->MsgID)&0xff);
	if (((DA < SA) && (SA < NodeCfg.Self)) || ((SA < NodeCfg.Self) && (NodeCfg.Self < DA)) || ((NodeCfg.Self < DA) && (DA < SA)))
	{
		return 1;
	}
	return 0;
}
/*
*说明：处理NMNormal状态的子任务
*      清除RXCount
*      根据收到的Alive报文和Ring报文，更新网络拓扑
*      根据收到的LimpHome报文，更新网络拓扑
*      判断是否被跳过，被跳过则发送Alive报文
*参数：NMPDU
*返回值:无
*/
static void NormalStandardNM(NMPDU_t* NMMsg,NMTypeU8_t* NMTxFlag)
{
	NMTypeU8_t Index;
	NMTypeU8_t SA;
	NMPDU_t NMMsgTx;
	NMRXCount = 0;
	//判断报文类型,Alive和Ring报文
	if ((NMMsg->MsgCtl & (NMMSGTYPE_ALIVE)) || (NMMsg->MsgCtl & (NMMSGTYPE_RING)))
	{
		//添加在线配置
		//取出源地址到NodeCfg.config.Present
		SA = (NMMsg->MsgID & 0xff);
		Index = FinePresentNode(SA);
		NodeCfg.config.Present[Index] = SA;
		//确定逻辑后继
		EnsureLogicSuccessor(NMMsg);
		//Alive报文，更新逻辑环为不稳定
		if ((NMMsg->MsgCtl & (NMMSGTYPE_ALIVE)))
		{
			NodeCfg.nmmarker.Stable = 0;
			NodeCfg.networkstatus.ConfigurationStable = 0;
			return ;
		}
		//Ring报文
		else if ((NMMsg->MsgCtl & (NMMSGTYPE_RING)))
		{
			CancelAlarm(NMTidTTYP);
			CancelAlarm(NMTidTMAX);
			//指向本节点或源地址=目的地址
			if ((NMMsg->MsgDA == NodeCfg.Self) || (NMMsg->MsgDA == SA))
			{
				NMTidTTYP = SetAlarm(NM_TIMER_TTYP);
			}
			
			else{
				NMTidTMAX = SetAlarm(NM_TIMER_TMAX);
				//判断是否被跳过
				if (IsSkiped(NMMsg))
				{
					if (NodeCfg.networkstatus.NMActive)
					{
						if (NodeCfg.networkstatus.BusSleep)
						{
							InitNMPDU(&NMMsgTx);
							NMMsgTx.MsgCtl |= ((NMMSGTYPE_SI)|(NMMSGTYPE_ALIVE));
							NMMsgTx.MsgDA = NodeCfg.Self;
							NMMsgTx.MsgID = NodeCfg.nmpara.NMAddr;
							*NMTxFlag = TX_CAN_Transmit(&NMMsgTx);
						}
						else
						{
							InitNMPDU(&NMMsgTx);
							NMMsgTx.MsgCtl |= (NMMSGTYPE_ALIVE);
							NMMsgTx.MsgDA = NodeCfg.Self;
							NMMsgTx.MsgID = NodeCfg.nmpara.NMAddr;
							*NMTxFlag = TX_CAN_Transmit(&NMMsgTx);
						}
					}
				}
				else{
					return;
				}
			}
		}
	}
	//LimpHome报文
	else{
		//添加LimpHome配置
		//取出源地址到NodeCfg.config.LimpHome
		SA = (NMMsg->MsgID & 0xff);
		Index = FineLimpHomeNode(SA);
		NodeCfg.config.LimpHome[Index] = SA;
	}
}

/*
*说明：处理NMNormal状态的任务
*      开始TTyp计时，准备发送第一条Ring报文
*      根据收到的Alive报文和Ring报文，更新网络拓扑
*      若发送和接受成功，则清除TXCount和RXCount
*      判断是否被跳过，被跳过则发送Alive报文
*参数：无
*返回值:无
*/
static void NMNormal()
{
	NMPDU_t NMMsgRecv;
	NMPDU_t NMMsgTx;
	NMTypeU8_t NMTxTTYPFlag = 0;
	NMTypeU8_t NMTxRecvFlag = 0;
#ifdef PRINT
	printf("NMNormal\n");
#endif
	while (1)
	{
		//收到了NM报文
		if (GetFromFIFO(&NMMsgRecv))
		{
			NMTXCount = 0;
			NormalStandardNM(&NMMsgRecv, &NMTxRecvFlag);
			#ifdef PRINT
			printf("Id:%lx DA:%x\n", NMMsgRecv.MsgID, NMMsgRecv.MsgDA);
			#endif
			if (NMMsgRecv.MsgCtl & NMMSGTYPE_SA)
			{
				if (NodeCfg.networkstatus.BusSleep)
				{
					//NMInitWaitBusSleep
#ifdef OSEKOS
					D_Offline();
#endif
					CancelAlarm(NMTidTMAX);
					CancelAlarm(NMTidTTYP);
					NMTidTWBS = SetAlarm(NM_TIMER_TWBS);
					NMCurrentState = NM_TWBS_NORMAL;
					NMCurrentSubState = NM_TWBS_NORMAL;
					NMPreState = NM_NORMAL;
					break;
				}
				else{
					continue;
				}
			}
			else {
				continue;
			}
		}
		//TTYP超时
		if (GetTimerIsOut(NM_TIMER_TTYP))
		{
			ClcTimerOutFlag(NM_TIMER_TTYP);
			CancelAlarm(NMTidTMAX);
			NMTidTMAX = SetAlarm(NM_TIMER_TMAX);
			//网络管理激活
			if (NodeCfg.networkstatus.NMActive)
			{
				if (NodeCfg.networkstatus.BusSleep)
				{
					InitNMPDU(&NMMsgTx);
					NMMsgTx.MsgCtl |= ((NMMSGTYPE_SI) | (NMMSGTYPE_RING));
					NMMsgTx.MsgDA = NodeCfg.LogicSuccessor;
					NMMsgTx.MsgID = NodeCfg.nmpara.NMAddr;
					NMTxTTYPFlag = TX_CAN_Transmit(&NMMsgTx);
				}
				else{
					InitNMPDU(&NMMsgTx);
					NMMsgTx.MsgCtl |= ((NMMSGTYPE_RING));
					NMMsgTx.MsgDA = NodeCfg.LogicSuccessor;
					NMMsgTx.MsgID = NodeCfg.nmpara.NMAddr;
					NMTxTTYPFlag = TX_CAN_Transmit(&NMMsgTx);
				}
				NMTXCount++;
			}
			//发送错误计数器超限
			if (NMTXCount > TXLIMIT)
			{
				CancelAlarm(NMTidTMAX);
				NMTidTError = SetAlarm(NM_TIMER_TERROR);
				//进入LimpHome状态
				NMCurrentState = NM_LIMPHOME;
				NMCurrentSubState = NM_LIMPHOME;
				NMPreState = NM_NORMAL;
				break;
			}
			//Stable是什么意思？？向应用程序提交稳定配置
			else{
				if (NodeCfg.nmmarker.Stable)
				{
					NodeCfg.networkstatus.ConfigurationStable = 1;
				}
				else{
					NodeCfg.nmmarker.Stable = 1;
				}
			}
			continue;
		}
		//TMAX超时
		if (GetTimerIsOut(NM_TIMER_TMAX))
		{
			ClcTimerOutFlag(NM_TIMER_TMAX);
			//进入NMInitReset状态
			NMCurrentState = NM_RESET;
			NMCurrentSubState = NM_RESET;
			NMPreState = NM_NORMAL;
			break;
		}
		//GotoMode(BusSleep)被调用
		if (CalledGotoModeBusSleep)
		{
			CalledGotoModeBusSleep = 0;
			if (NodeCfg.networkstatus.NMActive)
			{
				continue;
			}
			else{
				NMCurrentState = NM_NORMAL_PREPSLEEP;
				NMCurrentSubState = NM_NORMAL_PREPSLEEP;
				NMPreState = NM_NORMAL;
				break;
			}
		}
		//发送了NM报文
		if (NMTxTTYPFlag || NMTxRecvFlag)
		{
			NMTxTTYPFlag = 0;
			NMTxRecvFlag = 0;
			NMTXCount = 0;
			//发送的是Ring报文
			if (NMMsgTx.MsgCtl&(NMMSGTYPE_RING))
			{
				CancelAlarm(NMTidTMAX);
				CancelAlarm(NMTidTTYP);
				NMTidTMAX = SetAlarm(NM_TIMER_TMAX);
				/*发送的Ring报文的SI=1*/
				if (NMMsgTx.MsgCtl & (NMMSGTYPE_SI))
				{
					if (NodeCfg.networkstatus.BusSleep)
					{
						NMCurrentState = NM_NORMAL_PREPSLEEP;
						NMCurrentSubState = NM_NORMAL_PREPSLEEP;
						NMPreState = NM_NORMAL;
						break;
					}
					else{
						continue;
					}
				}
				else{
					continue;
				}
			}
			else{
				continue;
			}
		}
	}
}

/*
*说明：处理NMNormalPrepSleep状态的任务
*参数：无
*返回值:无
*说明：
*/
static void NMNormalPrepSleep()
{
	NMPDU_t NMMsgRecv;
	NMPDU_t NMMsgTx;
	NMTypeU8_t NMTxTTYPFlag = 0;
	NMTypeU8_t NMTxRecvFlag = 0;
#ifdef PRINT
	printf("NMPrepareBusSleep\n");
#endif
	while (1)
	{
		//收到了NM报文
		if (GetFromFIFO(&NMMsgRecv))
		{
			NormalStandardNM(&NMMsgRecv, &NMTxRecvFlag);
			//SI=1
			if (NMMsgRecv.MsgCtl & NMMSGTYPE_SI)
			{
				if (NMMsgRecv.MsgCtl & NMMSGTYPE_SA)//ACK=1
				{
					//if (NodeCfg.networkstatus.BusSleep)
					{
						//NMInitWaitBusSleep
#ifdef OSEKOS
						D_Offline();
#endif
						CancelAlarm(NMTidTMAX);
						CancelAlarm(NMTidTTYP);
						NMTidTWBS = SetAlarm(NM_TIMER_TWBS);
						NMCurrentState = NM_TWBS_NORMAL;
						NMCurrentSubState = NM_TWBS_NORMAL;
						NMPreState = NM_NORMAL_PREPSLEEP;
						break;
					}
				}
				//ACK=0
				else{
					continue;
				}
			}
			//SI=0
			else {
				NMCurrentState = NM_NORMAL;
				NMCurrentSubState = NM_NORMAL;
				NMPreState = NM_NORMAL_PREPSLEEP;
				break;
			}
		}
		//TTYP超时
		if (GetTimerIsOut(NM_TIMER_TTYP))
		{
			ClcTimerOutFlag(NM_TIMER_TTYP);
			if (NodeCfg.networkstatus.NMActive)
			{
				InitNMPDU(&NMMsgTx);
				NMMsgTx.MsgCtl |= ((NMMSGTYPE_SA) | (NMMSGTYPE_RING) | (NMMSGTYPE_SI));
				NMMsgTx.MsgDA = NodeCfg.LogicSuccessor;
				NMMsgTx.MsgID = NodeCfg.nmpara.NMAddr;
				NMTxTTYPFlag = TX_CAN_Transmit(&NMMsgTx);	

			}
			continue;
		}
		//TMAX超时
		if (GetTimerIsOut(NM_TIMER_TMAX))
		{
			ClcTimerOutFlag(NM_TIMER_TMAX);
			//进入NMInitReset状态
			NMCurrentState = NM_RESET;
			NMCurrentSubState = NM_INIT_RESET;
			NMPreState = NM_NORMAL_PREPSLEEP;
			break;
		}
		//GotoMode(Awake)被调用
		if (CalledGotoModeAwake)
		{
			CalledGotoModeAwake = 0;
			NMCurrentState = NM_NORMAL;
			NMCurrentSubState = NM_NORMAL;
			NMPreState = NM_NORMAL_PREPSLEEP;
			break;
		}
		//发送了NM报文
	    if (NMTxTTYPFlag || NMTxRecvFlag)
		{
			NMTxTTYPFlag = 0;
			NMTxRecvFlag = 0;
			//NMInitWaitBusSleep
#ifdef OSEKOS
			D_Offline();
#endif
			CancelAlarm(NMTidTMAX);
			CancelAlarm(NMTidTTYP);
			NMTidTWBS = SetAlarm(NM_TIMER_TWBS);
			NMCurrentState = NM_TWBS_NORMAL;
			NMCurrentSubState = NM_TWBS_NORMAL;
			NMPreState = NM_NORMAL_PREPSLEEP;
			break;
		}
	}
	
}

/*
*说明：处理NMTwbsNormal状态的任务
*参数：无
*返回值:无
*/
static void NMTwbsNormal()
{
	NMPDU_t NMMsgRecv;
	NMTypeU8_t NMTxFlag = 0;
#ifdef PRINT
	printf("NMTwbsNormal\n");
#endif
	while (1)
	{
		//TWBS超时
		if (GetTimerIsOut(NM_TIMER_TWBS))
		{
#ifdef OSEKOS
			D_Init();
#endif
			NMCurrentState = NM_BUSSLEEP;
			NMCurrentSubState = NM_BUSSLEEP;
			NMPreState = NM_TWBS_NORMAL;
			break;
		}
		//收到NM报文
		if (GetFromFIFO(&NMMsgRecv))
		{
			//SI = 1
			if (NMMsgRecv.MsgCtl & NMMSGTYPE_SI)
			{
				continue;
			}
			//SI = 0
			else{
				CancelAlarm(NMTidTWBS);
				NMCurrentState = NM_RESET;
				NMCurrentSubState = NM_INIT_RESET;
				NMPreState = NM_TWBS_NORMAL;
				break;
			}
		}
		//GotoMode(Awake)调用
		if (CalledGotoModeAwake)
		{
			CancelAlarm(NMTidTWBS);
			NMCurrentState = NM_RESET;
			NMCurrentSubState = NM_INIT_RESET;
			NMPreState = NM_TWBS_NORMAL;
			break;
		}
	}
}


/*
*说明：处理NMBusSleep状态的任务
*参数：无
*返回值:无
*/
static void NMBusSleep()
{
	NMPDU_t NMMsg;
#ifdef PRINT
	printf("NMBusSleep\n");
#endif

	while (1)
	{
		//GotoMode(Awake)被调用
		if (CalledGotoModeAwake)
		{
			CalledGotoModeAwake = 0;
			NMCurrentState = NM_INIT;
			NMCurrentSubState = NM_INIT;
			NMPreState = NM_BUSSLEEP;

			break;
		}
		//收到总线唤醒信号，SI = 0
		if (GetFromFIFO(&NMMsg)){
			//收到的报文的SI=0
			if (!(NMMsg.MsgCtl & NMMSGTYPE_SI))
			{
				NMCurrentState = NM_INIT;
				NMCurrentSubState = NM_INIT;
				NMPreState = NM_BUSSLEEP;
				break;
			}
			else{
				continue;
			}
		}
	}
}
//对网络状态的转换进行管理
void NMStateManage()
{
	while (1)
	{
		switch (NMCurrentState){
		case NM_INIT:
			NMInit();
			break;
		case NM_RESET:
			NMReset();
			break;
		case NM_NORMAL:
			NMNormal();
			break;
		case NM_LIMPHOME:
			NMLimpHome();
			break;
		case NM_NORMAL_PREPSLEEP:
			NMNormalPrepSleep();
			break;
		case NM_LIMPHOME_PREPSLEEP:
			NMLimpHomePrepSleep();
			break;
		case NM_TWBS_NORMAL:
			NMTwbsNormal();
			break;
		case NM_TWBS_LIMPHOME:
			NMTwbsLimpHome();
			break;
		case NM_BUSSLEEP:
			NMBusSleep();
			break;
		}		  
	}
}



