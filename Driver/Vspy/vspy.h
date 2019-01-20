// vspy generated header file
#ifndef VSPY_GENERATED_HEADER
#define VSPY_GENERATED_HEADER
#include "windows.h"
#include "string.h"
#include <stdio.h>
extern void * g_uiHandle;
typedef unsigned __int64 uint64;

#define printf Printf
int Printf(const char *szInMsg, ...);
int PrintfW(const wchar_t *szInMsg, ...);
int WriteLine(const char *szInMsg, ...);
int WriteLineW(const wchar_t *szInMsg, ...);
void DisplayLastError(LPCWSTR lpszFunction);

typedef void (* RS232OnError_fdef)(DWORD port, DWORD errorFlags);
typedef void (* RS232OnRxTx_fdef)(DWORD port, BYTE buffer[], DWORD dwSize);

DWORD ICS_RS232Open(DWORD port);
DWORD ICS_RS232Close(DWORD port);
DWORD ICS_RS232ConfigTimeout(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity, DWORD timeout);
DWORD ICS_RS232Config(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity);
DWORD ICS_RS232SetHandshake(DWORD port, DWORD handshake, DWORD XonLimit, DWORD XoffLimit, DWORD XonChar, DWORD XoffChar);
DWORD ICS_RS232SetSignalLine(DWORD port, DWORD line, DWORD state);
WORD ICS_RS232WriteByte(DWORD port, DWORD data);
WORD ICS_RS232WriteBlock(DWORD port, BYTE buffer[], DWORD size);
DWORD ICS_RS232Send(DWORD port, BYTE buffer[], DWORD size);
DWORD ICS_RS232Receive(DWORD port, BYTE buffer[], DWORD size);
void ICS_RS232CloseAllPorts();

typedef void	(__stdcall *lpOut32)(short, short);
typedef short	(__stdcall *lpInp32)(short);
typedef BOOL	(__stdcall *lpIsInpOutDriverOpen)(void);
void LoadInpOut();
void UnloadInpout();

#define J1939Priority(id)                   ((unsigned long)((id >> 26) & 0x7))
#define J1939PGN(id)                        ((unsigned long)((id >> 8) & 0x3FFFF))
// PGN is composed of EDP, DP, PF and PS which follow.
#define J1939ExtDataPage(id)                ((unsigned char)((id >> 25) & 0x1))
#define J1939DataPage(id)                   ((unsigned char)((id >> 24) & 0x1))
#define J1939PduFormat(id)                  ((unsigned char)((id >> 16) & 0xFF))
#define J1939PduSpecific(id)                ((unsigned char)((id >> 8) & 0xFF))
#define J1939SourceAddress(id)              ((unsigned char)(id & 0xFF))
#define J1939DestinationAddress(id)         ((unsigned char)(J1939PduFormat(id) < 240) ? ((id >> 8) & 0xFF) : 0)

#define SetJ1939Priority(id, prio)          (id = (prio << 26) | (id & 0x7FFFFFF))
#define SetJ1939PGN(id, pgn)                (id = (pgn << 8) | (id & 0xFF))
// PGN is composed of EDP, DP, PF and PS which follow.
#define SetJ1939ExtDataPage(id, edp)        (id = (edp << 25) | (id & 0x1DFFFFFF))
#define SetJ1939DataPage(id, dp)            (id = (dp << 24) | (id & 0x1EFFFFFF))
#define SetJ1939PduFormat(id, pf)           (id = (pf << 16) | (id & 0x1F00FFFF))
#define SetJ1939PduSpecific(id, ps)         (id = (ps << 8) | (id & 0x1FFF00FF))
#define SetJ1939SourceAddress(id, sa)       (id = sa | (id & 0x1FFFFF00))
#define SetJ1939DestinationAddress(id, da)  SetJ1939PduSpecific(id, da)

int Spy_TextAPI_W(wchar_t * wcCommand, wchar_t * wcResponse, int iResponseMaxLength);
int Spy_TextAPI(char * szCommand, char * szResponse, int iResponseMaxLength);

#define CM_CALLBACKTYPE_APP_SIGNAL                     0
#define CM_CALLBACKTYPE_MESSAGE                        1
#define CM_CALLBACKTYPE_TIMER                          2
#define CM_CALLBACKTYPE_MESSAGE_MG                     3
#define CM_CALLBACKTYPE_MESSAGE_TX                     4
#define CM_CALLBACKTYPE_BEFORE_MESSAGE_TX   5

#define CM_GETSET_SET_APP_SIGNAL                       0
#define CM_GETSET_GET_APP_SIGNAL                       1
#define CM_GETSET_SET_TMR_VALUE                        2
#define CM_GETSET_GET_TMR_VALUE                        3
#define CM_GETSET_SET_TMR_ENABLE                       4
#define CM_GETSET_GET_TMR_ENABLE                       5
#define CM_GETSET_FBLOCK_START                         6
#define CM_GETSET_FBLOCK_STOP                          7
#define CM_GETSET_FBLOCK_TRIGGER                       8
#define CM_GETSET_FBLOCK_SAVE                          9
#define CM_GETSET_FBLOCK_GET_ISRUNNING                10
#define CM_GETSET_FBLOCK_GET_ISTRIGGERED              11
#define CM_GETSET_FBLOCK_GET_NUMCOLLECTED             12
#define CM_GETSET_MSG_STATS_CLR                       13
#define CM_GETSET_DB_STATS_CLR                        14
#define CM_GETSET_TX_STATS_CLR                        15
#define CM_GETSET_NET_STATS_CLR                       16
#define CM_GETSET_NODE_STATS_CLR                      17
#define CM_GETSET_MSG_STATS_GET                       18
#define CM_GETSET_DB_STATS_GET                        19
#define CM_GETSET_TX_STATS_GET                        20
#define CM_GETSET_NET_STATS_GET                       21
#define CM_GETSET_NODE_STATS_GET                      22
#define CM_GETSET_SET_APP_SIGNAL_TEXT                 23
#define CM_GETSET_GET_APP_SIGNAL_TEXT                 24
#define CM_GETSET_DB_DLC_GET                          25
#define CM_GETSET_DB_NETWORK_GET                      26
#define CM_GETSET_DB_PERIOD_GET                       27
#define CM_GETSET_MSG_DLC_GET                         28
#define CM_GETSET_MSG_NETWORK_GET                     29
#define CM_GETSET_MSG_PERIOD_GET                      30
#define CM_GETSET_TX_DLC_GET                          31
#define CM_GETSET_TX_NETWORK_GET                      32
#define CM_GETSET_TX_PERIOD_GET                       33
#define CM_GETSET_SPY_LOCK                            34
#define CM_GETSET_SPY_UNLOCK                          35
#define CM_GETSET_DIAG_JOB_ISRUNNING                  36
#define CM_GETSET_DIAG_JOB_NumMessagesCollected       37
#define CM_GETSET_DIAG_JOB_Successful                 38
#define CM_GETSET_DIAG_JOB_ECUResponseCount           39
#define CM_GETSET_DIAG_JOB_TotalTimeAbs               40
#define CM_GETSET_DIAG_JOB_Last7FSubFunctionEx78      41
#define CM_GETSET_DIAG_JOB_7FCountEx78                42
#define CM_GETSET_DIAG_JOB_7FCountResponsePending     43
#define CM_GETSET_DIAGJOB_START                       44
#define CM_GETSET_DIAGJOB_STOP                        45
#define CM_GETSET_DIAGJOB_SAVE                        46
#define CM_GETSET_FBLOCK_ADD                          47
#define CM_GETSET_FBLOCK_FIND                         48
#define CM_GETSET_FBLOCK_POSTTRIGGER                  49
#define CM_GETSET_SET_TMR_PERIOD                      50
#define CM_GETSET_GET_TMR_TIME_TO_ELAPSE              51
#define CM_GETSET_GET_TIMENS                          52
#define CM_GETSET_SET_CAN_MODE                        53
#define CM_GETSET_SET_BTR                             54
#define CM_GETSET_STOP_MEASUREMENT                    55
#define CM_GETSET_CLEAR_TRACES                        56
#define CM_GETSET_FBLOCK_PAUSE                        57
#define CM_GETSET_FBLOCK_CONTINUE                     58
#define CM_GETSET_SYS_EXIT                            59
#define CM_GETSET_SYS_MINIMIZE                        60
#define CM_GETSET_GET_DB_NAME                         61
#define CM_GETSET_SET_LIN_WAKEUP_PARMS                62
#define CM_GETSET_SEND_LIN_WAKEUP                     63
#define CM_GETSET_SEND_LIN_SLEEP                      64
#define CM_GETSET_IL_ACTION                           65
#define CM_GETSET_SET_TXSIGNAL                        66
#define CM_GETSET_SET_APP_SIGNAL_AT                   67
#define CM_GETSET_GET_APP_SIGNAL_AT                   68
#define CM_GETSET_SET_APP_SIGNAL_TEXT_AT              69
#define CM_GETSET_GET_APP_SIGNAL_TEXT_AT              70
#define CM_GETSET_GET_NODE_NAME                       71
#define CM_GETSET_GET_NODE_TYPE                       72
#define CM_GETSET_GET_STATION_ADDR                    73
#define CM_GETSET_SET_APP_ACTIVE                      74
#define CM_GETSET_GET_SYS_CONF                        75
#define CM_GETSET_GET_REQ_STATE                       76
#define CM_GETSET_GET_SYS_BUS_REQ                     77
#define CM_GETSET_GET_SYS_FAIL_STATES                 78
#define CM_GETSET_GET_SYS_CURR_FAIL_STATES            79
#define CM_GETSET_GET_SYS_DLL_STATES                  80
#define CM_GETSET_GET_TARGET_CONF                     81
#define CM_GETSET_SET_TARGET_CONF                     82
#define CM_GETSET_GET_IS_WAKEUP_NODE                  83
#define CM_GETSET_GET_IND_ACTIVE_OTHER_BUS            84
#define CM_GETSET_REQ_NET_SHUTDOWN                    85
#define CM_GETSET_REQ_NET_ON_OTHER_BUS                86
#define CM_GETSET_REQ_NET_OFF_OTHER_BUS               87
#define CM_GETSET_TABLE_FBLOCK_ACTIVATE_SLOT		    88
#define CM_GETSET_TABLE_FBLOCK_DEACTIVATE_SLOT		89

#define CM_OSEK_GET_TXID                             501
#define CM_OSEK_SET_TXID                             502
#define CM_OSEK_GET_RXID                             503
#define CM_OSEK_SET_RXID                             504
#define CM_OSEK_GET_USEFC                            505
#define CM_OSEK_SET_USEFC                            506
#define CM_OSEK_SET_0PADDING                         507
#define CM_OSEK_GET_USEEXTID                         508
#define CM_OSEK_SET_USEEXTID                         509
#define CM_OSEK_GET_BS                               510
#define CM_OSEK_SET_BS                               511
#define CM_OSEK_GET_STMIN                            512
#define CM_OSEK_SET_STMIN                            513
#define CM_OSEK_GET_EVAL1FC                          514
#define CM_OSEK_SET_EVAL1FC                          515
#define CM_OSEK_GET_TIMEOUTAR                        516
#define CM_OSEK_SET_TIMEOUTAR                        517
#define CM_OSEK_GET_TIMEOUTAS                        518
#define CM_OSEK_SET_TIMEOUTAS                        519
#define CM_OSEK_GET_TIMEOUTBR                        520
#define CM_OSEK_SET_TIMEOUTBR                        521
#define CM_OSEK_GET_TIMEOUTBS                        522
#define CM_OSEK_SET_TIMEOUTBS                        523
#define CM_OSEK_GET_TIMEOUTCR                        524
#define CM_OSEK_SET_TIMEOUTCR                        525
#define CM_OSEK_GET_1FCBS                            526
#define CM_OSEK_SET_1FCBS                            527
#define CM_OSEK_SET_FIXEDST                          528
#define CM_OSEK_GET_0PATTERN                         529
#define CM_OSEK_SET_0PATTERN                         530
#define CM_OSEK_GET_STARTSN                          531
#define CM_OSEK_SET_STARTSN                          532
#define CM_OSEK_GET_IDFROMADR                        533
#define CM_OSEK_SET_IDFROMADR                        534
#define CM_OSEK_GET_ADRFROMID                        535
#define CM_OSEK_SET_ADRFROMID                        536
#define CM_OSEK_GET_TPBASEADR                        537
#define CM_OSEK_SET_TPBASEADR                        538
#define CM_OSEK_GET_MAXMSGLEN                        539
#define CM_OSEK_SET_MAXMSGLEN                        540
#define CM_OSEK_SET_FCDELAY                          541
#define CM_OSEK_SET_WFTMAX                           542
#define CM_OSEK_GET_DATAREQ                          543
#define CM_OSEK_GET_RXDATA                           544
#define CM_OSEK_GET_SRCADR                           545
#define CM_OSEK_GET_NMSTATUS                         546
#define CM_OSEK_SET_NMSTATUS                         547
#define CM_OSEK_GET_NMCONFIG                         548
#define CM_AUTOSAR_SET_STATUS                        549
#define CM_OSEK_SET_ADDRMODE                         550
#define CM_OSEK_GET_ADDRMODE                         551
#define CM_OSEK_SET_DLCMODE                          552
#define CM_OSEK_SET_CAN                              553
#define CM_OSEK_GET_TGTADR                           554
#define CM_OSEK_SET_TGTADR                           555
#define CM_OSEK_GET_TXMODE                           556
#define CM_OSEK_SET_TXMODE                           557
#define CM_OSEK_SET_MINSTMIN                         558
#define CM_OSEK_GET_ECUNUM                           559
#define CM_OSEK_SET_ECUNUM                           560
#define CM_OSEK_GET_LOFCTADR                         561
#define CM_OSEK_SET_LOFCTADR                         562
#define CM_OSEK_GET_HIFCTADR                         563
#define CM_OSEK_SET_HIFCTADR                         564
#define CM_OSEK_GET_MSGCOUNT                         565
#define CM_OSEK_SET_MSGCOUNT                         566
#define CM_OSEK_GET_TXPRIO                           567
#define CM_OSEK_SET_TXPRIO                           568
#define CM_OSEK_GET_FFPRIO                           569
#define CM_OSEK_SET_FFPRIO                           570
#define CM_OSEK_GET_FCPRIO                           571
#define CM_OSEK_SET_FCPRIO                           572
#define CM_OSEK_GET_USEALLAE                         573
#define CM_OSEK_SET_USEALLAE                         574
#define CM_OSEK_GET_TXTOTHRESHOLD                    575
#define CM_OSEK_SET_TXTOTHRESHOLD                    576
#define CM_OSEK_GET_RECENTAE                         577
#define CM_OSEK_SET_MAXCFBURST                       578
#define CM_OSEK_GET_ADREXT                           579
#define CM_OSEK_SET_ADREXT                           580
#define CM_OSEK_CONNECTREQ                           581
#define CM_OSEK_GET_CAN                              582
#define CM_OSEK_GET_0PADDING                         583
#define CM_OSEK_GET_FIXED_DLC                        584
#define CM_GET_VIEWCOUNT						   	   600
#define CM_GET_VIEWHANDLE					   	   	   601
#define CM_GET_VIEWTYPE							   602
#define CM_GET_VIEWPROCADDRESS					   603
#define CM_SET_SHOWVIEW							   604
#define CM_SET_HIDEVIEW							   605
#define CM_GET_VIEWISVISIBLE					   	   606
#define CM_SET_SHOWVIEWBYTYPE			               607

// Send this struct to CM_GET_VIEWPROCADDRESS
typedef struct _stGetViewProcAddressArgs
{
	void* InForm;
	const char* InFunctionName;
	void* OutFunctionPtr;
} stGetViewProcAddressArgs;

// Send this struct to CM_GET_VIEWTYPE
typedef struct _stGetViewTypeArgs
{
	void* InForm;
	int OutType;
} stGetViewTypeArgs;

// Send this struct to CM_GET_VIEWISVISIBLE
typedef struct _stGetViewIsVisibleArgs
{
	void* InForm;
	int OutVisible;
} stGetViewIsVisibleArgs;

// Typedefs for function pointers returned by CM_GET_VIEWPROCADDRESS
typedef int(_stdcall* VideoFrameReview_GetMaxCamCount)(void* pForm);
typedef int(_stdcall* VideoFrameReview_CamIsVisible)(void* pForm, int camIndex);
typedef void(_stdcall* VideoFrameReview_AddRect)(void* pForm, int cam, float percentLeft, float percentTop, float percentRight, float percentBottom, int color, int thickness);
typedef void(_stdcall* VideoFrameReview_ClearRects)(void* pForm, int camIndex);
typedef int(_stdcall* VideoFrameReview_AddText)(void* pForm, int cam, const char* text, float percentLeft, float percentTop, int color, int size);
typedef void(_stdcall* VideoFrameReview_UpdateText)(void* pForm, int cam, int index, const char* text, float percentLeft, float percentTop, int color, int size);
typedef void(_stdcall* VideoFrameReview_ClearTexts)(void* pForm, int cam);
typedef int(_stdcall* VideoFrameReview_AddBitmap)(void* pForm, int cam, float percentLeft, float percentTop, float percentRight, float percentBottom, int visible, const wchar_t* imagePath);
typedef void(_stdcall* VideoFrameReview_UpdateBitmap)(void* pForm, int cam, int index, float percentLeft, float percentTop, float percentRight, float percentBottom, int visible);
typedef void(_stdcall* VideoFrameReview_ClearBitmaps)(void* pForm, int cam);

#define ATTR_LIN_TX_SENDSLAVE                       0x10
#define ATTR_LIN_TX_CLASSIC_CHECKSUM                0x20
#define ATTR_LIN_TX_SEND_BREAK_ONLY                 0x40
#define ATTR_LIN_TX_SEND_HDR_ONLY                   0x80
#define ATTR_ACTIVE_INIT                            0x10
#define ATTR_CAN_29BIT_ID_FRAME                     0x20
#define ATTR_CAN_REMOTE_FRAME                       0x40
#define ATTR_CAN_TX_HIGH_VOLTAGE                    0x80
#define ATTR_ALL_RX_TRANSMIT                           1
#define ATTR_ALL_RX_ERROR                              2
#define ATTR_LIN_RX_MASTER_TX                      0x100
#define ATTR_LIN_RX_SLAVE_TX                       0x200
#define ATTR_CANFD_FRAME                          0x1000
#define ATTR_CANFD_ESI                            0x2000
#define ATTR_CANFD_BRS                            0x4000

// Spy_ErrorState iErrorBitfield flags
#define CAN_ERROR_STATUS_ACTIVE                   0x0000
#define CAN_ERROR_STATUS_TXRX_WARNING             0x0001  // EWARN: Transmitter or Receiver in Error State Warning bit
#define CAN_ERROR_STATUS_RX_WARNING               0x0002  // RXWAR: Receiver in Error State Warning bit
#define CAN_ERROR_STATUS_TX_WARNING               0x0004  // TXWAR: Transmitter in Error State Warning bit
#define CAN_ERROR_STATUS_RX_PASSIVE               0x0008  // RXBP: Receiver in Error State Bus Passive bit
#define CAN_ERROR_STATUS_TX_PASSIVE               0x0010  // TXBP: Transmitter in Error State Bus Passive bit
#define CAN_ERROR_STATUS_TX_BUS_OFF               0x0020  // TXBO: Transmitter in Error State Bus Off bit

#define SPY_CTL_PROP_ENABLE                       1
#define SPY_CTL_PROP_SET_BACKGROUND               2
#define SPY_CTL_PROP_SET_FOREGROUND               3
#define SPY_CTL_PROP_SET_CAPTION                  4
#define SPY_CTL_PROP_SET_LEFT                     5
#define SPY_CTL_PROP_SET_TOP                      6
#define SPY_CTL_PROP_SET_WIDTH                    7
#define SPY_CTL_PROP_SET_HEIGHT                   8
#define SPY_CTL_PROP_SET_TRANSPARENT              9
#define SPY_CTL_PROP_SET_FONT_NAME               10
#define SPY_CTL_PROP_SET_FONT_SIZE               11

struct stCallBackPointers
{
    void * pRegisterCallBack;
    void * pGetSetValueCallBack;
    void * pTransmitMessageCallBack;
    void * pOutputWindowCallBack;
    void * pTextAPICallBack;
    void * pGetSignalValue;
    void * pDecodeSignalValue;
    void * pTransmitMessagesFromSignalValues;
    void * pFindIndexForObjectFromNameCallBack;
    void * pShowPanelCallBack;
    void * pMessageGenericInit;
    void * pGetEcuCount;
    void * pGetMemoryBlockCount;
    void * pGetMemoryBlockInfo;
    void * pGetMemoryBlockData;
    void * pSetMemoryBlockData;
    void * pMessageRawInit;
    void * pSignalPhysicalToRaw;
    void * pTransmitMessagesFromRawSignalValues;
    void * pGetMessageName;
    void * pSetControlProp;
    void * pUpdateMessageSignalsFromBytes;
    void * pUpdateBytesFromSignals;
    void * pUpdateBytesFromRawSignals;
};
extern void (* CM_RegisterCallback) (void * uiHandle, unsigned short iValueType, unsigned short iIndex, void * pCallBackPointer) ;
extern void (* CM_GetSetValue) (void * uiHandle, unsigned short iValueType, unsigned short iIndex, void * pValueToSet) ;
extern int  (* CM_TextAPI) (void * uiHandle, wchar_t * pCommand, wchar_t * pResponse, int iResponseMaxLength) ;
extern int  (* CM_OutputWindow) (void * uiHandle, wchar_t * p_TextToWrite, int iColor, int iLength) ;
extern int  (* CM_TransmitMessage) (void * uiHandle, int iNetwork,int iID, int iNumDataBytes,int iBitField,unsigned char * p_btData);
extern int  (* CM_GetSignalValue) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,unsigned short iSignalIndex,void * pValueToSet);
extern int  (* CM_TxFromSignals) (void * uiHandle, unsigned short iMessageType,
                       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                       int iNetworkIndex, void * pSignalValues,
                       int iNumSignalCount);
extern int  (* CM_TxFromRawSignals) (void * uiHandle, unsigned short iMessageType,
                       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                       int iNetworkIndex, void * pSignalValues,
                       int iNumSignalCount);
extern int  (* CM_UpdateMessageSignalsFromBytes) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       unsigned char * p_btData, int iNumDataBytes);
extern int  (* CM_UpdateBytesFromSignals) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       double * p_dSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
extern int  (* CM_UpdateBytesFromRawSignals) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       uint64 * p_iSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
extern int  (* CM_FindIndexForObjectFromName) (void * uiHandle, int iObjectType,wchar_t * pName, int * p_iObjectIndex);
extern int  (* CM_GetMessageName) (void * uiHandle, int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize);
extern int  (* CM_ShowPanel) (void * uiHandle, wchar_t * pWindowName, wchar_t * pPanelName);
extern int  (* CM_SetControlProperty) (void * uiHandle, wchar_t * pPanelName, wchar_t * pWindowName, int prop, void *pValue);
extern int  (* CM_MessageGenericInit) (void * uiHandle, unsigned short iMessageType,
                       unsigned short iMessageIndex, void * p_MessageStats, int * p_iNetworkID,
                       int * p_iNumDataBytes, int  p_iNumDataMax, int * p_iPeriodMs, int * p_iID,
                       int * p_iBitField, unsigned char * p_btData, double * p_dSignals, int dSignalMaxCount,
                       int * p_iActualSignalMaxCount,__int64 * p_iTimeStampNanoSecondsHW,unsigned int * p_iTimeStampMillisecondsOS);
extern int  (* CM_MessageRawInit) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       uint64 * p_dSignals, int dSignalMaxCount, int * p_iActualSignalMaxCount);
extern uint64 (* CM_SignalPhysicalToRaw) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                       unsigned short iSignalIndex, double dPhysicalValue);
extern int  (* CM_GetEcuCount) (void * uiHandle);
extern int  (* CM_GetMemoryBlockCount) (void * uiHandle, int ecu);
extern int  (* CM_GetMemoryBlockInfo) (void * uiHandle, int ecu, int block, unsigned int *address, unsigned int *size);
extern int  (* CM_GetMemoryBlockData) (void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);
extern int  (* CM_SetMemoryBlockData) (void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);

#define CAN_ID_EXTENDED_BIT   0x80000000
#define isStdId(id) ((id & CAN_ID_EXTENDED_BIT) == 0)
#define isExtId(id) ((id & CAN_ID_EXTENDED_BIT) == CAN_ID_EXTENDED_BIT)
#define mkExtId(id) (id | CAN_ID_EXTENDED_BIT)
#define mkStdId(id) (id & (~CAN_ID_EXTENDED_BIT))
#define valOfId(id) ((long)id)
void SetUseExtendedIdBit();

#define GMLAN_SOURCE_MASK 0xff
#define GMLAN_PID_MASK    0xffff
#define GMLAND_PID_SHIFT  8
#define GMLAN_PRIO_MASK   0x07
#define GMLAND_PRIO_SHIFT 26
#define gmlanSetSourceId(id, source) (id |= (source & GMLAN_SOURCE_MASK))
#define gmlanSetPid(id, pid) (id |= ((pid & GMLAN_PID_MASK) << GMLAND_PID_SHIFT))
#define gmlanSetPrio(id, prio) (id |= ((prio & GMLAN_PRIO_MASK) << GMLAND_PRIO_SHIFT))
#define gmlanGetSourceId(id) (id & GMLAN_SOURCE_MASK)
#define gmlanGetPid(id) ((id >> GMLAND_PID_SHIFT) & GMLAN_PID_MASK)
#define gmlanGetPrio(id) ((id >> GMLAND_PRIO_SHIFT) & GMLAN_PRIO_MASK)
#define gmlanId(id, source) (id | (source & GMLAN_SOURCE_MASK))

int getStartDelay();
void setStartDelay(int delay);

void SpyShowPanel(char * pWindowName, char * pPanelName);
void SpyShowPanelW(wchar_t * pWindowName, wchar_t * pPanelName);
void SpySetControlProperty(char * pPanelName, char * pControlTag, int prop, void *pValue);
void SpySetControlPropertyW(wchar_t * pPanelName, wchar_t * pControlTag, int prop, void *pValue);
void Spy_Lock();
void Spy_Unlock();
int GetMessageName(int iMessageId, int iMessageContext, char * pName, int iBufferSize);
int GetMessageNameW(int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize);
double AS_Get(int index);
void AS_Set(int index, double dValue);
double AS_GetAt(int index, int element);
void AS_SetAt(int index, int element, double dValue);
int AS_GetText(int nIndex, void * szValue, int nLength);
int AS_SetText(int nIndex, void * szValue, int nLength);
int AS_GetTextW(int index, wchar_t * szValue);
void SpySetTxSignal(unsigned int iMessageIndex, unsigned int iSignalIndex, double dValue);
void SpySetTxSignalRaw(unsigned int iMessageIndex, unsigned int iSignalIndex, __int64 nValue);
void SpySetTxEvent(unsigned int iMessageIndex);
int AS_GetTextAtW(int index, int element, wchar_t * szValue);
int AS_SetTextAtW(int index, int element, wchar_t * szValue);
int SpyViewGetCount();
void* SpyViewGetHandle(int index);
int SpyViewGetType(void* pView);
void SpyViewShow(void* pView);
void SpyViewHide(void* pView);
int SpyViewIsVisible(void* pView);
void* SpyViewShowByType(int type);
void* SpyViewGetProcAddress(void* pView, const char* szProcName);

typedef struct {
    unsigned int iSignal;    /// signal to set
    unsigned int iType;      /// 0 physical, 1 raw
    union {
        double dValue;           /// value 
        __int64 nValue;
    };
} TxSetSignal;

// Network Statistics
typedef struct {
    unsigned int iCount;  /// count of messages on network
    unsigned int iRate; /// messages per second
    double dPercentUse; /// current bus utilization 
    unsigned int iMaxRate;    /// maximum messages per second
    double dMaxPercentUse;   /// maximum bus utilization
    unsigned int iErrorCount;   /// number of errors on a network
    unsigned int iTxCount;       /// number of messages transmitted on a network
    unsigned int iErrorRate; /// errors per second
    unsigned int iTxRate;        /// transmissions per second
    unsigned int iTxBufferFill;  /// current network buffer fill level
    unsigned int iCANTxErrCount;  /// transmit CAN errors
    unsigned int iCANRxErrCount;  /// receive CAN errors
} NetworkStats; 
int Spy_TranslateNetwork(int nNetworkOffset);
int Spy_UntranslateNetwork(int nNetwork);
int Spy_NetworksInUse();
int Spy_LINIndex(int iNetwork);

// network index variables - identify networks in vspy
extern int NET_HS_CAN;
void NET_HS_CAN_ClearStats();
void NET_HS_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_MS_CAN;
void NET_MS_CAN_ClearStats();
void NET_MS_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN;
void NET_SW_CAN_ClearStats();
void NET_SW_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1850_VPW;
void NET_J1850_VPW_ClearStats();
void NET_J1850_VPW_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K;
void NET_ISO9141_KW2K_ClearStats();
void NET_ISO9141_KW2K_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN;
void NET_LSFT_CAN_ClearStats();
void NET_LSFT_CAN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1850_PWM;
void NET_J1850_PWM_ClearStats();
void NET_J1850_PWM_GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1708;
void NET_J1708_ClearStats();
void NET_J1708_GetStats(NetworkStats * p_NetworkStats);
extern int NET_neoVI;
void NET_neoVI_ClearStats();
void NET_neoVI_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN2;
void NET_HS_CAN2_ClearStats();
void NET_HS_CAN2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN3;
void NET_HS_CAN3_ClearStats();
void NET_HS_CAN3_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN2;
void NET_LIN2_ClearStats();
void NET_LIN2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN3;
void NET_LIN3_ClearStats();
void NET_LIN3_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN4;
void NET_LIN4_ClearStats();
void NET_LIN4_GetStats(NetworkStats * p_NetworkStats);
extern int NET_CGI;
void NET_CGI_ClearStats();
void NET_CGI_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN;
void NET_LIN_ClearStats();
void NET_LIN_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_2;
void NET_ISO9141_KW2K_2_ClearStats();
void NET_ISO9141_KW2K_2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_3;
void NET_ISO9141_KW2K_3_ClearStats();
void NET_ISO9141_KW2K_3_GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_4;
void NET_ISO9141_KW2K_4_ClearStats();
void NET_ISO9141_KW2K_4_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN4;
void NET_HS_CAN4_ClearStats();
void NET_HS_CAN4_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN5;
void NET_HS_CAN5_ClearStats();
void NET_HS_CAN5_GetStats(NetworkStats * p_NetworkStats);
extern int NET_UART;
void NET_UART_ClearStats();
void NET_UART_GetStats(NetworkStats * p_NetworkStats);
extern int NET_UART2;
void NET_UART2_ClearStats();
void NET_UART2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN5;
void NET_LIN5_ClearStats();
void NET_LIN5_GetStats(NetworkStats * p_NetworkStats);
extern int NET_MOST__VNET_A_;
void NET_MOST__VNET_A__ClearStats();
void NET_MOST__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay1A__VNET_A_;
void NET_FlexRay1A__VNET_A__ClearStats();
void NET_FlexRay1A__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay1B__VNET_A_;
void NET_FlexRay1B__VNET_A__ClearStats();
void NET_FlexRay1B__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2A__VNET_A_;
void NET_FlexRay2A__VNET_A__ClearStats();
void NET_FlexRay2A__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2B__VNET_A_;
void NET_FlexRay2B__VNET_A__ClearStats();
void NET_FlexRay2B__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN__VNET_A_;
void NET_HS_CAN__VNET_A__ClearStats();
void NET_HS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_MS_CAN__VNET_A_;
void NET_MS_CAN__VNET_A__ClearStats();
void NET_MS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN__VNET_A_;
void NET_SW_CAN__VNET_A__ClearStats();
void NET_SW_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1850_VPW__VNET_A_;
void NET_J1850_VPW__VNET_A__ClearStats();
void NET_J1850_VPW__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN__VNET_A_;
void NET_LSFT_CAN__VNET_A__ClearStats();
void NET_LSFT_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1708__VNET_A_;
void NET_J1708__VNET_A__ClearStats();
void NET_J1708__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_neoVI__VNET_A_;
void NET_neoVI__VNET_A__ClearStats();
void NET_neoVI__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN2__VNET_A_;
void NET_HS_CAN2__VNET_A__ClearStats();
void NET_HS_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN3__VNET_A_;
void NET_HS_CAN3__VNET_A__ClearStats();
void NET_HS_CAN3__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN__VNET_A_;
void NET_LIN__VNET_A__ClearStats();
void NET_LIN__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN2__VNET_A_;
void NET_LIN2__VNET_A__ClearStats();
void NET_LIN2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN3__VNET_A_;
void NET_LIN3__VNET_A__ClearStats();
void NET_LIN3__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN4__VNET_A_;
void NET_LIN4__VNET_A__ClearStats();
void NET_LIN4__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_CGI__VNET_A_;
void NET_CGI__VNET_A__ClearStats();
void NET_CGI__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K__VNET_A_;
void NET_ISO9141_KW2K__VNET_A__ClearStats();
void NET_ISO9141_KW2K__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_2__VNET_A_;
void NET_ISO9141_KW2K_2__VNET_A__ClearStats();
void NET_ISO9141_KW2K_2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_3__VNET_A_;
void NET_ISO9141_KW2K_3__VNET_A__ClearStats();
void NET_ISO9141_KW2K_3__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_4__VNET_A_;
void NET_ISO9141_KW2K_4__VNET_A__ClearStats();
void NET_ISO9141_KW2K_4__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN__VNET_B_;
void NET_HS_CAN__VNET_B__ClearStats();
void NET_HS_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_MS_CAN__VNET_B_;
void NET_MS_CAN__VNET_B__ClearStats();
void NET_MS_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN__VNET_B_;
void NET_SW_CAN__VNET_B__ClearStats();
void NET_SW_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1850_VPW__VNET_B_;
void NET_J1850_VPW__VNET_B__ClearStats();
void NET_J1850_VPW__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN__VNET_B_;
void NET_LSFT_CAN__VNET_B__ClearStats();
void NET_LSFT_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_J1708__VNET_B_;
void NET_J1708__VNET_B__ClearStats();
void NET_J1708__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_neoVI__VNET_B_;
void NET_neoVI__VNET_B__ClearStats();
void NET_neoVI__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN2__VNET_B_;
void NET_HS_CAN2__VNET_B__ClearStats();
void NET_HS_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN3__VNET_B_;
void NET_HS_CAN3__VNET_B__ClearStats();
void NET_HS_CAN3__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN__VNET_B_;
void NET_LIN__VNET_B__ClearStats();
void NET_LIN__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN2__VNET_B_;
void NET_LIN2__VNET_B__ClearStats();
void NET_LIN2__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN3__VNET_B_;
void NET_LIN3__VNET_B__ClearStats();
void NET_LIN3__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN4__VNET_B_;
void NET_LIN4__VNET_B__ClearStats();
void NET_LIN4__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_CGI__VNET_B_;
void NET_CGI__VNET_B__ClearStats();
void NET_CGI__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K__VNET_B_;
void NET_ISO9141_KW2K__VNET_B__ClearStats();
void NET_ISO9141_KW2K__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_2__VNET_B_;
void NET_ISO9141_KW2K_2__VNET_B__ClearStats();
void NET_ISO9141_KW2K_2__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_3__VNET_B_;
void NET_ISO9141_KW2K_3__VNET_B__ClearStats();
void NET_ISO9141_KW2K_3__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_ISO9141_KW2K_4__VNET_B_;
void NET_ISO9141_KW2K_4__VNET_B__ClearStats();
void NET_ISO9141_KW2K_4__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN4__VNET_A_;
void NET_HS_CAN4__VNET_A__ClearStats();
void NET_HS_CAN4__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN5__VNET_A_;
void NET_HS_CAN5__VNET_A__ClearStats();
void NET_HS_CAN5__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN5__VNET_A_;
void NET_LIN5__VNET_A__ClearStats();
void NET_LIN5__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN4__VNET_B_;
void NET_HS_CAN4__VNET_B__ClearStats();
void NET_HS_CAN4__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN5__VNET_B_;
void NET_HS_CAN5__VNET_B__ClearStats();
void NET_HS_CAN5__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN5__VNET_B_;
void NET_LIN5__VNET_B__ClearStats();
void NET_LIN5__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_Ethernet_DAQ;
void NET_Ethernet_DAQ_ClearStats();
void NET_Ethernet_DAQ_GetStats(NetworkStats * p_NetworkStats);
extern int NET_Ethernet;
void NET_Ethernet_ClearStats();
void NET_Ethernet_GetStats(NetworkStats * p_NetworkStats);
extern int NET_MOST__VNET_B_;
void NET_MOST__VNET_B__ClearStats();
void NET_MOST__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay1A__VNET_B_;
void NET_FlexRay1A__VNET_B__ClearStats();
void NET_FlexRay1A__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay1B__VNET_B_;
void NET_FlexRay1B__VNET_B__ClearStats();
void NET_FlexRay1B__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2A__VNET_B_;
void NET_FlexRay2A__VNET_B__ClearStats();
void NET_FlexRay2A__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2B__VNET_B_;
void NET_FlexRay2B__VNET_B__ClearStats();
void NET_FlexRay2B__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN2;
void NET_SW_CAN2_ClearStats();
void NET_SW_CAN2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN2__VNET_A_;
void NET_SW_CAN2__VNET_A__ClearStats();
void NET_SW_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_SW_CAN2__VNET_B_;
void NET_SW_CAN2__VNET_B__ClearStats();
void NET_SW_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_FSA;
void NET_FSA_ClearStats();
void NET_FSA_GetStats(NetworkStats * p_NetworkStats);
extern int NET_TCP;
void NET_TCP_ClearStats();
void NET_TCP_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN6;
void NET_HS_CAN6_ClearStats();
void NET_HS_CAN6_GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN7;
void NET_HS_CAN7_ClearStats();
void NET_HS_CAN7_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN6;
void NET_LIN6_ClearStats();
void NET_LIN6_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN2;
void NET_LSFT_CAN2_ClearStats();
void NET_LSFT_CAN2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH01;
void NET_OP__BR__ETH01_ClearStats();
void NET_OP__BR__ETH01_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH02;
void NET_OP__BR__ETH02_ClearStats();
void NET_OP__BR__ETH02_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH03;
void NET_OP__BR__ETH03_ClearStats();
void NET_OP__BR__ETH03_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH04;
void NET_OP__BR__ETH04_ClearStats();
void NET_OP__BR__ETH04_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH05;
void NET_OP__BR__ETH05_ClearStats();
void NET_OP__BR__ETH05_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH06;
void NET_OP__BR__ETH06_ClearStats();
void NET_OP__BR__ETH06_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH07;
void NET_OP__BR__ETH07_ClearStats();
void NET_OP__BR__ETH07_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH08;
void NET_OP__BR__ETH08_ClearStats();
void NET_OP__BR__ETH08_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH09;
void NET_OP__BR__ETH09_ClearStats();
void NET_OP__BR__ETH09_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH10;
void NET_OP__BR__ETH10_ClearStats();
void NET_OP__BR__ETH10_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH11;
void NET_OP__BR__ETH11_ClearStats();
void NET_OP__BR__ETH11_GetStats(NetworkStats * p_NetworkStats);
extern int NET_OP__BR__ETH12;
void NET_OP__BR__ETH12_ClearStats();
void NET_OP__BR__ETH12_GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay;
void NET_FlexRay_ClearStats();
void NET_FlexRay_GetStats(NetworkStats * p_NetworkStats);
extern int NET_FlexRay2;
void NET_FlexRay2_ClearStats();
void NET_FlexRay2_GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN6__VNET_A_;
void NET_LIN6__VNET_A__ClearStats();
void NET_LIN6__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LIN6__VNET_B_;
void NET_LIN6__VNET_B__ClearStats();
void NET_LIN6__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN6__VNET_A_;
void NET_HS_CAN6__VNET_A__ClearStats();
void NET_HS_CAN6__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN6__VNET_B_;
void NET_HS_CAN6__VNET_B__ClearStats();
void NET_HS_CAN6__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN7__VNET_A_;
void NET_HS_CAN7__VNET_A__ClearStats();
void NET_HS_CAN7__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_HS_CAN7__VNET_B_;
void NET_HS_CAN7__VNET_B__ClearStats();
void NET_HS_CAN7__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN2__VNET_A_;
void NET_LSFT_CAN2__VNET_A__ClearStats();
void NET_LSFT_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_LSFT_CAN2__VNET_B_;
void NET_LSFT_CAN2__VNET_B__ClearStats();
void NET_LSFT_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats);
extern int NET_Ethernet__VNET_A_;
void NET_Ethernet__VNET_A__ClearStats();
void NET_Ethernet__VNET_A__GetStats(NetworkStats * p_NetworkStats);
extern int NET_Ethernet__VNET_B_;
void NET_Ethernet__VNET_B__ClearStats();
void NET_Ethernet__VNET_B__GetStats(NetworkStats * p_NetworkStats);

void SpyAppSig_CallAllHandlers();

// Application Signals
extern int AS_NMAC_DA_Index; // sig0
#define AS_NMAC_DA_Get() AS_Get(AS_NMAC_DA_Index)
#define AS_NMAC_DA_Set(dValue) AS_Set(AS_NMAC_DA_Index, dValue)

extern int AS_NMIPC_DA_Index; // sig1
#define AS_NMIPC_DA_Get() AS_Get(AS_NMIPC_DA_Index)
#define AS_NMIPC_DA_Set(dValue) AS_Set(AS_NMIPC_DA_Index, dValue)

extern int AS_NMTester_DA_Index; // sig2
#define AS_NMTester_DA_Get() AS_Get(AS_NMTester_DA_Index)
#define AS_NMTester_DA_Set(dValue) AS_Set(AS_NMTester_DA_Index, dValue)

extern int AS_NMAC_Sleep_Index; // sig3
#define AS_NMAC_Sleep_Get() AS_Get(AS_NMAC_Sleep_Index)
#define AS_NMAC_Sleep_Set(dValue) AS_Set(AS_NMAC_Sleep_Index, dValue)

extern int AS_NMIPC_Sleep_Index; // sig4
#define AS_NMIPC_Sleep_Get() AS_Get(AS_NMIPC_Sleep_Index)
#define AS_NMIPC_Sleep_Set(dValue) AS_Set(AS_NMIPC_Sleep_Index, dValue)

extern int AS_NMTester_Sleep_Index; // sig5
#define AS_NMTester_Sleep_Get() AS_Get(AS_NMTester_Sleep_Index)
#define AS_NMTester_Sleep_Set(dValue) AS_Set(AS_NMTester_Sleep_Index, dValue)

extern int FB_LimpHome_Ring_Index;
void FB_LimpHome_Ring_Start();
void FB_LimpHome_Ring_Stop();
void FB_LimpHome_Ring_Trigger();
void FB_LimpHome_Ring_Save();
double FB_LimpHome_Ring_IsRunning();
double FB_LimpHome_Ring_IsTriggered();
double FB_LimpHome_Ring_NumCollected();
extern int FB_LimpHome_LimpHome_Index;
void FB_LimpHome_LimpHome_Start();
void FB_LimpHome_LimpHome_Stop();
void FB_LimpHome_LimpHome_Trigger();
void FB_LimpHome_LimpHome_Save();
double FB_LimpHome_LimpHome_IsRunning();
double FB_LimpHome_LimpHome_IsTriggered();
double FB_LimpHome_LimpHome_NumCollected();
extern int FB_LimpHome_Alive_Index;
void FB_LimpHome_Alive_Start();
void FB_LimpHome_Alive_Stop();
void FB_LimpHome_Alive_Trigger();
void FB_LimpHome_Alive_Save();
double FB_LimpHome_Alive_IsRunning();
double FB_LimpHome_Alive_IsTriggered();
double FB_LimpHome_Alive_NumCollected();
extern int FB_LimpHome_ALive_Ring_Index;
void FB_LimpHome_ALive_Ring_Start();
void FB_LimpHome_ALive_Ring_Stop();
void FB_LimpHome_ALive_Ring_Trigger();
void FB_LimpHome_ALive_Ring_Save();
double FB_LimpHome_ALive_Ring_IsRunning();
double FB_LimpHome_ALive_Ring_IsTriggered();
double FB_LimpHome_ALive_Ring_NumCollected();

// Messages

typedef struct {
    unsigned char btPresent;  /// indicates message rxed at least once
    unsigned char  btPresentToggle; /// toggle every message rx
    unsigned char         btMultiFrameComplete; /// indicates frame is complete 
    double dUpdateRateRel;    /// periodic update rate
    double dUpdateRateAbs ;   /// absolute update rate
    int iPerSecond;   /// number of messages per second
    int iCount;       /// number of messages rxed
    int iChangeCount; /// count of everytime the message changes
    double dStartTime;        /// time between two first messages
    double dMsgMinTime;       /// min time between two messages
    double dMaxTime;          /// max time between two messages
    double dMeanTime;         /// average time between two messages
} MessageStats; 

typedef struct {
    int iNetwork; /// Network in Vehicle Spy
    int iID; /// Message ID
    __int64 iTimeStampNanoSecondsHW; /// TimeStamp By Hardware (3G Hardware Only)
    unsigned int iTimeStampMillisecondsOS; /// TimeStamp By OS (timeGetTime API)
    int iNumDataBytes; /// Number Of Data Bytes (CAN DLC)
    int iBitField;
    unsigned char btData[16]; /// Message data bytes
    unsigned char btInitialData[16]; /// Data bytes after initialization
} GenericMessage;

typedef struct {
    int iNetwork; /// Network in Vehicle Spy
    int iID; /// Message ID
    __int64 iTimeStampNanoSecondsHW; /// TimeStamp By Hardware (3G Hardware Only)
    unsigned int iTimeStampMillisecondsOS; /// TimeStamp By OS (timeGetTime API)
    int iNumDataBytes; /// Number Of Data Bytes (CAN DLC)
    int iBitField;
    unsigned char btData[4096]; /// Message data bytes
    unsigned char btInitialData[4096]; /// Data bytes after initialization
} GenericLongMessage;

void Spy_EveryMessage(GenericMessage * p_Msg);
void Spy_EveryLongMessage(GenericLongMessage * p_Msg);
int GenericMessageTransmit(GenericMessage * p_Msg);
int GenericLongMessageTransmit(GenericLongMessage * p_Msg);
int CANFDMessageTransmit(GenericLongMessage * p_Msg, BOOL bBRS);
extern int TX_NM_AC_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AC_NM_Sleep_ACK; /// Min: 0 Max: 1 Units: 
    BYTE AC_NM_Sleep_ACK_raw;
    double AC_NM_Sleep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE AC_NM_Sleep_Ind_raw;
    double AC_NM_Limphome; /// Min: 0 Max: 1 Units: 
    BYTE AC_NM_Limphome_raw;
    double AC_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE AC_NM_Ring_raw;
    double AC_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE AC_NM_Alive_raw;
    double AC_NM_DA; /// Min: 0 Max: 255 Units: 
    BYTE AC_NM_DA_raw;
} TX_NM_AC_HS_CAN;

#define TX_NM_AC_HS_CAN_SendType 0
#define TX_NM_AC_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define TX_NM_AC_HS_CAN_$_AC_NM_Sleep_ACK_$$_false 0
#define TX_NM_AC_HS_CAN_$_AC_NM_Sleep_ACK_$$_true 1
#define TX_NM_AC_HS_CAN_$_AC_NM_Sleep_Ind_$$_false 0
#define TX_NM_AC_HS_CAN_$_AC_NM_Sleep_Ind_$$_true 1
#define TX_NM_AC_HS_CAN_$_AC_NM_Limphome_$$_false 0
#define TX_NM_AC_HS_CAN_$_AC_NM_Limphome_$$_true 1
#define TX_NM_AC_HS_CAN_$_AC_NM_Ring_$$_false 0
#define TX_NM_AC_HS_CAN_$_AC_NM_Ring_$$_true 1
#define TX_NM_AC_HS_CAN_$_AC_NM_Alive_$$_false 0
#define TX_NM_AC_HS_CAN_$_AC_NM_Alive_$$_true 1
#pragma warning(default : 4005)

void TX_NM_AC_HS_CAN_Init(TX_NM_AC_HS_CAN * pMsg);
int TX_NM_AC_HS_CAN_Transmit(TX_NM_AC_HS_CAN * pMsg);
int TX_NM_AC_HS_CAN_Transmit_raw(TX_NM_AC_HS_CAN * pMsg);
int TX_NM_AC_HS_CAN_UpdateBytesFromSignals(TX_NM_AC_HS_CAN * pMsg);
int TX_NM_AC_HS_CAN_UpdateBytesFromRawSignals(TX_NM_AC_HS_CAN * pMsg);
#define TX_NM_AC_HS_CAN_AC_NM_Sleep_ACK_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, 0, dPhysicalValue);
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_Sleep_ACK_Physical(dval) SpySetTxSignal(TX_NM_AC_HS_CAN_Index, 0, dval)
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_Sleep_ACK_Raw(nval) SpySetTxSignalRaw(TX_NM_AC_HS_CAN_Index, 0, nval)
#define TX_NM_AC_HS_CAN_AC_NM_Sleep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, 1, dPhysicalValue);
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_Sleep_Ind_Physical(dval) SpySetTxSignal(TX_NM_AC_HS_CAN_Index, 1, dval)
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_Sleep_Ind_Raw(nval) SpySetTxSignalRaw(TX_NM_AC_HS_CAN_Index, 1, nval)
#define TX_NM_AC_HS_CAN_AC_NM_Limphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, 2, dPhysicalValue);
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_Limphome_Physical(dval) SpySetTxSignal(TX_NM_AC_HS_CAN_Index, 2, dval)
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_Limphome_Raw(nval) SpySetTxSignalRaw(TX_NM_AC_HS_CAN_Index, 2, nval)
#define TX_NM_AC_HS_CAN_AC_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, 3, dPhysicalValue);
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_Ring_Physical(dval) SpySetTxSignal(TX_NM_AC_HS_CAN_Index, 3, dval)
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_Ring_Raw(nval) SpySetTxSignalRaw(TX_NM_AC_HS_CAN_Index, 3, nval)
#define TX_NM_AC_HS_CAN_AC_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, 4, dPhysicalValue);
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_Alive_Physical(dval) SpySetTxSignal(TX_NM_AC_HS_CAN_Index, 4, dval)
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_Alive_Raw(nval) SpySetTxSignalRaw(TX_NM_AC_HS_CAN_Index, 4, nval)
#define TX_NM_AC_HS_CAN_AC_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, 5, dPhysicalValue);
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_DA_Physical(dval) SpySetTxSignal(TX_NM_AC_HS_CAN_Index, 5, dval)
#define TX_NM_AC_HS_CAN_SetSignal_AC_NM_DA_Raw(nval) SpySetTxSignalRaw(TX_NM_AC_HS_CAN_Index, 5, nval)
int TX_NM_AC_HS_CAN_TransmitFast();
#define TX_NM_AC_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_NM_AC_HS_CAN_Index, 0)
extern int TX_BCM1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double CheckAllLightsSignalState; /// Min: 0 Max: 3 Units: 
    BYTE CheckAllLightsSignalState_raw;
    double WheelAlexDifferLockOperateError; /// Min: 0 Max: 3 Units: 
    BYTE WheelAlexDifferLockOperateError_raw;
    double TrailerState_TrailerState; /// Min: 0 Max: 3 Units: 
    BYTE TrailerState_TrailerState_raw;
    double WiperWashSt; /// Min: 0 Max: 3 Units: 
    BYTE WiperWashSt_raw;
    double R_ReLSts; /// Min: 0 Max: 3 Units: 
    BYTE R_ReLSts_raw;
    double L_ReLSts; /// Min: 0 Max: 3 Units: 
    BYTE L_ReLSts_raw;
    double AtLgtSts; /// Min: 0 Max: 3 Units: 
    BYTE AtLgtSts_raw;
    double TopLgtSts; /// Min: 0 Max: 3 Units: 
    BYTE TopLgtSts_raw;
    double PosLgtOnWarr; /// Min: 0 Max: 3 Units: 
    BYTE PosLgtOnWarr_raw;
    double WiperModeSt; /// Min: 0 Max: 3 Units: 
    BYTE WiperModeSt_raw;
    double FuelStolenAlmSig; /// Min: 0 Max: 3 Units: 
    BYTE FuelStolenAlmSig_raw;
    double WheelDifferLockIndicatorLgt; /// Min: 0 Max: 3 Units: 
    BYTE WheelDifferLockIndicatorLgt_raw;
    double AxleDifferentialLockIndicatorLgt; /// Min: 0 Max: 3 Units: 
    BYTE AxleDifferentialLockIndicatorLgt_raw;
    double DayLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE DayLgtSt_raw;
    double HeadLgtWashStInd; /// Min: 0 Max: 3 Units: 
    BYTE HeadLgtWashStInd_raw;
    double FuelMassSignal; /// Min: 0 Max: 102 Units: %
    BYTE FuelMassSignal_raw;
    double BackCabWorkingLightState; /// Min: 0 Max: 3 Units: 
    BYTE BackCabWorkingLightState_raw;
    double RevLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE RevLgtSt_raw;
    double PosLgtStInd; /// Min: 0 Max: 3 Units: 
    BYTE PosLgtStInd_raw;
    double RFogLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE RFogLgtSt_raw;
    double FrontFogLightSts; /// Min: 0 Max: 3 Units: 
    BYTE FrontFogLightSts_raw;
    double BrkLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE BrkLgtSt_raw;
    double R_TurnLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE R_TurnLgtSt_raw;
    double L_TurnLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE L_TurnLgtSt_raw;
    double LBeamSt; /// Min: 0 Max: 3 Units: 
    BYTE LBeamSt_raw;
    double HBeamSt; /// Min: 0 Max: 3 Units: 
    BYTE HBeamSt_raw;
} TX_BCM1_HS_CAN;

#define TX_BCM1_HS_CAN_SendType 0
#define TX_BCM1_HS_CAN_SendRate 200

void TX_BCM1_HS_CAN_Init(TX_BCM1_HS_CAN * pMsg);
int TX_BCM1_HS_CAN_Transmit(TX_BCM1_HS_CAN * pMsg);
int TX_BCM1_HS_CAN_Transmit_raw(TX_BCM1_HS_CAN * pMsg);
int TX_BCM1_HS_CAN_UpdateBytesFromSignals(TX_BCM1_HS_CAN * pMsg);
int TX_BCM1_HS_CAN_UpdateBytesFromRawSignals(TX_BCM1_HS_CAN * pMsg);
#define TX_BCM1_HS_CAN_CheckAllLightsSignalState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 0, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_CheckAllLightsSignalState_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 0, dval)
#define TX_BCM1_HS_CAN_SetSignal_CheckAllLightsSignalState_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 0, nval)
#define TX_BCM1_HS_CAN_WheelAlexDifferLockOperateError_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 1, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_WheelAlexDifferLockOperateError_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 1, dval)
#define TX_BCM1_HS_CAN_SetSignal_WheelAlexDifferLockOperateError_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 1, nval)
#define TX_BCM1_HS_CAN_TrailerState_TrailerState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 2, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_TrailerState_TrailerState_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 2, dval)
#define TX_BCM1_HS_CAN_SetSignal_TrailerState_TrailerState_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 2, nval)
#define TX_BCM1_HS_CAN_WiperWashSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 3, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_WiperWashSt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 3, dval)
#define TX_BCM1_HS_CAN_SetSignal_WiperWashSt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 3, nval)
#define TX_BCM1_HS_CAN_R_ReLSts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 4, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_R_ReLSts_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 4, dval)
#define TX_BCM1_HS_CAN_SetSignal_R_ReLSts_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 4, nval)
#define TX_BCM1_HS_CAN_L_ReLSts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 5, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_L_ReLSts_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 5, dval)
#define TX_BCM1_HS_CAN_SetSignal_L_ReLSts_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 5, nval)
#define TX_BCM1_HS_CAN_AtLgtSts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 6, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_AtLgtSts_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 6, dval)
#define TX_BCM1_HS_CAN_SetSignal_AtLgtSts_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 6, nval)
#define TX_BCM1_HS_CAN_TopLgtSts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 7, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_TopLgtSts_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 7, dval)
#define TX_BCM1_HS_CAN_SetSignal_TopLgtSts_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 7, nval)
#define TX_BCM1_HS_CAN_PosLgtOnWarr_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 8, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_PosLgtOnWarr_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 8, dval)
#define TX_BCM1_HS_CAN_SetSignal_PosLgtOnWarr_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 8, nval)
#define TX_BCM1_HS_CAN_WiperModeSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 9, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_WiperModeSt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 9, dval)
#define TX_BCM1_HS_CAN_SetSignal_WiperModeSt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 9, nval)
#define TX_BCM1_HS_CAN_FuelStolenAlmSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 10, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_FuelStolenAlmSig_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 10, dval)
#define TX_BCM1_HS_CAN_SetSignal_FuelStolenAlmSig_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 10, nval)
#define TX_BCM1_HS_CAN_WheelDifferLockIndicatorLgt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 11, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_WheelDifferLockIndicatorLgt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 11, dval)
#define TX_BCM1_HS_CAN_SetSignal_WheelDifferLockIndicatorLgt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 11, nval)
#define TX_BCM1_HS_CAN_AxleDifferentialLockIndicatorLgt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 12, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_AxleDifferentialLockIndicatorLgt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 12, dval)
#define TX_BCM1_HS_CAN_SetSignal_AxleDifferentialLockIndicatorLgt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 12, nval)
#define TX_BCM1_HS_CAN_DayLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 13, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_DayLgtSt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 13, dval)
#define TX_BCM1_HS_CAN_SetSignal_DayLgtSt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 13, nval)
#define TX_BCM1_HS_CAN_HeadLgtWashStInd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 14, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_HeadLgtWashStInd_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 14, dval)
#define TX_BCM1_HS_CAN_SetSignal_HeadLgtWashStInd_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 14, nval)
#define TX_BCM1_HS_CAN_FuelMassSignal_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 15, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_FuelMassSignal_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 15, dval)
#define TX_BCM1_HS_CAN_SetSignal_FuelMassSignal_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 15, nval)
#define TX_BCM1_HS_CAN_BackCabWorkingLightState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 16, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_BackCabWorkingLightState_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 16, dval)
#define TX_BCM1_HS_CAN_SetSignal_BackCabWorkingLightState_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 16, nval)
#define TX_BCM1_HS_CAN_RevLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 17, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_RevLgtSt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 17, dval)
#define TX_BCM1_HS_CAN_SetSignal_RevLgtSt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 17, nval)
#define TX_BCM1_HS_CAN_PosLgtStInd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 18, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_PosLgtStInd_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 18, dval)
#define TX_BCM1_HS_CAN_SetSignal_PosLgtStInd_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 18, nval)
#define TX_BCM1_HS_CAN_RFogLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 19, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_RFogLgtSt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 19, dval)
#define TX_BCM1_HS_CAN_SetSignal_RFogLgtSt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 19, nval)
#define TX_BCM1_HS_CAN_FrontFogLightSts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 20, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_FrontFogLightSts_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 20, dval)
#define TX_BCM1_HS_CAN_SetSignal_FrontFogLightSts_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 20, nval)
#define TX_BCM1_HS_CAN_BrkLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 21, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_BrkLgtSt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 21, dval)
#define TX_BCM1_HS_CAN_SetSignal_BrkLgtSt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 21, nval)
#define TX_BCM1_HS_CAN_R_TurnLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 22, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_R_TurnLgtSt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 22, dval)
#define TX_BCM1_HS_CAN_SetSignal_R_TurnLgtSt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 22, nval)
#define TX_BCM1_HS_CAN_L_TurnLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 23, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_L_TurnLgtSt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 23, dval)
#define TX_BCM1_HS_CAN_SetSignal_L_TurnLgtSt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 23, nval)
#define TX_BCM1_HS_CAN_LBeamSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 24, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_LBeamSt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 24, dval)
#define TX_BCM1_HS_CAN_SetSignal_LBeamSt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 24, nval)
#define TX_BCM1_HS_CAN_HBeamSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, 25, dPhysicalValue);
#define TX_BCM1_HS_CAN_SetSignal_HBeamSt_Physical(dval) SpySetTxSignal(TX_BCM1_HS_CAN_Index, 25, dval)
#define TX_BCM1_HS_CAN_SetSignal_HBeamSt_Raw(nval) SpySetTxSignalRaw(TX_BCM1_HS_CAN_Index, 25, nval)
int TX_BCM1_HS_CAN_TransmitFast();
#define TX_BCM1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, TX_BCM1_HS_CAN_Index, 0)
extern int MG_NM_TXJ_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TXJ_NM_Sleep_Ack; /// Min: 0 Max: 1 Units: 
    BYTE TXJ_NM_Sleep_Ack_raw;
    double TXJ_NM_Sleep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE TXJ_NM_Sleep_Ind_raw;
    double TXJ_NM_Limphome; /// Min: 0 Max: 1 Units: 
    BYTE TXJ_NM_Limphome_raw;
    double TXJ_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE TXJ_NM_Ring_raw;
    double TXJ_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE TXJ_NM_Alive_raw;
    double TXJ_NM_DA; /// Min: 0 Max: 255 Units: 
    BYTE TXJ_NM_DA_raw;
} MG_NM_TXJ_HS_CAN;

#pragma warning(disable : 4005)
#define MG_NM_TXJ_HS_CAN_$_TXJ_NM_Sleep_Ack_$$_FALSE 0
#define MG_NM_TXJ_HS_CAN_$_TXJ_NM_Sleep_Ack_$$_TRUE_ 1
#define MG_NM_TXJ_HS_CAN_$_TXJ_NM_Sleep_Ind_$$_FALSE 0
#define MG_NM_TXJ_HS_CAN_$_TXJ_NM_Sleep_Ind_$$_TRUE_ 1
#define MG_NM_TXJ_HS_CAN_$_TXJ_NM_Limphome_$$_FALSE 0
#define MG_NM_TXJ_HS_CAN_$_TXJ_NM_Limphome_$$_TRUE_ 1
#define MG_NM_TXJ_HS_CAN_$_TXJ_NM_Ring_$$_FALSE 0
#define MG_NM_TXJ_HS_CAN_$_TXJ_NM_Ring_$$_TRUE_ 1
#define MG_NM_TXJ_HS_CAN_$_TXJ_NM_Alive_$$_FALSE 0
#define MG_NM_TXJ_HS_CAN_$_TXJ_NM_Alive_$$_TRUE_ 1
#pragma warning(default : 4005)

void MG_NM_TXJ_HS_CAN_Init(MG_NM_TXJ_HS_CAN * pMsg);
int MG_NM_TXJ_HS_CAN_Transmit(MG_NM_TXJ_HS_CAN * pMsg);
int MG_NM_TXJ_HS_CAN_Transmit_raw(MG_NM_TXJ_HS_CAN * pMsg);
int MG_NM_TXJ_HS_CAN_UpdateBytesFromSignals(MG_NM_TXJ_HS_CAN * pMsg);
int MG_NM_TXJ_HS_CAN_UpdateBytesFromRawSignals(MG_NM_TXJ_HS_CAN * pMsg);
#define MG_NM_TXJ_HS_CAN_TXJ_NM_Sleep_Ack_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, 0, dPhysicalValue);
#define MG_NM_TXJ_HS_CAN_TXJ_NM_Sleep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, 1, dPhysicalValue);
#define MG_NM_TXJ_HS_CAN_TXJ_NM_Limphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, 2, dPhysicalValue);
#define MG_NM_TXJ_HS_CAN_TXJ_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, 3, dPhysicalValue);
#define MG_NM_TXJ_HS_CAN_TXJ_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, 4, dPhysicalValue);
#define MG_NM_TXJ_HS_CAN_TXJ_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, 5, dPhysicalValue);
#define MG_NM_TXJ_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_NM_TXJ_HS_CAN_Index, 0)
extern int MG_NM_MMI_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AC_NMDataField; /// Min: 0 Max: 281474976710655 Units: 
    uint64 AC_NMDataField_raw;
    double AC_NMSleepAck; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMSleepAck_raw;
    double AC_NMSleepInd; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMSleepInd_raw;
    double AC_NMLimphome; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMLimphome_raw;
    double AC_NMRing; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMRing_raw;
    double AC_NMAlive; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMAlive_raw;
    double AC_NMDestAddress; /// Min: 0 Max: 255 Units: 
    BYTE AC_NMDestAddress_raw;
} MG_NM_MMI_HS_CAN;

#define MG_NM_MMI_HS_CAN_SendType 0
#define MG_NM_MMI_HS_CAN_SendRate 0
#pragma warning(disable : 4005)
#define MG_NM_MMI_HS_CAN_$_AC_NMSleepAck_$$_FALSE 0
#define MG_NM_MMI_HS_CAN_$_AC_NMSleepAck_$$_TRUE 1
#define MG_NM_MMI_HS_CAN_$_AC_NMSleepInd_$$_FALSE 0
#define MG_NM_MMI_HS_CAN_$_AC_NMSleepInd_$$_TRUE 1
#define MG_NM_MMI_HS_CAN_$_AC_NMLimphome_$$_FALSE 0
#define MG_NM_MMI_HS_CAN_$_AC_NMLimphome_$$_TRUE 1
#define MG_NM_MMI_HS_CAN_$_AC_NMRing_$$_FALSE 0
#define MG_NM_MMI_HS_CAN_$_AC_NMRing_$$_TRUE 1
#define MG_NM_MMI_HS_CAN_$_AC_NMAlive_$$_FALSE 0
#define MG_NM_MMI_HS_CAN_$_AC_NMAlive_$$_TRUE 1
#define MG_NM_MMI_HS_CAN_$_AC_NMDestAddress_$$_IPC 23
#define MG_NM_MMI_HS_CAN_$_AC_NMDestAddress_$$_BCM 33
#define MG_NM_MMI_HS_CAN_$_AC_NMDestAddress_$$_GW 37
#pragma warning(default : 4005)

void MG_NM_MMI_HS_CAN_Init(MG_NM_MMI_HS_CAN * pMsg);
int MG_NM_MMI_HS_CAN_Transmit(MG_NM_MMI_HS_CAN * pMsg);
int MG_NM_MMI_HS_CAN_Transmit_raw(MG_NM_MMI_HS_CAN * pMsg);
int MG_NM_MMI_HS_CAN_UpdateBytesFromSignals(MG_NM_MMI_HS_CAN * pMsg);
int MG_NM_MMI_HS_CAN_UpdateBytesFromRawSignals(MG_NM_MMI_HS_CAN * pMsg);
#define MG_NM_MMI_HS_CAN_AC_NMDataField_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, 0, dPhysicalValue);
#define MG_NM_MMI_HS_CAN_AC_NMSleepAck_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, 1, dPhysicalValue);
#define MG_NM_MMI_HS_CAN_AC_NMSleepInd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, 2, dPhysicalValue);
#define MG_NM_MMI_HS_CAN_AC_NMLimphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, 3, dPhysicalValue);
#define MG_NM_MMI_HS_CAN_AC_NMRing_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, 4, dPhysicalValue);
#define MG_NM_MMI_HS_CAN_AC_NMAlive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, 5, dPhysicalValue);
#define MG_NM_MMI_HS_CAN_AC_NMDestAddress_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, 6, dPhysicalValue);
#define MG_NM_MMI_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, MG_NM_MMI_HS_CAN_Index, 0)
extern int DB_Report_Message_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double MISC3_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC3_AIN_raw;
    double MISC4_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC4_AIN_raw;
    double MISC5_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC5_AIN_raw;
    double MISC6_AIN; /// Min: 0 Max: 1023 Units: 
    WORD MISC6_AIN_raw;
    double MISC1; /// Min: 0 Max: 1 Units: 
    BYTE MISC1_raw;
    double MISC2; /// Min: 0 Max: 1 Units: 
    BYTE MISC2_raw;
    double MISC3; /// Min: 0 Max: 1 Units: 
    BYTE MISC3_raw;
    double MISC4; /// Min: 0 Max: 1 Units: 
    BYTE MISC4_raw;
    double MISC5; /// Min: 0 Max: 1 Units: 
    BYTE MISC5_raw;
    double MISC6; /// Min: 0 Max: 1 Units: 
    BYTE MISC6_raw;
    double LED1; /// Min: 0 Max: 1 Units: 
    BYTE LED1_raw;
    double LED2; /// Min: 0 Max: 1 Units: 
    BYTE LED2_raw;
    double LIN1; /// Min: 0 Max: 1 Units: 
    BYTE LIN1_raw;
    double LIN2; /// Min: 0 Max: 1 Units: 
    BYTE LIN2_raw;
} DB_Report_Message_neoVI;


void DB_Report_Message_neoVI_Init(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_Transmit(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_Transmit_raw(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_UpdateBytesFromSignals(DB_Report_Message_neoVI * pMsg);
int DB_Report_Message_neoVI_UpdateBytesFromRawSignals(DB_Report_Message_neoVI * pMsg);
#define DB_Report_Message_neoVI_MISC3_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC4_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC5_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC6_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC5_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 8, dPhysicalValue);
#define DB_Report_Message_neoVI_MISC6_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 9, dPhysicalValue);
#define DB_Report_Message_neoVI_LED1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 10, dPhysicalValue);
#define DB_Report_Message_neoVI_LED2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 11, dPhysicalValue);
#define DB_Report_Message_neoVI_LIN1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 12, dPhysicalValue);
#define DB_Report_Message_neoVI_LIN2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_neoVI_Index, 13, dPhysicalValue);
#define DB_Report_Message_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_neoVI_Index, 0)
extern int DB_Report_Message__PWM__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double PWM_In_1; /// Min: 0 Max: 4294967295 Units: 
    DWORD PWM_In_1_raw;
} DB_Report_Message__PWM__neoVI;


void DB_Report_Message__PWM__neoVI_Init(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_Transmit(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_Transmit_raw(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_UpdateBytesFromSignals(DB_Report_Message__PWM__neoVI * pMsg);
int DB_Report_Message__PWM__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__PWM__neoVI * pMsg);
#define DB_Report_Message__PWM__neoVI_PWM_In_1_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__PWM__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__PWM__neoVI_Index, 0)
extern int DB_Report_Message__VCAN_RF__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double MISC1_AIN; /// Min: 0 Max: 41.55477149999999 Units: V
    WORD MISC1_AIN_raw;
    double MISC_1; /// Min: 0 Max: 1 Units: 
    BYTE MISC_1_raw;
    double MISC_2; /// Min: 0 Max: 1 Units: 
    BYTE MISC_2_raw;
    double MISC_3; /// Min: 0 Max: 1 Units: 
    BYTE MISC_3_raw;
    double MISC_4; /// Min: 0 Max: 1 Units: 
    BYTE MISC_4_raw;
    double Vehicle_Battery_Voltage; /// Min: 0 Max: 43.18778320312499 Units: V
    WORD Vehicle_Battery_Voltage_raw;
    double Temperature; /// Min: -215 Max: 114.677734375 Units: C
    WORD Temperature_raw;
    double Hardware_Revision; /// Min: 3 Max: 10.9921875 Units: 
    WORD Hardware_Revision_raw;
    double RTC_Battery_Measure_Enabled; /// Min: 0 Max: 1 Units: 
    BYTE RTC_Battery_Measure_Enabled_raw;
    double RTC_Battery_Voltage; /// Min: 0 Max: 3.29677734375 Units: V
    WORD RTC_Battery_Voltage_raw;
} DB_Report_Message__VCAN_RF__neoVI;


void DB_Report_Message__VCAN_RF__neoVI_Init(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_Transmit(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_Transmit_raw(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg);
int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg);
#define DB_Report_Message__VCAN_RF__neoVI_MISC1_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_MISC_4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_Vehicle_Battery_Voltage_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_Temperature_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_Hardware_Revision_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_RTC_Battery_Measure_Enabled_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 8, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_RTC_Battery_Voltage_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, 9, dPhysicalValue);
#define DB_Report_Message__VCAN_RF__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__VCAN_RF__neoVI_Index, 0)
extern int DB_Report_Message__neoVI_Fire2__neoVI_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double RTC_Battery; /// Min: 0 Max: 0 Units: V
    uint64 RTC_Battery_raw;
    double Temperature; /// Min: 0 Max: 0 Units: C
    uint64 Temperature_raw;
    double Vehicle_Battery; /// Min: 0 Max: 0 Units: V
    uint64 Vehicle_Battery_raw;
    double EMISC1_AIN; /// Min: 0 Max: 665.51513385 Units: V
    WORD EMISC1_AIN_raw;
    double EMISC2_AIN; /// Min: 0 Max: 665.51513385 Units: V
    WORD EMISC2_AIN_raw;
    double EMISC1_DIN; /// Min: 0 Max: 1 Units: 
    BYTE EMISC1_DIN_raw;
    double EMISC2_DIN; /// Min: 0 Max: 1 Units: 
    BYTE EMISC2_DIN_raw;
    double MISC5_DIN; /// Min: 0 Max: 1 Units: 
    BYTE MISC5_DIN_raw;
    double MISC6_DIN; /// Min: 0 Max: 1 Units: 
    BYTE MISC6_DIN_raw;
    double LED1; /// Min: 0 Max: 1 Units: 
    BYTE LED1_raw;
    double LED2; /// Min: 0 Max: 1 Units: 
    BYTE LED2_raw;
} DB_Report_Message__neoVI_Fire2__neoVI;


void DB_Report_Message__neoVI_Fire2__neoVI_Init(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_Transmit(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_Transmit_raw(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg);
#define DB_Report_Message__neoVI_Fire2__neoVI_RTC_Battery_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_Temperature_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_Vehicle_Battery_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_EMISC1_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_EMISC2_AIN_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_EMISC1_DIN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_EMISC2_DIN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_MISC5_DIN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_MISC6_DIN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 8, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_LED1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 9, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_LED2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, 10, dPhysicalValue);
#define DB_Report_Message__neoVI_Fire2__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__neoVI_Fire2__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Latitude__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Latitude; /// Min: 0 Max: 0 Units: degrees
    uint64 Latitude_raw;
} DB_Report_Message__GPS_Latitude__neoVI;


void DB_Report_Message__GPS_Latitude__neoVI_Init(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_Transmit(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg);
#define DB_Report_Message__GPS_Latitude__neoVI_Latitude_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Latitude__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Latitude__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Longitude__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Longitude; /// Min: 0 Max: 0 Units: degrees
    uint64 Longitude_raw;
} DB_Report_Message__GPS_Longitude__neoVI;


void DB_Report_Message__GPS_Longitude__neoVI_Init(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_Transmit(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg);
#define DB_Report_Message__GPS_Longitude__neoVI_Longitude_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Longitude__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Longitude__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Flags__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Update_Count; /// Min: 0 Max: 255 Units: 
    BYTE Update_Count_raw;
    double GPS_Date_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Date_Available_raw;
    double GPS_Time_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Time_Available_raw;
    double GPS_Accuracy_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Accuracy_Available_raw;
    double GPS_Bearing_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Bearing_Available_raw;
    double GPS_Speed_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Speed_Available_raw;
    double GPS_Altitude_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Altitude_Available_raw;
    double GPS_Lat_Lon_Available; /// Min: 0 Max: 1 Units: 
    BYTE GPS_Lat_Lon_Available_raw;
} DB_Report_Message__GPS_Flags__neoVI;


void DB_Report_Message__GPS_Flags__neoVI_Init(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_Transmit(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_Transmit_raw(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg);
int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg);
#define DB_Report_Message__GPS_Flags__neoVI_Update_Count_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Date_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Time_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Accuracy_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Bearing_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Speed_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Altitude_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_GPS_Lat_Lon_Available_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message__GPS_Flags__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Flags__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Altitude__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Altitude_Ellipse; /// Min: 0 Max: 0 Units: meters
    uint64 Altitude_Ellipse_raw;
} DB_Report_Message__GPS_Altitude__neoVI;


void DB_Report_Message__GPS_Altitude__neoVI_Init(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_Transmit(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg);
#define DB_Report_Message__GPS_Altitude__neoVI_Altitude_Ellipse_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Altitude__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Altitude__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Speed_Bearing__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Speed; /// Min: 0 Max: 0 Units: m/s
    DWORD Speed_raw;
    double Bearing; /// Min: 0 Max: 0 Units: degrees
    DWORD Bearing_raw;
} DB_Report_Message__GPS_Speed_Bearing__neoVI;


void DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit_raw(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg);
#define DB_Report_Message__GPS_Speed_Bearing__neoVI_Speed_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Speed_Bearing__neoVI_Bearing_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__GPS_Speed_Bearing__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Accuracy__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Accuracy; /// Min: 0 Max: 0 Units: meters
    DWORD Accuracy_raw;
} DB_Report_Message__GPS_Accuracy__neoVI;


void DB_Report_Message__GPS_Accuracy__neoVI_Init(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_Transmit(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_Transmit_raw(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg);
#define DB_Report_Message__GPS_Accuracy__neoVI_Accuracy_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Accuracy__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Accuracy__neoVI_Index, 0)
extern int DB_Report_Message__GPS_Time__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Timestamp; /// Min: 0 Max: 18446744073709551615 Units: ms since 1/1/1970
    uint64 Timestamp_raw;
} DB_Report_Message__GPS_Time__neoVI;


void DB_Report_Message__GPS_Time__neoVI_Init(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_Transmit(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_Transmit_raw(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Time__neoVI * pMsg);
int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Time__neoVI * pMsg);
#define DB_Report_Message__GPS_Time__neoVI_Timestamp_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__GPS_Time__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__GPS_Time__neoVI_Index, 0)
extern int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double WiviStartSector; /// Min: -2147483648 Max: 2147483647 Units: 
    DWORD WiviStartSector_raw;
    double WiviEndSector; /// Min: -2147483648 Max: 2147483647 Units: 
    DWORD WiviEndSector_raw;
} DB_Report_Message__WirelessneoVI_Sectors__neoVI;


void DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg);
#define DB_Report_Message__WirelessneoVI_Sectors__neoVI_WiviStartSector_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Sectors__neoVI_WiviEndSector_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Sectors__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, 0)
extern int DB_Report_Message__WirelessneoVI_Signals__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double WiviJob; /// Min: -128 Max: 127 Units: 
    BYTE WiviJob_raw;
    double WiviApkResponse; /// Min: -128 Max: 127 Units: 
    BYTE WiviApkResponse_raw;
    double WiviDataTransferMediumChoice; /// Min: -128 Max: 127 Units: 
    BYTE WiviDataTransferMediumChoice_raw;
    double WiviApkResponseTo; /// Min: -128 Max: 127 Units: 
    BYTE WiviApkResponseTo_raw;
    double WiviReserved0; /// Min: -128 Max: 127 Units: 
    BYTE WiviReserved0_raw;
    double WiviReserved1; /// Min: -128 Max: 127 Units: 
    BYTE WiviReserved1_raw;
} DB_Report_Message__WirelessneoVI_Signals__neoVI;


void DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviJob_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviApkResponse_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviDataTransferMediumChoice_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviApkResponseTo_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviReserved0_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_WiviReserved1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__WirelessneoVI_Signals__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, 0)
extern int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI;


void DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Init(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg);
int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg);
int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit_raw(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg);
#define DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, 0)
extern int DB_neoVI_Logger_Message_Data_Lost_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Logger_Message_Data_Lost_neoVI;


void DB_neoVI_Logger_Message_Data_Lost_neoVI_Init(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg);
int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg);
int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit_raw(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg);
#define DB_neoVI_Logger_Message_Data_Lost_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, 0)
extern int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI;


void DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Init(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg);
int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg);
int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit_raw(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg);
#define DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, 0)
extern int DB_neoVI_Logger_woke_up_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double SleepFlags; /// Min: 0 Max: 65535 Units: 
    WORD SleepFlags_raw;
    double WakeupFlags; /// Min: 0 Max: 65535 Units: 
    WORD WakeupFlags_raw;
    double WakeUpSms; /// Min: 0 Max: 1 Units: 
    BYTE WakeUpSms_raw;
    double WakeupSlaveA; /// Min: 0 Max: 1 Units: 
    BYTE WakeupSlaveA_raw;
    double WakeupSlaveB; /// Min: 0 Max: 1 Units: 
    BYTE WakeupSlaveB_raw;
    double WakeupMainVnet; /// Min: 0 Max: 1 Units: 
    BYTE WakeupMainVnet_raw;
    double WakeupUsb; /// Min: 0 Max: 1 Units: 
    BYTE WakeupUsb_raw;
    double PowerBoot; /// Min: 0 Max: 1 Units: 
    BYTE PowerBoot_raw;
    double LowVbatSleep; /// Min: 0 Max: 1 Units: 
    BYTE LowVbatSleep_raw;
    double NoCmSleep; /// Min: 0 Max: 1 Units: 
    BYTE NoCmSleep_raw;
} DB_neoVI_Logger_woke_up_neoVI;


void DB_neoVI_Logger_woke_up_neoVI_Init(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_Transmit(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_Transmit_raw(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg);
int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg);
#define DB_neoVI_Logger_woke_up_neoVI_SleepFlags_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupFlags_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeUpSms_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 2, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupSlaveA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 3, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupSlaveB_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 4, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupMainVnet_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 5, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_WakeupUsb_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 6, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_PowerBoot_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 7, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_LowVbatSleep_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 8, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_NoCmSleep_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, 9, dPhysicalValue);
#define DB_neoVI_Logger_woke_up_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Logger_woke_up_neoVI_Index, 0)
extern int DB_Report_Message_1_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Channel_A; /// Min: -9980.46875 Max: 10000 Units: mV
    WORD Channel_A_raw;
    double Channel_B; /// Min: -9980.46875 Max: 10000 Units: mV
    WORD Channel_B_raw;
    double Channel_1_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_1_Differential__raw;
    double Channel_2_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_2_Differential__raw;
} DB_Report_Message_1_Analog_Card__neoVI;


void DB_Report_Message_1_Analog_Card__neoVI_Init(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_Transmit(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_A_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_B_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_1_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_Channel_2_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message_1_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_1_Analog_Card__neoVI_Index, 0)
extern int DB_Report_Message_2_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Channel_3_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_3_Differential__raw;
    double Channel_4_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_4_Differential__raw;
    double Channel_5_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_5_Differential__raw;
    double Channel_6_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_6_Differential__raw;
} DB_Report_Message_2_Analog_Card__neoVI;


void DB_Report_Message_2_Analog_Card__neoVI_Init(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_Transmit(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_3_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_4_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_5_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_Channel_6_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message_2_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_2_Analog_Card__neoVI_Index, 0)
extern int DB_Report_Message_3_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Channel_7_Differential_; /// Min: -42978.83555 Max: 42980.14719999999 Units: mV
    WORD Channel_7_Differential__raw;
} DB_Report_Message_3_Analog_Card__neoVI;


void DB_Report_Message_3_Analog_Card__neoVI_Init(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_Transmit(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_3_Analog_Card__neoVI_Channel_7_Differential__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_3_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_3_Analog_Card__neoVI_Index, 0)
extern int DB_Report_Message_4_Analog_Card__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Timestamp; /// Min: 0 Max: 18446744073709551615 Units: 
    uint64 Timestamp_raw;
} DB_Report_Message_4_Analog_Card__neoVI;


void DB_Report_Message_4_Analog_Card__neoVI_Init(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_Transmit(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg);
#define DB_Report_Message_4_Analog_Card__neoVI_Timestamp_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message_4_Analog_Card__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message_4_Analog_Card__neoVI_Index, 0)
extern int DB_Time_Resync_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Timestamp; /// Min: -0 Max: 0 Units: ms
    uint64 Timestamp_raw;
} DB_Time_Resync_neoVI;


void DB_Time_Resync_neoVI_Init(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_Transmit(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_Transmit_raw(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_UpdateBytesFromSignals(DB_Time_Resync_neoVI * pMsg);
int DB_Time_Resync_neoVI_UpdateBytesFromRawSignals(DB_Time_Resync_neoVI * pMsg);
#define DB_Time_Resync_neoVI_Timestamp_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, 0, dPhysicalValue);
#define DB_Time_Resync_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Time_Resync_neoVI_Index, 0)
extern int DB_VNET_Clock_Edge_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_VNET_Clock_Edge_neoVI;


void DB_VNET_Clock_Edge_neoVI_Init(DB_VNET_Clock_Edge_neoVI * pMsg);
int DB_VNET_Clock_Edge_neoVI_Transmit(DB_VNET_Clock_Edge_neoVI * pMsg);
int DB_VNET_Clock_Edge_neoVI_Transmit_raw(DB_VNET_Clock_Edge_neoVI * pMsg);
#define DB_VNET_Clock_Edge_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VNET_Clock_Edge_neoVI_Index, 0)
extern int DB_VNET_A_Stats_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double msgTotal; /// Min: 0 Max: 65535 Units: 
    WORD msgTotal_raw;
    double rxSize; /// Min: 0 Max: 255 Units: 
    BYTE rxSize_raw;
    double scCnt; /// Min: 0 Max: 255 Units: 
    BYTE scCnt_raw;
    double yields; /// Min: 0 Max: 65535 Units: 
    WORD yields_raw;
    double bytesRead; /// Min: 0 Max: 65535 Units: 
    WORD bytesRead_raw;
} DB_VNET_A_Stats_neoVI;


void DB_VNET_A_Stats_neoVI_Init(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_Transmit(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_Transmit_raw(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_UpdateBytesFromSignals(DB_VNET_A_Stats_neoVI * pMsg);
int DB_VNET_A_Stats_neoVI_UpdateBytesFromRawSignals(DB_VNET_A_Stats_neoVI * pMsg);
#define DB_VNET_A_Stats_neoVI_msgTotal_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 0, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_rxSize_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 1, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_scCnt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 2, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_yields_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 3, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_bytesRead_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, 4, dPhysicalValue);
#define DB_VNET_A_Stats_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VNET_A_Stats_neoVI_Index, 0)
extern int DB_VNET_A_Reboot_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_VNET_A_Reboot_neoVI;


void DB_VNET_A_Reboot_neoVI_Init(DB_VNET_A_Reboot_neoVI * pMsg);
int DB_VNET_A_Reboot_neoVI_Transmit(DB_VNET_A_Reboot_neoVI * pMsg);
int DB_VNET_A_Reboot_neoVI_Transmit_raw(DB_VNET_A_Reboot_neoVI * pMsg);
#define DB_VNET_A_Reboot_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VNET_A_Reboot_neoVI_Index, 0)
extern int DB_neoVI_Went_To_Sleep_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_neoVI_Went_To_Sleep_neoVI;


void DB_neoVI_Went_To_Sleep_neoVI_Init(DB_neoVI_Went_To_Sleep_neoVI * pMsg);
int DB_neoVI_Went_To_Sleep_neoVI_Transmit(DB_neoVI_Went_To_Sleep_neoVI * pMsg);
int DB_neoVI_Went_To_Sleep_neoVI_Transmit_raw(DB_neoVI_Went_To_Sleep_neoVI * pMsg);
#define DB_neoVI_Went_To_Sleep_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Went_To_Sleep_neoVI_Index, 0)
extern int DB_Device_subsystem_restarted__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
} DB_Device_subsystem_restarted__neoVI;


void DB_Device_subsystem_restarted__neoVI_Init(DB_Device_subsystem_restarted__neoVI * pMsg);
int DB_Device_subsystem_restarted__neoVI_Transmit(DB_Device_subsystem_restarted__neoVI * pMsg);
int DB_Device_subsystem_restarted__neoVI_Transmit_raw(DB_Device_subsystem_restarted__neoVI * pMsg);
#define DB_Device_subsystem_restarted__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Device_subsystem_restarted__neoVI_Index, 0)
extern int DB_Ethernet_DAQ_Report_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Recording; /// Min: 0 Max: 1 Units: 
    BYTE Recording_raw;
    double FPGA_Alive; /// Min: 0 Max: 1 Units: 
    BYTE FPGA_Alive_raw;
    double Bad_Chip; /// Min: 0 Max: 1 Units: 
    BYTE Bad_Chip_raw;
    double Raw_MAC_Mode; /// Min: 0 Max: 1 Units: 
    BYTE Raw_MAC_Mode_raw;
    double IPv4_Filter; /// Min: 0 Max: 1 Units: 
    BYTE IPv4_Filter_raw;
    double RxOverflow; /// Min: 0 Max: 1 Units: 
    BYTE RxOverflow_raw;
    double CmdBusy; /// Min: 0 Max: 1 Units: 
    BYTE CmdBusy_raw;
    double LogTO; /// Min: 0 Max: 1 Units: 
    BYTE LogTO_raw;
    double SockActivityTO; /// Min: 0 Max: 1 Units: 
    BYTE SockActivityTO_raw;
    double FPGAComTO; /// Min: 0 Max: 255 Units: 
    BYTE FPGAComTO_raw;
    double SockConfigTO; /// Min: 0 Max: 255 Units: 
    BYTE SockConfigTO_raw;
    double SockDiscon; /// Min: 0 Max: 255 Units: 
    BYTE SockDiscon_raw;
    double WcfSM; /// Min: 0 Max: 255 Units: 
    BYTE WcfSM_raw;
    double TxMsgsPending; /// Min: 0 Max: 255 Units: 
    BYTE TxMsgsPending_raw;
} DB_Ethernet_DAQ_Report_neoVI;


void DB_Ethernet_DAQ_Report_neoVI_Init(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_Transmit(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_Transmit_raw(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg);
int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromRawSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg);
#define DB_Ethernet_DAQ_Report_neoVI_Recording_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 0, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_FPGA_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 1, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_Bad_Chip_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 2, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_Raw_MAC_Mode_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 3, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_IPv4_Filter_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 4, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_RxOverflow_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 5, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_CmdBusy_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 6, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_LogTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 7, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_SockActivityTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 8, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_FPGAComTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 9, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_SockConfigTO_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 10, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_SockDiscon_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 11, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_WcfSM_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 12, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_TxMsgsPending_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, 13, dPhysicalValue);
#define DB_Ethernet_DAQ_Report_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Ethernet_DAQ_Report_neoVI_Index, 0)
extern int DB_neoVI_Status_Update_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Type; /// Min: 0 Max: 255 Units: 
    BYTE Type_raw;
    double ChangeCount; /// Min: 0 Max: 255 Units: 
    BYTE ChangeCount_raw;
} DB_neoVI_Status_Update_neoVI;


void DB_neoVI_Status_Update_neoVI_Init(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_Transmit(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_Transmit_raw(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_UpdateBytesFromSignals(DB_neoVI_Status_Update_neoVI * pMsg);
int DB_neoVI_Status_Update_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Status_Update_neoVI * pMsg);
#define DB_neoVI_Status_Update_neoVI_Type_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Status_Update_neoVI_ChangeCount_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Status_Update_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Status_Update_neoVI_Index, 0)
extern int DB_Scc_Status_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double FvA; /// Min: 0 Max: 1 Units: 
    BYTE FvA_raw;
    double ScA; /// Min: 0 Max: 1 Units: 
    BYTE ScA_raw;
    double Atv; /// Min: 0 Max: 1 Units: 
    BYTE Atv_raw;
    double sip; /// Min: 0 Max: 1 Units: 
    BYTE sip_raw;
    double pt; /// Min: 0 Max: 4294967295 Units: 
    DWORD pt_raw;
    double Req; /// Min: 0 Max: 255 Units: 
    BYTE Req_raw;
} DB_Scc_Status_neoVI;


void DB_Scc_Status_neoVI_Init(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_Transmit(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_Transmit_raw(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_UpdateBytesFromSignals(DB_Scc_Status_neoVI * pMsg);
int DB_Scc_Status_neoVI_UpdateBytesFromRawSignals(DB_Scc_Status_neoVI * pMsg);
#define DB_Scc_Status_neoVI_FvA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 0, dPhysicalValue);
#define DB_Scc_Status_neoVI_ScA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 1, dPhysicalValue);
#define DB_Scc_Status_neoVI_Atv_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 2, dPhysicalValue);
#define DB_Scc_Status_neoVI_sip_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 3, dPhysicalValue);
#define DB_Scc_Status_neoVI_pt_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 4, dPhysicalValue);
#define DB_Scc_Status_neoVI_Req_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, 5, dPhysicalValue);
#define DB_Scc_Status_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Scc_Status_neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double PWM1_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM1_IN_raw;
    double PWM2_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM2_IN_raw;
    double PWM3_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM3_IN_raw;
    double PWM4_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM4_IN_raw;
    double PWM5_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM5_IN_raw;
    double PWM6_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM6_IN_raw;
    double PWM7_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM7_IN_raw;
    double PWM8_IN; /// Min: 0 Max: 1 Units: 
    BYTE PWM8_IN_raw;
} DB_Report_Message__Analog_Card_PWM_Inputs__neoVI;


void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM1_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM2_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM3_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 2, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM4_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 3, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM5_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 4, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM6_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 5, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM7_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 6, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_PWM8_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 7, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM1__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM1__neoVI;


void DB_Report_Message__Analog_Card_PWM1__neoVI_Init(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM1__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM1__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM1__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM2__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM2__neoVI;


void DB_Report_Message__Analog_Card_PWM2__neoVI_Init(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM2__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM2__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM2__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM3__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM3__neoVI;


void DB_Report_Message__Analog_Card_PWM3__neoVI_Init(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM3__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM3__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM3__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM4__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM4__neoVI;


void DB_Report_Message__Analog_Card_PWM4__neoVI_Init(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM4__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM4__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM4__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM5__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM5__neoVI;


void DB_Report_Message__Analog_Card_PWM5__neoVI_Init(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM5__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM5__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM5__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM6__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM6__neoVI;


void DB_Report_Message__Analog_Card_PWM6__neoVI_Init(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM6__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM6__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM6__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM7__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM7__neoVI;


void DB_Report_Message__Analog_Card_PWM7__neoVI_Init(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM7__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM7__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM7__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, 0)
extern int DB_Report_Message__Analog_Card_PWM8__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Pulse_Width_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Pulse_Width_ms__raw;
    double Period_ms_; /// Min: 0 Max: 0 Units: ms
    DWORD Period_ms__raw;
} DB_Report_Message__Analog_Card_PWM8__neoVI;


void DB_Report_Message__Analog_Card_PWM8__neoVI_Init(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg);
#define DB_Report_Message__Analog_Card_PWM8__neoVI_Pulse_Width_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, 0, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM8__neoVI_Period_ms__PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, 1, dPhysicalValue);
#define DB_Report_Message__Analog_Card_PWM8__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, 0)
extern int DB_neoVI_Device_Status_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double HID_Temperature__C_; /// Min: 0 Max: 255.99609375 Units: deg C
    WORD HID_Temperature__C__raw;
    double HID_Bus_Voltage__V_; /// Min: 0 Max: 255.99609375 Units: V
    WORD HID_Bus_Voltage__V__raw;
    double VNET_Temperature__C_; /// Min: 0 Max: 255.99609375 Units: deg C
    WORD VNET_Temperature__C__raw;
    double VNET_Bus_Voltage__V_; /// Min: 0 Max: 255.99609375 Units: V
    WORD VNET_Bus_Voltage__V__raw;
} DB_neoVI_Device_Status_neoVI;


void DB_neoVI_Device_Status_neoVI_Init(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_Transmit(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_Transmit_raw(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_neoVI * pMsg);
int DB_neoVI_Device_Status_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_neoVI * pMsg);
#define DB_neoVI_Device_Status_neoVI_HID_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_HID_Bus_Voltage__V__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_VNET_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 2, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_VNET_Bus_Voltage__V__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, 3, dPhysicalValue);
#define DB_neoVI_Device_Status_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Device_Status_neoVI_Index, 0)
extern int DB_neoVI_Device_Status_2_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Disk_Space_Avail__WiVI__KB; /// Min: 0 Max: 4294967295 Units: KB
    DWORD Disk_Space_Avail__WiVI__KB_raw;
    double Power_Supply_Voltage; /// Min: 0 Max: 255.99609375 Units: V
    WORD Power_Supply_Voltage_raw;
    double Temperature__C_; /// Min: 0 Max: 255.99609375 Units: deg C
    WORD Temperature__C__raw;
} DB_neoVI_Device_Status_2_neoVI;


void DB_neoVI_Device_Status_2_neoVI_Init(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_Transmit(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_Transmit_raw(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_2_neoVI * pMsg);
int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_2_neoVI * pMsg);
#define DB_neoVI_Device_Status_2_neoVI_Disk_Space_Avail__WiVI__KB_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, 0, dPhysicalValue);
#define DB_neoVI_Device_Status_2_neoVI_Power_Supply_Voltage_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, 1, dPhysicalValue);
#define DB_neoVI_Device_Status_2_neoVI_Temperature__C__PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, 2, dPhysicalValue);
#define DB_neoVI_Device_Status_2_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_neoVI_Device_Status_2_neoVI_Index, 0)
extern int DB_Trace_Logger_Status_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double State; /// Min: 0 Max: 8 Units: 
    BYTE State_raw;
    double Debug_Level; /// Min: 0 Max: 3 Units: 
    BYTE Debug_Level_raw;
    double IP_MSB_; /// Min: 0 Max: 255 Units: 
    BYTE IP_MSB__raw;
    double IP; /// Min: 0 Max: 255 Units: 
    BYTE IP_raw;
    double IP_sig4; /// Min: 0 Max: 255 Units: 
    BYTE IP_sig4_raw;
    double IP_LSB_; /// Min: 0 Max: 255 Units: 
    BYTE IP_LSB__raw;
    double Port; /// Min: 0 Max: 65535 Units: 
    WORD Port_raw;
} DB_Trace_Logger_Status_neoVI;

#pragma warning(disable : 4005)
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Direct_Connect 1
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Connecting 2
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Reconnecting 3
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Connected 4
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Set_Debug_Level 5
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Closing 6
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Closed 7
#define DB_Trace_Logger_Status_neoVI_$_State_$$_Timestamp 8
#pragma warning(default : 4005)

void DB_Trace_Logger_Status_neoVI_Init(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_Transmit(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_Transmit_raw(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_UpdateBytesFromSignals(DB_Trace_Logger_Status_neoVI * pMsg);
int DB_Trace_Logger_Status_neoVI_UpdateBytesFromRawSignals(DB_Trace_Logger_Status_neoVI * pMsg);
#define DB_Trace_Logger_Status_neoVI_State_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 0, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_Debug_Level_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 1, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_MSB__PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 2, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 3, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_sig4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 4, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_IP_LSB__PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 5, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_Port_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, 6, dPhysicalValue);
#define DB_Trace_Logger_Status_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Trace_Logger_Status_neoVI_Index, 0)
extern int DB_Trigger_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Logger_triggered; /// Min: 0 Max: 2 Units: 
    BYTE Logger_triggered_raw;
    double Pre_trigger_size; /// Min: 0 Max: 4294967295 Units: 
    DWORD Pre_trigger_size_raw;
    double Collection_index; /// Min: 0 Max: 255 Units: 
    BYTE Collection_index_raw;
} DB_Trigger_neoVI;

#pragma warning(disable : 4005)
#define DB_Trigger_neoVI_$_Logger_triggered_$$_NO_TRG 0
#define DB_Trigger_neoVI_$_Logger_triggered_$$_TRG_msg_ 1
#define DB_Trigger_neoVI_$_Logger_triggered_$$_TRG_ms_ 2
#pragma warning(default : 4005)

void DB_Trigger_neoVI_Init(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_Transmit(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_Transmit_raw(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_UpdateBytesFromSignals(DB_Trigger_neoVI * pMsg);
int DB_Trigger_neoVI_UpdateBytesFromRawSignals(DB_Trigger_neoVI * pMsg);
#define DB_Trigger_neoVI_Logger_triggered_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trigger_neoVI_Index, 0, dPhysicalValue);
#define DB_Trigger_neoVI_Pre_trigger_size_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trigger_neoVI_Index, 1, dPhysicalValue);
#define DB_Trigger_neoVI_Collection_index_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Trigger_neoVI_Index, 2, dPhysicalValue);
#define DB_Trigger_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Trigger_neoVI_Index, 0)
extern int DB_Ethernet_Status_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Link_Status; /// Min: 0 Max: 1 Units: 
    BYTE Link_Status_raw;
    double Link_Speed; /// Min: 0 Max: 2 Units: 
    BYTE Link_Speed_raw;
    double Link_Duplex; /// Min: 0 Max: 1 Units: 
    BYTE Link_Duplex_raw;
} DB_Ethernet_Status_neoVI;

#pragma warning(disable : 4005)
#define DB_Ethernet_Status_neoVI_$_Link_Status_$$_Link_Down 0
#define DB_Ethernet_Status_neoVI_$_Link_Status_$$_Link_Up 1
#define DB_Ethernet_Status_neoVI_$_Link_Speed_$$_10Mbps 0
#define DB_Ethernet_Status_neoVI_$_Link_Speed_$$_100Mbps 1
#define DB_Ethernet_Status_neoVI_$_Link_Speed_$$_1000Mbps 2
#define DB_Ethernet_Status_neoVI_$_Link_Duplex_$$_Half_Duplex 0
#define DB_Ethernet_Status_neoVI_$_Link_Duplex_$$_Full_Duplex 1
#pragma warning(default : 4005)

void DB_Ethernet_Status_neoVI_Init(DB_Ethernet_Status_neoVI * pMsg);
int DB_Ethernet_Status_neoVI_Transmit(DB_Ethernet_Status_neoVI * pMsg);
int DB_Ethernet_Status_neoVI_Transmit_raw(DB_Ethernet_Status_neoVI * pMsg);
int DB_Ethernet_Status_neoVI_UpdateBytesFromSignals(DB_Ethernet_Status_neoVI * pMsg);
int DB_Ethernet_Status_neoVI_UpdateBytesFromRawSignals(DB_Ethernet_Status_neoVI * pMsg);
#define DB_Ethernet_Status_neoVI_Link_Status_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, 0, dPhysicalValue);
#define DB_Ethernet_Status_neoVI_Link_Speed_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, 1, dPhysicalValue);
#define DB_Ethernet_Status_neoVI_Link_Duplex_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, 2, dPhysicalValue);
#define DB_Ethernet_Status_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Ethernet_Status_neoVI_Index, 0)
extern int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Network; /// Min: 0 Max: 11 Units: 
    BYTE Network_raw;
    double Link_Status; /// Min: 0 Max: 1 Units: 
    BYTE Link_Status_raw;
} DB_OP__BR__Ethernet___Link_status_changed_neoVI;

#pragma warning(disable : 4005)
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH1 0
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH2 1
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH3 2
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH4 3
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$________________OP_ETH5 4
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH6 5
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH7 6
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH8 7
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$________________OP_ETH9 8
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH10 9
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH11 10
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Network_$$_OP_ETH12 11
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Link_Status_$$_Down 0
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_$_Link_Status_$$_Up 1
#pragma warning(default : 4005)

void DB_OP__BR__Ethernet___Link_status_changed_neoVI_Init(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg);
int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Transmit(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg);
int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Transmit_raw(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg);
int DB_OP__BR__Ethernet___Link_status_changed_neoVI_UpdateBytesFromSignals(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg);
int DB_OP__BR__Ethernet___Link_status_changed_neoVI_UpdateBytesFromRawSignals(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg);
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_Network_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, 0, dPhysicalValue);
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_Link_Status_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, 1, dPhysicalValue);
#define DB_OP__BR__Ethernet___Link_status_changed_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, 0)
extern int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Period; /// Min: 0 Max: 4294967295 Units: us
    DWORD Period_raw;
    double Pulse_Width; /// Min: 0 Max: 4294967295 Units: us
    DWORD Pulse_Width_raw;
} DB_FIRE2_Report_Message_PWM_IN_1__neoVI;


void DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Init(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Transmit(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Transmit_raw(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_UpdateBytesFromSignals(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_UpdateBytesFromRawSignals(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg);
#define DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Period_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, 0, dPhysicalValue);
#define DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Pulse_Width_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, 1, dPhysicalValue);
#define DB_FIRE2_Report_Message_PWM_IN_1__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, 0)
extern int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Period; /// Min: 0 Max: 4294967295 Units: us
    DWORD Period_raw;
    double Pulse_Width; /// Min: 0 Max: 4294967295 Units: us
    DWORD Pulse_Width_raw;
} DB_FIRE2_Report_Message_PWM_IN_2__neoVI;


void DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Init(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Transmit(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Transmit_raw(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_UpdateBytesFromSignals(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg);
int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_UpdateBytesFromRawSignals(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg);
#define DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Period_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, 0, dPhysicalValue);
#define DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Pulse_Width_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, 1, dPhysicalValue);
#define DB_FIRE2_Report_Message_PWM_IN_2__neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, 0)
extern int DB_Hardware_Latency_Test_neoVI_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Latency__us_; /// Min: 0 Max: 18446744073709551615 Units: us
    uint64 Latency__us__raw;
} DB_Hardware_Latency_Test_neoVI;


void DB_Hardware_Latency_Test_neoVI_Init(DB_Hardware_Latency_Test_neoVI * pMsg);
int DB_Hardware_Latency_Test_neoVI_Transmit(DB_Hardware_Latency_Test_neoVI * pMsg);
int DB_Hardware_Latency_Test_neoVI_Transmit_raw(DB_Hardware_Latency_Test_neoVI * pMsg);
int DB_Hardware_Latency_Test_neoVI_UpdateBytesFromSignals(DB_Hardware_Latency_Test_neoVI * pMsg);
int DB_Hardware_Latency_Test_neoVI_UpdateBytesFromRawSignals(DB_Hardware_Latency_Test_neoVI * pMsg);
#define DB_Hardware_Latency_Test_neoVI_Latency__us__PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, 0, dPhysicalValue);
#define DB_Hardware_Latency_Test_neoVI_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Hardware_Latency_Test_neoVI_Index, 0)
extern int DB_SW1_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double WiperSwtOFF; /// Min: 0 Max: 3 Units: 
    BYTE WiperSwtOFF_raw;
    double WiperWashSwt; /// Min: 0 Max: 3 Units: 
    BYTE WiperWashSwt_raw;
    double WiperModeAutoSwt; /// Min: 0 Max: 3 Units: 
    BYTE WiperModeAutoSwt_raw;
    double WiperModeMistSwt; /// Min: 0 Max: 3 Units: 
    BYTE WiperModeMistSwt_raw;
    double AxleDifferentialLockSwt; /// Min: 0 Max: 3 Units: 
    BYTE AxleDifferentialLockSwt_raw;
    double WheelDifferLockSwt; /// Min: 0 Max: 3 Units: 
    BYTE WheelDifferLockSwt_raw;
    double RSerSwtSig; /// Min: 0 Max: 3 Units: 
    BYTE RSerSwtSig_raw;
    double RFogLgtSwtSig; /// Min: 0 Max: 3 Units: 
    BYTE RFogLgtSwtSig_raw;
    double FFogLgtSwtSig; /// Min: 0 Max: 3 Units: 
    BYTE FFogLgtSwtSig_raw;
    double LightSwt_II; /// Min: 0 Max: 3 Units: 
    BYTE LightSwt_II_raw;
    double LightSwt_I; /// Min: 0 Max: 3 Units: 
    BYTE LightSwt_I_raw;
    double RhTurnSwtSig; /// Min: 0 Max: 3 Units: 
    BYTE RhTurnSwtSig_raw;
    double LhTurnSwtSig; /// Min: 0 Max: 3 Units: 
    BYTE LhTurnSwtSig_raw;
    double HBSwtSig; /// Min: 0 Max: 3 Units: 
    BYTE HBSwtSig_raw;
    double Horn_Reserved; /// Min: 0 Max: 3 Units: 
    BYTE Horn_Reserved_raw;
    double WiperModeHighSwt; /// Min: 0 Max: 3 Units: 
    BYTE WiperModeHighSwt_raw;
    double WiperModeLowSwt; /// Min: 0 Max: 3 Units: 
    BYTE WiperModeLowSwt_raw;
    double LightSW_Auto; /// Min: 0 Max: 3 Units: 
    BYTE LightSW_Auto_raw;
} DB_SW1_HS_CAN;

#define DB_SW1_HS_CAN_SendType 0
#define DB_SW1_HS_CAN_SendRate 50
#pragma warning(disable : 4005)
#define DB_SW1_HS_CAN_$_WiperSwtOFF_$$____ 0
#define DB_SW1_HS_CAN_$_WiperSwtOFF_$$___ 1
#define DB_SW1_HS_CAN_$_WiperSwtOFF_$$___ 2
#define DB_SW1_HS_CAN_$_WiperSwtOFF_$$___ 3
#define DB_SW1_HS_CAN_$_WiperWashSwt_$$____ 0
#define DB_SW1_HS_CAN_$_WiperWashSwt_$$___ 1
#define DB_SW1_HS_CAN_$_WiperWashSwt_$$___ 2
#define DB_SW1_HS_CAN_$_WiperWashSwt_$$___ 3
#define DB_SW1_HS_CAN_$_WiperModeAutoSwt_$$____ 0
#define DB_SW1_HS_CAN_$_WiperModeAutoSwt_$$___ 1
#define DB_SW1_HS_CAN_$_WiperModeAutoSwt_$$___ 2
#define DB_SW1_HS_CAN_$_WiperModeAutoSwt_$$___ 3
#define DB_SW1_HS_CAN_$_WiperModeMistSwt_$$____ 0
#define DB_SW1_HS_CAN_$_WiperModeMistSwt_$$___ 1
#define DB_SW1_HS_CAN_$_WiperModeMistSwt_$$___ 2
#define DB_SW1_HS_CAN_$_WiperModeMistSwt_$$___ 3
#define DB_SW1_HS_CAN_$_AxleDifferentialLockSwt_$$____ 0
#define DB_SW1_HS_CAN_$_AxleDifferentialLockSwt_$$___ 1
#define DB_SW1_HS_CAN_$_AxleDifferentialLockSwt_$$___ 2
#define DB_SW1_HS_CAN_$_AxleDifferentialLockSwt_$$___ 3
#define DB_SW1_HS_CAN_$_WheelDifferLockSwt_$$____ 0
#define DB_SW1_HS_CAN_$_WheelDifferLockSwt_$$___ 1
#define DB_SW1_HS_CAN_$_WheelDifferLockSwt_$$___ 2
#define DB_SW1_HS_CAN_$_WheelDifferLockSwt_$$___ 3
#define DB_SW1_HS_CAN_$_RSerSwtSig_$$____ 0
#define DB_SW1_HS_CAN_$_RSerSwtSig_$$___ 1
#define DB_SW1_HS_CAN_$_RSerSwtSig_$$___ 2
#define DB_SW1_HS_CAN_$_RSerSwtSig_$$___ 3
#define DB_SW1_HS_CAN_$_RFogLgtSwtSig_$$____ 0
#define DB_SW1_HS_CAN_$_RFogLgtSwtSig_$$___ 1
#define DB_SW1_HS_CAN_$_RFogLgtSwtSig_$$___ 2
#define DB_SW1_HS_CAN_$_RFogLgtSwtSig_$$___ 3
#define DB_SW1_HS_CAN_$_FFogLgtSwtSig_$$____ 0
#define DB_SW1_HS_CAN_$_FFogLgtSwtSig_$$___ 1
#define DB_SW1_HS_CAN_$_FFogLgtSwtSig_$$___ 2
#define DB_SW1_HS_CAN_$_FFogLgtSwtSig_$$___ 3
#define DB_SW1_HS_CAN_$_LightSwt_II_$$____ 0
#define DB_SW1_HS_CAN_$_LightSwt_II_$$___ 1
#define DB_SW1_HS_CAN_$_LightSwt_II_$$___ 2
#define DB_SW1_HS_CAN_$_LightSwt_II_$$___ 3
#define DB_SW1_HS_CAN_$_LightSwt_I_$$____ 0
#define DB_SW1_HS_CAN_$_LightSwt_I_$$___ 1
#define DB_SW1_HS_CAN_$_LightSwt_I_$$___ 2
#define DB_SW1_HS_CAN_$_LightSwt_I_$$___ 3
#define DB_SW1_HS_CAN_$_RhTurnSwtSig_$$____ 0
#define DB_SW1_HS_CAN_$_RhTurnSwtSig_$$___ 1
#define DB_SW1_HS_CAN_$_RhTurnSwtSig_$$___ 2
#define DB_SW1_HS_CAN_$_RhTurnSwtSig_$$___ 3
#define DB_SW1_HS_CAN_$_LhTurnSwtSig_$$____ 0
#define DB_SW1_HS_CAN_$_LhTurnSwtSig_$$___ 1
#define DB_SW1_HS_CAN_$_LhTurnSwtSig_$$___ 2
#define DB_SW1_HS_CAN_$_LhTurnSwtSig_$$___ 3
#define DB_SW1_HS_CAN_$_HBSwtSig_$$____ 0
#define DB_SW1_HS_CAN_$_HBSwtSig_$$___ 1
#define DB_SW1_HS_CAN_$_HBSwtSig_$$___ 2
#define DB_SW1_HS_CAN_$_HBSwtSig_$$___ 3
#define DB_SW1_HS_CAN_$_Horn_Reserved_$$____ 0
#define DB_SW1_HS_CAN_$_Horn_Reserved_$$___ 1
#define DB_SW1_HS_CAN_$_Horn_Reserved_$$___ 2
#define DB_SW1_HS_CAN_$_Horn_Reserved_$$___ 3
#define DB_SW1_HS_CAN_$_WiperModeHighSwt_$$____ 0
#define DB_SW1_HS_CAN_$_WiperModeHighSwt_$$___ 1
#define DB_SW1_HS_CAN_$_WiperModeHighSwt_$$___ 2
#define DB_SW1_HS_CAN_$_WiperModeHighSwt_$$___ 3
#define DB_SW1_HS_CAN_$_WiperModeLowSwt_$$____ 0
#define DB_SW1_HS_CAN_$_WiperModeLowSwt_$$___ 1
#define DB_SW1_HS_CAN_$_WiperModeLowSwt_$$___ 2
#define DB_SW1_HS_CAN_$_WiperModeLowSwt_$$___ 3
#define DB_SW1_HS_CAN_$_LightSW_Auto_$$____ 0
#define DB_SW1_HS_CAN_$_LightSW_Auto_$$___ 1
#define DB_SW1_HS_CAN_$_LightSW_Auto_$$___ 2
#define DB_SW1_HS_CAN_$_LightSW_Auto_$$___ 3
#pragma warning(default : 4005)

void DB_SW1_HS_CAN_Init(DB_SW1_HS_CAN * pMsg);
int DB_SW1_HS_CAN_Transmit(DB_SW1_HS_CAN * pMsg);
int DB_SW1_HS_CAN_Transmit_raw(DB_SW1_HS_CAN * pMsg);
int DB_SW1_HS_CAN_UpdateBytesFromSignals(DB_SW1_HS_CAN * pMsg);
int DB_SW1_HS_CAN_UpdateBytesFromRawSignals(DB_SW1_HS_CAN * pMsg);
#define DB_SW1_HS_CAN_WiperSwtOFF_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_SW1_HS_CAN_WiperWashSwt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 1, dPhysicalValue);
#define DB_SW1_HS_CAN_WiperModeAutoSwt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 2, dPhysicalValue);
#define DB_SW1_HS_CAN_WiperModeMistSwt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 3, dPhysicalValue);
#define DB_SW1_HS_CAN_AxleDifferentialLockSwt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 4, dPhysicalValue);
#define DB_SW1_HS_CAN_WheelDifferLockSwt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 5, dPhysicalValue);
#define DB_SW1_HS_CAN_RSerSwtSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 6, dPhysicalValue);
#define DB_SW1_HS_CAN_RFogLgtSwtSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 7, dPhysicalValue);
#define DB_SW1_HS_CAN_FFogLgtSwtSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 8, dPhysicalValue);
#define DB_SW1_HS_CAN_LightSwt_II_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 9, dPhysicalValue);
#define DB_SW1_HS_CAN_LightSwt_I_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 10, dPhysicalValue);
#define DB_SW1_HS_CAN_RhTurnSwtSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 11, dPhysicalValue);
#define DB_SW1_HS_CAN_LhTurnSwtSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 12, dPhysicalValue);
#define DB_SW1_HS_CAN_HBSwtSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 13, dPhysicalValue);
#define DB_SW1_HS_CAN_Horn_Reserved_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 14, dPhysicalValue);
#define DB_SW1_HS_CAN_WiperModeHighSwt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 15, dPhysicalValue);
#define DB_SW1_HS_CAN_WiperModeLowSwt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 16, dPhysicalValue);
#define DB_SW1_HS_CAN_LightSW_Auto_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW1_HS_CAN_Index, 17, dPhysicalValue);
#define DB_SW1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_SW1_HS_CAN_Index, 0)
extern int DB_SW2_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Ignition_ACC; /// Min: 0 Max: 3 Units: 
    BYTE Ignition_ACC_raw;
    double Ignition_IN; /// Min: 0 Max: 3 Units: 
    BYTE Ignition_IN_raw;
    double Ignition_START; /// Min: 0 Max: 3 Units: 
    BYTE Ignition_START_raw;
    double Ignition_ON; /// Min: 0 Max: 3 Units: 
    BYTE Ignition_ON_raw;
    double Ignition_OFF; /// Min: 0 Max: 3 Units: 
    BYTE Ignition_OFF_raw;
    double FrontWorkLightSW; /// Min: 0 Max: 3 Units: 
    BYTE FrontWorkLightSW_raw;
    double ReservedSW4; /// Min: 0 Max: 3 Units: 
    BYTE ReservedSW4_raw;
    double WaistLightSW; /// Min: 0 Max: 3 Units: 
    BYTE WaistLightSW_raw;
} DB_SW2_HS_CAN;

#define DB_SW2_HS_CAN_SendType 0
#define DB_SW2_HS_CAN_SendRate 50

void DB_SW2_HS_CAN_Init(DB_SW2_HS_CAN * pMsg);
int DB_SW2_HS_CAN_Transmit(DB_SW2_HS_CAN * pMsg);
int DB_SW2_HS_CAN_Transmit_raw(DB_SW2_HS_CAN * pMsg);
int DB_SW2_HS_CAN_UpdateBytesFromSignals(DB_SW2_HS_CAN * pMsg);
int DB_SW2_HS_CAN_UpdateBytesFromRawSignals(DB_SW2_HS_CAN * pMsg);
#define DB_SW2_HS_CAN_Ignition_ACC_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW2_HS_CAN_Index, 0, dPhysicalValue);
#define DB_SW2_HS_CAN_Ignition_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW2_HS_CAN_Index, 1, dPhysicalValue);
#define DB_SW2_HS_CAN_Ignition_START_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW2_HS_CAN_Index, 2, dPhysicalValue);
#define DB_SW2_HS_CAN_Ignition_ON_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW2_HS_CAN_Index, 3, dPhysicalValue);
#define DB_SW2_HS_CAN_Ignition_OFF_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW2_HS_CAN_Index, 4, dPhysicalValue);
#define DB_SW2_HS_CAN_FrontWorkLightSW_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW2_HS_CAN_Index, 5, dPhysicalValue);
#define DB_SW2_HS_CAN_ReservedSW4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW2_HS_CAN_Index, 6, dPhysicalValue);
#define DB_SW2_HS_CAN_WaistLightSW_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_SW2_HS_CAN_Index, 7, dPhysicalValue);
#define DB_SW2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_SW2_HS_CAN_Index, 0)
extern int DB_VehCfg_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double BatteryCapacity; /// Min: 0 Max: 255 Units: Ah
    BYTE BatteryCapacity_raw;
    double VIN_Number3; /// Min: 0 Max: 255 Units: 
    BYTE VIN_Number3_raw;
    double VIN_Number2; /// Min: 0 Max: 18446744073709551615 Units: 
    uint64 VIN_Number2_raw;
    double VIN_Number1; /// Min: 0 Max: 18446744073709551615 Units: 
    uint64 VIN_Number1_raw;
    double EMS_TyperCfig; /// Min: 0 Max: 63 Units: 
    BYTE EMS_TyperCfig_raw;
    double TorqueCtrFunCfig; /// Min: 0 Max: 1 Units: 
    BYTE TorqueCtrFunCfig_raw;
    double OQS_A2_InstallCfig; /// Min: 0 Max: 1 Units: 
    BYTE OQS_A2_InstallCfig_raw;
    double OQS_A1_InstallCfig; /// Min: 0 Max: 1 Units: 
    BYTE OQS_A1_InstallCfig_raw;
    double OQS_T_InstallCfig; /// Min: 0 Max: 1 Units: 
    BYTE OQS_T_InstallCfig_raw;
    double OQS_E_InstallCfig; /// Min: 0 Max: 1 Units: 
    BYTE OQS_E_InstallCfig_raw;
    double EngineOilMassSense_InstallCfig; /// Min: 0 Max: 1 Units: 
    BYTE EngineOilMassSense_InstallCfig_raw;
    double Anti_ThiefFunCfig; /// Min: 0 Max: 1 Units: 
    BYTE Anti_ThiefFunCfig_raw;
    double FuelMassDetection_InstallCfig; /// Min: 0 Max: 1 Units: 
    BYTE FuelMassDetection_InstallCfig_raw;
    double RLS_InstallCfig; /// Min: 0 Max: 1 Units: 
    BYTE RLS_InstallCfig_raw;
    double BCM_InstallCfig; /// Min: 0 Max: 1 Units: 
    BYTE BCM_InstallCfig_raw;
    double ElectromagneticPowerSwtFunCfig; /// Min: 0 Max: 3 Units: 
    BYTE ElectromagneticPowerSwtFunCfig_raw;
} DB_VehCfg_HS_CAN;

#define DB_VehCfg_HS_CAN_SendType 2
#define DB_VehCfg_HS_CAN_SendRate 50

void DB_VehCfg_HS_CAN_Init(DB_VehCfg_HS_CAN * pMsg);
int DB_VehCfg_HS_CAN_Transmit(DB_VehCfg_HS_CAN * pMsg);
int DB_VehCfg_HS_CAN_Transmit_raw(DB_VehCfg_HS_CAN * pMsg);
int DB_VehCfg_HS_CAN_UpdateBytesFromSignals(DB_VehCfg_HS_CAN * pMsg);
int DB_VehCfg_HS_CAN_UpdateBytesFromRawSignals(DB_VehCfg_HS_CAN * pMsg);
#define DB_VehCfg_HS_CAN_BatteryCapacity_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 0, dPhysicalValue);
#define DB_VehCfg_HS_CAN_VIN_Number3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 1, dPhysicalValue);
#define DB_VehCfg_HS_CAN_VIN_Number2_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 2, dPhysicalValue);
#define DB_VehCfg_HS_CAN_VIN_Number1_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 3, dPhysicalValue);
#define DB_VehCfg_HS_CAN_EMS_TyperCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 4, dPhysicalValue);
#define DB_VehCfg_HS_CAN_TorqueCtrFunCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 5, dPhysicalValue);
#define DB_VehCfg_HS_CAN_OQS_A2_InstallCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 6, dPhysicalValue);
#define DB_VehCfg_HS_CAN_OQS_A1_InstallCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 7, dPhysicalValue);
#define DB_VehCfg_HS_CAN_OQS_T_InstallCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 8, dPhysicalValue);
#define DB_VehCfg_HS_CAN_OQS_E_InstallCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 9, dPhysicalValue);
#define DB_VehCfg_HS_CAN_EngineOilMassSense_InstallCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 10, dPhysicalValue);
#define DB_VehCfg_HS_CAN_Anti_ThiefFunCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 11, dPhysicalValue);
#define DB_VehCfg_HS_CAN_FuelMassDetection_InstallCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 12, dPhysicalValue);
#define DB_VehCfg_HS_CAN_RLS_InstallCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 13, dPhysicalValue);
#define DB_VehCfg_HS_CAN_BCM_InstallCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 14, dPhysicalValue);
#define DB_VehCfg_HS_CAN_ElectromagneticPowerSwtFunCfig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, 15, dPhysicalValue);
#define DB_VehCfg_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VehCfg_HS_CAN_Index, 0)
extern int DB_RouteSG_ChasO_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double OilTemperature_A2; /// Min: -273 Max: 1735 Units: 
    WORD OilTemperature_A2_raw;
    double OilTemperature_A1; /// Min: -273 Max: 1735 Units: 
    WORD OilTemperature_A1_raw;
    double OilTemperature_T; /// Min: -273 Max: 1735 Units: 
    WORD OilTemperature_T_raw;
    double OilTemperature_E; /// Min: -273 Max: 1735 Units: 
    WORD OilTemperature_E_raw;
} DB_RouteSG_ChasO_HS_CAN;

#define DB_RouteSG_ChasO_HS_CAN_SendType 0
#define DB_RouteSG_ChasO_HS_CAN_SendRate 30000
#define DB_RouteSG_ChasO_HS_CAN_SendStartDelay 0

void DB_RouteSG_ChasO_HS_CAN_Init(DB_RouteSG_ChasO_HS_CAN * pMsg);
int DB_RouteSG_ChasO_HS_CAN_Transmit(DB_RouteSG_ChasO_HS_CAN * pMsg);
int DB_RouteSG_ChasO_HS_CAN_Transmit_raw(DB_RouteSG_ChasO_HS_CAN * pMsg);
int DB_RouteSG_ChasO_HS_CAN_UpdateBytesFromSignals(DB_RouteSG_ChasO_HS_CAN * pMsg);
int DB_RouteSG_ChasO_HS_CAN_UpdateBytesFromRawSignals(DB_RouteSG_ChasO_HS_CAN * pMsg);
#define DB_RouteSG_ChasO_HS_CAN_OilTemperature_A2_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_RouteSG_ChasO_HS_CAN_Index, 0, dPhysicalValue);
#define DB_RouteSG_ChasO_HS_CAN_OilTemperature_A1_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_RouteSG_ChasO_HS_CAN_Index, 1, dPhysicalValue);
#define DB_RouteSG_ChasO_HS_CAN_OilTemperature_T_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_RouteSG_ChasO_HS_CAN_Index, 2, dPhysicalValue);
#define DB_RouteSG_ChasO_HS_CAN_OilTemperature_E_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_RouteSG_ChasO_HS_CAN_Index, 3, dPhysicalValue);
#define DB_RouteSG_ChasO_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_RouteSG_ChasO_HS_CAN_Index, 0)
extern int DB_NM_GW_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double GW_NM_Sleep_ACK; /// Min: 0 Max: 1 Units: 
    BYTE GW_NM_Sleep_ACK_raw;
    double GW_NM_Sleep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE GW_NM_Sleep_Ind_raw;
    double GW_NM_Limphome; /// Min: 0 Max: 1 Units: 
    BYTE GW_NM_Limphome_raw;
    double GW_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE GW_NM_Ring_raw;
    double GW_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE GW_NM_Alive_raw;
    double GW_NM_DA; /// Min: 0 Max: 255 Units: 
    BYTE GW_NM_DA_raw;
} DB_NM_GW_HS_CAN;

#define DB_NM_GW_HS_CAN_SendType 0
#define DB_NM_GW_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define DB_NM_GW_HS_CAN_$_GW_NM_Sleep_ACK_$$_false 0
#define DB_NM_GW_HS_CAN_$_GW_NM_Sleep_ACK_$$_true 1
#define DB_NM_GW_HS_CAN_$_GW_NM_Sleep_Ind_$$_false 0
#define DB_NM_GW_HS_CAN_$_GW_NM_Sleep_Ind_$$_true 1
#define DB_NM_GW_HS_CAN_$_GW_NM_Limphome_$$_false 0
#define DB_NM_GW_HS_CAN_$_GW_NM_Limphome_$$_true 1
#define DB_NM_GW_HS_CAN_$_GW_NM_Ring_$$_false 0
#define DB_NM_GW_HS_CAN_$_GW_NM_Ring_$$_true 1
#define DB_NM_GW_HS_CAN_$_GW_NM_Alive_$$_false 0
#define DB_NM_GW_HS_CAN_$_GW_NM_Alive_$$_true 1
#pragma warning(default : 4005)

void DB_NM_GW_HS_CAN_Init(DB_NM_GW_HS_CAN * pMsg);
int DB_NM_GW_HS_CAN_Transmit(DB_NM_GW_HS_CAN * pMsg);
int DB_NM_GW_HS_CAN_Transmit_raw(DB_NM_GW_HS_CAN * pMsg);
int DB_NM_GW_HS_CAN_UpdateBytesFromSignals(DB_NM_GW_HS_CAN * pMsg);
int DB_NM_GW_HS_CAN_UpdateBytesFromRawSignals(DB_NM_GW_HS_CAN * pMsg);
#define DB_NM_GW_HS_CAN_GW_NM_Sleep_ACK_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_GW_HS_CAN_GW_NM_Sleep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_GW_HS_CAN_GW_NM_Limphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_GW_HS_CAN_GW_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_GW_HS_CAN_GW_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_GW_HS_CAN_GW_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_GW_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_GW_HS_CAN_Index, 0)
extern int DB_MMIctrCab_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double MMIctrFLgCls; /// Min: 0 Max: 3 Units: 
    BYTE MMIctrFLgCls_raw;
    double RoofWorkCmd; /// Min: 0 Max: 7 Units: 
    BYTE RoofWorkCmd_raw;
    double RoofPositionCtr; /// Min: 0 Max: 255 Units: 
    BYTE RoofPositionCtr_raw;
    double MMIctrLBmCls; /// Min: 0 Max: 3 Units: 
    BYTE MMIctrLBmCls_raw;
    double MMIctrLBmOpn; /// Min: 0 Max: 3 Units: 
    BYTE MMIctrLBmOpn_raw;
    double MMIctrFLgOpn; /// Min: 0 Max: 3 Units: 
    BYTE MMIctrFLgOpn_raw;
} DB_MMIctrCab_HS_CAN;

#define DB_MMIctrCab_HS_CAN_SendType 8
#define DB_MMIctrCab_HS_CAN_SendStartDelay 0

void DB_MMIctrCab_HS_CAN_Init(DB_MMIctrCab_HS_CAN * pMsg);
int DB_MMIctrCab_HS_CAN_Transmit(DB_MMIctrCab_HS_CAN * pMsg);
int DB_MMIctrCab_HS_CAN_Transmit_raw(DB_MMIctrCab_HS_CAN * pMsg);
int DB_MMIctrCab_HS_CAN_UpdateBytesFromSignals(DB_MMIctrCab_HS_CAN * pMsg);
int DB_MMIctrCab_HS_CAN_UpdateBytesFromRawSignals(DB_MMIctrCab_HS_CAN * pMsg);
#define DB_MMIctrCab_HS_CAN_MMIctrFLgCls_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, 0, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_RoofWorkCmd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, 1, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_RoofPositionCtr_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, 2, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_MMIctrLBmCls_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, 3, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_MMIctrLBmOpn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, 4, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_MMIctrFLgOpn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, 5, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_MMIctrCab_HS_CAN_Index, 0)
extern int DB_TCO1_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TachographVehiclespeed; /// Min: 0 Max: 250.996 Units: km/h
    WORD TachographVehiclespeed_raw;
    double Tachographoutputshaftspeed; /// Min: 0 Max: 8031.875 Units: rpm
    WORD Tachographoutputshaftspeed_raw;
} DB_TCO1_HS_CAN;

#define DB_TCO1_HS_CAN_SendType 0
#define DB_TCO1_HS_CAN_SendRate 50

void DB_TCO1_HS_CAN_Init(DB_TCO1_HS_CAN * pMsg);
int DB_TCO1_HS_CAN_Transmit(DB_TCO1_HS_CAN * pMsg);
int DB_TCO1_HS_CAN_Transmit_raw(DB_TCO1_HS_CAN * pMsg);
int DB_TCO1_HS_CAN_UpdateBytesFromSignals(DB_TCO1_HS_CAN * pMsg);
int DB_TCO1_HS_CAN_UpdateBytesFromRawSignals(DB_TCO1_HS_CAN * pMsg);
#define DB_TCO1_HS_CAN_TachographVehiclespeed_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TCO1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_TCO1_HS_CAN_Tachographoutputshaftspeed_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TCO1_HS_CAN_Index, 1, dPhysicalValue);
#define DB_TCO1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_TCO1_HS_CAN_Index, 0)
extern int DB_VehicleCtr_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TXJ_CtrHBeamSig; /// Min: 0 Max: 3 Units: 
    BYTE TXJ_CtrHBeamSig_raw;
    double TXJ_CtrLowBeamSig; /// Min: 0 Max: 3 Units: 
    BYTE TXJ_CtrLowBeamSig_raw;
} DB_VehicleCtr_HS_CAN;

#define DB_VehicleCtr_HS_CAN_SendType 2
#define DB_VehicleCtr_HS_CAN_SendRate 50

void DB_VehicleCtr_HS_CAN_Init(DB_VehicleCtr_HS_CAN * pMsg);
int DB_VehicleCtr_HS_CAN_Transmit(DB_VehicleCtr_HS_CAN * pMsg);
int DB_VehicleCtr_HS_CAN_Transmit_raw(DB_VehicleCtr_HS_CAN * pMsg);
int DB_VehicleCtr_HS_CAN_UpdateBytesFromSignals(DB_VehicleCtr_HS_CAN * pMsg);
int DB_VehicleCtr_HS_CAN_UpdateBytesFromRawSignals(DB_VehicleCtr_HS_CAN * pMsg);
#define DB_VehicleCtr_HS_CAN_TXJ_CtrHBeamSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_Index, 0, dPhysicalValue);
#define DB_VehicleCtr_HS_CAN_TXJ_CtrLowBeamSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_Index, 1, dPhysicalValue);
#define DB_VehicleCtr_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VehicleCtr_HS_CAN_Index, 0)
extern int DB_BCM1_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double CheckAllLightsSignalState; /// Min: 0 Max: 3 Units: 
    BYTE CheckAllLightsSignalState_raw;
    double WheelAlexDifferLockOperateError; /// Min: 0 Max: 3 Units: 
    BYTE WheelAlexDifferLockOperateError_raw;
    double TrailerState_TrailerState; /// Min: 0 Max: 3 Units: 
    BYTE TrailerState_TrailerState_raw;
    double WiperWashSt; /// Min: 0 Max: 3 Units: 
    BYTE WiperWashSt_raw;
    double R_ReLSts; /// Min: 0 Max: 3 Units: 
    BYTE R_ReLSts_raw;
    double L_ReLSts; /// Min: 0 Max: 3 Units: 
    BYTE L_ReLSts_raw;
    double AtLgtSts; /// Min: 0 Max: 3 Units: 
    BYTE AtLgtSts_raw;
    double TopLgtSts; /// Min: 0 Max: 3 Units: 
    BYTE TopLgtSts_raw;
    double PosLgtOnWarr; /// Min: 0 Max: 3 Units: 
    BYTE PosLgtOnWarr_raw;
    double WiperModeSt; /// Min: 0 Max: 3 Units: 
    BYTE WiperModeSt_raw;
    double FuelStolenAlmSig; /// Min: 0 Max: 3 Units: 
    BYTE FuelStolenAlmSig_raw;
    double WheelDifferLockIndicatorLgt; /// Min: 0 Max: 3 Units: 
    BYTE WheelDifferLockIndicatorLgt_raw;
    double AxleDifferentialLockIndicatorLgt; /// Min: 0 Max: 3 Units: 
    BYTE AxleDifferentialLockIndicatorLgt_raw;
    double DayLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE DayLgtSt_raw;
    double HeadLgtWashStInd; /// Min: 0 Max: 3 Units: 
    BYTE HeadLgtWashStInd_raw;
    double FuelMassSignal; /// Min: 0 Max: 102 Units: %
    BYTE FuelMassSignal_raw;
    double BackCabWorkingLightState; /// Min: 0 Max: 3 Units: 
    BYTE BackCabWorkingLightState_raw;
    double RevLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE RevLgtSt_raw;
    double PosLgtStInd; /// Min: 0 Max: 3 Units: 
    BYTE PosLgtStInd_raw;
    double RFogLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE RFogLgtSt_raw;
    double FrontFogLightSts; /// Min: 0 Max: 3 Units: 
    BYTE FrontFogLightSts_raw;
    double BrkLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE BrkLgtSt_raw;
    double R_TurnLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE R_TurnLgtSt_raw;
    double L_TurnLgtSt; /// Min: 0 Max: 3 Units: 
    BYTE L_TurnLgtSt_raw;
    double LBeamSt; /// Min: 0 Max: 3 Units: 
    BYTE LBeamSt_raw;
    double HBeamSt; /// Min: 0 Max: 3 Units: 
    BYTE HBeamSt_raw;
} DB_BCM1_HS_CAN;

#define DB_BCM1_HS_CAN_SendType 0
#define DB_BCM1_HS_CAN_SendRate 200

void DB_BCM1_HS_CAN_Init(DB_BCM1_HS_CAN * pMsg);
int DB_BCM1_HS_CAN_Transmit(DB_BCM1_HS_CAN * pMsg);
int DB_BCM1_HS_CAN_Transmit_raw(DB_BCM1_HS_CAN * pMsg);
int DB_BCM1_HS_CAN_UpdateBytesFromSignals(DB_BCM1_HS_CAN * pMsg);
int DB_BCM1_HS_CAN_UpdateBytesFromRawSignals(DB_BCM1_HS_CAN * pMsg);
#define DB_BCM1_HS_CAN_CheckAllLightsSignalState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_BCM1_HS_CAN_WheelAlexDifferLockOperateError_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 1, dPhysicalValue);
#define DB_BCM1_HS_CAN_TrailerState_TrailerState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 2, dPhysicalValue);
#define DB_BCM1_HS_CAN_WiperWashSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 3, dPhysicalValue);
#define DB_BCM1_HS_CAN_R_ReLSts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 4, dPhysicalValue);
#define DB_BCM1_HS_CAN_L_ReLSts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 5, dPhysicalValue);
#define DB_BCM1_HS_CAN_AtLgtSts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 6, dPhysicalValue);
#define DB_BCM1_HS_CAN_TopLgtSts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 7, dPhysicalValue);
#define DB_BCM1_HS_CAN_PosLgtOnWarr_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 8, dPhysicalValue);
#define DB_BCM1_HS_CAN_WiperModeSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 9, dPhysicalValue);
#define DB_BCM1_HS_CAN_FuelStolenAlmSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 10, dPhysicalValue);
#define DB_BCM1_HS_CAN_WheelDifferLockIndicatorLgt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 11, dPhysicalValue);
#define DB_BCM1_HS_CAN_AxleDifferentialLockIndicatorLgt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 12, dPhysicalValue);
#define DB_BCM1_HS_CAN_DayLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 13, dPhysicalValue);
#define DB_BCM1_HS_CAN_HeadLgtWashStInd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 14, dPhysicalValue);
#define DB_BCM1_HS_CAN_FuelMassSignal_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 15, dPhysicalValue);
#define DB_BCM1_HS_CAN_BackCabWorkingLightState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 16, dPhysicalValue);
#define DB_BCM1_HS_CAN_RevLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 17, dPhysicalValue);
#define DB_BCM1_HS_CAN_PosLgtStInd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 18, dPhysicalValue);
#define DB_BCM1_HS_CAN_RFogLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 19, dPhysicalValue);
#define DB_BCM1_HS_CAN_FrontFogLightSts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 20, dPhysicalValue);
#define DB_BCM1_HS_CAN_BrkLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 21, dPhysicalValue);
#define DB_BCM1_HS_CAN_R_TurnLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 22, dPhysicalValue);
#define DB_BCM1_HS_CAN_L_TurnLgtSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 23, dPhysicalValue);
#define DB_BCM1_HS_CAN_LBeamSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 24, dPhysicalValue);
#define DB_BCM1_HS_CAN_HBeamSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, 25, dPhysicalValue);
#define DB_BCM1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_BCM1_HS_CAN_Index, 0)
extern int DB_BCM2_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double EngineOilLevel_ElecOilSense; /// Min: 0 Max: 100 Units: %
    BYTE EngineOilLevel_ElecOilSense_raw;
    double EngineOilTemp_ElecOilSense; /// Min: 0 Max: 100 Units: 
    BYTE EngineOilTemp_ElecOilSense_raw;
    double SOH; /// Min: 0 Max: 100 Units: %
    BYTE SOH_raw;
    double SOC; /// Min: 0 Max: 100 Units: %
    BYTE SOC_raw;
    double TransferOilQualityLevel; /// Min: 0 Max: 3 Units: 
    BYTE TransferOilQualityLevel_raw;
    double EngineOilQualityLevel; /// Min: 0 Max: 3 Units: 
    BYTE EngineOilQualityLevel_raw;
    double EnvirLightState; /// Min: 0 Max: 3 Units: 
    BYTE EnvirLightState_raw;
    double DoorUniteState; /// Min: 0 Max: 3 Units: 
    BYTE DoorUniteState_raw;
    double WaistLightState; /// Min: 0 Max: 3 Units: 
    BYTE WaistLightState_raw;
    double ForntWorkLightState; /// Min: 0 Max: 3 Units: 
    BYTE ForntWorkLightState_raw;
    double IC_LightLevelAutoCtr; /// Min: 0 Max: 7 Units: 
    BYTE IC_LightLevelAutoCtr_raw;
    double EngineOilMass_ElecOilSense; /// Min: 0 Max: 50 Units: L
    WORD EngineOilMass_ElecOilSense_raw;
    double Alex2ndOilQualityLevel; /// Min: 0 Max: 3 Units: 
    BYTE Alex2ndOilQualityLevel_raw;
    double Alex1stOilQualityLevel; /// Min: 0 Max: 3 Units: 
    BYTE Alex1stOilQualityLevel_raw;
    double DanodeRelayOutputState; /// Min: 0 Max: 3 Units: 
    BYTE DanodeRelayOutputState_raw;
    double ElectromagneticPowerSwtState; /// Min: 0 Max: 3 Units: 
    BYTE ElectromagneticPowerSwtState_raw;
} DB_BCM2_HS_CAN;

#define DB_BCM2_HS_CAN_SendType 0
#define DB_BCM2_HS_CAN_SendRate 200

void DB_BCM2_HS_CAN_Init(DB_BCM2_HS_CAN * pMsg);
int DB_BCM2_HS_CAN_Transmit(DB_BCM2_HS_CAN * pMsg);
int DB_BCM2_HS_CAN_Transmit_raw(DB_BCM2_HS_CAN * pMsg);
int DB_BCM2_HS_CAN_UpdateBytesFromSignals(DB_BCM2_HS_CAN * pMsg);
int DB_BCM2_HS_CAN_UpdateBytesFromRawSignals(DB_BCM2_HS_CAN * pMsg);
#define DB_BCM2_HS_CAN_EngineOilLevel_ElecOilSense_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 0, dPhysicalValue);
#define DB_BCM2_HS_CAN_EngineOilTemp_ElecOilSense_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 1, dPhysicalValue);
#define DB_BCM2_HS_CAN_SOH_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 2, dPhysicalValue);
#define DB_BCM2_HS_CAN_SOC_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 3, dPhysicalValue);
#define DB_BCM2_HS_CAN_TransferOilQualityLevel_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 4, dPhysicalValue);
#define DB_BCM2_HS_CAN_EngineOilQualityLevel_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 5, dPhysicalValue);
#define DB_BCM2_HS_CAN_EnvirLightState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 6, dPhysicalValue);
#define DB_BCM2_HS_CAN_DoorUniteState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 7, dPhysicalValue);
#define DB_BCM2_HS_CAN_WaistLightState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 8, dPhysicalValue);
#define DB_BCM2_HS_CAN_ForntWorkLightState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 9, dPhysicalValue);
#define DB_BCM2_HS_CAN_IC_LightLevelAutoCtr_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 10, dPhysicalValue);
#define DB_BCM2_HS_CAN_EngineOilMass_ElecOilSense_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 11, dPhysicalValue);
#define DB_BCM2_HS_CAN_Alex2ndOilQualityLevel_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 12, dPhysicalValue);
#define DB_BCM2_HS_CAN_Alex1stOilQualityLevel_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 13, dPhysicalValue);
#define DB_BCM2_HS_CAN_DanodeRelayOutputState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 14, dPhysicalValue);
#define DB_BCM2_HS_CAN_ElectromagneticPowerSwtState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, 15, dPhysicalValue);
#define DB_BCM2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_BCM2_HS_CAN_Index, 0)
extern int DB_BCM3_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double U_BATT; /// Min: 0 Max: 37 Units: V
    WORD U_BATT_raw;
    double R_TurnLgtCmdToIC; /// Min: 0 Max: 3 Units: 
    BYTE R_TurnLgtCmdToIC_raw;
    double L_TurnLgtCmdToIC; /// Min: 0 Max: 3 Units: 
    BYTE L_TurnLgtCmdToIC_raw;
    double I_RANGE; /// Min: 0 Max: 3 Units: 
    BYTE I_RANGE_raw;
    double IBATT; /// Min: 0 Max: 65535 Units: A
    WORD IBATT_raw;
} DB_BCM3_HS_CAN;

#define DB_BCM3_HS_CAN_SendType 0
#define DB_BCM3_HS_CAN_SendRate 200

void DB_BCM3_HS_CAN_Init(DB_BCM3_HS_CAN * pMsg);
int DB_BCM3_HS_CAN_Transmit(DB_BCM3_HS_CAN * pMsg);
int DB_BCM3_HS_CAN_Transmit_raw(DB_BCM3_HS_CAN * pMsg);
int DB_BCM3_HS_CAN_UpdateBytesFromSignals(DB_BCM3_HS_CAN * pMsg);
int DB_BCM3_HS_CAN_UpdateBytesFromRawSignals(DB_BCM3_HS_CAN * pMsg);
#define DB_BCM3_HS_CAN_U_BATT_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, 0, dPhysicalValue);
#define DB_BCM3_HS_CAN_R_TurnLgtCmdToIC_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, 1, dPhysicalValue);
#define DB_BCM3_HS_CAN_L_TurnLgtCmdToIC_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, 2, dPhysicalValue);
#define DB_BCM3_HS_CAN_I_RANGE_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, 3, dPhysicalValue);
#define DB_BCM3_HS_CAN_IBATT_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, 4, dPhysicalValue);
#define DB_BCM3_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_BCM3_HS_CAN_Index, 0)
extern int DB_BCMlinCmd_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double RainVal; /// Min: 0 Max: 65535 Units: 
    WORD RainVal_raw;
    double MMI_ON_OFF_Cmd; /// Min: 0 Max: 3 Units: 
    BYTE MMI_ON_OFF_Cmd_raw;
    double ScreenWiperSpeed; /// Min: 0 Max: 65535 Units: 
    WORD ScreenWiperSpeed_raw;
    double RoofWorkCmd; /// Min: 0 Max: 7 Units: 
    BYTE RoofWorkCmd_raw;
    double VolDec; /// Min: 0 Max: 3 Units: 
    BYTE VolDec_raw;
    double VolAd; /// Min: 0 Max: 3 Units: 
    BYTE VolAd_raw;
} DB_BCMlinCmd_HS_CAN;

#define DB_BCMlinCmd_HS_CAN_SendType 0
#define DB_BCMlinCmd_HS_CAN_SendRate 200
#pragma warning(disable : 4005)
#define DB_BCMlinCmd_HS_CAN_$_MMI_ON_OFF_Cmd_$$____ 0
#define DB_BCMlinCmd_HS_CAN_$_MMI_ON_OFF_Cmd_$$___ 1
#define DB_BCMlinCmd_HS_CAN_$_MMI_ON_OFF_Cmd_$$___ 2
#define DB_BCMlinCmd_HS_CAN_$_MMI_ON_OFF_Cmd_$$___ 3
#define DB_BCMlinCmd_HS_CAN_$_RoofWorkCmd_$$_no_command 0
#define DB_BCMlinCmd_HS_CAN_$_RoofWorkCmd_$$_auto_closing 1
#define DB_BCMlinCmd_HS_CAN_$_RoofWorkCmd_$$_manual_closing 2
#define DB_BCMlinCmd_HS_CAN_$_RoofWorkCmd_$$_reserved 3
#define DB_BCMlinCmd_HS_CAN_$_RoofWorkCmd_$$_reserved 4
#define DB_BCMlinCmd_HS_CAN_$_RoofWorkCmd_$$_auto_opening 5
#define DB_BCMlinCmd_HS_CAN_$_RoofWorkCmd_$$_manual_opening 6
#define DB_BCMlinCmd_HS_CAN_$_RoofWorkCmd_$$_reserved 7
#define DB_BCMlinCmd_HS_CAN_$_VolDec_$$____ 0
#define DB_BCMlinCmd_HS_CAN_$_VolDec_$$___ 1
#define DB_BCMlinCmd_HS_CAN_$_VolDec_$$___ 2
#define DB_BCMlinCmd_HS_CAN_$_VolDec_$$___ 3
#define DB_BCMlinCmd_HS_CAN_$_VolAd_$$____ 0
#define DB_BCMlinCmd_HS_CAN_$_VolAd_$$___ 1
#define DB_BCMlinCmd_HS_CAN_$_VolAd_$$___ 2
#define DB_BCMlinCmd_HS_CAN_$_VolAd_$$___ 3
#pragma warning(default : 4005)

void DB_BCMlinCmd_HS_CAN_Init(DB_BCMlinCmd_HS_CAN * pMsg);
int DB_BCMlinCmd_HS_CAN_Transmit(DB_BCMlinCmd_HS_CAN * pMsg);
int DB_BCMlinCmd_HS_CAN_Transmit_raw(DB_BCMlinCmd_HS_CAN * pMsg);
int DB_BCMlinCmd_HS_CAN_UpdateBytesFromSignals(DB_BCMlinCmd_HS_CAN * pMsg);
int DB_BCMlinCmd_HS_CAN_UpdateBytesFromRawSignals(DB_BCMlinCmd_HS_CAN * pMsg);
#define DB_BCMlinCmd_HS_CAN_RainVal_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, 0, dPhysicalValue);
#define DB_BCMlinCmd_HS_CAN_MMI_ON_OFF_Cmd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, 1, dPhysicalValue);
#define DB_BCMlinCmd_HS_CAN_ScreenWiperSpeed_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, 2, dPhysicalValue);
#define DB_BCMlinCmd_HS_CAN_RoofWorkCmd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, 3, dPhysicalValue);
#define DB_BCMlinCmd_HS_CAN_VolDec_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, 4, dPhysicalValue);
#define DB_BCMlinCmd_HS_CAN_VolAd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, 5, dPhysicalValue);
#define DB_BCMlinCmd_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_BCMlinCmd_HS_CAN_Index, 0)
extern int DB_OEL_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TurnSignalSwitch; /// Min: 0 Max: 16 Units: 
    BYTE TurnSignalSwitch_raw;
    double HazardLightSwitch; /// Min: 0 Max: 3 Units: 
    BYTE HazardLightSwitch_raw;
} DB_OEL_HS_CAN;

#define DB_OEL_HS_CAN_SendType 0
#define DB_OEL_HS_CAN_SendRate 1000
#define DB_OEL_HS_CAN_SendStartDelay 0
#pragma warning(disable : 4005)
#define DB_OEL_HS_CAN_$_TurnSignalSwitch_$$_Hazard_OFF 0
#define DB_OEL_HS_CAN_$_TurnSignalSwitch_$$_Hazard_ON 1
#define DB_OEL_HS_CAN_$_TurnSignalSwitch_$$_Error 2
#define DB_OEL_HS_CAN_$_TurnSignalSwitch_$$_Not_available 3
#define DB_OEL_HS_CAN_$_HazardLightSwitch_$$_Hazard_OFF 0
#define DB_OEL_HS_CAN_$_HazardLightSwitch_$$_Hazard_ON 1
#define DB_OEL_HS_CAN_$_HazardLightSwitch_$$_Error 2
#define DB_OEL_HS_CAN_$_HazardLightSwitch_$$_Not_available 3
#pragma warning(default : 4005)

void DB_OEL_HS_CAN_Init(DB_OEL_HS_CAN * pMsg);
int DB_OEL_HS_CAN_Transmit(DB_OEL_HS_CAN * pMsg);
int DB_OEL_HS_CAN_Transmit_raw(DB_OEL_HS_CAN * pMsg);
int DB_OEL_HS_CAN_UpdateBytesFromSignals(DB_OEL_HS_CAN * pMsg);
int DB_OEL_HS_CAN_UpdateBytesFromRawSignals(DB_OEL_HS_CAN * pMsg);
#define DB_OEL_HS_CAN_TurnSignalSwitch_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OEL_HS_CAN_Index, 0, dPhysicalValue);
#define DB_OEL_HS_CAN_HazardLightSwitch_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OEL_HS_CAN_Index, 1, dPhysicalValue);
#define DB_OEL_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_OEL_HS_CAN_Index, 0)
extern int DB_DM1_BCM_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double SPN_Mode; /// Min: 0 Max: 1 Units: 
    BYTE SPN_Mode_raw;
    double OccuranceCount; /// Min: 0 Max: 126 Units: 
    BYTE OccuranceCount_raw;
    double SPN_HighBit; /// Min: 0 Max: 7 Units: 
    BYTE SPN_HighBit_raw;
    double FMI; /// Min: 0 Max: 31 Units: 
    BYTE FMI_raw;
    double SPN_Num; /// Min: 0 Max: 65535 Units: 
    WORD SPN_Num_raw;
    double MalfunctionIndicatorLamp; /// Min: 0 Max: 3 Units: 
    BYTE MalfunctionIndicatorLamp_raw;
    double RedStopLamp; /// Min: 0 Max: 3 Units: 
    BYTE RedStopLamp_raw;
    double ProtectLamp; /// Min: 0 Max: 3 Units: 
    BYTE ProtectLamp_raw;
    double AmberWarningLamp; /// Min: 0 Max: 3 Units: 
    BYTE AmberWarningLamp_raw;
} DB_DM1_BCM_HS_CAN;

#define DB_DM1_BCM_HS_CAN_SendType 2
#define DB_DM1_BCM_HS_CAN_SendRate 1000
#pragma warning(disable : 4005)
#define DB_DM1_BCM_HS_CAN_$_MalfunctionIndicatorLamp_$$____ 0
#define DB_DM1_BCM_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 1
#define DB_DM1_BCM_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 2
#define DB_DM1_BCM_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 3
#define DB_DM1_BCM_HS_CAN_$_RedStopLamp_$$____ 0
#define DB_DM1_BCM_HS_CAN_$_RedStopLamp_$$___ 1
#define DB_DM1_BCM_HS_CAN_$_RedStopLamp_$$___ 2
#define DB_DM1_BCM_HS_CAN_$_RedStopLamp_$$___ 3
#define DB_DM1_BCM_HS_CAN_$_ProtectLamp_$$____ 0
#define DB_DM1_BCM_HS_CAN_$_ProtectLamp_$$___ 1
#define DB_DM1_BCM_HS_CAN_$_ProtectLamp_$$___ 2
#define DB_DM1_BCM_HS_CAN_$_ProtectLamp_$$___ 3
#define DB_DM1_BCM_HS_CAN_$_AmberWarningLamp_$$____ 0
#define DB_DM1_BCM_HS_CAN_$_AmberWarningLamp_$$___ 1
#define DB_DM1_BCM_HS_CAN_$_AmberWarningLamp_$$___ 2
#define DB_DM1_BCM_HS_CAN_$_AmberWarningLamp_$$___ 3
#pragma warning(default : 4005)

void DB_DM1_BCM_HS_CAN_Init(DB_DM1_BCM_HS_CAN * pMsg);
int DB_DM1_BCM_HS_CAN_Transmit(DB_DM1_BCM_HS_CAN * pMsg);
int DB_DM1_BCM_HS_CAN_Transmit_raw(DB_DM1_BCM_HS_CAN * pMsg);
int DB_DM1_BCM_HS_CAN_UpdateBytesFromSignals(DB_DM1_BCM_HS_CAN * pMsg);
int DB_DM1_BCM_HS_CAN_UpdateBytesFromRawSignals(DB_DM1_BCM_HS_CAN * pMsg);
#define DB_DM1_BCM_HS_CAN_SPN_Mode_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, 0, dPhysicalValue);
#define DB_DM1_BCM_HS_CAN_OccuranceCount_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, 1, dPhysicalValue);
#define DB_DM1_BCM_HS_CAN_SPN_HighBit_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, 2, dPhysicalValue);
#define DB_DM1_BCM_HS_CAN_FMI_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, 3, dPhysicalValue);
#define DB_DM1_BCM_HS_CAN_SPN_Num_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, 4, dPhysicalValue);
#define DB_DM1_BCM_HS_CAN_MalfunctionIndicatorLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, 5, dPhysicalValue);
#define DB_DM1_BCM_HS_CAN_RedStopLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, 6, dPhysicalValue);
#define DB_DM1_BCM_HS_CAN_ProtectLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, 7, dPhysicalValue);
#define DB_DM1_BCM_HS_CAN_AmberWarningLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, 8, dPhysicalValue);
#define DB_DM1_BCM_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_DM1_BCM_HS_CAN_Index, 0)
extern int DB_NM_BCM_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double BCM_NM_Sleep_ACK; /// Min: 0 Max: 1 Units: 
    BYTE BCM_NM_Sleep_ACK_raw;
    double BCM_NM_Sleep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE BCM_NM_Sleep_Ind_raw;
    double BCM_NM_Limphome; /// Min: 0 Max: 1 Units: 
    BYTE BCM_NM_Limphome_raw;
    double BCM_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE BCM_NM_Ring_raw;
    double BCM_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE BCM_NM_Alive_raw;
    double BCM_NM_DA; /// Min: 0 Max: 255 Units: 
    BYTE BCM_NM_DA_raw;
} DB_NM_BCM_HS_CAN;

#define DB_NM_BCM_HS_CAN_SendType 0
#define DB_NM_BCM_HS_CAN_SendRate 100
#define DB_NM_BCM_HS_CAN_SendStartDelay 0
#pragma warning(disable : 4005)
#define DB_NM_BCM_HS_CAN_$_BCM_NM_Sleep_ACK_$$_false 0
#define DB_NM_BCM_HS_CAN_$_BCM_NM_Sleep_ACK_$$_true 1
#define DB_NM_BCM_HS_CAN_$_BCM_NM_Sleep_Ind_$$_false 0
#define DB_NM_BCM_HS_CAN_$_BCM_NM_Sleep_Ind_$$_true 1
#define DB_NM_BCM_HS_CAN_$_BCM_NM_Limphome_$$_false 0
#define DB_NM_BCM_HS_CAN_$_BCM_NM_Limphome_$$_true 1
#define DB_NM_BCM_HS_CAN_$_BCM_NM_Ring_$$_false 0
#define DB_NM_BCM_HS_CAN_$_BCM_NM_Ring_$$_true 1
#define DB_NM_BCM_HS_CAN_$_BCM_NM_Alive_$$_false 0
#define DB_NM_BCM_HS_CAN_$_BCM_NM_Alive_$$_true 1
#pragma warning(default : 4005)

void DB_NM_BCM_HS_CAN_Init(DB_NM_BCM_HS_CAN * pMsg);
int DB_NM_BCM_HS_CAN_Transmit(DB_NM_BCM_HS_CAN * pMsg);
int DB_NM_BCM_HS_CAN_Transmit_raw(DB_NM_BCM_HS_CAN * pMsg);
int DB_NM_BCM_HS_CAN_UpdateBytesFromSignals(DB_NM_BCM_HS_CAN * pMsg);
int DB_NM_BCM_HS_CAN_UpdateBytesFromRawSignals(DB_NM_BCM_HS_CAN * pMsg);
#define DB_NM_BCM_HS_CAN_BCM_NM_Sleep_ACK_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_BCM_HS_CAN_BCM_NM_Sleep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_BCM_HS_CAN_BCM_NM_Limphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_BCM_HS_CAN_BCM_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_BCM_HS_CAN_BCM_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_BCM_HS_CAN_BCM_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_BCM_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_BCM_HS_CAN_Index, 0)
extern int DB_TW_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TyresLostWarningSig; /// Min: 0 Max: 3 Units: 
    BYTE TyresLostWarningSig_raw;
    double TyreID; /// Min: 0 Max: 255 Units: 
    BYTE TyreID_raw;
} DB_TW_HS_CAN;

#define DB_TW_HS_CAN_SendType 2
#define DB_TW_HS_CAN_SendRate 10000
#pragma warning(disable : 4005)
#define DB_TW_HS_CAN_$_TyresLostWarningSig_$$____ 0
#define DB_TW_HS_CAN_$_TyresLostWarningSig_$$___ 1
#define DB_TW_HS_CAN_$_TyresLostWarningSig_$$___ 2
#define DB_TW_HS_CAN_$_TyresLostWarningSig_$$___ 3
#pragma warning(default : 4005)

void DB_TW_HS_CAN_Init(DB_TW_HS_CAN * pMsg);
int DB_TW_HS_CAN_Transmit(DB_TW_HS_CAN * pMsg);
int DB_TW_HS_CAN_Transmit_raw(DB_TW_HS_CAN * pMsg);
int DB_TW_HS_CAN_UpdateBytesFromSignals(DB_TW_HS_CAN * pMsg);
int DB_TW_HS_CAN_UpdateBytesFromRawSignals(DB_TW_HS_CAN * pMsg);
#define DB_TW_HS_CAN_TyresLostWarningSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TW_HS_CAN_Index, 0, dPhysicalValue);
#define DB_TW_HS_CAN_TyreID_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TW_HS_CAN_Index, 1, dPhysicalValue);
#define DB_TW_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_TW_HS_CAN_Index, 0)
extern int DB_NM_TPMS_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TPMS_NM_Sleep_ACK; /// Min: 0 Max: 1 Units: 
    BYTE TPMS_NM_Sleep_ACK_raw;
    double TPMS_NM_Sleep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE TPMS_NM_Sleep_Ind_raw;
    double TPMS_NM_Limphome; /// Min: 0 Max: 1 Units: 
    BYTE TPMS_NM_Limphome_raw;
    double TPMS_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE TPMS_NM_Ring_raw;
    double TPMS_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE TPMS_NM_Alive_raw;
    double TPMS_NM_DA; /// Min: 0 Max: 255 Units: 
    BYTE TPMS_NM_DA_raw;
} DB_NM_TPMS_HS_CAN;

#define DB_NM_TPMS_HS_CAN_SendType 0
#define DB_NM_TPMS_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define DB_NM_TPMS_HS_CAN_$_TPMS_NM_Sleep_ACK_$$_false 0
#define DB_NM_TPMS_HS_CAN_$_TPMS_NM_Sleep_ACK_$$_true 1
#define DB_NM_TPMS_HS_CAN_$_TPMS_NM_Sleep_Ind_$$_false 0
#define DB_NM_TPMS_HS_CAN_$_TPMS_NM_Sleep_Ind_$$_true 1
#define DB_NM_TPMS_HS_CAN_$_TPMS_NM_Limphome_$$_false 0
#define DB_NM_TPMS_HS_CAN_$_TPMS_NM_Limphome_$$_true 1
#define DB_NM_TPMS_HS_CAN_$_TPMS_NM_Ring_$$_false 0
#define DB_NM_TPMS_HS_CAN_$_TPMS_NM_Ring_$$_true 1
#define DB_NM_TPMS_HS_CAN_$_TPMS_NM_Alive_$$_false 0
#define DB_NM_TPMS_HS_CAN_$_TPMS_NM_Alive_$$_true 1
#pragma warning(default : 4005)

void DB_NM_TPMS_HS_CAN_Init(DB_NM_TPMS_HS_CAN * pMsg);
int DB_NM_TPMS_HS_CAN_Transmit(DB_NM_TPMS_HS_CAN * pMsg);
int DB_NM_TPMS_HS_CAN_Transmit_raw(DB_NM_TPMS_HS_CAN * pMsg);
int DB_NM_TPMS_HS_CAN_UpdateBytesFromSignals(DB_NM_TPMS_HS_CAN * pMsg);
int DB_NM_TPMS_HS_CAN_UpdateBytesFromRawSignals(DB_NM_TPMS_HS_CAN * pMsg);
#define DB_NM_TPMS_HS_CAN_TPMS_NM_Sleep_ACK_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_TPMS_HS_CAN_TPMS_NM_Sleep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_TPMS_HS_CAN_TPMS_NM_Limphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_TPMS_HS_CAN_TPMS_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_TPMS_HS_CAN_TPMS_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_TPMS_HS_CAN_TPMS_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_TPMS_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_TPMS_HS_CAN_Index, 0)
extern int DB_DCM1_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TelecontrolLockOpenDoor; /// Min: 0 Max: 3 Units: 
    BYTE TelecontrolLockOpenDoor_raw;
    double RDrSwSig; /// Min: 0 Max: 3 Units: 
    BYTE RDrSwSig_raw;
    double LDrSwSig; /// Min: 0 Max: 3 Units: 
    BYTE LDrSwSig_raw;
    double TelecontrolLockInvalid; /// Min: 0 Max: 3 Units: 
    BYTE TelecontrolLockInvalid_raw;
} DB_DCM1_HS_CAN;

#define DB_DCM1_HS_CAN_SendType 0
#define DB_DCM1_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define DB_DCM1_HS_CAN_$_RDrSwSig_$$___ 0
#define DB_DCM1_HS_CAN_$_RDrSwSig_$$___ 1
#define DB_DCM1_HS_CAN_$_RDrSwSig_$$___ 2
#define DB_DCM1_HS_CAN_$_RDrSwSig_$$___ 3
#define DB_DCM1_HS_CAN_$_LDrSwSig_$$___ 0
#define DB_DCM1_HS_CAN_$_LDrSwSig_$$___ 1
#define DB_DCM1_HS_CAN_$_LDrSwSig_$$___ 2
#define DB_DCM1_HS_CAN_$_LDrSwSig_$$___ 3
#define DB_DCM1_HS_CAN_$_TelecontrolLockInvalid_$$____ 0
#define DB_DCM1_HS_CAN_$_TelecontrolLockInvalid_$$_____ 1
#define DB_DCM1_HS_CAN_$_TelecontrolLockInvalid_$$___ 2
#define DB_DCM1_HS_CAN_$_TelecontrolLockInvalid_$$___ 3
#pragma warning(default : 4005)

void DB_DCM1_HS_CAN_Init(DB_DCM1_HS_CAN * pMsg);
int DB_DCM1_HS_CAN_Transmit(DB_DCM1_HS_CAN * pMsg);
int DB_DCM1_HS_CAN_Transmit_raw(DB_DCM1_HS_CAN * pMsg);
int DB_DCM1_HS_CAN_UpdateBytesFromSignals(DB_DCM1_HS_CAN * pMsg);
int DB_DCM1_HS_CAN_UpdateBytesFromRawSignals(DB_DCM1_HS_CAN * pMsg);
#define DB_DCM1_HS_CAN_TelecontrolLockOpenDoor_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DCM1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_DCM1_HS_CAN_RDrSwSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DCM1_HS_CAN_Index, 1, dPhysicalValue);
#define DB_DCM1_HS_CAN_LDrSwSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DCM1_HS_CAN_Index, 2, dPhysicalValue);
#define DB_DCM1_HS_CAN_TelecontrolLockInvalid_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DCM1_HS_CAN_Index, 3, dPhysicalValue);
#define DB_DCM1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_DCM1_HS_CAN_Index, 0)
extern int DB_DCMcmd_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TelecontrolAtmosphereLightSwitch; /// Min: 0 Max: 3 Units: 
    BYTE TelecontrolAtmosphereLightSwitch_raw;
    double TelecontrolTopLightSwitch; /// Min: 0 Max: 3 Units: 
    BYTE TelecontrolTopLightSwitch_raw;
    double CheckALLLightsCmd; /// Min: 0 Max: 3 Units: 
    BYTE CheckALLLightsCmd_raw;
    double InLgtOFFSwt_InLgtOFFSwt; /// Min: 0 Max: 3 Units: 
    BYTE InLgtOFFSwt_InLgtOFFSwt_raw;
} DB_DCMcmd_HS_CAN;

#define DB_DCMcmd_HS_CAN_SendType 2
#define DB_DCMcmd_HS_CAN_SendRate 200
#pragma warning(disable : 4005)
#define DB_DCMcmd_HS_CAN_$_TelecontrolAtmosphereLightSwitch_$$____ 0
#define DB_DCMcmd_HS_CAN_$_TelecontrolAtmosphereLightSwitch_$$___ 1
#define DB_DCMcmd_HS_CAN_$_TelecontrolAtmosphereLightSwitch_$$___ 2
#define DB_DCMcmd_HS_CAN_$_TelecontrolAtmosphereLightSwitch_$$___ 3
#define DB_DCMcmd_HS_CAN_$_TelecontrolTopLightSwitch_$$____ 0
#define DB_DCMcmd_HS_CAN_$_TelecontrolTopLightSwitch_$$___ 1
#define DB_DCMcmd_HS_CAN_$_TelecontrolTopLightSwitch_$$___ 2
#define DB_DCMcmd_HS_CAN_$_TelecontrolTopLightSwitch_$$___ 3
#define DB_DCMcmd_HS_CAN_$_CheckALLLightsCmd_$$____ 0
#define DB_DCMcmd_HS_CAN_$_CheckALLLightsCmd_$$___ 1
#define DB_DCMcmd_HS_CAN_$_CheckALLLightsCmd_$$___ 2
#define DB_DCMcmd_HS_CAN_$_CheckALLLightsCmd_$$___ 3
#define DB_DCMcmd_HS_CAN_$_InLgtOFFSwt_InLgtOFFSwt_$$____ 0
#define DB_DCMcmd_HS_CAN_$_InLgtOFFSwt_InLgtOFFSwt_$$___ 1
#define DB_DCMcmd_HS_CAN_$_InLgtOFFSwt_InLgtOFFSwt_$$___ 2
#define DB_DCMcmd_HS_CAN_$_InLgtOFFSwt_InLgtOFFSwt_$$___ 3
#pragma warning(default : 4005)

void DB_DCMcmd_HS_CAN_Init(DB_DCMcmd_HS_CAN * pMsg);
int DB_DCMcmd_HS_CAN_Transmit(DB_DCMcmd_HS_CAN * pMsg);
int DB_DCMcmd_HS_CAN_Transmit_raw(DB_DCMcmd_HS_CAN * pMsg);
int DB_DCMcmd_HS_CAN_UpdateBytesFromSignals(DB_DCMcmd_HS_CAN * pMsg);
int DB_DCMcmd_HS_CAN_UpdateBytesFromRawSignals(DB_DCMcmd_HS_CAN * pMsg);
#define DB_DCMcmd_HS_CAN_TelecontrolAtmosphereLightSwitch_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DCMcmd_HS_CAN_Index, 0, dPhysicalValue);
#define DB_DCMcmd_HS_CAN_TelecontrolTopLightSwitch_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DCMcmd_HS_CAN_Index, 1, dPhysicalValue);
#define DB_DCMcmd_HS_CAN_CheckALLLightsCmd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DCMcmd_HS_CAN_Index, 2, dPhysicalValue);
#define DB_DCMcmd_HS_CAN_InLgtOFFSwt_InLgtOFFSwt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DCMcmd_HS_CAN_Index, 3, dPhysicalValue);
#define DB_DCMcmd_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_DCMcmd_HS_CAN_Index, 0)
extern int DB_NM_DCM_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DCM_NM_Sleep_ACK; /// Min: 0 Max: 1 Units: 
    BYTE DCM_NM_Sleep_ACK_raw;
    double DCM_NM_Sleep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE DCM_NM_Sleep_Ind_raw;
    double DCM_NM_Limphome; /// Min: 0 Max: 1 Units: 
    BYTE DCM_NM_Limphome_raw;
    double DCM_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE DCM_NM_Ring_raw;
    double DCM_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE DCM_NM_Alive_raw;
    double DCM_NM_DA; /// Min: 0 Max: 255 Units: 
    BYTE DCM_NM_DA_raw;
} DB_NM_DCM_HS_CAN;

#define DB_NM_DCM_HS_CAN_SendType 0
#define DB_NM_DCM_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define DB_NM_DCM_HS_CAN_$_DCM_NM_Sleep_ACK_$$_false 0
#define DB_NM_DCM_HS_CAN_$_DCM_NM_Sleep_ACK_$$_true 1
#define DB_NM_DCM_HS_CAN_$_DCM_NM_Sleep_Ind_$$_false 0
#define DB_NM_DCM_HS_CAN_$_DCM_NM_Sleep_Ind_$$_true 1
#define DB_NM_DCM_HS_CAN_$_DCM_NM_Limphome_$$_false 0
#define DB_NM_DCM_HS_CAN_$_DCM_NM_Limphome_$$_true 1
#define DB_NM_DCM_HS_CAN_$_DCM_NM_Ring_$$_false 0
#define DB_NM_DCM_HS_CAN_$_DCM_NM_Ring_$$_true 1
#define DB_NM_DCM_HS_CAN_$_DCM_NM_Alive_$$_false 0
#define DB_NM_DCM_HS_CAN_$_DCM_NM_Alive_$$_true 1
#pragma warning(default : 4005)

void DB_NM_DCM_HS_CAN_Init(DB_NM_DCM_HS_CAN * pMsg);
int DB_NM_DCM_HS_CAN_Transmit(DB_NM_DCM_HS_CAN * pMsg);
int DB_NM_DCM_HS_CAN_Transmit_raw(DB_NM_DCM_HS_CAN * pMsg);
int DB_NM_DCM_HS_CAN_UpdateBytesFromSignals(DB_NM_DCM_HS_CAN * pMsg);
int DB_NM_DCM_HS_CAN_UpdateBytesFromRawSignals(DB_NM_DCM_HS_CAN * pMsg);
#define DB_NM_DCM_HS_CAN_DCM_NM_Sleep_ACK_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_DCM_HS_CAN_DCM_NM_Sleep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_DCM_HS_CAN_DCM_NM_Limphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_DCM_HS_CAN_DCM_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_DCM_HS_CAN_DCM_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_DCM_HS_CAN_DCM_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_DCM_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_DCM_HS_CAN_Index, 0)
extern int DB_NM_AC_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AC_NM_Sleep_ACK; /// Min: 0 Max: 1 Units: 
    BYTE AC_NM_Sleep_ACK_raw;
    double AC_NM_Sleep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE AC_NM_Sleep_Ind_raw;
    double AC_NM_Limphome; /// Min: 0 Max: 1 Units: 
    BYTE AC_NM_Limphome_raw;
    double AC_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE AC_NM_Ring_raw;
    double AC_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE AC_NM_Alive_raw;
    double AC_NM_DA; /// Min: 0 Max: 255 Units: 
    BYTE AC_NM_DA_raw;
} DB_NM_AC_HS_CAN;

#define DB_NM_AC_HS_CAN_SendType 0
#define DB_NM_AC_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define DB_NM_AC_HS_CAN_$_AC_NM_Sleep_ACK_$$_false 0
#define DB_NM_AC_HS_CAN_$_AC_NM_Sleep_ACK_$$_true 1
#define DB_NM_AC_HS_CAN_$_AC_NM_Sleep_Ind_$$_false 0
#define DB_NM_AC_HS_CAN_$_AC_NM_Sleep_Ind_$$_true 1
#define DB_NM_AC_HS_CAN_$_AC_NM_Limphome_$$_false 0
#define DB_NM_AC_HS_CAN_$_AC_NM_Limphome_$$_true 1
#define DB_NM_AC_HS_CAN_$_AC_NM_Ring_$$_false 0
#define DB_NM_AC_HS_CAN_$_AC_NM_Ring_$$_true 1
#define DB_NM_AC_HS_CAN_$_AC_NM_Alive_$$_false 0
#define DB_NM_AC_HS_CAN_$_AC_NM_Alive_$$_true 1
#pragma warning(default : 4005)

void DB_NM_AC_HS_CAN_Init(DB_NM_AC_HS_CAN * pMsg);
int DB_NM_AC_HS_CAN_Transmit(DB_NM_AC_HS_CAN * pMsg);
int DB_NM_AC_HS_CAN_Transmit_raw(DB_NM_AC_HS_CAN * pMsg);
int DB_NM_AC_HS_CAN_UpdateBytesFromSignals(DB_NM_AC_HS_CAN * pMsg);
int DB_NM_AC_HS_CAN_UpdateBytesFromRawSignals(DB_NM_AC_HS_CAN * pMsg);
#define DB_NM_AC_HS_CAN_AC_NM_Sleep_ACK_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_AC_HS_CAN_AC_NM_Sleep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_AC_HS_CAN_AC_NM_Limphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_AC_HS_CAN_AC_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_AC_HS_CAN_AC_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_AC_HS_CAN_AC_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_AC_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_AC_HS_CAN_Index, 0)
extern int DB_IC1_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AccelerationSig; /// Min: -12.5 Max: 12.5 Units: m/s2
    BYTE AccelerationSig_raw;
    double RnSensty; /// Min: 0 Max: 15 Units: 
    BYTE RnSensty_raw;
    double RequestBCM_ResetA2_OilQB; /// Min: 0 Max: 3 Units: 
    BYTE RequestBCM_ResetA2_OilQB_raw;
    double RequestBCM_ResetA1_OilQB; /// Min: 0 Max: 3 Units: 
    BYTE RequestBCM_ResetA1_OilQB_raw;
    double RequestBCM_ResetT_OilQB; /// Min: 0 Max: 3 Units: 
    BYTE RequestBCM_ResetT_OilQB_raw;
    double RequestBCM_ResetE_QilQB; /// Min: 0 Max: 3 Units: 
    BYTE RequestBCM_ResetE_QilQB_raw;
} DB_IC1_HS_CAN;

#define DB_IC1_HS_CAN_SendType 0
#define DB_IC1_HS_CAN_SendRate 20
#pragma warning(disable : 4005)
#define DB_IC1_HS_CAN_$_RequestBCM_ResetA2_OilQB_$$____ 0
#define DB_IC1_HS_CAN_$_RequestBCM_ResetA2_OilQB_$$___ 1
#define DB_IC1_HS_CAN_$_RequestBCM_ResetA2_OilQB_$$___ 2
#define DB_IC1_HS_CAN_$_RequestBCM_ResetA2_OilQB_$$___ 3
#define DB_IC1_HS_CAN_$_RequestBCM_ResetA1_OilQB_$$____ 0
#define DB_IC1_HS_CAN_$_RequestBCM_ResetA1_OilQB_$$___ 1
#define DB_IC1_HS_CAN_$_RequestBCM_ResetA1_OilQB_$$___ 2
#define DB_IC1_HS_CAN_$_RequestBCM_ResetA1_OilQB_$$___ 3
#define DB_IC1_HS_CAN_$_RequestBCM_ResetT_OilQB_$$____ 0
#define DB_IC1_HS_CAN_$_RequestBCM_ResetT_OilQB_$$___ 1
#define DB_IC1_HS_CAN_$_RequestBCM_ResetT_OilQB_$$___ 2
#define DB_IC1_HS_CAN_$_RequestBCM_ResetT_OilQB_$$___ 3
#define DB_IC1_HS_CAN_$_RequestBCM_ResetE_QilQB_$$____ 0
#define DB_IC1_HS_CAN_$_RequestBCM_ResetE_QilQB_$$___ 1
#define DB_IC1_HS_CAN_$_RequestBCM_ResetE_QilQB_$$___ 2
#define DB_IC1_HS_CAN_$_RequestBCM_ResetE_QilQB_$$___ 3
#pragma warning(default : 4005)

void DB_IC1_HS_CAN_Init(DB_IC1_HS_CAN * pMsg);
int DB_IC1_HS_CAN_Transmit(DB_IC1_HS_CAN * pMsg);
int DB_IC1_HS_CAN_Transmit_raw(DB_IC1_HS_CAN * pMsg);
int DB_IC1_HS_CAN_UpdateBytesFromSignals(DB_IC1_HS_CAN * pMsg);
int DB_IC1_HS_CAN_UpdateBytesFromRawSignals(DB_IC1_HS_CAN * pMsg);
#define DB_IC1_HS_CAN_AccelerationSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_IC1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_IC1_HS_CAN_RnSensty_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_IC1_HS_CAN_Index, 1, dPhysicalValue);
#define DB_IC1_HS_CAN_RequestBCM_ResetA2_OilQB_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_IC1_HS_CAN_Index, 2, dPhysicalValue);
#define DB_IC1_HS_CAN_RequestBCM_ResetA1_OilQB_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_IC1_HS_CAN_Index, 3, dPhysicalValue);
#define DB_IC1_HS_CAN_RequestBCM_ResetT_OilQB_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_IC1_HS_CAN_Index, 4, dPhysicalValue);
#define DB_IC1_HS_CAN_RequestBCM_ResetE_QilQB_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_IC1_HS_CAN_Index, 5, dPhysicalValue);
#define DB_IC1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_IC1_HS_CAN_Index, 0)
extern int DB_NM_IC_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double IC_NM_Sleep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE IC_NM_Sleep_Ind_raw;
    double IC_NM_Sleep_ACK; /// Min: 0 Max: 1 Units: 
    BYTE IC_NM_Sleep_ACK_raw;
    double IC_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE IC_NM_Ring_raw;
    double IC_NM_Limphome; /// Min: 0 Max: 1 Units: 
    BYTE IC_NM_Limphome_raw;
    double IC_NM_DA; /// Min: 0 Max: 255 Units: 
    BYTE IC_NM_DA_raw;
    double IC_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE IC_NM_Alive_raw;
} DB_NM_IC_HS_CAN;

#define DB_NM_IC_HS_CAN_SendType 0
#define DB_NM_IC_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define DB_NM_IC_HS_CAN_$_IC_NM_Sleep_Ind_$$_false 0
#define DB_NM_IC_HS_CAN_$_IC_NM_Sleep_Ind_$$_true 1
#define DB_NM_IC_HS_CAN_$_IC_NM_Sleep_ACK_$$_false 0
#define DB_NM_IC_HS_CAN_$_IC_NM_Sleep_ACK_$$_true 1
#define DB_NM_IC_HS_CAN_$_IC_NM_Ring_$$_false 0
#define DB_NM_IC_HS_CAN_$_IC_NM_Ring_$$_true 1
#define DB_NM_IC_HS_CAN_$_IC_NM_Limphome_$$_false 0
#define DB_NM_IC_HS_CAN_$_IC_NM_Limphome_$$_true 1
#define DB_NM_IC_HS_CAN_$_IC_NM_Alive_$$_false 0
#define DB_NM_IC_HS_CAN_$_IC_NM_Alive_$$_true 1
#pragma warning(default : 4005)

void DB_NM_IC_HS_CAN_Init(DB_NM_IC_HS_CAN * pMsg);
int DB_NM_IC_HS_CAN_Transmit(DB_NM_IC_HS_CAN * pMsg);
int DB_NM_IC_HS_CAN_Transmit_raw(DB_NM_IC_HS_CAN * pMsg);
int DB_NM_IC_HS_CAN_UpdateBytesFromSignals(DB_NM_IC_HS_CAN * pMsg);
int DB_NM_IC_HS_CAN_UpdateBytesFromRawSignals(DB_NM_IC_HS_CAN * pMsg);
#define DB_NM_IC_HS_CAN_IC_NM_Sleep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_IC_HS_CAN_IC_NM_Sleep_ACK_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_IC_HS_CAN_IC_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_IC_HS_CAN_IC_NM_Limphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_IC_HS_CAN_IC_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_IC_HS_CAN_IC_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_IC_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_IC_HS_CAN_Index, 0)
extern int DB_OilQitT_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double OilDielectricConstant_T; /// Min: 0 Max: 7.842 Units: 
    WORD OilDielectricConstant_T_raw;
    double OilDensity_T; /// Min: 0 Max: 1.961 Units: gm/cc
    WORD OilDensity_T_raw;
    double OilViscosity_T; /// Min: 0 Max: 1003.984375 Units: cp
    WORD OilViscosity_T_raw;
} DB_OilQitT_HS_CAN;

#define DB_OilQitT_HS_CAN_SendType 0
#define DB_OilQitT_HS_CAN_SendRate 30000

void DB_OilQitT_HS_CAN_Init(DB_OilQitT_HS_CAN * pMsg);
int DB_OilQitT_HS_CAN_Transmit(DB_OilQitT_HS_CAN * pMsg);
int DB_OilQitT_HS_CAN_Transmit_raw(DB_OilQitT_HS_CAN * pMsg);
int DB_OilQitT_HS_CAN_UpdateBytesFromSignals(DB_OilQitT_HS_CAN * pMsg);
int DB_OilQitT_HS_CAN_UpdateBytesFromRawSignals(DB_OilQitT_HS_CAN * pMsg);
#define DB_OilQitT_HS_CAN_OilDielectricConstant_T_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitT_HS_CAN_Index, 0, dPhysicalValue);
#define DB_OilQitT_HS_CAN_OilDensity_T_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitT_HS_CAN_Index, 1, dPhysicalValue);
#define DB_OilQitT_HS_CAN_OilViscosity_T_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitT_HS_CAN_Index, 2, dPhysicalValue);
#define DB_OilQitT_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_OilQitT_HS_CAN_Index, 0)
extern int DB_OilQitE_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double OilDielectricConstant_E; /// Min: 0 Max: 7.842 Units: 
    WORD OilDielectricConstant_E_raw;
    double OilViscosity_E; /// Min: 0 Max: 1003.984375 Units: cp
    WORD OilViscosity_E_raw;
    double OilDensity_E; /// Min: 0 Max: 1.961 Units: gm/cc
    WORD OilDensity_E_raw;
} DB_OilQitE_HS_CAN;

#define DB_OilQitE_HS_CAN_SendType 0
#define DB_OilQitE_HS_CAN_SendRate 30000

void DB_OilQitE_HS_CAN_Init(DB_OilQitE_HS_CAN * pMsg);
int DB_OilQitE_HS_CAN_Transmit(DB_OilQitE_HS_CAN * pMsg);
int DB_OilQitE_HS_CAN_Transmit_raw(DB_OilQitE_HS_CAN * pMsg);
int DB_OilQitE_HS_CAN_UpdateBytesFromSignals(DB_OilQitE_HS_CAN * pMsg);
int DB_OilQitE_HS_CAN_UpdateBytesFromRawSignals(DB_OilQitE_HS_CAN * pMsg);
#define DB_OilQitE_HS_CAN_OilDielectricConstant_E_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitE_HS_CAN_Index, 0, dPhysicalValue);
#define DB_OilQitE_HS_CAN_OilViscosity_E_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitE_HS_CAN_Index, 1, dPhysicalValue);
#define DB_OilQitE_HS_CAN_OilDensity_E_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitE_HS_CAN_Index, 2, dPhysicalValue);
#define DB_OilQitE_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_OilQitE_HS_CAN_Index, 0)
extern int DB_OilQitA1_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double OilViscosity_A1; /// Min: 0 Max: 1003.984375 Units: cp
    WORD OilViscosity_A1_raw;
    double OilDielectricConstant_A1; /// Min: 0 Max: 7.842 Units: 
    WORD OilDielectricConstant_A1_raw;
    double OilDensity_A1; /// Min: 0 Max: 1.961 Units: gm/cc
    WORD OilDensity_A1_raw;
} DB_OilQitA1_HS_CAN;

#define DB_OilQitA1_HS_CAN_SendType 0
#define DB_OilQitA1_HS_CAN_SendRate 30000

void DB_OilQitA1_HS_CAN_Init(DB_OilQitA1_HS_CAN * pMsg);
int DB_OilQitA1_HS_CAN_Transmit(DB_OilQitA1_HS_CAN * pMsg);
int DB_OilQitA1_HS_CAN_Transmit_raw(DB_OilQitA1_HS_CAN * pMsg);
int DB_OilQitA1_HS_CAN_UpdateBytesFromSignals(DB_OilQitA1_HS_CAN * pMsg);
int DB_OilQitA1_HS_CAN_UpdateBytesFromRawSignals(DB_OilQitA1_HS_CAN * pMsg);
#define DB_OilQitA1_HS_CAN_OilViscosity_A1_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitA1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_OilQitA1_HS_CAN_OilDielectricConstant_A1_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitA1_HS_CAN_Index, 1, dPhysicalValue);
#define DB_OilQitA1_HS_CAN_OilDensity_A1_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitA1_HS_CAN_Index, 2, dPhysicalValue);
#define DB_OilQitA1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_OilQitA1_HS_CAN_Index, 0)
extern int DB_OilQitA2_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double OilDensity_A2; /// Min: 0 Max: 1.961 Units: gm/cc
    WORD OilDensity_A2_raw;
    double OilViscosity_A2; /// Min: 0 Max: 1023.984375 Units: cp
    WORD OilViscosity_A2_raw;
    double OilDielectricConstant_A2; /// Min: 0 Max: 7.842 Units: 
    WORD OilDielectricConstant_A2_raw;
} DB_OilQitA2_HS_CAN;

#define DB_OilQitA2_HS_CAN_SendType 0
#define DB_OilQitA2_HS_CAN_SendRate 30000

void DB_OilQitA2_HS_CAN_Init(DB_OilQitA2_HS_CAN * pMsg);
int DB_OilQitA2_HS_CAN_Transmit(DB_OilQitA2_HS_CAN * pMsg);
int DB_OilQitA2_HS_CAN_Transmit_raw(DB_OilQitA2_HS_CAN * pMsg);
int DB_OilQitA2_HS_CAN_UpdateBytesFromSignals(DB_OilQitA2_HS_CAN * pMsg);
int DB_OilQitA2_HS_CAN_UpdateBytesFromRawSignals(DB_OilQitA2_HS_CAN * pMsg);
#define DB_OilQitA2_HS_CAN_OilDensity_A2_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitA2_HS_CAN_Index, 0, dPhysicalValue);
#define DB_OilQitA2_HS_CAN_OilViscosity_A2_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitA2_HS_CAN_Index, 1, dPhysicalValue);
#define DB_OilQitA2_HS_CAN_OilDielectricConstant_A2_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_OilQitA2_HS_CAN_Index, 2, dPhysicalValue);
#define DB_OilQitA2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_OilQitA2_HS_CAN_Index, 0)
extern int DB_VCU_1_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double RevGearSig; /// Min: 0 Max: 3 Units: 
    BYTE RevGearSig_raw;
    double ExhaustBrake; /// Min: 0 Max: 3 Units: 
    BYTE ExhaustBrake_raw;
} DB_VCU_1_HS_CAN;

#define DB_VCU_1_HS_CAN_SendType 0
#define DB_VCU_1_HS_CAN_SendRate 50
#pragma warning(disable : 4005)
#define DB_VCU_1_HS_CAN_$_RevGearSig_$$____ 0
#define DB_VCU_1_HS_CAN_$_RevGearSig_$$___ 1
#define DB_VCU_1_HS_CAN_$_RevGearSig_$$___ 2
#define DB_VCU_1_HS_CAN_$_RevGearSig_$$___ 3
#define DB_VCU_1_HS_CAN_$_ExhaustBrake_$$____ 0
#define DB_VCU_1_HS_CAN_$_ExhaustBrake_$$___ 1
#define DB_VCU_1_HS_CAN_$_ExhaustBrake_$$___ 2
#define DB_VCU_1_HS_CAN_$_ExhaustBrake_$$___ 3
#pragma warning(default : 4005)

void DB_VCU_1_HS_CAN_Init(DB_VCU_1_HS_CAN * pMsg);
int DB_VCU_1_HS_CAN_Transmit(DB_VCU_1_HS_CAN * pMsg);
int DB_VCU_1_HS_CAN_Transmit_raw(DB_VCU_1_HS_CAN * pMsg);
int DB_VCU_1_HS_CAN_UpdateBytesFromSignals(DB_VCU_1_HS_CAN * pMsg);
int DB_VCU_1_HS_CAN_UpdateBytesFromRawSignals(DB_VCU_1_HS_CAN * pMsg);
#define DB_VCU_1_HS_CAN_RevGearSig_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VCU_1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_VCU_1_HS_CAN_ExhaustBrake_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VCU_1_HS_CAN_Index, 1, dPhysicalValue);
#define DB_VCU_1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VCU_1_HS_CAN_Index, 0)
extern int DB_CCVS_EMS_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Status_of_parking_brake; /// Min: 0 Max: 3 Units: 
    BYTE Status_of_parking_brake_raw;
    double Brake_Switch; /// Min: 0 Max: 3 Units: 
    BYTE Brake_Switch_raw;
} DB_CCVS_EMS_HS_CAN;

#define DB_CCVS_EMS_HS_CAN_SendType 0
#define DB_CCVS_EMS_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define DB_CCVS_EMS_HS_CAN_$_Status_of_parking_brake_$$_not_actuated 0
#define DB_CCVS_EMS_HS_CAN_$_Status_of_parking_brake_$$_actuated 1
#define DB_CCVS_EMS_HS_CAN_$_Status_of_parking_brake_$$_error 2
#define DB_CCVS_EMS_HS_CAN_$_Status_of_parking_brake_$$_not_available 3
#define DB_CCVS_EMS_HS_CAN_$_Brake_Switch_$$_not_actuated 0
#define DB_CCVS_EMS_HS_CAN_$_Brake_Switch_$$_actuated 1
#define DB_CCVS_EMS_HS_CAN_$_Brake_Switch_$$_error 2
#define DB_CCVS_EMS_HS_CAN_$_Brake_Switch_$$_not_available 3
#pragma warning(default : 4005)

void DB_CCVS_EMS_HS_CAN_Init(DB_CCVS_EMS_HS_CAN * pMsg);
int DB_CCVS_EMS_HS_CAN_Transmit(DB_CCVS_EMS_HS_CAN * pMsg);
int DB_CCVS_EMS_HS_CAN_Transmit_raw(DB_CCVS_EMS_HS_CAN * pMsg);
int DB_CCVS_EMS_HS_CAN_UpdateBytesFromSignals(DB_CCVS_EMS_HS_CAN * pMsg);
int DB_CCVS_EMS_HS_CAN_UpdateBytesFromRawSignals(DB_CCVS_EMS_HS_CAN * pMsg);
#define DB_CCVS_EMS_HS_CAN_Status_of_parking_brake_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_CCVS_EMS_HS_CAN_Index, 0, dPhysicalValue);
#define DB_CCVS_EMS_HS_CAN_Brake_Switch_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_CCVS_EMS_HS_CAN_Index, 1, dPhysicalValue);
#define DB_CCVS_EMS_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_CCVS_EMS_HS_CAN_Index, 0)
extern int DB_VDC1_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double VDC_BrakeLightRequest; /// Min: 0 Max: 3 Units: 
    BYTE VDC_BrakeLightRequest_raw;
} DB_VDC1_HS_CAN;

#define DB_VDC1_HS_CAN_SendType 0
#define DB_VDC1_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define DB_VDC1_HS_CAN_$_VDC_BrakeLightRequest_$$_turn_brake_light_not_on 0
#define DB_VDC1_HS_CAN_$_VDC_BrakeLightRequest_$$_turn_brake_light_on 1
#define DB_VDC1_HS_CAN_$_VDC_BrakeLightRequest_$$_Reserved 2
#define DB_VDC1_HS_CAN_$_VDC_BrakeLightRequest_$$_Dont_t_care_Take_no_action 3
#pragma warning(default : 4005)

void DB_VDC1_HS_CAN_Init(DB_VDC1_HS_CAN * pMsg);
int DB_VDC1_HS_CAN_Transmit(DB_VDC1_HS_CAN * pMsg);
int DB_VDC1_HS_CAN_Transmit_raw(DB_VDC1_HS_CAN * pMsg);
int DB_VDC1_HS_CAN_UpdateBytesFromSignals(DB_VDC1_HS_CAN * pMsg);
int DB_VDC1_HS_CAN_UpdateBytesFromRawSignals(DB_VDC1_HS_CAN * pMsg);
#define DB_VDC1_HS_CAN_VDC_BrakeLightRequest_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VDC1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_VDC1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VDC1_HS_CAN_Index, 0)
extern int DB_ERC1_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double RetarderEnable_BrakeAssistSW; /// Min: 0 Max: 3 Units: 
    BYTE RetarderEnable_BrakeAssistSW_raw;
} DB_ERC1_HS_CAN;

#define DB_ERC1_HS_CAN_SendType 0
#define DB_ERC1_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define DB_ERC1_HS_CAN_$_RetarderEnable_BrakeAssistSW_$$___________ 0
#define DB_ERC1_HS_CAN_$_RetarderEnable_BrakeAssistSW_$$___________ 1
#define DB_ERC1_HS_CAN_$_RetarderEnable_BrakeAssistSW_$$___ 2
#define DB_ERC1_HS_CAN_$_RetarderEnable_BrakeAssistSW_$$___ 3
#pragma warning(default : 4005)

void DB_ERC1_HS_CAN_Init(DB_ERC1_HS_CAN * pMsg);
int DB_ERC1_HS_CAN_Transmit(DB_ERC1_HS_CAN * pMsg);
int DB_ERC1_HS_CAN_Transmit_raw(DB_ERC1_HS_CAN * pMsg);
int DB_ERC1_HS_CAN_UpdateBytesFromSignals(DB_ERC1_HS_CAN * pMsg);
int DB_ERC1_HS_CAN_UpdateBytesFromRawSignals(DB_ERC1_HS_CAN * pMsg);
#define DB_ERC1_HS_CAN_RetarderEnable_BrakeAssistSW_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_ERC1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_ERC1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_ERC1_HS_CAN_Index, 0)
extern int DB_ETC2_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TransmissionCurrentGear; /// Min: -125 Max: 125 Units: 
    BYTE TransmissionCurrentGear_raw;
    double TransmissionSelectedGear; /// Min: -125 Max: 125 Units: 
    BYTE TransmissionSelectedGear_raw;
} DB_ETC2_HS_CAN;

#define DB_ETC2_HS_CAN_SendType 0
#define DB_ETC2_HS_CAN_SendRate 100

void DB_ETC2_HS_CAN_Init(DB_ETC2_HS_CAN * pMsg);
int DB_ETC2_HS_CAN_Transmit(DB_ETC2_HS_CAN * pMsg);
int DB_ETC2_HS_CAN_Transmit_raw(DB_ETC2_HS_CAN * pMsg);
int DB_ETC2_HS_CAN_UpdateBytesFromSignals(DB_ETC2_HS_CAN * pMsg);
int DB_ETC2_HS_CAN_UpdateBytesFromRawSignals(DB_ETC2_HS_CAN * pMsg);
#define DB_ETC2_HS_CAN_TransmissionCurrentGear_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_ETC2_HS_CAN_Index, 0, dPhysicalValue);
#define DB_ETC2_HS_CAN_TransmissionSelectedGear_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_ETC2_HS_CAN_Index, 1, dPhysicalValue);
#define DB_ETC2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_ETC2_HS_CAN_Index, 0)
extern int DB_EEC1_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double EngineSpeed; /// Min: 0 Max: 8191.875 Units: rpm
    WORD EngineSpeed_raw;
} DB_EEC1_HS_CAN;

#define DB_EEC1_HS_CAN_SendType 0
#define DB_EEC1_HS_CAN_SendRate 10

void DB_EEC1_HS_CAN_Init(DB_EEC1_HS_CAN * pMsg);
int DB_EEC1_HS_CAN_Transmit(DB_EEC1_HS_CAN * pMsg);
int DB_EEC1_HS_CAN_Transmit_raw(DB_EEC1_HS_CAN * pMsg);
int DB_EEC1_HS_CAN_UpdateBytesFromSignals(DB_EEC1_HS_CAN * pMsg);
int DB_EEC1_HS_CAN_UpdateBytesFromRawSignals(DB_EEC1_HS_CAN * pMsg);
#define DB_EEC1_HS_CAN_EngineSpeed_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_EEC1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_EEC1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_EEC1_HS_CAN_Index, 0)
extern int DB_EBC1_BCM_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double ABS_Trailer_Warning_Lamp_State; /// Min: 0 Max: 3 Units: 
    BYTE ABS_Trailer_Warning_Lamp_State_raw;
} DB_EBC1_BCM_HS_CAN;

#define DB_EBC1_BCM_HS_CAN_SendType 0
#define DB_EBC1_BCM_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define DB_EBC1_BCM_HS_CAN_$_ABS_Trailer_Warning_Lamp_State_$$_Trailer_warning_function_passive 0
#define DB_EBC1_BCM_HS_CAN_$_ABS_Trailer_Warning_Lamp_State_$$_Trailer_warning_function_active 1
#define DB_EBC1_BCM_HS_CAN_$_ABS_Trailer_Warning_Lamp_State_$$_not_supported 2
#define DB_EBC1_BCM_HS_CAN_$_ABS_Trailer_Warning_Lamp_State_$$_function_not_supported 3
#pragma warning(default : 4005)

void DB_EBC1_BCM_HS_CAN_Init(DB_EBC1_BCM_HS_CAN * pMsg);
int DB_EBC1_BCM_HS_CAN_Transmit(DB_EBC1_BCM_HS_CAN * pMsg);
int DB_EBC1_BCM_HS_CAN_Transmit_raw(DB_EBC1_BCM_HS_CAN * pMsg);
int DB_EBC1_BCM_HS_CAN_UpdateBytesFromSignals(DB_EBC1_BCM_HS_CAN * pMsg);
int DB_EBC1_BCM_HS_CAN_UpdateBytesFromRawSignals(DB_EBC1_BCM_HS_CAN * pMsg);
#define DB_EBC1_BCM_HS_CAN_ABS_Trailer_Warning_Lamp_State_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_EBC1_BCM_HS_CAN_Index, 0, dPhysicalValue);
#define DB_EBC1_BCM_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_EBC1_BCM_HS_CAN_Index, 0)
extern int DB_EBC1_ABS_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double ABS_active; /// Min: 0 Max: 3 Units: 
    BYTE ABS_active_raw;
} DB_EBC1_ABS_HS_CAN;

#define DB_EBC1_ABS_HS_CAN_SendType 0
#define DB_EBC1_ABS_HS_CAN_SendRate 100
#pragma warning(disable : 4005)
#define DB_EBC1_ABS_HS_CAN_$_ABS_active_$$_ABS_pssive_but_installed 0
#define DB_EBC1_ABS_HS_CAN_$_ABS_active_$$_ABS_active 1
#define DB_EBC1_ABS_HS_CAN_$_ABS_active_$$_Not_Supported 2
#define DB_EBC1_ABS_HS_CAN_$_ABS_active_$$_Not_available 3
#pragma warning(default : 4005)

void DB_EBC1_ABS_HS_CAN_Init(DB_EBC1_ABS_HS_CAN * pMsg);
int DB_EBC1_ABS_HS_CAN_Transmit(DB_EBC1_ABS_HS_CAN * pMsg);
int DB_EBC1_ABS_HS_CAN_Transmit_raw(DB_EBC1_ABS_HS_CAN * pMsg);
int DB_EBC1_ABS_HS_CAN_UpdateBytesFromSignals(DB_EBC1_ABS_HS_CAN * pMsg);
int DB_EBC1_ABS_HS_CAN_UpdateBytesFromRawSignals(DB_EBC1_ABS_HS_CAN * pMsg);
#define DB_EBC1_ABS_HS_CAN_ABS_active_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_EBC1_ABS_HS_CAN_Index, 0, dPhysicalValue);
#define DB_EBC1_ABS_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_EBC1_ABS_HS_CAN_Index, 0)
extern int DB_NM_TESTER_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AC_NMDataField; /// Min: 0 Max: 281474976710655 Units: 
    uint64 AC_NMDataField_raw;
    double AC_NMSleepAck; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMSleepAck_raw;
    double AC_NMSleepInd; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMSleepInd_raw;
    double AC_NMLimphome; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMLimphome_raw;
    double AC_NMRing; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMRing_raw;
    double AC_NMAlive; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMAlive_raw;
    double AC_NMDestAddress; /// Min: 0 Max: 255 Units: 
    BYTE AC_NMDestAddress_raw;
} DB_NM_TESTER_HS_CAN;

#define DB_NM_TESTER_HS_CAN_SendType 0
#define DB_NM_TESTER_HS_CAN_SendRate 0
#pragma warning(disable : 4005)
#define DB_NM_TESTER_HS_CAN_$_AC_NMSleepAck_$$_FALSE 0
#define DB_NM_TESTER_HS_CAN_$_AC_NMSleepAck_$$_TRUE 1
#define DB_NM_TESTER_HS_CAN_$_AC_NMSleepInd_$$_FALSE 0
#define DB_NM_TESTER_HS_CAN_$_AC_NMSleepInd_$$_TRUE 1
#define DB_NM_TESTER_HS_CAN_$_AC_NMLimphome_$$_FALSE 0
#define DB_NM_TESTER_HS_CAN_$_AC_NMLimphome_$$_TRUE 1
#define DB_NM_TESTER_HS_CAN_$_AC_NMRing_$$_FALSE 0
#define DB_NM_TESTER_HS_CAN_$_AC_NMRing_$$_TRUE 1
#define DB_NM_TESTER_HS_CAN_$_AC_NMAlive_$$_FALSE 0
#define DB_NM_TESTER_HS_CAN_$_AC_NMAlive_$$_TRUE 1
#define DB_NM_TESTER_HS_CAN_$_AC_NMDestAddress_$$_IPC 23
#define DB_NM_TESTER_HS_CAN_$_AC_NMDestAddress_$$_BCM 33
#define DB_NM_TESTER_HS_CAN_$_AC_NMDestAddress_$$_GW 37
#pragma warning(default : 4005)

void DB_NM_TESTER_HS_CAN_Init(DB_NM_TESTER_HS_CAN * pMsg);
int DB_NM_TESTER_HS_CAN_Transmit(DB_NM_TESTER_HS_CAN * pMsg);
int DB_NM_TESTER_HS_CAN_Transmit_raw(DB_NM_TESTER_HS_CAN * pMsg);
int DB_NM_TESTER_HS_CAN_UpdateBytesFromSignals(DB_NM_TESTER_HS_CAN * pMsg);
int DB_NM_TESTER_HS_CAN_UpdateBytesFromRawSignals(DB_NM_TESTER_HS_CAN * pMsg);
#define DB_NM_TESTER_HS_CAN_AC_NMDataField_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_TESTER_HS_CAN_AC_NMSleepAck_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_TESTER_HS_CAN_AC_NMSleepInd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_TESTER_HS_CAN_AC_NMLimphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_TESTER_HS_CAN_AC_NMRing_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_TESTER_HS_CAN_AC_NMAlive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_TESTER_HS_CAN_AC_NMDestAddress_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, 6, dPhysicalValue);
#define DB_NM_TESTER_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_TESTER_HS_CAN_Index, 0)
extern int DB_NM_AC_MMI_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AC_NMDataField; /// Min: 0 Max: 281474976710655 Units: 
    uint64 AC_NMDataField_raw;
    double AC_NMSleepAck; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMSleepAck_raw;
    double AC_NMSleepInd; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMSleepInd_raw;
    double AC_NMLimphome; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMLimphome_raw;
    double AC_NMRing; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMRing_raw;
    double AC_NMAlive; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMAlive_raw;
    double AC_NMDestAddress; /// Min: 0 Max: 255 Units: 
    BYTE AC_NMDestAddress_raw;
} DB_NM_AC_MMI_HS_CAN;

#define DB_NM_AC_MMI_HS_CAN_SendType 0
#define DB_NM_AC_MMI_HS_CAN_SendRate 0
#pragma warning(disable : 4005)
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMSleepAck_$$_FALSE 0
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMSleepAck_$$_TRUE 1
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMSleepInd_$$_FALSE 0
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMSleepInd_$$_TRUE 1
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMLimphome_$$_FALSE 0
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMLimphome_$$_TRUE 1
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMRing_$$_FALSE 0
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMRing_$$_TRUE 1
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMAlive_$$_FALSE 0
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMAlive_$$_TRUE 1
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMDestAddress_$$_IPC 23
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMDestAddress_$$_BCM 33
#define DB_NM_AC_MMI_HS_CAN_$_AC_NMDestAddress_$$_GW 37
#pragma warning(default : 4005)

void DB_NM_AC_MMI_HS_CAN_Init(DB_NM_AC_MMI_HS_CAN * pMsg);
int DB_NM_AC_MMI_HS_CAN_Transmit(DB_NM_AC_MMI_HS_CAN * pMsg);
int DB_NM_AC_MMI_HS_CAN_Transmit_raw(DB_NM_AC_MMI_HS_CAN * pMsg);
int DB_NM_AC_MMI_HS_CAN_UpdateBytesFromSignals(DB_NM_AC_MMI_HS_CAN * pMsg);
int DB_NM_AC_MMI_HS_CAN_UpdateBytesFromRawSignals(DB_NM_AC_MMI_HS_CAN * pMsg);
#define DB_NM_AC_MMI_HS_CAN_AC_NMDataField_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_AC_MMI_HS_CAN_AC_NMSleepAck_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_AC_MMI_HS_CAN_AC_NMSleepInd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_AC_MMI_HS_CAN_AC_NMLimphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_AC_MMI_HS_CAN_AC_NMRing_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_AC_MMI_HS_CAN_AC_NMAlive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_AC_MMI_HS_CAN_AC_NMDestAddress_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, 6, dPhysicalValue);
#define DB_NM_AC_MMI_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_AC_MMI_HS_CAN_Index, 0)
extern int DB_NM_MMI_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AC_NMDataField; /// Min: 0 Max: 281474976710655 Units: 
    uint64 AC_NMDataField_raw;
    double AC_NMSleepAck; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMSleepAck_raw;
    double AC_NMSleepInd; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMSleepInd_raw;
    double AC_NMLimphome; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMLimphome_raw;
    double AC_NMRing; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMRing_raw;
    double AC_NMAlive; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMAlive_raw;
    double AC_NMDestAddress; /// Min: 0 Max: 255 Units: 
    BYTE AC_NMDestAddress_raw;
} DB_NM_MMI_HS_CAN;

#define DB_NM_MMI_HS_CAN_SendType 0
#define DB_NM_MMI_HS_CAN_SendRate 0
#pragma warning(disable : 4005)
#define DB_NM_MMI_HS_CAN_$_AC_NMSleepAck_$$_FALSE 0
#define DB_NM_MMI_HS_CAN_$_AC_NMSleepAck_$$_TRUE 1
#define DB_NM_MMI_HS_CAN_$_AC_NMSleepInd_$$_FALSE 0
#define DB_NM_MMI_HS_CAN_$_AC_NMSleepInd_$$_TRUE 1
#define DB_NM_MMI_HS_CAN_$_AC_NMLimphome_$$_FALSE 0
#define DB_NM_MMI_HS_CAN_$_AC_NMLimphome_$$_TRUE 1
#define DB_NM_MMI_HS_CAN_$_AC_NMRing_$$_FALSE 0
#define DB_NM_MMI_HS_CAN_$_AC_NMRing_$$_TRUE 1
#define DB_NM_MMI_HS_CAN_$_AC_NMAlive_$$_FALSE 0
#define DB_NM_MMI_HS_CAN_$_AC_NMAlive_$$_TRUE 1
#define DB_NM_MMI_HS_CAN_$_AC_NMDestAddress_$$_IPC 23
#define DB_NM_MMI_HS_CAN_$_AC_NMDestAddress_$$_BCM 33
#define DB_NM_MMI_HS_CAN_$_AC_NMDestAddress_$$_GW 37
#pragma warning(default : 4005)

void DB_NM_MMI_HS_CAN_Init(DB_NM_MMI_HS_CAN * pMsg);
int DB_NM_MMI_HS_CAN_Transmit(DB_NM_MMI_HS_CAN * pMsg);
int DB_NM_MMI_HS_CAN_Transmit_raw(DB_NM_MMI_HS_CAN * pMsg);
int DB_NM_MMI_HS_CAN_UpdateBytesFromSignals(DB_NM_MMI_HS_CAN * pMsg);
int DB_NM_MMI_HS_CAN_UpdateBytesFromRawSignals(DB_NM_MMI_HS_CAN * pMsg);
#define DB_NM_MMI_HS_CAN_AC_NMDataField_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_AC_NMSleepAck_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_AC_NMSleepInd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_AC_NMLimphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_AC_NMRing_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_AC_NMAlive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_AC_NMDestAddress_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, 6, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_MMI_HS_CAN_Index, 0)
extern int DB_NM_RCM_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double RCM_NMDataFiels; /// Min: 0 Max: 281474976710655 Units: 
    uint64 RCM_NMDataFiels_raw;
    double RCM_NMSleepAck; /// Min: 0 Max: 1 Units: 
    BYTE RCM_NMSleepAck_raw;
    double RCM_NMSleepInd; /// Min: 0 Max: 1 Units: 
    BYTE RCM_NMSleepInd_raw;
    double RCM_NMLimphome; /// Min: 0 Max: 1 Units: 
    BYTE RCM_NMLimphome_raw;
    double RCM_NMRing; /// Min: 0 Max: 1 Units: 
    BYTE RCM_NMRing_raw;
    double RCM_NMAlive; /// Min: 0 Max: 1 Units: 
    BYTE RCM_NMAlive_raw;
    double RCM_NMDestAddress; /// Min: 0 Max: 255 Units: 
    BYTE RCM_NMDestAddress_raw;
} DB_NM_RCM_HS_CAN;

#define DB_NM_RCM_HS_CAN_SendType 0
#define DB_NM_RCM_HS_CAN_SendRate 0
#pragma warning(disable : 4005)
#define DB_NM_RCM_HS_CAN_$_RCM_NMSleepAck_$$_FALSE 0
#define DB_NM_RCM_HS_CAN_$_RCM_NMSleepAck_$$_TRUE 1
#define DB_NM_RCM_HS_CAN_$_RCM_NMSleepInd_$$_FALSE 0
#define DB_NM_RCM_HS_CAN_$_RCM_NMSleepInd_$$_TRUE 1
#define DB_NM_RCM_HS_CAN_$_RCM_NMLimphome_$$_FALSE 0
#define DB_NM_RCM_HS_CAN_$_RCM_NMLimphome_$$_TRUE 1
#define DB_NM_RCM_HS_CAN_$_RCM_NMRing_$$_FALSE 0
#define DB_NM_RCM_HS_CAN_$_RCM_NMRing_$$_TRUE 1
#define DB_NM_RCM_HS_CAN_$_RCM_NMAlive_$$_FALSE 0
#define DB_NM_RCM_HS_CAN_$_RCM_NMAlive_$$_TRUE 1
#define DB_NM_RCM_HS_CAN_$_RCM_NMDestAddress_$$_IPC 23
#define DB_NM_RCM_HS_CAN_$_RCM_NMDestAddress_$$_BCM 33
#define DB_NM_RCM_HS_CAN_$_RCM_NMDestAddress_$$_GW 37
#pragma warning(default : 4005)

void DB_NM_RCM_HS_CAN_Init(DB_NM_RCM_HS_CAN * pMsg);
int DB_NM_RCM_HS_CAN_Transmit(DB_NM_RCM_HS_CAN * pMsg);
int DB_NM_RCM_HS_CAN_Transmit_raw(DB_NM_RCM_HS_CAN * pMsg);
int DB_NM_RCM_HS_CAN_UpdateBytesFromSignals(DB_NM_RCM_HS_CAN * pMsg);
int DB_NM_RCM_HS_CAN_UpdateBytesFromRawSignals(DB_NM_RCM_HS_CAN * pMsg);
#define DB_NM_RCM_HS_CAN_RCM_NMDataFiels_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_RCM_HS_CAN_RCM_NMSleepAck_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_RCM_HS_CAN_RCM_NMSleepInd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_RCM_HS_CAN_RCM_NMLimphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_RCM_HS_CAN_RCM_NMRing_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_RCM_HS_CAN_RCM_NMAlive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_RCM_HS_CAN_RCM_NMDestAddress_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, 6, dPhysicalValue);
#define DB_NM_RCM_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_RCM_HS_CAN_Index, 0)
extern int DB_NM_IPC_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double IPC_NMDataField; /// Min: 0 Max: 281474976710655 Units: 
    uint64 IPC_NMDataField_raw;
    double IPC_NMSleepAck; /// Min: 0 Max: 1 Units: 
    BYTE IPC_NMSleepAck_raw;
    double IPC_NMSleepInd; /// Min: 0 Max: 1 Units: 
    BYTE IPC_NMSleepInd_raw;
    double IPC_NMLimphome; /// Min: 0 Max: 1 Units: 
    BYTE IPC_NMLimphome_raw;
    double IPC_NMRing; /// Min: 0 Max: 1 Units: 
    BYTE IPC_NMRing_raw;
    double IPC_NMAlive; /// Min: 0 Max: 1 Units: 
    BYTE IPC_NMAlive_raw;
    double IPC_NMDestAddress; /// Min: 0 Max: 255 Units: 
    BYTE IPC_NMDestAddress_raw;
} DB_NM_IPC_HS_CAN;

#define DB_NM_IPC_HS_CAN_SendType 0
#define DB_NM_IPC_HS_CAN_SendRate 0
#pragma warning(disable : 4005)
#define DB_NM_IPC_HS_CAN_$_IPC_NMSleepAck_$$_FALSE 0
#define DB_NM_IPC_HS_CAN_$_IPC_NMSleepAck_$$_TRUE 1
#define DB_NM_IPC_HS_CAN_$_IPC_NMSleepInd_$$_FALSE 0
#define DB_NM_IPC_HS_CAN_$_IPC_NMSleepInd_$$_TRUE 1
#define DB_NM_IPC_HS_CAN_$_IPC_NMLimphome_$$_FALSE 0
#define DB_NM_IPC_HS_CAN_$_IPC_NMLimphome_$$_TRUE 1
#define DB_NM_IPC_HS_CAN_$_IPC_NMRing_$$_FALSE 0
#define DB_NM_IPC_HS_CAN_$_IPC_NMRing_$$_TRUE 1
#define DB_NM_IPC_HS_CAN_$_IPC_NMAlive_$$_FALSE 0
#define DB_NM_IPC_HS_CAN_$_IPC_NMAlive_$$_TRUE 1
#define DB_NM_IPC_HS_CAN_$_IPC_NMDestAddress_$$_IPC 23
#define DB_NM_IPC_HS_CAN_$_IPC_NMDestAddress_$$_BCM 33
#define DB_NM_IPC_HS_CAN_$_IPC_NMDestAddress_$$_GW 37
#pragma warning(default : 4005)

void DB_NM_IPC_HS_CAN_Init(DB_NM_IPC_HS_CAN * pMsg);
int DB_NM_IPC_HS_CAN_Transmit(DB_NM_IPC_HS_CAN * pMsg);
int DB_NM_IPC_HS_CAN_Transmit_raw(DB_NM_IPC_HS_CAN * pMsg);
int DB_NM_IPC_HS_CAN_UpdateBytesFromSignals(DB_NM_IPC_HS_CAN * pMsg);
int DB_NM_IPC_HS_CAN_UpdateBytesFromRawSignals(DB_NM_IPC_HS_CAN * pMsg);
#define DB_NM_IPC_HS_CAN_IPC_NMDataField_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_IPC_HS_CAN_IPC_NMSleepAck_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_IPC_HS_CAN_IPC_NMSleepInd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_IPC_HS_CAN_IPC_NMLimphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_IPC_HS_CAN_IPC_NMRing_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_IPC_HS_CAN_IPC_NMAlive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_IPC_HS_CAN_IPC_NMDestAddress_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, 6, dPhysicalValue);
#define DB_NM_IPC_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_IPC_HS_CAN_Index, 0)
extern int DB_NM_AC_HS_CAN_db88_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double AC_NMDataField; /// Min: 0 Max: 281474976710655 Units: 
    uint64 AC_NMDataField_raw;
    double AC_NMSleepAck; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMSleepAck_raw;
    double AC_NMSleepInd; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMSleepInd_raw;
    double AC_NMLimphome; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMLimphome_raw;
    double AC_NMRing; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMRing_raw;
    double AC_NMAlive; /// Min: 0 Max: 1 Units: 
    BYTE AC_NMAlive_raw;
    double AC_NMDestAddress; /// Min: 0 Max: 255 Units: 
    BYTE AC_NMDestAddress_raw;
} DB_NM_AC_HS_CAN_db88;

#define DB_NM_AC_HS_CAN_db88_SendType 0
#define DB_NM_AC_HS_CAN_db88_SendRate 0
#pragma warning(disable : 4005)
#define DB_NM_AC_HS_CAN_db88_$_AC_NMSleepAck_$$_FALSE 0
#define DB_NM_AC_HS_CAN_db88_$_AC_NMSleepAck_$$_TRUE 1
#define DB_NM_AC_HS_CAN_db88_$_AC_NMSleepInd_$$_FALSE 0
#define DB_NM_AC_HS_CAN_db88_$_AC_NMSleepInd_$$_TRUE 1
#define DB_NM_AC_HS_CAN_db88_$_AC_NMLimphome_$$_FALSE 0
#define DB_NM_AC_HS_CAN_db88_$_AC_NMLimphome_$$_TRUE 1
#define DB_NM_AC_HS_CAN_db88_$_AC_NMRing_$$_FALSE 0
#define DB_NM_AC_HS_CAN_db88_$_AC_NMRing_$$_TRUE 1
#define DB_NM_AC_HS_CAN_db88_$_AC_NMAlive_$$_FALSE 0
#define DB_NM_AC_HS_CAN_db88_$_AC_NMAlive_$$_TRUE 1
#define DB_NM_AC_HS_CAN_db88_$_AC_NMDestAddress_$$_IPC 23
#define DB_NM_AC_HS_CAN_db88_$_AC_NMDestAddress_$$_BCM 33
#define DB_NM_AC_HS_CAN_db88_$_AC_NMDestAddress_$$_GW 37
#pragma warning(default : 4005)

void DB_NM_AC_HS_CAN_db88_Init(DB_NM_AC_HS_CAN_db88 * pMsg);
int DB_NM_AC_HS_CAN_db88_Transmit(DB_NM_AC_HS_CAN_db88 * pMsg);
int DB_NM_AC_HS_CAN_db88_Transmit_raw(DB_NM_AC_HS_CAN_db88 * pMsg);
int DB_NM_AC_HS_CAN_db88_UpdateBytesFromSignals(DB_NM_AC_HS_CAN_db88 * pMsg);
int DB_NM_AC_HS_CAN_db88_UpdateBytesFromRawSignals(DB_NM_AC_HS_CAN_db88 * pMsg);
#define DB_NM_AC_HS_CAN_db88_AC_NMDataField_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, 0, dPhysicalValue);
#define DB_NM_AC_HS_CAN_db88_AC_NMSleepAck_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, 1, dPhysicalValue);
#define DB_NM_AC_HS_CAN_db88_AC_NMSleepInd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, 2, dPhysicalValue);
#define DB_NM_AC_HS_CAN_db88_AC_NMLimphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, 3, dPhysicalValue);
#define DB_NM_AC_HS_CAN_db88_AC_NMRing_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, 4, dPhysicalValue);
#define DB_NM_AC_HS_CAN_db88_AC_NMAlive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, 5, dPhysicalValue);
#define DB_NM_AC_HS_CAN_db88_AC_NMDestAddress_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, 6, dPhysicalValue);
#define DB_NM_AC_HS_CAN_db88_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_AC_HS_CAN_db88_Index, 0)
extern int DB_Tester_HS_CAN_Index;
typedef struct {
    GenericLongMessage MessageData; /// Diagnostic Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Resv6; /// Min: 0 Max: 255 Units: 
    BYTE Resv6_raw;
    double Resv5; /// Min: 0 Max: 255 Units: 
    BYTE Resv5_raw;
    double Resv4; /// Min: 0 Max: 255 Units: 
    BYTE Resv4_raw;
    double Resv3; /// Min: 0 Max: 255 Units: 
    BYTE Resv3_raw;
    double Resv2; /// Min: 0 Max: 255 Units: 
    BYTE Resv2_raw;
    double FD; /// Min: 0 Max: 255 Units: 
    BYTE FD_raw;
    double Ctrl; /// Min: 0 Max: 255 Units: 
    BYTE Ctrl_raw;
    double Resv1; /// Min: 0 Max: 255 Units: 
    BYTE Resv1_raw;
} DB_Tester_HS_CAN;

#pragma warning(disable : 4005)
#define DB_Tester_HS_CAN_$_Resv6_$$_____Ring__ 255
#define DB_Tester_HS_CAN_$_Resv5_$$_____Ring__ 255
#define DB_Tester_HS_CAN_$_Resv4_$$_____Ring__ 255
#define DB_Tester_HS_CAN_$_Resv3_$$_____Ring__ 255
#define DB_Tester_HS_CAN_$_Resv2_$$_____Ring__ 255
#define DB_Tester_HS_CAN_$_Ctrl_$$_____Ring__ 255
#define DB_Tester_HS_CAN_$_Resv1_$$_____Ring__ 255
#pragma warning(default : 4005)

void DB_Tester_HS_CAN_Init(DB_Tester_HS_CAN * pMsg);
int DB_Tester_HS_CAN_Transmit(DB_Tester_HS_CAN * pMsg);
int DB_Tester_HS_CAN_Transmit_raw(DB_Tester_HS_CAN * pMsg);
int DB_Tester_HS_CAN_UpdateBytesFromSignals(DB_Tester_HS_CAN * pMsg);
int DB_Tester_HS_CAN_UpdateBytesFromRawSignals(DB_Tester_HS_CAN * pMsg);
#define DB_Tester_HS_CAN_Resv6_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Tester_HS_CAN_Index, 0, dPhysicalValue);
#define DB_Tester_HS_CAN_Resv5_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Tester_HS_CAN_Index, 1, dPhysicalValue);
#define DB_Tester_HS_CAN_Resv4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Tester_HS_CAN_Index, 2, dPhysicalValue);
#define DB_Tester_HS_CAN_Resv3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Tester_HS_CAN_Index, 3, dPhysicalValue);
#define DB_Tester_HS_CAN_Resv2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Tester_HS_CAN_Index, 4, dPhysicalValue);
#define DB_Tester_HS_CAN_FD_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Tester_HS_CAN_Index, 5, dPhysicalValue);
#define DB_Tester_HS_CAN_Ctrl_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Tester_HS_CAN_Index, 6, dPhysicalValue);
#define DB_Tester_HS_CAN_Resv1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_Tester_HS_CAN_Index, 7, dPhysicalValue);
#define DB_Tester_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_Tester_HS_CAN_Index, 0)
extern int DB_NM_EVM_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double EVM_NM_Sleep_Ack; /// Min: 0 Max: 1 Units: 
    BYTE EVM_NM_Sleep_Ack_raw;
    double EVM_NM_Sleep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE EVM_NM_Sleep_Ind_raw;
    double EVM_NM_Limphome; /// Min: 0 Max: 1 Units: 
    BYTE EVM_NM_Limphome_raw;
    double EVM_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE EVM_NM_Ring_raw;
    double EVM_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE EVM_NM_Alive_raw;
    double EVM_NM_DA; /// Min: 0 Max: 255 Units: 
    BYTE EVM_NM_DA_raw;
} DB_NM_EVM_HS_CAN;

#pragma warning(disable : 4005)
#define DB_NM_EVM_HS_CAN_$_EVM_NM_Sleep_Ack_$$_FALSE 0
#define DB_NM_EVM_HS_CAN_$_EVM_NM_Sleep_Ack_$$_TRUE 1
#define DB_NM_EVM_HS_CAN_$_EVM_NM_Sleep_Ind_$$_FALSE 0
#define DB_NM_EVM_HS_CAN_$_EVM_NM_Sleep_Ind_$$_TRUE 1
#define DB_NM_EVM_HS_CAN_$_EVM_NM_Limphome_$$_FALSE 0
#define DB_NM_EVM_HS_CAN_$_EVM_NM_Limphome_$$_TRUE 1
#define DB_NM_EVM_HS_CAN_$_EVM_NM_Ring_$$_FALSE 0
#define DB_NM_EVM_HS_CAN_$_EVM_NM_Ring_$$_TRUE 1
#define DB_NM_EVM_HS_CAN_$_EVM_NM_Alive_$$_FALSE 0
#define DB_NM_EVM_HS_CAN_$_EVM_NM_Alive_$$_TRUE 1
#pragma warning(default : 4005)

void DB_NM_EVM_HS_CAN_Init(DB_NM_EVM_HS_CAN * pMsg);
int DB_NM_EVM_HS_CAN_Transmit(DB_NM_EVM_HS_CAN * pMsg);
int DB_NM_EVM_HS_CAN_Transmit_raw(DB_NM_EVM_HS_CAN * pMsg);
int DB_NM_EVM_HS_CAN_UpdateBytesFromSignals(DB_NM_EVM_HS_CAN * pMsg);
int DB_NM_EVM_HS_CAN_UpdateBytesFromRawSignals(DB_NM_EVM_HS_CAN * pMsg);
#define DB_NM_EVM_HS_CAN_EVM_NM_Sleep_Ack_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_EVM_HS_CAN_EVM_NM_Sleep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_EVM_HS_CAN_EVM_NM_Limphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_EVM_HS_CAN_EVM_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_EVM_HS_CAN_EVM_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_EVM_HS_CAN_EVM_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_EVM_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_EVM_HS_CAN_Index, 0)
extern int DB_DM1_EVM_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double SPN_Mode; /// Min: 0 Max: 1 Units: 
    BYTE SPN_Mode_raw;
    double OccuranceCount; /// Min: 0 Max: 126 Units: 
    BYTE OccuranceCount_raw;
    double SPN_HighBit; /// Min: 0 Max: 7 Units: 
    BYTE SPN_HighBit_raw;
    double FMI; /// Min: 0 Max: 31 Units: 
    BYTE FMI_raw;
    double SPN_Num; /// Min: 0 Max: 65535 Units: 
    WORD SPN_Num_raw;
    double MalfunctionIndicatorLamp; /// Min: 0 Max: 3 Units: 
    BYTE MalfunctionIndicatorLamp_raw;
    double RedStopLamp; /// Min: 0 Max: 3 Units: 
    BYTE RedStopLamp_raw;
    double AmberWarningLamp; /// Min: 0 Max: 3 Units: 
    BYTE AmberWarningLamp_raw;
    double ProtectLamp; /// Min: 0 Max: 3 Units: 
    BYTE ProtectLamp_raw;
} DB_DM1_EVM_HS_CAN;

#define DB_DM1_EVM_HS_CAN_SendType 1
#define DB_DM1_EVM_HS_CAN_SendRate 1000
#pragma warning(disable : 4005)
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN___ 0
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN___ 1
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN___ 2
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN___ 3
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN___ 4
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN___ 5
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN___ 6
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN___ 7
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN____ 8
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN____ 9
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN____ 10
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN____ 11
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN____ 12
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN____ 13
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN____ 14
#define DB_DM1_EVM_HS_CAN_$_SPN_Num_$$_SPN____ 15
#define DB_DM1_EVM_HS_CAN_$_MalfunctionIndicatorLamp_$$____ 0
#define DB_DM1_EVM_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 1
#define DB_DM1_EVM_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 2
#define DB_DM1_EVM_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 3
#define DB_DM1_EVM_HS_CAN_$_RedStopLamp_$$____ 0
#define DB_DM1_EVM_HS_CAN_$_RedStopLamp_$$___ 1
#define DB_DM1_EVM_HS_CAN_$_RedStopLamp_$$___ 2
#define DB_DM1_EVM_HS_CAN_$_RedStopLamp_$$___ 3
#define DB_DM1_EVM_HS_CAN_$_AmberWarningLamp_$$____ 0
#define DB_DM1_EVM_HS_CAN_$_AmberWarningLamp_$$___ 1
#define DB_DM1_EVM_HS_CAN_$_AmberWarningLamp_$$___ 2
#define DB_DM1_EVM_HS_CAN_$_AmberWarningLamp_$$___ 3
#define DB_DM1_EVM_HS_CAN_$_ProtectLamp_$$____ 0
#define DB_DM1_EVM_HS_CAN_$_ProtectLamp_$$___ 1
#define DB_DM1_EVM_HS_CAN_$_ProtectLamp_$$___ 2
#define DB_DM1_EVM_HS_CAN_$_ProtectLamp_$$___ 3
#pragma warning(default : 4005)

void DB_DM1_EVM_HS_CAN_Init(DB_DM1_EVM_HS_CAN * pMsg);
int DB_DM1_EVM_HS_CAN_Transmit(DB_DM1_EVM_HS_CAN * pMsg);
int DB_DM1_EVM_HS_CAN_Transmit_raw(DB_DM1_EVM_HS_CAN * pMsg);
int DB_DM1_EVM_HS_CAN_UpdateBytesFromSignals(DB_DM1_EVM_HS_CAN * pMsg);
int DB_DM1_EVM_HS_CAN_UpdateBytesFromRawSignals(DB_DM1_EVM_HS_CAN * pMsg);
#define DB_DM1_EVM_HS_CAN_SPN_Mode_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, 0, dPhysicalValue);
#define DB_DM1_EVM_HS_CAN_OccuranceCount_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, 1, dPhysicalValue);
#define DB_DM1_EVM_HS_CAN_SPN_HighBit_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, 2, dPhysicalValue);
#define DB_DM1_EVM_HS_CAN_FMI_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, 3, dPhysicalValue);
#define DB_DM1_EVM_HS_CAN_SPN_Num_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, 4, dPhysicalValue);
#define DB_DM1_EVM_HS_CAN_MalfunctionIndicatorLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, 5, dPhysicalValue);
#define DB_DM1_EVM_HS_CAN_RedStopLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, 6, dPhysicalValue);
#define DB_DM1_EVM_HS_CAN_AmberWarningLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, 7, dPhysicalValue);
#define DB_DM1_EVM_HS_CAN_ProtectLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, 8, dPhysicalValue);
#define DB_DM1_EVM_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_DM1_EVM_HS_CAN_Index, 0)
extern int DB_EVM1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double RadarWarringLevel; /// Min: 0 Max: 3 Units: 
    BYTE RadarWarringLevel_raw;
    double RightDoublingWarring; /// Min: 0 Max: 3 Units: 
    BYTE RightDoublingWarring_raw;
    double LeftDoublingWarring; /// Min: 0 Max: 3 Units: 
    BYTE LeftDoublingWarring_raw;
    double RightVehicleBackWarring; /// Min: 0 Max: 3 Units: 
    BYTE RightVehicleBackWarring_raw;
    double LeftVehicleBackWarring; /// Min: 0 Max: 3 Units: 
    BYTE LeftVehicleBackWarring_raw;
    double Channel2ndVideoAngle_MMI; /// Min: 0 Max: 14 Units: 
    BYTE Channel2ndVideoAngle_MMI_raw;
    double Channel2ndVideoSource_MMI; /// Min: 0 Max: 15 Units: 
    BYTE Channel2ndVideoSource_MMI_raw;
} DB_EVM1_HS_CAN;

#pragma warning(disable : 4005)
#define DB_EVM1_HS_CAN_$_RadarWarringLevel_$$____ 0
#define DB_EVM1_HS_CAN_$_RadarWarringLevel_$$_____ 1
#define DB_EVM1_HS_CAN_$_RadarWarringLevel_$$_____ 2
#define DB_EVM1_HS_CAN_$_RadarWarringLevel_$$___ 3
#define DB_EVM1_HS_CAN_$_RightDoublingWarring_$$____ 0
#define DB_EVM1_HS_CAN_$_RightDoublingWarring_$$___ 1
#define DB_EVM1_HS_CAN_$_RightDoublingWarring_$$___ 2
#define DB_EVM1_HS_CAN_$_RightDoublingWarring_$$___ 3
#define DB_EVM1_HS_CAN_$_LeftDoublingWarring_$$____ 0
#define DB_EVM1_HS_CAN_$_LeftDoublingWarring_$$___ 1
#define DB_EVM1_HS_CAN_$_LeftDoublingWarring_$$___ 2
#define DB_EVM1_HS_CAN_$_LeftDoublingWarring_$$___ 3
#define DB_EVM1_HS_CAN_$_RightVehicleBackWarring_$$____ 0
#define DB_EVM1_HS_CAN_$_RightVehicleBackWarring_$$___ 1
#define DB_EVM1_HS_CAN_$_RightVehicleBackWarring_$$___ 2
#define DB_EVM1_HS_CAN_$_RightVehicleBackWarring_$$___ 3
#define DB_EVM1_HS_CAN_$_LeftVehicleBackWarring_$$____ 0
#define DB_EVM1_HS_CAN_$_LeftVehicleBackWarring_$$___ 1
#define DB_EVM1_HS_CAN_$_LeftVehicleBackWarring_$$___ 2
#define DB_EVM1_HS_CAN_$_LeftVehicleBackWarring_$$___ 3
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$_____ 0
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$___ 1
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$___ 2
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$______ 3
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$______ 4
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$_______ 5
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$_360___ 6
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$_____ 7
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$___ 8
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$___ 9
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$___ 10
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$___ 11
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$___ 12
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$___ 13
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$___ 14
#define DB_EVM1_HS_CAN_$_Channel2ndVideoAngle_MMI_$$___ 15
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$__________ 0
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____1 1
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____2 2
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____3 3
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____4 4
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____5 5
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____6 6
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____7 7
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____8 8
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____9 9
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____10 10
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____11 11
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____12 12
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____13 13
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$____14 14
#define DB_EVM1_HS_CAN_$_Channel2ndVideoSource_MMI_$$___ 15
#pragma warning(default : 4005)

void DB_EVM1_HS_CAN_Init(DB_EVM1_HS_CAN * pMsg);
int DB_EVM1_HS_CAN_Transmit(DB_EVM1_HS_CAN * pMsg);
int DB_EVM1_HS_CAN_Transmit_raw(DB_EVM1_HS_CAN * pMsg);
int DB_EVM1_HS_CAN_UpdateBytesFromSignals(DB_EVM1_HS_CAN * pMsg);
int DB_EVM1_HS_CAN_UpdateBytesFromRawSignals(DB_EVM1_HS_CAN * pMsg);
#define DB_EVM1_HS_CAN_RadarWarringLevel_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_EVM1_HS_CAN_RightDoublingWarring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, 1, dPhysicalValue);
#define DB_EVM1_HS_CAN_LeftDoublingWarring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, 2, dPhysicalValue);
#define DB_EVM1_HS_CAN_RightVehicleBackWarring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, 3, dPhysicalValue);
#define DB_EVM1_HS_CAN_LeftVehicleBackWarring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, 4, dPhysicalValue);
#define DB_EVM1_HS_CAN_Channel2ndVideoAngle_MMI_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, 5, dPhysicalValue);
#define DB_EVM1_HS_CAN_Channel2ndVideoSource_MMI_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, 6, dPhysicalValue);
#define DB_EVM1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_EVM1_HS_CAN_Index, 0)
extern int DB_NM_TXJ_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TXJ_NM_Sleep_Ack; /// Min: 0 Max: 1 Units: 
    BYTE TXJ_NM_Sleep_Ack_raw;
    double TXJ_NM_Sleep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE TXJ_NM_Sleep_Ind_raw;
    double TXJ_NM_Limphome; /// Min: 0 Max: 1 Units: 
    BYTE TXJ_NM_Limphome_raw;
    double TXJ_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE TXJ_NM_Ring_raw;
    double TXJ_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE TXJ_NM_Alive_raw;
    double TXJ_NM_DA; /// Min: 0 Max: 255 Units: 
    BYTE TXJ_NM_DA_raw;
} DB_NM_TXJ_HS_CAN;

#pragma warning(disable : 4005)
#define DB_NM_TXJ_HS_CAN_$_TXJ_NM_Sleep_Ack_$$_FALSE 0
#define DB_NM_TXJ_HS_CAN_$_TXJ_NM_Sleep_Ack_$$_TRUE_ 1
#define DB_NM_TXJ_HS_CAN_$_TXJ_NM_Sleep_Ind_$$_FALSE 0
#define DB_NM_TXJ_HS_CAN_$_TXJ_NM_Sleep_Ind_$$_TRUE_ 1
#define DB_NM_TXJ_HS_CAN_$_TXJ_NM_Limphome_$$_FALSE 0
#define DB_NM_TXJ_HS_CAN_$_TXJ_NM_Limphome_$$_TRUE_ 1
#define DB_NM_TXJ_HS_CAN_$_TXJ_NM_Ring_$$_FALSE 0
#define DB_NM_TXJ_HS_CAN_$_TXJ_NM_Ring_$$_TRUE_ 1
#define DB_NM_TXJ_HS_CAN_$_TXJ_NM_Alive_$$_FALSE 0
#define DB_NM_TXJ_HS_CAN_$_TXJ_NM_Alive_$$_TRUE_ 1
#pragma warning(default : 4005)

void DB_NM_TXJ_HS_CAN_Init(DB_NM_TXJ_HS_CAN * pMsg);
int DB_NM_TXJ_HS_CAN_Transmit(DB_NM_TXJ_HS_CAN * pMsg);
int DB_NM_TXJ_HS_CAN_Transmit_raw(DB_NM_TXJ_HS_CAN * pMsg);
int DB_NM_TXJ_HS_CAN_UpdateBytesFromSignals(DB_NM_TXJ_HS_CAN * pMsg);
int DB_NM_TXJ_HS_CAN_UpdateBytesFromRawSignals(DB_NM_TXJ_HS_CAN * pMsg);
#define DB_NM_TXJ_HS_CAN_TXJ_NM_Sleep_Ack_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, 0, dPhysicalValue);
#define DB_NM_TXJ_HS_CAN_TXJ_NM_Sleep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, 1, dPhysicalValue);
#define DB_NM_TXJ_HS_CAN_TXJ_NM_Limphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, 2, dPhysicalValue);
#define DB_NM_TXJ_HS_CAN_TXJ_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, 3, dPhysicalValue);
#define DB_NM_TXJ_HS_CAN_TXJ_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, 4, dPhysicalValue);
#define DB_NM_TXJ_HS_CAN_TXJ_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, 5, dPhysicalValue);
#define DB_NM_TXJ_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_TXJ_HS_CAN_Index, 0)
extern int DB_DM1_TXJ_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double SPN_Mode; /// Min: 0 Max: 1 Units: 
    BYTE SPN_Mode_raw;
    double OccuranceCount; /// Min: 0 Max: 126 Units: 
    BYTE OccuranceCount_raw;
    double SPN_HighBit; /// Min: 0 Max: 7 Units: 
    BYTE SPN_HighBit_raw;
    double FMI; /// Min: 0 Max: 31 Units: 
    BYTE FMI_raw;
    double RedStopLamp; /// Min: 0 Max: 3 Units: 
    BYTE RedStopLamp_raw;
    double SPN_Num; /// Min: 0 Max: 65535 Units: 
    WORD SPN_Num_raw;
    double MalfunctionIndicatorLamp; /// Min: 0 Max: 3 Units: 
    BYTE MalfunctionIndicatorLamp_raw;
    double AmberWarningLamp; /// Min: 0 Max: 3 Units: 
    BYTE AmberWarningLamp_raw;
    double ProtectLamp; /// Min: 0 Max: 3 Units: 
    BYTE ProtectLamp_raw;
} DB_DM1_TXJ_HS_CAN;

#define DB_DM1_TXJ_HS_CAN_SendType 1
#define DB_DM1_TXJ_HS_CAN_SendRate 1000
#pragma warning(disable : 4005)
#define DB_DM1_TXJ_HS_CAN_$_RedStopLamp_$$____ 0
#define DB_DM1_TXJ_HS_CAN_$_RedStopLamp_$$___ 1
#define DB_DM1_TXJ_HS_CAN_$_RedStopLamp_$$___ 2
#define DB_DM1_TXJ_HS_CAN_$_RedStopLamp_$$___ 3
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN___ 0
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN___ 1
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN___ 2
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN___ 3
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN___ 4
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN___ 5
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN___ 6
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN___ 7
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN____ 8
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN____ 9
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN____ 10
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN____ 11
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN____ 12
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN____ 13
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN____ 14
#define DB_DM1_TXJ_HS_CAN_$_SPN_Num_$$_SPN____ 15
#define DB_DM1_TXJ_HS_CAN_$_MalfunctionIndicatorLamp_$$____ 0
#define DB_DM1_TXJ_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 1
#define DB_DM1_TXJ_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 2
#define DB_DM1_TXJ_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 3
#define DB_DM1_TXJ_HS_CAN_$_AmberWarningLamp_$$____ 0
#define DB_DM1_TXJ_HS_CAN_$_AmberWarningLamp_$$___ 1
#define DB_DM1_TXJ_HS_CAN_$_AmberWarningLamp_$$___ 2
#define DB_DM1_TXJ_HS_CAN_$_AmberWarningLamp_$$___ 3
#define DB_DM1_TXJ_HS_CAN_$_ProtectLamp_$$____ 0
#define DB_DM1_TXJ_HS_CAN_$_ProtectLamp_$$___ 1
#define DB_DM1_TXJ_HS_CAN_$_ProtectLamp_$$___ 2
#define DB_DM1_TXJ_HS_CAN_$_ProtectLamp_$$___ 3
#pragma warning(default : 4005)

void DB_DM1_TXJ_HS_CAN_Init(DB_DM1_TXJ_HS_CAN * pMsg);
int DB_DM1_TXJ_HS_CAN_Transmit(DB_DM1_TXJ_HS_CAN * pMsg);
int DB_DM1_TXJ_HS_CAN_Transmit_raw(DB_DM1_TXJ_HS_CAN * pMsg);
int DB_DM1_TXJ_HS_CAN_UpdateBytesFromSignals(DB_DM1_TXJ_HS_CAN * pMsg);
int DB_DM1_TXJ_HS_CAN_UpdateBytesFromRawSignals(DB_DM1_TXJ_HS_CAN * pMsg);
#define DB_DM1_TXJ_HS_CAN_SPN_Mode_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, 0, dPhysicalValue);
#define DB_DM1_TXJ_HS_CAN_OccuranceCount_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, 1, dPhysicalValue);
#define DB_DM1_TXJ_HS_CAN_SPN_HighBit_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, 2, dPhysicalValue);
#define DB_DM1_TXJ_HS_CAN_FMI_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, 3, dPhysicalValue);
#define DB_DM1_TXJ_HS_CAN_RedStopLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, 4, dPhysicalValue);
#define DB_DM1_TXJ_HS_CAN_SPN_Num_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, 5, dPhysicalValue);
#define DB_DM1_TXJ_HS_CAN_MalfunctionIndicatorLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, 6, dPhysicalValue);
#define DB_DM1_TXJ_HS_CAN_AmberWarningLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, 7, dPhysicalValue);
#define DB_DM1_TXJ_HS_CAN_ProtectLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, 8, dPhysicalValue);
#define DB_DM1_TXJ_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_DM1_TXJ_HS_CAN_Index, 0)
extern int DB_VehicleCtr_HS_CAN_db95_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TXJ_SwitchAuxIn; /// Min: 0 Max: 3 Units: 
    BYTE TXJ_SwitchAuxIn_raw;
} DB_VehicleCtr_HS_CAN_db95;

#define DB_VehicleCtr_HS_CAN_db95_SendType 1
#define DB_VehicleCtr_HS_CAN_db95_SendRate 50
#pragma warning(disable : 4005)
#define DB_VehicleCtr_HS_CAN_db95_$_TXJ_SwitchAuxIn_$$___ 0
#define DB_VehicleCtr_HS_CAN_db95_$_TXJ_SwitchAuxIn_$$___ 1
#define DB_VehicleCtr_HS_CAN_db95_$_TXJ_SwitchAuxIn_$$_____ 2
#define DB_VehicleCtr_HS_CAN_db95_$_TXJ_SwitchAuxIn_$$___ 3
#pragma warning(default : 4005)

void DB_VehicleCtr_HS_CAN_db95_Init(DB_VehicleCtr_HS_CAN_db95 * pMsg);
int DB_VehicleCtr_HS_CAN_db95_Transmit(DB_VehicleCtr_HS_CAN_db95 * pMsg);
int DB_VehicleCtr_HS_CAN_db95_Transmit_raw(DB_VehicleCtr_HS_CAN_db95 * pMsg);
int DB_VehicleCtr_HS_CAN_db95_UpdateBytesFromSignals(DB_VehicleCtr_HS_CAN_db95 * pMsg);
int DB_VehicleCtr_HS_CAN_db95_UpdateBytesFromRawSignals(DB_VehicleCtr_HS_CAN_db95 * pMsg);
#define DB_VehicleCtr_HS_CAN_db95_TXJ_SwitchAuxIn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_db95_Index, 0, dPhysicalValue);
#define DB_VehicleCtr_HS_CAN_db95_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VehicleCtr_HS_CAN_db95_Index, 0)
extern int DB_VDS_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Altitude; /// Min: -2500 Max: 5531.875 Units: m
    WORD Altitude_raw;
    double Pitch; /// Min: 0 Max: 301.992 Units: ?
    WORD Pitch_raw;
    double NavigationBasedVehicleSpeed; /// Min: 0 Max: 250.996 Units: km/h
    WORD NavigationBasedVehicleSpeed_raw;
    double CompassBearing; /// Min: 0 Max: 501.99 Units: ?
    WORD CompassBearing_raw;
} DB_VDS_HS_CAN;


void DB_VDS_HS_CAN_Init(DB_VDS_HS_CAN * pMsg);
int DB_VDS_HS_CAN_Transmit(DB_VDS_HS_CAN * pMsg);
int DB_VDS_HS_CAN_Transmit_raw(DB_VDS_HS_CAN * pMsg);
int DB_VDS_HS_CAN_UpdateBytesFromSignals(DB_VDS_HS_CAN * pMsg);
int DB_VDS_HS_CAN_UpdateBytesFromRawSignals(DB_VDS_HS_CAN * pMsg);
#define DB_VDS_HS_CAN_Altitude_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VDS_HS_CAN_Index, 0, dPhysicalValue);
#define DB_VDS_HS_CAN_Pitch_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VDS_HS_CAN_Index, 1, dPhysicalValue);
#define DB_VDS_HS_CAN_NavigationBasedVehicleSpeed_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VDS_HS_CAN_Index, 2, dPhysicalValue);
#define DB_VDS_HS_CAN_CompassBearing_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_VDS_HS_CAN_Index, 3, dPhysicalValue);
#define DB_VDS_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_VDS_HS_CAN_Index, 0)
extern int DB_GPS_Item_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double BD_SatelliteCounts; /// Min: 0 Max: 15 Units: 
    BYTE BD_SatelliteCounts_raw;
    double GPS_SatelliteCounts; /// Min: 0 Max: 15 Units: 
    BYTE GPS_SatelliteCounts_raw;
    double GPS_Precision; /// Min: 0 Max: 3 Units: 
    BYTE GPS_Precision_raw;
    double GPS_Item; /// Min: 0 Max: 15 Units: 
    BYTE GPS_Item_raw;
} DB_GPS_Item_HS_CAN;

#pragma warning(disable : 4005)
#define DB_GPS_Item_HS_CAN_$_GPS_Precision_$$______ 0
#define DB_GPS_Item_HS_CAN_$_GPS_Precision_$$_____ 1
#define DB_GPS_Item_HS_CAN_$_GPS_Precision_$$___ 2
#define DB_GPS_Item_HS_CAN_$_GPS_Precision_$$___ 3
#pragma warning(default : 4005)

void DB_GPS_Item_HS_CAN_Init(DB_GPS_Item_HS_CAN * pMsg);
int DB_GPS_Item_HS_CAN_Transmit(DB_GPS_Item_HS_CAN * pMsg);
int DB_GPS_Item_HS_CAN_Transmit_raw(DB_GPS_Item_HS_CAN * pMsg);
int DB_GPS_Item_HS_CAN_UpdateBytesFromSignals(DB_GPS_Item_HS_CAN * pMsg);
int DB_GPS_Item_HS_CAN_UpdateBytesFromRawSignals(DB_GPS_Item_HS_CAN * pMsg);
#define DB_GPS_Item_HS_CAN_BD_SatelliteCounts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_GPS_Item_HS_CAN_Index, 0, dPhysicalValue);
#define DB_GPS_Item_HS_CAN_GPS_SatelliteCounts_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_GPS_Item_HS_CAN_Index, 1, dPhysicalValue);
#define DB_GPS_Item_HS_CAN_GPS_Precision_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_GPS_Item_HS_CAN_Index, 2, dPhysicalValue);
#define DB_GPS_Item_HS_CAN_GPS_Item_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_GPS_Item_HS_CAN_Index, 3, dPhysicalValue);
#define DB_GPS_Item_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_GPS_Item_HS_CAN_Index, 0)
extern int DB_PositionGPS_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Longitude; /// Min: -210 Max: 211.10812 Units: 
    DWORD Longitude_raw;
    double Latitude; /// Min: -210 Max: 211.10812 Units: 
    DWORD Latitude_raw;
} DB_PositionGPS_HS_CAN;


void DB_PositionGPS_HS_CAN_Init(DB_PositionGPS_HS_CAN * pMsg);
int DB_PositionGPS_HS_CAN_Transmit(DB_PositionGPS_HS_CAN * pMsg);
int DB_PositionGPS_HS_CAN_Transmit_raw(DB_PositionGPS_HS_CAN * pMsg);
int DB_PositionGPS_HS_CAN_UpdateBytesFromSignals(DB_PositionGPS_HS_CAN * pMsg);
int DB_PositionGPS_HS_CAN_UpdateBytesFromRawSignals(DB_PositionGPS_HS_CAN * pMsg);
#define DB_PositionGPS_HS_CAN_Longitude_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PositionGPS_HS_CAN_Index, 0, dPhysicalValue);
#define DB_PositionGPS_HS_CAN_Latitude_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_PositionGPS_HS_CAN_Index, 1, dPhysicalValue);
#define DB_PositionGPS_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_PositionGPS_HS_CAN_Index, 0)
extern int DB_TD_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double LocalHourOffset; /// Min: -23 Max: 23 Units: hour
    BYTE LocalHourOffset_raw;
    double LocalMinuteOffset; /// Min: -59 Max: 59 Units: min
    BYTE LocalMinuteOffset_raw;
    double Year; /// Min: 1985 Max: 2235 Units: 
    BYTE Year_raw;
    double Day; /// Min: 0 Max: 31.75 Units: days
    BYTE Day_raw;
    double Month; /// Min: 1 Max: 12 Units: Month
    BYTE Month_raw;
    double Hours; /// Min: 0 Max: 23 Units: hour
    BYTE Hours_raw;
    double Second; /// Min: 0 Max: 59.75 Units: s
    BYTE Second_raw;
    double Minutes; /// Min: 0 Max: 59 Units: min
    BYTE Minutes_raw;
} DB_TD_HS_CAN;


void DB_TD_HS_CAN_Init(DB_TD_HS_CAN * pMsg);
int DB_TD_HS_CAN_Transmit(DB_TD_HS_CAN * pMsg);
int DB_TD_HS_CAN_Transmit_raw(DB_TD_HS_CAN * pMsg);
int DB_TD_HS_CAN_UpdateBytesFromSignals(DB_TD_HS_CAN * pMsg);
int DB_TD_HS_CAN_UpdateBytesFromRawSignals(DB_TD_HS_CAN * pMsg);
#define DB_TD_HS_CAN_LocalHourOffset_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TD_HS_CAN_Index, 0, dPhysicalValue);
#define DB_TD_HS_CAN_LocalMinuteOffset_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TD_HS_CAN_Index, 1, dPhysicalValue);
#define DB_TD_HS_CAN_Year_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TD_HS_CAN_Index, 2, dPhysicalValue);
#define DB_TD_HS_CAN_Day_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TD_HS_CAN_Index, 3, dPhysicalValue);
#define DB_TD_HS_CAN_Month_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TD_HS_CAN_Index, 4, dPhysicalValue);
#define DB_TD_HS_CAN_Hours_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TD_HS_CAN_Index, 5, dPhysicalValue);
#define DB_TD_HS_CAN_Second_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TD_HS_CAN_Index, 6, dPhysicalValue);
#define DB_TD_HS_CAN_Minutes_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TD_HS_CAN_Index, 7, dPhysicalValue);
#define DB_TD_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_TD_HS_CAN_Index, 0)
extern int DB_TXJxMMI_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TXJ_MMI; /// Min: 0 Max: 18446744073709551615 Units: 
    uint64 TXJ_MMI_raw;
} DB_TXJxMMI_HS_CAN;


void DB_TXJxMMI_HS_CAN_Init(DB_TXJxMMI_HS_CAN * pMsg);
int DB_TXJxMMI_HS_CAN_Transmit(DB_TXJxMMI_HS_CAN * pMsg);
int DB_TXJxMMI_HS_CAN_Transmit_raw(DB_TXJxMMI_HS_CAN * pMsg);
int DB_TXJxMMI_HS_CAN_UpdateBytesFromSignals(DB_TXJxMMI_HS_CAN * pMsg);
int DB_TXJxMMI_HS_CAN_UpdateBytesFromRawSignals(DB_TXJxMMI_HS_CAN * pMsg);
#define DB_TXJxMMI_HS_CAN_TXJ_MMI_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TXJxMMI_HS_CAN_Index, 0, dPhysicalValue);
#define DB_TXJxMMI_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_TXJxMMI_HS_CAN_Index, 0)
extern int DB_TCO1_HS_CAN_db101_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TachographVehiclespeed; /// Min: 0 Max: 250.996 Units: km/h
    WORD TachographVehiclespeed_raw;
} DB_TCO1_HS_CAN_db101;


void DB_TCO1_HS_CAN_db101_Init(DB_TCO1_HS_CAN_db101 * pMsg);
int DB_TCO1_HS_CAN_db101_Transmit(DB_TCO1_HS_CAN_db101 * pMsg);
int DB_TCO1_HS_CAN_db101_Transmit_raw(DB_TCO1_HS_CAN_db101 * pMsg);
int DB_TCO1_HS_CAN_db101_UpdateBytesFromSignals(DB_TCO1_HS_CAN_db101 * pMsg);
int DB_TCO1_HS_CAN_db101_UpdateBytesFromRawSignals(DB_TCO1_HS_CAN_db101 * pMsg);
#define DB_TCO1_HS_CAN_db101_TachographVehiclespeed_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_TCO1_HS_CAN_db101_Index, 0, dPhysicalValue);
#define DB_TCO1_HS_CAN_db101_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_TCO1_HS_CAN_db101_Index, 0)
extern int DB_NM_MMI_HS_CAN_db102_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double MMI_NM_Sleep_Ack; /// Min: 0 Max: 1 Units: 
    BYTE MMI_NM_Sleep_Ack_raw;
    double MMI_NM_Sleep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE MMI_NM_Sleep_Ind_raw;
    double MMI_NM_Limphome; /// Min: 0 Max: 1 Units: 
    BYTE MMI_NM_Limphome_raw;
    double MMI_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE MMI_NM_Ring_raw;
    double MMI_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE MMI_NM_Alive_raw;
    double MMI_NM_DA; /// Min: 0 Max: 255 Units: 
    BYTE MMI_NM_DA_raw;
} DB_NM_MMI_HS_CAN_db102;

#pragma warning(disable : 4005)
#define DB_NM_MMI_HS_CAN_db102_$_MMI_NM_Sleep_Ack_$$_FALSE 0
#define DB_NM_MMI_HS_CAN_db102_$_MMI_NM_Sleep_Ack_$$_TRUE 1
#define DB_NM_MMI_HS_CAN_db102_$_MMI_NM_Sleep_Ind_$$_FALSE 0
#define DB_NM_MMI_HS_CAN_db102_$_MMI_NM_Sleep_Ind_$$_TRUE 1
#define DB_NM_MMI_HS_CAN_db102_$_MMI_NM_Limphome_$$_FALSE 0
#define DB_NM_MMI_HS_CAN_db102_$_MMI_NM_Limphome_$$_TRUE 1
#define DB_NM_MMI_HS_CAN_db102_$_MMI_NM_Ring_$$_FALSE 0
#define DB_NM_MMI_HS_CAN_db102_$_MMI_NM_Ring_$$_TRUE 1
#define DB_NM_MMI_HS_CAN_db102_$_MMI_NM_Alive_$$_FALSE 0
#define DB_NM_MMI_HS_CAN_db102_$_MMI_NM_Alive_$$_TRUE 1
#pragma warning(default : 4005)

void DB_NM_MMI_HS_CAN_db102_Init(DB_NM_MMI_HS_CAN_db102 * pMsg);
int DB_NM_MMI_HS_CAN_db102_Transmit(DB_NM_MMI_HS_CAN_db102 * pMsg);
int DB_NM_MMI_HS_CAN_db102_Transmit_raw(DB_NM_MMI_HS_CAN_db102 * pMsg);
int DB_NM_MMI_HS_CAN_db102_UpdateBytesFromSignals(DB_NM_MMI_HS_CAN_db102 * pMsg);
int DB_NM_MMI_HS_CAN_db102_UpdateBytesFromRawSignals(DB_NM_MMI_HS_CAN_db102 * pMsg);
#define DB_NM_MMI_HS_CAN_db102_MMI_NM_Sleep_Ack_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, 0, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_db102_MMI_NM_Sleep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, 1, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_db102_MMI_NM_Limphome_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, 2, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_db102_MMI_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, 3, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_db102_MMI_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, 4, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_db102_MMI_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, 5, dPhysicalValue);
#define DB_NM_MMI_HS_CAN_db102_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_MMI_HS_CAN_db102_Index, 0)
extern int DB_DM1_MMI_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double SPN_Mode; /// Min: 0 Max: 1 Units: 
    BYTE SPN_Mode_raw;
    double OccuranceCount; /// Min: 0 Max: 126 Units: 
    BYTE OccuranceCount_raw;
    double SPN_HighBit; /// Min: 0 Max: 7 Units: 
    BYTE SPN_HighBit_raw;
    double FMI; /// Min: 0 Max: 35 Units: 
    BYTE FMI_raw;
    double SPN_Num; /// Min: 0 Max: 65535 Units: 
    WORD SPN_Num_raw;
    double MalfunctionIndicatorLamp; /// Min: 0 Max: 3 Units: 
    BYTE MalfunctionIndicatorLamp_raw;
    double AmberWarningLamp; /// Min: 0 Max: 3 Units: 
    BYTE AmberWarningLamp_raw;
    double RedStopLamp; /// Min: 0 Max: 3 Units: 
    BYTE RedStopLamp_raw;
    double ProtectLamp; /// Min: 0 Max: 3 Units: 
    BYTE ProtectLamp_raw;
} DB_DM1_MMI_HS_CAN;

#define DB_DM1_MMI_HS_CAN_SendType 1
#define DB_DM1_MMI_HS_CAN_SendRate 1000
#pragma warning(disable : 4005)
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN___ 0
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN___ 1
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN___ 2
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN___ 3
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN___ 4
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN___ 5
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN___ 6
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN___ 7
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN____ 8
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN____ 9
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN____ 10
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN____ 11
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN____ 12
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN____ 13
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN____ 14
#define DB_DM1_MMI_HS_CAN_$_SPN_Num_$$_SPN____ 15
#define DB_DM1_MMI_HS_CAN_$_MalfunctionIndicatorLamp_$$____ 0
#define DB_DM1_MMI_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 1
#define DB_DM1_MMI_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 2
#define DB_DM1_MMI_HS_CAN_$_MalfunctionIndicatorLamp_$$___ 3
#define DB_DM1_MMI_HS_CAN_$_AmberWarningLamp_$$____ 0
#define DB_DM1_MMI_HS_CAN_$_AmberWarningLamp_$$___ 1
#define DB_DM1_MMI_HS_CAN_$_AmberWarningLamp_$$___ 2
#define DB_DM1_MMI_HS_CAN_$_AmberWarningLamp_$$___ 3
#define DB_DM1_MMI_HS_CAN_$_RedStopLamp_$$____ 0
#define DB_DM1_MMI_HS_CAN_$_RedStopLamp_$$___ 1
#define DB_DM1_MMI_HS_CAN_$_RedStopLamp_$$___ 2
#define DB_DM1_MMI_HS_CAN_$_RedStopLamp_$$___ 3
#define DB_DM1_MMI_HS_CAN_$_ProtectLamp_$$____ 0
#define DB_DM1_MMI_HS_CAN_$_ProtectLamp_$$___ 1
#define DB_DM1_MMI_HS_CAN_$_ProtectLamp_$$___ 2
#define DB_DM1_MMI_HS_CAN_$_ProtectLamp_$$___ 3
#pragma warning(default : 4005)

void DB_DM1_MMI_HS_CAN_Init(DB_DM1_MMI_HS_CAN * pMsg);
int DB_DM1_MMI_HS_CAN_Transmit(DB_DM1_MMI_HS_CAN * pMsg);
int DB_DM1_MMI_HS_CAN_Transmit_raw(DB_DM1_MMI_HS_CAN * pMsg);
int DB_DM1_MMI_HS_CAN_UpdateBytesFromSignals(DB_DM1_MMI_HS_CAN * pMsg);
int DB_DM1_MMI_HS_CAN_UpdateBytesFromRawSignals(DB_DM1_MMI_HS_CAN * pMsg);
#define DB_DM1_MMI_HS_CAN_SPN_Mode_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, 0, dPhysicalValue);
#define DB_DM1_MMI_HS_CAN_OccuranceCount_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, 1, dPhysicalValue);
#define DB_DM1_MMI_HS_CAN_SPN_HighBit_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, 2, dPhysicalValue);
#define DB_DM1_MMI_HS_CAN_FMI_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, 3, dPhysicalValue);
#define DB_DM1_MMI_HS_CAN_SPN_Num_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, 4, dPhysicalValue);
#define DB_DM1_MMI_HS_CAN_MalfunctionIndicatorLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, 5, dPhysicalValue);
#define DB_DM1_MMI_HS_CAN_AmberWarningLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, 6, dPhysicalValue);
#define DB_DM1_MMI_HS_CAN_RedStopLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, 7, dPhysicalValue);
#define DB_DM1_MMI_HS_CAN_ProtectLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, 8, dPhysicalValue);
#define DB_DM1_MMI_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_DM1_MMI_HS_CAN_Index, 0)
extern int DB_MMI_CtrDCM_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double BackOfSeatHypsokinesisPos; /// Min: 0 Max: 180 Units: ?
    BYTE BackOfSeatHypsokinesisPos_raw;
    double SeatHypsokinesisPos; /// Min: 0 Max: 180 Units: ?
    BYTE SeatHypsokinesisPos_raw;
    double MMI_Mem_Restore; /// Min: 0 Max: 1 Units: 
    BYTE MMI_Mem_Restore_raw;
    double SeatHorizonPos; /// Min: 0 Max: 100 Units: %
    BYTE SeatHorizonPos_raw;
    double M_MarkCmd; /// Min: 0 Max: 1 Units: 
    BYTE M_MarkCmd_raw;
    double SeatVerticalPos; /// Min: 0 Max: 100 Units: %
    BYTE SeatVerticalPos_raw;
    double RightRearMirVerticalAngle; /// Min: 0 Max: 255 Units: ?
    BYTE RightRearMirVerticalAngle_raw;
    double LeftRearMirVerticalAngle; /// Min: 0 Max: 255 Units: ?
    BYTE LeftRearMirVerticalAngle_raw;
    double RightRearMirHorizontalAngle; /// Min: 0 Max: 255 Units: 
    BYTE RightRearMirHorizontalAngle_raw;
    double LeftRearMirHorizontalAngle; /// Min: 0 Max: 255 Units: ?
    BYTE LeftRearMirHorizontalAngle_raw;
} DB_MMI_CtrDCM_HS_CAN;

#define DB_MMI_CtrDCM_HS_CAN_SendType 2
#pragma warning(disable : 4005)
#define DB_MMI_CtrDCM_HS_CAN_$_MMI_Mem_Restore_$$____ 0
#define DB_MMI_CtrDCM_HS_CAN_$_MMI_Mem_Restore_$$___ 1
#define DB_MMI_CtrDCM_HS_CAN_$_M_MarkCmd_$$____ 0
#define DB_MMI_CtrDCM_HS_CAN_$_M_MarkCmd_$$___ 1
#pragma warning(default : 4005)

void DB_MMI_CtrDCM_HS_CAN_Init(DB_MMI_CtrDCM_HS_CAN * pMsg);
int DB_MMI_CtrDCM_HS_CAN_Transmit(DB_MMI_CtrDCM_HS_CAN * pMsg);
int DB_MMI_CtrDCM_HS_CAN_Transmit_raw(DB_MMI_CtrDCM_HS_CAN * pMsg);
int DB_MMI_CtrDCM_HS_CAN_UpdateBytesFromSignals(DB_MMI_CtrDCM_HS_CAN * pMsg);
int DB_MMI_CtrDCM_HS_CAN_UpdateBytesFromRawSignals(DB_MMI_CtrDCM_HS_CAN * pMsg);
#define DB_MMI_CtrDCM_HS_CAN_BackOfSeatHypsokinesisPos_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, 0, dPhysicalValue);
#define DB_MMI_CtrDCM_HS_CAN_SeatHypsokinesisPos_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, 1, dPhysicalValue);
#define DB_MMI_CtrDCM_HS_CAN_MMI_Mem_Restore_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, 2, dPhysicalValue);
#define DB_MMI_CtrDCM_HS_CAN_SeatHorizonPos_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, 3, dPhysicalValue);
#define DB_MMI_CtrDCM_HS_CAN_M_MarkCmd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, 4, dPhysicalValue);
#define DB_MMI_CtrDCM_HS_CAN_SeatVerticalPos_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, 5, dPhysicalValue);
#define DB_MMI_CtrDCM_HS_CAN_RightRearMirVerticalAngle_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, 6, dPhysicalValue);
#define DB_MMI_CtrDCM_HS_CAN_LeftRearMirVerticalAngle_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, 7, dPhysicalValue);
#define DB_MMI_CtrDCM_HS_CAN_RightRearMirHorizontalAngle_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, 8, dPhysicalValue);
#define DB_MMI_CtrDCM_HS_CAN_LeftRearMirHorizontalAngle_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, 9, dPhysicalValue);
#define DB_MMI_CtrDCM_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_MMI_CtrDCM_HS_CAN_Index, 0)
extern int DB_MMIctrCab_HS_CAN_db105_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double BackOfSeatHypsokinesisForward; /// Min: 0 Max: 3 Units: 
    BYTE BackOfSeatHypsokinesisForward_raw;
    double BackOfSeatHypsokinesisBackward; /// Min: 0 Max: 3 Units: 
    BYTE BackOfSeatHypsokinesisBackward_raw;
    double SeatHypsokinesisForward; /// Min: 0 Max: 3 Units: 
    BYTE SeatHypsokinesisForward_raw;
    double SeatHypsokinesisBackward; /// Min: 0 Max: 3 Units: 
    BYTE SeatHypsokinesisBackward_raw;
    double SeatHorizonBackward; /// Min: 0 Max: 3 Units: 
    BYTE SeatHorizonBackward_raw;
    double SeatHorizonForward; /// Min: 0 Max: 3 Units: 
    BYTE SeatHorizonForward_raw;
    double SeatVerticalDown; /// Min: 0 Max: 3 Units: 
    BYTE SeatVerticalDown_raw;
    double SeatVerticalUp; /// Min: 0 Max: 3 Units: 
    BYTE SeatVerticalUp_raw;
    double MMIctrDrLockOpen; /// Min: 0 Max: 3 Units: 
    BYTE MMIctrDrLockOpen_raw;
    double LKAS_SW; /// Min: 0 Max: 3 Units: 
    BYTE LKAS_SW_raw;
    double RoofPositionCtr; /// Min: 0 Max: 255 Units: 
    BYTE RoofPositionCtr_raw;
    double RoofWorkCmd; /// Min: 0 Max: 7 Units: 
    BYTE RoofWorkCmd_raw;
    double MMIctrLBmOpn; /// Min: 0 Max: 3 Units: 
    BYTE MMIctrLBmOpn_raw;
    double MMIctrLBmCls; /// Min: 0 Max: 3 Units: 
    BYTE MMIctrLBmCls_raw;
    double MMIctrFLgOpn; /// Min: 0 Max: 3 Units: 
    BYTE MMIctrFLgOpn_raw;
    double MMIctrFLgCls; /// Min: 0 Max: 3 Units: 
    BYTE MMIctrFLgCls_raw;
    double MMIctrDrWdOpn; /// Min: 0 Max: 3 Units: 
    BYTE MMIctrDrWdOpn_raw;
    double MMIctrDrWdCls; /// Min: 0 Max: 3 Units: 
    BYTE MMIctrDrWdCls_raw;
} DB_MMIctrCab_HS_CAN_db105;

#pragma warning(disable : 4005)
#define DB_MMIctrCab_HS_CAN_db105_$_BackOfSeatHypsokinesisForward_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_BackOfSeatHypsokinesisForward_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_BackOfSeatHypsokinesisForward_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_BackOfSeatHypsokinesisForward_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_BackOfSeatHypsokinesisBackward_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_BackOfSeatHypsokinesisBackward_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_BackOfSeatHypsokinesisBackward_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_BackOfSeatHypsokinesisBackward_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHypsokinesisForward_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHypsokinesisForward_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHypsokinesisForward_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHypsokinesisForward_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHypsokinesisBackward_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHypsokinesisBackward_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHypsokinesisBackward_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHypsokinesisBackward_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHorizonBackward_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHorizonBackward_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHorizonBackward_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHorizonBackward_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHorizonForward_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHorizonForward_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHorizonForward_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_SeatHorizonForward_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_SeatVerticalDown_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_SeatVerticalDown_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_SeatVerticalDown_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_SeatVerticalDown_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_SeatVerticalUp_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_SeatVerticalUp_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_SeatVerticalUp_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_SeatVerticalUp_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrLockOpen_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrLockOpen_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrLockOpen_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrLockOpen_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_LKAS_SW_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_LKAS_SW_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_LKAS_SW_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_LKAS_SW_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 1
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 2
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 3
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 4
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 5
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 6
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 7
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 8
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 9
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 10
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 11
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 12
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 13
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 14
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 15
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 16
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 17
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 18
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 19
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 20
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 21
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 22
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 23
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 24
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 25
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 26
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 27
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 28
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 29
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 30
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 31
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 32
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 33
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 34
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 35
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 36
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 37
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 38
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 39
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 40
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 41
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 42
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 43
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 44
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 45
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 46
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 47
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 48
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 49
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 50
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 51
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 52
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 53
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 54
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 55
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 56
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 57
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 58
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 59
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 60
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 61
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 62
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 63
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 64
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 65
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 66
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 67
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 68
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 69
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 70
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 71
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 72
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 73
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 74
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 75
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 76
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 77
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 78
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 79
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 80
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 81
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 82
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 83
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 84
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 85
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 86
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 87
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 88
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 89
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 90
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 91
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 92
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 93
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 94
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 95
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 96
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 97
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 98
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 99
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 100
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 101
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 102
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 103
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 104
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 105
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 106
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 107
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 108
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 109
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 110
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 111
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 112
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 113
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 114
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 115
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 116
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 117
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 118
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 119
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 120
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 121
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 122
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 123
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 124
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 125
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 126
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 127
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 128
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 129
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 130
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 131
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 132
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 133
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 134
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 135
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 136
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 137
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 138
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 139
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 140
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 141
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 142
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 143
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 144
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 145
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 146
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 147
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 148
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 149
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 150
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 151
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 152
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 153
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 154
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 155
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 156
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 157
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 158
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 159
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 160
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 161
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 162
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 163
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 164
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 165
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 166
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 167
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 168
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 169
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 170
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 171
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 172
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 173
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 174
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 175
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 176
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 177
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 178
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 179
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$______ 180
#define DB_MMIctrCab_HS_CAN_db105_$_RoofPositionCtr_$$____ 255
#define DB_MMIctrCab_HS_CAN_db105_$_RoofWorkCmd_$$_No_command 0
#define DB_MMIctrCab_HS_CAN_db105_$_RoofWorkCmd_$$_Auto_Closing 1
#define DB_MMIctrCab_HS_CAN_db105_$_RoofWorkCmd_$$_Manual_Closing 2
#define DB_MMIctrCab_HS_CAN_db105_$_RoofWorkCmd_$$_Reserved 3
#define DB_MMIctrCab_HS_CAN_db105_$_RoofWorkCmd_$$_Reserved 4
#define DB_MMIctrCab_HS_CAN_db105_$_RoofWorkCmd_$$_Auto_Opening 5
#define DB_MMIctrCab_HS_CAN_db105_$_RoofWorkCmd_$$_Manual_Opening 6
#define DB_MMIctrCab_HS_CAN_db105_$_RoofWorkCmd_$$_Reserved 7
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrLBmOpn_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrLBmOpn_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrLBmOpn_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrLBmOpn_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrLBmCls_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrLBmCls_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrLBmCls_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrLBmCls_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrFLgOpn_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrFLgOpn_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrFLgOpn_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrFLgOpn_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrFLgCls_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrFLgCls_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrFLgCls_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrFLgCls_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrWdOpn_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrWdOpn_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrWdOpn_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrWdOpn_$$___ 3
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrWdCls_$$____ 0
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrWdCls_$$___ 1
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrWdCls_$$___ 2
#define DB_MMIctrCab_HS_CAN_db105_$_MMIctrDrWdCls_$$___ 3
#pragma warning(default : 4005)

void DB_MMIctrCab_HS_CAN_db105_Init(DB_MMIctrCab_HS_CAN_db105 * pMsg);
int DB_MMIctrCab_HS_CAN_db105_Transmit(DB_MMIctrCab_HS_CAN_db105 * pMsg);
int DB_MMIctrCab_HS_CAN_db105_Transmit_raw(DB_MMIctrCab_HS_CAN_db105 * pMsg);
int DB_MMIctrCab_HS_CAN_db105_UpdateBytesFromSignals(DB_MMIctrCab_HS_CAN_db105 * pMsg);
int DB_MMIctrCab_HS_CAN_db105_UpdateBytesFromRawSignals(DB_MMIctrCab_HS_CAN_db105 * pMsg);
#define DB_MMIctrCab_HS_CAN_db105_BackOfSeatHypsokinesisForward_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 0, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_BackOfSeatHypsokinesisBackward_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 1, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_SeatHypsokinesisForward_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 2, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_SeatHypsokinesisBackward_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 3, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_SeatHorizonBackward_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 4, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_SeatHorizonForward_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 5, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_SeatVerticalDown_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 6, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_SeatVerticalUp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 7, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_MMIctrDrLockOpen_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 8, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_LKAS_SW_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 9, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_RoofPositionCtr_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 10, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_RoofWorkCmd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 11, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_MMIctrLBmOpn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 12, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_MMIctrLBmCls_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 13, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_MMIctrFLgOpn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 14, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_MMIctrFLgCls_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 15, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_MMIctrDrWdOpn_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 16, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_MMIctrDrWdCls_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, 17, dPhysicalValue);
#define DB_MMIctrCab_HS_CAN_db105_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_MMIctrCab_HS_CAN_db105_Index, 0)
extern int DB_MMI_NAV_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double NAV_PhWaringDistce; /// Min: 0 Max: 1500 Units: m
    BYTE NAV_PhWaringDistce_raw;
    double NAV_PhWaring; /// Min: 0 Max: 7 Units: 
    BYTE NAV_PhWaring_raw;
    double NAV_TurnWaringDistce; /// Min: 0 Max: 1500 Units: m
    BYTE NAV_TurnWaringDistce_raw;
    double NAV_TurnWaring; /// Min: 0 Max: 7 Units: 
    BYTE NAV_TurnWaring_raw;
    double NAV_DesDistce; /// Min: 0 Max: 16777200 Units: m
    DWORD NAV_DesDistce_raw;
    double NAV_SpeedLitDistce; /// Min: 0 Max: 1500 Units: m
    BYTE NAV_SpeedLitDistce_raw;
    double NAV_SpeedLit; /// Min: 0 Max: 135 Units: km/h
    BYTE NAV_SpeedLit_raw;
    double CompassBearing; /// Min: 0 Max: 408 Units: ?
    WORD CompassBearing_raw;
} DB_MMI_NAV_HS_CAN;

#define DB_MMI_NAV_HS_CAN_SendType 1
#define DB_MMI_NAV_HS_CAN_SendRate 200
#pragma warning(disable : 4005)
#define DB_MMI_NAV_HS_CAN_$_NAV_PhWaring_$$____ 0
#define DB_MMI_NAV_HS_CAN_$_NAV_PhWaring_$$____ 1
#define DB_MMI_NAV_HS_CAN_$_NAV_PhWaring_$$___ 2
#define DB_MMI_NAV_HS_CAN_$_NAV_PhWaring_$$___ 3
#define DB_MMI_NAV_HS_CAN_$_NAV_PhWaring_$$___ 4
#define DB_MMI_NAV_HS_CAN_$_NAV_PhWaring_$$___ 5
#define DB_MMI_NAV_HS_CAN_$_NAV_PhWaring_$$___ 6
#define DB_MMI_NAV_HS_CAN_$_NAV_PhWaring_$$___ 7
#define DB_MMI_NAV_HS_CAN_$_NAV_TurnWaring_$$____ 0
#define DB_MMI_NAV_HS_CAN_$_NAV_TurnWaring_$$___ 1
#define DB_MMI_NAV_HS_CAN_$_NAV_TurnWaring_$$___ 2
#define DB_MMI_NAV_HS_CAN_$_NAV_TurnWaring_$$___ 3
#define DB_MMI_NAV_HS_CAN_$_NAV_TurnWaring_$$___ 4
#define DB_MMI_NAV_HS_CAN_$_NAV_TurnWaring_$$___ 5
#define DB_MMI_NAV_HS_CAN_$_NAV_TurnWaring_$$___ 6
#define DB_MMI_NAV_HS_CAN_$_NAV_TurnWaring_$$___ 7
#pragma warning(default : 4005)

void DB_MMI_NAV_HS_CAN_Init(DB_MMI_NAV_HS_CAN * pMsg);
int DB_MMI_NAV_HS_CAN_Transmit(DB_MMI_NAV_HS_CAN * pMsg);
int DB_MMI_NAV_HS_CAN_Transmit_raw(DB_MMI_NAV_HS_CAN * pMsg);
int DB_MMI_NAV_HS_CAN_UpdateBytesFromSignals(DB_MMI_NAV_HS_CAN * pMsg);
int DB_MMI_NAV_HS_CAN_UpdateBytesFromRawSignals(DB_MMI_NAV_HS_CAN * pMsg);
#define DB_MMI_NAV_HS_CAN_NAV_PhWaringDistce_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, 0, dPhysicalValue);
#define DB_MMI_NAV_HS_CAN_NAV_PhWaring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, 1, dPhysicalValue);
#define DB_MMI_NAV_HS_CAN_NAV_TurnWaringDistce_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, 2, dPhysicalValue);
#define DB_MMI_NAV_HS_CAN_NAV_TurnWaring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, 3, dPhysicalValue);
#define DB_MMI_NAV_HS_CAN_NAV_DesDistce_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, 4, dPhysicalValue);
#define DB_MMI_NAV_HS_CAN_NAV_SpeedLitDistce_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, 5, dPhysicalValue);
#define DB_MMI_NAV_HS_CAN_NAV_SpeedLit_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, 6, dPhysicalValue);
#define DB_MMI_NAV_HS_CAN_CompassBearing_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, 7, dPhysicalValue);
#define DB_MMI_NAV_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_MMI_NAV_HS_CAN_Index, 0)
extern int DB_MMI_XY_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double TouchState; /// Min: 0 Max: 3 Units: 
    BYTE TouchState_raw;
    double TouchPosition_Y; /// Min: 0 Max: 65535 Units: ?
    WORD TouchPosition_Y_raw;
    double TouchPosition_X; /// Min: 0 Max: 65535 Units: ?
    WORD TouchPosition_X_raw;
} DB_MMI_XY_HS_CAN;

#define DB_MMI_XY_HS_CAN_SendType 2
#pragma warning(disable : 4005)
#define DB_MMI_XY_HS_CAN_$_TouchState_$$____ 0
#define DB_MMI_XY_HS_CAN_$_TouchState_$$___ 1
#define DB_MMI_XY_HS_CAN_$_TouchState_$$___ 2
#define DB_MMI_XY_HS_CAN_$_TouchState_$$___ 3
#pragma warning(default : 4005)

void DB_MMI_XY_HS_CAN_Init(DB_MMI_XY_HS_CAN * pMsg);
int DB_MMI_XY_HS_CAN_Transmit(DB_MMI_XY_HS_CAN * pMsg);
int DB_MMI_XY_HS_CAN_Transmit_raw(DB_MMI_XY_HS_CAN * pMsg);
int DB_MMI_XY_HS_CAN_UpdateBytesFromSignals(DB_MMI_XY_HS_CAN * pMsg);
int DB_MMI_XY_HS_CAN_UpdateBytesFromRawSignals(DB_MMI_XY_HS_CAN * pMsg);
#define DB_MMI_XY_HS_CAN_TouchState_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_XY_HS_CAN_Index, 0, dPhysicalValue);
#define DB_MMI_XY_HS_CAN_TouchPosition_Y_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_XY_HS_CAN_Index, 1, dPhysicalValue);
#define DB_MMI_XY_HS_CAN_TouchPosition_X_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI_XY_HS_CAN_Index, 2, dPhysicalValue);
#define DB_MMI_XY_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_MMI_XY_HS_CAN_Index, 0)
extern int DB_MMIxTXJ_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double MMI_TXJ; /// Min: 0 Max: 9.22337203685478e+18 Units: 
    uint64 MMI_TXJ_raw;
} DB_MMIxTXJ_HS_CAN;


void DB_MMIxTXJ_HS_CAN_Init(DB_MMIxTXJ_HS_CAN * pMsg);
int DB_MMIxTXJ_HS_CAN_Transmit(DB_MMIxTXJ_HS_CAN * pMsg);
int DB_MMIxTXJ_HS_CAN_Transmit_raw(DB_MMIxTXJ_HS_CAN * pMsg);
int DB_MMIxTXJ_HS_CAN_UpdateBytesFromSignals(DB_MMIxTXJ_HS_CAN * pMsg);
int DB_MMIxTXJ_HS_CAN_UpdateBytesFromRawSignals(DB_MMIxTXJ_HS_CAN * pMsg);
#define DB_MMIxTXJ_HS_CAN_MMI_TXJ_PhysicalToRaw(dPhysicalValue) \
    (uint64 )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMIxTXJ_HS_CAN_Index, 0, dPhysicalValue);
#define DB_MMIxTXJ_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_MMIxTXJ_HS_CAN_Index, 0)
extern int DB_MMI2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double PhoneNum_12; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_12_raw;
    double PhoneNum_11; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_11_raw;
    double PhoneNum_10; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_10_raw;
    double PhoneNum_9; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_9_raw;
    double PhoneNum_8; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_8_raw;
    double PhoneNum_7; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_7_raw;
    double PhoneNum_6; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_6_raw;
    double PhoneNum_5; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_5_raw;
    double PhoneNum_4; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_4_raw;
    double PhoneNum_3; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_3_raw;
    double PhoneNum_2; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_2_raw;
    double PhoneNum_1; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNum_1_raw;
    double PhoneNumInternational_4; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNumInternational_4_raw;
    double PhoneNumInternational_3; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNumInternational_3_raw;
    double PhoneNumInternational_2; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNumInternational_2_raw;
    double PhoneNumInternational_1; /// Min: 0 Max: 9 Units: 
    BYTE PhoneNumInternational_1_raw;
} DB_MMI2_HS_CAN;

#define DB_MMI2_HS_CAN_SendType 1
#define DB_MMI2_HS_CAN_SendRate 2000

void DB_MMI2_HS_CAN_Init(DB_MMI2_HS_CAN * pMsg);
int DB_MMI2_HS_CAN_Transmit(DB_MMI2_HS_CAN * pMsg);
int DB_MMI2_HS_CAN_Transmit_raw(DB_MMI2_HS_CAN * pMsg);
int DB_MMI2_HS_CAN_UpdateBytesFromSignals(DB_MMI2_HS_CAN * pMsg);
int DB_MMI2_HS_CAN_UpdateBytesFromRawSignals(DB_MMI2_HS_CAN * pMsg);
#define DB_MMI2_HS_CAN_PhoneNum_12_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 0, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNum_11_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 1, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNum_10_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 2, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNum_9_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 3, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNum_8_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 4, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNum_7_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 5, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNum_6_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 6, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNum_5_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 7, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNum_4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 8, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNum_3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 9, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNum_2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 10, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNum_1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 11, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNumInternational_4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 12, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNumInternational_3_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 13, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNumInternational_2_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 14, dPhysicalValue);
#define DB_MMI2_HS_CAN_PhoneNumInternational_1_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, 15, dPhysicalValue);
#define DB_MMI2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_MMI2_HS_CAN_Index, 0)
extern int DB_MMI1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double BlowingRateGareSet; /// Min: 0 Max: 15 Units: 
    BYTE BlowingRateGareSet_raw;
    double OutAirModSetCmd; /// Min: 0 Max: 7 Units: 
    BYTE OutAirModSetCmd_raw;
    double TempSetCmd; /// Min: 13 Max: 44 Units:  
    BYTE TempSetCmd_raw;
    double VideoVolume; /// Min: 0 Max: 255 Units: <
    BYTE VideoVolume_raw;
    double Channel2ndVideoSourceChoose; /// Min: 0 Max: 15 Units: 
    BYTE Channel2ndVideoSourceChoose_raw;
    double Channel2ndVideoAngleChoose; /// Min: 0 Max: 15 Units: 
    BYTE Channel2ndVideoAngleChoose_raw;
    double FMRadioChannel; /// Min: 87.5 Max: 113 Units: MHz
    BYTE FMRadioChannel_raw;
    double AMRadioChannel; /// Min: 522 Max: 2817 Units: KHz
    BYTE AMRadioChannel_raw;
    double InletAirModSteCmd; /// Min: 0 Max: 3 Units: 
    BYTE InletAirModSteCmd_raw;
    double FMAMSt; /// Min: 0 Max: 15 Units: 
    BYTE FMAMSt_raw;
    double CalingSt; /// Min: 0 Max: 18.6666666666667 Units: 
    BYTE CalingSt_raw;
    double AuidoPlaySt; /// Min: 0 Max: 15 Units: 
    BYTE AuidoPlaySt_raw;
} DB_MMI1_HS_CAN;

#pragma warning(disable : 4005)
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$___ 0
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$_1_ 1
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$_2_ 2
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$_3_ 3
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$_4_ 4
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$_5_ 5
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$_6_ 6
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$_7_ 7
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$_____ 8
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$____ 9
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$____ 10
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$____ 11
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$____ 12
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$____ 13
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$____ 14
#define DB_MMI1_HS_CAN_$_BlowingRateGareSet_$$___ 15
#define DB_MMI1_HS_CAN_$_OutAirModSetCmd_$$___ 0
#define DB_MMI1_HS_CAN_$_OutAirModSetCmd_$$_____ 1
#define DB_MMI1_HS_CAN_$_OutAirModSetCmd_$$___ 2
#define DB_MMI1_HS_CAN_$_OutAirModSetCmd_$$_____ 3
#define DB_MMI1_HS_CAN_$_OutAirModSetCmd_$$___ 4
#define DB_MMI1_HS_CAN_$_OutAirModSetCmd_$$_____ 5
#define DB_MMI1_HS_CAN_$_OutAirModSetCmd_$$_______ 6
#define DB_MMI1_HS_CAN_$_OutAirModSetCmd_$$___ 7
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$__________ 0
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____1 1
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____2 2
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____3 3
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____4 4
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____5 5
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____6 6
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____7 7
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____8 8
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____9 9
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____10 10
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____11 11
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____12 12
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____13 13
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$____14 14
#define DB_MMI1_HS_CAN_$_Channel2ndVideoSourceChoose_$$___ 15
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$_____ 0
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$___ 1
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$___ 2
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$______ 3
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$______ 4
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$_______ 5
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$_360__ 6
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$_____ 7
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$___ 8
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$___ 9
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$___ 10
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$___ 11
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$___ 12
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$___ 13
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$___ 14
#define DB_MMI1_HS_CAN_$_Channel2ndVideoAngleChoose_$$___ 15
#define DB_MMI1_HS_CAN_$_InletAirModSteCmd_$$____ 0
#define DB_MMI1_HS_CAN_$_InletAirModSteCmd_$$____ 1
#define DB_MMI1_HS_CAN_$_InletAirModSteCmd_$$___ 2
#define DB_MMI1_HS_CAN_$_InletAirModSteCmd_$$___ 3
#define DB_MMI1_HS_CAN_$_FMAMSt_$$_FM1 0
#define DB_MMI1_HS_CAN_$_FMAMSt_$$_FM2 1
#define DB_MMI1_HS_CAN_$_FMAMSt_$$_FM3 2
#define DB_MMI1_HS_CAN_$_FMAMSt_$$_AM1 3
#define DB_MMI1_HS_CAN_$_FMAMSt_$$_AM2 4
#define DB_MMI1_HS_CAN_$_FMAMSt_$$_AM3 5
#define DB_MMI1_HS_CAN_$_FMAMSt_$$___ 6
#define DB_MMI1_HS_CAN_$_FMAMSt_$$___ 7
#define DB_MMI1_HS_CAN_$_FMAMSt_$$___ 8
#define DB_MMI1_HS_CAN_$_FMAMSt_$$___ 9
#define DB_MMI1_HS_CAN_$_FMAMSt_$$___ 10
#define DB_MMI1_HS_CAN_$_FMAMSt_$$___ 11
#define DB_MMI1_HS_CAN_$_FMAMSt_$$___ 12
#define DB_MMI1_HS_CAN_$_FMAMSt_$$___ 13
#define DB_MMI1_HS_CAN_$_FMAMSt_$$_Description_for_the_value__0xE_ 14
#define DB_MMI1_HS_CAN_$_CalingSt_$$_NoCalling 0
#define DB_MMI1_HS_CAN_$_CalingSt_$$____ 1
#define DB_MMI1_HS_CAN_$_CalingSt_$$____ 2
#define DB_MMI1_HS_CAN_$_CalingSt_$$____ 3
#define DB_MMI1_HS_CAN_$_CalingSt_$$___ 4
#define DB_MMI1_HS_CAN_$_CalingSt_$$___ 5
#define DB_MMI1_HS_CAN_$_CalingSt_$$___ 6
#define DB_MMI1_HS_CAN_$_CalingSt_$$___ 7
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$_Radio 0
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$_BT 1
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$_CD 2
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$_USB 3
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$_Video 4
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$_AUX_User 5
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$_AUX_TXJ 6
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$_AUX_CTW 7
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$____ 8
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$____ 9
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$____ 10
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$____ 11
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$____ 12
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$____ 13
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$___ 14
#define DB_MMI1_HS_CAN_$_AuidoPlaySt_$$___ 15
#pragma warning(default : 4005)

void DB_MMI1_HS_CAN_Init(DB_MMI1_HS_CAN * pMsg);
int DB_MMI1_HS_CAN_Transmit(DB_MMI1_HS_CAN * pMsg);
int DB_MMI1_HS_CAN_Transmit_raw(DB_MMI1_HS_CAN * pMsg);
int DB_MMI1_HS_CAN_UpdateBytesFromSignals(DB_MMI1_HS_CAN * pMsg);
int DB_MMI1_HS_CAN_UpdateBytesFromRawSignals(DB_MMI1_HS_CAN * pMsg);
#define DB_MMI1_HS_CAN_BlowingRateGareSet_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_MMI1_HS_CAN_OutAirModSetCmd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 1, dPhysicalValue);
#define DB_MMI1_HS_CAN_TempSetCmd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 2, dPhysicalValue);
#define DB_MMI1_HS_CAN_VideoVolume_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 3, dPhysicalValue);
#define DB_MMI1_HS_CAN_Channel2ndVideoSourceChoose_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 4, dPhysicalValue);
#define DB_MMI1_HS_CAN_Channel2ndVideoAngleChoose_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 5, dPhysicalValue);
#define DB_MMI1_HS_CAN_FMRadioChannel_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 6, dPhysicalValue);
#define DB_MMI1_HS_CAN_AMRadioChannel_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 7, dPhysicalValue);
#define DB_MMI1_HS_CAN_InletAirModSteCmd_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 8, dPhysicalValue);
#define DB_MMI1_HS_CAN_FMAMSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 9, dPhysicalValue);
#define DB_MMI1_HS_CAN_CalingSt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 10, dPhysicalValue);
#define DB_MMI1_HS_CAN_AuidoPlaySt_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, 11, dPhysicalValue);
#define DB_MMI1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_MMI1_HS_CAN_Index, 0)
extern int DB_NM_GW_HS_CAN_db111_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double GW_NM_Steep_Ind; /// Min: 0 Max: 1 Units: 
    BYTE GW_NM_Steep_Ind_raw;
    double GW_NM_Sleep_Ack; /// Min: 0 Max: 1 Units: 
    BYTE GW_NM_Sleep_Ack_raw;
    double GW_NM_Ring; /// Min: 0 Max: 1 Units: 
    BYTE GW_NM_Ring_raw;
    double GW_NM_Limphone; /// Min: 0 Max: 1 Units: 
    BYTE GW_NM_Limphone_raw;
    double GW_NM_DA; /// Min: -128 Max: 127 Units: 
    BYTE GW_NM_DA_raw;
    double GW_NM_Alive; /// Min: 0 Max: 1 Units: 
    BYTE GW_NM_Alive_raw;
} DB_NM_GW_HS_CAN_db111;

#pragma warning(disable : 4005)
#define DB_NM_GW_HS_CAN_db111_$_GW_NM_Steep_Ind_$$_FALSE 0
#define DB_NM_GW_HS_CAN_db111_$_GW_NM_Steep_Ind_$$_TRUE 1
#define DB_NM_GW_HS_CAN_db111_$_GW_NM_Sleep_Ack_$$_FALSE 0
#define DB_NM_GW_HS_CAN_db111_$_GW_NM_Sleep_Ack_$$_TRUE 1
#define DB_NM_GW_HS_CAN_db111_$_GW_NM_Ring_$$_FALSE 0
#define DB_NM_GW_HS_CAN_db111_$_GW_NM_Ring_$$_TRUE 1
#define DB_NM_GW_HS_CAN_db111_$_GW_NM_Limphone_$$_FALSE 0
#define DB_NM_GW_HS_CAN_db111_$_GW_NM_Limphone_$$_TRUE 1
#define DB_NM_GW_HS_CAN_db111_$_GW_NM_Alive_$$_FALSE 0
#define DB_NM_GW_HS_CAN_db111_$_GW_NM_Alive_$$_TRUE 1
#pragma warning(default : 4005)

void DB_NM_GW_HS_CAN_db111_Init(DB_NM_GW_HS_CAN_db111 * pMsg);
int DB_NM_GW_HS_CAN_db111_Transmit(DB_NM_GW_HS_CAN_db111 * pMsg);
int DB_NM_GW_HS_CAN_db111_Transmit_raw(DB_NM_GW_HS_CAN_db111 * pMsg);
int DB_NM_GW_HS_CAN_db111_UpdateBytesFromSignals(DB_NM_GW_HS_CAN_db111 * pMsg);
int DB_NM_GW_HS_CAN_db111_UpdateBytesFromRawSignals(DB_NM_GW_HS_CAN_db111 * pMsg);
#define DB_NM_GW_HS_CAN_db111_GW_NM_Steep_Ind_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, 0, dPhysicalValue);
#define DB_NM_GW_HS_CAN_db111_GW_NM_Sleep_Ack_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, 1, dPhysicalValue);
#define DB_NM_GW_HS_CAN_db111_GW_NM_Ring_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, 2, dPhysicalValue);
#define DB_NM_GW_HS_CAN_db111_GW_NM_Limphone_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, 3, dPhysicalValue);
#define DB_NM_GW_HS_CAN_db111_GW_NM_DA_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, 4, dPhysicalValue);
#define DB_NM_GW_HS_CAN_db111_GW_NM_Alive_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, 5, dPhysicalValue);
#define DB_NM_GW_HS_CAN_db111_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_NM_GW_HS_CAN_db111_Index, 0)
extern int DB_DMI_GW_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double SPN_Mode; /// Min: 0 Max: 1 Units: 
    BYTE SPN_Mode_raw;
    double OccuranceCount; /// Min: 0 Max: 126 Units: 
    BYTE OccuranceCount_raw;
    double SPN_HighBit; /// Min: 0 Max: 7 Units: 
    BYTE SPN_HighBit_raw;
    double FMI; /// Min: 0 Max: 31 Units: 
    BYTE FMI_raw;
    double SPN_Num; /// Min: 0 Max: 65535 Units: 
    WORD SPN_Num_raw;
    double MalfunctionIndicatroLamp; /// Min: 0 Max: 3 Units: 
    BYTE MalfunctionIndicatroLamp_raw;
    double RedStopLamp; /// Min: 0 Max: 3 Units: 
    BYTE RedStopLamp_raw;
    double ProtectLamp; /// Min: 0 Max: 3 Units: 
    BYTE ProtectLamp_raw;
    double AmberWarningLamp; /// Min: 0 Max: 3 Units: 
    BYTE AmberWarningLamp_raw;
} DB_DMI_GW_HS_CAN;

#define DB_DMI_GW_HS_CAN_SendType 1
#define DB_DMI_GW_HS_CAN_SendRate 1000
#pragma warning(disable : 4005)
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN___ 0
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN___ 1
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN___ 2
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN___ 3
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN___ 4
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN___ 5
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN___ 6
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN___ 7
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN____ 8
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN____ 9
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN____ 10
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN____ 11
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN____ 12
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN____ 13
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN____ 14
#define DB_DMI_GW_HS_CAN_$_SPN_Num_$$_SPN____ 15
#define DB_DMI_GW_HS_CAN_$_MalfunctionIndicatroLamp_$$____ 0
#define DB_DMI_GW_HS_CAN_$_MalfunctionIndicatroLamp_$$___ 1
#define DB_DMI_GW_HS_CAN_$_MalfunctionIndicatroLamp_$$___ 2
#define DB_DMI_GW_HS_CAN_$_MalfunctionIndicatroLamp_$$___ 3
#define DB_DMI_GW_HS_CAN_$_RedStopLamp_$$____ 0
#define DB_DMI_GW_HS_CAN_$_RedStopLamp_$$___ 1
#define DB_DMI_GW_HS_CAN_$_RedStopLamp_$$___ 2
#define DB_DMI_GW_HS_CAN_$_RedStopLamp_$$___ 3
#define DB_DMI_GW_HS_CAN_$_ProtectLamp_$$____ 0
#define DB_DMI_GW_HS_CAN_$_ProtectLamp_$$___ 1
#define DB_DMI_GW_HS_CAN_$_ProtectLamp_$$___ 2
#define DB_DMI_GW_HS_CAN_$_ProtectLamp_$$___ 3
#define DB_DMI_GW_HS_CAN_$_AmberWarningLamp_$$____ 0
#define DB_DMI_GW_HS_CAN_$_AmberWarningLamp_$$___ 1
#define DB_DMI_GW_HS_CAN_$_AmberWarningLamp_$$___ 2
#define DB_DMI_GW_HS_CAN_$_AmberWarningLamp_$$___ 3
#pragma warning(default : 4005)

void DB_DMI_GW_HS_CAN_Init(DB_DMI_GW_HS_CAN * pMsg);
int DB_DMI_GW_HS_CAN_Transmit(DB_DMI_GW_HS_CAN * pMsg);
int DB_DMI_GW_HS_CAN_Transmit_raw(DB_DMI_GW_HS_CAN * pMsg);
int DB_DMI_GW_HS_CAN_UpdateBytesFromSignals(DB_DMI_GW_HS_CAN * pMsg);
int DB_DMI_GW_HS_CAN_UpdateBytesFromRawSignals(DB_DMI_GW_HS_CAN * pMsg);
#define DB_DMI_GW_HS_CAN_SPN_Mode_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, 0, dPhysicalValue);
#define DB_DMI_GW_HS_CAN_OccuranceCount_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, 1, dPhysicalValue);
#define DB_DMI_GW_HS_CAN_SPN_HighBit_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, 2, dPhysicalValue);
#define DB_DMI_GW_HS_CAN_FMI_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, 3, dPhysicalValue);
#define DB_DMI_GW_HS_CAN_SPN_Num_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, 4, dPhysicalValue);
#define DB_DMI_GW_HS_CAN_MalfunctionIndicatroLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, 5, dPhysicalValue);
#define DB_DMI_GW_HS_CAN_RedStopLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, 6, dPhysicalValue);
#define DB_DMI_GW_HS_CAN_ProtectLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, 7, dPhysicalValue);
#define DB_DMI_GW_HS_CAN_AmberWarningLamp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, 8, dPhysicalValue);
#define DB_DMI_GW_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_DMI_GW_HS_CAN_Index, 0)
extern int DB_RouteSG_PT1_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double EngineOilPressure; /// Min: 0 Max: 1000 Units: + (4,0) [0|1000] "kPa

    BYTE EngineOilPressure_raw;
} DB_RouteSG_PT1_HS_CAN;


void DB_RouteSG_PT1_HS_CAN_Init(DB_RouteSG_PT1_HS_CAN * pMsg);
int DB_RouteSG_PT1_HS_CAN_Transmit(DB_RouteSG_PT1_HS_CAN * pMsg);
int DB_RouteSG_PT1_HS_CAN_Transmit_raw(DB_RouteSG_PT1_HS_CAN * pMsg);
int DB_RouteSG_PT1_HS_CAN_UpdateBytesFromSignals(DB_RouteSG_PT1_HS_CAN * pMsg);
int DB_RouteSG_PT1_HS_CAN_UpdateBytesFromRawSignals(DB_RouteSG_PT1_HS_CAN * pMsg);
#define DB_RouteSG_PT1_HS_CAN_EngineOilPressure_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_RouteSG_PT1_HS_CAN_Index, 0, dPhysicalValue);
#define DB_RouteSG_PT1_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_RouteSG_PT1_HS_CAN_Index, 0)
extern int DB_RouteSG_ChasOil_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double OilTemperature_T; /// Min: -273 Max: 1735 Units: + (0.03125,-273) [-273|1735] "

    WORD OilTemperature_T_raw;
} DB_RouteSG_ChasOil_HS_CAN;


void DB_RouteSG_ChasOil_HS_CAN_Init(DB_RouteSG_ChasOil_HS_CAN * pMsg);
int DB_RouteSG_ChasOil_HS_CAN_Transmit(DB_RouteSG_ChasOil_HS_CAN * pMsg);
int DB_RouteSG_ChasOil_HS_CAN_Transmit_raw(DB_RouteSG_ChasOil_HS_CAN * pMsg);
int DB_RouteSG_ChasOil_HS_CAN_UpdateBytesFromSignals(DB_RouteSG_ChasOil_HS_CAN * pMsg);
int DB_RouteSG_ChasOil_HS_CAN_UpdateBytesFromRawSignals(DB_RouteSG_ChasOil_HS_CAN * pMsg);
#define DB_RouteSG_ChasOil_HS_CAN_OilTemperature_T_PhysicalToRaw(dPhysicalValue) \
    (WORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_RouteSG_ChasOil_HS_CAN_Index, 0, dPhysicalValue);
#define DB_RouteSG_ChasOil_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_RouteSG_ChasOil_HS_CAN_Index, 0)
extern int DB_RouteSG_LNG_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DoubleFuelActualMod; /// Min: 0 Max: 255 Units: 
    BYTE DoubleFuelActualMod_raw;
} DB_RouteSG_LNG_HS_CAN;

#pragma warning(disable : 4005)
#define DB_RouteSG_LNG_HS_CAN_$_DoubleFuelActualMod_$$_0______ 0
#define DB_RouteSG_LNG_HS_CAN_$_DoubleFuelActualMod_$$_1______ 1
#pragma warning(default : 4005)

void DB_RouteSG_LNG_HS_CAN_Init(DB_RouteSG_LNG_HS_CAN * pMsg);
int DB_RouteSG_LNG_HS_CAN_Transmit(DB_RouteSG_LNG_HS_CAN * pMsg);
int DB_RouteSG_LNG_HS_CAN_Transmit_raw(DB_RouteSG_LNG_HS_CAN * pMsg);
int DB_RouteSG_LNG_HS_CAN_UpdateBytesFromSignals(DB_RouteSG_LNG_HS_CAN * pMsg);
int DB_RouteSG_LNG_HS_CAN_UpdateBytesFromRawSignals(DB_RouteSG_LNG_HS_CAN * pMsg);
#define DB_RouteSG_LNG_HS_CAN_DoubleFuelActualMod_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_RouteSG_LNG_HS_CAN_Index, 0, dPhysicalValue);
#define DB_RouteSG_LNG_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_RouteSG_LNG_HS_CAN_Index, 0)
extern int DB_RouteSG_DFS_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double DoubleFuelModFuelEco; /// Min: 0 Max: 2147483647.6 Units: L
    DWORD DoubleFuelModFuelEco_raw;
    double DieseModEco; /// Min: 0 Max: 2147483647.5 Units: L
    DWORD DieseModEco_raw;
} DB_RouteSG_DFS_HS_CAN;


void DB_RouteSG_DFS_HS_CAN_Init(DB_RouteSG_DFS_HS_CAN * pMsg);
int DB_RouteSG_DFS_HS_CAN_Transmit(DB_RouteSG_DFS_HS_CAN * pMsg);
int DB_RouteSG_DFS_HS_CAN_Transmit_raw(DB_RouteSG_DFS_HS_CAN * pMsg);
int DB_RouteSG_DFS_HS_CAN_UpdateBytesFromSignals(DB_RouteSG_DFS_HS_CAN * pMsg);
int DB_RouteSG_DFS_HS_CAN_UpdateBytesFromRawSignals(DB_RouteSG_DFS_HS_CAN * pMsg);
#define DB_RouteSG_DFS_HS_CAN_DoubleFuelModFuelEco_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_RouteSG_DFS_HS_CAN_Index, 0, dPhysicalValue);
#define DB_RouteSG_DFS_HS_CAN_DieseModEco_PhysicalToRaw(dPhysicalValue) \
    (DWORD )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_RouteSG_DFS_HS_CAN_Index, 1, dPhysicalValue);
#define DB_RouteSG_DFS_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_RouteSG_DFS_HS_CAN_Index, 0)
extern int DB_switch2_HS_CAN_Index;
typedef struct {
    GenericMessage MessageData; /// Message Data
    MessageStats Statistics; /// Message Statistics
    int iDefaultPeriodMilliseconds; /// Default Message Period
    double Ignition_OFF; /// Min: 0 Max: 3 Units: 
    BYTE Ignition_OFF_raw;
    double Ignition_IN; /// Min: 0 Max: 3 Units: 
    BYTE Ignition_IN_raw;
    double VolumeInc; /// Min: 0 Max: 3 Units: 
    BYTE VolumeInc_raw;
    double ReservedSW4; /// Min: 0 Max: 3 Units: 
    BYTE ReservedSW4_raw;
    double OK; /// Min: 0 Max: 3 Units: 
    BYTE OK_raw;
    double MenuRight; /// Min: 0 Max: 3 Units: 
    BYTE MenuRight_raw;
    double MenuUp; /// Min: 0 Max: 3 Units: 
    BYTE MenuUp_raw;
    double MenuLeft; /// Min: 0 Max: 3 Units: 
    BYTE MenuLeft_raw;
    double MenuDown; /// Min: 0 Max: 3 Units: 
    BYTE MenuDown_raw;
    double Ignition_START; /// Min: 0 Max: 3 Units: 
    BYTE Ignition_START_raw;
    double Ignition_ON; /// Min: 0 Max: 3 Units: 
    BYTE Ignition_ON_raw;
    double Ignition_ACC; /// Min: 0 Max: 3 Units: 
    BYTE Ignition_ACC_raw;
    double ESC; /// Min: 0 Max: 3 Units: 
    BYTE ESC_raw;
    double ChannelDec; /// Min: 0 Max: 3 Units: 
    BYTE ChannelDec_raw;
    double BluetoothPhone; /// Min: 0 Max: 3 Units: 
    BYTE BluetoothPhone_raw;
    double ChannelInc; /// Min: 0 Max: 3 Units: 
    BYTE ChannelInc_raw;
    double VoiceRequest; /// Min: 0 Max: 3 Units: 
    BYTE VoiceRequest_raw;
    double IC_or_MP5; /// Min: 0 Max: 3 Units: 
    BYTE IC_or_MP5_raw;
    double Mode; /// Min: 0 Max: 3 Units: 
    BYTE Mode_raw;
    double VolumeDec; /// Min: 0 Max: 3 Units: 
    BYTE VolumeDec_raw;
} DB_switch2_HS_CAN;

#pragma warning(disable : 4005)
#define DB_switch2_HS_CAN_$_Ignition_OFF_$$___ 0
#define DB_switch2_HS_CAN_$_Ignition_OFF_$$___ 1
#define DB_switch2_HS_CAN_$_Ignition_OFF_$$___ 2
#define DB_switch2_HS_CAN_$_Ignition_OFF_$$___ 3
#define DB_switch2_HS_CAN_$_Ignition_IN_$$___ 0
#define DB_switch2_HS_CAN_$_Ignition_IN_$$___ 1
#define DB_switch2_HS_CAN_$_Ignition_IN_$$___ 2
#define DB_switch2_HS_CAN_$_Ignition_IN_$$___ 3
#define DB_switch2_HS_CAN_$_VolumeInc_$$___ 0
#define DB_switch2_HS_CAN_$_VolumeInc_$$___ 1
#define DB_switch2_HS_CAN_$_VolumeInc_$$___ 2
#define DB_switch2_HS_CAN_$_VolumeInc_$$___ 3
#define DB_switch2_HS_CAN_$_ReservedSW4_$$___ 0
#define DB_switch2_HS_CAN_$_ReservedSW4_$$___ 1
#define DB_switch2_HS_CAN_$_ReservedSW4_$$___ 2
#define DB_switch2_HS_CAN_$_ReservedSW4_$$___ 3
#define DB_switch2_HS_CAN_$_OK_$$___ 0
#define DB_switch2_HS_CAN_$_OK_$$___ 1
#define DB_switch2_HS_CAN_$_OK_$$___ 2
#define DB_switch2_HS_CAN_$_OK_$$___ 3
#define DB_switch2_HS_CAN_$_MenuRight_$$___ 0
#define DB_switch2_HS_CAN_$_MenuRight_$$___ 1
#define DB_switch2_HS_CAN_$_MenuRight_$$___ 2
#define DB_switch2_HS_CAN_$_MenuRight_$$___ 3
#define DB_switch2_HS_CAN_$_MenuUp_$$___ 0
#define DB_switch2_HS_CAN_$_MenuUp_$$___ 1
#define DB_switch2_HS_CAN_$_MenuUp_$$___ 2
#define DB_switch2_HS_CAN_$_MenuUp_$$___ 3
#define DB_switch2_HS_CAN_$_MenuLeft_$$___ 0
#define DB_switch2_HS_CAN_$_MenuLeft_$$___ 1
#define DB_switch2_HS_CAN_$_MenuLeft_$$___ 2
#define DB_switch2_HS_CAN_$_MenuLeft_$$___ 3
#define DB_switch2_HS_CAN_$_MenuDown_$$___ 0
#define DB_switch2_HS_CAN_$_MenuDown_$$___ 1
#define DB_switch2_HS_CAN_$_MenuDown_$$___ 2
#define DB_switch2_HS_CAN_$_MenuDown_$$___ 3
#define DB_switch2_HS_CAN_$_Ignition_START_$$___ 0
#define DB_switch2_HS_CAN_$_Ignition_START_$$___ 1
#define DB_switch2_HS_CAN_$_Ignition_START_$$___ 2
#define DB_switch2_HS_CAN_$_Ignition_START_$$___ 3
#define DB_switch2_HS_CAN_$_Ignition_ON_$$___ 0
#define DB_switch2_HS_CAN_$_Ignition_ON_$$___ 1
#define DB_switch2_HS_CAN_$_Ignition_ON_$$___ 2
#define DB_switch2_HS_CAN_$_Ignition_ON_$$___ 3
#define DB_switch2_HS_CAN_$_Ignition_ACC_$$___ 0
#define DB_switch2_HS_CAN_$_Ignition_ACC_$$___ 1
#define DB_switch2_HS_CAN_$_Ignition_ACC_$$___ 2
#define DB_switch2_HS_CAN_$_Ignition_ACC_$$___ 3
#define DB_switch2_HS_CAN_$_ESC_$$___ 0
#define DB_switch2_HS_CAN_$_ESC_$$___ 1
#define DB_switch2_HS_CAN_$_ESC_$$___ 2
#define DB_switch2_HS_CAN_$_ESC_$$___ 3
#define DB_switch2_HS_CAN_$_ChannelDec_$$___ 0
#define DB_switch2_HS_CAN_$_ChannelDec_$$___ 1
#define DB_switch2_HS_CAN_$_ChannelDec_$$___ 2
#define DB_switch2_HS_CAN_$_ChannelDec_$$___ 3
#define DB_switch2_HS_CAN_$_BluetoothPhone_$$___ 0
#define DB_switch2_HS_CAN_$_BluetoothPhone_$$___ 1
#define DB_switch2_HS_CAN_$_BluetoothPhone_$$___ 2
#define DB_switch2_HS_CAN_$_BluetoothPhone_$$___ 3
#define DB_switch2_HS_CAN_$_ChannelInc_$$___ 0
#define DB_switch2_HS_CAN_$_ChannelInc_$$___ 1
#define DB_switch2_HS_CAN_$_ChannelInc_$$___ 2
#define DB_switch2_HS_CAN_$_ChannelInc_$$___ 3
#define DB_switch2_HS_CAN_$_VoiceRequest_$$___ 0
#define DB_switch2_HS_CAN_$_VoiceRequest_$$___ 1
#define DB_switch2_HS_CAN_$_VoiceRequest_$$___ 2
#define DB_switch2_HS_CAN_$_VoiceRequest_$$___ 3
#define DB_switch2_HS_CAN_$_IC_or_MP5_$$___ 0
#define DB_switch2_HS_CAN_$_IC_or_MP5_$$___ 1
#define DB_switch2_HS_CAN_$_IC_or_MP5_$$___ 2
#define DB_switch2_HS_CAN_$_IC_or_MP5_$$___ 3
#define DB_switch2_HS_CAN_$_Mode_$$___ 0
#define DB_switch2_HS_CAN_$_Mode_$$___ 1
#define DB_switch2_HS_CAN_$_Mode_$$___ 2
#define DB_switch2_HS_CAN_$_Mode_$$___ 3
#define DB_switch2_HS_CAN_$_VolumeDec_$$___ 0
#define DB_switch2_HS_CAN_$_VolumeDec_$$___ 1
#define DB_switch2_HS_CAN_$_VolumeDec_$$___ 2
#define DB_switch2_HS_CAN_$_VolumeDec_$$___ 3
#pragma warning(default : 4005)

void DB_switch2_HS_CAN_Init(DB_switch2_HS_CAN * pMsg);
int DB_switch2_HS_CAN_Transmit(DB_switch2_HS_CAN * pMsg);
int DB_switch2_HS_CAN_Transmit_raw(DB_switch2_HS_CAN * pMsg);
int DB_switch2_HS_CAN_UpdateBytesFromSignals(DB_switch2_HS_CAN * pMsg);
int DB_switch2_HS_CAN_UpdateBytesFromRawSignals(DB_switch2_HS_CAN * pMsg);
#define DB_switch2_HS_CAN_Ignition_OFF_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 0, dPhysicalValue);
#define DB_switch2_HS_CAN_Ignition_IN_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 1, dPhysicalValue);
#define DB_switch2_HS_CAN_VolumeInc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 2, dPhysicalValue);
#define DB_switch2_HS_CAN_ReservedSW4_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 3, dPhysicalValue);
#define DB_switch2_HS_CAN_OK_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 4, dPhysicalValue);
#define DB_switch2_HS_CAN_MenuRight_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 5, dPhysicalValue);
#define DB_switch2_HS_CAN_MenuUp_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 6, dPhysicalValue);
#define DB_switch2_HS_CAN_MenuLeft_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 7, dPhysicalValue);
#define DB_switch2_HS_CAN_MenuDown_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 8, dPhysicalValue);
#define DB_switch2_HS_CAN_Ignition_START_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 9, dPhysicalValue);
#define DB_switch2_HS_CAN_Ignition_ON_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 10, dPhysicalValue);
#define DB_switch2_HS_CAN_Ignition_ACC_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 11, dPhysicalValue);
#define DB_switch2_HS_CAN_ESC_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 12, dPhysicalValue);
#define DB_switch2_HS_CAN_ChannelDec_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 13, dPhysicalValue);
#define DB_switch2_HS_CAN_BluetoothPhone_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 14, dPhysicalValue);
#define DB_switch2_HS_CAN_ChannelInc_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 15, dPhysicalValue);
#define DB_switch2_HS_CAN_VoiceRequest_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 16, dPhysicalValue);
#define DB_switch2_HS_CAN_IC_or_MP5_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 17, dPhysicalValue);
#define DB_switch2_HS_CAN_Mode_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 18, dPhysicalValue);
#define DB_switch2_HS_CAN_VolumeDec_PhysicalToRaw(dPhysicalValue) \
    (BYTE )CM_SignalPhysicalToRaw(g_uiHandle, 0, DB_switch2_HS_CAN_Index, 19, dPhysicalValue);
#define DB_switch2_HS_CAN_ClearStats() \
    CM_GetSetValue(g_uiHandle, CM_GETSET_TX_STATS_CLR, DB_switch2_HS_CAN_Index, 0)

#endif // VSPY_GENERATED_HEADER
