#ifndef TYPE_PROGRAM_HXX
#define TYPE_PROGRAM_HXX

#include "type/process.hxx"
#include "type/program_rules.hxx"
#include <list>

#define FAIL_FORK_THROW 4

namespace taskmaster {

class Program
{
private: // fields
    ProgramRules       m_rules;
    std::list<Process> m_processes;

private: // methods
    void restart_process(RestartAttemptCounter restart_left);
    bool process_needs_to_be_or_not_to_be_restared(ExitStatus const status) const noexcept;
    void monitor_running_process(Process &current) const noexcept;
    void monitor_not_running_process(std::list<Process>::iterator const &current);

public:
    Program(ProgramRules &&rules) noexcept;

public: // methods
    void start();
    void monitor();
    bool must_be_started_at_launch();
};

} // namespace taskmaster

#endif
