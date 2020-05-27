#include "include/cpuinfo.h"


CPUInfo::CPUInfo() : UtilClass(hwType::CPU)
{
    drv = new CPUCounter;
    arch = drv->getArch();
    cpuName = drv->getProcName();
}

CPUInfo::~CPUInfo()
{
    delete drv;
}

int CPUInfo::getThreads(){
    return  drv->getThreads();
}

double CPUInfo::getUsage(){
    return  drv->getUsage();
}

double CPUInfo::getFull(){
    return 1.0;
}

std::string CPUInfo::getName()
{
    return drv->getProcName();
}

std::string CPUInfo::getArch() const{
    return arch;
}

std::string CPUInfo::getCpuName() const{
    return cpuName;
}

