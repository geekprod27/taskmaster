#ifndef TYPE_PROGRAM_HXX
#define TYPE_PROGRAM_HXX

#include "type/process.hxx"
#include "type/program_rules.hxx"

namespace taskmaster {

class Program
{

private: // fields
    ProgramRules const &m_rules;
    std::list<Process>  m_processes;

public: // constructors
    Program(
        ProgramRules const &rules
    )
    : m_rules(rules)
    {}
};

} // namespace taskmaster

#endif
