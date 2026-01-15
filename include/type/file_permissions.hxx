#ifndef TYPE_FILE_PERMISSION_HXX
#define TYPE_FILE_PERMISSION_HXX

#include <cstdint>

namespace taskmaster {

enum class e_file_permissions : uint_fast8_t {
    ___,
    __X,
    _W_,
    _WX,
    R__,
    R_X,
    RW_,
    RWX,
};

using t_file_permissions = struct {
    e_file_permissions user;
    e_file_permissions group;
    e_file_permissions others;
};

} // namespace taskmaster

#endif
