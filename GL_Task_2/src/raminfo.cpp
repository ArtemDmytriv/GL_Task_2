#include "raminfo.h"

RAMInfo::RAMInfo() : UtilClass(hwType::RAM)
{
    drv = new RAMCounter;
    totalPhysMem = drv->getTotalMB();
    totalVirtualMem = drv->getTotalVRamMB();
}


double RAMInfo::getUsage(){
    return  drv->getUsage();
}

double RAMInfo::getFull(){
    return  totalPhysMem;
}

RAMInfo::~RAMInfo(){
    delete(drv);
}
