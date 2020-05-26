#include "include/winutils.h"

namespace win_impl {

// CPU IMPLEMENTATION

CPUCounter::CPUCounter(){
    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    GetSystemInfo(&winsysInfo);
}

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

int CPUCounter::getThreads(){
    return winsysInfo.dwNumberOfProcessors;
}

std::string CPUCounter::getArch(){
    switch (winsysInfo.wProcessorArchitecture){
    case PROCESSOR_ARCHITECTURE_AMD64: return std::string("x64");
    case PROCESSOR_ARCHITECTURE_ARM:   return std::string("ARM");
    case PROCESSOR_ARCHITECTURE_INTEL: return std::string("x32");
    case PROCESSOR_ARCHITECTURE_IA64:  return std::string("itanium");
    default: return std::string("-");
    }
}

std::string CPUCounter::getProcName(){
    int CPUInfo[4] = {-1};
    char CPUBrandString[0x40];
    __cpuid(CPUInfo, 0x80000000);
    unsigned int nExIds = CPUInfo[0];

    memset(CPUBrandString, 0, sizeof(CPUBrandString));

    // Get the information associated with each extended ID.
    for (unsigned int i=0x80000000; i<=nExIds; ++i)
    {
        __cpuid(CPUInfo, i);
        // Interpret CPU brand string.
        if  (i == 0x80000002)
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if  (i == 0x80000003)
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if  (i == 0x80000004)
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
    }

    return std::string(CPUBrandString);
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

MEMORYSTATUSEX RAMCounter::getMemInfo() const
{
    return memInfo;
}

double RAMCounter::getVRamUsage(){
    GlobalMemoryStatusEx(&memInfo);
    return (totalVirtualMem - memInfo.ullAvailPageFile) / MB;
}

NetworkCounter::NetworkCounter()
{
    lastMaximum = 50;
}

double NetworkCounter::getUsage()
{
    return 21.21;
}

double NetworkCounter::getSpeed()
{
    return 21.21;
}

double NetworkCounter::getLastMaximum()
{
    return lastMaximum;
}

// NETW IMPLEMENTATION



}

