#pragma once

#ifndef PLATFORM_EQUALITY_ANY_H
#define PLATFORM_EQUALITY_ANY_H

#include <any>
#include <functional>

#if __cplusplus >= 201709
#include <concepts>
#endif

namespace Platform::Equality
{
    template<typename TOther>
#ifdef __cpp_lib_concepts
    requires
        requires(TOther left, TOther right)
        {
            {std::equal_to<TOther>{}(left, right)} -> std::same_as<bool>;
        }
#endif
    bool operator==(const std::any& object, TOther other)
    {
        return std::any_cast<TOther>(object) == other;
    }
}

namespace std
{
    template<>
    struct equal_to<std::any>
    {
        template<typename TOther>
        bool operator()(const std::any& object, TOther other)
        {
            return Platform::Equality::operator==(object, other);
        }
    };
}

#endif //PLATFORM_EQUALITY_ANY_H
