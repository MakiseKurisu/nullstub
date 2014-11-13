#define _BUILD_WAFFLE_COMPONENT_
#include <waffle.h>
#pragma GCC diagnostic ignored "-Wunused-parameter"

WAFFLE_COMPONENT_FUNCTION int WINAPI DetourMessageBoxA(
    _In_opt_    HWND hWnd,
    _In_opt_    LPCSTR lpText,
    _In_opt_    LPCSTR lpCaption,
    _In_        UINT uType
    )
{
    static LPMESSAGEBOXA BackupMessageBoxA;
    if (!BackupMessageBoxA)
    {
        BackupMessageBoxA = (LPMESSAGEBOXA) WaffleGetBackupAddress(TEXT("user32.dll"), TEXT("MessageBoxA"));
    }

    return BackupMessageBoxA(hWnd, "I'm in charge!", "Waffle", uType);
}

WAFFLE_COMPONENT_FUNCTION SIZE_T WINAPI ComponentInit(
    _In_    LPWAFFLE_PROCESS_SETTING lpstProcessSetting
    )
{
    return 0;
}

BOOL WINAPI DllMain(
    _In_    HINSTANCE hinstDLL,
    _In_    DWORD fdwReason,
    _In_    LPVOID lpvReserved
    )
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);
    }
    return TRUE;
}