#ifndef RAMINFO_H
#define RAMINFO_H

#include "head.h"

class RAMInfo : public UtilClass{
public:
    RAMInfo(hwType t = hwType::RAM);

    double getUsage() override;
    double getFull() override;
    std::string getName() override;

    ~RAMInfo();
private:
    hwType type;
    RAMCounter* drv;
    double totalPhysMem;
    double totalVirtualMem;
};

#endif // RAMINFO_H

