// OSEKNM_AC.cpp: Defines the entry point for the DLL application.
//
#include "../../../stdafx.h"

#define MIN_PROJECT_VERSION     2

extern "C" void __stdcall CM_ExtensionInit(unsigned int  uiHandle,  struct stCallBackPointers  * stCallBackPointers);
extern "C" void __stdcall Spy_EveryLoop(unsigned int uiCurrentTime);
extern "C" int __stdcall  Spy_Main();
extern "C" void Spy_BeforeStarted();
extern "C" void Spy_Started();
extern "C" void  Spy_Stopped();
extern "C" void  Spy_EveryGUILoop();
extern "C" void  Spy_KeyPress(int iKey, int iCTRLPressed, int iALTPressed);
extern "C" int  CM_GetVSPY_C_H_Version();
extern "C" void Spy_ErrorState(int iNetwork, int iTxErrorCount, int iRxErrorCount, int iErrorBitfield);
extern "C" void Spy_ErrorFrame(int iNetwork, int iTxErrorCount, int iRxErrorCount, int iErrorBitfield);
extern "C" void __stdcall CM_EveryMessage(int iNetwork,int iID,__int64 iTimeStampNanoSecondsHW,
						unsigned int iTimeStampMillisecondsOS,int iNumDataBytes,
						int iBitField,unsigned char * p_btData);
extern "C" int getStartDelay();
extern "C" void setStartDelay(int delay);
DWORD g_lStartTickCount = 0;
extern "C" HMODULE g_hDllHandle = NULL;
extern "C" void ICS_RS232CloseAllPorts();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    g_hDllHandle = hModule;
    return TRUE;
}

void _stdcall ICSCoreMiniExtensionInit(unsigned int uiHandle, struct stCallBackPointers *p_stCallBackPointers)
{
    // call the C function (defined in vspy.c)
    CM_ExtensionInit(uiHandle, p_stCallBackPointers);
}

void _stdcall ICSCoreMiniExtensionProcessMs(unsigned int uiCurrentTime)
{
    if (g_lStartTickCount && (GetTickCount() < g_lStartTickCount))
        return;
    Spy_EveryLoop(uiCurrentTime);
}

void _stdcall ICSCoreMiniExtensionProcessGUI()
{
    if (g_lStartTickCount && (GetTickCount() < g_lStartTickCount))
        return;
    Spy_EveryGUILoop();
}

int _stdcall ICSCoreMiniExtensionBeforeStarted()
{
    Spy_BeforeStarted();
    if (getStartDelay())
        g_lStartTickCount = GetTickCount() + getStartDelay();
    // return true for vehicle spy to continue starting
    return 1;
}

void _stdcall ICSCoreMiniExtensionStarted()
{
    if (getStartDelay())
    {
        while (GetTickCount() < g_lStartTickCount)
            Sleep(1);
        g_lStartTickCount = 0;
    }
    Spy_Started();
} // when vspy finally starts

void _stdcall ICSCoreMiniExtensionStopped()
{
    Spy_Stopped();
    ICS_RS232CloseAllPorts();
} // when vspy stops

void _stdcall ICSCoreMiniExtensionKeyPress(wchar_t iChar, int iBitField)
{
    if (g_lStartTickCount && (GetTickCount() < g_lStartTickCount))
        return;
    int iCTRLPressed;
    int iALTPressed;
    if (iBitField & 1) iCTRLPressed=1; else iCTRLPressed =0;
    if (iBitField & 2) iALTPressed=1; else iALTPressed =0;
    Spy_KeyPress(iChar,  iCTRLPressed,  iALTPressed);
}

DWORD _stdcall ICSCoreMiniExtensionMain(PVOID pArg)
{
    if (getStartDelay())
    {
        while (GetTickCount() < g_lStartTickCount)
            Sleep(1);
        g_lStartTickCount = 0;
    }
    return Spy_Main();
} // a separate thread runs this "main" function

void _stdcall ICSCoreMiniExtensionErrorFrame(int iNetwork, int iTxErrorCount, int iRxErrorCount, int iErrorBitfield)
{
    if (g_lStartTickCount && (GetTickCount() < g_lStartTickCount))
        return;
    Spy_ErrorFrame(iNetwork, iTxErrorCount, iRxErrorCount, iErrorBitfield);
}

void _stdcall ICSCoreMiniExtensionErrorState(int iNetwork, int iTxErrorCount, int iRxErrorCount, int iErrorBitfield)
{
    if (g_lStartTickCount && (GetTickCount() < g_lStartTickCount))
        return;
    Spy_ErrorState(iNetwork, iTxErrorCount, iRxErrorCount, iErrorBitfield);
}

void _stdcall ICSCoreMiniExtensionEveryMessage(int iNetwork,int iID,__int64 iTimeStampNanoSecondsHW,unsigned int iTimeStampMillisecondsOS,
						int iNumDataBytes,int iBitField,unsigned char * p_btData)
{
    if (g_lStartTickCount && (GetTickCount() < g_lStartTickCount))
        return;
    CM_EveryMessage(iNetwork,iID,iTimeStampNanoSecondsHW,iTimeStampMillisecondsOS,iNumDataBytes,iBitField,p_btData);
}

void _stdcall ICSCoreMiniAPIVersionCheck(int * pProjectVersion, int * pVSPY_C_H_Version)
{
    *pProjectVersion = MIN_PROJECT_VERSION;
    *pVSPY_C_H_Version = CM_GetVSPY_C_H_Version();
}
