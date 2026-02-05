#ifndef TYPE_PROGRAM_RULES_HXX
#define TYPE_PROGRAM_RULES_HXX

#include "type/c_string_array.hxx"
#include "type/exit_status.hxx"
#include "type/process_counter.hxx"
#include "type/process_rules.hxx"
#include "type/restart_on_exit_rule.hxx"
#include "type/signal.hxx"

namespace taskmaster {

struct ProgramRules {
    ProcessRules              m_process_rules;
    ProcessCounter            m_how_many_processes;
    bool                      m_must_be_started_at_launch;
    RestartOnExitRule         m_restart_on_exit_rule;
    std::vector<ExitStatus>   m_expected_exit_status; // always sorted
    std::chrono::milliseconds m_successful_start_time;
    Signal                    m_graceful_stop_signal;
    std::chrono::milliseconds m_graceful_stop_time;
};

} // namespace taskmaster

#endif
