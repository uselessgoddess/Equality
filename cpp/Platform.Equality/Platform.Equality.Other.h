#pragma once

#ifndef PLATFORM_EQUALITY_OTHER
#define PLATFORM_EQUALITY_OTHER

#include <concepts>
#include <functional>

// Да сделайте уже что-нибудь
namespace Platform::System
{
    template <typename _Type>
    concept IEnumerable = requires(_Type object)
    {
        {object.begin()} -> std::forward_iterator;
        {object.end()} -> std::forward_iterator;
    };
}

template <typename _Type>
concept std_equatable = requires(_Type left, _Type right)
{
    std::equal_to<_Type>{}(left, right);
};

template <typename _Type>
concept not_std_equatable = !std_equatable<_Type>;

namespace std
{
    template <not_std_equatable T> requires Platform::System::IEnumerable<T>
    struct equal_to<T>
    {
        bool operator()(const T& left, const T& right)
        {
            auto left_begin = left.begin();
            auto right_begin = right.begin();

            auto left_end = left.end();
            auto right_end = right.end();

            while(left_begin != left_end && right_begin != right_end)
            {
                if(*left_begin != *right_begin)
                {
                    return false;
                }
                ++left_begin;
                ++right_begin;
            }

            return (left_begin == left_end) && (right_begin == right_end);
        }
    };

}

#endif //PLATFORM_EQUALITY_OTHER
