#ifndef TYPE_PROGRAM_RULES_HXX
#define TYPE_PROGRAM_RULES_HXX

#include "type/c_string_array.hxx"
#include "type/exit_status.hxx"
#include "type/process_counter.hxx"
#include "type/restart_attempt_counter.hxx"
#include "type/restart_on_exit_rule.hxx"
#include "type/signal.hxx"
#include <filesystem>
#include <vector>

namespace taskmaster {

struct ProgramRules {
    CStringArray              m_command_arguments;
    ProcessCounter            m_how_many_processes;
    bool                      m_must_be_started_at_launch;
    RestartOnExitRule         m_restart_on_exit_rule;
    std::vector<ExitStatus>   m_expected_exit_status; // always sorted
    std::chrono::milliseconds m_successful_start_time;
    RestartAttemptCounter     m_how_many_restart_attempts; // before aborting
    Signal                    m_graceful_stop_signal;
    std::chrono::milliseconds m_graceful_stop_time;
    std::filesystem::path     m_stdout_redirection_file;
    std::filesystem::path     m_stderr_redirection_file;
    CStringArray              m_environment;
    std::filesystem::path     m_working_directory;
    mode_t                    m_permissions_on_new_files;
};

} // namespace taskmaster

#endif
