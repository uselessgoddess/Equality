#pragma once

#ifndef PLATFORM_EQUALITY_ANY
#define PLATFORM_EQUALITY_ANY

#include <any>
#include <concepts>
#include <stdexcept>
#include <typeindex>

#include "Platform.Equality.EqualityComparerFunctionType.h"

namespace Platform::Equality
{
    namespace Internal
    {
        template<class TValue, class TEqualityComparer>
        inline auto ToAnyEqualVisitor(TEqualityComparer&& func)
        {
            return std::pair<std::type_index, EqualityComparerFunctionType<std::any>>{
                std::type_index(typeid(TValue)),
                [func = std::forward<TEqualityComparer>(func)](const std::any& left, const std::any& right) -> std::size_t
                {
                    if constexpr (std::is_void_v<TValue>)
                    {
                        return func();
                    }
                    else
                    {
                        return func(std::any_cast<TValue>(left), std::any_cast<TValue>(right));
                    }
                }};
        }

        #define EQUALITY_COMPARER(Type) ToAnyEqualVisitor<Type>(std::equal_to<Type>{})
        static std::unordered_map<std::type_index, EqualityComparerFunctionType<std::any>>
            AnyEqualityComparers
            {
                EQUALITY_COMPARER(short int),
                EQUALITY_COMPARER(unsigned short int),
                EQUALITY_COMPARER(int),
                EQUALITY_COMPARER(unsigned int),
                EQUALITY_COMPARER(unsigned long int),
                EQUALITY_COMPARER(long long int),
                EQUALITY_COMPARER(unsigned long long int),
                EQUALITY_COMPARER(float),
                EQUALITY_COMPARER(double),
                EQUALITY_COMPARER(long double),
                EQUALITY_COMPARER(const char*),
                EQUALITY_COMPARER(const std::string&),
            };
        #undef EQUALITY_COMPARER
    }

    template<class T>
    inline void RegisterEqualityComparer(auto&& func)
    {
        Internal::AnyEqualityComparers.insert(Internal::ToAnyEqualVisitor<T>(std::forward<decltype(func)>(func)));
    }

    template<typename TOther>
    requires std::equality_comparable<TOther>
    bool operator==(const std::any& object, TOther other)
    {
        return std::any_cast<TOther>(object) == other;
    }

    bool operator==(const std::any& object, const std::any& other)
    {
        if (object.type() != other.type())
        {
            return false;
        }

        if (!Internal::AnyEqualityComparers.contains(object.type()))
        {
            // TODO later use std::format
            throw std::runtime_error(std::string("Equal function for type ")
                                         .append(object.type().name())
                                         .append(" is unregistered"));
        }

        const auto& comparer = Internal::AnyEqualityComparers[object.type()];
        return comparer(object, other);
    }
}

namespace std
{
    template<>
    struct equal_to<std::any>
    {
        constexpr bool operator()(const std::any& object, const auto& other) const
        {
            return Platform::Equality::operator==(object, other);
        }
    };
}

#endif