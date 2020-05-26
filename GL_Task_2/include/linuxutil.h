#ifndef LINUXUTIL_H
#define LINUXUTIL_H

#include "head.h"
#include "UtilClass.h"

namespace linux_impl{

class CPUCounter : UtilClass{
public:
    CPUCounter();
    double getUsage();
    int getThreads();
    std::string getArch() const;
    std::string getProcName() const;
private:
    std::string arch;
    std::string procname;
};

class RAMCounter : UtilClass{
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
