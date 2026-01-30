#ifndef RUN_HXX
#define RUN_HXX

namespace taskmaster {

/// \param program_name The name of the program (usually argv[0]).
///
/// \param configuration_file_path The path to the configuration file.
///
/// \warning `program_name` not being a valid C string is undefined behavior.
///
/// \warning `configuration_file_path` not being a valid C string is undefined behavior.
///
void run(char const *const program_name, char const *const configuration_file_path);

} // namespace taskmaster

#endif
