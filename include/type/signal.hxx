#ifndef TYPE_SIGNAL_HXX
#define TYPE_SIGNAL_HXX

#include <cstdint>

namespace taskmaster {

// Linux signal numbers for architectures:
// - x86
// - x64
// - ARM
// - most others
//
// Not valid for architectures:
// - Alpha/SPARC
// - MIPS
// - PA-RISC
//
enum class Signal : uint_fast8_t {
    SIGHUP    = 1,
    SIGINT    = 2,
    SIGQUIT   = 3,
    SIGILL    = 4,
    SIGTRAP   = 5,
    SIGABRT   = 6,
    SIGIOT    = 6,
    SIGBUS    = 7,
    SIGFPE    = 8,
    SIGKILL   = 9,
    SIGUSR1   = 10,
    SIGSEGV   = 11,
    SIGUSR2   = 12,
    SIGPIPE   = 13,
    SIGALRM   = 14,
    SIGTERM   = 15,
    SIGSTKFLT = 16,
    SIGCHLD   = 17,
    SIGCONT   = 18,
    SIGSTOP   = 19,
    SIGTSTP   = 20,
    SIGTTIN   = 21,
    SIGTTOU   = 22,
    SIGURG    = 23,
    SIGXCPU   = 24,
    SIGXFSZ   = 25,
    SIGVTALRM = 26,
    SIGPROF   = 27,
    SIGWINCH  = 28,
    SIGIO     = 29,
    SIGPOLL   = Signal::SIGIO,
    SIGPWR    = 30,
    SIGSYS    = 31,
    SIGUNUSED = 31,
};

} // namespace taskmaster

#endif
