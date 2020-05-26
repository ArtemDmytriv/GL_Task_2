#include "include/linuxutil.h"

namespace linux_impl{

// CPU

CPUCounter::CPUCounter(){
    std::ifstream fin ("/proc/stat");
    std::string temp;
    fin >> temp >> lastTotalUser
     >> lastTotalUserLow 
     >> lastTotalSys 
     >> lastTotalIdle;
    
    fin.close();
}

double CPUCounter::getUsage(){
    double usage = 0;
    
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

    std::ifstream fin ("/proc/stat");
    std::string temp;
    fin >> temp >> totalUser
     >> totalUserLow 
     >> totalSys 
     >> totalIdle;

    
    fin.close();

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle){
        //Overflow detection. Just skip this value.
        usage = -1.0;
    }
    else{
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
        usage = total;
        total += (totalIdle - lastTotalIdle);
        usage /= total;
        usage *= 100;
    }

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return usage;
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