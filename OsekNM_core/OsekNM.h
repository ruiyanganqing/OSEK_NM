/*
*OsekNM的状态、内部接口、系统对象、各项参数在此定义
*/
#ifndef OSEKNMSTATE_H
#define OSEKNMSTATE_H

void NMStateManage(void);

typedef unsigned char NetIdType_t;
typedef unsigned char NMTypeU8_t;
typedef unsigned int NMTypeU16_t;
typedef unsigned long NMTypeU32_t;
typedef unsigned char NMStateType_t;
typedef unsigned char NMCountType_t;
typedef unsigned int  NMTimerType_t;
typedef unsigned char  NMTidType_t;
typedef unsigned long NMMsgID_t;
typedef unsigned char NMMsgDA_t;
typedef unsigned char NMMsgCtl_t;
typedef unsigned char NMMsgData_t;

//OsekNM的所有内部状态封装到OsekNM结构体
/*typedef struct {
	NMNodeCfg_t NodeCfg;
	void (*NMInit)();
	void (*NMLimpHome)();
	void (*NMReset)();
	void (*NMNormal)();
	void (*NMPrepareSleep)();
	void (*NMTwbsNormal)();
	void (*NMBusSleep)();
	void (*NMPrepareBusSleep)();
	void (*NMWaitBusSleep)();
}OsekNM_t;*/

//最大网络节点数
#define MAXNODE 20;
//发送接收错误极值
#define TXLIMIT 8
#define RXLIMIT 4
//报文长度
#define OSEKNM_DLC 8
//定义报文类型
#define NMMSGTYPE_ALIVE    (1<<0)
#define NMMSGTYPE_RING     (1<<1)
#define NMMSGTYPE_LIMPHOME (1<<2)
#define NMMSGTYPE_SI       (1<<4)
#define NMMSGTYPE_SA       (1<<5)
//网络最大节点数,一个网段的节点应该不会超过20个
#define NM_PRESENTNUM   20
#define NM_LIMPHOMENUM  20

//定义网络状态类型
#define NM_OFF      0
#define NM_ON       1
#define NM_SHUTDOWN 2
#define NM_BUSSLEEP 3
#define NM_AWAKE    4
#define NM_INIT     5
#define NM_LIMPHOME 6
#define NM_NORMAL   7
#define NM_RESET    8
#define NM_TWBS_NORMAL        9
#define NM_TWBS_LIMPHOME      10
#define NM_NORMAL_PREPSLEEP   11
#define NM_LIMPHOME_PREPSLEEP 12
#define NM_INIT_RESET         13
#define NM_INIT_LIMPHOME      14
#define NM_INIT_NORMAL        15
#define NM_INIT_BUSSLEEP      17

//网络节点的配置
typedef struct{
	char Self;          //自身地址
	char LogicPre;      //逻辑前继节点地址
	char LogicSuccessor;//逻辑后继节点地址

	struct NMPara{   //网络管理的参数，调用API初始化或者是用配置文件里面定义的
		NMTypeU32_t NMAddr;//NM报文的ID
		NMTypeU16_t NMTtyp;
		NMTypeU16_t NMTMax;
		NMTypeU16_t NMTError;
		NMTypeU16_t NMTWBS;
	}nmpara;

	struct NetWorkStatus{  //网络状态
		char BusSleep;
		char ConfigurationStable;
		char NMActive;
	}networkstatus;   

	struct NMMarker{      //对节点自身状态的标记
		char Stable;   //稳定建环
		char LimpHome;//节点为LimpHome
	}nmmarker;

	struct Config{       //LimpHome、Normal等配置，提交给应用程序
		char Present[NM_PRESENTNUM];
		char LimpHome[NM_LIMPHOMENUM];
	}config;   
}NMNodeCfg_t;

//NM报文类型定义
typedef struct {
	NMMsgID_t MsgID; //报文ID
	NMMsgDA_t MsgDA; //目的地址
	NMMsgCtl_t MsgCtl;//控制字节
	NMMsgData_t MsgData[6];//数据域
}NMPDU_t;

//定时器、网络地址、节点地址等配置参数
typedef struct {
	NMTypeU32_t NMAddr;
	NMTypeU8_t NodeAddr;
	NMTypeU16_t TTYP;
	NMTypeU16_t TMAX;
	NMTypeU16_t TError;
	NMTypeU16_t TWBS;
}ConfPara_t;
#endif
