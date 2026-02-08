#include "type/c_string_array.hxx"
#include <algorithm>

namespace taskmaster {

CStringArray::CStringArray() { m_array[0] = nullptr; }

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

CStringArray::CStringArray(
    CStringArray &&other
) noexcept
: m_size(std::exchange(other.m_size, 0)), m_array(std::move(other.m_array))
{}

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
