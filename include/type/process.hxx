#ifndef TYPE_PROCESS_HXX
#define TYPE_PROCESS_HXX

#include "type/exit_status.hxx"
#include "type/program_rules.hxx"
#include <optional>
#include <sys/types.h>

namespace taskmaster {

class Process
{
public: // fields
    pid_t const               m_id;
    RestartAttemptCounter     m_restart_left;
    std::optional<ExitStatus> m_exit_status;
    bool                      m_started;

public: // constructors
    Process(ProcessRules const *rules);
};

} // namespace taskmaster

#endif
