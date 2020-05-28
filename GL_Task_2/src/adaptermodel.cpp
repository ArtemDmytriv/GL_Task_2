#include "adaptermodel.h"
#include "adapterlist.h"
#include "QVector"

AdapterModel::AdapterModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{
    std::cout << "Model was created\n";
}

int AdapterModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    // FIXME: Implement me!
    return mList->getCount();
}

QVariant AdapterModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    UtilClass* item = mList->items().at(index.row());

    QVariant var;
    var.setValue(item->getData());

    switch (role) {
        case NameRole:
            return QString::fromStdString(item->getName());
        case DataRole:
            return var;
    }

    return QVariant{};
}

bool AdapterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(value);

    if (!mList)
        return false;

    UtilClass* item = mList->items().at(index.row());
    switch (role) {
        case NameRole:
            break;
        case DataRole:
            item->update();
            break;
    }


    if (mList->setItemAt(index.row(), item)) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        emit dataUpdated();
        return true;
    }
    return false;
}

Qt::ItemFlags AdapterModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> AdapterModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[DataRole] = "data";
    return names;
}

AdapterList *AdapterModel::list() const
{
    return mList;
}

void AdapterModel::setList(AdapterList *list)
{
    beginResetModel();
    if (mList)
        mList->disconnect(this);
    mList = list;

    if (mList){
        connect(mList, &AdapterList::itemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
            endInsertRows();
        });

        connect(mList, &AdapterList::itemUpdated, this, [=]() {
            std::cout <<"@FROM MODEL@>> Data was updated" << std::endl;
            emit dataUpdated();
        });
    }
    endResetModel();
}
