#ifndef TYPE_ABSOLUTE_PATH
#define TYPE_ABSOLUTE_PATH

#include <string>

namespace taskmaster {

class AbsolutePath : public std::string
{

public: // constructors
    AbsolutePath() = default;

public: // destructor
    ~AbsolutePath() = default;

private: // methods
    bool is_syntactically_valid() const __attribute__((unavailable("not implemented yet")));
    bool is_accessible() const __attribute__((unavailable("not implemented yet")));
    bool is_regular_file() const __attribute__((unavailable("not implemented yet")));
};

} // namespace taskmaster

#endif
