#include "type/process.hxx"
#include "error.hxx"
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/wait.h>
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
    ProcessRules const &process_rules, taskmaster::RestartAttemptCounter how_many_restart_attempts
)
: m_id(fork()), m_restart_left(how_many_restart_attempts), m_started(false)
{
    if (m_id == -1) {
        throw std::system_error();
    }
    if (m_id != 0) {
        m_start_time = std::chrono::system_clock::now();
        return;
    }
    const int fd_err =
        open(process_rules.m_stderr_redirection_file.c_str(), O_WRONLY | O_CREAT | O_APPEND);
    const int fd_out =
        open(process_rules.m_stdout_redirection_file.c_str(), O_WRONLY | O_CREAT | O_APPEND);

    if (fd_err == -1 || fd_out == -1) {
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

bool Process::IsRunning() { return waitpid(m_id, &m_exit_status, WNOHANG) == 0; }

void Process::Started() { m_started = true; }

bool Process::IsStarted() { return m_started; }

ExitStatus Process::GetStatus() { return m_exit_status; }

taskmaster::RestartAttemptCounter Process::GetRestartAttemps() { return m_restart_left; }

} // namespace taskmaster

#include <list>