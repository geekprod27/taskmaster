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
    /// \param rules The rules of the program. (will be moved/consumed)
    ///
    Program(
        ProgramRules &&rules
    )
    : m_rules(std::move(rules))
    {}

    void start();
};

} // namespace taskmaster

#endif
