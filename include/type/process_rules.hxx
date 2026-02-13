#ifndef TYPE_PROCESS_RULES_HXX
#define TYPE_PROCESS_RULES_HXX

#include "type/c_string_array.hxx"
#include "type/restart_attempt_counter.hxx"
#include <filesystem>

namespace taskmaster {

struct ProcessRules {
    mode_t                m_permissions_on_new_files;
    std::filesystem::path m_stdout_redirection_file;
    std::filesystem::path m_stderr_redirection_file;
    std::filesystem::path m_working_directory;
    CStringArray          m_command_arguments;
    CStringArray          m_environment;
    RestartAttemptCounter m_how_many_restart_attempts; // before aborting
};

} // namespace taskmaster

#endif
