#ifndef TYPE_PROGRAM_RULES_HXX
#define TYPE_PROGRAM_RULES_HXX

#include "type/absolute_path.hxx"
#include "type/command.hxx"
#include "type/environment.hxx"
#include "type/exit_status.hxx"
#include "type/file_permissions.hxx"
#include "type/process_counter.hxx"
#include "type/restart_attempt_counter.hxx"
#include "type/restart_on_exit_rule.hxx"
#include "type/signal.hxx"
#include <ctime>
#include <vector>

namespace taskmaster {

using t_program_rules = struct {
    t_command                  m_start_command;
    t_process_counter          m_how_many_processes;
    bool                       m_must_be_started_at_launch;
    e_restart_on_exit_rule     m_restart_on_exit_rule;
    std::vector<t_exit_status> m_expected_exit_status;
    time_t                     m_successful_start_time; // TODO: define a time measurement unit
    t_restart_attempt_counter  m_how_many_restart_attempts; // before aborting
    e_signal                   m_graceful_stop_signal;
    time_t                     m_graceful_stop_time; // TODO: define a time measurement unit
    t_absolute_path            m_stdout_redirection_file;
    t_absolute_path            m_stderr_redirection_file;
    t_environment              m_environment;
    t_absolute_path            m_working_directory;
    t_file_permissions         m_permissions_on_new_files;
};

} // namespace taskmaster

#endif
