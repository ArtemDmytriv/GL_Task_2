#ifndef LINUXUTIL_H
#define LINUXUTIL_H

#include "head.h"
#include "UtilClass.h"

namespace linux_impl{

class CPUCounter{
public:
    CPUCounter();
    double getUsage();
    void* getCpuInfo();
private:


};

class RAMCounter{
public:
    RAMCounter();
    double getUsage();
    double getVRamUsage();
    double getTotalMB();
    double getTotalVRamMB();
private:

};

class NetworkCounter{

};

}

#endif // LINUXUTIL_H
