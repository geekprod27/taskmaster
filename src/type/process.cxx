#include "type/process.hxx"
#include "type/process_rules.hxx"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace taskmaster;

Process::Process(
    ProcessRules const *process_rules
)
{
    m_id = fork();
    if (m_id == -1) {
        std::cerr << "fork error" << std::endl;
        return;
    }
    else if (m_id == 0) {
        mode_t    old   = umask(0);
        const int fdErr = open(
            process_rules->m_stderr_redirection_file.c_str(),
            O_WRONLY | O_CREAT | O_APPEND,
            process_rules->m_permissions_on_new_files
        );
        const int fdOut = open(
            process_rules->m_stdout_redirection_file.c_str(),
            O_WRONLY | O_CREAT | O_APPEND,
            process_rules->m_permissions_on_new_files
        );
        umask(old);
        if (fdErr <= 0 || fdOut <= 0) {
            std::cerr << "open fail" << std::endl;
            exit(1);
        }

        if (dup2(fdOut, STDOUT_FILENO) == -1) {
            std::cerr << "dup2 stdout fail" << std::endl;
            exit(1);
        }
        close(fdOut);
        if (dup2(fdErr, STDERR_FILENO) == -1) {
            std::cerr << "dup2 stderr fail" << std::endl;
            exit(1);
        }
        close(fdErr);

        if (chdir(process_rules->m_working_directory.c_str()) == -1) {
            std::cerr << "chdir fail" << std::endl;
            exit(1);
        }

        execve(
            process_rules->m_command_arguments[0],
            process_rules->m_command_arguments,
            process_rules->m_environment
        );
        exit(1);
    }
    else {
        m_restart_left = process_rules->m_how_many_restart_attempts;
        m_started      = false;
    }
    return;
}
