#include "include/winutils.h"

namespace win_impl {

// CPU IMPLEMENTATION

CPUCounter::CPUCounter(){
    GetSystemTimes(&idleTime, &kernelTime, &userTime);
    GetSystemInfo(&winsysInfo);
}

unsigned long long CPUCounter::FileTimeToInt64(const FILETIME & ft){
    return (((unsigned long long)(ft.dwHighDateTime))<<32)|((unsigned long long)ft.dwLowDateTime);
}


double CPUCounter::CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime  = idleTicks - _previousIdleTicks;

    float ret = 1.0f -( (totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks  = idleTicks;
    return ret;
}

double CPUCounter::getUsage(){
   if (GetSystemTimes(&idleTime, &kernelTime, &userTime))
       return CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime)+FileTimeToInt64(userTime)) * 2;
   else
       return  -1.0;
}

int CPUCounter::getThreads(){
    return winsysInfo.dwNumberOfProcessors;
}

std::string CPUCounter::getArch(){
    switch (winsysInfo.wProcessorArchitecture){
    case PROCESSOR_ARCHITECTURE_AMD64: return std::string("x64");
    case PROCESSOR_ARCHITECTURE_ARM:   return std::string("ARM");
    case PROCESSOR_ARCHITECTURE_INTEL: return std::string("x32");
    case PROCESSOR_ARCHITECTURE_IA64:  return std::string("itanium");
    default: return std::string("-");
    }
}

std::string CPUCounter::getProcName(){
    int CPUInfo[4] = {-1};
    char CPUBrandString[0x40];
    __cpuid(CPUInfo, 0x80000000);
    unsigned int nExIds = CPUInfo[0];

    memset(CPUBrandString, 0, sizeof(CPUBrandString));

    // Get the information associated with each extended ID.
    for (unsigned int i=0x80000000; i<=nExIds; ++i)
    {
        __cpuid(CPUInfo, i);
        // Interpret CPU brand string.
        if  (i == 0x80000002)
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if  (i == 0x80000003)
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if  (i == 0x80000004)
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
    }

    return std::string(CPUBrandString);
}


// RAM IMPLEMENTATION

RAMCounter::RAMCounter(){
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    totalPhusMem = memInfo.ullTotalPhys;
    totalVirtualMem = memInfo.ullTotalPageFile;
}

double RAMCounter::getTotalMB(){
    return totalPhusMem / MB;
}

double RAMCounter::getUsage(){
    GlobalMemoryStatusEx(&memInfo);
    return (totalPhusMem - memInfo.ullAvailPhys) / MB;
}

double RAMCounter::getTotalVRamMB(){
    return totalVirtualMem / MB;
}

MEMORYSTATUSEX RAMCounter::getMemInfo() const
{
    return memInfo;
}

double RAMCounter::getVRamUsage(){
    GlobalMemoryStatusEx(&memInfo);
    return (totalVirtualMem - memInfo.ullAvailPageFile) / MB;
}

// NETWORK
using namespace std;
using namelist_t = std::vector<std::string>;

struct CounterNames { namelist_t counters, instances; };

static namelist_t NameListParser() { return namelist_t(); }

static namelist_t NameListParser(const std::string& buffer) {
    namelist_t names;
    auto iter = buffer.begin();
    do {
        std::string name;
        while (iter != buffer.end() && *iter) {
            name += *(iter++);
        }
        if (!name.empty()) {
            names.push_back(name);
        }
    } while (iter != buffer.end() && ++iter != buffer.end() && *iter);
    return names;
}

static CounterNames ListCounters(const std::string& object_name) {
    DWORD counter_list_size = 0;
    DWORD instance_list_size = 0;
    const DWORD detail_level = PERF_DETAIL_WIZARD;
    PdhEnumObjectItemsA(0, 0, object_name.c_str(), 0, &counter_list_size, 0, &instance_list_size, detail_level, 0);
    std::string counter_buf(counter_list_size, '\0');
    std::string inst_buf(instance_list_size, '\0');
    auto status = PdhEnumObjectItemsA(0, 0, object_name.c_str(), &counter_buf[0], &counter_list_size, &inst_buf[0], &instance_list_size, detail_level, 0);
    if (status != ERROR_SUCCESS) {
        return CounterNames();
    }

    auto counters = NameListParser(counter_buf);
    auto instances = NameListParser(inst_buf);

    return { counters, instances };
}

