#include "include/winutils.h"


unsigned long long CPUCounter::FileTimeToInt64(const FILETIME & ft){
    return (((unsigned long long)(ft.dwHighDateTime))<<32)|((unsigned long long)ft.dwLowDateTime);
}


double CPUCounter::CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime = totalTicks-_previousTotalTicks;
    unsigned long long idleTicksSinceLastTime  = idleTicks-_previousIdleTicks;

    float ret = 1.0f-((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks  = idleTicks;
    return ret;
}

float CPUCounter::getUsage(){
   return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime)+FileTimeToInt64(userTime)) : -1.0f;
}

RAMCounter::RAMCounter(){
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    totalVirtualMem = memInfo.ullTotalPageFile;
}

float RAMCounter::getTotalMB(){
    return memInfo.ullTotalPhys / 1048576;
}

float RAMCounter::getUsage(){
    GlobalMemoryStatusEx(&memInfo);
    return (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / 1048576;
}
