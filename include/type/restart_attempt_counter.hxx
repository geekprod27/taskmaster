#ifndef TYPE_RESTART_ATTEMPT_COUNTER_HXX
#define TYPE_RESTART_ATTEMPT_COUNTER_HXX

#include <cstdint>

namespace taskmaster {

using RestartAttemptCounter = uint_fast8_t;

static constexpr RestartAttemptCounter RESTART_ATTEMPT_COUNTER_MAX = UINT_FAST8_MAX;

} // namespace taskmaster

#endif
