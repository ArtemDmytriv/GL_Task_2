#ifndef HEAD_H
#define HEAD_H

#define DEBUG

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <thread>
#include <memory>
#include <utility>

// globals constants
const long GB = 1073741824; // bits in GB;
const int MB = 1048576; // bits in MB;
const int KB = 1024 ; // bits in KB;

namespace win_impl {}
namespace linux_impl {}
enum class hwType{ CPU, RAM, VRAM, NETW, GPU, NONE};


// defines
#define PAUSE 1000 /* miliseconds */

#ifdef _WIN32 /* Windows headers */
#define TIME 1000 /* ms */
#include "windows.h"
#include "intrin.h"
#include "pdh.h"
#include "pdhmsg.h"
#include "include/winutils.h"
using namespace win_impl;

#elif __linux__ /* Linux headers */
#define TIME 1 /* s */
#include "unistd.h"
#include "include/linuxutil.h"
using namespace linux_impl;

#endif

#endif // HEAD_H
