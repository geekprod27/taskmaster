#ifndef TYPE_ENVIRONMENT_HXX
#define TYPE_ENVIRONMENT_HXX

#include <map>
#include <string>

namespace taskmaster {

using EnvironmentVariableName  = std::string;
using EnvironmentVariableValue = std::string;
using Environment              = std::map<EnvironmentVariableName, EnvironmentVariableValue>;

} // namespace taskmaster

#endif
