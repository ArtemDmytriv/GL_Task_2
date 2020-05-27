#include "adapterlist.h"

AdapterList::AdapterList(int count, QObject* parent) :
    QObject(parent)
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
    return true;
}

