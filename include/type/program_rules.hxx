#ifndef TYPE_PROGRAM_RULES_HXX
#define TYPE_PROGRAM_RULES_HXX

#include "type/command.hxx"
#include "type/environment.hxx"
#include "type/exit_status.hxx"
#include "type/process_counter.hxx"
#include "type/restart_attempt_counter.hxx"
#include "type/restart_on_exit_rule.hxx"
#include "type/signal.hxx"
#include <chrono>

namespace taskmaster {

struct ProgramRules {
    Command                   m_start_command;
    ProcessCounter            m_how_many_processes;
    bool                      m_must_be_started_at_launch;
    RestartOnExitRule         m_restart_on_exit_rule;
    std::vector<ExitStatus>   m_expected_exit_status; // always sorted
    std::chrono::milliseconds m_successful_start_time;
    RestartAttemptCounter     m_how_many_restart_attempts; // before aborting
    Signal                    m_graceful_stop_signal;
    std::chrono::milliseconds m_graceful_stop_time;
    AbsolutePath              m_stdout_redirection_file;
    AbsolutePath              m_stderr_redirection_file;
    Environment               m_environment;
    AbsolutePath              m_working_directory;
    mode_t                    m_permissions_on_new_files;
};

} // namespace taskmaster

#endif
