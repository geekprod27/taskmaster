#include "type/process.hxx"
#include "error.hxx"
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

namespace taskmaster {

///  \brief Constructs a Process and initializes its execution environment.
///
/// Changes the current working directory to the one specified in
/// `ProcessRules`, then sets up standard output and standard error
/// redirection as defined by the rules.
///
/// \param process_rules Configuration rules for the process, including
///        working directory and I/O redirection.
///
/// \throw std::system_error
///        If the call to `fork()` fails.
///
Process::Process(
    ProcessRules const &process_rules
)
: m_id(fork()), m_restart_left(process_rules.m_how_many_restart_attempts), m_started(false)
{
    if (m_id == -1) {
        throw std::system_error();
    }
    if (m_id != 0) {
        return;
    }

    const int fd_err =
        open(process_rules.m_stderr_redirection_file.c_str(), O_WRONLY | O_CREAT | O_APPEND);
    const int fd_out =
        open(process_rules.m_stdout_redirection_file.c_str(), O_WRONLY | O_CREAT | O_APPEND);

    if (fd_err != -1 || fd_out != -1) {
        if (fd_err != -1) {
            close(fd_err);
        }
        if (fd_out != -1) {
            close(fd_out);
        }
        taskmaster::error::print("open fail");
        exit(EXIT_FAILURE);
    }

    if (dup2(fd_out, STDOUT_FILENO) == -1) {
        close(fd_out);
        close(fd_err);
        taskmaster::error::print("dup2 stdout fail");
        exit(EXIT_FAILURE);
    }
    close(fd_out);
    if (dup2(fd_err, STDERR_FILENO) == -1) {
        close(fd_err);
        taskmaster::error::print("dup2 stderr fail");
        exit(EXIT_FAILURE);
    }
    close(fd_err);

    if (chdir(process_rules.m_working_directory.c_str()) == -1) {
        taskmaster::error::print("chdir fail");
        exit(EXIT_FAILURE);
    }

    umask(process_rules.m_permissions_on_new_files);
    execve(
        process_rules.m_command_arguments[0],
        process_rules.m_command_arguments,
        process_rules.m_environment
    );
    taskmaster::error::print("execve fail");
    exit(EXIT_FAILURE);
}

bool Process::Monitor()
{
    int status;
    int checkprocess = waitpid(process->m_pid, &status, WNOHANG);
    if (checkprocess == 0) { // process encore en cours
        if (std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - process->m_start
            )
                .count()
            >= process->m_rules->m_successful_start_time) {
            process->succes_start = true;
        }
    }
    else {
        if (process->succes_start == false) {
            if (process->m_how_many_restart_left) {
                t_process tmp = start_process(process->m_rules);
                if (tmp.m_pid != 0) {
                    process->m_pid = tmp.m_pid;
                    process->m_how_many_restart_left--;
                }
            }
            else {
                std::cout << "le nombre de restart est arriver" << std::endl;
                return false;
            }
        }
        else if (process_need_restart(process, status)) {
            t_process tmp = start_process(process->m_rules);
            if (tmp.m_pid != 0) {
                process->m_pid = tmp.m_pid;
            }
        }
        else {
            return false;
        }
    }
    return true;
}

} // namespace taskmaster
