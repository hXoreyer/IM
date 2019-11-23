#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <iostream>
#include <string>
#include <sys/time.h>

#define INFO 0
#define WARNING 1
#define ERROR 2
#define FATAL 3

uint64_t GetTimeStamp();
std::string GetLogLevel(int level);
void Log(int level, const std::string message, std::string file, int line);

#define LOG(level, message) Log(level, message, __FILE__, __LINE__)

#endif