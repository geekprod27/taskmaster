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
    RestartAttemptCounter const           m_restart_left;
    ExitStatus                            m_exit_status;
    bool                                  m_started;
    std::chrono::steady_clock::time_point m_start_time;

public: // constructors
    Process(ProcessRules const &rules, const RestartAttemptCounter how_many_restart_attempts);

public:
    bool                  is_running() noexcept;
    void                  started() noexcept;
    bool                  is_started() const noexcept;
    ExitStatus            get_status() const noexcept;
    RestartAttemptCounter get_restart_attemps() const noexcept;
};

} // namespace taskmaster

#endif
