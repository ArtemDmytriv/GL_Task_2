#include "raminfo.h"

RAMInfo::RAMInfo(hwType t) :
    UtilClass(t),
    type(t)
{
    drv = new RAMCounter;
    totalPhysMem = drv->getTotalMB();
    totalVirtualMem = drv->getTotalVRamMB();
}


double RAMInfo::getUsage(){
    return  (type == hwType::RAM)? drv->getUsage() : drv->getVRamUsage();
}

double RAMInfo::getFull(){
    return  (type == hwType::RAM)? totalPhysMem : totalVirtualMem;
}

std::string RAMInfo::getName()
{
    return  ((type == hwType::RAM)? "RAM " : "VRAM ")
        + std::to_string(static_cast<int>((type == hwType::RAM)?totalPhysMem : totalVirtualMem))
        + " MB";
}

RAMInfo::~RAMInfo(){
    delete(drv);
}
