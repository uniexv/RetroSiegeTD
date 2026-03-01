#pragma once
#include <cstdint>

enum class GameState : uint8_t
{
    Menu = 0,
    Started = 1,
    Ended = 2
};
