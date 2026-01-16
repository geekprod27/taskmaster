#ifndef TYPE_PROCESS_HXX
#define TYPE_PROCESS_HXX

#include "type/exit_status.hxx"
#include <optional>
#include <sys/types.h>

namespace taskmaster {

class Process
{
public: // fields
    pid_t const               m_id;
    std::optional<ExitStatus> m_exit_status;

public: // constructors
    Process(
        pid_t const id
    )
    : m_id(id)
    {}
};

} // namespace taskmaster

#endif
