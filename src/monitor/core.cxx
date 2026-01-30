#include "type/program.hxx"
#include "type/program_name.hxx"
#include <iostream>
#include <map>

namespace taskmaster {

void start_programs(
    std::map<ProgramName, Program> &progs
)
{
    for (std::map<ProgramName, Program>::iterator it = progs.begin(); it != progs.end(); ++it) {
        it->second.start();
    }
}

void monitor_programs(
    std::map<ProgramName, Program> &progs
)
{
    start_programs(progs);
    while (true) {
        // Monitoring logic would go here
    }
}

} // namespace taskmaster
