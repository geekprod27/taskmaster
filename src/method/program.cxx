#include "type/program.hxx"
#include "error.hxx"
#include <algorithm>
#include <iostream>

namespace taskmaster {

/// \brief Spawns the required number of processes.
///
/// Creates child processes according to the value of
/// `m_rules.m_how_many_processes`.
/// Information about each successfully created process
/// is stored in the `m_processes` list.
///
/// \throw std::system_error
/// If `fork()` fails after multiple attempts.
///
void Program::start()
{
    uint_fast8_t fail = 0;

    for (size_t i = 0; i < m_rules.m_how_many_processes; i++) {
        try {
            m_processes.emplace_back(
                m_rules.m_process_rules, m_rules.m_process_rules.m_how_many_restart_attempts
            );
        }
        catch (std::system_error const &e) {
            fail++;
            if (fail >= FAIL_FORK_THROW) {
                throw;
            }
            i--;
        }
    }
}

void Program::RestartProcess(
    taskmaster::RestartAttemptCounter restart_left
)
{
    uint_fast8_t fail = 0;
retry_after_fork_fail:
    try {
        m_processes.emplace_back(m_rules.m_process_rules, restart_left);
    }
    catch (std::system_error const &e) {
        fail++;
        if (fail >= FAIL_FORK_THROW) {
            throw;
        }
        goto retry_after_fork_fail;
    }
}

void Program::MonitorRunningProcess(
    Process &current
)
{
    if (!current.IsStarted()
        && std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now() - current.m_start_time
           ) >= m_rules.m_successful_start_time) {
        current.Started();
    }
}

void Program::MonitorNotRunningProcess(
    std::list<Process>::iterator current
)
{
    // std::cerr << current->IsStarted() << std::endl;
    if (!current->IsStarted()) {
        taskmaster::RestartAttemptCounter restart_left = current->GetRestartAttemps();
        if (restart_left) {
            m_processes.erase(current);
            RestartProcess(restart_left - 1);
        }
        else { // TODO write in logs
            m_processes.erase(current);
            std::cout << "le nombre de restart est arriver" << std::endl;
        }
    }
    else if (ProcessNeedsToBeOrNotToBeRestared(current->GetStatus())) {
        m_processes.erase(current);
        RestartProcess(m_rules.m_process_rules.m_how_many_restart_attempts);
    }
}

void Program::Monitor()
{
    std::list<Process>::iterator next = m_processes.begin();

    while (next != m_processes.end()) {
        std::list<Process>::iterator const current = next++;
        if (current->IsRunning()) {
            // std::cerr << "run" << std::endl;
            MonitorRunningProcess(*current);
        }
        else {
            // std::cerr << "not run" << std::endl;
            MonitorNotRunningProcess(current);
        }
    }
}

bool Program::ProcessNeedsToBeOrNotToBeRestared(
    ExitStatus status
)
{
    if (m_rules.m_restart_on_exit_rule == RestartOnExitRule::ALWAYS) {
        return true;
    }
    else if (m_rules.m_restart_on_exit_rule == RestartOnExitRule::NEVER) {
        return false;
    }
    return std::binary_search(
        m_rules.m_expected_exit_status.begin(), m_rules.m_expected_exit_status.end(), status
    );
}

bool Program::MustBeStartedAtLaunch() { return m_rules.m_must_be_started_at_launch; }

// constructors
/// \param rules The rules of the program. (will be moved/consumed)
///
Program::Program(
    ProgramRules &&rules
)
: m_rules(std::move(rules))
{}

} // namespace taskmaster
