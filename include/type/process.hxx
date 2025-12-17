#ifndef TYPE_PROCESS_HXX
#define TYPE_PROCESS_HXX

#include "type/program_rules.hxx"
#include <chrono>

namespace taskmaster {

using t_process = struct {

    t_program_rules const                             *m_rules;
    pid_t                                              m_pid;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    t_restart_attempt_counter                          m_how_many_restart_left;
    bool                                               succes_start;
};

} // namespace taskmaster

#endif