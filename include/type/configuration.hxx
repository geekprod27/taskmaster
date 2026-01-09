#ifndef TYPE_CONFIGURATION_HXX
#define TYPE_CONFIGURATION_HXX

#include "type/program_rules.hxx"

namespace taskmaster {

class Configuration : public std::list<ProgramRules>
{

public: // contructors
    Configuration() = default;

public: // destructor
    ~Configuration() = default;
};

} // namespace taskmaster

#endif
