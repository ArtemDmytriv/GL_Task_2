#ifndef WINUTILS_H
#define WINUTILS_H

#include "head.h"
#include "UtilClass.h"

namespace win_impl {

class CPUCounter{
public:
    CPUCounter();
    double getUsage();
    void* getCpuInfo();// WIN implementation of cpu info
private:
    unsigned long long FileTimeToInt64(const FILETIME & ft);
    double CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
    FILETIME idleTime, kernelTime, userTime;
};

class RAMCounter{
public:
    RAMCounter();
    double getUsage();
    double getVRamUsage();
    double getTotalMB();
    double getTotalVRamMB();
private:
    MEMORYSTATUSEX memInfo;
    DWORDLONG totalPhusMem;
    DWORDLONG totalVirtualMem;
};

class NetworkCounter{

};

}

#endif // WINUTILS_H

