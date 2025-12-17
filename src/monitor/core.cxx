#include "type/process.hxx"
#include "type/program_rules.hxx"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace taskmaster;

t_process start_process(t_program_rules const *program_rules);

void start_program(
    std::vector<t_process> *process, t_program_rules const *program_rules
)
{
    for (size_t i = 0; i < program_rules->m_how_many_processes; i++) {
        t_process tmp;

        tmp = start_process(program_rules);
        if (tmp.m_pid != 0) {
            process->push_back(tmp);
        }
    }
}

bool process_need_restart(
    t_process *process, int status
)
{
    if (process->m_rules->m_restart_on_exit_rule == taskmaster::e_restart_on_exit_rule::ALWAYS) {
        return true;
    }
    else if (process->m_rules->m_restart_on_exit_rule
             == taskmaster::e_restart_on_exit_rule::NEVER) {
        return false;
    }
    return std::find(
               process->m_rules->m_expected_exit_status.begin(),
               process->m_rules->m_expected_exit_status.end(),
               status
           )
        == process->m_rules->m_expected_exit_status.end();
}

bool monitor_process(
    t_process *process
)
{
    int status;
    int checkprocess = waitpid(process->m_pid, &status, WNOHANG);
    if (checkprocess == 0) { // process encore en cours
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - process->m_start).count()
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
            } else {
                std::cout << "le nombre de restart est arriver" << std::endl;
                return false;
            }
        }
        else if (process_need_restart(process, status)) {
            t_process tmp = start_process(process->m_rules);
            if (tmp.m_pid != 0) {
                process->m_pid = tmp.m_pid;
            }
        } else {
            return false;
        }
    }
    return true;
}

void monitor_programs(
    std::vector<t_program_rules> const &program_rules
)
{
    std::vector<t_process> process;
    for (size_t i = 0; i < program_rules.size(); i++) {
        if (program_rules[i].m_must_be_started_at_launch) {
            start_program(&process, &program_rules[i]);
        }
    }
    while (true) {
        for (size_t i = 0; i < process.size(); i++) {
            if (monitor_process(&process[i]) == false) {
                process.erase(process.begin() + i);
            }
        }
    }
}
