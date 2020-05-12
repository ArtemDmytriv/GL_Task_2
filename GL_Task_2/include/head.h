#ifndef HEAD_H
#define HEAD_H

#ifdef _WIN32 /*Windows headers*/
#include "windows.h"

#elif __linux__ /* Linux headers */

#include "unistd.h"

#endif

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>


#endif // HEAD_H
