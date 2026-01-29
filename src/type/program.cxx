#include "type/program.hxx"

using namespace taskmaster;

void Program::start(
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