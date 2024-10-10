//
// Created by creeper on 10/10/24.
//

#ifndef MINILOG_INCLUDE_MINILOG_CONFIG_H
#define MINILOG_INCLUDE_MINILOG_CONFIG_H
#include <minilog/log-levels.h>
namespace minilog {
void setThreadSafety(bool threadSafe = true);
LogLevel defaultLogLevel();
void setDefaultLogLevel(LogLevel level);
std::ostream& defaultStream();
void setDefaultStream(std::ostream& stream);
}
#endif //MINILOG_INCLUDE_MINILOG_CONFIG_H
