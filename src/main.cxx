#include "logger.hxx"
#include "logger/type/log_level.hxx"
#include "logger/type/log_message.hxx"
#include "run.hxx"
#include "usage.hxx"

using namespace taskmaster;

int main(
    int const ac, char const *const *const av
)
{
    if (ac != 2) {
        logger::print(logger::LogLevel::Error, logger::LogMessage("invalid argument count"));
        usage::print(av[0]);
        return 1;
    }
    taskmaster::run(av[0], av[1]);
    return 0;
}
