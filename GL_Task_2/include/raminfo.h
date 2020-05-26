#ifndef RAMINFO_H
#define RAMINFO_H

#include "head.h"


class RAMInfo : UtilClass{
public:
    RAMInfo();

    double getUsage() override;
    double getFull() override;

    ~RAMInfo();
private:
    RAMCounter* drv;
    double totalPhusMem;
    double totalVirtualMem;
};

#endif // RAMINFO_H

