#ifndef UTILCLASS_H
#define UTILCLASS_H

#include "head.h"

#ifdef DEBUG
inline void debug_msg(std::string str) { std::cout << str << '\n'; }
#else
inline void debug_msg(std::string str) {}
#endif //DEBUG


class UtilClass{
public:

    UtilClass(hwType t = hwType::NONE);
    virtual ~UtilClass();

    virtual double getUsage() = 0;
    virtual double getFull() = 0;

    void update();
    void init();
    virtual std::string getName() = 0;

    hwType getType() const;
    std::vector<double> getData() const;
    double getMax();
private:
    hwType type = hwType::NONE;
    double maxval;
    std::vector<double> data;
};


#endif // UTILCLASS_H
