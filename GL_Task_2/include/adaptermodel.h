#ifndef ADAPTERMODEL_H
#define ADAPTERMODEL_H

#include "head.h"
#include <QAbstractListModel>

class AdapterModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AdapterModel(QObject *parent = nullptr);

    enum {
        NameRole = Qt::UserRole,
        DataRole
    };
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

private:
};

#endif // ADAPTERMODEL_H
