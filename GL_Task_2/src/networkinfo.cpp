#include "networkinfo.h"


NetworkInfo::NetworkInfo(netwType t) : UtilClass(hwType::NETW), mNetwType(t)
{
    drv = new NetworkCounter(t);
}

double NetworkInfo::getUsage()
{
    return drv->getUsage();
}

double NetworkInfo::getFull()
{
    return drv->getLastMaximum();
}

std::string NetworkInfo::getName()
{
    return drv->getName();
}

double NetworkInfo::getSpeed()
{
    return drv->getSpeed();
}

NetworkInfo::~NetworkInfo()
{
    delete(drv);
}
