#include "error.hxx"
#include "run.hxx"
#include "usage.hxx"

int main(
    int const ac, char const *const *const av
)
{
    if (ac != 2) {
        taskmaster::error::print("invalid argument count");
        taskmaster::usage::print(av[0]);
        return 1;
    }
    taskmaster::run(av[0], av[1]);
    return 0;
}
