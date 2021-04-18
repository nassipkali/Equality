#pragma once

#ifndef PLATFORM_EQUALITY_ANY
#define PLATFORM_EQUALITY_ANY

#include <any>
#include <functional>
#include <typeindex>
#include <concepts>
#include <stdexcept>

namespace Platform::Equality
{
    namespace Internal
    {
        template<class TValue, class TEqualityComparer>
        inline auto ToAnyEqualVisitor(TEqualityComparer&& func)
        {
            return std::pair<std::type_index, std::function<bool(const std::any&, const std::any&)>>
            {
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
                }
            };
        }

        #define BASE_VISITOR_REGISTER(Type) ToAnyEqualVisitor<Type>(std::equal_to<Type>{})
        static std::unordered_map<std::type_index, std::function<bool(const std::any&, const std::any&)>>
        AnyEqualityComparers
        {
            BASE_VISITOR_REGISTER(short int),
            BASE_VISITOR_REGISTER(unsigned short int),
            BASE_VISITOR_REGISTER(int),
            BASE_VISITOR_REGISTER(unsigned int),
            BASE_VISITOR_REGISTER(unsigned long int),
            BASE_VISITOR_REGISTER(long long int),
            BASE_VISITOR_REGISTER(unsigned long long int),
            BASE_VISITOR_REGISTER(float),
            BASE_VISITOR_REGISTER(double),
            BASE_VISITOR_REGISTER(long double),
            BASE_VISITOR_REGISTER(const char*),
            BASE_VISITOR_REGISTER(const std::string&),
        };
        #undef BASE_VISITOR_REGISTER
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
        if(object.type() != other.type())
        {
            return false;
        }

        if(!Internal::AnyEqualityComparers.contains(object.type()))
        {
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

#endif //PLATFORM_EQUALITY_ANY