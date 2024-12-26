#include <Windows.h>
#include <powrprof.h>
#include <cstring>

static int EnableTouchpad(bool enable)
{
    char cmd[80] = "SystemSettingsAdminFlows EnableTouchpad X";
    cmd[strlen(cmd) - 1] = enable ? '1' : '0';
    return system(cmd);
}

static ULONG isConnectedStandby(PVOID Context, ULONG Type, PVOID Setting)
{
    if (Type == PBT_APMSUSPEND)
    {
        EnableTouchpad(false);
    }
    else if (Type == PBT_APMRESUMESUSPEND)
    {
        EnableTouchpad(true);
    }
    return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    DEVICE_NOTIFY_SUBSCRIBE_PARAMETERS testCallback = {isConnectedStandby, nullptr};
    RegisterSuspendResumeNotification((HANDLE)&testCallback, DEVICE_NOTIFY_CALLBACK);
    while (true) {
        Sleep(10000);
    }
    return 0;
}
