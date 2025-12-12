#include "type/process.hxx"
#include "type/program_rules.hxx"
#include <iostream>
#include <vector>

using namespace taskmaster;

t_process start_process(t_program_rules const *program_rules);

void start_program(std::vector<t_process> *process, t_program_rules const *program_rules)
{
    for (size_t i = 0; i < program_rules->m_how_many_processes; i++) {
        t_process tmp;
        
        tmp = start_process(program_rules);
        if (tmp.m_pid != 0)
        {
            process->push_back(tmp);
        }
    }
}


void monitor_programs(std::vector<t_program_rules> const &program_rules) 
{
    std::vector<t_process> process;
    for (size_t i = 0; i < program_rules.size(); i++) {
        if (program_rules[i].m_must_be_started_at_launch)
        {
            start_program(&process, &program_rules[i]);
        }
    }
}
