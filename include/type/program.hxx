#ifndef TYPE_PROGRAM_HXX
#define TYPE_PROGRAM_HXX

#include "type/process.hxx"
#include "type/program_rules.hxx"

namespace taskmaster {

class Program
{
private: // fields
    ProgramRules         m_rules;
    std::vector<Process> m_processes;

public: // constructors
    /// \param rules The rules of the program. (will be moved/consumed)
    ///
    Program(
        ProgramRules &&rules
    )
    : m_rules(rules)
    {}
};

} // namespace taskmaster

#endif
