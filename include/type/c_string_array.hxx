#ifndef TYPE_C_STRING_ARRAY_HXX
#define TYPE_C_STRING_ARRAY_HXX

#include <algorithm>
#include <cstring>
#include <memory>
#include <vector>

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
    CStringArray(
        TP_Container const &strings
    )
    : m_size(strings.size()), m_array(m_size ? std::make_unique<char *[]>(m_size + 1) : nullptr)
    {
        std::vector<std::unique_ptr<char, void (*)(void *)>> tmp;

        tmp.reserve(m_size);
        for (typename TP_Container::value_type const &string : strings) {
            char *const c_string = strdup(string.c_str());

            if (c_string == nullptr) {
                throw std::bad_alloc();
            }
            tmp.emplace_back(c_string, free);
        }
        *std::transform(
            tmp.begin(),
            tmp.end(),
            m_array.get(),
            [](std::unique_ptr<char, void (*)(void *)> &ptr) { return ptr.release(); }
        ) = nullptr;
    }

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
