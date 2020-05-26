#ifndef WINUTILS_H
#define WINUTILS_H

#include "head.h"
#include "UtilClass.h"

namespace win_impl {

class CPUCounter{
public:
    CPUCounter();
    double getUsage();
    int getThreads();
    std::string getArch();
    std::string getProcName();
private:
    unsigned long long FileTimeToInt64(const FILETIME & ft);
    double CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
    FILETIME idleTime, kernelTime, userTime;
    SYSTEM_INFO winsysInfo;
};

class RAMCounter{
public:
    RAMCounter();
    double getUsage();
    double getVRamUsage();
    double getTotalMB();
    double getTotalVRamMB();

    MEMORYSTATUSEX getMemInfo() const;

private:
    MEMORYSTATUSEX memInfo;
    DWORDLONG totalPhusMem;
    DWORDLONG totalVirtualMem;
};

class NetworkCounter{
public:
    NetworkCounter();
    double getUsage();
    double getSpeed();
    double getLastMaximum();
private:
    double lastMaximum;
};

}

#endif // WINUTILS_H

