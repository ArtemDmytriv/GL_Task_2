#ifndef CPUINFO_H
#define CPUINFO_H

#include "head.h"
#include "UtilClass.h"

class CPUInfo : public UtilClass{
public:
    CPUInfo();
    ~CPUInfo();
    int getThreads();
    std::string getArch() const;
    std::string getCpuName() const;

    double getUsage() override;
    double getFull() override;
    std::string getName() override;

private:
    CPUCounter* drv;
    std::string arch;
    std::string cpuName;
    int cores;
};


#endif // CPUINFO_H
