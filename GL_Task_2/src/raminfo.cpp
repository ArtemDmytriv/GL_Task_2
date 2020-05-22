#include "raminfo.h"

RAMInfo::RAMInfo() : UtilClass(hwType::RAM)
{
    drv = new RAMCounter;
    totalPhusMem = drv->getTotalMB();
    totalVirtualMem = drv->getTotalVRamMB();
}


double RAMInfo::getUsage(){
    return  totalPhusMem * drv->getUsage();
}

double RAMInfo::getFull(){
    return  totalPhusMem;
}

RAMInfo::~RAMInfo(){
    delete(drv);
}
