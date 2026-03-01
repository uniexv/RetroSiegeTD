#pragma once
#include <string>
#include <type_traits>
#include <concepts>
#include <iostream>


namespace Debug
{

template <typename T>
void Print(T message, std::string prefix = "")
{
    
#ifdef RELEASE
    return;
#endif

    constexpr bool canParse = requires(T message) {
        { std::to_string(message) } -> std::convertible_to<std::string>;
    };
    constexpr bool isString = std::same_as<T, std::string>;
    constexpr bool isCString = std::same_as<T, const char *>;

    static_assert(canParse || isString || isCString, "Debug::Print input must be a string or stringable type");

    if constexpr (canParse)
    {
        std::cout << "DEBUG_INFO: " << prefix << ": " << std::to_string(message) << "\n";
    }
    else if constexpr (isCString)
    {
        std::cout << "DEBUG_INFO: " << prefix << ": " << std::string(message) << "\n";
    }
    else if constexpr (isString)
    {
        std::cout << "DEBUG_INFO: " << prefix << ": " << message << "\n";
    }
}
template <typename T>
void PrintError(T message, std::string prefix = "")
{

#ifdef RELEASE
    return;
#endif
    constexpr bool canParse = requires(T message) {
        { std::to_string(message) } -> std::convertible_to<std::string>;
    };
    constexpr bool isString = std::same_as<T, std::string>;
    constexpr bool isCString = std::same_as<T, const char *>;

    static_assert(canParse || isString || isCString, "Debug::Print input must be a string or stringable type");

    if constexpr (canParse)
    {
        std::cerr << "DEBUG_ERROR: " << prefix << ": " << std::to_string(message) << "\n";
    }
    else if constexpr (isCString)
    {
        std::cerr << "DEBUG_ERROR: " << prefix << ": " << std::string(message) << "\n";
    }
    else if constexpr (isString)
    {
        std::cerr << "DEBUG_ERROR: " << prefix << ": " << message << "\n";
    }
}
    
}