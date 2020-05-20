#ifndef WINUTILS_H
#define WINUTILS_H

#include "head.h"



#ifdef DEBUG
inline void debug_msg(std::string str) { std::cout << str << '\n'; }
#else
inline void debug_msg(std::string str) {}
#endif //DEBUG

class CpuUsage{
private:
    ULONGLONG SubtractTimes(const FILETIME& ftA, const FILETIME& ftB);
    bool EnoughTimePassed();
    inline bool IsFirstRun() const { return (m_dwLastRun == 0); }

    //system total times
    FILETIME m_ftPrevSysKernel;
    FILETIME m_ftPrevSysUser;

    //process times
    FILETIME m_ftPrevProcKernel;
    FILETIME m_ftPrevProcUser;

    short m_nCpuUsage;
    ULONGLONG m_dwLastRun;

    volatile LONG m_lRunCount;
public:
    CpuUsage();
    short getUsage();
};

class GpuUsage;

class RamUsage;

void getCPUinfo();

void getGPUinfo();

void getRAMinfo();


#endif // WINUTILS_H

