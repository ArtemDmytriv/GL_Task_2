#include "include/UtilClass.h"

UtilClass::UtilClass(hwType t){
    type = t;
}

UtilClass::~UtilClass()
{

}

void UtilClass::init(){
    maxval = this->getFull();
}

void UtilClass::update(){
    data.push_back(this->getUsage());
}

hwType UtilClass::getType() const
{
    return type;
}
