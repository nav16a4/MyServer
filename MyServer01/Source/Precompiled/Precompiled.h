//#pragma once
#ifndef PRECOMPILED_H
#define PRECOMPILED_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <exception>
#include <array>
#include <algorithm>
#include <iomanip>

#pragma comment(lib,"ws2_32")
#include <WinSock2.h>
#include <ws2tcpip.h>



/*
 * fmt library - C++20에 나올 std::format 대신 사용 
 * https://github.com/fmtlib/fmt
 * permissive MIT license
 */
#ifdef _DEBUG
#pragma comment(lib,"fmtd")
#else
#pragma comment(lib,"fmt")
#endif
//#include "ExternalLibrary/fmt/core.h"

#endif
