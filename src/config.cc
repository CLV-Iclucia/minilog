#include <mutex>
#include <iostream>
#include <minilog/config.h>
#include <minilog/spin-mutex.h>
namespace minilog {

static LogLevel defaultLevel = LogLevel::info;
static std::ostream &defaultOut = std::cout;
static spin_mutex levelMutex;
static spin_mutex streamMutex;
static bool threadSafe = false;

void setThreadSafety(bool safe) {
  threadSafe = safe;
}

LogLevel defaultLogLevel() {
  std::lock_guard<spin_mutex> lock(levelMutex);
  return defaultLevel;
}

void setDefaultLogLevel(LogLevel level) {
  std::lock_guard<spin_mutex> lock(levelMutex);
  defaultLevel = level;
}

void setDefaultStream(std::ostream &stream) {
  std::lock_guard<spin_mutex> lock(streamMutex);
  defaultOut.rdbuf(stream.rdbuf());
}

std::ostream &defaultStream() {
  std::lock_guard<spin_mutex> lock(streamMutex);
  return defaultOut;
}

}