#ifndef TYPE_PROCESS_HXX
#define TYPE_PROCESS_HXX

#include "type/program_rules.hxx"

namespace taskmaster {

using t_process = struct {

  t_program_rules const *m_rules;
  pid_t m_pid;
  t_restart_attempt_counter m_how_many_restart_left;
};

} // namespace taskmaster

#endif