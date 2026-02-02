#include "type/program.hxx"
#include "type/program_name.hxx"
#include <iostream>
#include <map>

namespace taskmaster {

void start_programs(
    std::map<ProgramName, Program> &programs
)
{
    for (auto &[program_name, program] : programs) {
        program.start();
    }
}

void start_and_monitor_programs(
    std::map<ProgramName, Program> &programs
)
{
    start_programs(programs);
    while (true) {
        // Monitoring logic would go here
    }
}

} // namespace taskmaster
