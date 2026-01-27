#include "type/process.hxx"
#include "type/program.hxx"
#include <iostream>
#include <vector>

using namespace taskmaster;

void Program::Start(
    void
)
{
    for (size_t i = 0; i < m_rules.m_how_many_processes; i++) {
        Process tmp(&m_rules);

        if (tmp.m_id != 0) {
            m_processes.push_back(tmp);
        }
    }
}

void start_programs(
    std::map<std::string, Program> progs
)
{
    for (std::map<std::string, Program>::iterator it = progs.begin(); it != progs.end(); ++it) {
        it->second.Start();
    }
}

void monitor_programs(
    std::map<std::string, Program> progs
)
{
    start_programs(progs);
    while (true) {
        // Monitoring logic would go here
    }
}
