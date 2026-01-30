#include "type/c_string_array.hxx"
#include <algorithm>
#include <cstring>
#include <utility>
#include <vector>

namespace taskmaster {

CStringArray::CStringArray(
    CStringArray const &other
)
: m_size(other.m_size), m_array(m_size ? std::make_unique<char *[]>(m_size + 1) : nullptr)
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
        tmp.begin(), tmp.end(), m_array.get(), [](std::unique_ptr<char, void (*)(void *)> &ptr) {
            return ptr.release();
        }
    );
}

CStringArray::CStringArray(
    CStringArray &&other
) noexcept
: m_size(std::exchange(other.m_size, 0)), m_array(std::move(other.m_array))
{}

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
    std::transform(
        tmp.begin(), tmp.end(), m_array.get(), [](std::unique_ptr<char, void (*)(void *)> &ptr) {
            return ptr.release();
        }
    );
}

CStringArray::~CStringArray() noexcept
{
    std::for_each(m_array.get(), m_array.get() + m_size, free);
}

CStringArray &CStringArray::assign(
    CStringArray other
) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
    return *this;
}

CStringArray &CStringArray::operator=(
    CStringArray const &rhs
)
{
    return assign(rhs);
}

CStringArray &CStringArray::operator=(
    CStringArray &&rhs
) noexcept
{
    return assign(std::move(rhs));
}

CStringArray::operator char *const *const() const { return m_array.get(); }

} // namespace taskmaster
