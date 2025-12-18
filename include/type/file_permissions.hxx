#ifndef TYPE_FILE_PERMISSION_HXX
#define TYPE_FILE_PERMISSION_HXX

#include <cstdint>

namespace taskmaster {

enum class e_file_permissions : uint_fast8_t {
    ___ = 0,
    __X = 1,
    _W_ = 2,
    _WX = 3,
    R__ = 4,
    R_X = 5,
    RW_ = 6,
    RWX = 7,
};

using t_file_permissions = struct {
    e_file_permissions user;
    e_file_permissions group;
    e_file_permissions others;
};

} // namespace taskmaster

#endif
