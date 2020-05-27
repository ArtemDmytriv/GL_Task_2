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

signals:
    void updatedItem();

public slots:
    void appendItem();

private:
    std::vector<UtilClass*> mItems;
};

//class AdapterUtil : public QObject {
//Q_OBJECT
//public:
//    AdapterUtil(UtilClass* mhw = nullptr, int timer = TIME, QObject* pobj = 0);
//    ~AdapterUtil();

//    Q_INVOKABLE void update();
//    Q_INVOKABLE void setTimer(int);
//    Q_INVOKABLE std::string getName() const;

//    int getTimer() const;
//private:
//    UtilClass* hw;

//    int timer;
//    std::string name;

//    double maxval;
//    std::vector<double> values;
//};


#endif // ADAPTERUTIL_H
