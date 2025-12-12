#ifndef TYPE_FILE_PERMISSION_HXX
#define TYPE_FILE_PERMISSION_HXX

#include <cstdint>

namespace taskmaster {

enum class Permissions : uint_fast8_t {
    ___,
    __X,
    _W_,
    _WX,
    R__,
    R_X,
    RW_,
    RWX,
};

using FilePermissions = struct {
    Permissions user;
    Permissions group;
    Permissions others;
};

} // namespace taskmaster

#endif
