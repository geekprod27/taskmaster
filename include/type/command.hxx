#ifndef TYPE_COMMAND_HXX
#define TYPE_COMMAND_HXX

#include "type/absolute_path.hxx"
#include <vector>

namespace taskmaster {

struct Command {
    AbsolutePath             m_path;
    std::vector<std::string> m_arguments;
};

} // namespace taskmaster

#endif
