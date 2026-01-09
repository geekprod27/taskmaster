#ifndef TYPE_CONFIGURATION_HXX
#define TYPE_CONFIGURATION_HXX

#include "type/program_rules.hxx"

namespace taskmaster {

class Configuration
{
private: // fields
    std::list<ProgramRules> m_programs;

public: // constructors
    Configuration() = default;

public: // destructor
    ~Configuration() = default;

public: // accessors
    std::list<ProgramRules> const &programs() const { return m_programs; }

public: // mutators
    void add_program_rules(
        ProgramRules const &rules
    )
    {
        m_programs.push_back(rules);
    }
};

} // namespace taskmaster

#endif
