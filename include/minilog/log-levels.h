#ifndef MINILOG_INCLUDE_MINILOG_LOG_LEVELS_H
#define MINILOG_INCLUDE_MINILOG_LOG_LEVELS_H

namespace minilog {

#define FOR_EACH_LOG_LEVEL(LEVEL) \
    LEVEL(trace) \
    LEVEL(debug) \
    LEVEL(info) \
    LEVEL(warn) \
    LEVEL(error) \
    LEVEL(fatal)

#define GENERATE_ENUM(ENUM) ENUM,
enum class LogLevel {
  FOR_EACH_LOG_LEVEL(GENERATE_ENUM)
};
#undef GENERATE_ENUM
}

#endif //MINILOG_LIBRARY_H
