#include "adapterlist.h"

AdapterList::AdapterList(int count = 4, QObject* pobj = 0) :
    QObject(pobj)
{
    mItems.resize(count);
}

std::vector<UtilClass *> AdapterList::items() const
{
    return mItems;
}

bool AdapterList::setItemAt(size_t index, UtilClass *item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
}

