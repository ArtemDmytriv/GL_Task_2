#ifndef CPUINFO_H
#define CPUINFO_H

#include "head.h"
#include "UtilClass.h"

class CPUInfo : UtilClass{
public:
    CPUInfo();

private:
    CPUCounter drv;
    std::string arch;
    int cores;
};

#endif // CPUINFO_H
