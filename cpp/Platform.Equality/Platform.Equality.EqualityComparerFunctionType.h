#ifndef PLATFORM_EQUALITY_EQUALITY_COMPARER_FUNCTION_TYPE
#define PLATFORM_EQUALITY_EQUALITY_COMPARER_FUNCTION_TYPE

#include <functional>

namespace Platform::Equality
{
    template<typename TValue>
    using EqualityComparerFunctionType = std::function<bool(const TValue&, const TValue&)>;
}

#endif//PLATFORM_EQUALITY_EQUALITY_COMPARER_FUNCTION_TYPE
