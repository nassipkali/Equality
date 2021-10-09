#pragma once

#include <functional>

namespace Platform::Equality
{
    template<typename TValue>
    using EqualityComparerFunctionType = std::function<bool(const TValue&, const TValue&)>;
}
