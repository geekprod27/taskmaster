#include "type/program.hxx"
#include "type/program_name.hxx"
#include <iostream>
#include <map>

namespace taskmaster {

///
/// Spawns processes for all programs.
///
/// Iterates over the given map of programs and calls
/// `Program::start()` for each entry.
///
/// This function does not handle errors internally.
/// Any `std::system_error` thrown by `Program::start()`
/// is propagated to the caller.
///
/// \param programs Map of program names to Program instances.
///
/// \throw std::system_error
///        If process creation fails for any program.
///
void start_programs(
    std::map<ProgramName, Program> &programs
)
{
    for (auto &[program_name, program] : programs) {
        program.start();
    }
}

/// Spawns and monitors all programs.
///
/// Calls `start_programs()` to create the processes for each
/// program in the map, then monitors their execution.
///
///  \param programs Map of program names to Program instances.
///
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
