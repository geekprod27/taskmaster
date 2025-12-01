#ifndef TYPE_ENVIRONMENT_HXX
#define TYPE_ENVIRONMENT_HXX

#include <map>
#include <string>

namespace taskmaster {

using t_environment_variable_name  = std::string;
using t_environment_variable_value = std::string;

using t_environment = std::map<t_environment_variable_name, t_environment_variable_value>;

} // namespace taskmaster

#endif
