#include "ansi_escape_sequences.hxx"
#include <iostream>
#include <unistd.h>

#define PRETTY SGR(TEXT_BOLD FOREGROUND_BRIGHT_RED)

using std::cerr;

namespace taskmaster::error {

static inline void print_to_tty(
    char const *const error_message
)
{
    cerr << PRETTY "Error" SGR() << ": " << error_message << '\n';
}

static inline void print_to_non_tty(
    char const *const error_message
)
{
    cerr << "Error: " << error_message << '\n';
}

void print(
    char const *const error_message
)
{
    isatty(STDERR_FILENO) ? print_to_tty(error_message) : print_to_non_tty(error_message);
}

} // namespace taskmaster::error
