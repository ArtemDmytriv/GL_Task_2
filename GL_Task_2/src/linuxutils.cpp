#include "include/linuxutil.h"

namespace linux_impl{

// CPU

CPUCounter::CPUCounter(){

}

double CPUCounter::getUsage(){
    return 0.4;
}

int CPUCounter::getThreads(){
    return 99;
}

std::string CPUCounter::getArch() const{
    return "--";
}

std::string CPUCounter::getProcName() const{
    return "???";
}

// RAM

RAMCounter::RAMCounter(){
    sysinfo (&memInfo);
}

double RAMCounter::getTotalMB(){
    totalPhysMem = memInfo.totalram;
    totalPhysMem *= memInfo.mem_unit;
    return static_cast<double> (totalPhysMem);
}


double RAMCounter::getUsage(){
    long long physMemUsed = totalPhysMem - memInfo.freeram;
    physMemUsed *= memInfo.mem_unit;
    return static_cast<double> (physMemUsed) / totalPhysMem;
}

double RAMCounter::getTotalVRamMB(){

    totalVirtualMem = memInfo.totalram;
    //Add other values in next statement to avoid int overflow on right hand side...
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;

    return static_cast<double> (totalVirtualMem);
}

double RAMCounter::getVRamUsage(){
    long long virtualMemUsed = totalVirtualMem - memInfo.freeram;
    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit;
    return static_cast<double> (virtualMemUsed) / totalVirtualMem;
}


}