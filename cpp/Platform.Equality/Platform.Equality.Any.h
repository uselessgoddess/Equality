#pragma once

#ifndef PLATFORM_EQUALITY_ANY_H
#define PLATFORM_EQUALITY_ANY_H

#include <any>
#include <functional>
#include <typeindex>
#include <concepts>
#include <stdexcept>


namespace Platform::Equality
{
    template<class T>
    inline auto to_any_hash_visitor(auto func)
    {
        return std::pair<std::type_index, std::function<bool(std::any, std::any)>>
        {
                std::type_index(typeid(T)),
                [func](std::any a, std::any b) -> std::size_t
                {
                    if constexpr (std::is_void_v<T>)
                        return func();
                    else
                        return func(std::any_cast<T>(a), std::any_cast<T>(b));
                }
        };
    }

    #define BASE_VISITOR_REGISTER(Type) to_any_hash_visitor<Type>([](Type a, Type b) {return a == b;})
    #define VISITOR_REGISTER(Type, Func) to_any_hash_visitor<Type>([](Type a, Type b) {return Func;})
    static std::unordered_map<std::type_index, std::function<bool(std::any, std::any)>>
    any_equal_visitor {
            BASE_VISITOR_REGISTER(short int),
            BASE_VISITOR_REGISTER(unsigned short int),
            BASE_VISITOR_REGISTER(int),
            BASE_VISITOR_REGISTER(unsigned int),
            BASE_VISITOR_REGISTER(unsigned long int),
            BASE_VISITOR_REGISTER(long long int),
            BASE_VISITOR_REGISTER(unsigned long long int),

            VISITOR_REGISTER(const char*, std::string(a) == std::string(b)),

            BASE_VISITOR_REGISTER(const std::string&),

    };
    #undef BASE_VISITOR_REGISTER
    #undef VISITOR_REGISTER

    template<class T>
    inline void register_any_hash_visitor(auto func)
    {
        any_equal_visitor.insert(to_any_hash_visitor<T>(func));
    }

    template<typename TOther>
#ifdef __cpp_lib_concepts
    requires
        requires(TOther left, TOther right)
        {
            {std::equal_to<TOther>{}(left, right)} -> std::same_as<bool>;
        }
        ||
        requires(TOther left, TOther right)
        {
            {left == right} -> std::same_as<bool>;
        }
#endif
    bool operator==(const std::any& object, TOther other)
    {
        return std::any_cast<TOther>(object) == other;
    }

    bool operator==(const std::any& object, const std::any& other)
    {
        if(object.type() != other.type())
            return false;

        if(!any_equal_visitor.contains(object.type()))
            throw std::runtime_error(std::string("Equal function for type ").append(object.type().name()).append(" is unregistered"));

        auto equaler = any_equal_visitor[object.type()];
        return equaler(object, other);
    }
}

namespace std
{
    template<>
    struct equal_to<std::any>
    {
        bool operator()(const std::any& object, const auto& other)
        {
            return Platform::Equality::operator==(object, other);
        }
    };
}

#endif //PLATFORM_EQUALITY_ANY_H
