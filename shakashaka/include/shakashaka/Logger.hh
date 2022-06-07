#ifndef AI_LOGGER_NAME_HH
#define AI_LOGGER_NAME_HH
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#pragma GCC diagnostic pop
#include <optional>
#include <string>

namespace shakashaka::logger
{
struct LoggerProperties
{
    std::string loggerName;
    std::optional<std::string> loggerOutputFile;
};
const auto defaultLoggerFormat =
    "[%Y-%m-%d %H:%M:%S:%e:%f %z] [%n] [%l] [process "
    "%P] [thread %t] [source %s] [function %!] [line %#] %v";
const auto shakashaka =
    LoggerProperties{"shakashaka_logger", "logs/shakashaka_logger.log"};
} // namespace shakashaka::logger
#endif // AI_LOGGER_NAME_HH
