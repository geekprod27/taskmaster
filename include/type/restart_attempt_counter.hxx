#ifndef RESTART_ATTEMPT_COUNTER_HXX
#define RESTART_ATTEMPT_COUNTER_HXX

#include <cstdint>

namespace taskmaster {

using t_restart_attempt_counter = uint_fast8_t;

constexpr static t_restart_attempt_counter const RESTART_ATTEMPT_COUNTER_MAX = UINT_FAST8_MAX;

} // namespace taskmaster

#endif
