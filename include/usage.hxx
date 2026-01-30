#ifndef USAGE_HXX
#define USAGE_HXX

namespace taskmaster::usage {

/// \param program_name The name of the program (usually argv[0]).
///
/// \warning `program_name` not being a valid C string is undefined behavior.
///
void print(char const *const program_name);

} // namespace taskmaster::usage

#endif
