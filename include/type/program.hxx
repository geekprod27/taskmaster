#ifndef TYPE_PROGRAM_HXX
#define TYPE_PROGRAM_HXX

#include "type/process.hxx"
#include "type/program_rules.hxx"
#include <list>

namespace taskmaster {

class Program
{
private: // fields
    ProgramRules       m_rules;
    std::list<Process> m_processes;

public: // constructors
    /// \param rules The program rules to move as part of the new `Program` instance.
    ///
    Program(
        ProgramRules &&rules
    )
    : m_rules(std::move(rules))
    {}
};

} // namespace taskmaster

#endif
