#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "head.h"

class BaseObject
{
public:
    BaseObject();
    virtual float getUsage() = 0;
    virtual void update() = 0;
    virtual ~BaseObject();
};

#endif // BASEOBJECT_H
