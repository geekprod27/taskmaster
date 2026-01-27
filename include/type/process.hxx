#ifndef TYPE_PROCESS_HXX
#define TYPE_PROCESS_HXX

#include "type/exit_status.hxx"
#include <optional>
#include <sys/types.h>

namespace taskmaster {

class Process
{
public: // fields
    pid_t                     m_id;
    uint_fast8_t              m_restart_left;
    std::optional<ExitStatus> m_exit_status;
    bool                      m_started;

public: // constructors
    Process(ProgramRules const *rules);
};

} // namespace taskmaster

#endif
