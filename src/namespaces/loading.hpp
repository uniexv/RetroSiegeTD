#pragma once
#include <raylib.h>
#include <cstdint>
#include <array>
#include "../structs/tile.hpp"

namespace Loading
{
    std::array<std::array<TileDirection, 18>, 18> LoadMapDirections(const char *path);
    std::array<std::array<TileType, 18>, 18> LoadTileTypes(const char *path);
}
