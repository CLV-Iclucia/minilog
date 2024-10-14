//
// Created by creeper on 10/10/24.
//

#ifndef MINILOG_INCLUDE_MINILOG_LOGGER_H
#define MINILOG_INCLUDE_MINILOG_LOGGER_H
#include <ostream>
#include <fstream>
#include <format>
#include <filesystem>
#include <minilog/config.h>
#include <minilog/properties.h>
#include <minilog/log-levels.h>
namespace minilog {
struct Logger : RAII {
  explicit Logger(std::ostream &stream = defaultStream(), LogLevel level = defaultLogLevel()) : stream(stream), level(level) {}
  explicit Logger(std::unique_ptr<std::ostream> stream, LogLevel level = defaultLogLevel()) : stream(std::move(stream)), level(level) {}

#define GENERATE_LOGGING_METHOD(LEVEL) \
    Logger& LEVEL(const std::string& message) { \
        if (level <= LogLevel::LEVEL) { \
        outStream() << std::format("[{}]: {}\n", #LEVEL, message); \
        }                              \
        return *this;                  \
        }

#define GENERATE_FMT_LOGGING_METHOD(LEVEL) \
    template <typename... Args>                                   \
    Logger& LEVEL(std::format_string<Args...> fmt, Args&&... args) { \
        if (level <= LogLevel::LEVEL) { \
        outStream() << "["#LEVEL"]: " << std::format(std::move(fmt), std::forward<Args>(args)...) << "\n"; \
        }                              \
        return *this;                  \
        }

  FOR_EACH_LOG_LEVEL(GENERATE_FMT_LOGGING_METHOD)
  FOR_EACH_LOG_LEVEL(GENERATE_LOGGING_METHOD)

  Logger& setLogLevel(LogLevel newLevel) {
    level = newLevel;
    return *this;
  }

  std::ostream& outStream() {
    if (std::holds_alternative<std::unique_ptr<std::ostream>>(stream)) {
      return *std::get<std::unique_ptr<std::ostream>>(stream);
    } else {
      return std::get<std::reference_wrapper<std::ostream>>(stream);
    }
  }

protected:
  std::variant<std::reference_wrapper<std::ostream>, std::unique_ptr<std::ostream>> stream;
  LogLevel level;
};

#undef GENERATE_LOGGING_METHOD
#undef GENERATE_FMT_LOGGING_METHOD

#define GENERATE_QUICK_FMT_LOGGING_FUNCTION(LEVEL) \
    template <typename... Args> \
    void LEVEL(std::format_string<Args...> fmt, Args&&... args) { \
        Logger().LEVEL(std::move(fmt), std::forward<Args>(args)...); \
    }

#define GENERATE_QUICK_LOGGING_FUNCTION(LEVEL) \
    void LEVEL(const std::string& message) { \
        Logger().LEVEL(message); \
    }

FOR_EACH_LOG_LEVEL(GENERATE_QUICK_FMT_LOGGING_FUNCTION)
FOR_EACH_LOG_LEVEL(GENERATE_QUICK_LOGGING_FUNCTION)
#undef GENERATE_QUICK_LOGGING_FUNCTION
#undef GENERATE_QUICK_FMT_LOGGING_FUNCTION

std::unique_ptr<Logger> createFileLogger(const std::filesystem::path &path, LogLevel level = defaultLogLevel()) {
  auto file = std::make_unique<std::ofstream>(path);
  return std::make_unique<Logger>(std::move(file), level);
}
}
#endif //MINILOG_INCLUDE_MINILOG_LOGGER_H
