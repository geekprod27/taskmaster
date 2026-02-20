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
        case LogLevel::Debug  : return print_with_prefix("Debug", message);
        case LogLevel::Info   : return print_with_prefix("Info", message);
        case LogLevel::Warning: return print_with_prefix("Warning", message);
        case LogLevel::Error  : return print_with_prefix("Error", message);
        }
    }
    switch (level) {
    case LogLevel::Debug  : return print_with_prefix(PRETTY_DEBUG "Debug" SGR(), message);
    case LogLevel::Info   : return print_with_prefix(PRETTY_INFO "Info" SGR(), message);
    case LogLevel::Warning: return print_with_prefix(PRETTY_WARNING "Warning" SGR(), message);
    case LogLevel::Error  : return print_with_prefix(PRETTY_ERROR "Error" SGR(), message);
    }
}

} // namespace taskmaster::logger
