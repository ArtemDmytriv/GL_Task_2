#include "AdapterUtil.h"

AdapterUtil::AdapterUtil(QObject* pobj, UtilClass *mhw, int mtimer) :
    QObject(pobj),
    hw(mhw),
    timer(mtimer)
{
    maxval = hw->getFull();
    name = hw->getName();
}

AdapterUtil::~AdapterUtil()
{

}

void AdapterUtil::update(){

}

void AdapterUtil::setTimer(int timer)
{
    this->timer = (timer <= 1)? 1 : timer;
}

std::string AdapterUtil::getName() const
{
    return name;
}

int AdapterUtil::getTimer() const
{
    return timer;
}
