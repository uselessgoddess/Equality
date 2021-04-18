#pragma once

#ifndef PLATFORM_EQUALITY_OTHER
#define PLATFORM_EQUALITY_OTHER

#include <concepts>
#include <functional>
#include <algorithm>

namespace std
{
    template<std::ranges::range T>
    requires (!std::equality_comparable<T>)
    struct equal_to<T>
    {
        constexpr bool operator()(const T& left, const T& right) const
        {
            return ranges::equal(left, right);
        }
    };
}

#endif //PLATFORM_EQUALITY_OTHER
