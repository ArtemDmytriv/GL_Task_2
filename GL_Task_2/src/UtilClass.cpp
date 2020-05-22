#include "include/UtilClass.h"

UtilClass::UtilClass(hwType t){
    type = t;
}

UtilClass::~UtilClass()
{

}

hwType UtilClass::getType() const
{
    return type;
}
