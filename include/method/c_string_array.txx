#ifndef METHOD_C_STRING_ARRAY_TXX
#define METHOD_C_STRING_ARRAY_TXX

#include "type/c_string_array.hxx"
#include <cstdlib>
#include <cstring>
#include <memory>
#include <new>
#include <ranges>
#include <span>
#include <vector>

namespace taskmaster {

/// \param `strings` is the set of strings to deep-copy.
///
/// \throw `std::bad_alloc` on `std::make_unique` failure.
/// \throw `std::bad_alloc` on `std::vector::reserve` failure.
/// \throw `std::bad_alloc` on `strdup` failure.
/// \throw `std::length_error` on `std::vector::reserve` failure.
///
template <typename TP_Container>
CStringArray::CStringArray(
    TP_Container const &strings
)
: m_size(strings.size())
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
    for (auto &&[dst, src] : std::ranges::views::zip(std::span{m_array.get(), m_size}, tmp)) {
        dst = src.release();
    }
    m_array[m_size] = nullptr;
}

} // namespace taskmaster

#endif
