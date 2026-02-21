#include "type/program.hxx"
#include "error.hxx"
#include <algorithm>
#include <iostream>

namespace taskmaster {

using namespace std::chrono;

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

void Program::restart_process(
    const RestartAttemptCounter restart_left
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

void Program::monitor_running_process(
    Process &current
) const noexcept
{
    if (!current.is_started()
        && duration_cast<milliseconds>(steady_clock::now() - current.m_start_time)
               >= m_rules.m_successful_start_time) {
        current.started();
    }
}

void Program::monitor_not_running_process(
    std::list<Process>::iterator const &current
)
{
    m_processes.erase(current);
    if (!current->is_started()) {
        RestartAttemptCounter const restart_left = current->get_restart_attemps();

        if (restart_left) {
            restart_process(restart_left - 1);
        }
        else { // TODO write in logs
            std::cout << "le nombre de restart est arriver" << std::endl;
        }
    }
    else if (process_needs_to_be_or_not_to_be_restared(current->get_status())) {
        restart_process(m_rules.m_process_rules.m_how_many_restart_attempts);
    }
}

void Program::monitor()
{
    std::list<Process>::iterator next = m_processes.begin();

    while (next != m_processes.end()) {
        std::list<Process>::iterator const current = next++;
        (current->is_running()) ? monitor_running_process(*current)
                                : monitor_not_running_process(current);
    }
}

bool Program::process_needs_to_be_or_not_to_be_restared(
    ExitStatus const status
) const noexcept
{
    return (m_rules.m_restart_on_exit_rule == RestartOnExitRule::ALWAYS)
        || (m_rules.m_restart_on_exit_rule != RestartOnExitRule::NEVER
            && std::binary_search(
                m_rules.m_expected_exit_status.begin(), m_rules.m_expected_exit_status.end(), status
            ));
}

bool Program::must_be_started_at_launch() { return m_rules.m_must_be_started_at_launch; }

// constructors
/// \param rules The rules of the program. (will be moved/consumed)
///
Program::Program(
    ProgramRules &&rules
) noexcept
: m_rules(std::move(rules))
{}

} // namespace taskmaster
