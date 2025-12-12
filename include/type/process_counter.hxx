#ifndef TYPE_PROCESS_COUNTER_HXX
#define TYPE_PROCESS_COUNTER_HXX

#include <cstdint>

namespace taskmaster {

using ProcessCounter = uint_fast8_t;

constexpr static ProcessCounter const PROCESS_COUNTER_MAX = UINT_FAST8_MAX;

} // namespace taskmaster

#endif
