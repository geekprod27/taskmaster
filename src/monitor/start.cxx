#include "type/process.hxx"
#include "type/program_rules.hxx"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace taskmaster;

Process::Process(
    ProgramRules const *program_rules
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
            program_rules->m_stderr_redirection_file.c_str(),
            O_WRONLY | O_CREAT | O_APPEND,
            program_rules->m_permissions_on_new_files
        );
        const int fdOut = open(
            program_rules->m_stdout_redirection_file.c_str(),
            O_WRONLY | O_CREAT | O_APPEND,
            program_rules->m_permissions_on_new_files
        );
        umask(old);
        if (fdErr <= 0 || fdOut <= 0) {
            std::cerr << "open fail" << std::endl;
            exit(1);
        }

        dup2(fdOut, STDOUT_FILENO);
        close(fdOut);
        dup2(fdErr, STDERR_FILENO);
        close(fdErr);

        chdir(program_rules->m_working_directory.c_str());

        execve(
            program_rules->m_start_command.m_path.c_str(),
            program_rules->m_start_command.m_arguments,
            program_rules->m_environment
        );
        exit(0);
    }
    else {
        m_restart_left = program_rules->m_how_many_restart_attempts;
        m_started      = false;
    }
    return;
}