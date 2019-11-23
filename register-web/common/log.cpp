#include "log.h"

uint64_t GetTimeStamp()
{
    struct timeval timeval_;
    gettimeofday(&timeval_, NULL);
    return timeval_.tv_sec;
}

std::string GetLogLevel(int level)
{
    switch(level)
    {
        case 0: return "INFO";
                break;
        case 1: return "WARNING";
                break;
        case 2: return "ERROR";
                break;
        case 3: return "FARAL";
                break;
        default:return "UNKNOWN";
                break; 
    }
}

void Log(int level, const std::string message, std::string file, int line)
{
    printf("[%ld:%s] [%s] (%s:%d)\n", GetTimeStamp(), GetLogLevel(level).c_str(), \
            message.c_str(), file.c_str(), line);
}