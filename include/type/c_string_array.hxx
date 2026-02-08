#ifndef TYPE_C_STRING_ARRAY_HXX
#define TYPE_C_STRING_ARRAY_HXX

#include <memory>

namespace taskmaster {

class CStringArray
{
private: // fields
    size_t                    m_size  = 0;
    std::unique_ptr<char *[]> m_array = std::make_unique<char *[]>(m_size + 1);

public: // constructors
    /// \throw `std::bad_alloc` on `std::make_unique` failure.
    ///
    CStringArray();

    /// \param `other` is the `CStringArray` to deep-copy.
    ///
    /// \throw `std::bad_alloc` on `std::make_unique` failure.
    /// \throw `std::bad_alloc` on `strdup` failure.
    ///
    CStringArray(CStringArray const &other);

    /// \param `other` is the `CStringArray` to move.
    ///
    CStringArray(CStringArray &&other) noexcept;

    /// \param `strings` is the set of strings to deep-copy.
    ///
    /// \throw `std::bad_alloc` on `std::make_unique` failure.
    /// \throw `std::bad_alloc` on `std::vector::reserve` failure.
    /// \throw `std::bad_alloc` on `strdup` failure.
    /// \throw `std::length_error` on `std::vector::reserve` failure.
    ///
    template <typename TP_Container>
    CStringArray(TP_Container const &strings);

public: // destructor
    ~CStringArray() noexcept;

private: // methods
    /// \param `other` is the `CStringArray` to deep-copy.
    ///
    CStringArray &assign(CStringArray other) noexcept;

public: // operators
    /// \param `rhs` is the `CStringArray` to deep-copy.
    ///
    /// \throw `std::bad_alloc` on `CStringArray(rhs)` failure.
    ///
    CStringArray &operator=(CStringArray const &rhs);

    /// \param `rhs` is the `CStringArray` to move.
    ///
    CStringArray &operator=(CStringArray &&rhs) noexcept;

    operator char *const *const() const;
};

} // namespace taskmaster

#include "method/c_string_array.txx"

#endif
