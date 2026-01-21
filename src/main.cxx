#include "error.hxx"
#include "run.hxx"
#include "usage.hxx"
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

int main(
    int const ac, char const *const *const av
)
{
    if (ac != 2) {
        taskmaster::error::print("invalid argument count");
        taskmaster::usage::print(av[0]);
        exit(EXIT_FAILURE);
    }
    taskmaster::run(av[0], av[1]);
}
