#include "type/process.hxx"
#include "type/process_rules.hxx"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace taskmaster {

Process::Process(
    ProcessRules const *process_rules
)
: m_restart_left(process_rules->m_how_many_restart_attempts), m_started(false)
{
    m_id = fork();
    if (m_id == -1) {
        std::cerr << "fork error" << std::endl;
        return;
    }
    if (m_id == 0) {
        mode_t const    old   = umask(0);
        const int fd_err = open(
            process_rules->m_stderr_redirection_file.c_str(),
            O_WRONLY | O_CREAT | O_APPEND,
            process_rules->m_permissions_on_new_files
        );
        const int fd_out = open(
            process_rules->m_stdout_redirection_file.c_str(),
            O_WRONLY | O_CREAT | O_APPEND,
            process_rules->m_permissions_on_new_files
        );
        umask(old);
        if (fd_err <= 0 || fd_out <= 0) {
            std::cerr << "open fail" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (dup2(fd_out, STDOUT_FILENO) == -1) {
            std::cerr << "dup2 stdout fail" << std::endl;
            exit(EXIT_FAILURE);
        }
        close(fd_out);
        if (dup2(fd_err, STDERR_FILENO) == -1) {
            std::cerr << "dup2 stderr fail" << std::endl;
            exit(EXIT_FAILURE);
        }
        close(fd_err);

        if (chdir(process_rules->m_working_directory.c_str()) == -1) {
            std::cerr << "chdir fail" << std::endl;
            exit(EXIT_FAILURE);
        }

        execve(
            process_rules->m_command_arguments[0],
            process_rules->m_command_arguments,
            process_rules->m_environment
        );
        exit(EXIT_FAILURE);
    }
}

} // namespace taskmaster
