#ifndef TYPE_RESTART_RULE_HXX
#define TYPE_RESTART_RULE_HXX

#include <cstdint>

namespace taskmaster {
enum class e_restart_on_exit_rule : uint_fast8_t { ALWAYS, NEVER, ON_UNEXPECTED_EXITS_ONLY };
}

#endif
