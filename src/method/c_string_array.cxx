#include "type/c_string_array.hxx"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <new>
#include <ranges>
#include <span>
#include <string.h>
#include <utility>
#include <vector>

namespace taskmaster {

/// \throw std::bad_alloc on `std::make_unique` failure.
///
CStringArray::CStringArray() { m_array[0] = nullptr; }

/// \param other is the `CStringArray` to deep-copy.
///
/// \throw std::bad_alloc    on `std::make_unique`     failure.
/// \throw std::bad_alloc    on `std::vector::reserve` failure.
/// \throw std::bad_alloc    on `strdup`               failure.
/// \throw std::length_error on `std::vector::reserve` failure.
///
CStringArray::CStringArray(
    CStringArray const &other
)
: m_size(other.m_size)
{
    std::vector<std::unique_ptr<char, void (*)(void *)>> tmp;

    tmp.reserve(m_size);
    for (char const *const other_c_string : std::span{other.m_array.get(), m_size}) {
        char *const c_string = strdup(other_c_string);

        if (c_string == nullptr) {
            throw std::bad_alloc();
        }
        tmp.emplace_back(c_string, free);
    }
    for (auto &&[dst, src] : std::ranges::views::zip(std::span{m_array.get(), m_size}, tmp)) {
        dst = src.release();
    }
    m_array[m_size] = nullptr;
}

/// \param other is the `CStringArray` to move.
///
CStringArray::CStringArray(
    CStringArray &&other
) noexcept
: m_size(std::exchange(other.m_size, 0)), m_array(std::move(other.m_array))
{}

CStringArray::~CStringArray() noexcept
{
    std::for_each(m_array.get(), m_array.get() + m_size, free);
}

/// \param other is the `CStringArray` to deep-copy.
///
CStringArray &CStringArray::assign(
    CStringArray other
) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
    return *this;
}

/// \param rhs is the `CStringArray` to deep-copy.
///
/// \throw std::bad_alloc on `CStringArray(rhs)` failure.
///
CStringArray &CStringArray::operator=(
    CStringArray const &rhs
)
{
    return assign(rhs);
}

/// \param rhs is the `CStringArray` to move.
///
CStringArray &CStringArray::operator=(
    CStringArray &&rhs
) noexcept
{
    return assign(std::move(rhs));
}

CStringArray::operator char *const *const() const { return m_array.get(); }

} // namespace taskmaster
