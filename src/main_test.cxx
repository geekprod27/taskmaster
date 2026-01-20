#include "type/program_rules.hxx"

using namespace taskmaster;

void monitor_programs(std::vector<t_program_rules> const &program_rules);

int main() {
    t_program_rules test {
        {
            "/usr/bin/ls",
            {"ls", "-l"}
        },
        1, // process counter
        true, // must be start at launch
        taskmaster::e_restart_on_exit_rule::NEVER,
        {0}, // expected exit status
        20, // start time
        3, // restart attempt
        taskmaster::e_signal::SIGHUP, // stop signal
        1, // stop time
        "/home/nathan/taskmaster/test_out", //stdout
        "/home/nathan/taskmaster/test_err", //stderr
        {
            {"foo", "bar"}
        }, //env
        "/home/nathan/taskmaster", //work dir
        {
            taskmaster::e_file_permissions::RWX,
            taskmaster::e_file_permissions::RWX,
            taskmaster::e_file_permissions::RWX
        } // file perm
    };
    std::vector<t_program_rules> program_rules {test};
    monitor_programs(program_rules);
    return 0; 
}
