#ifndef PLATFORM_EQUALITY_BASE
#define PLATFORM_EQUALITY_BASE

#include <functional>

namespace Platform::Equality
{
    template<typename TValue>
    using EqualityComparerFunctionType = std::function<bool(const TValue&, const TValue&)>;
}

#endif//PLATFORM_EQUALITY_BASE
