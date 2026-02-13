#ifndef TYPE_COMMAND_HXX
#define TYPE_COMMAND_HXX

#include "type/absolute_path.hxx"
#include "type/exit_status.hxx"
#include <vector>

namespace taskmaster {

using t_command = struct {
    t_absolute_path          m_path;
    std::vector<std::string> m_arguments;
};

} // namespace taskmaster

#endif
