#ifndef WINUTILS_H
#define WINUTILS_H

#include "head.h"
#include "UtilClass.h"

int GB = 1073741824; // bits in GB;
int MB = 1048576; // bits in MB;
int KB = 1024 ; // bits in KB;

#ifdef DEBUG
inline void debug_msg(std::string str) { std::cout << str << '\n'; }
#else
inline void debug_msg(std::string str) {}
#endif //DEBUG

class CPUCounter{
public:
    CPUCounter();
    float getUsage();
private:
    unsigned long long FileTimeToInt64(const FILETIME & ft);
    double CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
    FILETIME idleTime, kernelTime, userTime;
};

class RAMCounter{
public:
    RAMCounter();
    float getUsage();
    float getTotalMB();
private:
    MEMORYSTATUSEX memInfo;
    DWORDLONG totalVirtualMem;
};


class VRAMCounter{
public:
    VRAMCounter();
    float getUsage();
    float getTotalMB();
private:
    MEMORYSTATUSEX memInfo;
    DWORDLONG totalVirtualMem;
};


#endif // WINUTILS_H

