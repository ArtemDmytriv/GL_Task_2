#ifndef UTILCLASS_H
#define UTILCLASS_H

#include "head.h"

union Data{
   // ...
};


class UtilClass{
public:
    enum class hwType{ CPU, RAM, VRAM, NETW, GPU, NONE};

    UtilClass();
    virtual ~UtilClass();

    virtual float getUsagePerc();
    virtual float getFull();
    virtual float getSpeed();

private:
    hwType type = hwType::NONE;

};


#endif // UTILCLASS_H
