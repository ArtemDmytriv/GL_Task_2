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
    NetworkCounter(netwType t = netwType::ETH);
    double getUsage();
    double getSpeed();
    std::string getName();
    double getLastMaximum();
private:
    double lastMaximum;
    netwType mnetwType;
    struct CounterData {
        PDH_HCOUNTER hcounter;
        std::string  name;
        std::string  path;
    };

    PDH_HQUERY               hquery;
    std::vector<CounterData> counter_list;
    std::string              object_name;
    std::string              instance_name;

    volatile bool keep_going;
};

}

#endif // WINUTILS_H

