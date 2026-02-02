#include "type/program.hxx"

namespace taskmaster {

/**
 * @brief Spawns the required number of processes.
 *
 * Creates child processes according to the value of
 * `m_rules.m_how_many_processes`.
 * Information about each successfully created process
 * is stored in the `m_processes` list.
 *
 * The method retries process creation on failure. If
 * `fork()` fails repeatedly, a `std::system_error`
 * exception is thrown.
 *
 * @throw std::system_error
 *        If `fork()` fails after multiple attempts.
 */
void Program::start()
{
    uint_fast8_t fail = 0;
    for (size_t i = 0; i < m_rules.m_how_many_processes; i++) {
        try {
            m_processes.emplace_back(&m_rules.m_process_rules);
        }
        catch (std::system_error &e) {
            fail++;
            i--;
            if (fail >= 4) {
                throw std::system_error();
            }
        }
    }
}

} // namespace taskmaster
