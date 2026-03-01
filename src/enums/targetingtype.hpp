#pragma once
#include <cstdint>
#include <string>


enum class TargetingType : uint8_t
{
    First = 0,
    Last = 1,
    Strongest = 2,
    Weakest = 3,
};

namespace TargetingTypeUtility
{
    inline const std::string ToString(TargetingType targetingType)
    {
        switch (targetingType)
        {
            case TargetingType::First: return "First";
            case TargetingType::Last: return "Last";
            case TargetingType::Strongest: return "Strongest";
            case TargetingType::Weakest: return "Weakest";
            default: return "Unknown";
        }
    }
}

