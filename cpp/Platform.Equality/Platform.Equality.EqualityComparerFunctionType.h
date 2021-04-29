#ifndef PLATFORM_EQUALITY_EQUALITYCOMPARERFUNCTIONTYPE
#define PLATFORM_EQUALITY_EQUALITYCOMPARERFUNCTIONTYPE

#include <functional>

namespace Platform::Equality
{
    template<typename TValue>
    using EqualityComparerFunctionType = std::function<bool(const TValue&, const TValue&)>;
}

#endif//PLATFORM_EQUALITY_EQUALITYCOMPARERFUNCTIONTYPE
