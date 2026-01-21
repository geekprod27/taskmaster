#ifndef TYPE_ABSOLUTE_PATH_HXX
#define TYPE_ABSOLUTE_PATH_HXX

#include <stdexcept>
#include <string>

namespace taskmaster {

class AbsolutePath
{
private: // fields
    std::string m_path;

public: // constructors
    /// \param s The string representing the absolute path. (will be moved/consumed)
    ///
    /// \warning `s` not being a POSIX compliant absolute path is undefined behavior.
    ///
    AbsolutePath(
        std::string &&s
    )
    : m_path(std::move(s))
    {}

    /// \param other The `AbsolutePath` instance to copy.
    ///
    AbsolutePath(AbsolutePath const &other) = default;

    /// \param other The `AbsolutePath` instance to move.
    ///
    AbsolutePath(AbsolutePath &&other) = default;

public: // destructor
    ~AbsolutePath() = default;

private: // methods
    bool exists_on_filesystem() const __attribute__((unavailable("not implemented yet")));

    bool is_regular_file() const __attribute__((unavailable("not implemented yet")));

public: // methods
    /// https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap03.html
    bool is_posix_compliant() const __attribute__((unavailable("not implemented yet")));

public: // operators
    /// \param s The string representing the absolute path. (will be moved/consumed)
    ///
    /// \warning `s` not being a POSIX
    ///
    AbsolutePath &operator=(
        std::string &&s
    )
    {
        m_path = std::move(s);
        return *this;
    }

    AbsolutePath &operator=(AbsolutePath const &other) = default;

    AbsolutePath &operator=(AbsolutePath &&other) = default;
};

} // namespace taskmaster

#endif
