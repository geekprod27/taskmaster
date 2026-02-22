#include "logger.hxx"
#include "ansi_escape_sequences.hxx"
#include "logger/type/log_level.hxx"
#include "logger/type/log_message.hxx"
#include <iostream>
#include <unistd.h>

namespace taskmaster::logger {

constexpr struct {
    char const *const m_text;
    char const *const m_pretty;
} PREFIXES[LogLevel::COUNT] = {
    [LogLevel::DEBUG]   = {.m_text = "debug",   .m_pretty = SGR(TEXT_BOLD FOREGROUND_YELLOW) },
    [LogLevel::INFO]    = {.m_text = "info",    .m_pretty = SGR(TEXT_BOLD FOREGROUND_GREEN)  },
    [LogLevel::WARNING] = {.m_text = "warning", .m_pretty = SGR(TEXT_BOLD FOREGROUND_MAGENTA)},
    [LogLevel::ERROR]   = {.m_text = "error",   .m_pretty = SGR(TEXT_BOLD FOREGROUND_RED)    },
};

void print(
    LogLevel const level, LogMessage const &message
) noexcept
{
    using std::cout;

    isatty(STDOUT_FILENO) && cout << PREFIXES[level].m_pretty;
    cout << PREFIXES[level].m_text;
    isatty(STDOUT_FILENO) && cout << SGR();
    cout << ": " << message.str() << '\n';
}

} // namespace taskmaster::logger
