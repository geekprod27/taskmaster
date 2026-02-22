#ifndef LOGGER_TYPE_LOG_LEVEL_HXX
#define LOGGER_TYPE_LOG_LEVEL_HXX

#include <cstdint>

namespace taskmaster::logger {

enum LogLevel : uint_fast8_t {
    DEBUG,
    INFO,
    WARNING,
    ERROR,

    COUNT
};

} // namespace taskmaster::logger

#endif
