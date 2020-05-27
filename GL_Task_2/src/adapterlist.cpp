#include "adapterlist.h"

AdapterList::AdapterList(int count, QObject* parent) :
    QObject(parent)
{
    std::cout << "List was created\n";
    mItems.resize(count);
}

std::vector<UtilClass *> AdapterList::items() const
{
    return mItems;
}

bool AdapterList::setItemAt(size_t index, UtilClass *item)
{
    if (index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}

int AdapterList::getCount() const
{
    return mItems.size();
}

void AdapterList::debugPrintData() const
{
    for (auto & elem : mItems){
        std::cout << elem->getName() << std::endl;
        for (auto & usage : elem->getData()){
            std::cout <<usage <<" ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n%#%#%#%#%#%#%#%#%#%\n";
}

void AdapterList::appendItem(UtilClass *item)
{
    mItems.push_back(item);
    emit itemAppended();
}

void AdapterList::updateAllItems()
{
    for(auto elem : mItems){
        elem->update();
    }
    emit itemUpdated();
}




