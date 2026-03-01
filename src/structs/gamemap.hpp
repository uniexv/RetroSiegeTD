#pragma once
#include "tile.hpp"
#include <cstdint>
#include <array>
struct GameMap
{
    std::array<std::array<TileDirection, 18>, 18> p_pathDirections = {}; 
    std::array<std::array<TileType, 18>, 18> p_tileIdMap = {};
    uint16_t p_id = 0;
};
