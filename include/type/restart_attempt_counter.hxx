#ifndef RESTART_ATTEMPT_COUNTER_HXX
#define RESTART_ATTEMPT_COUNTER_HXX

#include <cstdint>

namespace taskmaster {

using RestartAttemptCounter = uint_fast8_t;

constexpr static RestartAttemptCounter const RESTART_ATTEMPT_COUNTER_MAX = UINT_FAST8_MAX;

} // namespace taskmaster

#endif
