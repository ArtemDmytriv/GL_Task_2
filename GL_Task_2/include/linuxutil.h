#ifndef LINUXUTIL_H
#define LINUXUTIL_H

#include "head.h"
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "UtilClass.h"

namespace linux_impl{

class CPUCounter{
public:
    CPUCounter();
    double getUsage();
    int getThreads();
    std::string getArch() const;
    std::string getProcName() const;
private:
    unsigned long long lastTotalUser, lastTotalUserLow; 
    unsigned long long lastTotalSys, lastTotalIdle;

};

class RAMCounter{
public:
    RAMCounter();
    double getUsage();
    double getVRamUsage();
    double getTotalMB();
    double getTotalVRamMB();
private:
    struct sysinfo memInfo;
    long long totalPhysMem;
    long long totalVirtualMem;
};

class NetworkCounter{
public:
    NetworkCounter(netwType t = netwType::ETH);
    double getUsage();
    double getSpeed();
    double getLastMaximum();
    std::string getName();
private:
    netwType mnetwType;
    double lastMaximum;
};

}

#endif // LINUXUTIL_H
