#include "ansi_escape_sequences.hxx"
#include <iostream>
#include <unistd.h>

#define PRETTY SGR(TEXT_BOLD FOREGROUND_BRIGHT_YELLOW)

using std::cerr;

namespace taskmaster::usage {

/// \param program_name The name of the program (usually argv[0]).
///
/// \warning `program_name` not being a valid C string is undefined behavior.
///
static inline void print_to_tty(
    char const *const program_name
)
{
    cerr << PRETTY "Usage" SGR() << ": " << program_name << " <configuration_file>\n";
}

/// \param program_name The name of the program (usually argv[0]).
///
/// \warning `program_name` not being a valid C string is undefined behavior.
///
static inline void print_to_non_tty(
    char const *const program_name
)
{
    cerr << "Usage: " << program_name << " <configuration_file>\n";
}

/// \param program_name The name of the program (usually argv[0]).
///
/// \warning `program_name` not being a valid C string is undefined behavior.
///
void print(
    char const *const program_name
)
{
    isatty(STDERR_FILENO) ? print_to_tty(program_name) : print_to_non_tty(program_name);
}

} // namespace taskmaster::usage
