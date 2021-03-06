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
    }

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return usage;
}

int CPUCounter::getThreads(){
    return sysconf( _SC_NPROCESSORS_ONLN );
}

std::string CPUCounter::getArch() const{
    std::ifstream fin ("/proc/cpuinfo");
    std::string line, arch;
    while (!fin.eof()){
        getline(fin, line);
        if (line.find("flags") != std::string::npos){

            fin.close();
            if(line.find("lm") != std::string::npos)
                return "x64";
            if(line.find("tm") != std::string::npos)
                return "x32";
            if(line.find("rm") != std::string::npos)
                return "x16";
        }
    }
    return "NaN";
}

std::string CPUCounter::getProcName() const{
    std::ifstream fin ("/proc/cpuinfo");
    std::string line, arch;
    size_t pos = 0;
    while (!fin.eof()){
        getline(fin, line);
        if ( (pos = line.find("model name")) != std::string::npos){
            return line.substr(line.find(':', pos) + 2, line.find('\n'));
        }
    }
    return "NaN";
}

// RAM

RAMCounter::RAMCounter(){
    sysinfo (&memInfo);

    totalPhysMem = memInfo.totalram;
    totalPhysMem *= memInfo.mem_unit;

    totalVirtualMem = memInfo.totalram;
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;
}

double RAMCounter::getTotalMB(){
    return static_cast<double> (totalPhysMem) / MB;;
}


double RAMCounter::getUsage(){
    long long physMemUsed = totalPhysMem - memInfo.freeram;
    physMemUsed *= memInfo.mem_unit;
    return static_cast<double> (physMemUsed) / MB;
}

double RAMCounter::getTotalVRamMB(){
    return static_cast<double> (totalVirtualMem) / MB;
}

double RAMCounter::getVRamUsage(){
    long long virtualMemUsed = totalVirtualMem - memInfo.freeram;
    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit;
    return static_cast<double> (virtualMemUsed) / MB;
}

// NETWORK

NetworkCounter::NetworkCounter(netwType t) : mnetwType(t){

}

double NetworkCounter::getUsage(){
    return getSpeed();
}

double NetworkCounter::getSpeed(){
    std::string interface = (mnetwType == netwType::ETH)? "eth0" : "lo";
    std::ifstream net_work_monitor(std::string("/sys/class/net/"  + interface + "/") );

    if (net_work_monitor.good() == 1){
        std::ifstream network_speed_check;
        network_speed_check.open("/sys/class/net/" + interface + "/statistics/rx_bytes");
        std::string output;
        if (network_speed_check.is_open()) {
            while (!network_speed_check.eof()) {
                network_speed_check >> output;
            }
        }
        net_work_monitor.close();
        network_speed_check.close();

        auto speed = std::stoi(output);
        if (lastMaximum < speed){
            lastMaximum = speed;
        }
        return speed / KB;
    }
    return 0;
}

double NetworkCounter::getLastMaximum(){
    return lastMaximum / KB;
}

std::string NetworkCounter::getName(){
    return (mnetwType == netwType::ETH)? "eth0" : "lo";
}

}
