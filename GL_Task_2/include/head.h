#ifndef HEAD_H
#define HEAD_H

#define DEBUG

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#ifdef _WIN32 /*Windows headers*/

#include "windows.h"
#include "include/winutils.h"

#elif __linux__ /* Linux headers */

#include "unistd.h"

#endif

#endif // HEAD_H
