#ifndef WINUTILS_H
#define WINUTILS_H

#include "head.h"
#include "pdh.h"
#include "TCHAR.h"


#ifdef DEBUG
inline void debug_msg(std::string str) { std::cout << str << '\n'; }
#else
inline void debug_msg(std::string str) {}
#endif //DEBUG

class CPUCounter {
public:
    // Provide actual CPU usage value in range
    float getUsage();
private:
    unsigned long long FileTimeToInt64(const FILETIME & ft);
    double CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
    FILETIME idleTime, kernelTime, userTime;
};


class RamUsage;

void getCPUinfo();

void getGPUinfo();

void getRAMinfo();


#endif // WINUTILS_H

