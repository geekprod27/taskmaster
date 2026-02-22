#include "logger.hxx"
#include "ansi_escape_sequences.hxx"
#include "logger/type/log_level.hxx"
#include "logger/type/log_message.hxx"
#include <iostream>
#include <unistd.h>

#define PRETTY_DEBUG   SGR(TEXT_BOLD FOREGROUND_YELLOW)
#define PRETTY_INFO    SGR(TEXT_BOLD FOREGROUND_GREEN)
#define PRETTY_WARNING SGR(TEXT_BOLD FOREGROUND_MAGENTA)
#define PRETTY_ERROR   SGR(TEXT_BOLD FOREGROUND_RED)

namespace taskmaster::logger {

static inline void print_with_prefix(
    char const *const prefix, LogMessage const &message
) noexcept
{
    std::cout << prefix << ": " << message.str() << '\n';
}

void print(
    LogLevel const level, LogMessage const &message
) noexcept
{
    if (!isatty(STDOUT_FILENO)) {
        switch (level) {
        case LogLevel::DEBUG  : return print_with_prefix("debug", message);
        case LogLevel::INFO   : return print_with_prefix("info", message);
        case LogLevel::WARNING: return print_with_prefix("warning", message);
        case LogLevel::ERROR  : return print_with_prefix("error", message);
        }
    }
    switch (level) {
    case LogLevel::DEBUG  : return print_with_prefix(PRETTY_DEBUG "debug" SGR(), message);
    case LogLevel::INFO   : return print_with_prefix(PRETTY_INFO "info" SGR(), message);
    case LogLevel::WARNING: return print_with_prefix(PRETTY_WARNING "warning" SGR(), message);
    case LogLevel::ERROR  : return print_with_prefix(PRETTY_ERROR "error" SGR(), message);
    }
}

} // namespace taskmaster::logger
