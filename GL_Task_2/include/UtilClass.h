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

    hwType getType() const;

private:
    hwType type = hwType::NONE;

};


#endif // UTILCLASS_H