static std::string CounterPath(std::string object_name, std::string counter_name, std::string instance_name) {
    PDH_COUNTER_PATH_ELEMENTS_A path_elements = { 0 };
    path_elements.szObjectName = &object_name[0];
    path_elements.szCounterName = &counter_name[0];
    path_elements.szInstanceName = &instance_name[0];
    std::string path(PDH_MAX_COUNTER_PATH + 1, '\0');
    DWORD len = PDH_MAX_COUNTER_PATH;
    auto status = PdhMakeCounterPathA(&path_elements, &path[0], &len, 0);
    if (status != ERROR_SUCCESS) {
        std::cout << std::hex << status << '\n';
        return std::string("Error");
    }
    path.resize(len - (path[len - 1] == '\0'));
    return path;
}

NetworkCounter::NetworkCounter()
{
    PdhOpenQuery(0, 0, &hquery) == ERROR_SUCCESS || (hquery = 0);

    lastMaximum = 0.0;

    std::string name = "Network Interface";
    object_name = name;
    auto counter_names = ListCounters(name);
    if (counter_names.instances.size()) {
        std::cout << "Automatically selecting instance \"" << counter_names.instances[0] << "\"\n";
        instance_name = counter_names.instances[0];
    }

    if (!hquery) {
        std::cout << "AddCounter: Query was not successfully created\n";
        return;
    }
    if (object_name.empty()) {
        std::cout << "AddCounter: No Object Name selected\n";
        return;
    }
    if (instance_name.empty()) {
        std::cout << "AddCounter: No Instance Name selected\n";
        return;
    }

    CounterData counter_data;
    name = "Bytes Received/sec";
    counter_data.name = name;
    counter_data.path = CounterPath(object_name, name, instance_name);
    auto status = PdhAddCounterA(hquery, counter_data.path.c_str(), 0, &counter_data.hcounter);
    if (status != ERROR_SUCCESS) {
        std::cout << "AddCounter Failed: " << std::hex << status << '\n';
        return;
    }
    counter_list.push_back(counter_data);
}

double NetworkCounter::getUsage()
{
    if (counter_list.empty()) {
        std::cout << "CounterPollingDump: Nothing to do, the Counter List is empty\n";
        return 0.0;
    }
    size_t max_name_len = 0;
    for (const auto& counter : counter_list) {
        if (counter.name.length() > max_name_len) max_name_len = counter.name.length();
    }

    auto status = PdhCollectQueryData(hquery);
    if (status != ERROR_SUCCESS) {
        std::cout << "CounterPollingDump: PdhCollectQueryData failed: " << std::hex << status << '\n';
        return 0.0;
    }
    for (const auto& counter : counter_list) {
        DWORD counter_type;
        PDH_FMT_COUNTERVALUE fmt_value = { 0 };
        auto status = PdhGetFormattedCounterValue(counter.hcounter, PDH_FMT_DOUBLE, &counter_type, &fmt_value);
        if (status != ERROR_SUCCESS) {
            if (status == PDH_INVALID_DATA) {
                std::cout << " -- no data --\n";
                continue;
            }
            std::cout << "CounterPollingDump: PdhGetFormattedCounterValue failed: " << std::hex << status << '\n';
            return 0.0;
        }

        if (lastMaximum < fmt_value.doubleValue){
            lastMaximum = fmt_value.doubleValue;
        }
        return fmt_value.doubleValue;
    }
    return 0.0;
}

double NetworkCounter::getSpeed()
{
    return 0.0;
}

string NetworkCounter::getName()
{
    return instance_name;
}

double NetworkCounter::getLastMaximum()
{
    return lastMaximum;
}

// NETW IMPLEMENTATION



}

