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

public:
    Program(ProgramRules &&rules) : m_rules(std::move(rules));

    void start();
};

} // namespace taskmaster

#endif
