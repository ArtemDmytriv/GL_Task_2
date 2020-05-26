#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include "head.h"


class NetworkInfo : public UtilClass{
public:
    NetworkInfo();

    double getUsage() override;
    double getFull() override;

    ~NetworkInfo();
private:
    NetworkCounter *drv;
    double LastMax;
};

#endif // NETWORKINFO_H

