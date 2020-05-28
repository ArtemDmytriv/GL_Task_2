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

    QList<double> values;
    auto vec = item->getData();
    values.reserve(vec.size());
    std::copy(vec.begin(), vec.end(), std::back_inserter(values));
    QVariant var;
    var.setValue(values);

    switch (role) {
        case NameRole:
            return QString::fromStdString(item->getName());
        case DataRole:
            return var;
        case MaxRole:
            return item->getMax();
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
        case MaxRole:
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
    names[MaxRole] = "max";
    return names;
}

AdapterList *AdapterModel::list() const
{
    return mList;
}

void AdapterModel::saveToFile(QVariant time, QVariant kinds, QVariant savepath = "")
{
    int t = time.toInt();
    int k = kinds.toInt();

    std::cout << "start Save file\n";
    std::string path = savepath.toString().toStdString();

    std::ofstream fout(path + "data.txt");
    if (k & 1)
        fout << "CPU,";
    if (k & 2)
        fout << "RAM,";
    if (k & 4)
        fout << "VRAM,";
    if (k & 8)
        fout << "NETW,";
    fout << "\n";
    std::vector<UtilClass*> lst = mList->items();

    for (size_t i = 0; i < lst[0]->getData().size(); ++i){
        for (size_t j = 0; j < lst.size(); ++j){
            if (k & (int)pow(2,j))
                fout << lst[j]->getData()[i] << ",";
        }
        fout << '\n';
    }
    std::cout << "end Save file\n";
    fout.close();
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
