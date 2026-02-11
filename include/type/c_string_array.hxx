#ifndef TYPE_C_STRING_ARRAY_HXX
#define TYPE_C_STRING_ARRAY_HXX

#include <cstddef>
#include <memory>

namespace taskmaster {

class CStringArray
{
private: // fields
    size_t                    m_size  = 0;
    std::unique_ptr<char *[]> m_array = std::make_unique<char *[]>(m_size + 1);

public: // constructors
    CStringArray();
    CStringArray(CStringArray const &other);
    CStringArray(CStringArray &&other) noexcept;
    template <typename TP_Container>
    CStringArray(TP_Container const &strings);

public: // destructor
    ~CStringArray() noexcept;

private: // methods
    CStringArray &assign(CStringArray other) noexcept;

public: // operators
    CStringArray &operator=(CStringArray const &rhs);
    CStringArray &operator=(CStringArray &&rhs) noexcept;
                  operator char *const *const() const;
};

} // namespace taskmaster

#include "method/c_string_array.txx"

#endif
