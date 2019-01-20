//定义OsekNM规范的服务
#ifndef OSEKNMSERVER_H
#define OSEKNMSERVER_H
#include "OSEKNM.h"
//返回值定义
#define E_OK     0
#define E_ERROR -1
typedef unsigned char StatusType_t;
typedef unsigned char NMModeName_t;
typedef unsigned char NodeIdType_t;
typedef unsigned char TickType_t;
//网络Mode
#define Awake    0
#define Bussleep 1

//服务函数接口
StatusType_t StartNM(void);
StatusType_t StopNM(void);
StatusType_t GotoMode(NMModeName_t NewMode);
StatusType_t InitDirectNMParams(NMTypeU32_t Netid, NMTypeU8_t NodeId, NMTypeU16_t TimerTyp,
	NMTypeU16_t TimerMax, NMTypeU16_t TimerError, NMTypeU16_t TimerWBS, NMTypeU16_t TimerTx);
StatusType_t SilentNM(void);
StatusType_t TalkNM(void);
#endif
