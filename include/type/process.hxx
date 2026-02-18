#ifndef TYPE_PROCESS_HXX
#define TYPE_PROCESS_HXX

#include "type/exit_status.hxx"
#include "type/process_rules.hxx"
#include <optional>
#include <sys/types.h>

namespace taskmaster {

class Process
{
public: // fields
    pid_t const                           m_id;
    RestartAttemptCounter                 m_restart_left;
    ExitStatus                            m_exit_status;
    bool                                  m_started;
    std::chrono::system_clock::time_point m_start_time;

public: // constructors
    Process(ProcessRules const &rules, taskmaster::RestartAttemptCounter how_many_restart_attempts);

public:
    bool                              IsRunning();
    void                              Started();
    bool                              GetStarted();
    ExitStatus                        GetStatus();
    taskmaster::RestartAttemptCounter GetRestartAttemps();
};

} // namespace taskmaster

#endif
