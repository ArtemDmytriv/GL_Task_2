#include "include/winutils.h"

namespace win_impl {

// CPU IMPLEMENTATION

unsigned long long CPUCounter::FileTimeToInt64(const FILETIME & ft){
    return (((unsigned long long)(ft.dwHighDateTime))<<32)|((unsigned long long)ft.dwLowDateTime);
}


double CPUCounter::CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime  = idleTicks - _previousIdleTicks;

    float ret = 1.0f -( (totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks  = idleTicks;
    return ret;
}

double CPUCounter::getUsage(){
   if (GetSystemTimes(&idleTime, &kernelTime, &userTime))
       return CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime)+FileTimeToInt64(userTime));
   else
       return  -1.0;
}

// RAM IMPLEMENTATION

RAMCounter::RAMCounter(){
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    totalPhusMem = memInfo.ullTotalPhys;
    totalVirtualMem = memInfo.ullTotalPageFile;
}

double RAMCounter::getTotalMB(){
    return totalPhusMem / MB;
}

double RAMCounter::getUsage(){
    GlobalMemoryStatusEx(&memInfo);
    return (totalPhusMem - memInfo.ullAvailPhys) / MB;
}

double RAMCounter::getTotalVRamMB(){
    return totalVirtualMem / MB;
}

double RAMCounter::getVRamUsage(){
    GlobalMemoryStatusEx(&memInfo);
    return (totalVirtualMem - memInfo.ullAvailPageFile) / MB;
}

// NETW IMPLEMENTATION

using namespace std;

#include "wbemcli.h"

int NetworkCounter(){
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_PerfRawData_Tcpip_NetworkInterface"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres))
    {
        cout << "Query for operating system name failed."
            << " Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;               // Program has failed.
    }


    // Get the data from the query
    IWbemClassObject *pclsObj = NULL;
    ULONG uReturn = 0;

    while (pEnumerator)
    {

        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
            &pclsObj, &uReturn);

        if (0 == uReturn)
        {
        break;
        }


        VARIANT vtProp;
        VariantInit(&vtProp);

        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        wcout << " network adapter : " << vtProp.bstrVal << endl;
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"BytesReceivedPerSec", 0, &vtProp, 0, 0);
        wcout << " BytesReceivedPerSec  : " << vtProp.bstrVal << endl;
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"BytesSentPerSec", 0, &vtProp, 0, 0);
        wcout << " BytesSentPerSec  : " << vtProp.bstrVal << endl;
        VariantClear(&vtProp);

        hr = pclsObj->Get(L"Timestamp_Sys100NS", 0, &vtProp, 0, 0);
        wcout << " Timestamp_Sys100NS  : " << vtProp.bstrVal << endl;
        VariantClear(&vtProp);




        pclsObj->Release();
    }
}

}
