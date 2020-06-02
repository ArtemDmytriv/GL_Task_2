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

std::vector<double> UtilClass::getData() const
{
    return data;
}

double UtilClass::getMax()
{
    if (type == hwType::NETW){
        return this->getFull();
    }
    else{
        return maxval;
    }
}
