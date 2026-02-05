#ifndef METHOD_C_STRING_ARRAY_TXX
#define METHOD_C_STRING_ARRAY_TXX

#include <algorithm>
#include <cstring>
#include <vector>

namespace taskmaster {

template <typename TP_Container>
CStringArray::CStringArray(
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
        tmp.begin(), tmp.end(), m_array.get(), [](std::unique_ptr<char, void (*)(void *)> &ptr) {
            return ptr.release();
        }
    ) = nullptr;
}

} // namespace taskmaster

#endif
