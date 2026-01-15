#ifndef TYPE_RESTART_ON_EXIT_RULE_HXX
#define TYPE_RESTART_ON_EXIT_RULE_HXX

#include <cstdint>

namespace taskmaster {

enum class RestartOnExitRule : uint_fast8_t { ALWAYS, NEVER, ON_UNEXPECTED_EXITS_ONLY };

} // namespace taskmaster

#endif
