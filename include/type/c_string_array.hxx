#ifndef TYPE_C_STRING_ARRAY_HXX
#define TYPE_C_STRING_ARRAY_HXX

#include <memory>

namespace taskmaster {

class CStringArray
{
private: // fields
    size_t                    m_size = 0;
    std::unique_ptr<char *[]> m_array;

public: // constructors
    CStringArray() noexcept = default;

    /// \param other The `CStringArray` to deep-copy.
    ///
    /// \exception std::bad_alloc if an internal allocation fails.
    ///
    CStringArray(CStringArray const &other);

    /// \param other The `CStringArray` to move.
    ///
    CStringArray(CStringArray &&other) noexcept;

    /// \param strings The strings to deep-copy.
    ///
    /// \exception std::bad_alloc if an internal allocation fails.
    ///
    template <typename TP_Container>
    CStringArray(TP_Container const &strings);

public: // destructor
    ~CStringArray() noexcept;

private: // methods
    /// \param other The `CStringArray` to deep-copy.
    ///
    CStringArray &assign(CStringArray other) noexcept;

public: // operators
    /// \param rhs The `CStringArray` to deep-copy.
    ///
    /// \exception std::bad_alloc if the allocation of the new CStringArray instance fails.
    ///
    CStringArray &operator=(CStringArray const &rhs);

    /// \param rhs The `CStringArray` to move.
    ///
    CStringArray &operator=(CStringArray &&rhs) noexcept;

    operator char *const *const() const;
};

} // namespace taskmaster

#endif
