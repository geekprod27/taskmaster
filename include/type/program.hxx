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
    void               RestartProcess(taskmaster::RestartAttemptCounter restart_left);
    bool               ProcessNeedsToBeOrNotToBeRestared(ExitStatus status);
    void               MonitorRunningProcess(Process &current);
    void               MonitorNotRunningProcess(std::list<Process>::iterator current);

public:
    Program(ProgramRules &&rules);

    void start();
    void Monitor();
    bool MustBeStartedAtLaunch();
};

} // namespace taskmaster

#endif
