#include "networkinfo.h"


NetworkInfo::NetworkInfo() : UtilClass(hwType::NETW)
{
    drv = new NetworkCounter;
}

double NetworkInfo::getUsage()
{
    return drv->getUsage();
}

double NetworkInfo::getFull()
{
    return drv->getLastMaximum();
}

double NetworkInfo::getSpeed()
{
    return drv->getSpeed();
}

NetworkInfo::~NetworkInfo()
{
    delete(drv);
}
