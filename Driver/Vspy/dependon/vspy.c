// vspy generated implementation file
#include "../vspy.h"
#include "stdarg.h"

void * g_uiHandle = NULL;
unsigned char g_bUseExtendedIdBit = 0;
long g_lStartDelay = 0;

#define MIN_VSPY_H_VERSION     1

int getStartDelay()
{
    return g_lStartDelay;
}

void setStartDelay(int delay)
{
    if ((delay < 0) || (delay > 99999))
    {
        Printf("setStartDelay was passed an invalid value: %d\n", delay);
        delay = 0;
    }
    g_lStartDelay = delay;
}

int CM_GetVSPY_C_H_Version()
{
    return MIN_VSPY_H_VERSION;
}

void SetUseExtendedIdBit()
{
    g_bUseExtendedIdBit = 1;
}

int GetMessageName(int iMessageId, int iMessageContext, char * pName, int iBufferSize)
{
    int nLen;
    wchar_t *pWideBuffer = malloc(iBufferSize * sizeof(wchar_t));
    if (isExtId(iMessageId))
        iMessageId = mkStdId(iMessageId);
    if (CM_GetMessageName(g_uiHandle, iMessageId, iMessageContext, pWideBuffer, iBufferSize))
    {
        nLen = WideCharToMultiByte(0, 0, pWideBuffer, (int)wcslen(pWideBuffer), NULL, 0, NULL, NULL);
        WideCharToMultiByte(0, 0, pWideBuffer, (int)wcslen(pWideBuffer), pName, nLen, NULL, NULL);
        pName[nLen] = 0;
        free(pWideBuffer);
        return 1;
    }
    free(pWideBuffer);
    return 0;
}

int GetMessageNameW(int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize)
{
    if (isExtId(iMessageId))
        iMessageId = mkStdId(iMessageId);
    return CM_GetMessageName(g_uiHandle, iMessageId, iMessageContext, pName, iBufferSize);
}

int SpyViewGetCount()
{
    int temp = 0;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWCOUNT, 0, &temp);
    return temp;
}

int SpyViewGetType(void* pView)
{
    stGetViewTypeArgs args;
    args.InForm = pView;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWTYPE, 0, &args);
    return args.OutType;
}

void* SpyViewGetHandle(int index){

    void* temp = NULL;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWHANDLE, index, &temp);
    return temp;
}

void SpyViewShow(void* pView)
{
    CM_GetSetValue(g_uiHandle, CM_SET_SHOWVIEW, 0, pView);
}

void SpyViewHide(void* pView)
{
    CM_GetSetValue(g_uiHandle, CM_SET_HIDEVIEW, 0, pView);
}

int SpyViewIsVisible(void* pView)
{
    stGetViewIsVisibleArgs args;
    args.InForm = pView;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWISVISIBLE, 0, &args);
    return args.OutVisible;
}

void* SpyViewShowByType(int type)
{
    void* temp = NULL;
    CM_GetSetValue(g_uiHandle, CM_SET_SHOWVIEWBYTYPE, type, &temp);
    return temp;
}

void* SpyViewGetProcAddress(void* pView, const char* szProcName)
{
    stGetViewProcAddressArgs args;
    args.InForm = pView;
    args.InFunctionName = szProcName;
    args.OutFunctionPtr = NULL;
    CM_GetSetValue(g_uiHandle, CM_GET_VIEWPROCADDRESS, 0, &args);
    return args.OutFunctionPtr;
}

double AS_Get(int index)
{
    double dTemp;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL, index, &dTemp);
    return dTemp;
}

void AS_Set(int index, double dValue)
{
    double dTemp = dValue;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL, index, &dTemp);
}

struct AppSigValue
{
    int nOffset;
    double dValue;
};

double AS_GetAt(int index, int element)
{
    struct AppSigValue sVal;
    if (element == 0)
        return AS_Get(index);
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_AT, index, &sVal);
    return sVal.dValue;
}

void AS_SetAt(int index, int element, double dValue)
{
    struct AppSigValue sVal;
    if (element == 0)
    {
        AS_Set(index, dValue);
        return;
    }
    sVal.dValue = dValue;
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_AT, index, &sVal);
}

int AS_GetText(int nIndex, void * szValue, int nLength)
{
    wchar_t szTemp[1024];
    int nLen = nLength;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_TEXT, nIndex, szTemp);
    if (nLen <= 0)
        nLen = min(WideCharToMultiByte(0, 0, szTemp, (int)wcslen(szTemp), NULL, 0, NULL, NULL), 1023);
    if (wcsncmp(szTemp, L"#0x", 3) == 0)  // Binary
    {
        wchar_t szByte[] = L"00";
        int nByte;
        nLen = ((int)wcslen(szTemp) - 3) / 2;
        for (nByte = 0; nByte < nLen; ++nByte)
        {
            szByte[0] = szTemp[3 + nByte * 2];
            szByte[1] = szTemp[4 + nByte * 2];
            *((BYTE *)szValue + nByte) = (BYTE)wcstol(szByte, NULL, 16);
        }
        return nLen;
    }
    WideCharToMultiByte(0, 0, szTemp, (int)wcslen(szTemp), (char *)szValue, nLen, NULL, NULL);
    *((char *)szValue + nLen) = 0;
    return (int)strlen(szValue);
}

int AS_SetText(int nIndex, void * szValue, int nLength)
{
    BOOL bIsBinary = 0;
    wchar_t szTemp[1024];
    int nLen = nLength;
    if (nLen <= 0)
        nLen = min(MultiByteToWideChar(0, 0, (char *)szValue, (int)strlen(szValue), NULL, 0), 1023);
    else
    {
        int nByte;
        wcscpy_s(szTemp, 4, L"#0x");
        for (nByte = 0; nByte < nLength; ++nByte)
        {
            if ((*((BYTE *)szValue) + nByte) < 32)
                bIsBinary = 1;
            swprintf(szTemp + (nByte * 2) + 3, _countof(szTemp) - (nByte * 2) - 3, L"%02x",
                     (*((BYTE *)szValue) + nByte));
        }
    }
    if (bIsBinary)
    {
        CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, nIndex, szTemp);
        return nLength;
    }
    else
    {
        MultiByteToWideChar(0, 0, szValue, (int)strlen(szValue), szTemp, nLen);
        szTemp[nLen] = 0;
        CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT, nIndex, szTemp);
        return (int)strlen(szValue);
    }
}

int AS_GetTextW(int index, wchar_t * szValue)
{
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_TEXT, index, szValue);
    return (int)wcslen(szValue);
}

struct AppSigTextValue
{
    int nOffset;
    wchar_t *szValue;
};

int AS_GetTextAtW(int index, int element, wchar_t * szValue)
{
    struct AppSigTextValue sVal;
    sVal.szValue = szValue;
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_GET_APP_SIGNAL_TEXT_AT, index, &sVal);
    return (int)wcslen(szValue);
}

int AS_SetTextAtW(int index, int element, wchar_t * szValue)
{
    struct AppSigTextValue sVal;
    sVal.szValue = szValue;
    sVal.nOffset = element;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_APP_SIGNAL_TEXT_AT, index, &sVal);
    return (int)wcslen(szValue);
}

int CanNetworksInUse[] = {
    0,  //HS_CAN
    1,  //MS_CAN
};

int Spy_NetworksInUse()
{
    return _countof(CanNetworksInUse);
}

int Spy_TranslateNetwork(int nNetworkOffset)
{
    if ((nNetworkOffset <= 1) || (nNetworkOffset > Spy_NetworksInUse()))
        return CanNetworksInUse[0] + 1;
    else
        return CanNetworksInUse[nNetworkOffset - 1] + 1;
}
int Spy_UntranslateNetwork(int nNetwork)
{
    int can;
    for (can = 0; can < Spy_NetworksInUse(); ++can)
    {
        if (CanNetworksInUse[can] + 1 == nNetwork)
            return can + 1;
    }
    return 1;
}

int Spy_LINIndex(int iNetwork)
{
    if (iNetwork == NET_LIN2)
        return 2;
    else if (iNetwork == NET_LIN3)
        return 3;
    else if (iNetwork == NET_LIN4)
        return 4;
    else if (iNetwork == NET_LIN2__VNET_A_)
        return 2;
    else if (iNetwork == NET_LIN3__VNET_A_)
        return 3;
    else if (iNetwork == NET_LIN4__VNET_A_)
        return 4;
    else if (iNetwork == NET_LIN2__VNET_B_)
        return 2;
    else if (iNetwork == NET_LIN3__VNET_B_)
        return 3;
    else if (iNetwork == NET_LIN4__VNET_B_)
        return 4;
    else
        return 1;
}

// network index variables - identify networks in vspy
int NET_HS_CAN = 0;
void NET_HS_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN,0);
}
void NET_HS_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN,p_NetworkStats);
}
int NET_MS_CAN = 1;
void NET_MS_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MS_CAN,0);
}
void NET_MS_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MS_CAN,p_NetworkStats);
}
int NET_SW_CAN = 2;
void NET_SW_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN,0);
}
void NET_SW_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN,p_NetworkStats);
}
int NET_J1850_VPW = 3;
void NET_J1850_VPW_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1850_VPW,0);
}
void NET_J1850_VPW_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1850_VPW,p_NetworkStats);
}
int NET_ISO9141_KW2K = 4;
void NET_ISO9141_KW2K_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K,0);
}
void NET_ISO9141_KW2K_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K,p_NetworkStats);
}
int NET_LSFT_CAN = 5;
void NET_LSFT_CAN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN,0);
}
void NET_LSFT_CAN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN,p_NetworkStats);
}
int NET_J1850_PWM = 6;
void NET_J1850_PWM_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1850_PWM,0);
}
void NET_J1850_PWM_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1850_PWM,p_NetworkStats);
}
int NET_J1708 = 7;
void NET_J1708_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1708,0);
}
void NET_J1708_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1708,p_NetworkStats);
}
int NET_neoVI = 8;
void NET_neoVI_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_neoVI,0);
}
void NET_neoVI_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_neoVI,p_NetworkStats);
}
int NET_HS_CAN2 = 9;
void NET_HS_CAN2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN2,0);
}
void NET_HS_CAN2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN2,p_NetworkStats);
}
int NET_HS_CAN3 = 10;
void NET_HS_CAN3_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN3,0);
}
void NET_HS_CAN3_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN3,p_NetworkStats);
}
int NET_LIN2 = 11;
void NET_LIN2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN2,0);
}
void NET_LIN2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN2,p_NetworkStats);
}
int NET_LIN3 = 12;
void NET_LIN3_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN3,0);
}
void NET_LIN3_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN3,p_NetworkStats);
}
int NET_LIN4 = 13;
void NET_LIN4_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN4,0);
}
void NET_LIN4_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN4,p_NetworkStats);
}
int NET_CGI = 14;
void NET_CGI_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_CGI,0);
}
void NET_CGI_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_CGI,p_NetworkStats);
}
int NET_LIN = 15;
void NET_LIN_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN,0);
}
void NET_LIN_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN,p_NetworkStats);
}
int NET_ISO9141_KW2K_2 = 16;
void NET_ISO9141_KW2K_2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_2,0);
}
void NET_ISO9141_KW2K_2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_2,p_NetworkStats);
}
int NET_ISO9141_KW2K_3 = 17;
void NET_ISO9141_KW2K_3_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_3,0);
}
void NET_ISO9141_KW2K_3_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_3,p_NetworkStats);
}
int NET_ISO9141_KW2K_4 = 18;
void NET_ISO9141_KW2K_4_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_4,0);
}
void NET_ISO9141_KW2K_4_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_4,p_NetworkStats);
}
int NET_HS_CAN4 = 19;
void NET_HS_CAN4_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN4,0);
}
void NET_HS_CAN4_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN4,p_NetworkStats);
}
int NET_HS_CAN5 = 20;
void NET_HS_CAN5_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN5,0);
}
void NET_HS_CAN5_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN5,p_NetworkStats);
}
int NET_UART = 21;
void NET_UART_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_UART,0);
}
void NET_UART_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_UART,p_NetworkStats);
}
int NET_UART2 = 22;
void NET_UART2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_UART2,0);
}
void NET_UART2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_UART2,p_NetworkStats);
}
int NET_LIN5 = 23;
void NET_LIN5_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN5,0);
}
void NET_LIN5_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN5,p_NetworkStats);
}
int NET_MOST__VNET_A_ = 24;
void NET_MOST__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MOST__VNET_A_,0);
}
void NET_MOST__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MOST__VNET_A_,p_NetworkStats);
}
int NET_FlexRay1A__VNET_A_ = 25;
void NET_FlexRay1A__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay1A__VNET_A_,0);
}
void NET_FlexRay1A__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay1A__VNET_A_,p_NetworkStats);
}
int NET_FlexRay1B__VNET_A_ = 26;
void NET_FlexRay1B__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay1B__VNET_A_,0);
}
void NET_FlexRay1B__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay1B__VNET_A_,p_NetworkStats);
}
int NET_FlexRay2A__VNET_A_ = 27;
void NET_FlexRay2A__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2A__VNET_A_,0);
}
void NET_FlexRay2A__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2A__VNET_A_,p_NetworkStats);
}
int NET_FlexRay2B__VNET_A_ = 28;
void NET_FlexRay2B__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2B__VNET_A_,0);
}
void NET_FlexRay2B__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2B__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN__VNET_A_ = 29;
void NET_HS_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN__VNET_A_,0);
}
void NET_HS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN__VNET_A_,p_NetworkStats);
}
int NET_MS_CAN__VNET_A_ = 30;
void NET_MS_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MS_CAN__VNET_A_,0);
}
void NET_MS_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MS_CAN__VNET_A_,p_NetworkStats);
}
int NET_SW_CAN__VNET_A_ = 31;
void NET_SW_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN__VNET_A_,0);
}
void NET_SW_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN__VNET_A_,p_NetworkStats);
}
int NET_J1850_VPW__VNET_A_ = 32;
void NET_J1850_VPW__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1850_VPW__VNET_A_,0);
}
void NET_J1850_VPW__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1850_VPW__VNET_A_,p_NetworkStats);
}
int NET_LSFT_CAN__VNET_A_ = 33;
void NET_LSFT_CAN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN__VNET_A_,0);
}
void NET_LSFT_CAN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN__VNET_A_,p_NetworkStats);
}
int NET_J1708__VNET_A_ = 34;
void NET_J1708__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1708__VNET_A_,0);
}
void NET_J1708__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1708__VNET_A_,p_NetworkStats);
}
int NET_neoVI__VNET_A_ = 35;
void NET_neoVI__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_neoVI__VNET_A_,0);
}
void NET_neoVI__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_neoVI__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN2__VNET_A_ = 36;
void NET_HS_CAN2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN2__VNET_A_,0);
}
void NET_HS_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN2__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN3__VNET_A_ = 37;
void NET_HS_CAN3__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN3__VNET_A_,0);
}
void NET_HS_CAN3__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN3__VNET_A_,p_NetworkStats);
}
int NET_LIN__VNET_A_ = 38;
void NET_LIN__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN__VNET_A_,0);
}
void NET_LIN__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN__VNET_A_,p_NetworkStats);
}
int NET_LIN2__VNET_A_ = 39;
void NET_LIN2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN2__VNET_A_,0);
}
void NET_LIN2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN2__VNET_A_,p_NetworkStats);
}
int NET_LIN3__VNET_A_ = 40;
void NET_LIN3__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN3__VNET_A_,0);
}
void NET_LIN3__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN3__VNET_A_,p_NetworkStats);
}
int NET_LIN4__VNET_A_ = 41;
void NET_LIN4__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN4__VNET_A_,0);
}
void NET_LIN4__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN4__VNET_A_,p_NetworkStats);
}
int NET_CGI__VNET_A_ = 42;
void NET_CGI__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_CGI__VNET_A_,0);
}
void NET_CGI__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_CGI__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K__VNET_A_ = 43;
void NET_ISO9141_KW2K__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K__VNET_A_,0);
}
void NET_ISO9141_KW2K__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K_2__VNET_A_ = 44;
void NET_ISO9141_KW2K_2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_2__VNET_A_,0);
}
void NET_ISO9141_KW2K_2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_2__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K_3__VNET_A_ = 45;
void NET_ISO9141_KW2K_3__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_3__VNET_A_,0);
}
void NET_ISO9141_KW2K_3__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_3__VNET_A_,p_NetworkStats);
}
int NET_ISO9141_KW2K_4__VNET_A_ = 46;
void NET_ISO9141_KW2K_4__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_4__VNET_A_,0);
}
void NET_ISO9141_KW2K_4__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_4__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN__VNET_B_ = 47;
void NET_HS_CAN__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN__VNET_B_,0);
}
void NET_HS_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN__VNET_B_,p_NetworkStats);
}
int NET_MS_CAN__VNET_B_ = 48;
void NET_MS_CAN__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MS_CAN__VNET_B_,0);
}
void NET_MS_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MS_CAN__VNET_B_,p_NetworkStats);
}
int NET_SW_CAN__VNET_B_ = 49;
void NET_SW_CAN__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN__VNET_B_,0);
}
void NET_SW_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN__VNET_B_,p_NetworkStats);
}
int NET_J1850_VPW__VNET_B_ = 50;
void NET_J1850_VPW__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1850_VPW__VNET_B_,0);
}
void NET_J1850_VPW__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1850_VPW__VNET_B_,p_NetworkStats);
}
int NET_LSFT_CAN__VNET_B_ = 51;
void NET_LSFT_CAN__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN__VNET_B_,0);
}
void NET_LSFT_CAN__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN__VNET_B_,p_NetworkStats);
}
int NET_J1708__VNET_B_ = 52;
void NET_J1708__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_J1708__VNET_B_,0);
}
void NET_J1708__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_J1708__VNET_B_,p_NetworkStats);
}
int NET_neoVI__VNET_B_ = 53;
void NET_neoVI__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_neoVI__VNET_B_,0);
}
void NET_neoVI__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_neoVI__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN2__VNET_B_ = 54;
void NET_HS_CAN2__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN2__VNET_B_,0);
}
void NET_HS_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN2__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN3__VNET_B_ = 55;
void NET_HS_CAN3__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN3__VNET_B_,0);
}
void NET_HS_CAN3__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN3__VNET_B_,p_NetworkStats);
}
int NET_LIN__VNET_B_ = 56;
void NET_LIN__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN__VNET_B_,0);
}
void NET_LIN__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN__VNET_B_,p_NetworkStats);
}
int NET_LIN2__VNET_B_ = 57;
void NET_LIN2__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN2__VNET_B_,0);
}
void NET_LIN2__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN2__VNET_B_,p_NetworkStats);
}
int NET_LIN3__VNET_B_ = 58;
void NET_LIN3__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN3__VNET_B_,0);
}
void NET_LIN3__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN3__VNET_B_,p_NetworkStats);
}
int NET_LIN4__VNET_B_ = 59;
void NET_LIN4__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN4__VNET_B_,0);
}
void NET_LIN4__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN4__VNET_B_,p_NetworkStats);
}
int NET_CGI__VNET_B_ = 60;
void NET_CGI__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_CGI__VNET_B_,0);
}
void NET_CGI__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_CGI__VNET_B_,p_NetworkStats);
}
int NET_ISO9141_KW2K__VNET_B_ = 61;
void NET_ISO9141_KW2K__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K__VNET_B_,0);
}
void NET_ISO9141_KW2K__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K__VNET_B_,p_NetworkStats);
}
int NET_ISO9141_KW2K_2__VNET_B_ = 62;
void NET_ISO9141_KW2K_2__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_2__VNET_B_,0);
}
void NET_ISO9141_KW2K_2__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_2__VNET_B_,p_NetworkStats);
}
int NET_ISO9141_KW2K_3__VNET_B_ = 63;
void NET_ISO9141_KW2K_3__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_3__VNET_B_,0);
}
void NET_ISO9141_KW2K_3__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_3__VNET_B_,p_NetworkStats);
}
int NET_ISO9141_KW2K_4__VNET_B_ = 64;
void NET_ISO9141_KW2K_4__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_ISO9141_KW2K_4__VNET_B_,0);
}
void NET_ISO9141_KW2K_4__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_ISO9141_KW2K_4__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN4__VNET_A_ = 65;
void NET_HS_CAN4__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN4__VNET_A_,0);
}
void NET_HS_CAN4__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN4__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN5__VNET_A_ = 66;
void NET_HS_CAN5__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN5__VNET_A_,0);
}
void NET_HS_CAN5__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN5__VNET_A_,p_NetworkStats);
}
int NET_LIN5__VNET_A_ = 67;
void NET_LIN5__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN5__VNET_A_,0);
}
void NET_LIN5__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN5__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN4__VNET_B_ = 68;
void NET_HS_CAN4__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN4__VNET_B_,0);
}
void NET_HS_CAN4__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN4__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN5__VNET_B_ = 69;
void NET_HS_CAN5__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN5__VNET_B_,0);
}
void NET_HS_CAN5__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN5__VNET_B_,p_NetworkStats);
}
int NET_LIN5__VNET_B_ = 70;
void NET_LIN5__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN5__VNET_B_,0);
}
void NET_LIN5__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN5__VNET_B_,p_NetworkStats);
}
int NET_Ethernet_DAQ = 71;
void NET_Ethernet_DAQ_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_Ethernet_DAQ,0);
}
void NET_Ethernet_DAQ_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_Ethernet_DAQ,p_NetworkStats);
}
int NET_Ethernet = 72;
void NET_Ethernet_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_Ethernet,0);
}
void NET_Ethernet_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_Ethernet,p_NetworkStats);
}
int NET_MOST__VNET_B_ = 73;
void NET_MOST__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_MOST__VNET_B_,0);
}
void NET_MOST__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_MOST__VNET_B_,p_NetworkStats);
}
int NET_FlexRay1A__VNET_B_ = 74;
void NET_FlexRay1A__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay1A__VNET_B_,0);
}
void NET_FlexRay1A__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay1A__VNET_B_,p_NetworkStats);
}
int NET_FlexRay1B__VNET_B_ = 75;
void NET_FlexRay1B__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay1B__VNET_B_,0);
}
void NET_FlexRay1B__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay1B__VNET_B_,p_NetworkStats);
}
int NET_FlexRay2A__VNET_B_ = 76;
void NET_FlexRay2A__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2A__VNET_B_,0);
}
void NET_FlexRay2A__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2A__VNET_B_,p_NetworkStats);
}
int NET_FlexRay2B__VNET_B_ = 77;
void NET_FlexRay2B__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2B__VNET_B_,0);
}
void NET_FlexRay2B__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2B__VNET_B_,p_NetworkStats);
}
int NET_SW_CAN2 = 78;
void NET_SW_CAN2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN2,0);
}
void NET_SW_CAN2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN2,p_NetworkStats);
}
int NET_SW_CAN2__VNET_A_ = 79;
void NET_SW_CAN2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN2__VNET_A_,0);
}
void NET_SW_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN2__VNET_A_,p_NetworkStats);
}
int NET_SW_CAN2__VNET_B_ = 80;
void NET_SW_CAN2__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_SW_CAN2__VNET_B_,0);
}
void NET_SW_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_SW_CAN2__VNET_B_,p_NetworkStats);
}
int NET_FSA = 81;
void NET_FSA_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FSA,0);
}
void NET_FSA_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FSA,p_NetworkStats);
}
int NET_TCP = 82;
void NET_TCP_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_TCP,0);
}
void NET_TCP_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_TCP,p_NetworkStats);
}
int NET_HS_CAN6 = 83;
void NET_HS_CAN6_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN6,0);
}
void NET_HS_CAN6_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN6,p_NetworkStats);
}
int NET_HS_CAN7 = 84;
void NET_HS_CAN7_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN7,0);
}
void NET_HS_CAN7_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN7,p_NetworkStats);
}
int NET_LIN6 = 85;
void NET_LIN6_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN6,0);
}
void NET_LIN6_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN6,p_NetworkStats);
}
int NET_LSFT_CAN2 = 86;
void NET_LSFT_CAN2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN2,0);
}
void NET_LSFT_CAN2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN2,p_NetworkStats);
}
int NET_OP__BR__ETH01 = 87;
void NET_OP__BR__ETH01_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH01,0);
}
void NET_OP__BR__ETH01_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH01,p_NetworkStats);
}
int NET_OP__BR__ETH02 = 88;
void NET_OP__BR__ETH02_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH02,0);
}
void NET_OP__BR__ETH02_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH02,p_NetworkStats);
}
int NET_OP__BR__ETH03 = 89;
void NET_OP__BR__ETH03_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH03,0);
}
void NET_OP__BR__ETH03_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH03,p_NetworkStats);
}
int NET_OP__BR__ETH04 = 90;
void NET_OP__BR__ETH04_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH04,0);
}
void NET_OP__BR__ETH04_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH04,p_NetworkStats);
}
int NET_OP__BR__ETH05 = 91;
void NET_OP__BR__ETH05_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH05,0);
}
void NET_OP__BR__ETH05_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH05,p_NetworkStats);
}
int NET_OP__BR__ETH06 = 92;
void NET_OP__BR__ETH06_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH06,0);
}
void NET_OP__BR__ETH06_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH06,p_NetworkStats);
}
int NET_OP__BR__ETH07 = 93;
void NET_OP__BR__ETH07_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH07,0);
}
void NET_OP__BR__ETH07_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH07,p_NetworkStats);
}
int NET_OP__BR__ETH08 = 94;
void NET_OP__BR__ETH08_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH08,0);
}
void NET_OP__BR__ETH08_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH08,p_NetworkStats);
}
int NET_OP__BR__ETH09 = 95;
void NET_OP__BR__ETH09_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH09,0);
}
void NET_OP__BR__ETH09_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH09,p_NetworkStats);
}
int NET_OP__BR__ETH10 = 96;
void NET_OP__BR__ETH10_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH10,0);
}
void NET_OP__BR__ETH10_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH10,p_NetworkStats);
}
int NET_OP__BR__ETH11 = 97;
void NET_OP__BR__ETH11_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH11,0);
}
void NET_OP__BR__ETH11_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH11,p_NetworkStats);
}
int NET_OP__BR__ETH12 = 98;
void NET_OP__BR__ETH12_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_OP__BR__ETH12,0);
}
void NET_OP__BR__ETH12_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_OP__BR__ETH12,p_NetworkStats);
}
int NET_FlexRay = 99;
void NET_FlexRay_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay,0);
}
void NET_FlexRay_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay,p_NetworkStats);
}
int NET_FlexRay2 = 100;
void NET_FlexRay2_ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_FlexRay2,0);
}
void NET_FlexRay2_GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_FlexRay2,p_NetworkStats);
}
int NET_LIN6__VNET_A_ = 101;
void NET_LIN6__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN6__VNET_A_,0);
}
void NET_LIN6__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN6__VNET_A_,p_NetworkStats);
}
int NET_LIN6__VNET_B_ = 102;
void NET_LIN6__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LIN6__VNET_B_,0);
}
void NET_LIN6__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LIN6__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN6__VNET_A_ = 103;
void NET_HS_CAN6__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN6__VNET_A_,0);
}
void NET_HS_CAN6__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN6__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN6__VNET_B_ = 104;
void NET_HS_CAN6__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN6__VNET_B_,0);
}
void NET_HS_CAN6__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN6__VNET_B_,p_NetworkStats);
}
int NET_HS_CAN7__VNET_A_ = 105;
void NET_HS_CAN7__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN7__VNET_A_,0);
}
void NET_HS_CAN7__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN7__VNET_A_,p_NetworkStats);
}
int NET_HS_CAN7__VNET_B_ = 106;
void NET_HS_CAN7__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_HS_CAN7__VNET_B_,0);
}
void NET_HS_CAN7__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_HS_CAN7__VNET_B_,p_NetworkStats);
}
int NET_LSFT_CAN2__VNET_A_ = 107;
void NET_LSFT_CAN2__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN2__VNET_A_,0);
}
void NET_LSFT_CAN2__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN2__VNET_A_,p_NetworkStats);
}
int NET_LSFT_CAN2__VNET_B_ = 108;
void NET_LSFT_CAN2__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_LSFT_CAN2__VNET_B_,0);
}
void NET_LSFT_CAN2__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_LSFT_CAN2__VNET_B_,p_NetworkStats);
}
int NET_Ethernet__VNET_A_ = 109;
void NET_Ethernet__VNET_A__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_Ethernet__VNET_A_,0);
}
void NET_Ethernet__VNET_A__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_Ethernet__VNET_A_,p_NetworkStats);
}
int NET_Ethernet__VNET_B_ = 110;
void NET_Ethernet__VNET_B__ClearStats()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_CLR,NET_Ethernet__VNET_B_,0);
}
void NET_Ethernet__VNET_B__GetStats(NetworkStats * p_NetworkStats)
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_NET_STATS_GET,NET_Ethernet__VNET_B_,p_NetworkStats);
}

int GenericMessageTransmit(GenericMessage * p_Msg)
{
    int iID;
    int iBitField;
    iID = p_Msg->iID;
    iBitField = p_Msg->iBitField;
    if (isExtId(iID))
    {
        iID = mkStdId(iID);
        iBitField |= ATTR_CAN_29BIT_ID_FRAME;
    }

    return CM_TransmitMessage(g_uiHandle, p_Msg->iNetwork, iID, p_Msg->iNumDataBytes, iBitField, p_Msg->btData);
}

int GenericLongMessageTransmit(GenericLongMessage * p_Msg)
{
    int iID;
    int iBitField;
    iID = p_Msg->iID;
    iBitField = p_Msg->iBitField;

    return CM_TransmitMessage(g_uiHandle, p_Msg->iNetwork, iID, p_Msg->iNumDataBytes, iBitField, p_Msg->btData);
}

int CANFDMessageTransmit(GenericLongMessage * p_Msg, BOOL bBRS)
{
    int iID;
    int iBitField;
    iID = p_Msg->iID;
    iBitField = p_Msg->iBitField;
    if (isExtId(iID))
    {
        iID = mkStdId(iID);
        iBitField |= ATTR_CAN_29BIT_ID_FRAME;
    }
    iBitField |= ATTR_CANFD_FRAME;
    if (bBRS)
        iBitField |= ATTR_CANFD_BRS;

    return CM_TransmitMessage(g_uiHandle, p_Msg->iNetwork, iID, p_Msg->iNumDataBytes, iBitField, p_Msg->btData);
}

void SpySetTxSignal(unsigned int iMessageIndex, unsigned int iSignalIndex, double dValue)
{
    TxSetSignal txSetSignal;
    txSetSignal.iSignal = iSignalIndex;
    txSetSignal.iType = 0;
    txSetSignal.dValue = dValue;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_TXSIGNAL, iMessageIndex, &txSetSignal);
}

void SpySetTxSignalRaw(unsigned int iMessageIndex, unsigned int iSignalIndex, __int64 nValue)
{
    TxSetSignal txSetSignal;
    txSetSignal.iSignal = iSignalIndex;
    txSetSignal.iType = 1;
    txSetSignal.nValue = nValue;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_TXSIGNAL, iMessageIndex, &txSetSignal);
}

void SpySetTxEvent(unsigned int iMessageIndex)
{
    TxSetSignal txSetSignal;
    txSetSignal.iType = 2;
    CM_GetSetValue(g_uiHandle, CM_GETSET_SET_TXSIGNAL, iMessageIndex, &txSetSignal);
}

int Spy_TextAPI_W(wchar_t * wcCommand, wchar_t * wcResponse, int iResponseMaxLength)
{
    return CM_TextAPI(g_uiHandle,wcCommand,wcResponse,iResponseMaxLength);
}

int Spy_TextAPI(char * szCommand, char * szResponse, int iResponseMaxLength)
{
    int iCount;
    int iResult;
    wchar_t wcCommand[1024];
    wchar_t wcResponse[1024];
    iCount = MultiByteToWideChar(0, 0, szCommand, (int)strlen(szCommand), NULL, 0);
    MultiByteToWideChar(0, 0, szCommand, (int)strlen(szCommand), wcCommand, iCount);
    wcCommand[iCount] = 0;
    iResult = CM_TextAPI(g_uiHandle, wcCommand, wcResponse, 1024);
    iCount = WideCharToMultiByte(0, 0, wcResponse, (int)wcslen(wcResponse), NULL, 0, NULL, NULL);
    WideCharToMultiByte(0, 0, wcResponse, (int)wcslen(wcResponse), szResponse, iCount, NULL, NULL);
    szResponse[iCount] = 0;
    return iResult;
}

#define MAX_PRINT_BUF_SIZE 1024

int OutputChars(const char *szMsg, int nLen)
{
    wchar_t *pWideBuffer;
    int iCount = MultiByteToWideChar(0, 0, szMsg, nLen, NULL, 0);
    pWideBuffer = malloc((iCount + 1) * sizeof(wchar_t));
    MultiByteToWideChar(0, 0, szMsg, nLen, pWideBuffer, iCount);
    pWideBuffer[iCount] = 0;
    CM_OutputWindow(g_uiHandle, pWideBuffer, 0x0000, 0);
    free(pWideBuffer);
    return iCount;
}

int Printf(const char *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    char szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vsprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    iNumCharacters = OutputChars(szMsg, iNumCharacters);
    va_end(ap);
    return iNumCharacters;
}

int PrintfW(const wchar_t *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    wchar_t szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vswprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    va_end(ap);
    CM_OutputWindow(g_uiHandle, szMsg, 0x0000, 0);
    return iNumCharacters;
}

int WriteLine(const char *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    char szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vsprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    strcat_s(szMsg, MAX_PRINT_BUF_SIZE, "\n");
    ++iNumCharacters;
    iNumCharacters = OutputChars(szMsg, iNumCharacters);
    va_end(ap);
    return iNumCharacters;
}

int WriteLineW(const wchar_t *szInMsg, ...)
{
    va_list ap;
    int iNumCharacters;
    wchar_t szMsg[MAX_PRINT_BUF_SIZE];
    va_start(ap, szInMsg);
    iNumCharacters = vswprintf_s(szMsg, MAX_PRINT_BUF_SIZE, szInMsg, ap);
    va_end(ap);
    wcscat_s(szMsg, MAX_PRINT_BUF_SIZE, L"\n");
    CM_OutputWindow(g_uiHandle, szMsg, 0x0000, 0);
    return iNumCharacters + 1;
}

// Retrieve the system error message for the last error code
void DisplayLastError(LPCWSTR lpszFunction)
{
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR) &lpMsgBuf, 0, NULL );

    // Display the error message
    if (lpszFunction)
        PrintfW(L"%ls failed with error %d: %ls\n", lpszFunction, dw, lpMsgBuf);
    else
        PrintfW(L"Error %d: %ls\n", dw, lpMsgBuf);

    LocalFree(lpMsgBuf);
}

#define ICS_MAX_RS232_PORT 255
HANDLE hSerialPorts[ICS_MAX_RS232_PORT] = { INVALID_HANDLE_VALUE };

RS232OnRxTx_fdef fptr_ICS_RS232OnSend = NULL;
RS232OnRxTx_fdef fptr_ICS_RS232OnReceive = NULL;
RS232OnError_fdef fptr_ICS_RS232OnError = NULL;

DWORD ICS_RS232Open(DWORD port)
{
    wchar_t szPort[20];
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Open was passed an invalid port number: %d\n", port);
        return 0;
    }
    wsprintf(szPort, TEXT("\\\\.\\COM%d"), port);
    hSerialPorts[port - 1] = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
        return 1;
    else
    {
        DisplayLastError(TEXT("ICS_RS232Open"));
        return 0;
    }
}

DWORD ICS_RS232Close(DWORD port)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Close was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hSerialPorts[port - 1]);
        hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
        return 1;
    }
    else
    {
        PrintfW(L"ICS_RS232Close port number %d was not opened\n", port);
        return 0;
    }
}

DWORD ICS_RS232ConfigTimeout(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity, DWORD timeout)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232ConfigTimeout was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DCB comState;
        if (GetCommState(hSerialPorts[port - 1], &comState))
		{
            DCB newComState = comState;

            newComState.BaudRate = baudrate;
            newComState.ByteSize = (BYTE)numberOfDataBits;
            newComState.StopBits = (BYTE)numberOfStopBits;
            newComState.Parity = (BYTE)parity;

            if (SetCommState(hSerialPorts[port - 1], &newComState))
            {
                // Add CommTimeout
                COMMTIMEOUTS commTimeout;
                GetCommTimeouts(hSerialPorts[port - 1], &commTimeout);

                commTimeout.ReadIntervalTimeout = 0;
                commTimeout.ReadTotalTimeoutMultiplier = 0;
                commTimeout.ReadTotalTimeoutConstant = timeout;
                commTimeout.WriteTotalTimeoutMultiplier = 0;
                commTimeout.WriteTotalTimeoutConstant = timeout;

                SetCommTimeouts(hSerialPorts[port - 1], &commTimeout);
                return 1;
            }
            else
            {
                DisplayLastError(TEXT("ICS_RS232Config"));
                hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
                return 0;
            }
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232Config"));
            hSerialPorts[port - 1] = INVALID_HANDLE_VALUE; 
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232Config port number %d was not opened\n", port); 
        return 0;
    }
}

DWORD ICS_RS232Config(DWORD port, DWORD baudrate, DWORD numberOfDataBits, DWORD numberOfStopBits, DWORD parity)
{
    return ICS_RS232ConfigTimeout(port, baudrate, numberOfDataBits, numberOfStopBits, parity, 10);
}

DWORD ICS_RS232SetHandshake(DWORD port, DWORD handshake, DWORD XonLimit, DWORD XoffLimit, DWORD XonChar, DWORD XoffChar)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232SetHandshake was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DCB comState;
        if (GetCommState(hSerialPorts[port - 1], &comState))
        {
            if (handshake == 128) // Software handshake
            {
                comState.fRtsControl = RTS_CONTROL_HANDSHAKE;
                comState.XonLim = (WORD)XonLimit;
                comState.XoffLim = (WORD)XoffLimit;
                comState.XonChar = (char)XonChar;
                comState.XoffChar = (char)XoffChar;
                if (SetCommState(hSerialPorts[port - 1], &comState))
                    return 1;
                else
                {
                    DisplayLastError(TEXT("RS232SetHandshake"));
                    hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
                    return 0;
                }
            }
            else
            {
                return 1;
            }
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232SetHandshake"));
            hSerialPorts[port - 1] = INVALID_HANDLE_VALUE;
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232SetHandshake port number %d was not opened\n", port);
        return 0;
    }
}

DWORD ICS_RS232SetSignalLine(DWORD port, DWORD line, DWORD state)
{
    return 0;
}

DWORD ICS_RS232Send(DWORD port, BYTE buffer[], DWORD size)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Send was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DWORD dwBytesWritten = 0;
        if (WriteFile(hSerialPorts[port - 1], buffer, size, &dwBytesWritten, NULL))
        {
            if (fptr_ICS_RS232OnSend)
                fptr_ICS_RS232OnSend(port, buffer, size);
            return 1;
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232Send"));
            if (fptr_ICS_RS232OnError)
                fptr_ICS_RS232OnError(port, 0x1);
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232Send port number %d was not opened\n", port);
        return 0;
    }
}

DWORD ICS_RS232Receive(DWORD port, BYTE buffer[], DWORD size)
{
    if ((port <= 0) || (port > ICS_MAX_RS232_PORT))
    {
        PrintfW(L"ICS_RS232Receive was passed an invalid port number: %d\n", port);
        return 0;
    }
    if (hSerialPorts[port - 1] != INVALID_HANDLE_VALUE)
    {
        DWORD dwBytesRead = 0;
        if (ReadFile(hSerialPorts[port - 1], buffer, size, &dwBytesRead, NULL))
        {
            if (dwBytesRead < size)
                buffer[dwBytesRead] = 0;
            if (fptr_ICS_RS232OnReceive)
                fptr_ICS_RS232OnReceive(port, buffer, size);
            return 1;
        }
        else
        {
            DisplayLastError(TEXT("ICS_RS232Receive"));
            if (fptr_ICS_RS232OnError)
                fptr_ICS_RS232OnError(port, 0x2);
            return 0;
        }
    }
    else
    {
        PrintfW(L"ICS_RS232Receive port number %d was not opened\n", port);
        return 0;
    }
}

WORD ICS_RS232WriteByte(DWORD port, DWORD data)
{
    return (WORD)ICS_RS232Send(port, (LPBYTE)&data, 1);
}

WORD ICS_RS232WriteBlock(DWORD port, BYTE buffer[], DWORD size)
{
    return (WORD)ICS_RS232Send(port, buffer, size);
}

void ICS_RS232CloseAllPorts()
{
    int nPort;
    for (nPort = 0; nPort < ICS_MAX_RS232_PORT; ++nPort)
    {
        if (hSerialPorts[nPort] != INVALID_HANDLE_VALUE)
        {
            CloseHandle(hSerialPorts[nPort]);
            hSerialPorts[nPort] = INVALID_HANDLE_VALUE;
        }
    }
    UnloadInpout();
}

HINSTANCE hInpOutDll = NULL;
char bIOErrorDisp = 0;
lpOut32 gfpOut32 = NULL;
lpInp32 gfpInp32 = NULL;
lpIsInpOutDriverOpen gfpIsInpOutDriverOpen = NULL;

void LoadInpOut()
{
    if (hInpOutDll == NULL)
    {
        char szPath[MAX_PATH];
        char *pLastSlash;
        GetModuleFileNameA(NULL, szPath, sizeof(szPath));
        pLastSlash = strrchr(szPath, '\\');
        if (pLastSlash)
            *(pLastSlash + 1) = 0;
        strcat_s(szPath, MAX_PATH, "inpout32.DLL");
        hInpOutDll = LoadLibraryA(szPath);
    }
    if (hInpOutDll == NULL)
    {
        if (bIOErrorDisp == 0)
        {
            PrintfW(L"InpOut32.DLL is not installed!");
            bIOErrorDisp = 1;
        }
    }
    else if (gfpIsInpOutDriverOpen == NULL)
    {
		gfpOut32 = (lpOut32)GetProcAddress(hInpOutDll, "Out32");
		gfpInp32 = (lpInp32)GetProcAddress(hInpOutDll, "Inp32");
		gfpIsInpOutDriverOpen = (lpIsInpOutDriverOpen)GetProcAddress(hInpOutDll, "IsInpOutDriverOpen");
    }
}

void UnloadInpout()
{
    if (hInpOutDll)
    {
        gfpOut32 = NULL;
        gfpInp32 = NULL;
        gfpIsInpOutDriverOpen = NULL;
        FreeLibrary(hInpOutDll);
    }
}

void SpyAppSig_CallAllHandlers()
{
}

void (* CM_RegisterCallback) (void * uiHandle, unsigned short iValueType, unsigned short iIndex, void * pCallBackPointer) ;
void (* CM_GetSetValue) (void * uiHandle, unsigned short iValueType, unsigned short iIndex, void * pValueToSet) ;
int (* CM_TextAPI) (void * uiHandle, wchar_t * pCommand, wchar_t * pResponse, int iResponseMaxLength) ;
int (* CM_FindIndexForObjectFromName) (void * uiHandle, int iObjectType,wchar_t * pName, int * p_iObjectIndex);
int (* CM_GetMessageName) (void * uiHandle, int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize);
int (* CM_ShowPanel) (void * uiHandle, wchar_t * pWindowName, wchar_t * pPanelName);
int (* CM_SetControlProperty) (void * uiHandle, wchar_t * pPanelName, wchar_t * pWindowName, int prop, void *pValue);
int (* CM_OutputWindow) (void * uiHandle, wchar_t * p_TextToWrite, int iColor, int iLength) ;
int (* CM_TransmitMessage) (void * uiHandle, int iNetwork,int iID, int iNumDataBytes,int iBitField,unsigned char * p_btData);
int (* CM_GetSignalValue) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,unsigned short iSignalIndex,void * pValueToSet);
int (* CM_TxFromSignals) (void * uiHandle, unsigned short iMessageType,
				       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
				       int iNetworkIndex, void * pSignalValues, int iNumSignalCount);
int (* CM_TxFromRawSignals) (void * uiHandle, unsigned short iMessageType,
				       unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
				       int iNetworkIndex, void * pSignalValues, int iNumSignalCount);
int (* CM_MessageGenericInit) (void * uiHandle, unsigned short iMessageType,
					   unsigned short iMessageIndex, void * p_MessageStats, int * p_iNetworkID,
					   int * p_iNumDataBytes, int  p_iNumDataMax, int * p_iPeriodMs, int * p_iID,
					   int * p_iBitField, unsigned char * p_btData, double * p_dSignals, int dSignalMaxCount,
					   int * p_iActualSignalMaxCount,__int64 * p_iTimeStampNanoSecondsHW,unsigned int * p_iTimeStampMillisecondsOS);
int (* CM_MessageRawInit) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   uint64 * p_dSignals, int dSignalMaxCount, int * p_iActualSignalMaxCount);
uint64 (* CM_SignalPhysicalToRaw) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   unsigned short iSignalIndex, double dPhysicalValue);
int (* CM_UpdateMessageSignalsFromBytes) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    unsigned char * p_btData, int iNumDataBytes);
int (* CM_UpdateBytesFromSignals) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    double * p_dSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
int (* CM_UpdateBytesFromRawSignals) (void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    uint64 * p_iSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes);
int (* CM_GetEcuCount) (void * uiHandle);
int (* CM_GetMemoryBlockCount) (void * uiHandle, int ecu);
int (* CM_GetMemoryBlockInfo) (void * uiHandle, int ecu, int block, unsigned int *address, unsigned int *size);
int (* CM_GetMemoryBlockData) (void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);
int (* CM_SetMemoryBlockData) (void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size);

void __stdcall CM_ExtensionInit(void * uiHandle, struct stCallBackPointers  * p_stCallBackPointers)
{
    g_uiHandle = uiHandle;
    // setup the callback function to communicate to the CoreMini
    CM_RegisterCallback = (void ( *)(void *, unsigned short, unsigned short, void *)) p_stCallBackPointers->pRegisterCallBack;
    CM_GetSetValue = (void ( *)(void * , unsigned short, unsigned short, void *)) p_stCallBackPointers->pGetSetValueCallBack; 
    CM_TextAPI = (int ( *)(void *, wchar_t *, wchar_t *, int)) p_stCallBackPointers->pTextAPICallBack;
    CM_FindIndexForObjectFromName = (int ( *)(void *, int, wchar_t *, int *)) p_stCallBackPointers->pFindIndexForObjectFromNameCallBack;
    CM_GetMessageName = (int ( *)(void * uiHandle, int iMessageId, int iMessageContext, wchar_t * pName, int iBufferSize)) p_stCallBackPointers->pGetMessageName;
    CM_ShowPanel = (int ( *)(void *, wchar_t *, wchar_t *)) p_stCallBackPointers->pShowPanelCallBack;
    CM_SetControlProperty = (int ( *)(void *, wchar_t *, wchar_t *, int, void *)) p_stCallBackPointers->pSetControlProp;
    CM_OutputWindow = (int ( *)(void *, wchar_t *, int, int)) p_stCallBackPointers->pOutputWindowCallBack;
    CM_TransmitMessage = (int (* )(void *, int, int, int, int, unsigned char *)) p_stCallBackPointers->pTransmitMessageCallBack  ;
    CM_GetSignalValue = (int (* )(void *, unsigned short, unsigned short, unsigned short, void *)) p_stCallBackPointers->pGetSignalValue;
    CM_TxFromSignals = (int (* )(void * uiHandle, unsigned short iMessageType,
                    unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                    int iNetworkIndex, void * pSignalValues,
                    int iNumSignalCount)) p_stCallBackPointers->pTransmitMessagesFromSignalValues; 
    CM_TxFromRawSignals = (int (* )(void * uiHandle, unsigned short iMessageType,
                    unsigned short iMessageIndex, unsigned char * bt_DefaultBytes, int iByteCount,
                    int iNetworkIndex, void * pSignalValues,
                    int iNumSignalCount)) p_stCallBackPointers->pTransmitMessagesFromRawSignalValues;
    CM_MessageGenericInit = (int (* )(void * uiHandle, unsigned short iMessageType,
                    unsigned short iMessageIndex, void *p_MessageStats, int *p_iNetworkID,
                    int *p_iNumDataBytes, int  p_iNumDataMax, int *p_iPeriodMs, int *p_iID,
                    int *p_iBitField, unsigned char *p_btData, double *p_dSignals, int dSignalMaxCount,
                    int *p_iActualSignalMaxCount, __int64 *p_iTimeStampNanoSecondsHW, unsigned int *p_iTimeStampMillisecondsOS)) p_stCallBackPointers->pMessageGenericInit; 
    CM_MessageRawInit = (int (* )(void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   uint64 * p_dSignals, int dSignalMaxCount, int * p_iActualSignalMaxCount)) p_stCallBackPointers->pMessageRawInit;
    CM_SignalPhysicalToRaw = (uint64 (* )(void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
					   unsigned short iSignalIndex, double dPhysicalValue)) p_stCallBackPointers->pSignalPhysicalToRaw;
    CM_UpdateMessageSignalsFromBytes = (int (* )(void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    unsigned char * p_btData, int iNumDataBytes)) p_stCallBackPointers->pUpdateMessageSignalsFromBytes;
    CM_UpdateBytesFromSignals = (int (* )(void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    double * p_dSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes)) p_stCallBackPointers->pUpdateBytesFromSignals;
    CM_UpdateBytesFromRawSignals = (int (* )(void * uiHandle, unsigned short iMessageType, unsigned short iMessageIndex,
                    uint64 * p_iSignals, int dSignalMaxCount, unsigned char * p_btData, int iNumDataBytes)) p_stCallBackPointers->pUpdateBytesFromRawSignals;
    CM_GetEcuCount = (int (* )(void * uiHandle)) p_stCallBackPointers->pGetEcuCount;
    CM_GetMemoryBlockCount = (int (* )(void * uiHandle, int ecu)) p_stCallBackPointers->pGetMemoryBlockCount;
    CM_GetMemoryBlockInfo = (int (* )(void * uiHandle, int ecu, int block, unsigned int *address, unsigned int *size)) p_stCallBackPointers->pGetMemoryBlockInfo;
    CM_GetMemoryBlockData = (int (* )(void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size)) p_stCallBackPointers->pGetMemoryBlockData;
    CM_SetMemoryBlockData = (int (* )(void * uiHandle, int ecu, int block, unsigned char *buffer, unsigned int address, unsigned int size)) p_stCallBackPointers->pSetMemoryBlockData;
    // fix up the index variables by searching for the names
    // network indexes
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN",&NET_HS_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MS CAN",&NET_MS_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN",&NET_SW_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1850 VPW",&NET_J1850_VPW);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K",&NET_ISO9141_KW2K);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN",&NET_LSFT_CAN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1850 PWM",&NET_J1850_PWM);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1708",&NET_J1708);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"neoVI",&NET_neoVI);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN2",&NET_HS_CAN2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN3",&NET_HS_CAN3);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN2",&NET_LIN2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN3",&NET_LIN3);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN4",&NET_LIN4);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"CGI",&NET_CGI);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN",&NET_LIN);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 2",&NET_ISO9141_KW2K_2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 3",&NET_ISO9141_KW2K_3);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 4",&NET_ISO9141_KW2K_4);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN4",&NET_HS_CAN4);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN5",&NET_HS_CAN5);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"UART",&NET_UART);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"UART2",&NET_UART2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN5",&NET_LIN5);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MOST (VNET A)",&NET_MOST__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay1A (VNET A)",&NET_FlexRay1A__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay1B (VNET A)",&NET_FlexRay1B__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2A (VNET A)",&NET_FlexRay2A__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2B (VNET A)",&NET_FlexRay2B__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN (VNET A)",&NET_HS_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MS CAN (VNET A)",&NET_MS_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN (VNET A)",&NET_SW_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1850 VPW (VNET A)",&NET_J1850_VPW__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN (VNET A)",&NET_LSFT_CAN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1708 (VNET A)",&NET_J1708__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"neoVI (VNET A)",&NET_neoVI__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN2 (VNET A)",&NET_HS_CAN2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN3 (VNET A)",&NET_HS_CAN3__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN (VNET A)",&NET_LIN__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN2 (VNET A)",&NET_LIN2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN3 (VNET A)",&NET_LIN3__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN4 (VNET A)",&NET_LIN4__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"CGI (VNET A)",&NET_CGI__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K (VNET A)",&NET_ISO9141_KW2K__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 2 (VNET A)",&NET_ISO9141_KW2K_2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 3 (VNET A)",&NET_ISO9141_KW2K_3__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 4 (VNET A)",&NET_ISO9141_KW2K_4__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN (VNET B)",&NET_HS_CAN__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MS CAN (VNET B)",&NET_MS_CAN__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN (VNET B)",&NET_SW_CAN__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1850 VPW (VNET B)",&NET_J1850_VPW__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN (VNET B)",&NET_LSFT_CAN__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"J1708 (VNET B)",&NET_J1708__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"neoVI (VNET B)",&NET_neoVI__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN2 (VNET B)",&NET_HS_CAN2__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN3 (VNET B)",&NET_HS_CAN3__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN (VNET B)",&NET_LIN__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN2 (VNET B)",&NET_LIN2__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN3 (VNET B)",&NET_LIN3__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN4 (VNET B)",&NET_LIN4__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"CGI (VNET B)",&NET_CGI__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K (VNET B)",&NET_ISO9141_KW2K__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 2 (VNET B)",&NET_ISO9141_KW2K_2__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 3 (VNET B)",&NET_ISO9141_KW2K_3__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"ISO9141/KW2K 4 (VNET B)",&NET_ISO9141_KW2K_4__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN4 (VNET A)",&NET_HS_CAN4__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN5 (VNET A)",&NET_HS_CAN5__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN5 (VNET A)",&NET_LIN5__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN4 (VNET B)",&NET_HS_CAN4__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN5 (VNET B)",&NET_HS_CAN5__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN5 (VNET B)",&NET_LIN5__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"Ethernet DAQ",&NET_Ethernet_DAQ);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"Ethernet",&NET_Ethernet);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"MOST (VNET B)",&NET_MOST__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay1A (VNET B)",&NET_FlexRay1A__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay1B (VNET B)",&NET_FlexRay1B__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2A (VNET B)",&NET_FlexRay2A__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2B (VNET B)",&NET_FlexRay2B__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN2",&NET_SW_CAN2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN2 (VNET A)",&NET_SW_CAN2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"SW CAN2 (VNET B)",&NET_SW_CAN2__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FSA",&NET_FSA);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"TCP",&NET_TCP);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN6",&NET_HS_CAN6);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN7",&NET_HS_CAN7);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN6",&NET_LIN6);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN2",&NET_LSFT_CAN2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH01",&NET_OP__BR__ETH01);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH02",&NET_OP__BR__ETH02);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH03",&NET_OP__BR__ETH03);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH04",&NET_OP__BR__ETH04);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH05",&NET_OP__BR__ETH05);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH06",&NET_OP__BR__ETH06);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH07",&NET_OP__BR__ETH07);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH08",&NET_OP__BR__ETH08);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH09",&NET_OP__BR__ETH09);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH10",&NET_OP__BR__ETH10);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH11",&NET_OP__BR__ETH11);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"OP (BR) ETH12",&NET_OP__BR__ETH12);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay",&NET_FlexRay);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"FlexRay2",&NET_FlexRay2);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN6 (VNET A)",&NET_LIN6__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LIN6 (VNET B)",&NET_LIN6__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN6 (VNET A)",&NET_HS_CAN6__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN6 (VNET B)",&NET_HS_CAN6__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN7 (VNET A)",&NET_HS_CAN7__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"HS CAN7 (VNET B)",&NET_HS_CAN7__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN2 (VNET A)",&NET_LSFT_CAN2__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"LSFT CAN2 (VNET B)",&NET_LSFT_CAN2__VNET_B_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"Ethernet (VNET A)",&NET_Ethernet__VNET_A_);
     CM_FindIndexForObjectFromName(g_uiHandle,0,L"Ethernet (VNET B)",&NET_Ethernet__VNET_B_);

    // database indexes
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_neoVI",&DB_Report_Message_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__PWM__neoVI",&DB_Report_Message__PWM__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__VCAN_RF__neoVI",&DB_Report_Message__VCAN_RF__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__neoVI_Fire2__neoVI",&DB_Report_Message__neoVI_Fire2__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Latitude__neoVI",&DB_Report_Message__GPS_Latitude__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Longitude__neoVI",&DB_Report_Message__GPS_Longitude__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Flags__neoVI",&DB_Report_Message__GPS_Flags__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Altitude__neoVI",&DB_Report_Message__GPS_Altitude__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Speed_Bearing__neoVI",&DB_Report_Message__GPS_Speed_Bearing__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Accuracy__neoVI",&DB_Report_Message__GPS_Accuracy__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__GPS_Time__neoVI",&DB_Report_Message__GPS_Time__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__WirelessneoVI_Sectors__neoVI",&DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__WirelessneoVI_Signals__neoVI",&DB_Report_Message__WirelessneoVI_Signals__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI",&DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger_Message_Data_Lost_neoVI",&DB_neoVI_Logger_Message_Data_Lost_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI",&DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Logger_woke_up_neoVI",&DB_neoVI_Logger_woke_up_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_1_Analog_Card__neoVI",&DB_Report_Message_1_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_2_Analog_Card__neoVI",&DB_Report_Message_2_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_3_Analog_Card__neoVI",&DB_Report_Message_3_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message_4_Analog_Card__neoVI",&DB_Report_Message_4_Analog_Card__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Time_Resync_neoVI",&DB_Time_Resync_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VNET_Clock_Edge_neoVI",&DB_VNET_Clock_Edge_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VNET_A_Stats_neoVI",&DB_VNET_A_Stats_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VNET_A_Reboot_neoVI",&DB_VNET_A_Reboot_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Went_To_Sleep_neoVI",&DB_neoVI_Went_To_Sleep_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Device_subsystem_restarted__neoVI",&DB_Device_subsystem_restarted__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Ethernet_DAQ_Report_neoVI",&DB_Ethernet_DAQ_Report_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Status_Update_neoVI",&DB_neoVI_Status_Update_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Scc_Status_neoVI",&DB_Scc_Status_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM_Inputs__neoVI",&DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM1__neoVI",&DB_Report_Message__Analog_Card_PWM1__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM2__neoVI",&DB_Report_Message__Analog_Card_PWM2__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM3__neoVI",&DB_Report_Message__Analog_Card_PWM3__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM4__neoVI",&DB_Report_Message__Analog_Card_PWM4__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM5__neoVI",&DB_Report_Message__Analog_Card_PWM5__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM6__neoVI",&DB_Report_Message__Analog_Card_PWM6__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM7__neoVI",&DB_Report_Message__Analog_Card_PWM7__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Report_Message__Analog_Card_PWM8__neoVI",&DB_Report_Message__Analog_Card_PWM8__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Device_Status_neoVI",&DB_neoVI_Device_Status_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_neoVI_Device_Status_2_neoVI",&DB_neoVI_Device_Status_2_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Trace_Logger_Status_neoVI",&DB_Trace_Logger_Status_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Trigger_neoVI",&DB_Trigger_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Ethernet_Status_neoVI",&DB_Ethernet_Status_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_OP__BR__Ethernet___Link_status_changed_neoVI",&DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_FIRE2_Report_Message_PWM_IN_1__neoVI",&DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_FIRE2_Report_Message_PWM_IN_2__neoVI",&DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Hardware_Latency_Test_neoVI",&DB_Hardware_Latency_Test_neoVI_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_SW1_HS_CAN",&DB_SW1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_SW2_HS_CAN",&DB_SW2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VehCfg_HS_CAN",&DB_VehCfg_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_RouteSG_ChasO_HS_CAN",&DB_RouteSG_ChasO_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_GW_HS_CAN",&DB_NM_GW_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_MMIctrCab_HS_CAN",&DB_MMIctrCab_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_TCO1_HS_CAN",&DB_TCO1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VehicleCtr_HS_CAN",&DB_VehicleCtr_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_BCM1_HS_CAN",&DB_BCM1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_BCM2_HS_CAN",&DB_BCM2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_BCM3_HS_CAN",&DB_BCM3_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_BCMlinCmd_HS_CAN",&DB_BCMlinCmd_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_OEL_HS_CAN",&DB_OEL_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_DM1_BCM_HS_CAN",&DB_DM1_BCM_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_BCM_HS_CAN",&DB_NM_BCM_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_TW_HS_CAN",&DB_TW_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_TPMS_HS_CAN",&DB_NM_TPMS_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_DCM1_HS_CAN",&DB_DCM1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_DCMcmd_HS_CAN",&DB_DCMcmd_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_DCM_HS_CAN",&DB_NM_DCM_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_AC_HS_CAN",&DB_NM_AC_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_IC1_HS_CAN",&DB_IC1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_IC_HS_CAN",&DB_NM_IC_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_OilQitT_HS_CAN",&DB_OilQitT_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_OilQitE_HS_CAN",&DB_OilQitE_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_OilQitA1_HS_CAN",&DB_OilQitA1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_OilQitA2_HS_CAN",&DB_OilQitA2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VCU_1_HS_CAN",&DB_VCU_1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_CCVS_EMS_HS_CAN",&DB_CCVS_EMS_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VDC1_HS_CAN",&DB_VDC1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_ERC1_HS_CAN",&DB_ERC1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_ETC2_HS_CAN",&DB_ETC2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_EEC1_HS_CAN",&DB_EEC1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_EBC1_BCM_HS_CAN",&DB_EBC1_BCM_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_EBC1_ABS_HS_CAN",&DB_EBC1_ABS_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_TESTER_HS_CAN",&DB_NM_TESTER_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_AC_MMI_HS_CAN",&DB_NM_AC_MMI_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_MMI_HS_CAN",&DB_NM_MMI_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_RCM_HS_CAN",&DB_NM_RCM_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_IPC_HS_CAN",&DB_NM_IPC_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_AC_HS_CAN_db88",&DB_NM_AC_HS_CAN_db88_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_Tester_HS_CAN",&DB_Tester_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_EVM_HS_CAN",&DB_NM_EVM_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_DM1_EVM_HS_CAN",&DB_DM1_EVM_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_EVM1_HS_CAN",&DB_EVM1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_TXJ_HS_CAN",&DB_NM_TXJ_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_DM1_TXJ_HS_CAN",&DB_DM1_TXJ_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VehicleCtr_HS_CAN_db95",&DB_VehicleCtr_HS_CAN_db95_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_VDS_HS_CAN",&DB_VDS_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_GPS_Item_HS_CAN",&DB_GPS_Item_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_PositionGPS_HS_CAN",&DB_PositionGPS_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_TD_HS_CAN",&DB_TD_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_TXJxMMI_HS_CAN",&DB_TXJxMMI_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_TCO1_HS_CAN_db101",&DB_TCO1_HS_CAN_db101_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_MMI_HS_CAN_db102",&DB_NM_MMI_HS_CAN_db102_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_DM1_MMI_HS_CAN",&DB_DM1_MMI_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_MMI_CtrDCM_HS_CAN",&DB_MMI_CtrDCM_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_MMIctrCab_HS_CAN_db105",&DB_MMIctrCab_HS_CAN_db105_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_MMI_NAV_HS_CAN",&DB_MMI_NAV_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_MMI_XY_HS_CAN",&DB_MMI_XY_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_MMIxTXJ_HS_CAN",&DB_MMIxTXJ_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_MMI2_HS_CAN",&DB_MMI2_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_MMI1_HS_CAN",&DB_MMI1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_NM_GW_HS_CAN_db111",&DB_NM_GW_HS_CAN_db111_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_DMI_GW_HS_CAN",&DB_DMI_GW_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_RouteSG_PT1_HS_CAN",&DB_RouteSG_PT1_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_RouteSG_ChasOil_HS_CAN",&DB_RouteSG_ChasOil_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_RouteSG_LNG_HS_CAN",&DB_RouteSG_LNG_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_RouteSG_DFS_HS_CAN",&DB_RouteSG_DFS_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,1,L"DB_switch2_HS_CAN",&DB_switch2_HS_CAN_Index);

    // messages indexes
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_NM_TXJ_HS_CAN",&MG_NM_TXJ_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,2,L"MG_NM_MMI_HS_CAN",&MG_NM_MMI_HS_CAN_Index);

    // tx messages indexes
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_NM_AC_HS_CAN",&TX_NM_AC_HS_CAN_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,3,L"TX_BCM1_HS_CAN",&TX_BCM1_HS_CAN_Index);

    // function block indexes
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_LimpHome_Ring",&FB_LimpHome_Ring_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_LimpHome_LimpHome",&FB_LimpHome_LimpHome_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_LimpHome_Alive",&FB_LimpHome_Alive_Index);
     CM_FindIndexForObjectFromName(g_uiHandle,4,L"FB_LimpHome_ALive_Ring",&FB_LimpHome_ALive_Ring_Index);

    // diagnostic job indexes

    // app signals indexes
     CM_FindIndexForObjectFromName(g_uiHandle,5,L"AS_NM_AC",&AS_NM_AC_Index);

}
void __stdcall CM_EveryMessage(int iNetwork, int iID, __int64 iTimeStampNanoSecondsHW, unsigned int iTimeStampMillisecondsOS,
									  int iNumDataBytes, int iBitField, unsigned char *p_btData)
{
    GenericMessage stMsg = {0};
    stMsg.iNetwork = iNetwork;
    stMsg.iID = iID;
    stMsg.iNumDataBytes = iNumDataBytes;
    if (stMsg.iNumDataBytes > sizeof(stMsg.btData))
        stMsg.iNumDataBytes = sizeof(stMsg.btData);
    stMsg.iBitField = iBitField;
    stMsg.iTimeStampMillisecondsOS = iTimeStampMillisecondsOS;
    stMsg.iTimeStampNanoSecondsHW = iTimeStampNanoSecondsHW;
    if (g_bUseExtendedIdBit && (stMsg.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        stMsg.iID = mkExtId(stMsg.iID);
    memcpy(stMsg.btData, p_btData, stMsg.iNumDataBytes);
    Spy_EveryMessage(&stMsg);

    if ((stMsg.iBitField & ATTR_CANFD_FRAME) || (stMsg.iNumDataBytes < iNumDataBytes))
    {
        GenericLongMessage stLongMsg = {0};
        stLongMsg.iNetwork = stMsg.iNetwork;
        stLongMsg.iID = stMsg.iID;
        stLongMsg.iNumDataBytes = iNumDataBytes;
        if (stLongMsg.iNumDataBytes > sizeof(stLongMsg.btData))
            stLongMsg.iNumDataBytes = sizeof(stLongMsg.btData);
        stLongMsg.iBitField = stMsg.iBitField;
        stLongMsg.iTimeStampMillisecondsOS = stMsg.iTimeStampMillisecondsOS;
        stLongMsg.iTimeStampNanoSecondsHW = stMsg.iTimeStampNanoSecondsHW;
        memcpy(stLongMsg.btData, p_btData, stLongMsg.iNumDataBytes);
        Spy_EveryLongMessage(&stLongMsg);
    }
}

void Spy_Lock()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_SPY_LOCK,0,0);
}
void Spy_Unlock()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_SPY_UNLOCK,0,0);
}

void SpyShowPanel(char * pWindowName, char * pPanelName)
{
    wchar_t szWideWindowName[1024];
    wchar_t szWidePanelName[1024];
    int iCount;

    iCount = MultiByteToWideChar(0, 0, pWindowName, (int)strlen(pWindowName), NULL, 0);
    MultiByteToWideChar(0, 0, pWindowName, (int)strlen(pWindowName), szWideWindowName, iCount);
    szWideWindowName[iCount] = 0;

    iCount = MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), NULL, 0);
    MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), szWidePanelName, iCount);
    szWidePanelName[iCount] = 0;

    // call the api
    CM_ShowPanel(g_uiHandle,szWideWindowName,szWidePanelName);
}

void SpyShowPanelW(wchar_t * pWindowName, wchar_t * pPanelName)
{
    CM_ShowPanel(g_uiHandle,pWindowName,pPanelName);
}

void SpySetControlProperty(char * pPanelName, char * pControlTag, int prop, void *pValue)
{
    wchar_t szWidePanelName[1024];
    wchar_t szWideControlTag[1024];
    int iCount;

    iCount = MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), NULL, 0);
    MultiByteToWideChar(0, 0, pPanelName, (int)strlen(pPanelName), szWidePanelName, iCount);
    szWidePanelName[iCount] = 0;

    iCount = MultiByteToWideChar(0, 0, pControlTag, (int)strlen(pControlTag), NULL, 0);
    MultiByteToWideChar(0, 0, pControlTag, (int)strlen(pControlTag), szWideControlTag, iCount);
    szWideControlTag[iCount] = 0;
    if (SPY_CTL_PROP_SET_CAPTION == prop)
    {
        wchar_t szWideValue[1024];
        iCount = MultiByteToWideChar(0, 0, pValue, (int)strlen(pValue), NULL, 0);
        MultiByteToWideChar(0, 0, pValue, (int)strlen(pValue), szWideValue, iCount);
        szWideValue[iCount] = 0;
        CM_SetControlProperty(g_uiHandle, szWidePanelName, szWideControlTag, prop, szWideValue);
    }
    else // call the api
        CM_SetControlProperty(g_uiHandle, szWidePanelName, szWideControlTag, prop, pValue);
}

void SpySetControlPropertyW(wchar_t * pPanelName, wchar_t * pControlTag, int prop, void *pValue)
{
    CM_SetControlProperty(g_uiHandle, pPanelName, pControlTag, prop, pValue);
}
int AS_NM_AC_Index = 0; // sig0
int FB_LimpHome_Ring_Index = 0;
void FB_LimpHome_Ring_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_LimpHome_Ring_Index,NULL);
}
void FB_LimpHome_Ring_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_LimpHome_Ring_Index,NULL);
}
void FB_LimpHome_Ring_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_LimpHome_Ring_Index,NULL);
}
void FB_LimpHome_Ring_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_LimpHome_Ring_Index,NULL);
}
double FB_LimpHome_Ring_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_LimpHome_Ring_Index,&dTemp);
    return dTemp;
}
double FB_LimpHome_Ring_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_LimpHome_Ring_Index,&dTemp);
    return dTemp;
}
double FB_LimpHome_Ring_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_LimpHome_Ring_Index,&dTemp);
    return dTemp;
}
int FB_LimpHome_LimpHome_Index = 1;
void FB_LimpHome_LimpHome_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_LimpHome_LimpHome_Index,NULL);
}
void FB_LimpHome_LimpHome_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_LimpHome_LimpHome_Index,NULL);
}
void FB_LimpHome_LimpHome_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_LimpHome_LimpHome_Index,NULL);
}
void FB_LimpHome_LimpHome_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_LimpHome_LimpHome_Index,NULL);
}
double FB_LimpHome_LimpHome_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_LimpHome_LimpHome_Index,&dTemp);
    return dTemp;
}
double FB_LimpHome_LimpHome_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_LimpHome_LimpHome_Index,&dTemp);
    return dTemp;
}
double FB_LimpHome_LimpHome_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_LimpHome_LimpHome_Index,&dTemp);
    return dTemp;
}
int FB_LimpHome_Alive_Index = 2;
void FB_LimpHome_Alive_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_LimpHome_Alive_Index,NULL);
}
void FB_LimpHome_Alive_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_LimpHome_Alive_Index,NULL);
}
void FB_LimpHome_Alive_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_LimpHome_Alive_Index,NULL);
}
void FB_LimpHome_Alive_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_LimpHome_Alive_Index,NULL);
}
double FB_LimpHome_Alive_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_LimpHome_Alive_Index,&dTemp);
    return dTemp;
}
double FB_LimpHome_Alive_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_LimpHome_Alive_Index,&dTemp);
    return dTemp;
}
double FB_LimpHome_Alive_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_LimpHome_Alive_Index,&dTemp);
    return dTemp;
}
int FB_LimpHome_ALive_Ring_Index = 3;
void FB_LimpHome_ALive_Ring_Start()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_START,FB_LimpHome_ALive_Ring_Index,NULL);
}
void FB_LimpHome_ALive_Ring_Stop()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_STOP,FB_LimpHome_ALive_Ring_Index,NULL);
}
void FB_LimpHome_ALive_Ring_Trigger()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_TRIGGER,FB_LimpHome_ALive_Ring_Index,NULL);
}
void FB_LimpHome_ALive_Ring_Save()
{
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_SAVE,FB_LimpHome_ALive_Ring_Index,NULL);
}
double FB_LimpHome_ALive_Ring_IsRunning()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISRUNNING,FB_LimpHome_ALive_Ring_Index,&dTemp);
    return dTemp;
}
double FB_LimpHome_ALive_Ring_IsTriggered()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_ISTRIGGERED,FB_LimpHome_ALive_Ring_Index,&dTemp);
    return dTemp;
}
double FB_LimpHome_ALive_Ring_NumCollected()
{
    double dTemp;
    CM_GetSetValue(g_uiHandle,CM_GETSET_FBLOCK_GET_NUMCOLLECTED,FB_LimpHome_ALive_Ring_Index,&dTemp);
    return dTemp;
}

int TX_NM_AC_HS_CAN_Index = 0;

void TX_NM_AC_HS_CAN_Init(TX_NM_AC_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_NM_AC_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AC_NM_Sleep_ACK = dValues[0];
    pMsg->AC_NM_Sleep_Ind = dValues[1];
    pMsg->AC_NM_Limphome = dValues[2];
    pMsg->AC_NM_Ring = dValues[3];
    pMsg->AC_NM_Alive = dValues[4];
    pMsg->AC_NM_DA = dValues[5];
    CM_MessageRawInit(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->AC_NM_Sleep_ACK_raw = (BYTE)nRawValues[0];
    pMsg->AC_NM_Sleep_Ind_raw = (BYTE)nRawValues[1];
    pMsg->AC_NM_Limphome_raw = (BYTE)nRawValues[2];
    pMsg->AC_NM_Ring_raw = (BYTE)nRawValues[3];
    pMsg->AC_NM_Alive_raw = (BYTE)nRawValues[4];
    pMsg->AC_NM_DA_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void TX_NM_AC_HS_CAN_LoadSignalValuesArray(TX_NM_AC_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AC_NM_Sleep_ACK;
    dArray[1] = pMsg->AC_NM_Sleep_Ind;
    dArray[2] = pMsg->AC_NM_Limphome;
    dArray[3] = pMsg->AC_NM_Ring;
    dArray[4] = pMsg->AC_NM_Alive;
    dArray[5] = pMsg->AC_NM_DA;
}

void TX_NM_AC_HS_CAN_LoadRawSignalValuesArray(TX_NM_AC_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AC_NM_Sleep_ACK_raw;
    nRawValues[1] = pMsg->AC_NM_Sleep_Ind_raw;
    nRawValues[2] = pMsg->AC_NM_Limphome_raw;
    nRawValues[3] = pMsg->AC_NM_Ring_raw;
    nRawValues[4] = pMsg->AC_NM_Alive_raw;
    nRawValues[5] = pMsg->AC_NM_DA_raw;
}

int TX_NM_AC_HS_CAN_Transmit(TX_NM_AC_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_NM_AC_HS_CAN_Init(pMsg);
    }

    TX_NM_AC_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int TX_NM_AC_HS_CAN_Transmit_raw(TX_NM_AC_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_NM_AC_HS_CAN_Init(pMsg);
    }

    TX_NM_AC_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int TX_NM_AC_HS_CAN_UpdateBytesFromSignals(TX_NM_AC_HS_CAN * pMsg)
{
    double dArray[6];

    TX_NM_AC_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int TX_NM_AC_HS_CAN_UpdateBytesFromRawSignals(TX_NM_AC_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    TX_NM_AC_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 2, TX_NM_AC_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int TX_NM_AC_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_NM_AC_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int TX_BCM1_HS_CAN_Index = 1;

void TX_BCM1_HS_CAN_Init(TX_BCM1_HS_CAN * pMsg)
{
    double dValues[26] = {0.0};
    uint64 nRawValues[26] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 2, 
    TX_BCM1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 26, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->CheckAllLightsSignalState = dValues[0];
    pMsg->WheelAlexDifferLockOperateError = dValues[1];
    pMsg->TrailerState_TrailerState = dValues[2];
    pMsg->WiperWashSt = dValues[3];
    pMsg->R_ReLSts = dValues[4];
    pMsg->L_ReLSts = dValues[5];
    pMsg->AtLgtSts = dValues[6];
    pMsg->TopLgtSts = dValues[7];
    pMsg->PosLgtOnWarr = dValues[8];
    pMsg->WiperModeSt = dValues[9];
    pMsg->FuelStolenAlmSig = dValues[10];
    pMsg->WheelDifferLockIndicatorLgt = dValues[11];
    pMsg->AxleDifferentialLockIndicatorLgt = dValues[12];
    pMsg->DayLgtSt = dValues[13];
    pMsg->HeadLgtWashStInd = dValues[14];
    pMsg->FuelMassSignal = dValues[15];
    pMsg->BackCabWorkingLightState = dValues[16];
    pMsg->RevLgtSt = dValues[17];
    pMsg->PosLgtStInd = dValues[18];
    pMsg->RFogLgtSt = dValues[19];
    pMsg->FrontFogLightSts = dValues[20];
    pMsg->BrkLgtSt = dValues[21];
    pMsg->R_TurnLgtSt = dValues[22];
    pMsg->L_TurnLgtSt = dValues[23];
    pMsg->LBeamSt = dValues[24];
    pMsg->HBeamSt = dValues[25];
    CM_MessageRawInit(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, nRawValues, 26, &iActualSignalMaxCount);
    pMsg->CheckAllLightsSignalState_raw = (BYTE)nRawValues[0];
    pMsg->WheelAlexDifferLockOperateError_raw = (BYTE)nRawValues[1];
    pMsg->TrailerState_TrailerState_raw = (BYTE)nRawValues[2];
    pMsg->WiperWashSt_raw = (BYTE)nRawValues[3];
    pMsg->R_ReLSts_raw = (BYTE)nRawValues[4];
    pMsg->L_ReLSts_raw = (BYTE)nRawValues[5];
    pMsg->AtLgtSts_raw = (BYTE)nRawValues[6];
    pMsg->TopLgtSts_raw = (BYTE)nRawValues[7];
    pMsg->PosLgtOnWarr_raw = (BYTE)nRawValues[8];
    pMsg->WiperModeSt_raw = (BYTE)nRawValues[9];
    pMsg->FuelStolenAlmSig_raw = (BYTE)nRawValues[10];
    pMsg->WheelDifferLockIndicatorLgt_raw = (BYTE)nRawValues[11];
    pMsg->AxleDifferentialLockIndicatorLgt_raw = (BYTE)nRawValues[12];
    pMsg->DayLgtSt_raw = (BYTE)nRawValues[13];
    pMsg->HeadLgtWashStInd_raw = (BYTE)nRawValues[14];
    pMsg->FuelMassSignal_raw = (BYTE)nRawValues[15];
    pMsg->BackCabWorkingLightState_raw = (BYTE)nRawValues[16];
    pMsg->RevLgtSt_raw = (BYTE)nRawValues[17];
    pMsg->PosLgtStInd_raw = (BYTE)nRawValues[18];
    pMsg->RFogLgtSt_raw = (BYTE)nRawValues[19];
    pMsg->FrontFogLightSts_raw = (BYTE)nRawValues[20];
    pMsg->BrkLgtSt_raw = (BYTE)nRawValues[21];
    pMsg->R_TurnLgtSt_raw = (BYTE)nRawValues[22];
    pMsg->L_TurnLgtSt_raw = (BYTE)nRawValues[23];
    pMsg->LBeamSt_raw = (BYTE)nRawValues[24];
    pMsg->HBeamSt_raw = (BYTE)nRawValues[25];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void TX_BCM1_HS_CAN_LoadSignalValuesArray(TX_BCM1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->CheckAllLightsSignalState;
    dArray[1] = pMsg->WheelAlexDifferLockOperateError;
    dArray[2] = pMsg->TrailerState_TrailerState;
    dArray[3] = pMsg->WiperWashSt;
    dArray[4] = pMsg->R_ReLSts;
    dArray[5] = pMsg->L_ReLSts;
    dArray[6] = pMsg->AtLgtSts;
    dArray[7] = pMsg->TopLgtSts;
    dArray[8] = pMsg->PosLgtOnWarr;
    dArray[9] = pMsg->WiperModeSt;
    dArray[10] = pMsg->FuelStolenAlmSig;
    dArray[11] = pMsg->WheelDifferLockIndicatorLgt;
    dArray[12] = pMsg->AxleDifferentialLockIndicatorLgt;
    dArray[13] = pMsg->DayLgtSt;
    dArray[14] = pMsg->HeadLgtWashStInd;
    dArray[15] = pMsg->FuelMassSignal;
    dArray[16] = pMsg->BackCabWorkingLightState;
    dArray[17] = pMsg->RevLgtSt;
    dArray[18] = pMsg->PosLgtStInd;
    dArray[19] = pMsg->RFogLgtSt;
    dArray[20] = pMsg->FrontFogLightSts;
    dArray[21] = pMsg->BrkLgtSt;
    dArray[22] = pMsg->R_TurnLgtSt;
    dArray[23] = pMsg->L_TurnLgtSt;
    dArray[24] = pMsg->LBeamSt;
    dArray[25] = pMsg->HBeamSt;
}

void TX_BCM1_HS_CAN_LoadRawSignalValuesArray(TX_BCM1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->CheckAllLightsSignalState_raw;
    nRawValues[1] = pMsg->WheelAlexDifferLockOperateError_raw;
    nRawValues[2] = pMsg->TrailerState_TrailerState_raw;
    nRawValues[3] = pMsg->WiperWashSt_raw;
    nRawValues[4] = pMsg->R_ReLSts_raw;
    nRawValues[5] = pMsg->L_ReLSts_raw;
    nRawValues[6] = pMsg->AtLgtSts_raw;
    nRawValues[7] = pMsg->TopLgtSts_raw;
    nRawValues[8] = pMsg->PosLgtOnWarr_raw;
    nRawValues[9] = pMsg->WiperModeSt_raw;
    nRawValues[10] = pMsg->FuelStolenAlmSig_raw;
    nRawValues[11] = pMsg->WheelDifferLockIndicatorLgt_raw;
    nRawValues[12] = pMsg->AxleDifferentialLockIndicatorLgt_raw;
    nRawValues[13] = pMsg->DayLgtSt_raw;
    nRawValues[14] = pMsg->HeadLgtWashStInd_raw;
    nRawValues[15] = pMsg->FuelMassSignal_raw;
    nRawValues[16] = pMsg->BackCabWorkingLightState_raw;
    nRawValues[17] = pMsg->RevLgtSt_raw;
    nRawValues[18] = pMsg->PosLgtStInd_raw;
    nRawValues[19] = pMsg->RFogLgtSt_raw;
    nRawValues[20] = pMsg->FrontFogLightSts_raw;
    nRawValues[21] = pMsg->BrkLgtSt_raw;
    nRawValues[22] = pMsg->R_TurnLgtSt_raw;
    nRawValues[23] = pMsg->L_TurnLgtSt_raw;
    nRawValues[24] = pMsg->LBeamSt_raw;
    nRawValues[25] = pMsg->HBeamSt_raw;
}

int TX_BCM1_HS_CAN_Transmit(TX_BCM1_HS_CAN * pMsg)
{
    double dArray[26];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_BCM1_HS_CAN_Init(pMsg);
    }

    TX_BCM1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 26);
}

int TX_BCM1_HS_CAN_Transmit_raw(TX_BCM1_HS_CAN * pMsg)
{
    uint64 nRawValues[26];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        TX_BCM1_HS_CAN_Init(pMsg);
    }

    TX_BCM1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 26);
}

int TX_BCM1_HS_CAN_UpdateBytesFromSignals(TX_BCM1_HS_CAN * pMsg)
{
    double dArray[26];

    TX_BCM1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, dArray, 26, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int TX_BCM1_HS_CAN_UpdateBytesFromRawSignals(TX_BCM1_HS_CAN * pMsg)
{
    uint64 nRawValues[26];

    TX_BCM1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 2, TX_BCM1_HS_CAN_Index, nRawValues, 26, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int TX_BCM1_HS_CAN_TransmitFast()
{
    unsigned char bt_DefaultBytes[8] = {0};
    return CM_TxFromSignals(g_uiHandle,4,TX_BCM1_HS_CAN_Index,bt_DefaultBytes,8,0,0,0);
}


int MG_NM_TXJ_HS_CAN_Index = 0;

void MG_NM_TXJ_HS_CAN_Init(MG_NM_TXJ_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_NM_TXJ_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TXJ_NM_Sleep_Ack = dValues[0];
    pMsg->TXJ_NM_Sleep_Ind = dValues[1];
    pMsg->TXJ_NM_Limphome = dValues[2];
    pMsg->TXJ_NM_Ring = dValues[3];
    pMsg->TXJ_NM_Alive = dValues[4];
    pMsg->TXJ_NM_DA = dValues[5];
    CM_MessageRawInit(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->TXJ_NM_Sleep_Ack_raw = (BYTE)nRawValues[0];
    pMsg->TXJ_NM_Sleep_Ind_raw = (BYTE)nRawValues[1];
    pMsg->TXJ_NM_Limphome_raw = (BYTE)nRawValues[2];
    pMsg->TXJ_NM_Ring_raw = (BYTE)nRawValues[3];
    pMsg->TXJ_NM_Alive_raw = (BYTE)nRawValues[4];
    pMsg->TXJ_NM_DA_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void MG_NM_TXJ_HS_CAN_LoadSignalValuesArray(MG_NM_TXJ_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TXJ_NM_Sleep_Ack;
    dArray[1] = pMsg->TXJ_NM_Sleep_Ind;
    dArray[2] = pMsg->TXJ_NM_Limphome;
    dArray[3] = pMsg->TXJ_NM_Ring;
    dArray[4] = pMsg->TXJ_NM_Alive;
    dArray[5] = pMsg->TXJ_NM_DA;
}

void MG_NM_TXJ_HS_CAN_LoadRawSignalValuesArray(MG_NM_TXJ_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TXJ_NM_Sleep_Ack_raw;
    nRawValues[1] = pMsg->TXJ_NM_Sleep_Ind_raw;
    nRawValues[2] = pMsg->TXJ_NM_Limphome_raw;
    nRawValues[3] = pMsg->TXJ_NM_Ring_raw;
    nRawValues[4] = pMsg->TXJ_NM_Alive_raw;
    nRawValues[5] = pMsg->TXJ_NM_DA_raw;
}

int MG_NM_TXJ_HS_CAN_Transmit(MG_NM_TXJ_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_NM_TXJ_HS_CAN_Init(pMsg);
    }

    MG_NM_TXJ_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int MG_NM_TXJ_HS_CAN_Transmit_raw(MG_NM_TXJ_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_NM_TXJ_HS_CAN_Init(pMsg);
    }

    MG_NM_TXJ_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int MG_NM_TXJ_HS_CAN_UpdateBytesFromSignals(MG_NM_TXJ_HS_CAN * pMsg)
{
    double dArray[6];

    MG_NM_TXJ_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int MG_NM_TXJ_HS_CAN_UpdateBytesFromRawSignals(MG_NM_TXJ_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    MG_NM_TXJ_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 1, MG_NM_TXJ_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int MG_NM_MMI_HS_CAN_Index = 1;

void MG_NM_MMI_HS_CAN_Init(MG_NM_MMI_HS_CAN * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 1, 
    MG_NM_MMI_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AC_NMDataField = dValues[0];
    pMsg->AC_NMSleepAck = dValues[1];
    pMsg->AC_NMSleepInd = dValues[2];
    pMsg->AC_NMLimphome = dValues[3];
    pMsg->AC_NMRing = dValues[4];
    pMsg->AC_NMAlive = dValues[5];
    pMsg->AC_NMDestAddress = dValues[6];
    CM_MessageRawInit(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->AC_NMDataField_raw = (uint64)nRawValues[0];
    pMsg->AC_NMSleepAck_raw = (BYTE)nRawValues[1];
    pMsg->AC_NMSleepInd_raw = (BYTE)nRawValues[2];
    pMsg->AC_NMLimphome_raw = (BYTE)nRawValues[3];
    pMsg->AC_NMRing_raw = (BYTE)nRawValues[4];
    pMsg->AC_NMAlive_raw = (BYTE)nRawValues[5];
    pMsg->AC_NMDestAddress_raw = (BYTE)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void MG_NM_MMI_HS_CAN_LoadSignalValuesArray(MG_NM_MMI_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AC_NMDataField;
    dArray[1] = pMsg->AC_NMSleepAck;
    dArray[2] = pMsg->AC_NMSleepInd;
    dArray[3] = pMsg->AC_NMLimphome;
    dArray[4] = pMsg->AC_NMRing;
    dArray[5] = pMsg->AC_NMAlive;
    dArray[6] = pMsg->AC_NMDestAddress;
}

void MG_NM_MMI_HS_CAN_LoadRawSignalValuesArray(MG_NM_MMI_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AC_NMDataField_raw;
    nRawValues[1] = pMsg->AC_NMSleepAck_raw;
    nRawValues[2] = pMsg->AC_NMSleepInd_raw;
    nRawValues[3] = pMsg->AC_NMLimphome_raw;
    nRawValues[4] = pMsg->AC_NMRing_raw;
    nRawValues[5] = pMsg->AC_NMAlive_raw;
    nRawValues[6] = pMsg->AC_NMDestAddress_raw;
}

int MG_NM_MMI_HS_CAN_Transmit(MG_NM_MMI_HS_CAN * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_NM_MMI_HS_CAN_Init(pMsg);
    }

    MG_NM_MMI_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int MG_NM_MMI_HS_CAN_Transmit_raw(MG_NM_MMI_HS_CAN * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        MG_NM_MMI_HS_CAN_Init(pMsg);
    }

    MG_NM_MMI_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int MG_NM_MMI_HS_CAN_UpdateBytesFromSignals(MG_NM_MMI_HS_CAN * pMsg)
{
    double dArray[7];

    MG_NM_MMI_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int MG_NM_MMI_HS_CAN_UpdateBytesFromRawSignals(MG_NM_MMI_HS_CAN * pMsg)
{
    uint64 nRawValues[7];

    MG_NM_MMI_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 1, MG_NM_MMI_HS_CAN_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message_neoVI_Index = 0;

void DB_Report_Message_neoVI_Init(DB_Report_Message_neoVI * pMsg)
{
    double dValues[14] = {0.0};
    uint64 nRawValues[14] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 14, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->MISC3_AIN = dValues[0];
    pMsg->MISC4_AIN = dValues[1];
    pMsg->MISC5_AIN = dValues[2];
    pMsg->MISC6_AIN = dValues[3];
    pMsg->MISC1 = dValues[4];
    pMsg->MISC2 = dValues[5];
    pMsg->MISC3 = dValues[6];
    pMsg->MISC4 = dValues[7];
    pMsg->MISC5 = dValues[8];
    pMsg->MISC6 = dValues[9];
    pMsg->LED1 = dValues[10];
    pMsg->LED2 = dValues[11];
    pMsg->LIN1 = dValues[12];
    pMsg->LIN2 = dValues[13];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_neoVI_Index, nRawValues, 14, &iActualSignalMaxCount);
    pMsg->MISC3_AIN_raw = (WORD)nRawValues[0];
    pMsg->MISC4_AIN_raw = (WORD)nRawValues[1];
    pMsg->MISC5_AIN_raw = (WORD)nRawValues[2];
    pMsg->MISC6_AIN_raw = (WORD)nRawValues[3];
    pMsg->MISC1_raw = (BYTE)nRawValues[4];
    pMsg->MISC2_raw = (BYTE)nRawValues[5];
    pMsg->MISC3_raw = (BYTE)nRawValues[6];
    pMsg->MISC4_raw = (BYTE)nRawValues[7];
    pMsg->MISC5_raw = (BYTE)nRawValues[8];
    pMsg->MISC6_raw = (BYTE)nRawValues[9];
    pMsg->LED1_raw = (BYTE)nRawValues[10];
    pMsg->LED2_raw = (BYTE)nRawValues[11];
    pMsg->LIN1_raw = (BYTE)nRawValues[12];
    pMsg->LIN2_raw = (BYTE)nRawValues[13];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_neoVI_LoadSignalValuesArray(DB_Report_Message_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->MISC3_AIN;
    dArray[1] = pMsg->MISC4_AIN;
    dArray[2] = pMsg->MISC5_AIN;
    dArray[3] = pMsg->MISC6_AIN;
    dArray[4] = pMsg->MISC1;
    dArray[5] = pMsg->MISC2;
    dArray[6] = pMsg->MISC3;
    dArray[7] = pMsg->MISC4;
    dArray[8] = pMsg->MISC5;
    dArray[9] = pMsg->MISC6;
    dArray[10] = pMsg->LED1;
    dArray[11] = pMsg->LED2;
    dArray[12] = pMsg->LIN1;
    dArray[13] = pMsg->LIN2;
}

void DB_Report_Message_neoVI_LoadRawSignalValuesArray(DB_Report_Message_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->MISC3_AIN_raw;
    nRawValues[1] = pMsg->MISC4_AIN_raw;
    nRawValues[2] = pMsg->MISC5_AIN_raw;
    nRawValues[3] = pMsg->MISC6_AIN_raw;
    nRawValues[4] = pMsg->MISC1_raw;
    nRawValues[5] = pMsg->MISC2_raw;
    nRawValues[6] = pMsg->MISC3_raw;
    nRawValues[7] = pMsg->MISC4_raw;
    nRawValues[8] = pMsg->MISC5_raw;
    nRawValues[9] = pMsg->MISC6_raw;
    nRawValues[10] = pMsg->LED1_raw;
    nRawValues[11] = pMsg->LED2_raw;
    nRawValues[12] = pMsg->LIN1_raw;
    nRawValues[13] = pMsg->LIN2_raw;
}

int DB_Report_Message_neoVI_Transmit(DB_Report_Message_neoVI * pMsg)
{
    double dArray[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_neoVI_Init(pMsg);
    }

    DB_Report_Message_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 14);
}

int DB_Report_Message_neoVI_Transmit_raw(DB_Report_Message_neoVI * pMsg)
{
    uint64 nRawValues[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_neoVI_Init(pMsg);
    }

    DB_Report_Message_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 14);
}

int DB_Report_Message_neoVI_UpdateBytesFromSignals(DB_Report_Message_neoVI * pMsg)
{
    double dArray[14];

    DB_Report_Message_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, dArray, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message_neoVI_UpdateBytesFromRawSignals(DB_Report_Message_neoVI * pMsg)
{
    uint64 nRawValues[14];

    DB_Report_Message_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_neoVI_Index, nRawValues, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__PWM__neoVI_Index = 1;

void DB_Report_Message__PWM__neoVI_Init(DB_Report_Message__PWM__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__PWM__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->PWM_In_1 = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->PWM_In_1_raw = (DWORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__PWM__neoVI_LoadSignalValuesArray(DB_Report_Message__PWM__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->PWM_In_1;
}

void DB_Report_Message__PWM__neoVI_LoadRawSignalValuesArray(DB_Report_Message__PWM__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->PWM_In_1_raw;
}

int DB_Report_Message__PWM__neoVI_Transmit(DB_Report_Message__PWM__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__PWM__neoVI_Init(pMsg);
    }

    DB_Report_Message__PWM__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__PWM__neoVI_Transmit_raw(DB_Report_Message__PWM__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__PWM__neoVI_Init(pMsg);
    }

    DB_Report_Message__PWM__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__PWM__neoVI_UpdateBytesFromSignals(DB_Report_Message__PWM__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__PWM__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__PWM__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__PWM__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__PWM__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__PWM__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__VCAN_RF__neoVI_Index = 2;

void DB_Report_Message__VCAN_RF__neoVI_Init(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    double dValues[10] = {0.0};
    uint64 nRawValues[10] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__VCAN_RF__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 10, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->MISC1_AIN = dValues[0];
    pMsg->MISC_1 = dValues[1];
    pMsg->MISC_2 = dValues[2];
    pMsg->MISC_3 = dValues[3];
    pMsg->MISC_4 = dValues[4];
    pMsg->Vehicle_Battery_Voltage = dValues[5];
    pMsg->Temperature = dValues[6];
    pMsg->Hardware_Revision = dValues[7];
    pMsg->RTC_Battery_Measure_Enabled = dValues[8];
    pMsg->RTC_Battery_Voltage = dValues[9];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, nRawValues, 10, &iActualSignalMaxCount);
    pMsg->MISC1_AIN_raw = (WORD)nRawValues[0];
    pMsg->MISC_1_raw = (BYTE)nRawValues[1];
    pMsg->MISC_2_raw = (BYTE)nRawValues[2];
    pMsg->MISC_3_raw = (BYTE)nRawValues[3];
    pMsg->MISC_4_raw = (BYTE)nRawValues[4];
    pMsg->Vehicle_Battery_Voltage_raw = (WORD)nRawValues[5];
    pMsg->Temperature_raw = (WORD)nRawValues[6];
    pMsg->Hardware_Revision_raw = (WORD)nRawValues[7];
    pMsg->RTC_Battery_Measure_Enabled_raw = (BYTE)nRawValues[8];
    pMsg->RTC_Battery_Voltage_raw = (WORD)nRawValues[9];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__VCAN_RF__neoVI_LoadSignalValuesArray(DB_Report_Message__VCAN_RF__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->MISC1_AIN;
    dArray[1] = pMsg->MISC_1;
    dArray[2] = pMsg->MISC_2;
    dArray[3] = pMsg->MISC_3;
    dArray[4] = pMsg->MISC_4;
    dArray[5] = pMsg->Vehicle_Battery_Voltage;
    dArray[6] = pMsg->Temperature;
    dArray[7] = pMsg->Hardware_Revision;
    dArray[8] = pMsg->RTC_Battery_Measure_Enabled;
    dArray[9] = pMsg->RTC_Battery_Voltage;
}

void DB_Report_Message__VCAN_RF__neoVI_LoadRawSignalValuesArray(DB_Report_Message__VCAN_RF__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->MISC1_AIN_raw;
    nRawValues[1] = pMsg->MISC_1_raw;
    nRawValues[2] = pMsg->MISC_2_raw;
    nRawValues[3] = pMsg->MISC_3_raw;
    nRawValues[4] = pMsg->MISC_4_raw;
    nRawValues[5] = pMsg->Vehicle_Battery_Voltage_raw;
    nRawValues[6] = pMsg->Temperature_raw;
    nRawValues[7] = pMsg->Hardware_Revision_raw;
    nRawValues[8] = pMsg->RTC_Battery_Measure_Enabled_raw;
    nRawValues[9] = pMsg->RTC_Battery_Voltage_raw;
}

int DB_Report_Message__VCAN_RF__neoVI_Transmit(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    double dArray[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__VCAN_RF__neoVI_Init(pMsg);
    }

    DB_Report_Message__VCAN_RF__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 10);
}

int DB_Report_Message__VCAN_RF__neoVI_Transmit_raw(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    uint64 nRawValues[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__VCAN_RF__neoVI_Init(pMsg);
    }

    DB_Report_Message__VCAN_RF__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 10);
}

int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    double dArray[10];

    DB_Report_Message__VCAN_RF__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, dArray, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__VCAN_RF__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__VCAN_RF__neoVI * pMsg)
{
    uint64 nRawValues[10];

    DB_Report_Message__VCAN_RF__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__VCAN_RF__neoVI_Index, nRawValues, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__neoVI_Fire2__neoVI_Index = 3;

void DB_Report_Message__neoVI_Fire2__neoVI_Init(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    double dValues[11] = {0.0};
    uint64 nRawValues[11] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__neoVI_Fire2__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 11, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->RTC_Battery = dValues[0];
    pMsg->Temperature = dValues[1];
    pMsg->Vehicle_Battery = dValues[2];
    pMsg->EMISC1_AIN = dValues[3];
    pMsg->EMISC2_AIN = dValues[4];
    pMsg->EMISC1_DIN = dValues[5];
    pMsg->EMISC2_DIN = dValues[6];
    pMsg->MISC5_DIN = dValues[7];
    pMsg->MISC6_DIN = dValues[8];
    pMsg->LED1 = dValues[9];
    pMsg->LED2 = dValues[10];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, nRawValues, 11, &iActualSignalMaxCount);
    pMsg->RTC_Battery_raw = (uint64)nRawValues[0];
    pMsg->Temperature_raw = (uint64)nRawValues[1];
    pMsg->Vehicle_Battery_raw = (uint64)nRawValues[2];
    pMsg->EMISC1_AIN_raw = (WORD)nRawValues[3];
    pMsg->EMISC2_AIN_raw = (WORD)nRawValues[4];
    pMsg->EMISC1_DIN_raw = (BYTE)nRawValues[5];
    pMsg->EMISC2_DIN_raw = (BYTE)nRawValues[6];
    pMsg->MISC5_DIN_raw = (BYTE)nRawValues[7];
    pMsg->MISC6_DIN_raw = (BYTE)nRawValues[8];
    pMsg->LED1_raw = (BYTE)nRawValues[9];
    pMsg->LED2_raw = (BYTE)nRawValues[10];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__neoVI_Fire2__neoVI_LoadSignalValuesArray(DB_Report_Message__neoVI_Fire2__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->RTC_Battery;
    dArray[1] = pMsg->Temperature;
    dArray[2] = pMsg->Vehicle_Battery;
    dArray[3] = pMsg->EMISC1_AIN;
    dArray[4] = pMsg->EMISC2_AIN;
    dArray[5] = pMsg->EMISC1_DIN;
    dArray[6] = pMsg->EMISC2_DIN;
    dArray[7] = pMsg->MISC5_DIN;
    dArray[8] = pMsg->MISC6_DIN;
    dArray[9] = pMsg->LED1;
    dArray[10] = pMsg->LED2;
}

void DB_Report_Message__neoVI_Fire2__neoVI_LoadRawSignalValuesArray(DB_Report_Message__neoVI_Fire2__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->RTC_Battery_raw;
    nRawValues[1] = pMsg->Temperature_raw;
    nRawValues[2] = pMsg->Vehicle_Battery_raw;
    nRawValues[3] = pMsg->EMISC1_AIN_raw;
    nRawValues[4] = pMsg->EMISC2_AIN_raw;
    nRawValues[5] = pMsg->EMISC1_DIN_raw;
    nRawValues[6] = pMsg->EMISC2_DIN_raw;
    nRawValues[7] = pMsg->MISC5_DIN_raw;
    nRawValues[8] = pMsg->MISC6_DIN_raw;
    nRawValues[9] = pMsg->LED1_raw;
    nRawValues[10] = pMsg->LED2_raw;
}

int DB_Report_Message__neoVI_Fire2__neoVI_Transmit(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    double dArray[11];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__neoVI_Fire2__neoVI_Init(pMsg);
    }

    DB_Report_Message__neoVI_Fire2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 11);
}

int DB_Report_Message__neoVI_Fire2__neoVI_Transmit_raw(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    uint64 nRawValues[11];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__neoVI_Fire2__neoVI_Init(pMsg);
    }

    DB_Report_Message__neoVI_Fire2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 11);
}

int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    double dArray[11];

    DB_Report_Message__neoVI_Fire2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, dArray, 11, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__neoVI_Fire2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__neoVI_Fire2__neoVI * pMsg)
{
    uint64 nRawValues[11];

    DB_Report_Message__neoVI_Fire2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__neoVI_Fire2__neoVI_Index, nRawValues, 11, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Latitude__neoVI_Index = 4;

void DB_Report_Message__GPS_Latitude__neoVI_Init(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Latitude__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Latitude = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Latitude_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Latitude__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Latitude__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Latitude;
}

void DB_Report_Message__GPS_Latitude__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Latitude__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Latitude_raw;
}

int DB_Report_Message__GPS_Latitude__neoVI_Transmit(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Latitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Latitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Latitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Latitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Latitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Latitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Latitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Latitude__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Latitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Latitude__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Longitude__neoVI_Index = 5;

void DB_Report_Message__GPS_Longitude__neoVI_Init(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Longitude__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Longitude = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Longitude_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Longitude__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Longitude__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Longitude;
}

void DB_Report_Message__GPS_Longitude__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Longitude__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Longitude_raw;
}

int DB_Report_Message__GPS_Longitude__neoVI_Transmit(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Longitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Longitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Longitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Longitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Longitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Longitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Longitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Longitude__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Longitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Longitude__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Flags__neoVI_Index = 6;

void DB_Report_Message__GPS_Flags__neoVI_Init(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Flags__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Update_Count = dValues[0];
    pMsg->GPS_Date_Available = dValues[1];
    pMsg->GPS_Time_Available = dValues[2];
    pMsg->GPS_Accuracy_Available = dValues[3];
    pMsg->GPS_Bearing_Available = dValues[4];
    pMsg->GPS_Speed_Available = dValues[5];
    pMsg->GPS_Altitude_Available = dValues[6];
    pMsg->GPS_Lat_Lon_Available = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->Update_Count_raw = (BYTE)nRawValues[0];
    pMsg->GPS_Date_Available_raw = (BYTE)nRawValues[1];
    pMsg->GPS_Time_Available_raw = (BYTE)nRawValues[2];
    pMsg->GPS_Accuracy_Available_raw = (BYTE)nRawValues[3];
    pMsg->GPS_Bearing_Available_raw = (BYTE)nRawValues[4];
    pMsg->GPS_Speed_Available_raw = (BYTE)nRawValues[5];
    pMsg->GPS_Altitude_Available_raw = (BYTE)nRawValues[6];
    pMsg->GPS_Lat_Lon_Available_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Flags__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Flags__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Update_Count;
    dArray[1] = pMsg->GPS_Date_Available;
    dArray[2] = pMsg->GPS_Time_Available;
    dArray[3] = pMsg->GPS_Accuracy_Available;
    dArray[4] = pMsg->GPS_Bearing_Available;
    dArray[5] = pMsg->GPS_Speed_Available;
    dArray[6] = pMsg->GPS_Altitude_Available;
    dArray[7] = pMsg->GPS_Lat_Lon_Available;
}

void DB_Report_Message__GPS_Flags__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Flags__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Update_Count_raw;
    nRawValues[1] = pMsg->GPS_Date_Available_raw;
    nRawValues[2] = pMsg->GPS_Time_Available_raw;
    nRawValues[3] = pMsg->GPS_Accuracy_Available_raw;
    nRawValues[4] = pMsg->GPS_Bearing_Available_raw;
    nRawValues[5] = pMsg->GPS_Speed_Available_raw;
    nRawValues[6] = pMsg->GPS_Altitude_Available_raw;
    nRawValues[7] = pMsg->GPS_Lat_Lon_Available_raw;
}

int DB_Report_Message__GPS_Flags__neoVI_Transmit(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Flags__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Flags__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_Report_Message__GPS_Flags__neoVI_Transmit_raw(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Flags__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Flags__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    double dArray[8];

    DB_Report_Message__GPS_Flags__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Flags__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Flags__neoVI * pMsg)
{
    uint64 nRawValues[8];

    DB_Report_Message__GPS_Flags__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Flags__neoVI_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Altitude__neoVI_Index = 7;

void DB_Report_Message__GPS_Altitude__neoVI_Init(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Altitude__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Altitude_Ellipse = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Altitude_Ellipse_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Altitude__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Altitude__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Altitude_Ellipse;
}

void DB_Report_Message__GPS_Altitude__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Altitude__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Altitude_Ellipse_raw;
}

int DB_Report_Message__GPS_Altitude__neoVI_Transmit(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Altitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Altitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Altitude__neoVI_Transmit_raw(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Altitude__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Altitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Altitude__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Altitude__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Altitude__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Altitude__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Altitude__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Speed_Bearing__neoVI_Index = 8;

void DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Speed = dValues[0];
    pMsg->Bearing = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Speed_raw = (DWORD)nRawValues[0];
    pMsg->Bearing_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Speed;
    dArray[1] = pMsg->Bearing;
}

void DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Speed_raw;
    nRawValues[1] = pMsg->Bearing_raw;
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_Transmit_raw(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Speed_Bearing__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Speed_Bearing__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Speed_Bearing__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__GPS_Speed_Bearing__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Speed_Bearing__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Accuracy__neoVI_Index = 9;

void DB_Report_Message__GPS_Accuracy__neoVI_Init(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Accuracy__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Accuracy = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Accuracy_raw = (DWORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Accuracy__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Accuracy__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Accuracy;
}

void DB_Report_Message__GPS_Accuracy__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Accuracy__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Accuracy_raw;
}

int DB_Report_Message__GPS_Accuracy__neoVI_Transmit(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Accuracy__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Accuracy__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Accuracy__neoVI_Transmit_raw(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Accuracy__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Accuracy__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Accuracy__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Accuracy__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Accuracy__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Accuracy__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Accuracy__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__GPS_Time__neoVI_Index = 10;

void DB_Report_Message__GPS_Time__neoVI_Init(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__GPS_Time__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Timestamp = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Timestamp_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__GPS_Time__neoVI_LoadSignalValuesArray(DB_Report_Message__GPS_Time__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Timestamp;
}

void DB_Report_Message__GPS_Time__neoVI_LoadRawSignalValuesArray(DB_Report_Message__GPS_Time__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Timestamp_raw;
}

int DB_Report_Message__GPS_Time__neoVI_Transmit(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Time__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Time__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message__GPS_Time__neoVI_Transmit_raw(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__GPS_Time__neoVI_Init(pMsg);
    }

    DB_Report_Message__GPS_Time__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromSignals(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message__GPS_Time__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__GPS_Time__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__GPS_Time__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message__GPS_Time__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__GPS_Time__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index = 11;

void DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->WiviStartSector = dValues[0];
    pMsg->WiviEndSector = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->WiviStartSector_raw = (DWORD)nRawValues[0];
    pMsg->WiviEndSector_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadSignalValuesArray(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->WiviStartSector;
    dArray[1] = pMsg->WiviEndSector;
}

void DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadRawSignalValuesArray(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->WiviStartSector_raw;
    nRawValues[1] = pMsg->WiviEndSector_raw;
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Sectors__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__WirelessneoVI_Sectors__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Sectors__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__WirelessneoVI_Sectors__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Sectors__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__WirelessneoVI_Signals__neoVI_Index = 12;

void DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->WiviJob = dValues[0];
    pMsg->WiviApkResponse = dValues[1];
    pMsg->WiviDataTransferMediumChoice = dValues[2];
    pMsg->WiviApkResponseTo = dValues[3];
    pMsg->WiviReserved0 = dValues[4];
    pMsg->WiviReserved1 = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->WiviJob_raw = (BYTE)nRawValues[0];
    pMsg->WiviApkResponse_raw = (BYTE)nRawValues[1];
    pMsg->WiviDataTransferMediumChoice_raw = (BYTE)nRawValues[2];
    pMsg->WiviApkResponseTo_raw = (BYTE)nRawValues[3];
    pMsg->WiviReserved0_raw = (BYTE)nRawValues[4];
    pMsg->WiviReserved1_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadSignalValuesArray(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->WiviJob;
    dArray[1] = pMsg->WiviApkResponse;
    dArray[2] = pMsg->WiviDataTransferMediumChoice;
    dArray[3] = pMsg->WiviApkResponseTo;
    dArray[4] = pMsg->WiviReserved0;
    dArray[5] = pMsg->WiviReserved1;
}

void DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadRawSignalValuesArray(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->WiviJob_raw;
    nRawValues[1] = pMsg->WiviApkResponse_raw;
    nRawValues[2] = pMsg->WiviDataTransferMediumChoice_raw;
    nRawValues[3] = pMsg->WiviApkResponseTo_raw;
    nRawValues[4] = pMsg->WiviReserved0_raw;
    nRawValues[5] = pMsg->WiviReserved1_raw;
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_Transmit_raw(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__WirelessneoVI_Signals__neoVI_Init(pMsg);
    }

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    double dArray[6];

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__WirelessneoVI_Signals__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__WirelessneoVI_Signals__neoVI * pMsg)
{
    uint64 nRawValues[6];

    DB_Report_Message__WirelessneoVI_Signals__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__WirelessneoVI_Signals__neoVI_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index = 13;

void DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Init(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Transmit_raw(DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_temporarily_disconnected_from_SD_Card_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Logger_Message_Data_Lost_neoVI_Index = 14;

void DB_neoVI_Logger_Message_Data_Lost_neoVI_Init(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Logger_Message_Data_Lost_neoVI_Transmit_raw(DB_neoVI_Logger_Message_Data_Lost_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_Message_Data_Lost_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index = 15;

void DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Init(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Transmit_raw(DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger___Extractor_skipped_invalid_record_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Logger_woke_up_neoVI_Index = 16;

void DB_neoVI_Logger_woke_up_neoVI_Init(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    double dValues[10] = {0.0};
    uint64 nRawValues[10] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Logger_woke_up_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 10, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->SleepFlags = dValues[0];
    pMsg->WakeupFlags = dValues[1];
    pMsg->WakeUpSms = dValues[2];
    pMsg->WakeupSlaveA = dValues[3];
    pMsg->WakeupSlaveB = dValues[4];
    pMsg->WakeupMainVnet = dValues[5];
    pMsg->WakeupUsb = dValues[6];
    pMsg->PowerBoot = dValues[7];
    pMsg->LowVbatSleep = dValues[8];
    pMsg->NoCmSleep = dValues[9];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, nRawValues, 10, &iActualSignalMaxCount);
    pMsg->SleepFlags_raw = (WORD)nRawValues[0];
    pMsg->WakeupFlags_raw = (WORD)nRawValues[1];
    pMsg->WakeUpSms_raw = (BYTE)nRawValues[2];
    pMsg->WakeupSlaveA_raw = (BYTE)nRawValues[3];
    pMsg->WakeupSlaveB_raw = (BYTE)nRawValues[4];
    pMsg->WakeupMainVnet_raw = (BYTE)nRawValues[5];
    pMsg->WakeupUsb_raw = (BYTE)nRawValues[6];
    pMsg->PowerBoot_raw = (BYTE)nRawValues[7];
    pMsg->LowVbatSleep_raw = (BYTE)nRawValues[8];
    pMsg->NoCmSleep_raw = (BYTE)nRawValues[9];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Logger_woke_up_neoVI_LoadSignalValuesArray(DB_neoVI_Logger_woke_up_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->SleepFlags;
    dArray[1] = pMsg->WakeupFlags;
    dArray[2] = pMsg->WakeUpSms;
    dArray[3] = pMsg->WakeupSlaveA;
    dArray[4] = pMsg->WakeupSlaveB;
    dArray[5] = pMsg->WakeupMainVnet;
    dArray[6] = pMsg->WakeupUsb;
    dArray[7] = pMsg->PowerBoot;
    dArray[8] = pMsg->LowVbatSleep;
    dArray[9] = pMsg->NoCmSleep;
}

void DB_neoVI_Logger_woke_up_neoVI_LoadRawSignalValuesArray(DB_neoVI_Logger_woke_up_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->SleepFlags_raw;
    nRawValues[1] = pMsg->WakeupFlags_raw;
    nRawValues[2] = pMsg->WakeUpSms_raw;
    nRawValues[3] = pMsg->WakeupSlaveA_raw;
    nRawValues[4] = pMsg->WakeupSlaveB_raw;
    nRawValues[5] = pMsg->WakeupMainVnet_raw;
    nRawValues[6] = pMsg->WakeupUsb_raw;
    nRawValues[7] = pMsg->PowerBoot_raw;
    nRawValues[8] = pMsg->LowVbatSleep_raw;
    nRawValues[9] = pMsg->NoCmSleep_raw;
}

int DB_neoVI_Logger_woke_up_neoVI_Transmit(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    double dArray[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Logger_woke_up_neoVI_Init(pMsg);
    }

    DB_neoVI_Logger_woke_up_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 10);
}

int DB_neoVI_Logger_woke_up_neoVI_Transmit_raw(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    uint64 nRawValues[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Logger_woke_up_neoVI_Init(pMsg);
    }

    DB_neoVI_Logger_woke_up_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 10);
}

int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    double dArray[10];

    DB_neoVI_Logger_woke_up_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, dArray, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_neoVI_Logger_woke_up_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Logger_woke_up_neoVI * pMsg)
{
    uint64 nRawValues[10];

    DB_neoVI_Logger_woke_up_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Logger_woke_up_neoVI_Index, nRawValues, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message_1_Analog_Card__neoVI_Index = 17;

void DB_Report_Message_1_Analog_Card__neoVI_Init(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_1_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Channel_A = dValues[0];
    pMsg->Channel_B = dValues[1];
    pMsg->Channel_1_Differential_ = dValues[2];
    pMsg->Channel_2_Differential_ = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->Channel_A_raw = (WORD)nRawValues[0];
    pMsg->Channel_B_raw = (WORD)nRawValues[1];
    pMsg->Channel_1_Differential__raw = (WORD)nRawValues[2];
    pMsg->Channel_2_Differential__raw = (WORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_1_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_1_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Channel_A;
    dArray[1] = pMsg->Channel_B;
    dArray[2] = pMsg->Channel_1_Differential_;
    dArray[3] = pMsg->Channel_2_Differential_;
}

void DB_Report_Message_1_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_1_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Channel_A_raw;
    nRawValues[1] = pMsg->Channel_B_raw;
    nRawValues[2] = pMsg->Channel_1_Differential__raw;
    nRawValues[3] = pMsg->Channel_2_Differential__raw;
}

int DB_Report_Message_1_Analog_Card__neoVI_Transmit(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_1_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_1_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_Report_Message_1_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_1_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_1_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    double dArray[4];

    DB_Report_Message_1_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message_1_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_1_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];

    DB_Report_Message_1_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_1_Analog_Card__neoVI_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message_2_Analog_Card__neoVI_Index = 18;

void DB_Report_Message_2_Analog_Card__neoVI_Init(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_2_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Channel_3_Differential_ = dValues[0];
    pMsg->Channel_4_Differential_ = dValues[1];
    pMsg->Channel_5_Differential_ = dValues[2];
    pMsg->Channel_6_Differential_ = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->Channel_3_Differential__raw = (WORD)nRawValues[0];
    pMsg->Channel_4_Differential__raw = (WORD)nRawValues[1];
    pMsg->Channel_5_Differential__raw = (WORD)nRawValues[2];
    pMsg->Channel_6_Differential__raw = (WORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_2_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_2_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Channel_3_Differential_;
    dArray[1] = pMsg->Channel_4_Differential_;
    dArray[2] = pMsg->Channel_5_Differential_;
    dArray[3] = pMsg->Channel_6_Differential_;
}

void DB_Report_Message_2_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_2_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Channel_3_Differential__raw;
    nRawValues[1] = pMsg->Channel_4_Differential__raw;
    nRawValues[2] = pMsg->Channel_5_Differential__raw;
    nRawValues[3] = pMsg->Channel_6_Differential__raw;
}

int DB_Report_Message_2_Analog_Card__neoVI_Transmit(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_2_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_2_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_Report_Message_2_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_2_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_2_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    double dArray[4];

    DB_Report_Message_2_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message_2_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_2_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[4];

    DB_Report_Message_2_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_2_Analog_Card__neoVI_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message_3_Analog_Card__neoVI_Index = 19;

void DB_Report_Message_3_Analog_Card__neoVI_Init(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_3_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Channel_7_Differential_ = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Channel_7_Differential__raw = (WORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_3_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_3_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Channel_7_Differential_;
}

void DB_Report_Message_3_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_3_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Channel_7_Differential__raw;
}

int DB_Report_Message_3_Analog_Card__neoVI_Transmit(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_3_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_3_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message_3_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_3_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_3_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message_3_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message_3_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_3_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message_3_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_3_Analog_Card__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message_4_Analog_Card__neoVI_Index = 20;

void DB_Report_Message_4_Analog_Card__neoVI_Init(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message_4_Analog_Card__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Timestamp = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Timestamp_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message_4_Analog_Card__neoVI_LoadSignalValuesArray(DB_Report_Message_4_Analog_Card__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Timestamp;
}

void DB_Report_Message_4_Analog_Card__neoVI_LoadRawSignalValuesArray(DB_Report_Message_4_Analog_Card__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Timestamp_raw;
}

int DB_Report_Message_4_Analog_Card__neoVI_Transmit(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_4_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_4_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Report_Message_4_Analog_Card__neoVI_Transmit_raw(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message_4_Analog_Card__neoVI_Init(pMsg);
    }

    DB_Report_Message_4_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    double dArray[1];

    DB_Report_Message_4_Analog_Card__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message_4_Analog_Card__neoVI_UpdateBytesFromRawSignals(DB_Report_Message_4_Analog_Card__neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Report_Message_4_Analog_Card__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message_4_Analog_Card__neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Time_Resync_neoVI_Index = 21;

void DB_Time_Resync_neoVI_Init(DB_Time_Resync_neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Time_Resync_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Timestamp = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Timestamp_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Time_Resync_neoVI_LoadSignalValuesArray(DB_Time_Resync_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Timestamp;
}

void DB_Time_Resync_neoVI_LoadRawSignalValuesArray(DB_Time_Resync_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Timestamp_raw;
}

int DB_Time_Resync_neoVI_Transmit(DB_Time_Resync_neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Time_Resync_neoVI_Init(pMsg);
    }

    DB_Time_Resync_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Time_Resync_neoVI_Transmit_raw(DB_Time_Resync_neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Time_Resync_neoVI_Init(pMsg);
    }

    DB_Time_Resync_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Time_Resync_neoVI_UpdateBytesFromSignals(DB_Time_Resync_neoVI * pMsg)
{
    double dArray[1];

    DB_Time_Resync_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Time_Resync_neoVI_UpdateBytesFromRawSignals(DB_Time_Resync_neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Time_Resync_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Time_Resync_neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_VNET_Clock_Edge_neoVI_Index = 22;

void DB_VNET_Clock_Edge_neoVI_Init(DB_VNET_Clock_Edge_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VNET_Clock_Edge_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_VNET_Clock_Edge_neoVI_Transmit(DB_VNET_Clock_Edge_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_VNET_Clock_Edge_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_VNET_Clock_Edge_neoVI_Transmit_raw(DB_VNET_Clock_Edge_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VNET_Clock_Edge_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_VNET_A_Stats_neoVI_Index = 23;

void DB_VNET_A_Stats_neoVI_Init(DB_VNET_A_Stats_neoVI * pMsg)
{
    double dValues[5] = {0.0};
    uint64 nRawValues[5] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VNET_A_Stats_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 5, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->msgTotal = dValues[0];
    pMsg->rxSize = dValues[1];
    pMsg->scCnt = dValues[2];
    pMsg->yields = dValues[3];
    pMsg->bytesRead = dValues[4];
    CM_MessageRawInit(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, nRawValues, 5, &iActualSignalMaxCount);
    pMsg->msgTotal_raw = (WORD)nRawValues[0];
    pMsg->rxSize_raw = (BYTE)nRawValues[1];
    pMsg->scCnt_raw = (BYTE)nRawValues[2];
    pMsg->yields_raw = (WORD)nRawValues[3];
    pMsg->bytesRead_raw = (WORD)nRawValues[4];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_VNET_A_Stats_neoVI_LoadSignalValuesArray(DB_VNET_A_Stats_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->msgTotal;
    dArray[1] = pMsg->rxSize;
    dArray[2] = pMsg->scCnt;
    dArray[3] = pMsg->yields;
    dArray[4] = pMsg->bytesRead;
}

void DB_VNET_A_Stats_neoVI_LoadRawSignalValuesArray(DB_VNET_A_Stats_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->msgTotal_raw;
    nRawValues[1] = pMsg->rxSize_raw;
    nRawValues[2] = pMsg->scCnt_raw;
    nRawValues[3] = pMsg->yields_raw;
    nRawValues[4] = pMsg->bytesRead_raw;
}

int DB_VNET_A_Stats_neoVI_Transmit(DB_VNET_A_Stats_neoVI * pMsg)
{
    double dArray[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VNET_A_Stats_neoVI_Init(pMsg);
    }

    DB_VNET_A_Stats_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 5);
}

int DB_VNET_A_Stats_neoVI_Transmit_raw(DB_VNET_A_Stats_neoVI * pMsg)
{
    uint64 nRawValues[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VNET_A_Stats_neoVI_Init(pMsg);
    }

    DB_VNET_A_Stats_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 5);
}

int DB_VNET_A_Stats_neoVI_UpdateBytesFromSignals(DB_VNET_A_Stats_neoVI * pMsg)
{
    double dArray[5];

    DB_VNET_A_Stats_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, dArray, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_VNET_A_Stats_neoVI_UpdateBytesFromRawSignals(DB_VNET_A_Stats_neoVI * pMsg)
{
    uint64 nRawValues[5];

    DB_VNET_A_Stats_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_VNET_A_Stats_neoVI_Index, nRawValues, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_VNET_A_Reboot_neoVI_Index = 24;

void DB_VNET_A_Reboot_neoVI_Init(DB_VNET_A_Reboot_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VNET_A_Reboot_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_VNET_A_Reboot_neoVI_Transmit(DB_VNET_A_Reboot_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_VNET_A_Reboot_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_VNET_A_Reboot_neoVI_Transmit_raw(DB_VNET_A_Reboot_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VNET_A_Reboot_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_neoVI_Went_To_Sleep_neoVI_Index = 25;

void DB_neoVI_Went_To_Sleep_neoVI_Init(DB_neoVI_Went_To_Sleep_neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Went_To_Sleep_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_neoVI_Went_To_Sleep_neoVI_Transmit(DB_neoVI_Went_To_Sleep_neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Went_To_Sleep_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_neoVI_Went_To_Sleep_neoVI_Transmit_raw(DB_neoVI_Went_To_Sleep_neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Went_To_Sleep_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_Device_subsystem_restarted__neoVI_Index = 26;

void DB_Device_subsystem_restarted__neoVI_Init(DB_Device_subsystem_restarted__neoVI * pMsg)
{
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Device_subsystem_restarted__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    NULL, 0, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

int DB_Device_subsystem_restarted__neoVI_Transmit(DB_Device_subsystem_restarted__neoVI * pMsg)
{
    return CM_TxFromSignals(g_uiHandle, 0, DB_Device_subsystem_restarted__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}

int DB_Device_subsystem_restarted__neoVI_Transmit_raw(DB_Device_subsystem_restarted__neoVI * pMsg)
{
    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Device_subsystem_restarted__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, 0, 0);
}


int DB_Ethernet_DAQ_Report_neoVI_Index = 27;

void DB_Ethernet_DAQ_Report_neoVI_Init(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    double dValues[14] = {0.0};
    uint64 nRawValues[14] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Ethernet_DAQ_Report_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 14, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Recording = dValues[0];
    pMsg->FPGA_Alive = dValues[1];
    pMsg->Bad_Chip = dValues[2];
    pMsg->Raw_MAC_Mode = dValues[3];
    pMsg->IPv4_Filter = dValues[4];
    pMsg->RxOverflow = dValues[5];
    pMsg->CmdBusy = dValues[6];
    pMsg->LogTO = dValues[7];
    pMsg->SockActivityTO = dValues[8];
    pMsg->FPGAComTO = dValues[9];
    pMsg->SockConfigTO = dValues[10];
    pMsg->SockDiscon = dValues[11];
    pMsg->WcfSM = dValues[12];
    pMsg->TxMsgsPending = dValues[13];
    CM_MessageRawInit(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, nRawValues, 14, &iActualSignalMaxCount);
    pMsg->Recording_raw = (BYTE)nRawValues[0];
    pMsg->FPGA_Alive_raw = (BYTE)nRawValues[1];
    pMsg->Bad_Chip_raw = (BYTE)nRawValues[2];
    pMsg->Raw_MAC_Mode_raw = (BYTE)nRawValues[3];
    pMsg->IPv4_Filter_raw = (BYTE)nRawValues[4];
    pMsg->RxOverflow_raw = (BYTE)nRawValues[5];
    pMsg->CmdBusy_raw = (BYTE)nRawValues[6];
    pMsg->LogTO_raw = (BYTE)nRawValues[7];
    pMsg->SockActivityTO_raw = (BYTE)nRawValues[8];
    pMsg->FPGAComTO_raw = (BYTE)nRawValues[9];
    pMsg->SockConfigTO_raw = (BYTE)nRawValues[10];
    pMsg->SockDiscon_raw = (BYTE)nRawValues[11];
    pMsg->WcfSM_raw = (BYTE)nRawValues[12];
    pMsg->TxMsgsPending_raw = (BYTE)nRawValues[13];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Ethernet_DAQ_Report_neoVI_LoadSignalValuesArray(DB_Ethernet_DAQ_Report_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Recording;
    dArray[1] = pMsg->FPGA_Alive;
    dArray[2] = pMsg->Bad_Chip;
    dArray[3] = pMsg->Raw_MAC_Mode;
    dArray[4] = pMsg->IPv4_Filter;
    dArray[5] = pMsg->RxOverflow;
    dArray[6] = pMsg->CmdBusy;
    dArray[7] = pMsg->LogTO;
    dArray[8] = pMsg->SockActivityTO;
    dArray[9] = pMsg->FPGAComTO;
    dArray[10] = pMsg->SockConfigTO;
    dArray[11] = pMsg->SockDiscon;
    dArray[12] = pMsg->WcfSM;
    dArray[13] = pMsg->TxMsgsPending;
}

void DB_Ethernet_DAQ_Report_neoVI_LoadRawSignalValuesArray(DB_Ethernet_DAQ_Report_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Recording_raw;
    nRawValues[1] = pMsg->FPGA_Alive_raw;
    nRawValues[2] = pMsg->Bad_Chip_raw;
    nRawValues[3] = pMsg->Raw_MAC_Mode_raw;
    nRawValues[4] = pMsg->IPv4_Filter_raw;
    nRawValues[5] = pMsg->RxOverflow_raw;
    nRawValues[6] = pMsg->CmdBusy_raw;
    nRawValues[7] = pMsg->LogTO_raw;
    nRawValues[8] = pMsg->SockActivityTO_raw;
    nRawValues[9] = pMsg->FPGAComTO_raw;
    nRawValues[10] = pMsg->SockConfigTO_raw;
    nRawValues[11] = pMsg->SockDiscon_raw;
    nRawValues[12] = pMsg->WcfSM_raw;
    nRawValues[13] = pMsg->TxMsgsPending_raw;
}

int DB_Ethernet_DAQ_Report_neoVI_Transmit(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    double dArray[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Ethernet_DAQ_Report_neoVI_Init(pMsg);
    }

    DB_Ethernet_DAQ_Report_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 14);
}

int DB_Ethernet_DAQ_Report_neoVI_Transmit_raw(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    uint64 nRawValues[14];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Ethernet_DAQ_Report_neoVI_Init(pMsg);
    }

    DB_Ethernet_DAQ_Report_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 14);
}

int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    double dArray[14];

    DB_Ethernet_DAQ_Report_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, dArray, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Ethernet_DAQ_Report_neoVI_UpdateBytesFromRawSignals(DB_Ethernet_DAQ_Report_neoVI * pMsg)
{
    uint64 nRawValues[14];

    DB_Ethernet_DAQ_Report_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Ethernet_DAQ_Report_neoVI_Index, nRawValues, 14, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_neoVI_Status_Update_neoVI_Index = 28;

void DB_neoVI_Status_Update_neoVI_Init(DB_neoVI_Status_Update_neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Status_Update_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Type = dValues[0];
    pMsg->ChangeCount = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Type_raw = (BYTE)nRawValues[0];
    pMsg->ChangeCount_raw = (BYTE)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Status_Update_neoVI_LoadSignalValuesArray(DB_neoVI_Status_Update_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Type;
    dArray[1] = pMsg->ChangeCount;
}

void DB_neoVI_Status_Update_neoVI_LoadRawSignalValuesArray(DB_neoVI_Status_Update_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Type_raw;
    nRawValues[1] = pMsg->ChangeCount_raw;
}

int DB_neoVI_Status_Update_neoVI_Transmit(DB_neoVI_Status_Update_neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Status_Update_neoVI_Init(pMsg);
    }

    DB_neoVI_Status_Update_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_neoVI_Status_Update_neoVI_Transmit_raw(DB_neoVI_Status_Update_neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Status_Update_neoVI_Init(pMsg);
    }

    DB_neoVI_Status_Update_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_neoVI_Status_Update_neoVI_UpdateBytesFromSignals(DB_neoVI_Status_Update_neoVI * pMsg)
{
    double dArray[2];

    DB_neoVI_Status_Update_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_neoVI_Status_Update_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Status_Update_neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_neoVI_Status_Update_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Status_Update_neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Scc_Status_neoVI_Index = 29;

void DB_Scc_Status_neoVI_Init(DB_Scc_Status_neoVI * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Scc_Status_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->FvA = dValues[0];
    pMsg->ScA = dValues[1];
    pMsg->Atv = dValues[2];
    pMsg->sip = dValues[3];
    pMsg->pt = dValues[4];
    pMsg->Req = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->FvA_raw = (BYTE)nRawValues[0];
    pMsg->ScA_raw = (BYTE)nRawValues[1];
    pMsg->Atv_raw = (BYTE)nRawValues[2];
    pMsg->sip_raw = (BYTE)nRawValues[3];
    pMsg->pt_raw = (DWORD)nRawValues[4];
    pMsg->Req_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Scc_Status_neoVI_LoadSignalValuesArray(DB_Scc_Status_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->FvA;
    dArray[1] = pMsg->ScA;
    dArray[2] = pMsg->Atv;
    dArray[3] = pMsg->sip;
    dArray[4] = pMsg->pt;
    dArray[5] = pMsg->Req;
}

void DB_Scc_Status_neoVI_LoadRawSignalValuesArray(DB_Scc_Status_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->FvA_raw;
    nRawValues[1] = pMsg->ScA_raw;
    nRawValues[2] = pMsg->Atv_raw;
    nRawValues[3] = pMsg->sip_raw;
    nRawValues[4] = pMsg->pt_raw;
    nRawValues[5] = pMsg->Req_raw;
}

int DB_Scc_Status_neoVI_Transmit(DB_Scc_Status_neoVI * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Scc_Status_neoVI_Init(pMsg);
    }

    DB_Scc_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_Scc_Status_neoVI_Transmit_raw(DB_Scc_Status_neoVI * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Scc_Status_neoVI_Init(pMsg);
    }

    DB_Scc_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_Scc_Status_neoVI_UpdateBytesFromSignals(DB_Scc_Status_neoVI * pMsg)
{
    double dArray[6];

    DB_Scc_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Scc_Status_neoVI_UpdateBytesFromRawSignals(DB_Scc_Status_neoVI * pMsg)
{
    uint64 nRawValues[6];

    DB_Scc_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Scc_Status_neoVI_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index = 30;

void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->PWM1_IN = dValues[0];
    pMsg->PWM2_IN = dValues[1];
    pMsg->PWM3_IN = dValues[2];
    pMsg->PWM4_IN = dValues[3];
    pMsg->PWM5_IN = dValues[4];
    pMsg->PWM6_IN = dValues[5];
    pMsg->PWM7_IN = dValues[6];
    pMsg->PWM8_IN = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->PWM1_IN_raw = (BYTE)nRawValues[0];
    pMsg->PWM2_IN_raw = (BYTE)nRawValues[1];
    pMsg->PWM3_IN_raw = (BYTE)nRawValues[2];
    pMsg->PWM4_IN_raw = (BYTE)nRawValues[3];
    pMsg->PWM5_IN_raw = (BYTE)nRawValues[4];
    pMsg->PWM6_IN_raw = (BYTE)nRawValues[5];
    pMsg->PWM7_IN_raw = (BYTE)nRawValues[6];
    pMsg->PWM8_IN_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->PWM1_IN;
    dArray[1] = pMsg->PWM2_IN;
    dArray[2] = pMsg->PWM3_IN;
    dArray[3] = pMsg->PWM4_IN;
    dArray[4] = pMsg->PWM5_IN;
    dArray[5] = pMsg->PWM6_IN;
    dArray[6] = pMsg->PWM7_IN;
    dArray[7] = pMsg->PWM8_IN;
}

void DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->PWM1_IN_raw;
    nRawValues[1] = pMsg->PWM2_IN_raw;
    nRawValues[2] = pMsg->PWM3_IN_raw;
    nRawValues[3] = pMsg->PWM4_IN_raw;
    nRawValues[4] = pMsg->PWM5_IN_raw;
    nRawValues[5] = pMsg->PWM6_IN_raw;
    nRawValues[6] = pMsg->PWM7_IN_raw;
    nRawValues[7] = pMsg->PWM8_IN_raw;
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    double dArray[8];

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM_Inputs__neoVI * pMsg)
{
    uint64 nRawValues[8];

    DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM_Inputs__neoVI_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM1__neoVI_Index = 31;

void DB_Report_Message__Analog_Card_PWM1__neoVI_Init(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM1__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM1__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM1__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM1__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM1__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM1__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM1__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM1__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM1__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM2__neoVI_Index = 32;

void DB_Report_Message__Analog_Card_PWM2__neoVI_Init(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM2__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM2__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM2__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM2__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM2__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM2__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM2__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM2__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM3__neoVI_Index = 33;

void DB_Report_Message__Analog_Card_PWM3__neoVI_Init(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM3__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM3__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM3__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM3__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM3__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM3__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM3__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM3__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM3__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM4__neoVI_Index = 34;

void DB_Report_Message__Analog_Card_PWM4__neoVI_Init(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM4__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM4__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM4__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM4__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM4__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM4__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM4__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM4__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM4__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM5__neoVI_Index = 35;

void DB_Report_Message__Analog_Card_PWM5__neoVI_Init(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM5__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM5__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM5__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM5__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM5__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM5__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM5__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM5__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM5__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM6__neoVI_Index = 36;

void DB_Report_Message__Analog_Card_PWM6__neoVI_Init(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM6__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM6__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM6__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM6__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM6__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM6__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM6__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM6__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM6__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM7__neoVI_Index = 37;

void DB_Report_Message__Analog_Card_PWM7__neoVI_Init(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM7__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM7__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM7__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM7__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM7__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM7__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM7__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM7__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM7__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Report_Message__Analog_Card_PWM8__neoVI_Index = 38;

void DB_Report_Message__Analog_Card_PWM8__neoVI_Init(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Report_Message__Analog_Card_PWM8__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Pulse_Width_ms_ = dValues[0];
    pMsg->Period_ms_ = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Pulse_Width_ms__raw = (DWORD)nRawValues[0];
    pMsg->Period_ms__raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Report_Message__Analog_Card_PWM8__neoVI_LoadSignalValuesArray(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Pulse_Width_ms_;
    dArray[1] = pMsg->Period_ms_;
}

void DB_Report_Message__Analog_Card_PWM8__neoVI_LoadRawSignalValuesArray(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Pulse_Width_ms__raw;
    nRawValues[1] = pMsg->Period_ms__raw;
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM8__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_Transmit_raw(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Report_Message__Analog_Card_PWM8__neoVI_Init(pMsg);
    }

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    double dArray[2];

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Report_Message__Analog_Card_PWM8__neoVI_UpdateBytesFromRawSignals(DB_Report_Message__Analog_Card_PWM8__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_Report_Message__Analog_Card_PWM8__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Report_Message__Analog_Card_PWM8__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_neoVI_Device_Status_neoVI_Index = 39;

void DB_neoVI_Device_Status_neoVI_Init(DB_neoVI_Device_Status_neoVI * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Device_Status_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->HID_Temperature__C_ = dValues[0];
    pMsg->HID_Bus_Voltage__V_ = dValues[1];
    pMsg->VNET_Temperature__C_ = dValues[2];
    pMsg->VNET_Bus_Voltage__V_ = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->HID_Temperature__C__raw = (WORD)nRawValues[0];
    pMsg->HID_Bus_Voltage__V__raw = (WORD)nRawValues[1];
    pMsg->VNET_Temperature__C__raw = (WORD)nRawValues[2];
    pMsg->VNET_Bus_Voltage__V__raw = (WORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Device_Status_neoVI_LoadSignalValuesArray(DB_neoVI_Device_Status_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->HID_Temperature__C_;
    dArray[1] = pMsg->HID_Bus_Voltage__V_;
    dArray[2] = pMsg->VNET_Temperature__C_;
    dArray[3] = pMsg->VNET_Bus_Voltage__V_;
}

void DB_neoVI_Device_Status_neoVI_LoadRawSignalValuesArray(DB_neoVI_Device_Status_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->HID_Temperature__C__raw;
    nRawValues[1] = pMsg->HID_Bus_Voltage__V__raw;
    nRawValues[2] = pMsg->VNET_Temperature__C__raw;
    nRawValues[3] = pMsg->VNET_Bus_Voltage__V__raw;
}

int DB_neoVI_Device_Status_neoVI_Transmit(DB_neoVI_Device_Status_neoVI * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_neoVI_Device_Status_neoVI_Transmit_raw(DB_neoVI_Device_Status_neoVI * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_neoVI_Device_Status_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_neoVI * pMsg)
{
    double dArray[4];

    DB_neoVI_Device_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_neoVI_Device_Status_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_neoVI * pMsg)
{
    uint64 nRawValues[4];

    DB_neoVI_Device_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_neoVI_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_neoVI_Device_Status_2_neoVI_Index = 40;

void DB_neoVI_Device_Status_2_neoVI_Init(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_neoVI_Device_Status_2_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Disk_Space_Avail__WiVI__KB = dValues[0];
    pMsg->Power_Supply_Voltage = dValues[1];
    pMsg->Temperature__C_ = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->Disk_Space_Avail__WiVI__KB_raw = (DWORD)nRawValues[0];
    pMsg->Power_Supply_Voltage_raw = (WORD)nRawValues[1];
    pMsg->Temperature__C__raw = (WORD)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_neoVI_Device_Status_2_neoVI_LoadSignalValuesArray(DB_neoVI_Device_Status_2_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Disk_Space_Avail__WiVI__KB;
    dArray[1] = pMsg->Power_Supply_Voltage;
    dArray[2] = pMsg->Temperature__C_;
}

void DB_neoVI_Device_Status_2_neoVI_LoadRawSignalValuesArray(DB_neoVI_Device_Status_2_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Disk_Space_Avail__WiVI__KB_raw;
    nRawValues[1] = pMsg->Power_Supply_Voltage_raw;
    nRawValues[2] = pMsg->Temperature__C__raw;
}

int DB_neoVI_Device_Status_2_neoVI_Transmit(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_2_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_2_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_neoVI_Device_Status_2_neoVI_Transmit_raw(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_neoVI_Device_Status_2_neoVI_Init(pMsg);
    }

    DB_neoVI_Device_Status_2_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromSignals(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    double dArray[3];

    DB_neoVI_Device_Status_2_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_neoVI_Device_Status_2_neoVI_UpdateBytesFromRawSignals(DB_neoVI_Device_Status_2_neoVI * pMsg)
{
    uint64 nRawValues[3];

    DB_neoVI_Device_Status_2_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_neoVI_Device_Status_2_neoVI_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Trace_Logger_Status_neoVI_Index = 41;

void DB_Trace_Logger_Status_neoVI_Init(DB_Trace_Logger_Status_neoVI * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Trace_Logger_Status_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->State = dValues[0];
    pMsg->Debug_Level = dValues[1];
    pMsg->IP_MSB_ = dValues[2];
    pMsg->IP = dValues[3];
    pMsg->IP_sig4 = dValues[4];
    pMsg->IP_LSB_ = dValues[5];
    pMsg->Port = dValues[6];
    CM_MessageRawInit(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->State_raw = (BYTE)nRawValues[0];
    pMsg->Debug_Level_raw = (BYTE)nRawValues[1];
    pMsg->IP_MSB__raw = (BYTE)nRawValues[2];
    pMsg->IP_raw = (BYTE)nRawValues[3];
    pMsg->IP_sig4_raw = (BYTE)nRawValues[4];
    pMsg->IP_LSB__raw = (BYTE)nRawValues[5];
    pMsg->Port_raw = (WORD)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Trace_Logger_Status_neoVI_LoadSignalValuesArray(DB_Trace_Logger_Status_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->State;
    dArray[1] = pMsg->Debug_Level;
    dArray[2] = pMsg->IP_MSB_;
    dArray[3] = pMsg->IP;
    dArray[4] = pMsg->IP_sig4;
    dArray[5] = pMsg->IP_LSB_;
    dArray[6] = pMsg->Port;
}

void DB_Trace_Logger_Status_neoVI_LoadRawSignalValuesArray(DB_Trace_Logger_Status_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->State_raw;
    nRawValues[1] = pMsg->Debug_Level_raw;
    nRawValues[2] = pMsg->IP_MSB__raw;
    nRawValues[3] = pMsg->IP_raw;
    nRawValues[4] = pMsg->IP_sig4_raw;
    nRawValues[5] = pMsg->IP_LSB__raw;
    nRawValues[6] = pMsg->Port_raw;
}

int DB_Trace_Logger_Status_neoVI_Transmit(DB_Trace_Logger_Status_neoVI * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trace_Logger_Status_neoVI_Init(pMsg);
    }

    DB_Trace_Logger_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int DB_Trace_Logger_Status_neoVI_Transmit_raw(DB_Trace_Logger_Status_neoVI * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trace_Logger_Status_neoVI_Init(pMsg);
    }

    DB_Trace_Logger_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int DB_Trace_Logger_Status_neoVI_UpdateBytesFromSignals(DB_Trace_Logger_Status_neoVI * pMsg)
{
    double dArray[7];

    DB_Trace_Logger_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Trace_Logger_Status_neoVI_UpdateBytesFromRawSignals(DB_Trace_Logger_Status_neoVI * pMsg)
{
    uint64 nRawValues[7];

    DB_Trace_Logger_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Trace_Logger_Status_neoVI_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Trigger_neoVI_Index = 42;

void DB_Trigger_neoVI_Init(DB_Trigger_neoVI * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Trigger_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Logger_triggered = dValues[0];
    pMsg->Pre_trigger_size = dValues[1];
    pMsg->Collection_index = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_Trigger_neoVI_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->Logger_triggered_raw = (BYTE)nRawValues[0];
    pMsg->Pre_trigger_size_raw = (DWORD)nRawValues[1];
    pMsg->Collection_index_raw = (BYTE)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Trigger_neoVI_LoadSignalValuesArray(DB_Trigger_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Logger_triggered;
    dArray[1] = pMsg->Pre_trigger_size;
    dArray[2] = pMsg->Collection_index;
}

void DB_Trigger_neoVI_LoadRawSignalValuesArray(DB_Trigger_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Logger_triggered_raw;
    nRawValues[1] = pMsg->Pre_trigger_size_raw;
    nRawValues[2] = pMsg->Collection_index_raw;
}

int DB_Trigger_neoVI_Transmit(DB_Trigger_neoVI * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trigger_neoVI_Init(pMsg);
    }

    DB_Trigger_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_Trigger_neoVI_Transmit_raw(DB_Trigger_neoVI * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Trigger_neoVI_Init(pMsg);
    }

    DB_Trigger_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_Trigger_neoVI_UpdateBytesFromSignals(DB_Trigger_neoVI * pMsg)
{
    double dArray[3];

    DB_Trigger_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Trigger_neoVI_UpdateBytesFromRawSignals(DB_Trigger_neoVI * pMsg)
{
    uint64 nRawValues[3];

    DB_Trigger_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Trigger_neoVI_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Ethernet_Status_neoVI_Index = 43;

void DB_Ethernet_Status_neoVI_Init(DB_Ethernet_Status_neoVI * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Ethernet_Status_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Link_Status = dValues[0];
    pMsg->Link_Speed = dValues[1];
    pMsg->Link_Duplex = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->Link_Status_raw = (BYTE)nRawValues[0];
    pMsg->Link_Speed_raw = (BYTE)nRawValues[1];
    pMsg->Link_Duplex_raw = (BYTE)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Ethernet_Status_neoVI_LoadSignalValuesArray(DB_Ethernet_Status_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Link_Status;
    dArray[1] = pMsg->Link_Speed;
    dArray[2] = pMsg->Link_Duplex;
}

void DB_Ethernet_Status_neoVI_LoadRawSignalValuesArray(DB_Ethernet_Status_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Link_Status_raw;
    nRawValues[1] = pMsg->Link_Speed_raw;
    nRawValues[2] = pMsg->Link_Duplex_raw;
}

int DB_Ethernet_Status_neoVI_Transmit(DB_Ethernet_Status_neoVI * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Ethernet_Status_neoVI_Init(pMsg);
    }

    DB_Ethernet_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_Ethernet_Status_neoVI_Transmit_raw(DB_Ethernet_Status_neoVI * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Ethernet_Status_neoVI_Init(pMsg);
    }

    DB_Ethernet_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_Ethernet_Status_neoVI_UpdateBytesFromSignals(DB_Ethernet_Status_neoVI * pMsg)
{
    double dArray[3];

    DB_Ethernet_Status_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Ethernet_Status_neoVI_UpdateBytesFromRawSignals(DB_Ethernet_Status_neoVI * pMsg)
{
    uint64 nRawValues[3];

    DB_Ethernet_Status_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Ethernet_Status_neoVI_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index = 44;

void DB_OP__BR__Ethernet___Link_status_changed_neoVI_Init(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Network = dValues[0];
    pMsg->Link_Status = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Network_raw = (BYTE)nRawValues[0];
    pMsg->Link_Status_raw = (BYTE)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadSignalValuesArray(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Network;
    dArray[1] = pMsg->Link_Status;
}

void DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadRawSignalValuesArray(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Network_raw;
    nRawValues[1] = pMsg->Link_Status_raw;
}

int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Transmit(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OP__BR__Ethernet___Link_status_changed_neoVI_Init(pMsg);
    }

    DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_OP__BR__Ethernet___Link_status_changed_neoVI_Transmit_raw(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OP__BR__Ethernet___Link_status_changed_neoVI_Init(pMsg);
    }

    DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_OP__BR__Ethernet___Link_status_changed_neoVI_UpdateBytesFromSignals(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg)
{
    double dArray[2];

    DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_OP__BR__Ethernet___Link_status_changed_neoVI_UpdateBytesFromRawSignals(DB_OP__BR__Ethernet___Link_status_changed_neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_OP__BR__Ethernet___Link_status_changed_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_OP__BR__Ethernet___Link_status_changed_neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index = 45;

void DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Init(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Period = dValues[0];
    pMsg->Pulse_Width = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Period_raw = (DWORD)nRawValues[0];
    pMsg->Pulse_Width_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadSignalValuesArray(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Period;
    dArray[1] = pMsg->Pulse_Width;
}

void DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadRawSignalValuesArray(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Period_raw;
    nRawValues[1] = pMsg->Pulse_Width_raw;
}

int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Transmit(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Init(pMsg);
    }

    DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Transmit_raw(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Init(pMsg);
    }

    DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_UpdateBytesFromSignals(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg)
{
    double dArray[2];

    DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_FIRE2_Report_Message_PWM_IN_1__neoVI_UpdateBytesFromRawSignals(DB_FIRE2_Report_Message_PWM_IN_1__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_FIRE2_Report_Message_PWM_IN_1__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_1__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index = 46;

void DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Init(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Period = dValues[0];
    pMsg->Pulse_Width = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Period_raw = (DWORD)nRawValues[0];
    pMsg->Pulse_Width_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadSignalValuesArray(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Period;
    dArray[1] = pMsg->Pulse_Width;
}

void DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadRawSignalValuesArray(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Period_raw;
    nRawValues[1] = pMsg->Pulse_Width_raw;
}

int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Transmit(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Init(pMsg);
    }

    DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Transmit_raw(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Init(pMsg);
    }

    DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_UpdateBytesFromSignals(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg)
{
    double dArray[2];

    DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_FIRE2_Report_Message_PWM_IN_2__neoVI_UpdateBytesFromRawSignals(DB_FIRE2_Report_Message_PWM_IN_2__neoVI * pMsg)
{
    uint64 nRawValues[2];

    DB_FIRE2_Report_Message_PWM_IN_2__neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_FIRE2_Report_Message_PWM_IN_2__neoVI_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Hardware_Latency_Test_neoVI_Index = 47;

void DB_Hardware_Latency_Test_neoVI_Init(DB_Hardware_Latency_Test_neoVI * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Hardware_Latency_Test_neoVI_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Latency__us_ = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->Latency__us__raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Hardware_Latency_Test_neoVI_LoadSignalValuesArray(DB_Hardware_Latency_Test_neoVI * pMsg, double *dArray)
{
    dArray[0] = pMsg->Latency__us_;
}

void DB_Hardware_Latency_Test_neoVI_LoadRawSignalValuesArray(DB_Hardware_Latency_Test_neoVI * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Latency__us__raw;
}

int DB_Hardware_Latency_Test_neoVI_Transmit(DB_Hardware_Latency_Test_neoVI * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Hardware_Latency_Test_neoVI_Init(pMsg);
    }

    DB_Hardware_Latency_Test_neoVI_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_Hardware_Latency_Test_neoVI_Transmit_raw(DB_Hardware_Latency_Test_neoVI * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Hardware_Latency_Test_neoVI_Init(pMsg);
    }

    DB_Hardware_Latency_Test_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_Hardware_Latency_Test_neoVI_UpdateBytesFromSignals(DB_Hardware_Latency_Test_neoVI * pMsg)
{
    double dArray[1];

    DB_Hardware_Latency_Test_neoVI_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Hardware_Latency_Test_neoVI_UpdateBytesFromRawSignals(DB_Hardware_Latency_Test_neoVI * pMsg)
{
    uint64 nRawValues[1];

    DB_Hardware_Latency_Test_neoVI_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Hardware_Latency_Test_neoVI_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_SW1_HS_CAN_Index = 48;

void DB_SW1_HS_CAN_Init(DB_SW1_HS_CAN * pMsg)
{
    double dValues[18] = {0.0};
    uint64 nRawValues[18] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_SW1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 18, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->WiperSwtOFF = dValues[0];
    pMsg->WiperWashSwt = dValues[1];
    pMsg->WiperModeAutoSwt = dValues[2];
    pMsg->WiperModeMistSwt = dValues[3];
    pMsg->AxleDifferentialLockSwt = dValues[4];
    pMsg->WheelDifferLockSwt = dValues[5];
    pMsg->RSerSwtSig = dValues[6];
    pMsg->RFogLgtSwtSig = dValues[7];
    pMsg->FFogLgtSwtSig = dValues[8];
    pMsg->LightSwt_II = dValues[9];
    pMsg->LightSwt_I = dValues[10];
    pMsg->RhTurnSwtSig = dValues[11];
    pMsg->LhTurnSwtSig = dValues[12];
    pMsg->HBSwtSig = dValues[13];
    pMsg->Horn_Reserved = dValues[14];
    pMsg->WiperModeHighSwt = dValues[15];
    pMsg->WiperModeLowSwt = dValues[16];
    pMsg->LightSW_Auto = dValues[17];
    CM_MessageRawInit(g_uiHandle, 0, DB_SW1_HS_CAN_Index, nRawValues, 18, &iActualSignalMaxCount);
    pMsg->WiperSwtOFF_raw = (BYTE)nRawValues[0];
    pMsg->WiperWashSwt_raw = (BYTE)nRawValues[1];
    pMsg->WiperModeAutoSwt_raw = (BYTE)nRawValues[2];
    pMsg->WiperModeMistSwt_raw = (BYTE)nRawValues[3];
    pMsg->AxleDifferentialLockSwt_raw = (BYTE)nRawValues[4];
    pMsg->WheelDifferLockSwt_raw = (BYTE)nRawValues[5];
    pMsg->RSerSwtSig_raw = (BYTE)nRawValues[6];
    pMsg->RFogLgtSwtSig_raw = (BYTE)nRawValues[7];
    pMsg->FFogLgtSwtSig_raw = (BYTE)nRawValues[8];
    pMsg->LightSwt_II_raw = (BYTE)nRawValues[9];
    pMsg->LightSwt_I_raw = (BYTE)nRawValues[10];
    pMsg->RhTurnSwtSig_raw = (BYTE)nRawValues[11];
    pMsg->LhTurnSwtSig_raw = (BYTE)nRawValues[12];
    pMsg->HBSwtSig_raw = (BYTE)nRawValues[13];
    pMsg->Horn_Reserved_raw = (BYTE)nRawValues[14];
    pMsg->WiperModeHighSwt_raw = (BYTE)nRawValues[15];
    pMsg->WiperModeLowSwt_raw = (BYTE)nRawValues[16];
    pMsg->LightSW_Auto_raw = (BYTE)nRawValues[17];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_SW1_HS_CAN_LoadSignalValuesArray(DB_SW1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->WiperSwtOFF;
    dArray[1] = pMsg->WiperWashSwt;
    dArray[2] = pMsg->WiperModeAutoSwt;
    dArray[3] = pMsg->WiperModeMistSwt;
    dArray[4] = pMsg->AxleDifferentialLockSwt;
    dArray[5] = pMsg->WheelDifferLockSwt;
    dArray[6] = pMsg->RSerSwtSig;
    dArray[7] = pMsg->RFogLgtSwtSig;
    dArray[8] = pMsg->FFogLgtSwtSig;
    dArray[9] = pMsg->LightSwt_II;
    dArray[10] = pMsg->LightSwt_I;
    dArray[11] = pMsg->RhTurnSwtSig;
    dArray[12] = pMsg->LhTurnSwtSig;
    dArray[13] = pMsg->HBSwtSig;
    dArray[14] = pMsg->Horn_Reserved;
    dArray[15] = pMsg->WiperModeHighSwt;
    dArray[16] = pMsg->WiperModeLowSwt;
    dArray[17] = pMsg->LightSW_Auto;
}

void DB_SW1_HS_CAN_LoadRawSignalValuesArray(DB_SW1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->WiperSwtOFF_raw;
    nRawValues[1] = pMsg->WiperWashSwt_raw;
    nRawValues[2] = pMsg->WiperModeAutoSwt_raw;
    nRawValues[3] = pMsg->WiperModeMistSwt_raw;
    nRawValues[4] = pMsg->AxleDifferentialLockSwt_raw;
    nRawValues[5] = pMsg->WheelDifferLockSwt_raw;
    nRawValues[6] = pMsg->RSerSwtSig_raw;
    nRawValues[7] = pMsg->RFogLgtSwtSig_raw;
    nRawValues[8] = pMsg->FFogLgtSwtSig_raw;
    nRawValues[9] = pMsg->LightSwt_II_raw;
    nRawValues[10] = pMsg->LightSwt_I_raw;
    nRawValues[11] = pMsg->RhTurnSwtSig_raw;
    nRawValues[12] = pMsg->LhTurnSwtSig_raw;
    nRawValues[13] = pMsg->HBSwtSig_raw;
    nRawValues[14] = pMsg->Horn_Reserved_raw;
    nRawValues[15] = pMsg->WiperModeHighSwt_raw;
    nRawValues[16] = pMsg->WiperModeLowSwt_raw;
    nRawValues[17] = pMsg->LightSW_Auto_raw;
}

int DB_SW1_HS_CAN_Transmit(DB_SW1_HS_CAN * pMsg)
{
    double dArray[18];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_SW1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_SW1_HS_CAN_Init(pMsg);
    }

    DB_SW1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_SW1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 18);
}

int DB_SW1_HS_CAN_Transmit_raw(DB_SW1_HS_CAN * pMsg)
{
    uint64 nRawValues[18];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_SW1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_SW1_HS_CAN_Init(pMsg);
    }

    DB_SW1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_SW1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 18);
}

int DB_SW1_HS_CAN_UpdateBytesFromSignals(DB_SW1_HS_CAN * pMsg)
{
    double dArray[18];

    DB_SW1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_SW1_HS_CAN_Index, dArray, 18, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_SW1_HS_CAN_UpdateBytesFromRawSignals(DB_SW1_HS_CAN * pMsg)
{
    uint64 nRawValues[18];

    DB_SW1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_SW1_HS_CAN_Index, nRawValues, 18, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_SW2_HS_CAN_Index = 49;

void DB_SW2_HS_CAN_Init(DB_SW2_HS_CAN * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_SW2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Ignition_ACC = dValues[0];
    pMsg->Ignition_IN = dValues[1];
    pMsg->Ignition_START = dValues[2];
    pMsg->Ignition_ON = dValues[3];
    pMsg->Ignition_OFF = dValues[4];
    pMsg->FrontWorkLightSW = dValues[5];
    pMsg->ReservedSW4 = dValues[6];
    pMsg->WaistLightSW = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_SW2_HS_CAN_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->Ignition_ACC_raw = (BYTE)nRawValues[0];
    pMsg->Ignition_IN_raw = (BYTE)nRawValues[1];
    pMsg->Ignition_START_raw = (BYTE)nRawValues[2];
    pMsg->Ignition_ON_raw = (BYTE)nRawValues[3];
    pMsg->Ignition_OFF_raw = (BYTE)nRawValues[4];
    pMsg->FrontWorkLightSW_raw = (BYTE)nRawValues[5];
    pMsg->ReservedSW4_raw = (BYTE)nRawValues[6];
    pMsg->WaistLightSW_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_SW2_HS_CAN_LoadSignalValuesArray(DB_SW2_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->Ignition_ACC;
    dArray[1] = pMsg->Ignition_IN;
    dArray[2] = pMsg->Ignition_START;
    dArray[3] = pMsg->Ignition_ON;
    dArray[4] = pMsg->Ignition_OFF;
    dArray[5] = pMsg->FrontWorkLightSW;
    dArray[6] = pMsg->ReservedSW4;
    dArray[7] = pMsg->WaistLightSW;
}

void DB_SW2_HS_CAN_LoadRawSignalValuesArray(DB_SW2_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Ignition_ACC_raw;
    nRawValues[1] = pMsg->Ignition_IN_raw;
    nRawValues[2] = pMsg->Ignition_START_raw;
    nRawValues[3] = pMsg->Ignition_ON_raw;
    nRawValues[4] = pMsg->Ignition_OFF_raw;
    nRawValues[5] = pMsg->FrontWorkLightSW_raw;
    nRawValues[6] = pMsg->ReservedSW4_raw;
    nRawValues[7] = pMsg->WaistLightSW_raw;
}

int DB_SW2_HS_CAN_Transmit(DB_SW2_HS_CAN * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_SW2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_SW2_HS_CAN_Init(pMsg);
    }

    DB_SW2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_SW2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_SW2_HS_CAN_Transmit_raw(DB_SW2_HS_CAN * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_SW2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_SW2_HS_CAN_Init(pMsg);
    }

    DB_SW2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_SW2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_SW2_HS_CAN_UpdateBytesFromSignals(DB_SW2_HS_CAN * pMsg)
{
    double dArray[8];

    DB_SW2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_SW2_HS_CAN_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_SW2_HS_CAN_UpdateBytesFromRawSignals(DB_SW2_HS_CAN * pMsg)
{
    uint64 nRawValues[8];

    DB_SW2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_SW2_HS_CAN_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_VehCfg_HS_CAN_Index = 50;

void DB_VehCfg_HS_CAN_Init(DB_VehCfg_HS_CAN * pMsg)
{
    double dValues[16] = {0.0};
    uint64 nRawValues[16] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VehCfg_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 16, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->BatteryCapacity = dValues[0];
    pMsg->VIN_Number3 = dValues[1];
    pMsg->VIN_Number2 = dValues[2];
    pMsg->VIN_Number1 = dValues[3];
    pMsg->EMS_TyperCfig = dValues[4];
    pMsg->TorqueCtrFunCfig = dValues[5];
    pMsg->OQS_A2_InstallCfig = dValues[6];
    pMsg->OQS_A1_InstallCfig = dValues[7];
    pMsg->OQS_T_InstallCfig = dValues[8];
    pMsg->OQS_E_InstallCfig = dValues[9];
    pMsg->EngineOilMassSense_InstallCfig = dValues[10];
    pMsg->Anti_ThiefFunCfig = dValues[11];
    pMsg->FuelMassDetection_InstallCfig = dValues[12];
    pMsg->RLS_InstallCfig = dValues[13];
    pMsg->BCM_InstallCfig = dValues[14];
    pMsg->ElectromagneticPowerSwtFunCfig = dValues[15];
    CM_MessageRawInit(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, nRawValues, 16, &iActualSignalMaxCount);
    pMsg->BatteryCapacity_raw = (BYTE)nRawValues[0];
    pMsg->VIN_Number3_raw = (BYTE)nRawValues[1];
    pMsg->VIN_Number2_raw = (uint64)nRawValues[2];
    pMsg->VIN_Number1_raw = (uint64)nRawValues[3];
    pMsg->EMS_TyperCfig_raw = (BYTE)nRawValues[4];
    pMsg->TorqueCtrFunCfig_raw = (BYTE)nRawValues[5];
    pMsg->OQS_A2_InstallCfig_raw = (BYTE)nRawValues[6];
    pMsg->OQS_A1_InstallCfig_raw = (BYTE)nRawValues[7];
    pMsg->OQS_T_InstallCfig_raw = (BYTE)nRawValues[8];
    pMsg->OQS_E_InstallCfig_raw = (BYTE)nRawValues[9];
    pMsg->EngineOilMassSense_InstallCfig_raw = (BYTE)nRawValues[10];
    pMsg->Anti_ThiefFunCfig_raw = (BYTE)nRawValues[11];
    pMsg->FuelMassDetection_InstallCfig_raw = (BYTE)nRawValues[12];
    pMsg->RLS_InstallCfig_raw = (BYTE)nRawValues[13];
    pMsg->BCM_InstallCfig_raw = (BYTE)nRawValues[14];
    pMsg->ElectromagneticPowerSwtFunCfig_raw = (BYTE)nRawValues[15];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_VehCfg_HS_CAN_LoadSignalValuesArray(DB_VehCfg_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->BatteryCapacity;
    dArray[1] = pMsg->VIN_Number3;
    dArray[2] = pMsg->VIN_Number2;
    dArray[3] = pMsg->VIN_Number1;
    dArray[4] = pMsg->EMS_TyperCfig;
    dArray[5] = pMsg->TorqueCtrFunCfig;
    dArray[6] = pMsg->OQS_A2_InstallCfig;
    dArray[7] = pMsg->OQS_A1_InstallCfig;
    dArray[8] = pMsg->OQS_T_InstallCfig;
    dArray[9] = pMsg->OQS_E_InstallCfig;
    dArray[10] = pMsg->EngineOilMassSense_InstallCfig;
    dArray[11] = pMsg->Anti_ThiefFunCfig;
    dArray[12] = pMsg->FuelMassDetection_InstallCfig;
    dArray[13] = pMsg->RLS_InstallCfig;
    dArray[14] = pMsg->BCM_InstallCfig;
    dArray[15] = pMsg->ElectromagneticPowerSwtFunCfig;
}

void DB_VehCfg_HS_CAN_LoadRawSignalValuesArray(DB_VehCfg_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->BatteryCapacity_raw;
    nRawValues[1] = pMsg->VIN_Number3_raw;
    nRawValues[2] = pMsg->VIN_Number2_raw;
    nRawValues[3] = pMsg->VIN_Number1_raw;
    nRawValues[4] = pMsg->EMS_TyperCfig_raw;
    nRawValues[5] = pMsg->TorqueCtrFunCfig_raw;
    nRawValues[6] = pMsg->OQS_A2_InstallCfig_raw;
    nRawValues[7] = pMsg->OQS_A1_InstallCfig_raw;
    nRawValues[8] = pMsg->OQS_T_InstallCfig_raw;
    nRawValues[9] = pMsg->OQS_E_InstallCfig_raw;
    nRawValues[10] = pMsg->EngineOilMassSense_InstallCfig_raw;
    nRawValues[11] = pMsg->Anti_ThiefFunCfig_raw;
    nRawValues[12] = pMsg->FuelMassDetection_InstallCfig_raw;
    nRawValues[13] = pMsg->RLS_InstallCfig_raw;
    nRawValues[14] = pMsg->BCM_InstallCfig_raw;
    nRawValues[15] = pMsg->ElectromagneticPowerSwtFunCfig_raw;
}

int DB_VehCfg_HS_CAN_Transmit(DB_VehCfg_HS_CAN * pMsg)
{
    double dArray[16];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VehCfg_HS_CAN_Init(pMsg);
    }

    DB_VehCfg_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 16);
}

int DB_VehCfg_HS_CAN_Transmit_raw(DB_VehCfg_HS_CAN * pMsg)
{
    uint64 nRawValues[16];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VehCfg_HS_CAN_Init(pMsg);
    }

    DB_VehCfg_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 16);
}

int DB_VehCfg_HS_CAN_UpdateBytesFromSignals(DB_VehCfg_HS_CAN * pMsg)
{
    double dArray[16];

    DB_VehCfg_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, dArray, 16, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_VehCfg_HS_CAN_UpdateBytesFromRawSignals(DB_VehCfg_HS_CAN * pMsg)
{
    uint64 nRawValues[16];

    DB_VehCfg_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_VehCfg_HS_CAN_Index, nRawValues, 16, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_RouteSG_ChasO_HS_CAN_Index = 51;

void DB_RouteSG_ChasO_HS_CAN_Init(DB_RouteSG_ChasO_HS_CAN * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_RouteSG_ChasO_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->OilTemperature_A2 = dValues[0];
    pMsg->OilTemperature_A1 = dValues[1];
    pMsg->OilTemperature_T = dValues[2];
    pMsg->OilTemperature_E = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_RouteSG_ChasO_HS_CAN_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->OilTemperature_A2_raw = (WORD)nRawValues[0];
    pMsg->OilTemperature_A1_raw = (WORD)nRawValues[1];
    pMsg->OilTemperature_T_raw = (WORD)nRawValues[2];
    pMsg->OilTemperature_E_raw = (WORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_RouteSG_ChasO_HS_CAN_LoadSignalValuesArray(DB_RouteSG_ChasO_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->OilTemperature_A2;
    dArray[1] = pMsg->OilTemperature_A1;
    dArray[2] = pMsg->OilTemperature_T;
    dArray[3] = pMsg->OilTemperature_E;
}

void DB_RouteSG_ChasO_HS_CAN_LoadRawSignalValuesArray(DB_RouteSG_ChasO_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->OilTemperature_A2_raw;
    nRawValues[1] = pMsg->OilTemperature_A1_raw;
    nRawValues[2] = pMsg->OilTemperature_T_raw;
    nRawValues[3] = pMsg->OilTemperature_E_raw;
}

int DB_RouteSG_ChasO_HS_CAN_Transmit(DB_RouteSG_ChasO_HS_CAN * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_RouteSG_ChasO_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_RouteSG_ChasO_HS_CAN_Init(pMsg);
    }

    DB_RouteSG_ChasO_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_RouteSG_ChasO_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_RouteSG_ChasO_HS_CAN_Transmit_raw(DB_RouteSG_ChasO_HS_CAN * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_RouteSG_ChasO_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_RouteSG_ChasO_HS_CAN_Init(pMsg);
    }

    DB_RouteSG_ChasO_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_RouteSG_ChasO_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_RouteSG_ChasO_HS_CAN_UpdateBytesFromSignals(DB_RouteSG_ChasO_HS_CAN * pMsg)
{
    double dArray[4];

    DB_RouteSG_ChasO_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_RouteSG_ChasO_HS_CAN_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_RouteSG_ChasO_HS_CAN_UpdateBytesFromRawSignals(DB_RouteSG_ChasO_HS_CAN * pMsg)
{
    uint64 nRawValues[4];

    DB_RouteSG_ChasO_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_RouteSG_ChasO_HS_CAN_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_GW_HS_CAN_Index = 52;

void DB_NM_GW_HS_CAN_Init(DB_NM_GW_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_GW_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->GW_NM_Sleep_ACK = dValues[0];
    pMsg->GW_NM_Sleep_Ind = dValues[1];
    pMsg->GW_NM_Limphome = dValues[2];
    pMsg->GW_NM_Ring = dValues[3];
    pMsg->GW_NM_Alive = dValues[4];
    pMsg->GW_NM_DA = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->GW_NM_Sleep_ACK_raw = (BYTE)nRawValues[0];
    pMsg->GW_NM_Sleep_Ind_raw = (BYTE)nRawValues[1];
    pMsg->GW_NM_Limphome_raw = (BYTE)nRawValues[2];
    pMsg->GW_NM_Ring_raw = (BYTE)nRawValues[3];
    pMsg->GW_NM_Alive_raw = (BYTE)nRawValues[4];
    pMsg->GW_NM_DA_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_GW_HS_CAN_LoadSignalValuesArray(DB_NM_GW_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->GW_NM_Sleep_ACK;
    dArray[1] = pMsg->GW_NM_Sleep_Ind;
    dArray[2] = pMsg->GW_NM_Limphome;
    dArray[3] = pMsg->GW_NM_Ring;
    dArray[4] = pMsg->GW_NM_Alive;
    dArray[5] = pMsg->GW_NM_DA;
}

void DB_NM_GW_HS_CAN_LoadRawSignalValuesArray(DB_NM_GW_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->GW_NM_Sleep_ACK_raw;
    nRawValues[1] = pMsg->GW_NM_Sleep_Ind_raw;
    nRawValues[2] = pMsg->GW_NM_Limphome_raw;
    nRawValues[3] = pMsg->GW_NM_Ring_raw;
    nRawValues[4] = pMsg->GW_NM_Alive_raw;
    nRawValues[5] = pMsg->GW_NM_DA_raw;
}

int DB_NM_GW_HS_CAN_Transmit(DB_NM_GW_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_GW_HS_CAN_Init(pMsg);
    }

    DB_NM_GW_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_NM_GW_HS_CAN_Transmit_raw(DB_NM_GW_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_GW_HS_CAN_Init(pMsg);
    }

    DB_NM_GW_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_NM_GW_HS_CAN_UpdateBytesFromSignals(DB_NM_GW_HS_CAN * pMsg)
{
    double dArray[6];

    DB_NM_GW_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_GW_HS_CAN_UpdateBytesFromRawSignals(DB_NM_GW_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_NM_GW_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_GW_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_MMIctrCab_HS_CAN_Index = 53;

void DB_MMIctrCab_HS_CAN_Init(DB_MMIctrCab_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_MMIctrCab_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->MMIctrFLgCls = dValues[0];
    pMsg->RoofWorkCmd = dValues[1];
    pMsg->RoofPositionCtr = dValues[2];
    pMsg->MMIctrLBmCls = dValues[3];
    pMsg->MMIctrLBmOpn = dValues[4];
    pMsg->MMIctrFLgOpn = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->MMIctrFLgCls_raw = (BYTE)nRawValues[0];
    pMsg->RoofWorkCmd_raw = (BYTE)nRawValues[1];
    pMsg->RoofPositionCtr_raw = (BYTE)nRawValues[2];
    pMsg->MMIctrLBmCls_raw = (BYTE)nRawValues[3];
    pMsg->MMIctrLBmOpn_raw = (BYTE)nRawValues[4];
    pMsg->MMIctrFLgOpn_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_MMIctrCab_HS_CAN_LoadSignalValuesArray(DB_MMIctrCab_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->MMIctrFLgCls;
    dArray[1] = pMsg->RoofWorkCmd;
    dArray[2] = pMsg->RoofPositionCtr;
    dArray[3] = pMsg->MMIctrLBmCls;
    dArray[4] = pMsg->MMIctrLBmOpn;
    dArray[5] = pMsg->MMIctrFLgOpn;
}

void DB_MMIctrCab_HS_CAN_LoadRawSignalValuesArray(DB_MMIctrCab_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->MMIctrFLgCls_raw;
    nRawValues[1] = pMsg->RoofWorkCmd_raw;
    nRawValues[2] = pMsg->RoofPositionCtr_raw;
    nRawValues[3] = pMsg->MMIctrLBmCls_raw;
    nRawValues[4] = pMsg->MMIctrLBmOpn_raw;
    nRawValues[5] = pMsg->MMIctrFLgOpn_raw;
}

int DB_MMIctrCab_HS_CAN_Transmit(DB_MMIctrCab_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMIctrCab_HS_CAN_Init(pMsg);
    }

    DB_MMIctrCab_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_MMIctrCab_HS_CAN_Transmit_raw(DB_MMIctrCab_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMIctrCab_HS_CAN_Init(pMsg);
    }

    DB_MMIctrCab_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_MMIctrCab_HS_CAN_UpdateBytesFromSignals(DB_MMIctrCab_HS_CAN * pMsg)
{
    double dArray[6];

    DB_MMIctrCab_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_MMIctrCab_HS_CAN_UpdateBytesFromRawSignals(DB_MMIctrCab_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_MMIctrCab_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_TCO1_HS_CAN_Index = 54;

void DB_TCO1_HS_CAN_Init(DB_TCO1_HS_CAN * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_TCO1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TachographVehiclespeed = dValues[0];
    pMsg->Tachographoutputshaftspeed = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_TCO1_HS_CAN_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->TachographVehiclespeed_raw = (WORD)nRawValues[0];
    pMsg->Tachographoutputshaftspeed_raw = (WORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_TCO1_HS_CAN_LoadSignalValuesArray(DB_TCO1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TachographVehiclespeed;
    dArray[1] = pMsg->Tachographoutputshaftspeed;
}

void DB_TCO1_HS_CAN_LoadRawSignalValuesArray(DB_TCO1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TachographVehiclespeed_raw;
    nRawValues[1] = pMsg->Tachographoutputshaftspeed_raw;
}

int DB_TCO1_HS_CAN_Transmit(DB_TCO1_HS_CAN * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_TCO1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_TCO1_HS_CAN_Init(pMsg);
    }

    DB_TCO1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_TCO1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_TCO1_HS_CAN_Transmit_raw(DB_TCO1_HS_CAN * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_TCO1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_TCO1_HS_CAN_Init(pMsg);
    }

    DB_TCO1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_TCO1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_TCO1_HS_CAN_UpdateBytesFromSignals(DB_TCO1_HS_CAN * pMsg)
{
    double dArray[2];

    DB_TCO1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_TCO1_HS_CAN_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_TCO1_HS_CAN_UpdateBytesFromRawSignals(DB_TCO1_HS_CAN * pMsg)
{
    uint64 nRawValues[2];

    DB_TCO1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_TCO1_HS_CAN_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_VehicleCtr_HS_CAN_Index = 55;

void DB_VehicleCtr_HS_CAN_Init(DB_VehicleCtr_HS_CAN * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VehicleCtr_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TXJ_CtrHBeamSig = dValues[0];
    pMsg->TXJ_CtrLowBeamSig = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->TXJ_CtrHBeamSig_raw = (BYTE)nRawValues[0];
    pMsg->TXJ_CtrLowBeamSig_raw = (BYTE)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_VehicleCtr_HS_CAN_LoadSignalValuesArray(DB_VehicleCtr_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TXJ_CtrHBeamSig;
    dArray[1] = pMsg->TXJ_CtrLowBeamSig;
}

void DB_VehicleCtr_HS_CAN_LoadRawSignalValuesArray(DB_VehicleCtr_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TXJ_CtrHBeamSig_raw;
    nRawValues[1] = pMsg->TXJ_CtrLowBeamSig_raw;
}

int DB_VehicleCtr_HS_CAN_Transmit(DB_VehicleCtr_HS_CAN * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VehicleCtr_HS_CAN_Init(pMsg);
    }

    DB_VehicleCtr_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_VehicleCtr_HS_CAN_Transmit_raw(DB_VehicleCtr_HS_CAN * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VehicleCtr_HS_CAN_Init(pMsg);
    }

    DB_VehicleCtr_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_VehicleCtr_HS_CAN_UpdateBytesFromSignals(DB_VehicleCtr_HS_CAN * pMsg)
{
    double dArray[2];

    DB_VehicleCtr_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_VehicleCtr_HS_CAN_UpdateBytesFromRawSignals(DB_VehicleCtr_HS_CAN * pMsg)
{
    uint64 nRawValues[2];

    DB_VehicleCtr_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_BCM1_HS_CAN_Index = 56;

void DB_BCM1_HS_CAN_Init(DB_BCM1_HS_CAN * pMsg)
{
    double dValues[26] = {0.0};
    uint64 nRawValues[26] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_BCM1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 26, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->CheckAllLightsSignalState = dValues[0];
    pMsg->WheelAlexDifferLockOperateError = dValues[1];
    pMsg->TrailerState_TrailerState = dValues[2];
    pMsg->WiperWashSt = dValues[3];
    pMsg->R_ReLSts = dValues[4];
    pMsg->L_ReLSts = dValues[5];
    pMsg->AtLgtSts = dValues[6];
    pMsg->TopLgtSts = dValues[7];
    pMsg->PosLgtOnWarr = dValues[8];
    pMsg->WiperModeSt = dValues[9];
    pMsg->FuelStolenAlmSig = dValues[10];
    pMsg->WheelDifferLockIndicatorLgt = dValues[11];
    pMsg->AxleDifferentialLockIndicatorLgt = dValues[12];
    pMsg->DayLgtSt = dValues[13];
    pMsg->HeadLgtWashStInd = dValues[14];
    pMsg->FuelMassSignal = dValues[15];
    pMsg->BackCabWorkingLightState = dValues[16];
    pMsg->RevLgtSt = dValues[17];
    pMsg->PosLgtStInd = dValues[18];
    pMsg->RFogLgtSt = dValues[19];
    pMsg->FrontFogLightSts = dValues[20];
    pMsg->BrkLgtSt = dValues[21];
    pMsg->R_TurnLgtSt = dValues[22];
    pMsg->L_TurnLgtSt = dValues[23];
    pMsg->LBeamSt = dValues[24];
    pMsg->HBeamSt = dValues[25];
    CM_MessageRawInit(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, nRawValues, 26, &iActualSignalMaxCount);
    pMsg->CheckAllLightsSignalState_raw = (BYTE)nRawValues[0];
    pMsg->WheelAlexDifferLockOperateError_raw = (BYTE)nRawValues[1];
    pMsg->TrailerState_TrailerState_raw = (BYTE)nRawValues[2];
    pMsg->WiperWashSt_raw = (BYTE)nRawValues[3];
    pMsg->R_ReLSts_raw = (BYTE)nRawValues[4];
    pMsg->L_ReLSts_raw = (BYTE)nRawValues[5];
    pMsg->AtLgtSts_raw = (BYTE)nRawValues[6];
    pMsg->TopLgtSts_raw = (BYTE)nRawValues[7];
    pMsg->PosLgtOnWarr_raw = (BYTE)nRawValues[8];
    pMsg->WiperModeSt_raw = (BYTE)nRawValues[9];
    pMsg->FuelStolenAlmSig_raw = (BYTE)nRawValues[10];
    pMsg->WheelDifferLockIndicatorLgt_raw = (BYTE)nRawValues[11];
    pMsg->AxleDifferentialLockIndicatorLgt_raw = (BYTE)nRawValues[12];
    pMsg->DayLgtSt_raw = (BYTE)nRawValues[13];
    pMsg->HeadLgtWashStInd_raw = (BYTE)nRawValues[14];
    pMsg->FuelMassSignal_raw = (BYTE)nRawValues[15];
    pMsg->BackCabWorkingLightState_raw = (BYTE)nRawValues[16];
    pMsg->RevLgtSt_raw = (BYTE)nRawValues[17];
    pMsg->PosLgtStInd_raw = (BYTE)nRawValues[18];
    pMsg->RFogLgtSt_raw = (BYTE)nRawValues[19];
    pMsg->FrontFogLightSts_raw = (BYTE)nRawValues[20];
    pMsg->BrkLgtSt_raw = (BYTE)nRawValues[21];
    pMsg->R_TurnLgtSt_raw = (BYTE)nRawValues[22];
    pMsg->L_TurnLgtSt_raw = (BYTE)nRawValues[23];
    pMsg->LBeamSt_raw = (BYTE)nRawValues[24];
    pMsg->HBeamSt_raw = (BYTE)nRawValues[25];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_BCM1_HS_CAN_LoadSignalValuesArray(DB_BCM1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->CheckAllLightsSignalState;
    dArray[1] = pMsg->WheelAlexDifferLockOperateError;
    dArray[2] = pMsg->TrailerState_TrailerState;
    dArray[3] = pMsg->WiperWashSt;
    dArray[4] = pMsg->R_ReLSts;
    dArray[5] = pMsg->L_ReLSts;
    dArray[6] = pMsg->AtLgtSts;
    dArray[7] = pMsg->TopLgtSts;
    dArray[8] = pMsg->PosLgtOnWarr;
    dArray[9] = pMsg->WiperModeSt;
    dArray[10] = pMsg->FuelStolenAlmSig;
    dArray[11] = pMsg->WheelDifferLockIndicatorLgt;
    dArray[12] = pMsg->AxleDifferentialLockIndicatorLgt;
    dArray[13] = pMsg->DayLgtSt;
    dArray[14] = pMsg->HeadLgtWashStInd;
    dArray[15] = pMsg->FuelMassSignal;
    dArray[16] = pMsg->BackCabWorkingLightState;
    dArray[17] = pMsg->RevLgtSt;
    dArray[18] = pMsg->PosLgtStInd;
    dArray[19] = pMsg->RFogLgtSt;
    dArray[20] = pMsg->FrontFogLightSts;
    dArray[21] = pMsg->BrkLgtSt;
    dArray[22] = pMsg->R_TurnLgtSt;
    dArray[23] = pMsg->L_TurnLgtSt;
    dArray[24] = pMsg->LBeamSt;
    dArray[25] = pMsg->HBeamSt;
}

void DB_BCM1_HS_CAN_LoadRawSignalValuesArray(DB_BCM1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->CheckAllLightsSignalState_raw;
    nRawValues[1] = pMsg->WheelAlexDifferLockOperateError_raw;
    nRawValues[2] = pMsg->TrailerState_TrailerState_raw;
    nRawValues[3] = pMsg->WiperWashSt_raw;
    nRawValues[4] = pMsg->R_ReLSts_raw;
    nRawValues[5] = pMsg->L_ReLSts_raw;
    nRawValues[6] = pMsg->AtLgtSts_raw;
    nRawValues[7] = pMsg->TopLgtSts_raw;
    nRawValues[8] = pMsg->PosLgtOnWarr_raw;
    nRawValues[9] = pMsg->WiperModeSt_raw;
    nRawValues[10] = pMsg->FuelStolenAlmSig_raw;
    nRawValues[11] = pMsg->WheelDifferLockIndicatorLgt_raw;
    nRawValues[12] = pMsg->AxleDifferentialLockIndicatorLgt_raw;
    nRawValues[13] = pMsg->DayLgtSt_raw;
    nRawValues[14] = pMsg->HeadLgtWashStInd_raw;
    nRawValues[15] = pMsg->FuelMassSignal_raw;
    nRawValues[16] = pMsg->BackCabWorkingLightState_raw;
    nRawValues[17] = pMsg->RevLgtSt_raw;
    nRawValues[18] = pMsg->PosLgtStInd_raw;
    nRawValues[19] = pMsg->RFogLgtSt_raw;
    nRawValues[20] = pMsg->FrontFogLightSts_raw;
    nRawValues[21] = pMsg->BrkLgtSt_raw;
    nRawValues[22] = pMsg->R_TurnLgtSt_raw;
    nRawValues[23] = pMsg->L_TurnLgtSt_raw;
    nRawValues[24] = pMsg->LBeamSt_raw;
    nRawValues[25] = pMsg->HBeamSt_raw;
}

int DB_BCM1_HS_CAN_Transmit(DB_BCM1_HS_CAN * pMsg)
{
    double dArray[26];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_BCM1_HS_CAN_Init(pMsg);
    }

    DB_BCM1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 26);
}

int DB_BCM1_HS_CAN_Transmit_raw(DB_BCM1_HS_CAN * pMsg)
{
    uint64 nRawValues[26];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_BCM1_HS_CAN_Init(pMsg);
    }

    DB_BCM1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 26);
}

int DB_BCM1_HS_CAN_UpdateBytesFromSignals(DB_BCM1_HS_CAN * pMsg)
{
    double dArray[26];

    DB_BCM1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, dArray, 26, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_BCM1_HS_CAN_UpdateBytesFromRawSignals(DB_BCM1_HS_CAN * pMsg)
{
    uint64 nRawValues[26];

    DB_BCM1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_BCM1_HS_CAN_Index, nRawValues, 26, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_BCM2_HS_CAN_Index = 57;

void DB_BCM2_HS_CAN_Init(DB_BCM2_HS_CAN * pMsg)
{
    double dValues[16] = {0.0};
    uint64 nRawValues[16] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_BCM2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 16, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->EngineOilLevel_ElecOilSense = dValues[0];
    pMsg->EngineOilTemp_ElecOilSense = dValues[1];
    pMsg->SOH = dValues[2];
    pMsg->SOC = dValues[3];
    pMsg->TransferOilQualityLevel = dValues[4];
    pMsg->EngineOilQualityLevel = dValues[5];
    pMsg->EnvirLightState = dValues[6];
    pMsg->DoorUniteState = dValues[7];
    pMsg->WaistLightState = dValues[8];
    pMsg->ForntWorkLightState = dValues[9];
    pMsg->IC_LightLevelAutoCtr = dValues[10];
    pMsg->EngineOilMass_ElecOilSense = dValues[11];
    pMsg->Alex2ndOilQualityLevel = dValues[12];
    pMsg->Alex1stOilQualityLevel = dValues[13];
    pMsg->DanodeRelayOutputState = dValues[14];
    pMsg->ElectromagneticPowerSwtState = dValues[15];
    CM_MessageRawInit(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, nRawValues, 16, &iActualSignalMaxCount);
    pMsg->EngineOilLevel_ElecOilSense_raw = (BYTE)nRawValues[0];
    pMsg->EngineOilTemp_ElecOilSense_raw = (BYTE)nRawValues[1];
    pMsg->SOH_raw = (BYTE)nRawValues[2];
    pMsg->SOC_raw = (BYTE)nRawValues[3];
    pMsg->TransferOilQualityLevel_raw = (BYTE)nRawValues[4];
    pMsg->EngineOilQualityLevel_raw = (BYTE)nRawValues[5];
    pMsg->EnvirLightState_raw = (BYTE)nRawValues[6];
    pMsg->DoorUniteState_raw = (BYTE)nRawValues[7];
    pMsg->WaistLightState_raw = (BYTE)nRawValues[8];
    pMsg->ForntWorkLightState_raw = (BYTE)nRawValues[9];
    pMsg->IC_LightLevelAutoCtr_raw = (BYTE)nRawValues[10];
    pMsg->EngineOilMass_ElecOilSense_raw = (WORD)nRawValues[11];
    pMsg->Alex2ndOilQualityLevel_raw = (BYTE)nRawValues[12];
    pMsg->Alex1stOilQualityLevel_raw = (BYTE)nRawValues[13];
    pMsg->DanodeRelayOutputState_raw = (BYTE)nRawValues[14];
    pMsg->ElectromagneticPowerSwtState_raw = (BYTE)nRawValues[15];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_BCM2_HS_CAN_LoadSignalValuesArray(DB_BCM2_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->EngineOilLevel_ElecOilSense;
    dArray[1] = pMsg->EngineOilTemp_ElecOilSense;
    dArray[2] = pMsg->SOH;
    dArray[3] = pMsg->SOC;
    dArray[4] = pMsg->TransferOilQualityLevel;
    dArray[5] = pMsg->EngineOilQualityLevel;
    dArray[6] = pMsg->EnvirLightState;
    dArray[7] = pMsg->DoorUniteState;
    dArray[8] = pMsg->WaistLightState;
    dArray[9] = pMsg->ForntWorkLightState;
    dArray[10] = pMsg->IC_LightLevelAutoCtr;
    dArray[11] = pMsg->EngineOilMass_ElecOilSense;
    dArray[12] = pMsg->Alex2ndOilQualityLevel;
    dArray[13] = pMsg->Alex1stOilQualityLevel;
    dArray[14] = pMsg->DanodeRelayOutputState;
    dArray[15] = pMsg->ElectromagneticPowerSwtState;
}

void DB_BCM2_HS_CAN_LoadRawSignalValuesArray(DB_BCM2_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->EngineOilLevel_ElecOilSense_raw;
    nRawValues[1] = pMsg->EngineOilTemp_ElecOilSense_raw;
    nRawValues[2] = pMsg->SOH_raw;
    nRawValues[3] = pMsg->SOC_raw;
    nRawValues[4] = pMsg->TransferOilQualityLevel_raw;
    nRawValues[5] = pMsg->EngineOilQualityLevel_raw;
    nRawValues[6] = pMsg->EnvirLightState_raw;
    nRawValues[7] = pMsg->DoorUniteState_raw;
    nRawValues[8] = pMsg->WaistLightState_raw;
    nRawValues[9] = pMsg->ForntWorkLightState_raw;
    nRawValues[10] = pMsg->IC_LightLevelAutoCtr_raw;
    nRawValues[11] = pMsg->EngineOilMass_ElecOilSense_raw;
    nRawValues[12] = pMsg->Alex2ndOilQualityLevel_raw;
    nRawValues[13] = pMsg->Alex1stOilQualityLevel_raw;
    nRawValues[14] = pMsg->DanodeRelayOutputState_raw;
    nRawValues[15] = pMsg->ElectromagneticPowerSwtState_raw;
}

int DB_BCM2_HS_CAN_Transmit(DB_BCM2_HS_CAN * pMsg)
{
    double dArray[16];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_BCM2_HS_CAN_Init(pMsg);
    }

    DB_BCM2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 16);
}

int DB_BCM2_HS_CAN_Transmit_raw(DB_BCM2_HS_CAN * pMsg)
{
    uint64 nRawValues[16];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_BCM2_HS_CAN_Init(pMsg);
    }

    DB_BCM2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 16);
}

int DB_BCM2_HS_CAN_UpdateBytesFromSignals(DB_BCM2_HS_CAN * pMsg)
{
    double dArray[16];

    DB_BCM2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, dArray, 16, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_BCM2_HS_CAN_UpdateBytesFromRawSignals(DB_BCM2_HS_CAN * pMsg)
{
    uint64 nRawValues[16];

    DB_BCM2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_BCM2_HS_CAN_Index, nRawValues, 16, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_BCM3_HS_CAN_Index = 58;

void DB_BCM3_HS_CAN_Init(DB_BCM3_HS_CAN * pMsg)
{
    double dValues[5] = {0.0};
    uint64 nRawValues[5] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_BCM3_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 5, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->U_BATT = dValues[0];
    pMsg->R_TurnLgtCmdToIC = dValues[1];
    pMsg->L_TurnLgtCmdToIC = dValues[2];
    pMsg->I_RANGE = dValues[3];
    pMsg->IBATT = dValues[4];
    CM_MessageRawInit(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, nRawValues, 5, &iActualSignalMaxCount);
    pMsg->U_BATT_raw = (WORD)nRawValues[0];
    pMsg->R_TurnLgtCmdToIC_raw = (BYTE)nRawValues[1];
    pMsg->L_TurnLgtCmdToIC_raw = (BYTE)nRawValues[2];
    pMsg->I_RANGE_raw = (BYTE)nRawValues[3];
    pMsg->IBATT_raw = (WORD)nRawValues[4];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_BCM3_HS_CAN_LoadSignalValuesArray(DB_BCM3_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->U_BATT;
    dArray[1] = pMsg->R_TurnLgtCmdToIC;
    dArray[2] = pMsg->L_TurnLgtCmdToIC;
    dArray[3] = pMsg->I_RANGE;
    dArray[4] = pMsg->IBATT;
}

void DB_BCM3_HS_CAN_LoadRawSignalValuesArray(DB_BCM3_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->U_BATT_raw;
    nRawValues[1] = pMsg->R_TurnLgtCmdToIC_raw;
    nRawValues[2] = pMsg->L_TurnLgtCmdToIC_raw;
    nRawValues[3] = pMsg->I_RANGE_raw;
    nRawValues[4] = pMsg->IBATT_raw;
}

int DB_BCM3_HS_CAN_Transmit(DB_BCM3_HS_CAN * pMsg)
{
    double dArray[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_BCM3_HS_CAN_Init(pMsg);
    }

    DB_BCM3_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 5);
}

int DB_BCM3_HS_CAN_Transmit_raw(DB_BCM3_HS_CAN * pMsg)
{
    uint64 nRawValues[5];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_BCM3_HS_CAN_Init(pMsg);
    }

    DB_BCM3_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 5);
}

int DB_BCM3_HS_CAN_UpdateBytesFromSignals(DB_BCM3_HS_CAN * pMsg)
{
    double dArray[5];

    DB_BCM3_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, dArray, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_BCM3_HS_CAN_UpdateBytesFromRawSignals(DB_BCM3_HS_CAN * pMsg)
{
    uint64 nRawValues[5];

    DB_BCM3_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_BCM3_HS_CAN_Index, nRawValues, 5, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_BCMlinCmd_HS_CAN_Index = 59;

void DB_BCMlinCmd_HS_CAN_Init(DB_BCMlinCmd_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_BCMlinCmd_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->RainVal = dValues[0];
    pMsg->MMI_ON_OFF_Cmd = dValues[1];
    pMsg->ScreenWiperSpeed = dValues[2];
    pMsg->RoofWorkCmd = dValues[3];
    pMsg->VolDec = dValues[4];
    pMsg->VolAd = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->RainVal_raw = (WORD)nRawValues[0];
    pMsg->MMI_ON_OFF_Cmd_raw = (BYTE)nRawValues[1];
    pMsg->ScreenWiperSpeed_raw = (WORD)nRawValues[2];
    pMsg->RoofWorkCmd_raw = (BYTE)nRawValues[3];
    pMsg->VolDec_raw = (BYTE)nRawValues[4];
    pMsg->VolAd_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_BCMlinCmd_HS_CAN_LoadSignalValuesArray(DB_BCMlinCmd_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->RainVal;
    dArray[1] = pMsg->MMI_ON_OFF_Cmd;
    dArray[2] = pMsg->ScreenWiperSpeed;
    dArray[3] = pMsg->RoofWorkCmd;
    dArray[4] = pMsg->VolDec;
    dArray[5] = pMsg->VolAd;
}

void DB_BCMlinCmd_HS_CAN_LoadRawSignalValuesArray(DB_BCMlinCmd_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->RainVal_raw;
    nRawValues[1] = pMsg->MMI_ON_OFF_Cmd_raw;
    nRawValues[2] = pMsg->ScreenWiperSpeed_raw;
    nRawValues[3] = pMsg->RoofWorkCmd_raw;
    nRawValues[4] = pMsg->VolDec_raw;
    nRawValues[5] = pMsg->VolAd_raw;
}

int DB_BCMlinCmd_HS_CAN_Transmit(DB_BCMlinCmd_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_BCMlinCmd_HS_CAN_Init(pMsg);
    }

    DB_BCMlinCmd_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_BCMlinCmd_HS_CAN_Transmit_raw(DB_BCMlinCmd_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_BCMlinCmd_HS_CAN_Init(pMsg);
    }

    DB_BCMlinCmd_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_BCMlinCmd_HS_CAN_UpdateBytesFromSignals(DB_BCMlinCmd_HS_CAN * pMsg)
{
    double dArray[6];

    DB_BCMlinCmd_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_BCMlinCmd_HS_CAN_UpdateBytesFromRawSignals(DB_BCMlinCmd_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_BCMlinCmd_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_BCMlinCmd_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_OEL_HS_CAN_Index = 60;

void DB_OEL_HS_CAN_Init(DB_OEL_HS_CAN * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_OEL_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TurnSignalSwitch = dValues[0];
    pMsg->HazardLightSwitch = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_OEL_HS_CAN_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->TurnSignalSwitch_raw = (BYTE)nRawValues[0];
    pMsg->HazardLightSwitch_raw = (BYTE)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_OEL_HS_CAN_LoadSignalValuesArray(DB_OEL_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TurnSignalSwitch;
    dArray[1] = pMsg->HazardLightSwitch;
}

void DB_OEL_HS_CAN_LoadRawSignalValuesArray(DB_OEL_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TurnSignalSwitch_raw;
    nRawValues[1] = pMsg->HazardLightSwitch_raw;
}

int DB_OEL_HS_CAN_Transmit(DB_OEL_HS_CAN * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OEL_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OEL_HS_CAN_Init(pMsg);
    }

    DB_OEL_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_OEL_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_OEL_HS_CAN_Transmit_raw(DB_OEL_HS_CAN * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OEL_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OEL_HS_CAN_Init(pMsg);
    }

    DB_OEL_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_OEL_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_OEL_HS_CAN_UpdateBytesFromSignals(DB_OEL_HS_CAN * pMsg)
{
    double dArray[2];

    DB_OEL_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_OEL_HS_CAN_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_OEL_HS_CAN_UpdateBytesFromRawSignals(DB_OEL_HS_CAN * pMsg)
{
    uint64 nRawValues[2];

    DB_OEL_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_OEL_HS_CAN_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_DM1_BCM_HS_CAN_Index = 61;

void DB_DM1_BCM_HS_CAN_Init(DB_DM1_BCM_HS_CAN * pMsg)
{
    double dValues[9] = {0.0};
    uint64 nRawValues[9] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_DM1_BCM_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 9, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->SPN_Mode = dValues[0];
    pMsg->OccuranceCount = dValues[1];
    pMsg->SPN_HighBit = dValues[2];
    pMsg->FMI = dValues[3];
    pMsg->SPN_Num = dValues[4];
    pMsg->MalfunctionIndicatorLamp = dValues[5];
    pMsg->RedStopLamp = dValues[6];
    pMsg->ProtectLamp = dValues[7];
    pMsg->AmberWarningLamp = dValues[8];
    CM_MessageRawInit(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, nRawValues, 9, &iActualSignalMaxCount);
    pMsg->SPN_Mode_raw = (BYTE)nRawValues[0];
    pMsg->OccuranceCount_raw = (BYTE)nRawValues[1];
    pMsg->SPN_HighBit_raw = (BYTE)nRawValues[2];
    pMsg->FMI_raw = (BYTE)nRawValues[3];
    pMsg->SPN_Num_raw = (WORD)nRawValues[4];
    pMsg->MalfunctionIndicatorLamp_raw = (BYTE)nRawValues[5];
    pMsg->RedStopLamp_raw = (BYTE)nRawValues[6];
    pMsg->ProtectLamp_raw = (BYTE)nRawValues[7];
    pMsg->AmberWarningLamp_raw = (BYTE)nRawValues[8];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_DM1_BCM_HS_CAN_LoadSignalValuesArray(DB_DM1_BCM_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->SPN_Mode;
    dArray[1] = pMsg->OccuranceCount;
    dArray[2] = pMsg->SPN_HighBit;
    dArray[3] = pMsg->FMI;
    dArray[4] = pMsg->SPN_Num;
    dArray[5] = pMsg->MalfunctionIndicatorLamp;
    dArray[6] = pMsg->RedStopLamp;
    dArray[7] = pMsg->ProtectLamp;
    dArray[8] = pMsg->AmberWarningLamp;
}

void DB_DM1_BCM_HS_CAN_LoadRawSignalValuesArray(DB_DM1_BCM_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->SPN_Mode_raw;
    nRawValues[1] = pMsg->OccuranceCount_raw;
    nRawValues[2] = pMsg->SPN_HighBit_raw;
    nRawValues[3] = pMsg->FMI_raw;
    nRawValues[4] = pMsg->SPN_Num_raw;
    nRawValues[5] = pMsg->MalfunctionIndicatorLamp_raw;
    nRawValues[6] = pMsg->RedStopLamp_raw;
    nRawValues[7] = pMsg->ProtectLamp_raw;
    nRawValues[8] = pMsg->AmberWarningLamp_raw;
}

int DB_DM1_BCM_HS_CAN_Transmit(DB_DM1_BCM_HS_CAN * pMsg)
{
    double dArray[9];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DM1_BCM_HS_CAN_Init(pMsg);
    }

    DB_DM1_BCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 9);
}

int DB_DM1_BCM_HS_CAN_Transmit_raw(DB_DM1_BCM_HS_CAN * pMsg)
{
    uint64 nRawValues[9];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DM1_BCM_HS_CAN_Init(pMsg);
    }

    DB_DM1_BCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 9);
}

int DB_DM1_BCM_HS_CAN_UpdateBytesFromSignals(DB_DM1_BCM_HS_CAN * pMsg)
{
    double dArray[9];

    DB_DM1_BCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, dArray, 9, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_DM1_BCM_HS_CAN_UpdateBytesFromRawSignals(DB_DM1_BCM_HS_CAN * pMsg)
{
    uint64 nRawValues[9];

    DB_DM1_BCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_DM1_BCM_HS_CAN_Index, nRawValues, 9, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_BCM_HS_CAN_Index = 62;

void DB_NM_BCM_HS_CAN_Init(DB_NM_BCM_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_BCM_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->BCM_NM_Sleep_ACK = dValues[0];
    pMsg->BCM_NM_Sleep_Ind = dValues[1];
    pMsg->BCM_NM_Limphome = dValues[2];
    pMsg->BCM_NM_Ring = dValues[3];
    pMsg->BCM_NM_Alive = dValues[4];
    pMsg->BCM_NM_DA = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->BCM_NM_Sleep_ACK_raw = (BYTE)nRawValues[0];
    pMsg->BCM_NM_Sleep_Ind_raw = (BYTE)nRawValues[1];
    pMsg->BCM_NM_Limphome_raw = (BYTE)nRawValues[2];
    pMsg->BCM_NM_Ring_raw = (BYTE)nRawValues[3];
    pMsg->BCM_NM_Alive_raw = (BYTE)nRawValues[4];
    pMsg->BCM_NM_DA_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_BCM_HS_CAN_LoadSignalValuesArray(DB_NM_BCM_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->BCM_NM_Sleep_ACK;
    dArray[1] = pMsg->BCM_NM_Sleep_Ind;
    dArray[2] = pMsg->BCM_NM_Limphome;
    dArray[3] = pMsg->BCM_NM_Ring;
    dArray[4] = pMsg->BCM_NM_Alive;
    dArray[5] = pMsg->BCM_NM_DA;
}

void DB_NM_BCM_HS_CAN_LoadRawSignalValuesArray(DB_NM_BCM_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->BCM_NM_Sleep_ACK_raw;
    nRawValues[1] = pMsg->BCM_NM_Sleep_Ind_raw;
    nRawValues[2] = pMsg->BCM_NM_Limphome_raw;
    nRawValues[3] = pMsg->BCM_NM_Ring_raw;
    nRawValues[4] = pMsg->BCM_NM_Alive_raw;
    nRawValues[5] = pMsg->BCM_NM_DA_raw;
}

int DB_NM_BCM_HS_CAN_Transmit(DB_NM_BCM_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_BCM_HS_CAN_Init(pMsg);
    }

    DB_NM_BCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_NM_BCM_HS_CAN_Transmit_raw(DB_NM_BCM_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_BCM_HS_CAN_Init(pMsg);
    }

    DB_NM_BCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_NM_BCM_HS_CAN_UpdateBytesFromSignals(DB_NM_BCM_HS_CAN * pMsg)
{
    double dArray[6];

    DB_NM_BCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_BCM_HS_CAN_UpdateBytesFromRawSignals(DB_NM_BCM_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_NM_BCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_BCM_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_TW_HS_CAN_Index = 63;

void DB_TW_HS_CAN_Init(DB_TW_HS_CAN * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_TW_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TyresLostWarningSig = dValues[0];
    pMsg->TyreID = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_TW_HS_CAN_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->TyresLostWarningSig_raw = (BYTE)nRawValues[0];
    pMsg->TyreID_raw = (BYTE)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_TW_HS_CAN_LoadSignalValuesArray(DB_TW_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TyresLostWarningSig;
    dArray[1] = pMsg->TyreID;
}

void DB_TW_HS_CAN_LoadRawSignalValuesArray(DB_TW_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TyresLostWarningSig_raw;
    nRawValues[1] = pMsg->TyreID_raw;
}

int DB_TW_HS_CAN_Transmit(DB_TW_HS_CAN * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_TW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_TW_HS_CAN_Init(pMsg);
    }

    DB_TW_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_TW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_TW_HS_CAN_Transmit_raw(DB_TW_HS_CAN * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_TW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_TW_HS_CAN_Init(pMsg);
    }

    DB_TW_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_TW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_TW_HS_CAN_UpdateBytesFromSignals(DB_TW_HS_CAN * pMsg)
{
    double dArray[2];

    DB_TW_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_TW_HS_CAN_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_TW_HS_CAN_UpdateBytesFromRawSignals(DB_TW_HS_CAN * pMsg)
{
    uint64 nRawValues[2];

    DB_TW_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_TW_HS_CAN_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_TPMS_HS_CAN_Index = 64;

void DB_NM_TPMS_HS_CAN_Init(DB_NM_TPMS_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_TPMS_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TPMS_NM_Sleep_ACK = dValues[0];
    pMsg->TPMS_NM_Sleep_Ind = dValues[1];
    pMsg->TPMS_NM_Limphome = dValues[2];
    pMsg->TPMS_NM_Ring = dValues[3];
    pMsg->TPMS_NM_Alive = dValues[4];
    pMsg->TPMS_NM_DA = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->TPMS_NM_Sleep_ACK_raw = (BYTE)nRawValues[0];
    pMsg->TPMS_NM_Sleep_Ind_raw = (BYTE)nRawValues[1];
    pMsg->TPMS_NM_Limphome_raw = (BYTE)nRawValues[2];
    pMsg->TPMS_NM_Ring_raw = (BYTE)nRawValues[3];
    pMsg->TPMS_NM_Alive_raw = (BYTE)nRawValues[4];
    pMsg->TPMS_NM_DA_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_TPMS_HS_CAN_LoadSignalValuesArray(DB_NM_TPMS_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TPMS_NM_Sleep_ACK;
    dArray[1] = pMsg->TPMS_NM_Sleep_Ind;
    dArray[2] = pMsg->TPMS_NM_Limphome;
    dArray[3] = pMsg->TPMS_NM_Ring;
    dArray[4] = pMsg->TPMS_NM_Alive;
    dArray[5] = pMsg->TPMS_NM_DA;
}

void DB_NM_TPMS_HS_CAN_LoadRawSignalValuesArray(DB_NM_TPMS_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TPMS_NM_Sleep_ACK_raw;
    nRawValues[1] = pMsg->TPMS_NM_Sleep_Ind_raw;
    nRawValues[2] = pMsg->TPMS_NM_Limphome_raw;
    nRawValues[3] = pMsg->TPMS_NM_Ring_raw;
    nRawValues[4] = pMsg->TPMS_NM_Alive_raw;
    nRawValues[5] = pMsg->TPMS_NM_DA_raw;
}

int DB_NM_TPMS_HS_CAN_Transmit(DB_NM_TPMS_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_TPMS_HS_CAN_Init(pMsg);
    }

    DB_NM_TPMS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_NM_TPMS_HS_CAN_Transmit_raw(DB_NM_TPMS_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_TPMS_HS_CAN_Init(pMsg);
    }

    DB_NM_TPMS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_NM_TPMS_HS_CAN_UpdateBytesFromSignals(DB_NM_TPMS_HS_CAN * pMsg)
{
    double dArray[6];

    DB_NM_TPMS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_TPMS_HS_CAN_UpdateBytesFromRawSignals(DB_NM_TPMS_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_NM_TPMS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_TPMS_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_DCM1_HS_CAN_Index = 65;

void DB_DCM1_HS_CAN_Init(DB_DCM1_HS_CAN * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_DCM1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TelecontrolLockOpenDoor = dValues[0];
    pMsg->RDrSwSig = dValues[1];
    pMsg->LDrSwSig = dValues[2];
    pMsg->TelecontrolLockInvalid = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_DCM1_HS_CAN_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->TelecontrolLockOpenDoor_raw = (BYTE)nRawValues[0];
    pMsg->RDrSwSig_raw = (BYTE)nRawValues[1];
    pMsg->LDrSwSig_raw = (BYTE)nRawValues[2];
    pMsg->TelecontrolLockInvalid_raw = (BYTE)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_DCM1_HS_CAN_LoadSignalValuesArray(DB_DCM1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TelecontrolLockOpenDoor;
    dArray[1] = pMsg->RDrSwSig;
    dArray[2] = pMsg->LDrSwSig;
    dArray[3] = pMsg->TelecontrolLockInvalid;
}

void DB_DCM1_HS_CAN_LoadRawSignalValuesArray(DB_DCM1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TelecontrolLockOpenDoor_raw;
    nRawValues[1] = pMsg->RDrSwSig_raw;
    nRawValues[2] = pMsg->LDrSwSig_raw;
    nRawValues[3] = pMsg->TelecontrolLockInvalid_raw;
}

int DB_DCM1_HS_CAN_Transmit(DB_DCM1_HS_CAN * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DCM1_HS_CAN_Init(pMsg);
    }

    DB_DCM1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_DCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_DCM1_HS_CAN_Transmit_raw(DB_DCM1_HS_CAN * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DCM1_HS_CAN_Init(pMsg);
    }

    DB_DCM1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_DCM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_DCM1_HS_CAN_UpdateBytesFromSignals(DB_DCM1_HS_CAN * pMsg)
{
    double dArray[4];

    DB_DCM1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_DCM1_HS_CAN_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_DCM1_HS_CAN_UpdateBytesFromRawSignals(DB_DCM1_HS_CAN * pMsg)
{
    uint64 nRawValues[4];

    DB_DCM1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_DCM1_HS_CAN_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_DCMcmd_HS_CAN_Index = 66;

void DB_DCMcmd_HS_CAN_Init(DB_DCMcmd_HS_CAN * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_DCMcmd_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TelecontrolAtmosphereLightSwitch = dValues[0];
    pMsg->TelecontrolTopLightSwitch = dValues[1];
    pMsg->CheckALLLightsCmd = dValues[2];
    pMsg->InLgtOFFSwt_InLgtOFFSwt = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_DCMcmd_HS_CAN_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->TelecontrolAtmosphereLightSwitch_raw = (BYTE)nRawValues[0];
    pMsg->TelecontrolTopLightSwitch_raw = (BYTE)nRawValues[1];
    pMsg->CheckALLLightsCmd_raw = (BYTE)nRawValues[2];
    pMsg->InLgtOFFSwt_InLgtOFFSwt_raw = (BYTE)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_DCMcmd_HS_CAN_LoadSignalValuesArray(DB_DCMcmd_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TelecontrolAtmosphereLightSwitch;
    dArray[1] = pMsg->TelecontrolTopLightSwitch;
    dArray[2] = pMsg->CheckALLLightsCmd;
    dArray[3] = pMsg->InLgtOFFSwt_InLgtOFFSwt;
}

void DB_DCMcmd_HS_CAN_LoadRawSignalValuesArray(DB_DCMcmd_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TelecontrolAtmosphereLightSwitch_raw;
    nRawValues[1] = pMsg->TelecontrolTopLightSwitch_raw;
    nRawValues[2] = pMsg->CheckALLLightsCmd_raw;
    nRawValues[3] = pMsg->InLgtOFFSwt_InLgtOFFSwt_raw;
}

int DB_DCMcmd_HS_CAN_Transmit(DB_DCMcmd_HS_CAN * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DCMcmd_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DCMcmd_HS_CAN_Init(pMsg);
    }

    DB_DCMcmd_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_DCMcmd_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_DCMcmd_HS_CAN_Transmit_raw(DB_DCMcmd_HS_CAN * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DCMcmd_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DCMcmd_HS_CAN_Init(pMsg);
    }

    DB_DCMcmd_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_DCMcmd_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_DCMcmd_HS_CAN_UpdateBytesFromSignals(DB_DCMcmd_HS_CAN * pMsg)
{
    double dArray[4];

    DB_DCMcmd_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_DCMcmd_HS_CAN_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_DCMcmd_HS_CAN_UpdateBytesFromRawSignals(DB_DCMcmd_HS_CAN * pMsg)
{
    uint64 nRawValues[4];

    DB_DCMcmd_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_DCMcmd_HS_CAN_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_DCM_HS_CAN_Index = 67;

void DB_NM_DCM_HS_CAN_Init(DB_NM_DCM_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_DCM_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DCM_NM_Sleep_ACK = dValues[0];
    pMsg->DCM_NM_Sleep_Ind = dValues[1];
    pMsg->DCM_NM_Limphome = dValues[2];
    pMsg->DCM_NM_Ring = dValues[3];
    pMsg->DCM_NM_Alive = dValues[4];
    pMsg->DCM_NM_DA = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->DCM_NM_Sleep_ACK_raw = (BYTE)nRawValues[0];
    pMsg->DCM_NM_Sleep_Ind_raw = (BYTE)nRawValues[1];
    pMsg->DCM_NM_Limphome_raw = (BYTE)nRawValues[2];
    pMsg->DCM_NM_Ring_raw = (BYTE)nRawValues[3];
    pMsg->DCM_NM_Alive_raw = (BYTE)nRawValues[4];
    pMsg->DCM_NM_DA_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_DCM_HS_CAN_LoadSignalValuesArray(DB_NM_DCM_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DCM_NM_Sleep_ACK;
    dArray[1] = pMsg->DCM_NM_Sleep_Ind;
    dArray[2] = pMsg->DCM_NM_Limphome;
    dArray[3] = pMsg->DCM_NM_Ring;
    dArray[4] = pMsg->DCM_NM_Alive;
    dArray[5] = pMsg->DCM_NM_DA;
}

void DB_NM_DCM_HS_CAN_LoadRawSignalValuesArray(DB_NM_DCM_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DCM_NM_Sleep_ACK_raw;
    nRawValues[1] = pMsg->DCM_NM_Sleep_Ind_raw;
    nRawValues[2] = pMsg->DCM_NM_Limphome_raw;
    nRawValues[3] = pMsg->DCM_NM_Ring_raw;
    nRawValues[4] = pMsg->DCM_NM_Alive_raw;
    nRawValues[5] = pMsg->DCM_NM_DA_raw;
}

int DB_NM_DCM_HS_CAN_Transmit(DB_NM_DCM_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_DCM_HS_CAN_Init(pMsg);
    }

    DB_NM_DCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_NM_DCM_HS_CAN_Transmit_raw(DB_NM_DCM_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_DCM_HS_CAN_Init(pMsg);
    }

    DB_NM_DCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_NM_DCM_HS_CAN_UpdateBytesFromSignals(DB_NM_DCM_HS_CAN * pMsg)
{
    double dArray[6];

    DB_NM_DCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_DCM_HS_CAN_UpdateBytesFromRawSignals(DB_NM_DCM_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_NM_DCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_DCM_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_AC_HS_CAN_Index = 68;

void DB_NM_AC_HS_CAN_Init(DB_NM_AC_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_AC_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AC_NM_Sleep_ACK = dValues[0];
    pMsg->AC_NM_Sleep_Ind = dValues[1];
    pMsg->AC_NM_Limphome = dValues[2];
    pMsg->AC_NM_Ring = dValues[3];
    pMsg->AC_NM_Alive = dValues[4];
    pMsg->AC_NM_DA = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->AC_NM_Sleep_ACK_raw = (BYTE)nRawValues[0];
    pMsg->AC_NM_Sleep_Ind_raw = (BYTE)nRawValues[1];
    pMsg->AC_NM_Limphome_raw = (BYTE)nRawValues[2];
    pMsg->AC_NM_Ring_raw = (BYTE)nRawValues[3];
    pMsg->AC_NM_Alive_raw = (BYTE)nRawValues[4];
    pMsg->AC_NM_DA_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_AC_HS_CAN_LoadSignalValuesArray(DB_NM_AC_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AC_NM_Sleep_ACK;
    dArray[1] = pMsg->AC_NM_Sleep_Ind;
    dArray[2] = pMsg->AC_NM_Limphome;
    dArray[3] = pMsg->AC_NM_Ring;
    dArray[4] = pMsg->AC_NM_Alive;
    dArray[5] = pMsg->AC_NM_DA;
}

void DB_NM_AC_HS_CAN_LoadRawSignalValuesArray(DB_NM_AC_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AC_NM_Sleep_ACK_raw;
    nRawValues[1] = pMsg->AC_NM_Sleep_Ind_raw;
    nRawValues[2] = pMsg->AC_NM_Limphome_raw;
    nRawValues[3] = pMsg->AC_NM_Ring_raw;
    nRawValues[4] = pMsg->AC_NM_Alive_raw;
    nRawValues[5] = pMsg->AC_NM_DA_raw;
}

int DB_NM_AC_HS_CAN_Transmit(DB_NM_AC_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_AC_HS_CAN_Init(pMsg);
    }

    DB_NM_AC_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_NM_AC_HS_CAN_Transmit_raw(DB_NM_AC_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_AC_HS_CAN_Init(pMsg);
    }

    DB_NM_AC_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_NM_AC_HS_CAN_UpdateBytesFromSignals(DB_NM_AC_HS_CAN * pMsg)
{
    double dArray[6];

    DB_NM_AC_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_AC_HS_CAN_UpdateBytesFromRawSignals(DB_NM_AC_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_NM_AC_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_AC_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_IC1_HS_CAN_Index = 69;

void DB_IC1_HS_CAN_Init(DB_IC1_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_IC1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AccelerationSig = dValues[0];
    pMsg->RnSensty = dValues[1];
    pMsg->RequestBCM_ResetA2_OilQB = dValues[2];
    pMsg->RequestBCM_ResetA1_OilQB = dValues[3];
    pMsg->RequestBCM_ResetT_OilQB = dValues[4];
    pMsg->RequestBCM_ResetE_QilQB = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_IC1_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->AccelerationSig_raw = (BYTE)nRawValues[0];
    pMsg->RnSensty_raw = (BYTE)nRawValues[1];
    pMsg->RequestBCM_ResetA2_OilQB_raw = (BYTE)nRawValues[2];
    pMsg->RequestBCM_ResetA1_OilQB_raw = (BYTE)nRawValues[3];
    pMsg->RequestBCM_ResetT_OilQB_raw = (BYTE)nRawValues[4];
    pMsg->RequestBCM_ResetE_QilQB_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_IC1_HS_CAN_LoadSignalValuesArray(DB_IC1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AccelerationSig;
    dArray[1] = pMsg->RnSensty;
    dArray[2] = pMsg->RequestBCM_ResetA2_OilQB;
    dArray[3] = pMsg->RequestBCM_ResetA1_OilQB;
    dArray[4] = pMsg->RequestBCM_ResetT_OilQB;
    dArray[5] = pMsg->RequestBCM_ResetE_QilQB;
}

void DB_IC1_HS_CAN_LoadRawSignalValuesArray(DB_IC1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AccelerationSig_raw;
    nRawValues[1] = pMsg->RnSensty_raw;
    nRawValues[2] = pMsg->RequestBCM_ResetA2_OilQB_raw;
    nRawValues[3] = pMsg->RequestBCM_ResetA1_OilQB_raw;
    nRawValues[4] = pMsg->RequestBCM_ResetT_OilQB_raw;
    nRawValues[5] = pMsg->RequestBCM_ResetE_QilQB_raw;
}

int DB_IC1_HS_CAN_Transmit(DB_IC1_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_IC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_IC1_HS_CAN_Init(pMsg);
    }

    DB_IC1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_IC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_IC1_HS_CAN_Transmit_raw(DB_IC1_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_IC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_IC1_HS_CAN_Init(pMsg);
    }

    DB_IC1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_IC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_IC1_HS_CAN_UpdateBytesFromSignals(DB_IC1_HS_CAN * pMsg)
{
    double dArray[6];

    DB_IC1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_IC1_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_IC1_HS_CAN_UpdateBytesFromRawSignals(DB_IC1_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_IC1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_IC1_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_IC_HS_CAN_Index = 70;

void DB_NM_IC_HS_CAN_Init(DB_NM_IC_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_IC_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->IC_NM_Sleep_Ind = dValues[0];
    pMsg->IC_NM_Sleep_ACK = dValues[1];
    pMsg->IC_NM_Ring = dValues[2];
    pMsg->IC_NM_Limphome = dValues[3];
    pMsg->IC_NM_DA = dValues[4];
    pMsg->IC_NM_Alive = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->IC_NM_Sleep_Ind_raw = (BYTE)nRawValues[0];
    pMsg->IC_NM_Sleep_ACK_raw = (BYTE)nRawValues[1];
    pMsg->IC_NM_Ring_raw = (BYTE)nRawValues[2];
    pMsg->IC_NM_Limphome_raw = (BYTE)nRawValues[3];
    pMsg->IC_NM_DA_raw = (BYTE)nRawValues[4];
    pMsg->IC_NM_Alive_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_IC_HS_CAN_LoadSignalValuesArray(DB_NM_IC_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->IC_NM_Sleep_Ind;
    dArray[1] = pMsg->IC_NM_Sleep_ACK;
    dArray[2] = pMsg->IC_NM_Ring;
    dArray[3] = pMsg->IC_NM_Limphome;
    dArray[4] = pMsg->IC_NM_DA;
    dArray[5] = pMsg->IC_NM_Alive;
}

void DB_NM_IC_HS_CAN_LoadRawSignalValuesArray(DB_NM_IC_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->IC_NM_Sleep_Ind_raw;
    nRawValues[1] = pMsg->IC_NM_Sleep_ACK_raw;
    nRawValues[2] = pMsg->IC_NM_Ring_raw;
    nRawValues[3] = pMsg->IC_NM_Limphome_raw;
    nRawValues[4] = pMsg->IC_NM_DA_raw;
    nRawValues[5] = pMsg->IC_NM_Alive_raw;
}

int DB_NM_IC_HS_CAN_Transmit(DB_NM_IC_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_IC_HS_CAN_Init(pMsg);
    }

    DB_NM_IC_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_NM_IC_HS_CAN_Transmit_raw(DB_NM_IC_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_IC_HS_CAN_Init(pMsg);
    }

    DB_NM_IC_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_NM_IC_HS_CAN_UpdateBytesFromSignals(DB_NM_IC_HS_CAN * pMsg)
{
    double dArray[6];

    DB_NM_IC_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_IC_HS_CAN_UpdateBytesFromRawSignals(DB_NM_IC_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_NM_IC_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_IC_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_OilQitT_HS_CAN_Index = 71;

void DB_OilQitT_HS_CAN_Init(DB_OilQitT_HS_CAN * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_OilQitT_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->OilDielectricConstant_T = dValues[0];
    pMsg->OilDensity_T = dValues[1];
    pMsg->OilViscosity_T = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_OilQitT_HS_CAN_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->OilDielectricConstant_T_raw = (WORD)nRawValues[0];
    pMsg->OilDensity_T_raw = (WORD)nRawValues[1];
    pMsg->OilViscosity_T_raw = (WORD)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_OilQitT_HS_CAN_LoadSignalValuesArray(DB_OilQitT_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->OilDielectricConstant_T;
    dArray[1] = pMsg->OilDensity_T;
    dArray[2] = pMsg->OilViscosity_T;
}

void DB_OilQitT_HS_CAN_LoadRawSignalValuesArray(DB_OilQitT_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->OilDielectricConstant_T_raw;
    nRawValues[1] = pMsg->OilDensity_T_raw;
    nRawValues[2] = pMsg->OilViscosity_T_raw;
}

int DB_OilQitT_HS_CAN_Transmit(DB_OilQitT_HS_CAN * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OilQitT_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OilQitT_HS_CAN_Init(pMsg);
    }

    DB_OilQitT_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_OilQitT_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_OilQitT_HS_CAN_Transmit_raw(DB_OilQitT_HS_CAN * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OilQitT_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OilQitT_HS_CAN_Init(pMsg);
    }

    DB_OilQitT_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_OilQitT_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_OilQitT_HS_CAN_UpdateBytesFromSignals(DB_OilQitT_HS_CAN * pMsg)
{
    double dArray[3];

    DB_OilQitT_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_OilQitT_HS_CAN_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_OilQitT_HS_CAN_UpdateBytesFromRawSignals(DB_OilQitT_HS_CAN * pMsg)
{
    uint64 nRawValues[3];

    DB_OilQitT_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_OilQitT_HS_CAN_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_OilQitE_HS_CAN_Index = 72;

void DB_OilQitE_HS_CAN_Init(DB_OilQitE_HS_CAN * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_OilQitE_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->OilDielectricConstant_E = dValues[0];
    pMsg->OilViscosity_E = dValues[1];
    pMsg->OilDensity_E = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_OilQitE_HS_CAN_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->OilDielectricConstant_E_raw = (WORD)nRawValues[0];
    pMsg->OilViscosity_E_raw = (WORD)nRawValues[1];
    pMsg->OilDensity_E_raw = (WORD)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_OilQitE_HS_CAN_LoadSignalValuesArray(DB_OilQitE_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->OilDielectricConstant_E;
    dArray[1] = pMsg->OilViscosity_E;
    dArray[2] = pMsg->OilDensity_E;
}

void DB_OilQitE_HS_CAN_LoadRawSignalValuesArray(DB_OilQitE_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->OilDielectricConstant_E_raw;
    nRawValues[1] = pMsg->OilViscosity_E_raw;
    nRawValues[2] = pMsg->OilDensity_E_raw;
}

int DB_OilQitE_HS_CAN_Transmit(DB_OilQitE_HS_CAN * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OilQitE_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OilQitE_HS_CAN_Init(pMsg);
    }

    DB_OilQitE_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_OilQitE_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_OilQitE_HS_CAN_Transmit_raw(DB_OilQitE_HS_CAN * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OilQitE_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OilQitE_HS_CAN_Init(pMsg);
    }

    DB_OilQitE_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_OilQitE_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_OilQitE_HS_CAN_UpdateBytesFromSignals(DB_OilQitE_HS_CAN * pMsg)
{
    double dArray[3];

    DB_OilQitE_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_OilQitE_HS_CAN_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_OilQitE_HS_CAN_UpdateBytesFromRawSignals(DB_OilQitE_HS_CAN * pMsg)
{
    uint64 nRawValues[3];

    DB_OilQitE_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_OilQitE_HS_CAN_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_OilQitA1_HS_CAN_Index = 73;

void DB_OilQitA1_HS_CAN_Init(DB_OilQitA1_HS_CAN * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_OilQitA1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->OilViscosity_A1 = dValues[0];
    pMsg->OilDielectricConstant_A1 = dValues[1];
    pMsg->OilDensity_A1 = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_OilQitA1_HS_CAN_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->OilViscosity_A1_raw = (WORD)nRawValues[0];
    pMsg->OilDielectricConstant_A1_raw = (WORD)nRawValues[1];
    pMsg->OilDensity_A1_raw = (WORD)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_OilQitA1_HS_CAN_LoadSignalValuesArray(DB_OilQitA1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->OilViscosity_A1;
    dArray[1] = pMsg->OilDielectricConstant_A1;
    dArray[2] = pMsg->OilDensity_A1;
}

void DB_OilQitA1_HS_CAN_LoadRawSignalValuesArray(DB_OilQitA1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->OilViscosity_A1_raw;
    nRawValues[1] = pMsg->OilDielectricConstant_A1_raw;
    nRawValues[2] = pMsg->OilDensity_A1_raw;
}

int DB_OilQitA1_HS_CAN_Transmit(DB_OilQitA1_HS_CAN * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OilQitA1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OilQitA1_HS_CAN_Init(pMsg);
    }

    DB_OilQitA1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_OilQitA1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_OilQitA1_HS_CAN_Transmit_raw(DB_OilQitA1_HS_CAN * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OilQitA1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OilQitA1_HS_CAN_Init(pMsg);
    }

    DB_OilQitA1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_OilQitA1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_OilQitA1_HS_CAN_UpdateBytesFromSignals(DB_OilQitA1_HS_CAN * pMsg)
{
    double dArray[3];

    DB_OilQitA1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_OilQitA1_HS_CAN_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_OilQitA1_HS_CAN_UpdateBytesFromRawSignals(DB_OilQitA1_HS_CAN * pMsg)
{
    uint64 nRawValues[3];

    DB_OilQitA1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_OilQitA1_HS_CAN_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_OilQitA2_HS_CAN_Index = 74;

void DB_OilQitA2_HS_CAN_Init(DB_OilQitA2_HS_CAN * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_OilQitA2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->OilDensity_A2 = dValues[0];
    pMsg->OilViscosity_A2 = dValues[1];
    pMsg->OilDielectricConstant_A2 = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_OilQitA2_HS_CAN_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->OilDensity_A2_raw = (WORD)nRawValues[0];
    pMsg->OilViscosity_A2_raw = (WORD)nRawValues[1];
    pMsg->OilDielectricConstant_A2_raw = (WORD)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_OilQitA2_HS_CAN_LoadSignalValuesArray(DB_OilQitA2_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->OilDensity_A2;
    dArray[1] = pMsg->OilViscosity_A2;
    dArray[2] = pMsg->OilDielectricConstant_A2;
}

void DB_OilQitA2_HS_CAN_LoadRawSignalValuesArray(DB_OilQitA2_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->OilDensity_A2_raw;
    nRawValues[1] = pMsg->OilViscosity_A2_raw;
    nRawValues[2] = pMsg->OilDielectricConstant_A2_raw;
}

int DB_OilQitA2_HS_CAN_Transmit(DB_OilQitA2_HS_CAN * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OilQitA2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OilQitA2_HS_CAN_Init(pMsg);
    }

    DB_OilQitA2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_OilQitA2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_OilQitA2_HS_CAN_Transmit_raw(DB_OilQitA2_HS_CAN * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_OilQitA2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_OilQitA2_HS_CAN_Init(pMsg);
    }

    DB_OilQitA2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_OilQitA2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_OilQitA2_HS_CAN_UpdateBytesFromSignals(DB_OilQitA2_HS_CAN * pMsg)
{
    double dArray[3];

    DB_OilQitA2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_OilQitA2_HS_CAN_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_OilQitA2_HS_CAN_UpdateBytesFromRawSignals(DB_OilQitA2_HS_CAN * pMsg)
{
    uint64 nRawValues[3];

    DB_OilQitA2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_OilQitA2_HS_CAN_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_VCU_1_HS_CAN_Index = 75;

void DB_VCU_1_HS_CAN_Init(DB_VCU_1_HS_CAN * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VCU_1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->RevGearSig = dValues[0];
    pMsg->ExhaustBrake = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_VCU_1_HS_CAN_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->RevGearSig_raw = (BYTE)nRawValues[0];
    pMsg->ExhaustBrake_raw = (BYTE)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_VCU_1_HS_CAN_LoadSignalValuesArray(DB_VCU_1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->RevGearSig;
    dArray[1] = pMsg->ExhaustBrake;
}

void DB_VCU_1_HS_CAN_LoadRawSignalValuesArray(DB_VCU_1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->RevGearSig_raw;
    nRawValues[1] = pMsg->ExhaustBrake_raw;
}

int DB_VCU_1_HS_CAN_Transmit(DB_VCU_1_HS_CAN * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VCU_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VCU_1_HS_CAN_Init(pMsg);
    }

    DB_VCU_1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_VCU_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_VCU_1_HS_CAN_Transmit_raw(DB_VCU_1_HS_CAN * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VCU_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VCU_1_HS_CAN_Init(pMsg);
    }

    DB_VCU_1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VCU_1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_VCU_1_HS_CAN_UpdateBytesFromSignals(DB_VCU_1_HS_CAN * pMsg)
{
    double dArray[2];

    DB_VCU_1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_VCU_1_HS_CAN_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_VCU_1_HS_CAN_UpdateBytesFromRawSignals(DB_VCU_1_HS_CAN * pMsg)
{
    uint64 nRawValues[2];

    DB_VCU_1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_VCU_1_HS_CAN_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_CCVS_EMS_HS_CAN_Index = 76;

void DB_CCVS_EMS_HS_CAN_Init(DB_CCVS_EMS_HS_CAN * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_CCVS_EMS_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Status_of_parking_brake = dValues[0];
    pMsg->Brake_Switch = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_CCVS_EMS_HS_CAN_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Status_of_parking_brake_raw = (BYTE)nRawValues[0];
    pMsg->Brake_Switch_raw = (BYTE)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_CCVS_EMS_HS_CAN_LoadSignalValuesArray(DB_CCVS_EMS_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->Status_of_parking_brake;
    dArray[1] = pMsg->Brake_Switch;
}

void DB_CCVS_EMS_HS_CAN_LoadRawSignalValuesArray(DB_CCVS_EMS_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Status_of_parking_brake_raw;
    nRawValues[1] = pMsg->Brake_Switch_raw;
}

int DB_CCVS_EMS_HS_CAN_Transmit(DB_CCVS_EMS_HS_CAN * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_CCVS_EMS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_CCVS_EMS_HS_CAN_Init(pMsg);
    }

    DB_CCVS_EMS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_CCVS_EMS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_CCVS_EMS_HS_CAN_Transmit_raw(DB_CCVS_EMS_HS_CAN * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_CCVS_EMS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_CCVS_EMS_HS_CAN_Init(pMsg);
    }

    DB_CCVS_EMS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_CCVS_EMS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_CCVS_EMS_HS_CAN_UpdateBytesFromSignals(DB_CCVS_EMS_HS_CAN * pMsg)
{
    double dArray[2];

    DB_CCVS_EMS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_CCVS_EMS_HS_CAN_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_CCVS_EMS_HS_CAN_UpdateBytesFromRawSignals(DB_CCVS_EMS_HS_CAN * pMsg)
{
    uint64 nRawValues[2];

    DB_CCVS_EMS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_CCVS_EMS_HS_CAN_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_VDC1_HS_CAN_Index = 77;

void DB_VDC1_HS_CAN_Init(DB_VDC1_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VDC1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->VDC_BrakeLightRequest = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_VDC1_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->VDC_BrakeLightRequest_raw = (BYTE)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_VDC1_HS_CAN_LoadSignalValuesArray(DB_VDC1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->VDC_BrakeLightRequest;
}

void DB_VDC1_HS_CAN_LoadRawSignalValuesArray(DB_VDC1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->VDC_BrakeLightRequest_raw;
}

int DB_VDC1_HS_CAN_Transmit(DB_VDC1_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VDC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VDC1_HS_CAN_Init(pMsg);
    }

    DB_VDC1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_VDC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_VDC1_HS_CAN_Transmit_raw(DB_VDC1_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VDC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VDC1_HS_CAN_Init(pMsg);
    }

    DB_VDC1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VDC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_VDC1_HS_CAN_UpdateBytesFromSignals(DB_VDC1_HS_CAN * pMsg)
{
    double dArray[1];

    DB_VDC1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_VDC1_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_VDC1_HS_CAN_UpdateBytesFromRawSignals(DB_VDC1_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_VDC1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_VDC1_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_ERC1_HS_CAN_Index = 78;

void DB_ERC1_HS_CAN_Init(DB_ERC1_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_ERC1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->RetarderEnable_BrakeAssistSW = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_ERC1_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->RetarderEnable_BrakeAssistSW_raw = (BYTE)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_ERC1_HS_CAN_LoadSignalValuesArray(DB_ERC1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->RetarderEnable_BrakeAssistSW;
}

void DB_ERC1_HS_CAN_LoadRawSignalValuesArray(DB_ERC1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->RetarderEnable_BrakeAssistSW_raw;
}

int DB_ERC1_HS_CAN_Transmit(DB_ERC1_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_ERC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_ERC1_HS_CAN_Init(pMsg);
    }

    DB_ERC1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_ERC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_ERC1_HS_CAN_Transmit_raw(DB_ERC1_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_ERC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_ERC1_HS_CAN_Init(pMsg);
    }

    DB_ERC1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_ERC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_ERC1_HS_CAN_UpdateBytesFromSignals(DB_ERC1_HS_CAN * pMsg)
{
    double dArray[1];

    DB_ERC1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_ERC1_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_ERC1_HS_CAN_UpdateBytesFromRawSignals(DB_ERC1_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_ERC1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_ERC1_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_ETC2_HS_CAN_Index = 79;

void DB_ETC2_HS_CAN_Init(DB_ETC2_HS_CAN * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_ETC2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TransmissionCurrentGear = dValues[0];
    pMsg->TransmissionSelectedGear = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_ETC2_HS_CAN_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->TransmissionCurrentGear_raw = (BYTE)nRawValues[0];
    pMsg->TransmissionSelectedGear_raw = (BYTE)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_ETC2_HS_CAN_LoadSignalValuesArray(DB_ETC2_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TransmissionCurrentGear;
    dArray[1] = pMsg->TransmissionSelectedGear;
}

void DB_ETC2_HS_CAN_LoadRawSignalValuesArray(DB_ETC2_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TransmissionCurrentGear_raw;
    nRawValues[1] = pMsg->TransmissionSelectedGear_raw;
}

int DB_ETC2_HS_CAN_Transmit(DB_ETC2_HS_CAN * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_ETC2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_ETC2_HS_CAN_Init(pMsg);
    }

    DB_ETC2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_ETC2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_ETC2_HS_CAN_Transmit_raw(DB_ETC2_HS_CAN * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_ETC2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_ETC2_HS_CAN_Init(pMsg);
    }

    DB_ETC2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_ETC2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_ETC2_HS_CAN_UpdateBytesFromSignals(DB_ETC2_HS_CAN * pMsg)
{
    double dArray[2];

    DB_ETC2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_ETC2_HS_CAN_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_ETC2_HS_CAN_UpdateBytesFromRawSignals(DB_ETC2_HS_CAN * pMsg)
{
    uint64 nRawValues[2];

    DB_ETC2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_ETC2_HS_CAN_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_EEC1_HS_CAN_Index = 80;

void DB_EEC1_HS_CAN_Init(DB_EEC1_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_EEC1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->EngineSpeed = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_EEC1_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->EngineSpeed_raw = (WORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_EEC1_HS_CAN_LoadSignalValuesArray(DB_EEC1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->EngineSpeed;
}

void DB_EEC1_HS_CAN_LoadRawSignalValuesArray(DB_EEC1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->EngineSpeed_raw;
}

int DB_EEC1_HS_CAN_Transmit(DB_EEC1_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_EEC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_EEC1_HS_CAN_Init(pMsg);
    }

    DB_EEC1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_EEC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_EEC1_HS_CAN_Transmit_raw(DB_EEC1_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_EEC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_EEC1_HS_CAN_Init(pMsg);
    }

    DB_EEC1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_EEC1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_EEC1_HS_CAN_UpdateBytesFromSignals(DB_EEC1_HS_CAN * pMsg)
{
    double dArray[1];

    DB_EEC1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_EEC1_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_EEC1_HS_CAN_UpdateBytesFromRawSignals(DB_EEC1_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_EEC1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_EEC1_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_EBC1_BCM_HS_CAN_Index = 81;

void DB_EBC1_BCM_HS_CAN_Init(DB_EBC1_BCM_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_EBC1_BCM_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->ABS_Trailer_Warning_Lamp_State = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_EBC1_BCM_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->ABS_Trailer_Warning_Lamp_State_raw = (BYTE)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_EBC1_BCM_HS_CAN_LoadSignalValuesArray(DB_EBC1_BCM_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->ABS_Trailer_Warning_Lamp_State;
}

void DB_EBC1_BCM_HS_CAN_LoadRawSignalValuesArray(DB_EBC1_BCM_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->ABS_Trailer_Warning_Lamp_State_raw;
}

int DB_EBC1_BCM_HS_CAN_Transmit(DB_EBC1_BCM_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_EBC1_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_EBC1_BCM_HS_CAN_Init(pMsg);
    }

    DB_EBC1_BCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_EBC1_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_EBC1_BCM_HS_CAN_Transmit_raw(DB_EBC1_BCM_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_EBC1_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_EBC1_BCM_HS_CAN_Init(pMsg);
    }

    DB_EBC1_BCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_EBC1_BCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_EBC1_BCM_HS_CAN_UpdateBytesFromSignals(DB_EBC1_BCM_HS_CAN * pMsg)
{
    double dArray[1];

    DB_EBC1_BCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_EBC1_BCM_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_EBC1_BCM_HS_CAN_UpdateBytesFromRawSignals(DB_EBC1_BCM_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_EBC1_BCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_EBC1_BCM_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_EBC1_ABS_HS_CAN_Index = 82;

void DB_EBC1_ABS_HS_CAN_Init(DB_EBC1_ABS_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_EBC1_ABS_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->ABS_active = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_EBC1_ABS_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->ABS_active_raw = (BYTE)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_EBC1_ABS_HS_CAN_LoadSignalValuesArray(DB_EBC1_ABS_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->ABS_active;
}

void DB_EBC1_ABS_HS_CAN_LoadRawSignalValuesArray(DB_EBC1_ABS_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->ABS_active_raw;
}

int DB_EBC1_ABS_HS_CAN_Transmit(DB_EBC1_ABS_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_EBC1_ABS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_EBC1_ABS_HS_CAN_Init(pMsg);
    }

    DB_EBC1_ABS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_EBC1_ABS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_EBC1_ABS_HS_CAN_Transmit_raw(DB_EBC1_ABS_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_EBC1_ABS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_EBC1_ABS_HS_CAN_Init(pMsg);
    }

    DB_EBC1_ABS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_EBC1_ABS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_EBC1_ABS_HS_CAN_UpdateBytesFromSignals(DB_EBC1_ABS_HS_CAN * pMsg)
{
    double dArray[1];

    DB_EBC1_ABS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_EBC1_ABS_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_EBC1_ABS_HS_CAN_UpdateBytesFromRawSignals(DB_EBC1_ABS_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_EBC1_ABS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_EBC1_ABS_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_TESTER_HS_CAN_Index = 83;

void DB_NM_TESTER_HS_CAN_Init(DB_NM_TESTER_HS_CAN * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_TESTER_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AC_NMDataField = dValues[0];
    pMsg->AC_NMSleepAck = dValues[1];
    pMsg->AC_NMSleepInd = dValues[2];
    pMsg->AC_NMLimphome = dValues[3];
    pMsg->AC_NMRing = dValues[4];
    pMsg->AC_NMAlive = dValues[5];
    pMsg->AC_NMDestAddress = dValues[6];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->AC_NMDataField_raw = (uint64)nRawValues[0];
    pMsg->AC_NMSleepAck_raw = (BYTE)nRawValues[1];
    pMsg->AC_NMSleepInd_raw = (BYTE)nRawValues[2];
    pMsg->AC_NMLimphome_raw = (BYTE)nRawValues[3];
    pMsg->AC_NMRing_raw = (BYTE)nRawValues[4];
    pMsg->AC_NMAlive_raw = (BYTE)nRawValues[5];
    pMsg->AC_NMDestAddress_raw = (BYTE)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_TESTER_HS_CAN_LoadSignalValuesArray(DB_NM_TESTER_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AC_NMDataField;
    dArray[1] = pMsg->AC_NMSleepAck;
    dArray[2] = pMsg->AC_NMSleepInd;
    dArray[3] = pMsg->AC_NMLimphome;
    dArray[4] = pMsg->AC_NMRing;
    dArray[5] = pMsg->AC_NMAlive;
    dArray[6] = pMsg->AC_NMDestAddress;
}

void DB_NM_TESTER_HS_CAN_LoadRawSignalValuesArray(DB_NM_TESTER_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AC_NMDataField_raw;
    nRawValues[1] = pMsg->AC_NMSleepAck_raw;
    nRawValues[2] = pMsg->AC_NMSleepInd_raw;
    nRawValues[3] = pMsg->AC_NMLimphome_raw;
    nRawValues[4] = pMsg->AC_NMRing_raw;
    nRawValues[5] = pMsg->AC_NMAlive_raw;
    nRawValues[6] = pMsg->AC_NMDestAddress_raw;
}

int DB_NM_TESTER_HS_CAN_Transmit(DB_NM_TESTER_HS_CAN * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_TESTER_HS_CAN_Init(pMsg);
    }

    DB_NM_TESTER_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int DB_NM_TESTER_HS_CAN_Transmit_raw(DB_NM_TESTER_HS_CAN * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_TESTER_HS_CAN_Init(pMsg);
    }

    DB_NM_TESTER_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int DB_NM_TESTER_HS_CAN_UpdateBytesFromSignals(DB_NM_TESTER_HS_CAN * pMsg)
{
    double dArray[7];

    DB_NM_TESTER_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_TESTER_HS_CAN_UpdateBytesFromRawSignals(DB_NM_TESTER_HS_CAN * pMsg)
{
    uint64 nRawValues[7];

    DB_NM_TESTER_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_TESTER_HS_CAN_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_AC_MMI_HS_CAN_Index = 84;

void DB_NM_AC_MMI_HS_CAN_Init(DB_NM_AC_MMI_HS_CAN * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_AC_MMI_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AC_NMDataField = dValues[0];
    pMsg->AC_NMSleepAck = dValues[1];
    pMsg->AC_NMSleepInd = dValues[2];
    pMsg->AC_NMLimphome = dValues[3];
    pMsg->AC_NMRing = dValues[4];
    pMsg->AC_NMAlive = dValues[5];
    pMsg->AC_NMDestAddress = dValues[6];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->AC_NMDataField_raw = (uint64)nRawValues[0];
    pMsg->AC_NMSleepAck_raw = (BYTE)nRawValues[1];
    pMsg->AC_NMSleepInd_raw = (BYTE)nRawValues[2];
    pMsg->AC_NMLimphome_raw = (BYTE)nRawValues[3];
    pMsg->AC_NMRing_raw = (BYTE)nRawValues[4];
    pMsg->AC_NMAlive_raw = (BYTE)nRawValues[5];
    pMsg->AC_NMDestAddress_raw = (BYTE)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_AC_MMI_HS_CAN_LoadSignalValuesArray(DB_NM_AC_MMI_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AC_NMDataField;
    dArray[1] = pMsg->AC_NMSleepAck;
    dArray[2] = pMsg->AC_NMSleepInd;
    dArray[3] = pMsg->AC_NMLimphome;
    dArray[4] = pMsg->AC_NMRing;
    dArray[5] = pMsg->AC_NMAlive;
    dArray[6] = pMsg->AC_NMDestAddress;
}

void DB_NM_AC_MMI_HS_CAN_LoadRawSignalValuesArray(DB_NM_AC_MMI_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AC_NMDataField_raw;
    nRawValues[1] = pMsg->AC_NMSleepAck_raw;
    nRawValues[2] = pMsg->AC_NMSleepInd_raw;
    nRawValues[3] = pMsg->AC_NMLimphome_raw;
    nRawValues[4] = pMsg->AC_NMRing_raw;
    nRawValues[5] = pMsg->AC_NMAlive_raw;
    nRawValues[6] = pMsg->AC_NMDestAddress_raw;
}

int DB_NM_AC_MMI_HS_CAN_Transmit(DB_NM_AC_MMI_HS_CAN * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_AC_MMI_HS_CAN_Init(pMsg);
    }

    DB_NM_AC_MMI_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int DB_NM_AC_MMI_HS_CAN_Transmit_raw(DB_NM_AC_MMI_HS_CAN * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_AC_MMI_HS_CAN_Init(pMsg);
    }

    DB_NM_AC_MMI_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int DB_NM_AC_MMI_HS_CAN_UpdateBytesFromSignals(DB_NM_AC_MMI_HS_CAN * pMsg)
{
    double dArray[7];

    DB_NM_AC_MMI_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_AC_MMI_HS_CAN_UpdateBytesFromRawSignals(DB_NM_AC_MMI_HS_CAN * pMsg)
{
    uint64 nRawValues[7];

    DB_NM_AC_MMI_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_AC_MMI_HS_CAN_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_MMI_HS_CAN_Index = 85;

void DB_NM_MMI_HS_CAN_Init(DB_NM_MMI_HS_CAN * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_MMI_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AC_NMDataField = dValues[0];
    pMsg->AC_NMSleepAck = dValues[1];
    pMsg->AC_NMSleepInd = dValues[2];
    pMsg->AC_NMLimphome = dValues[3];
    pMsg->AC_NMRing = dValues[4];
    pMsg->AC_NMAlive = dValues[5];
    pMsg->AC_NMDestAddress = dValues[6];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->AC_NMDataField_raw = (uint64)nRawValues[0];
    pMsg->AC_NMSleepAck_raw = (BYTE)nRawValues[1];
    pMsg->AC_NMSleepInd_raw = (BYTE)nRawValues[2];
    pMsg->AC_NMLimphome_raw = (BYTE)nRawValues[3];
    pMsg->AC_NMRing_raw = (BYTE)nRawValues[4];
    pMsg->AC_NMAlive_raw = (BYTE)nRawValues[5];
    pMsg->AC_NMDestAddress_raw = (BYTE)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_MMI_HS_CAN_LoadSignalValuesArray(DB_NM_MMI_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->AC_NMDataField;
    dArray[1] = pMsg->AC_NMSleepAck;
    dArray[2] = pMsg->AC_NMSleepInd;
    dArray[3] = pMsg->AC_NMLimphome;
    dArray[4] = pMsg->AC_NMRing;
    dArray[5] = pMsg->AC_NMAlive;
    dArray[6] = pMsg->AC_NMDestAddress;
}

void DB_NM_MMI_HS_CAN_LoadRawSignalValuesArray(DB_NM_MMI_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AC_NMDataField_raw;
    nRawValues[1] = pMsg->AC_NMSleepAck_raw;
    nRawValues[2] = pMsg->AC_NMSleepInd_raw;
    nRawValues[3] = pMsg->AC_NMLimphome_raw;
    nRawValues[4] = pMsg->AC_NMRing_raw;
    nRawValues[5] = pMsg->AC_NMAlive_raw;
    nRawValues[6] = pMsg->AC_NMDestAddress_raw;
}

int DB_NM_MMI_HS_CAN_Transmit(DB_NM_MMI_HS_CAN * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_MMI_HS_CAN_Init(pMsg);
    }

    DB_NM_MMI_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int DB_NM_MMI_HS_CAN_Transmit_raw(DB_NM_MMI_HS_CAN * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_MMI_HS_CAN_Init(pMsg);
    }

    DB_NM_MMI_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int DB_NM_MMI_HS_CAN_UpdateBytesFromSignals(DB_NM_MMI_HS_CAN * pMsg)
{
    double dArray[7];

    DB_NM_MMI_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_MMI_HS_CAN_UpdateBytesFromRawSignals(DB_NM_MMI_HS_CAN * pMsg)
{
    uint64 nRawValues[7];

    DB_NM_MMI_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_MMI_HS_CAN_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_RCM_HS_CAN_Index = 86;

void DB_NM_RCM_HS_CAN_Init(DB_NM_RCM_HS_CAN * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_RCM_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->RCM_NMDataFiels = dValues[0];
    pMsg->RCM_NMSleepAck = dValues[1];
    pMsg->RCM_NMSleepInd = dValues[2];
    pMsg->RCM_NMLimphome = dValues[3];
    pMsg->RCM_NMRing = dValues[4];
    pMsg->RCM_NMAlive = dValues[5];
    pMsg->RCM_NMDestAddress = dValues[6];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->RCM_NMDataFiels_raw = (uint64)nRawValues[0];
    pMsg->RCM_NMSleepAck_raw = (BYTE)nRawValues[1];
    pMsg->RCM_NMSleepInd_raw = (BYTE)nRawValues[2];
    pMsg->RCM_NMLimphome_raw = (BYTE)nRawValues[3];
    pMsg->RCM_NMRing_raw = (BYTE)nRawValues[4];
    pMsg->RCM_NMAlive_raw = (BYTE)nRawValues[5];
    pMsg->RCM_NMDestAddress_raw = (BYTE)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_RCM_HS_CAN_LoadSignalValuesArray(DB_NM_RCM_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->RCM_NMDataFiels;
    dArray[1] = pMsg->RCM_NMSleepAck;
    dArray[2] = pMsg->RCM_NMSleepInd;
    dArray[3] = pMsg->RCM_NMLimphome;
    dArray[4] = pMsg->RCM_NMRing;
    dArray[5] = pMsg->RCM_NMAlive;
    dArray[6] = pMsg->RCM_NMDestAddress;
}

void DB_NM_RCM_HS_CAN_LoadRawSignalValuesArray(DB_NM_RCM_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->RCM_NMDataFiels_raw;
    nRawValues[1] = pMsg->RCM_NMSleepAck_raw;
    nRawValues[2] = pMsg->RCM_NMSleepInd_raw;
    nRawValues[3] = pMsg->RCM_NMLimphome_raw;
    nRawValues[4] = pMsg->RCM_NMRing_raw;
    nRawValues[5] = pMsg->RCM_NMAlive_raw;
    nRawValues[6] = pMsg->RCM_NMDestAddress_raw;
}

int DB_NM_RCM_HS_CAN_Transmit(DB_NM_RCM_HS_CAN * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_RCM_HS_CAN_Init(pMsg);
    }

    DB_NM_RCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int DB_NM_RCM_HS_CAN_Transmit_raw(DB_NM_RCM_HS_CAN * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_RCM_HS_CAN_Init(pMsg);
    }

    DB_NM_RCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int DB_NM_RCM_HS_CAN_UpdateBytesFromSignals(DB_NM_RCM_HS_CAN * pMsg)
{
    double dArray[7];

    DB_NM_RCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_RCM_HS_CAN_UpdateBytesFromRawSignals(DB_NM_RCM_HS_CAN * pMsg)
{
    uint64 nRawValues[7];

    DB_NM_RCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_RCM_HS_CAN_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_IPC_HS_CAN_Index = 87;

void DB_NM_IPC_HS_CAN_Init(DB_NM_IPC_HS_CAN * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_IPC_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->IPC_NMDataField = dValues[0];
    pMsg->IPC_NMSleepAck = dValues[1];
    pMsg->IPC_NMSleepInd = dValues[2];
    pMsg->IPC_NMLimphome = dValues[3];
    pMsg->IPC_NMRing = dValues[4];
    pMsg->IPC_NMAlive = dValues[5];
    pMsg->IPC_NMDestAddress = dValues[6];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->IPC_NMDataField_raw = (uint64)nRawValues[0];
    pMsg->IPC_NMSleepAck_raw = (BYTE)nRawValues[1];
    pMsg->IPC_NMSleepInd_raw = (BYTE)nRawValues[2];
    pMsg->IPC_NMLimphome_raw = (BYTE)nRawValues[3];
    pMsg->IPC_NMRing_raw = (BYTE)nRawValues[4];
    pMsg->IPC_NMAlive_raw = (BYTE)nRawValues[5];
    pMsg->IPC_NMDestAddress_raw = (BYTE)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_IPC_HS_CAN_LoadSignalValuesArray(DB_NM_IPC_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->IPC_NMDataField;
    dArray[1] = pMsg->IPC_NMSleepAck;
    dArray[2] = pMsg->IPC_NMSleepInd;
    dArray[3] = pMsg->IPC_NMLimphome;
    dArray[4] = pMsg->IPC_NMRing;
    dArray[5] = pMsg->IPC_NMAlive;
    dArray[6] = pMsg->IPC_NMDestAddress;
}

void DB_NM_IPC_HS_CAN_LoadRawSignalValuesArray(DB_NM_IPC_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->IPC_NMDataField_raw;
    nRawValues[1] = pMsg->IPC_NMSleepAck_raw;
    nRawValues[2] = pMsg->IPC_NMSleepInd_raw;
    nRawValues[3] = pMsg->IPC_NMLimphome_raw;
    nRawValues[4] = pMsg->IPC_NMRing_raw;
    nRawValues[5] = pMsg->IPC_NMAlive_raw;
    nRawValues[6] = pMsg->IPC_NMDestAddress_raw;
}

int DB_NM_IPC_HS_CAN_Transmit(DB_NM_IPC_HS_CAN * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_IPC_HS_CAN_Init(pMsg);
    }

    DB_NM_IPC_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int DB_NM_IPC_HS_CAN_Transmit_raw(DB_NM_IPC_HS_CAN * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_IPC_HS_CAN_Init(pMsg);
    }

    DB_NM_IPC_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int DB_NM_IPC_HS_CAN_UpdateBytesFromSignals(DB_NM_IPC_HS_CAN * pMsg)
{
    double dArray[7];

    DB_NM_IPC_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_IPC_HS_CAN_UpdateBytesFromRawSignals(DB_NM_IPC_HS_CAN * pMsg)
{
    uint64 nRawValues[7];

    DB_NM_IPC_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_IPC_HS_CAN_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_AC_HS_CAN_db88_Index = 88;

void DB_NM_AC_HS_CAN_db88_Init(DB_NM_AC_HS_CAN_db88 * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_AC_HS_CAN_db88_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->AC_NMDataField = dValues[0];
    pMsg->AC_NMSleepAck = dValues[1];
    pMsg->AC_NMSleepInd = dValues[2];
    pMsg->AC_NMLimphome = dValues[3];
    pMsg->AC_NMRing = dValues[4];
    pMsg->AC_NMAlive = dValues[5];
    pMsg->AC_NMDestAddress = dValues[6];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->AC_NMDataField_raw = (uint64)nRawValues[0];
    pMsg->AC_NMSleepAck_raw = (BYTE)nRawValues[1];
    pMsg->AC_NMSleepInd_raw = (BYTE)nRawValues[2];
    pMsg->AC_NMLimphome_raw = (BYTE)nRawValues[3];
    pMsg->AC_NMRing_raw = (BYTE)nRawValues[4];
    pMsg->AC_NMAlive_raw = (BYTE)nRawValues[5];
    pMsg->AC_NMDestAddress_raw = (BYTE)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_AC_HS_CAN_db88_LoadSignalValuesArray(DB_NM_AC_HS_CAN_db88 * pMsg, double *dArray)
{
    dArray[0] = pMsg->AC_NMDataField;
    dArray[1] = pMsg->AC_NMSleepAck;
    dArray[2] = pMsg->AC_NMSleepInd;
    dArray[3] = pMsg->AC_NMLimphome;
    dArray[4] = pMsg->AC_NMRing;
    dArray[5] = pMsg->AC_NMAlive;
    dArray[6] = pMsg->AC_NMDestAddress;
}

void DB_NM_AC_HS_CAN_db88_LoadRawSignalValuesArray(DB_NM_AC_HS_CAN_db88 * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->AC_NMDataField_raw;
    nRawValues[1] = pMsg->AC_NMSleepAck_raw;
    nRawValues[2] = pMsg->AC_NMSleepInd_raw;
    nRawValues[3] = pMsg->AC_NMLimphome_raw;
    nRawValues[4] = pMsg->AC_NMRing_raw;
    nRawValues[5] = pMsg->AC_NMAlive_raw;
    nRawValues[6] = pMsg->AC_NMDestAddress_raw;
}

int DB_NM_AC_HS_CAN_db88_Transmit(DB_NM_AC_HS_CAN_db88 * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_AC_HS_CAN_db88_Init(pMsg);
    }

    DB_NM_AC_HS_CAN_db88_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int DB_NM_AC_HS_CAN_db88_Transmit_raw(DB_NM_AC_HS_CAN_db88 * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_AC_HS_CAN_db88_Init(pMsg);
    }

    DB_NM_AC_HS_CAN_db88_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int DB_NM_AC_HS_CAN_db88_UpdateBytesFromSignals(DB_NM_AC_HS_CAN_db88 * pMsg)
{
    double dArray[7];

    DB_NM_AC_HS_CAN_db88_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_AC_HS_CAN_db88_UpdateBytesFromRawSignals(DB_NM_AC_HS_CAN_db88 * pMsg)
{
    uint64 nRawValues[7];

    DB_NM_AC_HS_CAN_db88_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_AC_HS_CAN_db88_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_Tester_HS_CAN_Index = 89;

void DB_Tester_HS_CAN_Init(DB_Tester_HS_CAN * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_Tester_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Resv6 = dValues[0];
    pMsg->Resv5 = dValues[1];
    pMsg->Resv4 = dValues[2];
    pMsg->Resv3 = dValues[3];
    pMsg->Resv2 = dValues[4];
    pMsg->FD = dValues[5];
    pMsg->Ctrl = dValues[6];
    pMsg->Resv1 = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_Tester_HS_CAN_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->Resv6_raw = (BYTE)nRawValues[0];
    pMsg->Resv5_raw = (BYTE)nRawValues[1];
    pMsg->Resv4_raw = (BYTE)nRawValues[2];
    pMsg->Resv3_raw = (BYTE)nRawValues[3];
    pMsg->Resv2_raw = (BYTE)nRawValues[4];
    pMsg->FD_raw = (BYTE)nRawValues[5];
    pMsg->Ctrl_raw = (BYTE)nRawValues[6];
    pMsg->Resv1_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_Tester_HS_CAN_LoadSignalValuesArray(DB_Tester_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->Resv6;
    dArray[1] = pMsg->Resv5;
    dArray[2] = pMsg->Resv4;
    dArray[3] = pMsg->Resv3;
    dArray[4] = pMsg->Resv2;
    dArray[5] = pMsg->FD;
    dArray[6] = pMsg->Ctrl;
    dArray[7] = pMsg->Resv1;
}

void DB_Tester_HS_CAN_LoadRawSignalValuesArray(DB_Tester_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Resv6_raw;
    nRawValues[1] = pMsg->Resv5_raw;
    nRawValues[2] = pMsg->Resv4_raw;
    nRawValues[3] = pMsg->Resv3_raw;
    nRawValues[4] = pMsg->Resv2_raw;
    nRawValues[5] = pMsg->FD_raw;
    nRawValues[6] = pMsg->Ctrl_raw;
    nRawValues[7] = pMsg->Resv1_raw;
}

int DB_Tester_HS_CAN_Transmit(DB_Tester_HS_CAN * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Tester_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Tester_HS_CAN_Init(pMsg);
    }

    DB_Tester_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_Tester_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_Tester_HS_CAN_Transmit_raw(DB_Tester_HS_CAN * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_Tester_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_Tester_HS_CAN_Init(pMsg);
    }

    DB_Tester_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_Tester_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_Tester_HS_CAN_UpdateBytesFromSignals(DB_Tester_HS_CAN * pMsg)
{
    double dArray[8];

    DB_Tester_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_Tester_HS_CAN_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_Tester_HS_CAN_UpdateBytesFromRawSignals(DB_Tester_HS_CAN * pMsg)
{
    uint64 nRawValues[8];

    DB_Tester_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_Tester_HS_CAN_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_EVM_HS_CAN_Index = 90;

void DB_NM_EVM_HS_CAN_Init(DB_NM_EVM_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_EVM_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->EVM_NM_Sleep_Ack = dValues[0];
    pMsg->EVM_NM_Sleep_Ind = dValues[1];
    pMsg->EVM_NM_Limphome = dValues[2];
    pMsg->EVM_NM_Ring = dValues[3];
    pMsg->EVM_NM_Alive = dValues[4];
    pMsg->EVM_NM_DA = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->EVM_NM_Sleep_Ack_raw = (BYTE)nRawValues[0];
    pMsg->EVM_NM_Sleep_Ind_raw = (BYTE)nRawValues[1];
    pMsg->EVM_NM_Limphome_raw = (BYTE)nRawValues[2];
    pMsg->EVM_NM_Ring_raw = (BYTE)nRawValues[3];
    pMsg->EVM_NM_Alive_raw = (BYTE)nRawValues[4];
    pMsg->EVM_NM_DA_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_EVM_HS_CAN_LoadSignalValuesArray(DB_NM_EVM_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->EVM_NM_Sleep_Ack;
    dArray[1] = pMsg->EVM_NM_Sleep_Ind;
    dArray[2] = pMsg->EVM_NM_Limphome;
    dArray[3] = pMsg->EVM_NM_Ring;
    dArray[4] = pMsg->EVM_NM_Alive;
    dArray[5] = pMsg->EVM_NM_DA;
}

void DB_NM_EVM_HS_CAN_LoadRawSignalValuesArray(DB_NM_EVM_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->EVM_NM_Sleep_Ack_raw;
    nRawValues[1] = pMsg->EVM_NM_Sleep_Ind_raw;
    nRawValues[2] = pMsg->EVM_NM_Limphome_raw;
    nRawValues[3] = pMsg->EVM_NM_Ring_raw;
    nRawValues[4] = pMsg->EVM_NM_Alive_raw;
    nRawValues[5] = pMsg->EVM_NM_DA_raw;
}

int DB_NM_EVM_HS_CAN_Transmit(DB_NM_EVM_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_EVM_HS_CAN_Init(pMsg);
    }

    DB_NM_EVM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_NM_EVM_HS_CAN_Transmit_raw(DB_NM_EVM_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_EVM_HS_CAN_Init(pMsg);
    }

    DB_NM_EVM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_NM_EVM_HS_CAN_UpdateBytesFromSignals(DB_NM_EVM_HS_CAN * pMsg)
{
    double dArray[6];

    DB_NM_EVM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_EVM_HS_CAN_UpdateBytesFromRawSignals(DB_NM_EVM_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_NM_EVM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_EVM_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_DM1_EVM_HS_CAN_Index = 91;

void DB_DM1_EVM_HS_CAN_Init(DB_DM1_EVM_HS_CAN * pMsg)
{
    double dValues[9] = {0.0};
    uint64 nRawValues[9] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_DM1_EVM_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 9, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->SPN_Mode = dValues[0];
    pMsg->OccuranceCount = dValues[1];
    pMsg->SPN_HighBit = dValues[2];
    pMsg->FMI = dValues[3];
    pMsg->SPN_Num = dValues[4];
    pMsg->MalfunctionIndicatorLamp = dValues[5];
    pMsg->RedStopLamp = dValues[6];
    pMsg->AmberWarningLamp = dValues[7];
    pMsg->ProtectLamp = dValues[8];
    CM_MessageRawInit(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, nRawValues, 9, &iActualSignalMaxCount);
    pMsg->SPN_Mode_raw = (BYTE)nRawValues[0];
    pMsg->OccuranceCount_raw = (BYTE)nRawValues[1];
    pMsg->SPN_HighBit_raw = (BYTE)nRawValues[2];
    pMsg->FMI_raw = (BYTE)nRawValues[3];
    pMsg->SPN_Num_raw = (WORD)nRawValues[4];
    pMsg->MalfunctionIndicatorLamp_raw = (BYTE)nRawValues[5];
    pMsg->RedStopLamp_raw = (BYTE)nRawValues[6];
    pMsg->AmberWarningLamp_raw = (BYTE)nRawValues[7];
    pMsg->ProtectLamp_raw = (BYTE)nRawValues[8];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_DM1_EVM_HS_CAN_LoadSignalValuesArray(DB_DM1_EVM_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->SPN_Mode;
    dArray[1] = pMsg->OccuranceCount;
    dArray[2] = pMsg->SPN_HighBit;
    dArray[3] = pMsg->FMI;
    dArray[4] = pMsg->SPN_Num;
    dArray[5] = pMsg->MalfunctionIndicatorLamp;
    dArray[6] = pMsg->RedStopLamp;
    dArray[7] = pMsg->AmberWarningLamp;
    dArray[8] = pMsg->ProtectLamp;
}

void DB_DM1_EVM_HS_CAN_LoadRawSignalValuesArray(DB_DM1_EVM_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->SPN_Mode_raw;
    nRawValues[1] = pMsg->OccuranceCount_raw;
    nRawValues[2] = pMsg->SPN_HighBit_raw;
    nRawValues[3] = pMsg->FMI_raw;
    nRawValues[4] = pMsg->SPN_Num_raw;
    nRawValues[5] = pMsg->MalfunctionIndicatorLamp_raw;
    nRawValues[6] = pMsg->RedStopLamp_raw;
    nRawValues[7] = pMsg->AmberWarningLamp_raw;
    nRawValues[8] = pMsg->ProtectLamp_raw;
}

int DB_DM1_EVM_HS_CAN_Transmit(DB_DM1_EVM_HS_CAN * pMsg)
{
    double dArray[9];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DM1_EVM_HS_CAN_Init(pMsg);
    }

    DB_DM1_EVM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 9);
}

int DB_DM1_EVM_HS_CAN_Transmit_raw(DB_DM1_EVM_HS_CAN * pMsg)
{
    uint64 nRawValues[9];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DM1_EVM_HS_CAN_Init(pMsg);
    }

    DB_DM1_EVM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 9);
}

int DB_DM1_EVM_HS_CAN_UpdateBytesFromSignals(DB_DM1_EVM_HS_CAN * pMsg)
{
    double dArray[9];

    DB_DM1_EVM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, dArray, 9, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_DM1_EVM_HS_CAN_UpdateBytesFromRawSignals(DB_DM1_EVM_HS_CAN * pMsg)
{
    uint64 nRawValues[9];

    DB_DM1_EVM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_DM1_EVM_HS_CAN_Index, nRawValues, 9, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_EVM1_HS_CAN_Index = 92;

void DB_EVM1_HS_CAN_Init(DB_EVM1_HS_CAN * pMsg)
{
    double dValues[7] = {0.0};
    uint64 nRawValues[7] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_EVM1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 7, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->RadarWarringLevel = dValues[0];
    pMsg->RightDoublingWarring = dValues[1];
    pMsg->LeftDoublingWarring = dValues[2];
    pMsg->RightVehicleBackWarring = dValues[3];
    pMsg->LeftVehicleBackWarring = dValues[4];
    pMsg->Channel2ndVideoAngle_MMI = dValues[5];
    pMsg->Channel2ndVideoSource_MMI = dValues[6];
    CM_MessageRawInit(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, nRawValues, 7, &iActualSignalMaxCount);
    pMsg->RadarWarringLevel_raw = (BYTE)nRawValues[0];
    pMsg->RightDoublingWarring_raw = (BYTE)nRawValues[1];
    pMsg->LeftDoublingWarring_raw = (BYTE)nRawValues[2];
    pMsg->RightVehicleBackWarring_raw = (BYTE)nRawValues[3];
    pMsg->LeftVehicleBackWarring_raw = (BYTE)nRawValues[4];
    pMsg->Channel2ndVideoAngle_MMI_raw = (BYTE)nRawValues[5];
    pMsg->Channel2ndVideoSource_MMI_raw = (BYTE)nRawValues[6];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_EVM1_HS_CAN_LoadSignalValuesArray(DB_EVM1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->RadarWarringLevel;
    dArray[1] = pMsg->RightDoublingWarring;
    dArray[2] = pMsg->LeftDoublingWarring;
    dArray[3] = pMsg->RightVehicleBackWarring;
    dArray[4] = pMsg->LeftVehicleBackWarring;
    dArray[5] = pMsg->Channel2ndVideoAngle_MMI;
    dArray[6] = pMsg->Channel2ndVideoSource_MMI;
}

void DB_EVM1_HS_CAN_LoadRawSignalValuesArray(DB_EVM1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->RadarWarringLevel_raw;
    nRawValues[1] = pMsg->RightDoublingWarring_raw;
    nRawValues[2] = pMsg->LeftDoublingWarring_raw;
    nRawValues[3] = pMsg->RightVehicleBackWarring_raw;
    nRawValues[4] = pMsg->LeftVehicleBackWarring_raw;
    nRawValues[5] = pMsg->Channel2ndVideoAngle_MMI_raw;
    nRawValues[6] = pMsg->Channel2ndVideoSource_MMI_raw;
}

int DB_EVM1_HS_CAN_Transmit(DB_EVM1_HS_CAN * pMsg)
{
    double dArray[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_EVM1_HS_CAN_Init(pMsg);
    }

    DB_EVM1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 7);
}

int DB_EVM1_HS_CAN_Transmit_raw(DB_EVM1_HS_CAN * pMsg)
{
    uint64 nRawValues[7];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_EVM1_HS_CAN_Init(pMsg);
    }

    DB_EVM1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 7);
}

int DB_EVM1_HS_CAN_UpdateBytesFromSignals(DB_EVM1_HS_CAN * pMsg)
{
    double dArray[7];

    DB_EVM1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, dArray, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_EVM1_HS_CAN_UpdateBytesFromRawSignals(DB_EVM1_HS_CAN * pMsg)
{
    uint64 nRawValues[7];

    DB_EVM1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_EVM1_HS_CAN_Index, nRawValues, 7, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_TXJ_HS_CAN_Index = 93;

void DB_NM_TXJ_HS_CAN_Init(DB_NM_TXJ_HS_CAN * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_TXJ_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TXJ_NM_Sleep_Ack = dValues[0];
    pMsg->TXJ_NM_Sleep_Ind = dValues[1];
    pMsg->TXJ_NM_Limphome = dValues[2];
    pMsg->TXJ_NM_Ring = dValues[3];
    pMsg->TXJ_NM_Alive = dValues[4];
    pMsg->TXJ_NM_DA = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->TXJ_NM_Sleep_Ack_raw = (BYTE)nRawValues[0];
    pMsg->TXJ_NM_Sleep_Ind_raw = (BYTE)nRawValues[1];
    pMsg->TXJ_NM_Limphome_raw = (BYTE)nRawValues[2];
    pMsg->TXJ_NM_Ring_raw = (BYTE)nRawValues[3];
    pMsg->TXJ_NM_Alive_raw = (BYTE)nRawValues[4];
    pMsg->TXJ_NM_DA_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_TXJ_HS_CAN_LoadSignalValuesArray(DB_NM_TXJ_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TXJ_NM_Sleep_Ack;
    dArray[1] = pMsg->TXJ_NM_Sleep_Ind;
    dArray[2] = pMsg->TXJ_NM_Limphome;
    dArray[3] = pMsg->TXJ_NM_Ring;
    dArray[4] = pMsg->TXJ_NM_Alive;
    dArray[5] = pMsg->TXJ_NM_DA;
}

void DB_NM_TXJ_HS_CAN_LoadRawSignalValuesArray(DB_NM_TXJ_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TXJ_NM_Sleep_Ack_raw;
    nRawValues[1] = pMsg->TXJ_NM_Sleep_Ind_raw;
    nRawValues[2] = pMsg->TXJ_NM_Limphome_raw;
    nRawValues[3] = pMsg->TXJ_NM_Ring_raw;
    nRawValues[4] = pMsg->TXJ_NM_Alive_raw;
    nRawValues[5] = pMsg->TXJ_NM_DA_raw;
}

int DB_NM_TXJ_HS_CAN_Transmit(DB_NM_TXJ_HS_CAN * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_TXJ_HS_CAN_Init(pMsg);
    }

    DB_NM_TXJ_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_NM_TXJ_HS_CAN_Transmit_raw(DB_NM_TXJ_HS_CAN * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_TXJ_HS_CAN_Init(pMsg);
    }

    DB_NM_TXJ_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_NM_TXJ_HS_CAN_UpdateBytesFromSignals(DB_NM_TXJ_HS_CAN * pMsg)
{
    double dArray[6];

    DB_NM_TXJ_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_TXJ_HS_CAN_UpdateBytesFromRawSignals(DB_NM_TXJ_HS_CAN * pMsg)
{
    uint64 nRawValues[6];

    DB_NM_TXJ_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_TXJ_HS_CAN_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_DM1_TXJ_HS_CAN_Index = 94;

void DB_DM1_TXJ_HS_CAN_Init(DB_DM1_TXJ_HS_CAN * pMsg)
{
    double dValues[9] = {0.0};
    uint64 nRawValues[9] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_DM1_TXJ_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 9, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->SPN_Mode = dValues[0];
    pMsg->OccuranceCount = dValues[1];
    pMsg->SPN_HighBit = dValues[2];
    pMsg->FMI = dValues[3];
    pMsg->RedStopLamp = dValues[4];
    pMsg->SPN_Num = dValues[5];
    pMsg->MalfunctionIndicatorLamp = dValues[6];
    pMsg->AmberWarningLamp = dValues[7];
    pMsg->ProtectLamp = dValues[8];
    CM_MessageRawInit(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, nRawValues, 9, &iActualSignalMaxCount);
    pMsg->SPN_Mode_raw = (BYTE)nRawValues[0];
    pMsg->OccuranceCount_raw = (BYTE)nRawValues[1];
    pMsg->SPN_HighBit_raw = (BYTE)nRawValues[2];
    pMsg->FMI_raw = (BYTE)nRawValues[3];
    pMsg->RedStopLamp_raw = (BYTE)nRawValues[4];
    pMsg->SPN_Num_raw = (WORD)nRawValues[5];
    pMsg->MalfunctionIndicatorLamp_raw = (BYTE)nRawValues[6];
    pMsg->AmberWarningLamp_raw = (BYTE)nRawValues[7];
    pMsg->ProtectLamp_raw = (BYTE)nRawValues[8];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_DM1_TXJ_HS_CAN_LoadSignalValuesArray(DB_DM1_TXJ_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->SPN_Mode;
    dArray[1] = pMsg->OccuranceCount;
    dArray[2] = pMsg->SPN_HighBit;
    dArray[3] = pMsg->FMI;
    dArray[4] = pMsg->RedStopLamp;
    dArray[5] = pMsg->SPN_Num;
    dArray[6] = pMsg->MalfunctionIndicatorLamp;
    dArray[7] = pMsg->AmberWarningLamp;
    dArray[8] = pMsg->ProtectLamp;
}

void DB_DM1_TXJ_HS_CAN_LoadRawSignalValuesArray(DB_DM1_TXJ_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->SPN_Mode_raw;
    nRawValues[1] = pMsg->OccuranceCount_raw;
    nRawValues[2] = pMsg->SPN_HighBit_raw;
    nRawValues[3] = pMsg->FMI_raw;
    nRawValues[4] = pMsg->RedStopLamp_raw;
    nRawValues[5] = pMsg->SPN_Num_raw;
    nRawValues[6] = pMsg->MalfunctionIndicatorLamp_raw;
    nRawValues[7] = pMsg->AmberWarningLamp_raw;
    nRawValues[8] = pMsg->ProtectLamp_raw;
}

int DB_DM1_TXJ_HS_CAN_Transmit(DB_DM1_TXJ_HS_CAN * pMsg)
{
    double dArray[9];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DM1_TXJ_HS_CAN_Init(pMsg);
    }

    DB_DM1_TXJ_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 9);
}

int DB_DM1_TXJ_HS_CAN_Transmit_raw(DB_DM1_TXJ_HS_CAN * pMsg)
{
    uint64 nRawValues[9];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DM1_TXJ_HS_CAN_Init(pMsg);
    }

    DB_DM1_TXJ_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 9);
}

int DB_DM1_TXJ_HS_CAN_UpdateBytesFromSignals(DB_DM1_TXJ_HS_CAN * pMsg)
{
    double dArray[9];

    DB_DM1_TXJ_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, dArray, 9, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_DM1_TXJ_HS_CAN_UpdateBytesFromRawSignals(DB_DM1_TXJ_HS_CAN * pMsg)
{
    uint64 nRawValues[9];

    DB_DM1_TXJ_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_DM1_TXJ_HS_CAN_Index, nRawValues, 9, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_VehicleCtr_HS_CAN_db95_Index = 95;

void DB_VehicleCtr_HS_CAN_db95_Init(DB_VehicleCtr_HS_CAN_db95 * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VehicleCtr_HS_CAN_db95_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TXJ_SwitchAuxIn = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_db95_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->TXJ_SwitchAuxIn_raw = (BYTE)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_VehicleCtr_HS_CAN_db95_LoadSignalValuesArray(DB_VehicleCtr_HS_CAN_db95 * pMsg, double *dArray)
{
    dArray[0] = pMsg->TXJ_SwitchAuxIn;
}

void DB_VehicleCtr_HS_CAN_db95_LoadRawSignalValuesArray(DB_VehicleCtr_HS_CAN_db95 * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TXJ_SwitchAuxIn_raw;
}

int DB_VehicleCtr_HS_CAN_db95_Transmit(DB_VehicleCtr_HS_CAN_db95 * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_db95_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VehicleCtr_HS_CAN_db95_Init(pMsg);
    }

    DB_VehicleCtr_HS_CAN_db95_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_db95_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_VehicleCtr_HS_CAN_db95_Transmit_raw(DB_VehicleCtr_HS_CAN_db95 * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_db95_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VehicleCtr_HS_CAN_db95_Init(pMsg);
    }

    DB_VehicleCtr_HS_CAN_db95_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_db95_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_VehicleCtr_HS_CAN_db95_UpdateBytesFromSignals(DB_VehicleCtr_HS_CAN_db95 * pMsg)
{
    double dArray[1];

    DB_VehicleCtr_HS_CAN_db95_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_db95_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_VehicleCtr_HS_CAN_db95_UpdateBytesFromRawSignals(DB_VehicleCtr_HS_CAN_db95 * pMsg)
{
    uint64 nRawValues[1];

    DB_VehicleCtr_HS_CAN_db95_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_VehicleCtr_HS_CAN_db95_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_VDS_HS_CAN_Index = 96;

void DB_VDS_HS_CAN_Init(DB_VDS_HS_CAN * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_VDS_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Altitude = dValues[0];
    pMsg->Pitch = dValues[1];
    pMsg->NavigationBasedVehicleSpeed = dValues[2];
    pMsg->CompassBearing = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_VDS_HS_CAN_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->Altitude_raw = (WORD)nRawValues[0];
    pMsg->Pitch_raw = (WORD)nRawValues[1];
    pMsg->NavigationBasedVehicleSpeed_raw = (WORD)nRawValues[2];
    pMsg->CompassBearing_raw = (WORD)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_VDS_HS_CAN_LoadSignalValuesArray(DB_VDS_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->Altitude;
    dArray[1] = pMsg->Pitch;
    dArray[2] = pMsg->NavigationBasedVehicleSpeed;
    dArray[3] = pMsg->CompassBearing;
}

void DB_VDS_HS_CAN_LoadRawSignalValuesArray(DB_VDS_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Altitude_raw;
    nRawValues[1] = pMsg->Pitch_raw;
    nRawValues[2] = pMsg->NavigationBasedVehicleSpeed_raw;
    nRawValues[3] = pMsg->CompassBearing_raw;
}

int DB_VDS_HS_CAN_Transmit(DB_VDS_HS_CAN * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VDS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VDS_HS_CAN_Init(pMsg);
    }

    DB_VDS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_VDS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_VDS_HS_CAN_Transmit_raw(DB_VDS_HS_CAN * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_VDS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_VDS_HS_CAN_Init(pMsg);
    }

    DB_VDS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_VDS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_VDS_HS_CAN_UpdateBytesFromSignals(DB_VDS_HS_CAN * pMsg)
{
    double dArray[4];

    DB_VDS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_VDS_HS_CAN_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_VDS_HS_CAN_UpdateBytesFromRawSignals(DB_VDS_HS_CAN * pMsg)
{
    uint64 nRawValues[4];

    DB_VDS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_VDS_HS_CAN_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_GPS_Item_HS_CAN_Index = 97;

void DB_GPS_Item_HS_CAN_Init(DB_GPS_Item_HS_CAN * pMsg)
{
    double dValues[4] = {0.0};
    uint64 nRawValues[4] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_GPS_Item_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 4, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->BD_SatelliteCounts = dValues[0];
    pMsg->GPS_SatelliteCounts = dValues[1];
    pMsg->GPS_Precision = dValues[2];
    pMsg->GPS_Item = dValues[3];
    CM_MessageRawInit(g_uiHandle, 0, DB_GPS_Item_HS_CAN_Index, nRawValues, 4, &iActualSignalMaxCount);
    pMsg->BD_SatelliteCounts_raw = (BYTE)nRawValues[0];
    pMsg->GPS_SatelliteCounts_raw = (BYTE)nRawValues[1];
    pMsg->GPS_Precision_raw = (BYTE)nRawValues[2];
    pMsg->GPS_Item_raw = (BYTE)nRawValues[3];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_GPS_Item_HS_CAN_LoadSignalValuesArray(DB_GPS_Item_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->BD_SatelliteCounts;
    dArray[1] = pMsg->GPS_SatelliteCounts;
    dArray[2] = pMsg->GPS_Precision;
    dArray[3] = pMsg->GPS_Item;
}

void DB_GPS_Item_HS_CAN_LoadRawSignalValuesArray(DB_GPS_Item_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->BD_SatelliteCounts_raw;
    nRawValues[1] = pMsg->GPS_SatelliteCounts_raw;
    nRawValues[2] = pMsg->GPS_Precision_raw;
    nRawValues[3] = pMsg->GPS_Item_raw;
}

int DB_GPS_Item_HS_CAN_Transmit(DB_GPS_Item_HS_CAN * pMsg)
{
    double dArray[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_GPS_Item_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_GPS_Item_HS_CAN_Init(pMsg);
    }

    DB_GPS_Item_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_GPS_Item_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 4);
}

int DB_GPS_Item_HS_CAN_Transmit_raw(DB_GPS_Item_HS_CAN * pMsg)
{
    uint64 nRawValues[4];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_GPS_Item_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_GPS_Item_HS_CAN_Init(pMsg);
    }

    DB_GPS_Item_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_GPS_Item_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 4);
}

int DB_GPS_Item_HS_CAN_UpdateBytesFromSignals(DB_GPS_Item_HS_CAN * pMsg)
{
    double dArray[4];

    DB_GPS_Item_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_GPS_Item_HS_CAN_Index, dArray, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_GPS_Item_HS_CAN_UpdateBytesFromRawSignals(DB_GPS_Item_HS_CAN * pMsg)
{
    uint64 nRawValues[4];

    DB_GPS_Item_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_GPS_Item_HS_CAN_Index, nRawValues, 4, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_PositionGPS_HS_CAN_Index = 98;

void DB_PositionGPS_HS_CAN_Init(DB_PositionGPS_HS_CAN * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_PositionGPS_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Longitude = dValues[0];
    pMsg->Latitude = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_PositionGPS_HS_CAN_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->Longitude_raw = (DWORD)nRawValues[0];
    pMsg->Latitude_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_PositionGPS_HS_CAN_LoadSignalValuesArray(DB_PositionGPS_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->Longitude;
    dArray[1] = pMsg->Latitude;
}

void DB_PositionGPS_HS_CAN_LoadRawSignalValuesArray(DB_PositionGPS_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Longitude_raw;
    nRawValues[1] = pMsg->Latitude_raw;
}

int DB_PositionGPS_HS_CAN_Transmit(DB_PositionGPS_HS_CAN * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_PositionGPS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_PositionGPS_HS_CAN_Init(pMsg);
    }

    DB_PositionGPS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_PositionGPS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_PositionGPS_HS_CAN_Transmit_raw(DB_PositionGPS_HS_CAN * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_PositionGPS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_PositionGPS_HS_CAN_Init(pMsg);
    }

    DB_PositionGPS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_PositionGPS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_PositionGPS_HS_CAN_UpdateBytesFromSignals(DB_PositionGPS_HS_CAN * pMsg)
{
    double dArray[2];

    DB_PositionGPS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_PositionGPS_HS_CAN_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_PositionGPS_HS_CAN_UpdateBytesFromRawSignals(DB_PositionGPS_HS_CAN * pMsg)
{
    uint64 nRawValues[2];

    DB_PositionGPS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_PositionGPS_HS_CAN_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_TD_HS_CAN_Index = 99;

void DB_TD_HS_CAN_Init(DB_TD_HS_CAN * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_TD_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->LocalHourOffset = dValues[0];
    pMsg->LocalMinuteOffset = dValues[1];
    pMsg->Year = dValues[2];
    pMsg->Day = dValues[3];
    pMsg->Month = dValues[4];
    pMsg->Hours = dValues[5];
    pMsg->Second = dValues[6];
    pMsg->Minutes = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_TD_HS_CAN_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->LocalHourOffset_raw = (BYTE)nRawValues[0];
    pMsg->LocalMinuteOffset_raw = (BYTE)nRawValues[1];
    pMsg->Year_raw = (BYTE)nRawValues[2];
    pMsg->Day_raw = (BYTE)nRawValues[3];
    pMsg->Month_raw = (BYTE)nRawValues[4];
    pMsg->Hours_raw = (BYTE)nRawValues[5];
    pMsg->Second_raw = (BYTE)nRawValues[6];
    pMsg->Minutes_raw = (BYTE)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_TD_HS_CAN_LoadSignalValuesArray(DB_TD_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->LocalHourOffset;
    dArray[1] = pMsg->LocalMinuteOffset;
    dArray[2] = pMsg->Year;
    dArray[3] = pMsg->Day;
    dArray[4] = pMsg->Month;
    dArray[5] = pMsg->Hours;
    dArray[6] = pMsg->Second;
    dArray[7] = pMsg->Minutes;
}

void DB_TD_HS_CAN_LoadRawSignalValuesArray(DB_TD_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->LocalHourOffset_raw;
    nRawValues[1] = pMsg->LocalMinuteOffset_raw;
    nRawValues[2] = pMsg->Year_raw;
    nRawValues[3] = pMsg->Day_raw;
    nRawValues[4] = pMsg->Month_raw;
    nRawValues[5] = pMsg->Hours_raw;
    nRawValues[6] = pMsg->Second_raw;
    nRawValues[7] = pMsg->Minutes_raw;
}

int DB_TD_HS_CAN_Transmit(DB_TD_HS_CAN * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_TD_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_TD_HS_CAN_Init(pMsg);
    }

    DB_TD_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_TD_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_TD_HS_CAN_Transmit_raw(DB_TD_HS_CAN * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_TD_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_TD_HS_CAN_Init(pMsg);
    }

    DB_TD_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_TD_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_TD_HS_CAN_UpdateBytesFromSignals(DB_TD_HS_CAN * pMsg)
{
    double dArray[8];

    DB_TD_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_TD_HS_CAN_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_TD_HS_CAN_UpdateBytesFromRawSignals(DB_TD_HS_CAN * pMsg)
{
    uint64 nRawValues[8];

    DB_TD_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_TD_HS_CAN_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_TXJxMMI_HS_CAN_Index = 100;

void DB_TXJxMMI_HS_CAN_Init(DB_TXJxMMI_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_TXJxMMI_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TXJ_MMI = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_TXJxMMI_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->TXJ_MMI_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_TXJxMMI_HS_CAN_LoadSignalValuesArray(DB_TXJxMMI_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TXJ_MMI;
}

void DB_TXJxMMI_HS_CAN_LoadRawSignalValuesArray(DB_TXJxMMI_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TXJ_MMI_raw;
}

int DB_TXJxMMI_HS_CAN_Transmit(DB_TXJxMMI_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_TXJxMMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_TXJxMMI_HS_CAN_Init(pMsg);
    }

    DB_TXJxMMI_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_TXJxMMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_TXJxMMI_HS_CAN_Transmit_raw(DB_TXJxMMI_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_TXJxMMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_TXJxMMI_HS_CAN_Init(pMsg);
    }

    DB_TXJxMMI_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_TXJxMMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_TXJxMMI_HS_CAN_UpdateBytesFromSignals(DB_TXJxMMI_HS_CAN * pMsg)
{
    double dArray[1];

    DB_TXJxMMI_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_TXJxMMI_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_TXJxMMI_HS_CAN_UpdateBytesFromRawSignals(DB_TXJxMMI_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_TXJxMMI_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_TXJxMMI_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_TCO1_HS_CAN_db101_Index = 101;

void DB_TCO1_HS_CAN_db101_Init(DB_TCO1_HS_CAN_db101 * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_TCO1_HS_CAN_db101_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TachographVehiclespeed = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_TCO1_HS_CAN_db101_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->TachographVehiclespeed_raw = (WORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_TCO1_HS_CAN_db101_LoadSignalValuesArray(DB_TCO1_HS_CAN_db101 * pMsg, double *dArray)
{
    dArray[0] = pMsg->TachographVehiclespeed;
}

void DB_TCO1_HS_CAN_db101_LoadRawSignalValuesArray(DB_TCO1_HS_CAN_db101 * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TachographVehiclespeed_raw;
}

int DB_TCO1_HS_CAN_db101_Transmit(DB_TCO1_HS_CAN_db101 * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_TCO1_HS_CAN_db101_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_TCO1_HS_CAN_db101_Init(pMsg);
    }

    DB_TCO1_HS_CAN_db101_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_TCO1_HS_CAN_db101_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_TCO1_HS_CAN_db101_Transmit_raw(DB_TCO1_HS_CAN_db101 * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_TCO1_HS_CAN_db101_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_TCO1_HS_CAN_db101_Init(pMsg);
    }

    DB_TCO1_HS_CAN_db101_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_TCO1_HS_CAN_db101_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_TCO1_HS_CAN_db101_UpdateBytesFromSignals(DB_TCO1_HS_CAN_db101 * pMsg)
{
    double dArray[1];

    DB_TCO1_HS_CAN_db101_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_TCO1_HS_CAN_db101_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_TCO1_HS_CAN_db101_UpdateBytesFromRawSignals(DB_TCO1_HS_CAN_db101 * pMsg)
{
    uint64 nRawValues[1];

    DB_TCO1_HS_CAN_db101_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_TCO1_HS_CAN_db101_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_MMI_HS_CAN_db102_Index = 102;

void DB_NM_MMI_HS_CAN_db102_Init(DB_NM_MMI_HS_CAN_db102 * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_MMI_HS_CAN_db102_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->MMI_NM_Sleep_Ack = dValues[0];
    pMsg->MMI_NM_Sleep_Ind = dValues[1];
    pMsg->MMI_NM_Limphome = dValues[2];
    pMsg->MMI_NM_Ring = dValues[3];
    pMsg->MMI_NM_Alive = dValues[4];
    pMsg->MMI_NM_DA = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->MMI_NM_Sleep_Ack_raw = (BYTE)nRawValues[0];
    pMsg->MMI_NM_Sleep_Ind_raw = (BYTE)nRawValues[1];
    pMsg->MMI_NM_Limphome_raw = (BYTE)nRawValues[2];
    pMsg->MMI_NM_Ring_raw = (BYTE)nRawValues[3];
    pMsg->MMI_NM_Alive_raw = (BYTE)nRawValues[4];
    pMsg->MMI_NM_DA_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_MMI_HS_CAN_db102_LoadSignalValuesArray(DB_NM_MMI_HS_CAN_db102 * pMsg, double *dArray)
{
    dArray[0] = pMsg->MMI_NM_Sleep_Ack;
    dArray[1] = pMsg->MMI_NM_Sleep_Ind;
    dArray[2] = pMsg->MMI_NM_Limphome;
    dArray[3] = pMsg->MMI_NM_Ring;
    dArray[4] = pMsg->MMI_NM_Alive;
    dArray[5] = pMsg->MMI_NM_DA;
}

void DB_NM_MMI_HS_CAN_db102_LoadRawSignalValuesArray(DB_NM_MMI_HS_CAN_db102 * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->MMI_NM_Sleep_Ack_raw;
    nRawValues[1] = pMsg->MMI_NM_Sleep_Ind_raw;
    nRawValues[2] = pMsg->MMI_NM_Limphome_raw;
    nRawValues[3] = pMsg->MMI_NM_Ring_raw;
    nRawValues[4] = pMsg->MMI_NM_Alive_raw;
    nRawValues[5] = pMsg->MMI_NM_DA_raw;
}

int DB_NM_MMI_HS_CAN_db102_Transmit(DB_NM_MMI_HS_CAN_db102 * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_MMI_HS_CAN_db102_Init(pMsg);
    }

    DB_NM_MMI_HS_CAN_db102_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_NM_MMI_HS_CAN_db102_Transmit_raw(DB_NM_MMI_HS_CAN_db102 * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_MMI_HS_CAN_db102_Init(pMsg);
    }

    DB_NM_MMI_HS_CAN_db102_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_NM_MMI_HS_CAN_db102_UpdateBytesFromSignals(DB_NM_MMI_HS_CAN_db102 * pMsg)
{
    double dArray[6];

    DB_NM_MMI_HS_CAN_db102_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_MMI_HS_CAN_db102_UpdateBytesFromRawSignals(DB_NM_MMI_HS_CAN_db102 * pMsg)
{
    uint64 nRawValues[6];

    DB_NM_MMI_HS_CAN_db102_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_MMI_HS_CAN_db102_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_DM1_MMI_HS_CAN_Index = 103;

void DB_DM1_MMI_HS_CAN_Init(DB_DM1_MMI_HS_CAN * pMsg)
{
    double dValues[9] = {0.0};
    uint64 nRawValues[9] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_DM1_MMI_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 9, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->SPN_Mode = dValues[0];
    pMsg->OccuranceCount = dValues[1];
    pMsg->SPN_HighBit = dValues[2];
    pMsg->FMI = dValues[3];
    pMsg->SPN_Num = dValues[4];
    pMsg->MalfunctionIndicatorLamp = dValues[5];
    pMsg->AmberWarningLamp = dValues[6];
    pMsg->RedStopLamp = dValues[7];
    pMsg->ProtectLamp = dValues[8];
    CM_MessageRawInit(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, nRawValues, 9, &iActualSignalMaxCount);
    pMsg->SPN_Mode_raw = (BYTE)nRawValues[0];
    pMsg->OccuranceCount_raw = (BYTE)nRawValues[1];
    pMsg->SPN_HighBit_raw = (BYTE)nRawValues[2];
    pMsg->FMI_raw = (BYTE)nRawValues[3];
    pMsg->SPN_Num_raw = (WORD)nRawValues[4];
    pMsg->MalfunctionIndicatorLamp_raw = (BYTE)nRawValues[5];
    pMsg->AmberWarningLamp_raw = (BYTE)nRawValues[6];
    pMsg->RedStopLamp_raw = (BYTE)nRawValues[7];
    pMsg->ProtectLamp_raw = (BYTE)nRawValues[8];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_DM1_MMI_HS_CAN_LoadSignalValuesArray(DB_DM1_MMI_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->SPN_Mode;
    dArray[1] = pMsg->OccuranceCount;
    dArray[2] = pMsg->SPN_HighBit;
    dArray[3] = pMsg->FMI;
    dArray[4] = pMsg->SPN_Num;
    dArray[5] = pMsg->MalfunctionIndicatorLamp;
    dArray[6] = pMsg->AmberWarningLamp;
    dArray[7] = pMsg->RedStopLamp;
    dArray[8] = pMsg->ProtectLamp;
}

void DB_DM1_MMI_HS_CAN_LoadRawSignalValuesArray(DB_DM1_MMI_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->SPN_Mode_raw;
    nRawValues[1] = pMsg->OccuranceCount_raw;
    nRawValues[2] = pMsg->SPN_HighBit_raw;
    nRawValues[3] = pMsg->FMI_raw;
    nRawValues[4] = pMsg->SPN_Num_raw;
    nRawValues[5] = pMsg->MalfunctionIndicatorLamp_raw;
    nRawValues[6] = pMsg->AmberWarningLamp_raw;
    nRawValues[7] = pMsg->RedStopLamp_raw;
    nRawValues[8] = pMsg->ProtectLamp_raw;
}

int DB_DM1_MMI_HS_CAN_Transmit(DB_DM1_MMI_HS_CAN * pMsg)
{
    double dArray[9];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DM1_MMI_HS_CAN_Init(pMsg);
    }

    DB_DM1_MMI_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 9);
}

int DB_DM1_MMI_HS_CAN_Transmit_raw(DB_DM1_MMI_HS_CAN * pMsg)
{
    uint64 nRawValues[9];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DM1_MMI_HS_CAN_Init(pMsg);
    }

    DB_DM1_MMI_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 9);
}

int DB_DM1_MMI_HS_CAN_UpdateBytesFromSignals(DB_DM1_MMI_HS_CAN * pMsg)
{
    double dArray[9];

    DB_DM1_MMI_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, dArray, 9, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_DM1_MMI_HS_CAN_UpdateBytesFromRawSignals(DB_DM1_MMI_HS_CAN * pMsg)
{
    uint64 nRawValues[9];

    DB_DM1_MMI_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_DM1_MMI_HS_CAN_Index, nRawValues, 9, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_MMI_CtrDCM_HS_CAN_Index = 104;

void DB_MMI_CtrDCM_HS_CAN_Init(DB_MMI_CtrDCM_HS_CAN * pMsg)
{
    double dValues[10] = {0.0};
    uint64 nRawValues[10] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_MMI_CtrDCM_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 10, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->BackOfSeatHypsokinesisPos = dValues[0];
    pMsg->SeatHypsokinesisPos = dValues[1];
    pMsg->MMI_Mem_Restore = dValues[2];
    pMsg->SeatHorizonPos = dValues[3];
    pMsg->M_MarkCmd = dValues[4];
    pMsg->SeatVerticalPos = dValues[5];
    pMsg->RightRearMirVerticalAngle = dValues[6];
    pMsg->LeftRearMirVerticalAngle = dValues[7];
    pMsg->RightRearMirHorizontalAngle = dValues[8];
    pMsg->LeftRearMirHorizontalAngle = dValues[9];
    CM_MessageRawInit(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, nRawValues, 10, &iActualSignalMaxCount);
    pMsg->BackOfSeatHypsokinesisPos_raw = (BYTE)nRawValues[0];
    pMsg->SeatHypsokinesisPos_raw = (BYTE)nRawValues[1];
    pMsg->MMI_Mem_Restore_raw = (BYTE)nRawValues[2];
    pMsg->SeatHorizonPos_raw = (BYTE)nRawValues[3];
    pMsg->M_MarkCmd_raw = (BYTE)nRawValues[4];
    pMsg->SeatVerticalPos_raw = (BYTE)nRawValues[5];
    pMsg->RightRearMirVerticalAngle_raw = (BYTE)nRawValues[6];
    pMsg->LeftRearMirVerticalAngle_raw = (BYTE)nRawValues[7];
    pMsg->RightRearMirHorizontalAngle_raw = (BYTE)nRawValues[8];
    pMsg->LeftRearMirHorizontalAngle_raw = (BYTE)nRawValues[9];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_MMI_CtrDCM_HS_CAN_LoadSignalValuesArray(DB_MMI_CtrDCM_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->BackOfSeatHypsokinesisPos;
    dArray[1] = pMsg->SeatHypsokinesisPos;
    dArray[2] = pMsg->MMI_Mem_Restore;
    dArray[3] = pMsg->SeatHorizonPos;
    dArray[4] = pMsg->M_MarkCmd;
    dArray[5] = pMsg->SeatVerticalPos;
    dArray[6] = pMsg->RightRearMirVerticalAngle;
    dArray[7] = pMsg->LeftRearMirVerticalAngle;
    dArray[8] = pMsg->RightRearMirHorizontalAngle;
    dArray[9] = pMsg->LeftRearMirHorizontalAngle;
}

void DB_MMI_CtrDCM_HS_CAN_LoadRawSignalValuesArray(DB_MMI_CtrDCM_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->BackOfSeatHypsokinesisPos_raw;
    nRawValues[1] = pMsg->SeatHypsokinesisPos_raw;
    nRawValues[2] = pMsg->MMI_Mem_Restore_raw;
    nRawValues[3] = pMsg->SeatHorizonPos_raw;
    nRawValues[4] = pMsg->M_MarkCmd_raw;
    nRawValues[5] = pMsg->SeatVerticalPos_raw;
    nRawValues[6] = pMsg->RightRearMirVerticalAngle_raw;
    nRawValues[7] = pMsg->LeftRearMirVerticalAngle_raw;
    nRawValues[8] = pMsg->RightRearMirHorizontalAngle_raw;
    nRawValues[9] = pMsg->LeftRearMirHorizontalAngle_raw;
}

int DB_MMI_CtrDCM_HS_CAN_Transmit(DB_MMI_CtrDCM_HS_CAN * pMsg)
{
    double dArray[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMI_CtrDCM_HS_CAN_Init(pMsg);
    }

    DB_MMI_CtrDCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 10);
}

int DB_MMI_CtrDCM_HS_CAN_Transmit_raw(DB_MMI_CtrDCM_HS_CAN * pMsg)
{
    uint64 nRawValues[10];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMI_CtrDCM_HS_CAN_Init(pMsg);
    }

    DB_MMI_CtrDCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 10);
}

int DB_MMI_CtrDCM_HS_CAN_UpdateBytesFromSignals(DB_MMI_CtrDCM_HS_CAN * pMsg)
{
    double dArray[10];

    DB_MMI_CtrDCM_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, dArray, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_MMI_CtrDCM_HS_CAN_UpdateBytesFromRawSignals(DB_MMI_CtrDCM_HS_CAN * pMsg)
{
    uint64 nRawValues[10];

    DB_MMI_CtrDCM_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_MMI_CtrDCM_HS_CAN_Index, nRawValues, 10, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_MMIctrCab_HS_CAN_db105_Index = 105;

void DB_MMIctrCab_HS_CAN_db105_Init(DB_MMIctrCab_HS_CAN_db105 * pMsg)
{
    double dValues[18] = {0.0};
    uint64 nRawValues[18] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_MMIctrCab_HS_CAN_db105_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 18, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->BackOfSeatHypsokinesisForward = dValues[0];
    pMsg->BackOfSeatHypsokinesisBackward = dValues[1];
    pMsg->SeatHypsokinesisForward = dValues[2];
    pMsg->SeatHypsokinesisBackward = dValues[3];
    pMsg->SeatHorizonBackward = dValues[4];
    pMsg->SeatHorizonForward = dValues[5];
    pMsg->SeatVerticalDown = dValues[6];
    pMsg->SeatVerticalUp = dValues[7];
    pMsg->MMIctrDrLockOpen = dValues[8];
    pMsg->LKAS_SW = dValues[9];
    pMsg->RoofPositionCtr = dValues[10];
    pMsg->RoofWorkCmd = dValues[11];
    pMsg->MMIctrLBmOpn = dValues[12];
    pMsg->MMIctrLBmCls = dValues[13];
    pMsg->MMIctrFLgOpn = dValues[14];
    pMsg->MMIctrFLgCls = dValues[15];
    pMsg->MMIctrDrWdOpn = dValues[16];
    pMsg->MMIctrDrWdCls = dValues[17];
    CM_MessageRawInit(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, nRawValues, 18, &iActualSignalMaxCount);
    pMsg->BackOfSeatHypsokinesisForward_raw = (BYTE)nRawValues[0];
    pMsg->BackOfSeatHypsokinesisBackward_raw = (BYTE)nRawValues[1];
    pMsg->SeatHypsokinesisForward_raw = (BYTE)nRawValues[2];
    pMsg->SeatHypsokinesisBackward_raw = (BYTE)nRawValues[3];
    pMsg->SeatHorizonBackward_raw = (BYTE)nRawValues[4];
    pMsg->SeatHorizonForward_raw = (BYTE)nRawValues[5];
    pMsg->SeatVerticalDown_raw = (BYTE)nRawValues[6];
    pMsg->SeatVerticalUp_raw = (BYTE)nRawValues[7];
    pMsg->MMIctrDrLockOpen_raw = (BYTE)nRawValues[8];
    pMsg->LKAS_SW_raw = (BYTE)nRawValues[9];
    pMsg->RoofPositionCtr_raw = (BYTE)nRawValues[10];
    pMsg->RoofWorkCmd_raw = (BYTE)nRawValues[11];
    pMsg->MMIctrLBmOpn_raw = (BYTE)nRawValues[12];
    pMsg->MMIctrLBmCls_raw = (BYTE)nRawValues[13];
    pMsg->MMIctrFLgOpn_raw = (BYTE)nRawValues[14];
    pMsg->MMIctrFLgCls_raw = (BYTE)nRawValues[15];
    pMsg->MMIctrDrWdOpn_raw = (BYTE)nRawValues[16];
    pMsg->MMIctrDrWdCls_raw = (BYTE)nRawValues[17];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_MMIctrCab_HS_CAN_db105_LoadSignalValuesArray(DB_MMIctrCab_HS_CAN_db105 * pMsg, double *dArray)
{
    dArray[0] = pMsg->BackOfSeatHypsokinesisForward;
    dArray[1] = pMsg->BackOfSeatHypsokinesisBackward;
    dArray[2] = pMsg->SeatHypsokinesisForward;
    dArray[3] = pMsg->SeatHypsokinesisBackward;
    dArray[4] = pMsg->SeatHorizonBackward;
    dArray[5] = pMsg->SeatHorizonForward;
    dArray[6] = pMsg->SeatVerticalDown;
    dArray[7] = pMsg->SeatVerticalUp;
    dArray[8] = pMsg->MMIctrDrLockOpen;
    dArray[9] = pMsg->LKAS_SW;
    dArray[10] = pMsg->RoofPositionCtr;
    dArray[11] = pMsg->RoofWorkCmd;
    dArray[12] = pMsg->MMIctrLBmOpn;
    dArray[13] = pMsg->MMIctrLBmCls;
    dArray[14] = pMsg->MMIctrFLgOpn;
    dArray[15] = pMsg->MMIctrFLgCls;
    dArray[16] = pMsg->MMIctrDrWdOpn;
    dArray[17] = pMsg->MMIctrDrWdCls;
}

void DB_MMIctrCab_HS_CAN_db105_LoadRawSignalValuesArray(DB_MMIctrCab_HS_CAN_db105 * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->BackOfSeatHypsokinesisForward_raw;
    nRawValues[1] = pMsg->BackOfSeatHypsokinesisBackward_raw;
    nRawValues[2] = pMsg->SeatHypsokinesisForward_raw;
    nRawValues[3] = pMsg->SeatHypsokinesisBackward_raw;
    nRawValues[4] = pMsg->SeatHorizonBackward_raw;
    nRawValues[5] = pMsg->SeatHorizonForward_raw;
    nRawValues[6] = pMsg->SeatVerticalDown_raw;
    nRawValues[7] = pMsg->SeatVerticalUp_raw;
    nRawValues[8] = pMsg->MMIctrDrLockOpen_raw;
    nRawValues[9] = pMsg->LKAS_SW_raw;
    nRawValues[10] = pMsg->RoofPositionCtr_raw;
    nRawValues[11] = pMsg->RoofWorkCmd_raw;
    nRawValues[12] = pMsg->MMIctrLBmOpn_raw;
    nRawValues[13] = pMsg->MMIctrLBmCls_raw;
    nRawValues[14] = pMsg->MMIctrFLgOpn_raw;
    nRawValues[15] = pMsg->MMIctrFLgCls_raw;
    nRawValues[16] = pMsg->MMIctrDrWdOpn_raw;
    nRawValues[17] = pMsg->MMIctrDrWdCls_raw;
}

int DB_MMIctrCab_HS_CAN_db105_Transmit(DB_MMIctrCab_HS_CAN_db105 * pMsg)
{
    double dArray[18];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMIctrCab_HS_CAN_db105_Init(pMsg);
    }

    DB_MMIctrCab_HS_CAN_db105_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 18);
}

int DB_MMIctrCab_HS_CAN_db105_Transmit_raw(DB_MMIctrCab_HS_CAN_db105 * pMsg)
{
    uint64 nRawValues[18];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMIctrCab_HS_CAN_db105_Init(pMsg);
    }

    DB_MMIctrCab_HS_CAN_db105_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 18);
}

int DB_MMIctrCab_HS_CAN_db105_UpdateBytesFromSignals(DB_MMIctrCab_HS_CAN_db105 * pMsg)
{
    double dArray[18];

    DB_MMIctrCab_HS_CAN_db105_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, dArray, 18, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_MMIctrCab_HS_CAN_db105_UpdateBytesFromRawSignals(DB_MMIctrCab_HS_CAN_db105 * pMsg)
{
    uint64 nRawValues[18];

    DB_MMIctrCab_HS_CAN_db105_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_MMIctrCab_HS_CAN_db105_Index, nRawValues, 18, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_MMI_NAV_HS_CAN_Index = 106;

void DB_MMI_NAV_HS_CAN_Init(DB_MMI_NAV_HS_CAN * pMsg)
{
    double dValues[8] = {0.0};
    uint64 nRawValues[8] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_MMI_NAV_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 8, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->NAV_PhWaringDistce = dValues[0];
    pMsg->NAV_PhWaring = dValues[1];
    pMsg->NAV_TurnWaringDistce = dValues[2];
    pMsg->NAV_TurnWaring = dValues[3];
    pMsg->NAV_DesDistce = dValues[4];
    pMsg->NAV_SpeedLitDistce = dValues[5];
    pMsg->NAV_SpeedLit = dValues[6];
    pMsg->CompassBearing = dValues[7];
    CM_MessageRawInit(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, nRawValues, 8, &iActualSignalMaxCount);
    pMsg->NAV_PhWaringDistce_raw = (BYTE)nRawValues[0];
    pMsg->NAV_PhWaring_raw = (BYTE)nRawValues[1];
    pMsg->NAV_TurnWaringDistce_raw = (BYTE)nRawValues[2];
    pMsg->NAV_TurnWaring_raw = (BYTE)nRawValues[3];
    pMsg->NAV_DesDistce_raw = (DWORD)nRawValues[4];
    pMsg->NAV_SpeedLitDistce_raw = (BYTE)nRawValues[5];
    pMsg->NAV_SpeedLit_raw = (BYTE)nRawValues[6];
    pMsg->CompassBearing_raw = (WORD)nRawValues[7];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_MMI_NAV_HS_CAN_LoadSignalValuesArray(DB_MMI_NAV_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->NAV_PhWaringDistce;
    dArray[1] = pMsg->NAV_PhWaring;
    dArray[2] = pMsg->NAV_TurnWaringDistce;
    dArray[3] = pMsg->NAV_TurnWaring;
    dArray[4] = pMsg->NAV_DesDistce;
    dArray[5] = pMsg->NAV_SpeedLitDistce;
    dArray[6] = pMsg->NAV_SpeedLit;
    dArray[7] = pMsg->CompassBearing;
}

void DB_MMI_NAV_HS_CAN_LoadRawSignalValuesArray(DB_MMI_NAV_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->NAV_PhWaringDistce_raw;
    nRawValues[1] = pMsg->NAV_PhWaring_raw;
    nRawValues[2] = pMsg->NAV_TurnWaringDistce_raw;
    nRawValues[3] = pMsg->NAV_TurnWaring_raw;
    nRawValues[4] = pMsg->NAV_DesDistce_raw;
    nRawValues[5] = pMsg->NAV_SpeedLitDistce_raw;
    nRawValues[6] = pMsg->NAV_SpeedLit_raw;
    nRawValues[7] = pMsg->CompassBearing_raw;
}

int DB_MMI_NAV_HS_CAN_Transmit(DB_MMI_NAV_HS_CAN * pMsg)
{
    double dArray[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMI_NAV_HS_CAN_Init(pMsg);
    }

    DB_MMI_NAV_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 8);
}

int DB_MMI_NAV_HS_CAN_Transmit_raw(DB_MMI_NAV_HS_CAN * pMsg)
{
    uint64 nRawValues[8];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMI_NAV_HS_CAN_Init(pMsg);
    }

    DB_MMI_NAV_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 8);
}

int DB_MMI_NAV_HS_CAN_UpdateBytesFromSignals(DB_MMI_NAV_HS_CAN * pMsg)
{
    double dArray[8];

    DB_MMI_NAV_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, dArray, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_MMI_NAV_HS_CAN_UpdateBytesFromRawSignals(DB_MMI_NAV_HS_CAN * pMsg)
{
    uint64 nRawValues[8];

    DB_MMI_NAV_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_MMI_NAV_HS_CAN_Index, nRawValues, 8, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_MMI_XY_HS_CAN_Index = 107;

void DB_MMI_XY_HS_CAN_Init(DB_MMI_XY_HS_CAN * pMsg)
{
    double dValues[3] = {0.0};
    uint64 nRawValues[3] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_MMI_XY_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 3, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->TouchState = dValues[0];
    pMsg->TouchPosition_Y = dValues[1];
    pMsg->TouchPosition_X = dValues[2];
    CM_MessageRawInit(g_uiHandle, 0, DB_MMI_XY_HS_CAN_Index, nRawValues, 3, &iActualSignalMaxCount);
    pMsg->TouchState_raw = (BYTE)nRawValues[0];
    pMsg->TouchPosition_Y_raw = (WORD)nRawValues[1];
    pMsg->TouchPosition_X_raw = (WORD)nRawValues[2];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_MMI_XY_HS_CAN_LoadSignalValuesArray(DB_MMI_XY_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->TouchState;
    dArray[1] = pMsg->TouchPosition_Y;
    dArray[2] = pMsg->TouchPosition_X;
}

void DB_MMI_XY_HS_CAN_LoadRawSignalValuesArray(DB_MMI_XY_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->TouchState_raw;
    nRawValues[1] = pMsg->TouchPosition_Y_raw;
    nRawValues[2] = pMsg->TouchPosition_X_raw;
}

int DB_MMI_XY_HS_CAN_Transmit(DB_MMI_XY_HS_CAN * pMsg)
{
    double dArray[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMI_XY_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMI_XY_HS_CAN_Init(pMsg);
    }

    DB_MMI_XY_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_MMI_XY_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 3);
}

int DB_MMI_XY_HS_CAN_Transmit_raw(DB_MMI_XY_HS_CAN * pMsg)
{
    uint64 nRawValues[3];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMI_XY_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMI_XY_HS_CAN_Init(pMsg);
    }

    DB_MMI_XY_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_MMI_XY_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 3);
}

int DB_MMI_XY_HS_CAN_UpdateBytesFromSignals(DB_MMI_XY_HS_CAN * pMsg)
{
    double dArray[3];

    DB_MMI_XY_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_MMI_XY_HS_CAN_Index, dArray, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_MMI_XY_HS_CAN_UpdateBytesFromRawSignals(DB_MMI_XY_HS_CAN * pMsg)
{
    uint64 nRawValues[3];

    DB_MMI_XY_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_MMI_XY_HS_CAN_Index, nRawValues, 3, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_MMIxTXJ_HS_CAN_Index = 108;

void DB_MMIxTXJ_HS_CAN_Init(DB_MMIxTXJ_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_MMIxTXJ_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->MMI_TXJ = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_MMIxTXJ_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->MMI_TXJ_raw = (uint64)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_MMIxTXJ_HS_CAN_LoadSignalValuesArray(DB_MMIxTXJ_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->MMI_TXJ;
}

void DB_MMIxTXJ_HS_CAN_LoadRawSignalValuesArray(DB_MMIxTXJ_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->MMI_TXJ_raw;
}

int DB_MMIxTXJ_HS_CAN_Transmit(DB_MMIxTXJ_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMIxTXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMIxTXJ_HS_CAN_Init(pMsg);
    }

    DB_MMIxTXJ_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_MMIxTXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_MMIxTXJ_HS_CAN_Transmit_raw(DB_MMIxTXJ_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMIxTXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMIxTXJ_HS_CAN_Init(pMsg);
    }

    DB_MMIxTXJ_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_MMIxTXJ_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_MMIxTXJ_HS_CAN_UpdateBytesFromSignals(DB_MMIxTXJ_HS_CAN * pMsg)
{
    double dArray[1];

    DB_MMIxTXJ_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_MMIxTXJ_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_MMIxTXJ_HS_CAN_UpdateBytesFromRawSignals(DB_MMIxTXJ_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_MMIxTXJ_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_MMIxTXJ_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_MMI2_HS_CAN_Index = 109;

void DB_MMI2_HS_CAN_Init(DB_MMI2_HS_CAN * pMsg)
{
    double dValues[16] = {0.0};
    uint64 nRawValues[16] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_MMI2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 16, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->PhoneNum_12 = dValues[0];
    pMsg->PhoneNum_11 = dValues[1];
    pMsg->PhoneNum_10 = dValues[2];
    pMsg->PhoneNum_9 = dValues[3];
    pMsg->PhoneNum_8 = dValues[4];
    pMsg->PhoneNum_7 = dValues[5];
    pMsg->PhoneNum_6 = dValues[6];
    pMsg->PhoneNum_5 = dValues[7];
    pMsg->PhoneNum_4 = dValues[8];
    pMsg->PhoneNum_3 = dValues[9];
    pMsg->PhoneNum_2 = dValues[10];
    pMsg->PhoneNum_1 = dValues[11];
    pMsg->PhoneNumInternational_4 = dValues[12];
    pMsg->PhoneNumInternational_3 = dValues[13];
    pMsg->PhoneNumInternational_2 = dValues[14];
    pMsg->PhoneNumInternational_1 = dValues[15];
    CM_MessageRawInit(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, nRawValues, 16, &iActualSignalMaxCount);
    pMsg->PhoneNum_12_raw = (BYTE)nRawValues[0];
    pMsg->PhoneNum_11_raw = (BYTE)nRawValues[1];
    pMsg->PhoneNum_10_raw = (BYTE)nRawValues[2];
    pMsg->PhoneNum_9_raw = (BYTE)nRawValues[3];
    pMsg->PhoneNum_8_raw = (BYTE)nRawValues[4];
    pMsg->PhoneNum_7_raw = (BYTE)nRawValues[5];
    pMsg->PhoneNum_6_raw = (BYTE)nRawValues[6];
    pMsg->PhoneNum_5_raw = (BYTE)nRawValues[7];
    pMsg->PhoneNum_4_raw = (BYTE)nRawValues[8];
    pMsg->PhoneNum_3_raw = (BYTE)nRawValues[9];
    pMsg->PhoneNum_2_raw = (BYTE)nRawValues[10];
    pMsg->PhoneNum_1_raw = (BYTE)nRawValues[11];
    pMsg->PhoneNumInternational_4_raw = (BYTE)nRawValues[12];
    pMsg->PhoneNumInternational_3_raw = (BYTE)nRawValues[13];
    pMsg->PhoneNumInternational_2_raw = (BYTE)nRawValues[14];
    pMsg->PhoneNumInternational_1_raw = (BYTE)nRawValues[15];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_MMI2_HS_CAN_LoadSignalValuesArray(DB_MMI2_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->PhoneNum_12;
    dArray[1] = pMsg->PhoneNum_11;
    dArray[2] = pMsg->PhoneNum_10;
    dArray[3] = pMsg->PhoneNum_9;
    dArray[4] = pMsg->PhoneNum_8;
    dArray[5] = pMsg->PhoneNum_7;
    dArray[6] = pMsg->PhoneNum_6;
    dArray[7] = pMsg->PhoneNum_5;
    dArray[8] = pMsg->PhoneNum_4;
    dArray[9] = pMsg->PhoneNum_3;
    dArray[10] = pMsg->PhoneNum_2;
    dArray[11] = pMsg->PhoneNum_1;
    dArray[12] = pMsg->PhoneNumInternational_4;
    dArray[13] = pMsg->PhoneNumInternational_3;
    dArray[14] = pMsg->PhoneNumInternational_2;
    dArray[15] = pMsg->PhoneNumInternational_1;
}

void DB_MMI2_HS_CAN_LoadRawSignalValuesArray(DB_MMI2_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->PhoneNum_12_raw;
    nRawValues[1] = pMsg->PhoneNum_11_raw;
    nRawValues[2] = pMsg->PhoneNum_10_raw;
    nRawValues[3] = pMsg->PhoneNum_9_raw;
    nRawValues[4] = pMsg->PhoneNum_8_raw;
    nRawValues[5] = pMsg->PhoneNum_7_raw;
    nRawValues[6] = pMsg->PhoneNum_6_raw;
    nRawValues[7] = pMsg->PhoneNum_5_raw;
    nRawValues[8] = pMsg->PhoneNum_4_raw;
    nRawValues[9] = pMsg->PhoneNum_3_raw;
    nRawValues[10] = pMsg->PhoneNum_2_raw;
    nRawValues[11] = pMsg->PhoneNum_1_raw;
    nRawValues[12] = pMsg->PhoneNumInternational_4_raw;
    nRawValues[13] = pMsg->PhoneNumInternational_3_raw;
    nRawValues[14] = pMsg->PhoneNumInternational_2_raw;
    nRawValues[15] = pMsg->PhoneNumInternational_1_raw;
}

int DB_MMI2_HS_CAN_Transmit(DB_MMI2_HS_CAN * pMsg)
{
    double dArray[16];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMI2_HS_CAN_Init(pMsg);
    }

    DB_MMI2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 16);
}

int DB_MMI2_HS_CAN_Transmit_raw(DB_MMI2_HS_CAN * pMsg)
{
    uint64 nRawValues[16];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMI2_HS_CAN_Init(pMsg);
    }

    DB_MMI2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 16);
}

int DB_MMI2_HS_CAN_UpdateBytesFromSignals(DB_MMI2_HS_CAN * pMsg)
{
    double dArray[16];

    DB_MMI2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, dArray, 16, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_MMI2_HS_CAN_UpdateBytesFromRawSignals(DB_MMI2_HS_CAN * pMsg)
{
    uint64 nRawValues[16];

    DB_MMI2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_MMI2_HS_CAN_Index, nRawValues, 16, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_MMI1_HS_CAN_Index = 110;

void DB_MMI1_HS_CAN_Init(DB_MMI1_HS_CAN * pMsg)
{
    double dValues[12] = {0.0};
    uint64 nRawValues[12] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_MMI1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 12, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->BlowingRateGareSet = dValues[0];
    pMsg->OutAirModSetCmd = dValues[1];
    pMsg->TempSetCmd = dValues[2];
    pMsg->VideoVolume = dValues[3];
    pMsg->Channel2ndVideoSourceChoose = dValues[4];
    pMsg->Channel2ndVideoAngleChoose = dValues[5];
    pMsg->FMRadioChannel = dValues[6];
    pMsg->AMRadioChannel = dValues[7];
    pMsg->InletAirModSteCmd = dValues[8];
    pMsg->FMAMSt = dValues[9];
    pMsg->CalingSt = dValues[10];
    pMsg->AuidoPlaySt = dValues[11];
    CM_MessageRawInit(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, nRawValues, 12, &iActualSignalMaxCount);
    pMsg->BlowingRateGareSet_raw = (BYTE)nRawValues[0];
    pMsg->OutAirModSetCmd_raw = (BYTE)nRawValues[1];
    pMsg->TempSetCmd_raw = (BYTE)nRawValues[2];
    pMsg->VideoVolume_raw = (BYTE)nRawValues[3];
    pMsg->Channel2ndVideoSourceChoose_raw = (BYTE)nRawValues[4];
    pMsg->Channel2ndVideoAngleChoose_raw = (BYTE)nRawValues[5];
    pMsg->FMRadioChannel_raw = (BYTE)nRawValues[6];
    pMsg->AMRadioChannel_raw = (BYTE)nRawValues[7];
    pMsg->InletAirModSteCmd_raw = (BYTE)nRawValues[8];
    pMsg->FMAMSt_raw = (BYTE)nRawValues[9];
    pMsg->CalingSt_raw = (BYTE)nRawValues[10];
    pMsg->AuidoPlaySt_raw = (BYTE)nRawValues[11];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_MMI1_HS_CAN_LoadSignalValuesArray(DB_MMI1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->BlowingRateGareSet;
    dArray[1] = pMsg->OutAirModSetCmd;
    dArray[2] = pMsg->TempSetCmd;
    dArray[3] = pMsg->VideoVolume;
    dArray[4] = pMsg->Channel2ndVideoSourceChoose;
    dArray[5] = pMsg->Channel2ndVideoAngleChoose;
    dArray[6] = pMsg->FMRadioChannel;
    dArray[7] = pMsg->AMRadioChannel;
    dArray[8] = pMsg->InletAirModSteCmd;
    dArray[9] = pMsg->FMAMSt;
    dArray[10] = pMsg->CalingSt;
    dArray[11] = pMsg->AuidoPlaySt;
}

void DB_MMI1_HS_CAN_LoadRawSignalValuesArray(DB_MMI1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->BlowingRateGareSet_raw;
    nRawValues[1] = pMsg->OutAirModSetCmd_raw;
    nRawValues[2] = pMsg->TempSetCmd_raw;
    nRawValues[3] = pMsg->VideoVolume_raw;
    nRawValues[4] = pMsg->Channel2ndVideoSourceChoose_raw;
    nRawValues[5] = pMsg->Channel2ndVideoAngleChoose_raw;
    nRawValues[6] = pMsg->FMRadioChannel_raw;
    nRawValues[7] = pMsg->AMRadioChannel_raw;
    nRawValues[8] = pMsg->InletAirModSteCmd_raw;
    nRawValues[9] = pMsg->FMAMSt_raw;
    nRawValues[10] = pMsg->CalingSt_raw;
    nRawValues[11] = pMsg->AuidoPlaySt_raw;
}

int DB_MMI1_HS_CAN_Transmit(DB_MMI1_HS_CAN * pMsg)
{
    double dArray[12];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMI1_HS_CAN_Init(pMsg);
    }

    DB_MMI1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 12);
}

int DB_MMI1_HS_CAN_Transmit_raw(DB_MMI1_HS_CAN * pMsg)
{
    uint64 nRawValues[12];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_MMI1_HS_CAN_Init(pMsg);
    }

    DB_MMI1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 12);
}

int DB_MMI1_HS_CAN_UpdateBytesFromSignals(DB_MMI1_HS_CAN * pMsg)
{
    double dArray[12];

    DB_MMI1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, dArray, 12, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_MMI1_HS_CAN_UpdateBytesFromRawSignals(DB_MMI1_HS_CAN * pMsg)
{
    uint64 nRawValues[12];

    DB_MMI1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_MMI1_HS_CAN_Index, nRawValues, 12, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_NM_GW_HS_CAN_db111_Index = 111;

void DB_NM_GW_HS_CAN_db111_Init(DB_NM_GW_HS_CAN_db111 * pMsg)
{
    double dValues[6] = {0.0};
    uint64 nRawValues[6] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_NM_GW_HS_CAN_db111_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 6, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->GW_NM_Steep_Ind = dValues[0];
    pMsg->GW_NM_Sleep_Ack = dValues[1];
    pMsg->GW_NM_Ring = dValues[2];
    pMsg->GW_NM_Limphone = dValues[3];
    pMsg->GW_NM_DA = dValues[4];
    pMsg->GW_NM_Alive = dValues[5];
    CM_MessageRawInit(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, nRawValues, 6, &iActualSignalMaxCount);
    pMsg->GW_NM_Steep_Ind_raw = (BYTE)nRawValues[0];
    pMsg->GW_NM_Sleep_Ack_raw = (BYTE)nRawValues[1];
    pMsg->GW_NM_Ring_raw = (BYTE)nRawValues[2];
    pMsg->GW_NM_Limphone_raw = (BYTE)nRawValues[3];
    pMsg->GW_NM_DA_raw = (BYTE)nRawValues[4];
    pMsg->GW_NM_Alive_raw = (BYTE)nRawValues[5];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_NM_GW_HS_CAN_db111_LoadSignalValuesArray(DB_NM_GW_HS_CAN_db111 * pMsg, double *dArray)
{
    dArray[0] = pMsg->GW_NM_Steep_Ind;
    dArray[1] = pMsg->GW_NM_Sleep_Ack;
    dArray[2] = pMsg->GW_NM_Ring;
    dArray[3] = pMsg->GW_NM_Limphone;
    dArray[4] = pMsg->GW_NM_DA;
    dArray[5] = pMsg->GW_NM_Alive;
}

void DB_NM_GW_HS_CAN_db111_LoadRawSignalValuesArray(DB_NM_GW_HS_CAN_db111 * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->GW_NM_Steep_Ind_raw;
    nRawValues[1] = pMsg->GW_NM_Sleep_Ack_raw;
    nRawValues[2] = pMsg->GW_NM_Ring_raw;
    nRawValues[3] = pMsg->GW_NM_Limphone_raw;
    nRawValues[4] = pMsg->GW_NM_DA_raw;
    nRawValues[5] = pMsg->GW_NM_Alive_raw;
}

int DB_NM_GW_HS_CAN_db111_Transmit(DB_NM_GW_HS_CAN_db111 * pMsg)
{
    double dArray[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_GW_HS_CAN_db111_Init(pMsg);
    }

    DB_NM_GW_HS_CAN_db111_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 6);
}

int DB_NM_GW_HS_CAN_db111_Transmit_raw(DB_NM_GW_HS_CAN_db111 * pMsg)
{
    uint64 nRawValues[6];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_NM_GW_HS_CAN_db111_Init(pMsg);
    }

    DB_NM_GW_HS_CAN_db111_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 6);
}

int DB_NM_GW_HS_CAN_db111_UpdateBytesFromSignals(DB_NM_GW_HS_CAN_db111 * pMsg)
{
    double dArray[6];

    DB_NM_GW_HS_CAN_db111_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, dArray, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_NM_GW_HS_CAN_db111_UpdateBytesFromRawSignals(DB_NM_GW_HS_CAN_db111 * pMsg)
{
    uint64 nRawValues[6];

    DB_NM_GW_HS_CAN_db111_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_NM_GW_HS_CAN_db111_Index, nRawValues, 6, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_DMI_GW_HS_CAN_Index = 112;

void DB_DMI_GW_HS_CAN_Init(DB_DMI_GW_HS_CAN * pMsg)
{
    double dValues[9] = {0.0};
    uint64 nRawValues[9] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_DMI_GW_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 9, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->SPN_Mode = dValues[0];
    pMsg->OccuranceCount = dValues[1];
    pMsg->SPN_HighBit = dValues[2];
    pMsg->FMI = dValues[3];
    pMsg->SPN_Num = dValues[4];
    pMsg->MalfunctionIndicatroLamp = dValues[5];
    pMsg->RedStopLamp = dValues[6];
    pMsg->ProtectLamp = dValues[7];
    pMsg->AmberWarningLamp = dValues[8];
    CM_MessageRawInit(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, nRawValues, 9, &iActualSignalMaxCount);
    pMsg->SPN_Mode_raw = (BYTE)nRawValues[0];
    pMsg->OccuranceCount_raw = (BYTE)nRawValues[1];
    pMsg->SPN_HighBit_raw = (BYTE)nRawValues[2];
    pMsg->FMI_raw = (BYTE)nRawValues[3];
    pMsg->SPN_Num_raw = (WORD)nRawValues[4];
    pMsg->MalfunctionIndicatroLamp_raw = (BYTE)nRawValues[5];
    pMsg->RedStopLamp_raw = (BYTE)nRawValues[6];
    pMsg->ProtectLamp_raw = (BYTE)nRawValues[7];
    pMsg->AmberWarningLamp_raw = (BYTE)nRawValues[8];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_DMI_GW_HS_CAN_LoadSignalValuesArray(DB_DMI_GW_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->SPN_Mode;
    dArray[1] = pMsg->OccuranceCount;
    dArray[2] = pMsg->SPN_HighBit;
    dArray[3] = pMsg->FMI;
    dArray[4] = pMsg->SPN_Num;
    dArray[5] = pMsg->MalfunctionIndicatroLamp;
    dArray[6] = pMsg->RedStopLamp;
    dArray[7] = pMsg->ProtectLamp;
    dArray[8] = pMsg->AmberWarningLamp;
}

void DB_DMI_GW_HS_CAN_LoadRawSignalValuesArray(DB_DMI_GW_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->SPN_Mode_raw;
    nRawValues[1] = pMsg->OccuranceCount_raw;
    nRawValues[2] = pMsg->SPN_HighBit_raw;
    nRawValues[3] = pMsg->FMI_raw;
    nRawValues[4] = pMsg->SPN_Num_raw;
    nRawValues[5] = pMsg->MalfunctionIndicatroLamp_raw;
    nRawValues[6] = pMsg->RedStopLamp_raw;
    nRawValues[7] = pMsg->ProtectLamp_raw;
    nRawValues[8] = pMsg->AmberWarningLamp_raw;
}

int DB_DMI_GW_HS_CAN_Transmit(DB_DMI_GW_HS_CAN * pMsg)
{
    double dArray[9];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DMI_GW_HS_CAN_Init(pMsg);
    }

    DB_DMI_GW_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 9);
}

int DB_DMI_GW_HS_CAN_Transmit_raw(DB_DMI_GW_HS_CAN * pMsg)
{
    uint64 nRawValues[9];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_DMI_GW_HS_CAN_Init(pMsg);
    }

    DB_DMI_GW_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 9);
}

int DB_DMI_GW_HS_CAN_UpdateBytesFromSignals(DB_DMI_GW_HS_CAN * pMsg)
{
    double dArray[9];

    DB_DMI_GW_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, dArray, 9, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_DMI_GW_HS_CAN_UpdateBytesFromRawSignals(DB_DMI_GW_HS_CAN * pMsg)
{
    uint64 nRawValues[9];

    DB_DMI_GW_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_DMI_GW_HS_CAN_Index, nRawValues, 9, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_RouteSG_PT1_HS_CAN_Index = 113;

void DB_RouteSG_PT1_HS_CAN_Init(DB_RouteSG_PT1_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_RouteSG_PT1_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->EngineOilPressure = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_RouteSG_PT1_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->EngineOilPressure_raw = (BYTE)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_RouteSG_PT1_HS_CAN_LoadSignalValuesArray(DB_RouteSG_PT1_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->EngineOilPressure;
}

void DB_RouteSG_PT1_HS_CAN_LoadRawSignalValuesArray(DB_RouteSG_PT1_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->EngineOilPressure_raw;
}

int DB_RouteSG_PT1_HS_CAN_Transmit(DB_RouteSG_PT1_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_RouteSG_PT1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_RouteSG_PT1_HS_CAN_Init(pMsg);
    }

    DB_RouteSG_PT1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_RouteSG_PT1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_RouteSG_PT1_HS_CAN_Transmit_raw(DB_RouteSG_PT1_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_RouteSG_PT1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_RouteSG_PT1_HS_CAN_Init(pMsg);
    }

    DB_RouteSG_PT1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_RouteSG_PT1_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_RouteSG_PT1_HS_CAN_UpdateBytesFromSignals(DB_RouteSG_PT1_HS_CAN * pMsg)
{
    double dArray[1];

    DB_RouteSG_PT1_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_RouteSG_PT1_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_RouteSG_PT1_HS_CAN_UpdateBytesFromRawSignals(DB_RouteSG_PT1_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_RouteSG_PT1_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_RouteSG_PT1_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_RouteSG_ChasOil_HS_CAN_Index = 114;

void DB_RouteSG_ChasOil_HS_CAN_Init(DB_RouteSG_ChasOil_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_RouteSG_ChasOil_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->OilTemperature_T = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_RouteSG_ChasOil_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->OilTemperature_T_raw = (WORD)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_RouteSG_ChasOil_HS_CAN_LoadSignalValuesArray(DB_RouteSG_ChasOil_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->OilTemperature_T;
}

void DB_RouteSG_ChasOil_HS_CAN_LoadRawSignalValuesArray(DB_RouteSG_ChasOil_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->OilTemperature_T_raw;
}

int DB_RouteSG_ChasOil_HS_CAN_Transmit(DB_RouteSG_ChasOil_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_RouteSG_ChasOil_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_RouteSG_ChasOil_HS_CAN_Init(pMsg);
    }

    DB_RouteSG_ChasOil_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_RouteSG_ChasOil_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_RouteSG_ChasOil_HS_CAN_Transmit_raw(DB_RouteSG_ChasOil_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_RouteSG_ChasOil_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_RouteSG_ChasOil_HS_CAN_Init(pMsg);
    }

    DB_RouteSG_ChasOil_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_RouteSG_ChasOil_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_RouteSG_ChasOil_HS_CAN_UpdateBytesFromSignals(DB_RouteSG_ChasOil_HS_CAN * pMsg)
{
    double dArray[1];

    DB_RouteSG_ChasOil_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_RouteSG_ChasOil_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_RouteSG_ChasOil_HS_CAN_UpdateBytesFromRawSignals(DB_RouteSG_ChasOil_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_RouteSG_ChasOil_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_RouteSG_ChasOil_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_RouteSG_LNG_HS_CAN_Index = 115;

void DB_RouteSG_LNG_HS_CAN_Init(DB_RouteSG_LNG_HS_CAN * pMsg)
{
    double dValues[1] = {0.0};
    uint64 nRawValues[1] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_RouteSG_LNG_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 1, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DoubleFuelActualMod = dValues[0];
    CM_MessageRawInit(g_uiHandle, 0, DB_RouteSG_LNG_HS_CAN_Index, nRawValues, 1, &iActualSignalMaxCount);
    pMsg->DoubleFuelActualMod_raw = (BYTE)nRawValues[0];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_RouteSG_LNG_HS_CAN_LoadSignalValuesArray(DB_RouteSG_LNG_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DoubleFuelActualMod;
}

void DB_RouteSG_LNG_HS_CAN_LoadRawSignalValuesArray(DB_RouteSG_LNG_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DoubleFuelActualMod_raw;
}

int DB_RouteSG_LNG_HS_CAN_Transmit(DB_RouteSG_LNG_HS_CAN * pMsg)
{
    double dArray[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_RouteSG_LNG_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_RouteSG_LNG_HS_CAN_Init(pMsg);
    }

    DB_RouteSG_LNG_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_RouteSG_LNG_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 1);
}

int DB_RouteSG_LNG_HS_CAN_Transmit_raw(DB_RouteSG_LNG_HS_CAN * pMsg)
{
    uint64 nRawValues[1];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_RouteSG_LNG_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_RouteSG_LNG_HS_CAN_Init(pMsg);
    }

    DB_RouteSG_LNG_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_RouteSG_LNG_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 1);
}

int DB_RouteSG_LNG_HS_CAN_UpdateBytesFromSignals(DB_RouteSG_LNG_HS_CAN * pMsg)
{
    double dArray[1];

    DB_RouteSG_LNG_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_RouteSG_LNG_HS_CAN_Index, dArray, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_RouteSG_LNG_HS_CAN_UpdateBytesFromRawSignals(DB_RouteSG_LNG_HS_CAN * pMsg)
{
    uint64 nRawValues[1];

    DB_RouteSG_LNG_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_RouteSG_LNG_HS_CAN_Index, nRawValues, 1, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_RouteSG_DFS_HS_CAN_Index = 116;

void DB_RouteSG_DFS_HS_CAN_Init(DB_RouteSG_DFS_HS_CAN * pMsg)
{
    double dValues[2] = {0.0};
    uint64 nRawValues[2] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_RouteSG_DFS_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 2, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->DoubleFuelModFuelEco = dValues[0];
    pMsg->DieseModEco = dValues[1];
    CM_MessageRawInit(g_uiHandle, 0, DB_RouteSG_DFS_HS_CAN_Index, nRawValues, 2, &iActualSignalMaxCount);
    pMsg->DoubleFuelModFuelEco_raw = (DWORD)nRawValues[0];
    pMsg->DieseModEco_raw = (DWORD)nRawValues[1];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_RouteSG_DFS_HS_CAN_LoadSignalValuesArray(DB_RouteSG_DFS_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->DoubleFuelModFuelEco;
    dArray[1] = pMsg->DieseModEco;
}

void DB_RouteSG_DFS_HS_CAN_LoadRawSignalValuesArray(DB_RouteSG_DFS_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->DoubleFuelModFuelEco_raw;
    nRawValues[1] = pMsg->DieseModEco_raw;
}

int DB_RouteSG_DFS_HS_CAN_Transmit(DB_RouteSG_DFS_HS_CAN * pMsg)
{
    double dArray[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_RouteSG_DFS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_RouteSG_DFS_HS_CAN_Init(pMsg);
    }

    DB_RouteSG_DFS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_RouteSG_DFS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 2);
}

int DB_RouteSG_DFS_HS_CAN_Transmit_raw(DB_RouteSG_DFS_HS_CAN * pMsg)
{
    uint64 nRawValues[2];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_RouteSG_DFS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_RouteSG_DFS_HS_CAN_Init(pMsg);
    }

    DB_RouteSG_DFS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_RouteSG_DFS_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 2);
}

int DB_RouteSG_DFS_HS_CAN_UpdateBytesFromSignals(DB_RouteSG_DFS_HS_CAN * pMsg)
{
    double dArray[2];

    DB_RouteSG_DFS_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_RouteSG_DFS_HS_CAN_Index, dArray, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_RouteSG_DFS_HS_CAN_UpdateBytesFromRawSignals(DB_RouteSG_DFS_HS_CAN * pMsg)
{
    uint64 nRawValues[2];

    DB_RouteSG_DFS_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_RouteSG_DFS_HS_CAN_Index, nRawValues, 2, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}


int DB_switch2_HS_CAN_Index = 117;

void DB_switch2_HS_CAN_Init(DB_switch2_HS_CAN * pMsg)
{
    double dValues[20] = {0.0};
    uint64 nRawValues[20] = {0};
    int iActualSignalMaxCount;

    CM_MessageGenericInit(g_uiHandle, 0, 
    DB_switch2_HS_CAN_Index, &pMsg->Statistics, &pMsg->MessageData.iNetwork, 
    &pMsg->MessageData.iNumDataBytes, sizeof(pMsg->MessageData.btData),
    &pMsg->iDefaultPeriodMilliseconds, &pMsg->MessageData.iID,
    &pMsg->MessageData.iBitField, &pMsg->MessageData.btData[0],
    &dValues[0], 20, // number of signals when vspy.h was generated
    &iActualSignalMaxCount, &pMsg->MessageData.iTimeStampNanoSecondsHW, &pMsg->MessageData.iTimeStampMillisecondsOS);
    memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
    pMsg->Ignition_OFF = dValues[0];
    pMsg->Ignition_IN = dValues[1];
    pMsg->VolumeInc = dValues[2];
    pMsg->ReservedSW4 = dValues[3];
    pMsg->OK = dValues[4];
    pMsg->MenuRight = dValues[5];
    pMsg->MenuUp = dValues[6];
    pMsg->MenuLeft = dValues[7];
    pMsg->MenuDown = dValues[8];
    pMsg->Ignition_START = dValues[9];
    pMsg->Ignition_ON = dValues[10];
    pMsg->Ignition_ACC = dValues[11];
    pMsg->ESC = dValues[12];
    pMsg->ChannelDec = dValues[13];
    pMsg->BluetoothPhone = dValues[14];
    pMsg->ChannelInc = dValues[15];
    pMsg->VoiceRequest = dValues[16];
    pMsg->IC_or_MP5 = dValues[17];
    pMsg->Mode = dValues[18];
    pMsg->VolumeDec = dValues[19];
    CM_MessageRawInit(g_uiHandle, 0, DB_switch2_HS_CAN_Index, nRawValues, 20, &iActualSignalMaxCount);
    pMsg->Ignition_OFF_raw = (BYTE)nRawValues[0];
    pMsg->Ignition_IN_raw = (BYTE)nRawValues[1];
    pMsg->VolumeInc_raw = (BYTE)nRawValues[2];
    pMsg->ReservedSW4_raw = (BYTE)nRawValues[3];
    pMsg->OK_raw = (BYTE)nRawValues[4];
    pMsg->MenuRight_raw = (BYTE)nRawValues[5];
    pMsg->MenuUp_raw = (BYTE)nRawValues[6];
    pMsg->MenuLeft_raw = (BYTE)nRawValues[7];
    pMsg->MenuDown_raw = (BYTE)nRawValues[8];
    pMsg->Ignition_START_raw = (BYTE)nRawValues[9];
    pMsg->Ignition_ON_raw = (BYTE)nRawValues[10];
    pMsg->Ignition_ACC_raw = (BYTE)nRawValues[11];
    pMsg->ESC_raw = (BYTE)nRawValues[12];
    pMsg->ChannelDec_raw = (BYTE)nRawValues[13];
    pMsg->BluetoothPhone_raw = (BYTE)nRawValues[14];
    pMsg->ChannelInc_raw = (BYTE)nRawValues[15];
    pMsg->VoiceRequest_raw = (BYTE)nRawValues[16];
    pMsg->IC_or_MP5_raw = (BYTE)nRawValues[17];
    pMsg->Mode_raw = (BYTE)nRawValues[18];
    pMsg->VolumeDec_raw = (BYTE)nRawValues[19];
    if (g_bUseExtendedIdBit && (pMsg->MessageData.iBitField & ATTR_CAN_29BIT_ID_FRAME))
        pMsg->MessageData.iID = mkExtId(pMsg->MessageData.iID);
}

void DB_switch2_HS_CAN_LoadSignalValuesArray(DB_switch2_HS_CAN * pMsg, double *dArray)
{
    dArray[0] = pMsg->Ignition_OFF;
    dArray[1] = pMsg->Ignition_IN;
    dArray[2] = pMsg->VolumeInc;
    dArray[3] = pMsg->ReservedSW4;
    dArray[4] = pMsg->OK;
    dArray[5] = pMsg->MenuRight;
    dArray[6] = pMsg->MenuUp;
    dArray[7] = pMsg->MenuLeft;
    dArray[8] = pMsg->MenuDown;
    dArray[9] = pMsg->Ignition_START;
    dArray[10] = pMsg->Ignition_ON;
    dArray[11] = pMsg->Ignition_ACC;
    dArray[12] = pMsg->ESC;
    dArray[13] = pMsg->ChannelDec;
    dArray[14] = pMsg->BluetoothPhone;
    dArray[15] = pMsg->ChannelInc;
    dArray[16] = pMsg->VoiceRequest;
    dArray[17] = pMsg->IC_or_MP5;
    dArray[18] = pMsg->Mode;
    dArray[19] = pMsg->VolumeDec;
}

void DB_switch2_HS_CAN_LoadRawSignalValuesArray(DB_switch2_HS_CAN * pMsg, uint64 *nRawValues)
{
    nRawValues[0] = pMsg->Ignition_OFF_raw;
    nRawValues[1] = pMsg->Ignition_IN_raw;
    nRawValues[2] = pMsg->VolumeInc_raw;
    nRawValues[3] = pMsg->ReservedSW4_raw;
    nRawValues[4] = pMsg->OK_raw;
    nRawValues[5] = pMsg->MenuRight_raw;
    nRawValues[6] = pMsg->MenuUp_raw;
    nRawValues[7] = pMsg->MenuLeft_raw;
    nRawValues[8] = pMsg->MenuDown_raw;
    nRawValues[9] = pMsg->Ignition_START_raw;
    nRawValues[10] = pMsg->Ignition_ON_raw;
    nRawValues[11] = pMsg->Ignition_ACC_raw;
    nRawValues[12] = pMsg->ESC_raw;
    nRawValues[13] = pMsg->ChannelDec_raw;
    nRawValues[14] = pMsg->BluetoothPhone_raw;
    nRawValues[15] = pMsg->ChannelInc_raw;
    nRawValues[16] = pMsg->VoiceRequest_raw;
    nRawValues[17] = pMsg->IC_or_MP5_raw;
    nRawValues[18] = pMsg->Mode_raw;
    nRawValues[19] = pMsg->VolumeDec_raw;
}

int DB_switch2_HS_CAN_Transmit(DB_switch2_HS_CAN * pMsg)
{
    double dArray[20];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, pMsg->MessageData.iNumDataBytes))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_switch2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_switch2_HS_CAN_Init(pMsg);
    }

    DB_switch2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    return CM_TxFromSignals(g_uiHandle, 0, DB_switch2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, dArray, 20);
}

int DB_switch2_HS_CAN_Transmit_raw(DB_switch2_HS_CAN * pMsg)
{
    uint64 nRawValues[20];
    if (memcmp(pMsg->MessageData.btData, pMsg->MessageData.btInitialData, sizeof(pMsg->MessageData.btData)))
    {
        CM_UpdateMessageSignalsFromBytes(g_uiHandle, 0, DB_switch2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes);
        DB_switch2_HS_CAN_Init(pMsg);
    }

    DB_switch2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    return CM_TxFromRawSignals(g_uiHandle, 0, DB_switch2_HS_CAN_Index, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes, pMsg->MessageData.iNetwork, nRawValues, 20);
}

int DB_switch2_HS_CAN_UpdateBytesFromSignals(DB_switch2_HS_CAN * pMsg)
{
    double dArray[20];

    DB_switch2_HS_CAN_LoadSignalValuesArray(pMsg, dArray);

    if (CM_UpdateBytesFromSignals(g_uiHandle, 0, DB_switch2_HS_CAN_Index, dArray, 20, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

int DB_switch2_HS_CAN_UpdateBytesFromRawSignals(DB_switch2_HS_CAN * pMsg)
{
    uint64 nRawValues[20];

    DB_switch2_HS_CAN_LoadRawSignalValuesArray(pMsg, nRawValues);

    if (CM_UpdateBytesFromRawSignals(g_uiHandle, 0, DB_switch2_HS_CAN_Index, nRawValues, 20, pMsg->MessageData.btData, pMsg->MessageData.iNumDataBytes))
    {
        memcpy(pMsg->MessageData.btInitialData, pMsg->MessageData.btData, sizeof(pMsg->MessageData.btData));
        return 1;
    }
    return 0;
}

