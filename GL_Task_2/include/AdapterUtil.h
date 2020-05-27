#ifndef ADAPTERUTIL_H
#define ADAPTERUTIL_H

#include "head.h"
#include "UtilClass.h"
#include "QtCore"

class AdapterUtil : public QObject{
Q_OBJECT
public:
    AdapterUtil(QObject* pobj = 0, UtilClass* mhw = nullptr, int timer = TIME);
    ~AdapterUtil();

    Q_INVOKABLE void update();
    Q_INVOKABLE void setTimer(int);
    Q_INVOKABLE std::string getName() const;
    int getTimer() const;
private:
    UtilClass* hw;

    int timer;
    std::string name;

    double maxval;
    std::vector<double> values;
};



#endif // ADAPTERUTIL_H
