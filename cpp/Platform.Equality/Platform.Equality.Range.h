#pragma once

#include <algorithm>
#include <concepts>
#include <functional>

namespace std
{
    template<std::ranges::range T>
    requires(!std::equality_comparable<T>)
    struct equal_to<T>
    {
        constexpr bool operator()(const T& left, const T& right) const
        {
            return std::ranges::equal(left, right);
        }
    };
}
