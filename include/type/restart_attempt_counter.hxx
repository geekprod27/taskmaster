<<<<<<< HEAD
#ifndef TYPE_RESTART_ATTEMPT_COUNTER_HXX
#define TYPE_RESTART_ATTEMPT_COUNTER_HXX
=======
#ifndef RESTART_ATTEMPT_COUNTER_HXX
#define RESTART_ATTEMPT_COUNTER_HXX
>>>>>>> 27e0401 (feat: defined most of the needed types)

#include <cstdint>

namespace taskmaster {

using RestartAttemptCounter = uint_fast8_t;

static constexpr RestartAttemptCounter RESTART_ATTEMPT_COUNTER_MAX = UINT_FAST8_MAX;

} // namespace taskmaster

#endif
