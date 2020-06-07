#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include "head.h"


class NetworkInfo : public UtilClass{
public:
    netwType mNetwType;

    NetworkInfo(netwType t = netwType::ETH);

    double getUsage() override;
    double getFull() override;
    std::string getName() override;

    double getSpeed();

    ~NetworkInfo();
private:

    NetworkCounter *drv;
    double LastMax;
};

#endif // NETWORKINFO_H

