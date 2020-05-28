#ifndef ADAPTERUTIL_H
#define ADAPTERUTIL_H

#include "head.h"
#include "UtilClass.h"
#include "QAbstractListModel"
#include "QtCore"


class AdapterList : public QObject {
    Q_OBJECT
public:

    explicit AdapterList(int count = 0, QObject *parent = 0);

    std::vector<UtilClass *> items() const;
    bool setItemAt(size_t index, UtilClass* item);
    int getCount() const;

    void debugPrintData() const;
signals:
    void itemAppended();
    void itemUpdated();

public slots:
    void appendItem(UtilClass *item);
    void updateAllItems();

private:
    std::vector<UtilClass*> mItems;
};



#endif // ADAPTERUTIL_H
