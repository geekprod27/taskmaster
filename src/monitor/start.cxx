#include "type/process.hxx"
#include "type/program_rules.hxx"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace taskmaster;

char **convert_map_string(
    t_environment toConvert
)
{
    char **result = new char *[toConvert.size() + 1];

    t_environment::iterator it;
    int                     i = 0;
    for (it = toConvert.begin(); it != toConvert.end(); it++) {
        std::string tmp = it->first + "=" + it->second;
        result[i]       = strdup(tmp.c_str());
        i++;
    }
    result[toConvert.size()] = nullptr;

    return result;
}

char **convert_vector_string(
    std::vector<std::string> toConvert
)
{
    char **result = new char *[toConvert.size() + 1];

    for (size_t i = 0; i < toConvert.size(); i++) {
        result[i] = strdup(toConvert[i].c_str());
    }

    result[toConvert.size()] = nullptr;

    return result;
}

t_process start_process(
    t_program_rules const *program_rules
)
{
    pid_t c_pid = fork();
    if (c_pid == -1) {
        std::cerr << "fork error" << std::endl;
        return {};
    }
    else if (c_pid == 0) {
        const int fdErr = open(
            program_rules->m_stderr_redirection_file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0755
        );
        const int fdOut = open(
            program_rules->m_stdout_redirection_file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0755
        );

        if (fdErr <= 0 || fdOut <= 0) {
            std::cerr << "open fail" << std::endl;
            exit(1);
        }

        
        dup2(fdOut, STDOUT_FILENO);
        close(fdOut);
        dup2(fdErr, STDERR_FILENO);
        close(fdErr);

        execve(
            program_rules->m_start_command.m_path.c_str(),
            convert_vector_string(program_rules->m_start_command.m_arguments),
            convert_map_string(program_rules->m_environment)
        );
        exit(0);
    }
    else {
        std::cout << "Starting process" << std::endl;
        t_process process = {program_rules, c_pid, std::chrono::steady_clock::now(), program_rules->m_how_many_restart_attempts, false};
        return process;
    }
}