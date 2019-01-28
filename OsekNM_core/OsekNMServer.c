/*
*实现OSEK_NM规范的服务，该服务提供给上层程序
*/
#include "OsekNMServer.h"
#include "OsekNM.h"

//节点当前状态
extern NMStateType_t NMCurrentState;
extern NMStateType_t NMCurrentSubState;
//节点上一个状态
extern NMStateType_t  NMPreState;

extern NMTypeU8_t CalledGotoModeAwake;
extern NMTypeU8_t CalledGotoModeBusSleep;
extern NMNodeCfg_t NodeCfg;
extern ConfPara_t ConfPara;
extern NMTypeU8_t ConfigedPara;
extern int TidTimer;
/*函数名：StartNM
*参数：通信网络的地址
*返回值：E_OK 无错
*说明：开启网络管理，网络状态从NMOFF转移到NMON
*/
/*函数名：StartNM
*参数：通信网络的地址
*返回值：E_OK 无错
*说明：开启网络管理，网络状态从NMOFF转移到NMON
*/
StatusType_t StartNM()
{
	/*NM状态从NMOFF到NMON*/
	NMCurrentState = NM_INIT;
	NMPreState = NM_OFF;
	NMStateManage();
	return E_OK;
}

/*函数名：StopNM
*参数：通信网络的地址
*返回值：E_OK 无错
*说明：关闭网络管理，网络状态从NMON转移到NMShutdown，处理完NMShutdown的任务后转移到NMOFF
*/
StatusType_t StopNM()
{
	/*NM状态从NMON到NMOFF*/
	NMCurrentState = NM_SHUTDOWN;
	NMPreState = NM_INIT;
	//关闭资源
	return E_OK;
}

/*函数名：GotoMode
*参数：Netid：通信网络的地址，NewMode：要设置的模式，只有BusSleep和Awake
*返回值：E_OK 无错
*说明：设置节点的networkstatus.BusSleep
*/
StatusType_t GotoMode(NMModeName_t NewMode)
{
	switch (NewMode)
	{
	case Awake:
		NodeCfg.networkstatus.BusSleep = 0;
		CalledGotoModeAwake = 1;
		break;
	case Bussleep:
		NodeCfg.networkstatus.BusSleep = 1;
		CalledGotoModeBusSleep = 1;
		break;
	}
	return E_OK;
}

/*函数名：InitDirectNMParams
*参数：Netid：通信网络的地址，NodeId：节点地址，TimerTyp：两个Ring报文间的典型时间间隔，TimerMax：两个Ring报文间的最大时间间隔，
       TimerError：两个LimpHome报文间的时间间隔，TimerWBS：进入BusSleep的等待时间，TimerTx：重新传输请求的延迟
*返回值：E_OK 无错
*说明：关闭网络管理，网络状态从NMON转移到NMShutdown，处理完NMShutdown的任务后转移到NMOFF
*/
StatusType_t InitDirectNMParams(NMTypeU32_t Netid, NMTypeU8_t NodeId, NMTypeU16_t TimerTyp,
	NMTypeU16_t TimerMax, NMTypeU16_t TimerError, NMTypeU16_t TimerWBS, NMTypeU16_t TimerTx)
{
	/*NM状态从NMOFF到NMON*/
	ConfPara.NMAddr = Netid;
	ConfPara.NodeAddr = NodeId;
	ConfPara.TError = TimerError;
	ConfPara.TMAX = TimerMax;
	ConfPara.TTYP = TimerTyp;
	ConfPara.TWBS = TimerWBS;
	ConfigedPara = 1;
	return E_OK;
}

/*函数名：SilentNM
*参数：Netid：通信网络的地址
*返回值：E_OK 无错
*说明：禁止网络通信，网络状态从NMActive转移到NMPassive
*/
StatusType_t SilentNM()
{
	/*NM状态从NMOFF到NMON*/
	NodeCfg.networkstatus.NMActive = 0;
	return E_OK;
}

/*函数名：TalkNM
*参数：Netid：通信网络的地址
*返回值：E_OK 无错
*说明：使能网络通信，网络状态从NMPassive转移到NMActive
*/
StatusType_t TalkNM()
{
	/*NM状态从NMOFF到NMON*/
	NodeCfg.networkstatus.NMActive = 1;
	return E_OK;
}
