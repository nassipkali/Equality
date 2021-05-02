#pragma once

#ifndef PLATFORM_EQUALITY_RANGE
#define PLATFORM_EQUALITY_RANGE

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

#endif//PLATFORM_EQUALITY_RANGE
