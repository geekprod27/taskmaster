#ifndef TYPE_C_STRING_ARRAY_HXX
#define TYPE_C_STRING_ARRAY_HXX

#include <algorithm>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

namespace taskmaster {

class CStringArray
{
private: // fields
    size_t                    m_size;
    std::unique_ptr<char *[]> m_array;

public: // constructors
    constexpr CStringArray() noexcept : m_size(), m_array() {}

    /// \param other The `CStringArray` to deep-copy.
    ///
    /// \exception std::bad_alloc if an internal allocation fails.
    ///
    CStringArray(
        CStringArray const &other
    )
    : m_size(other.m_size), m_array(std::make_unique<char *[]>(m_size + 1))
    {
        std::vector<std::unique_ptr<char, void (*)(void *)>> tmp;

        tmp.reserve(m_size);
        for (size_t i = 0; i < m_size; ++i) {
            char *const c_string = strdup(other.m_array[i]);

            if (c_string == nullptr) {
                throw std::bad_alloc();
            }
            tmp.emplace_back(c_string, free);
        }
        std::transform(
            tmp.begin(),
            tmp.end(),
            m_array.get(),
            [](std::unique_ptr<char, void (*)(void *)> &ptr) { return ptr.release(); }
        );
        m_array[m_size] = nullptr;
    }

    /// \param other The `CStringArray` to move.
    ///
    CStringArray(
        CStringArray &&other
    ) noexcept
    : m_size(std::move(other.m_size)), m_array(std::move(other.m_array))
    {
        other.m_size = 0;
    }

    /// \param strings The strings to deep-copy.
    ///
    /// \exception std::bad_alloc if an internal allocation fails.
    ///
    /// \warning `TP_Container` not being a standard container of `std::string`s
    ///          is undefined behavior.
    ///
    template <typename TP_Container>
    CStringArray(
        TP_Container const &strings
    )
    : m_size(strings.size()), m_array(std::make_unique<char *[]>(m_size + 1))
    {
        std::vector<std::unique_ptr<char, void (*)(void *)>> tmp;

        tmp.reserve(m_size);
        for (std::string const &string : strings) {
            char *const c_string = strdup(string.c_str());

            if (c_string == nullptr) {
                throw std::bad_alloc();
            }
            tmp.emplace_back(c_string, free);
        }
        std::transform(
            tmp.begin(),
            tmp.end(),
            m_array.get(),
            [](std::unique_ptr<char, void (*)(void *)> &ptr) { return ptr.release(); }
        );
        m_array[m_size] = nullptr;
    }

public: // destructor
    ~CStringArray() noexcept { std::for_each(m_array.get(), m_array.get() + m_size, free); }

private: // methods
    CStringArray &assign(
        CStringArray other
    ) noexcept
    {
        std::swap(m_size, other.m_size);
        std::swap(m_array, other.m_array);
        return *this;
    }

public: // operators
    /// \exception std::bad_alloc if the allocation of the new CStringArray instance fails.
    ///
    CStringArray &operator=(
        CStringArray const &rhs
    )
    {
        return assign(rhs);
    }

    CStringArray &operator=(
        CStringArray &&rhs
    ) noexcept
    {
        return assign(std::move(rhs));
    }

    operator char *const *const() const { return m_array.get(); }
};

} // namespace taskmaster

#endif
