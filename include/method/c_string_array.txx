#ifndef METHOD_C_STRING_ARRAY_TXX
#define METHOD_C_STRING_ARRAY_TXX

#include <cstring>
#include <ranges>
#include <vector>

namespace taskmaster {

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
