#include "type/program.hxx"
#include "type/program_name.hxx"
#include <map>

namespace taskmaster {

void run(
    char const *const program_name __attribute__((unused)),
    char const *const configuration_file_path __attribute__((unused))
)
{
    std::map<ProgramName, Program> programs;

    // TODO: check that `configuration_file_path` is a valid POSIX compliant path,
    //       with only portable filenames. If it is relative, then transform it to absolute.

    // TODO: check that the resulting path leads to an accessible regular file.

    // TODO: open the designated file and parse the configuration from it (TOML).

    // TODO: run the monitor with `programs` as argument.
}

} // namespace taskmaster
