#ifndef TYPE_LOGGER_HXX
#define TYPE_LOGGER_HXX

#include "logger/type/log_level.hxx"
#include "logger/type/log_message.hxx"

namespace taskmaster::logger {

void print(LogLevel const level, LogMessage const &message) noexcept;

} // namespace taskmaster::logger

#endif
