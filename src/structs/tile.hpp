#pragma once
#include <cstdint>
#include <raylib.h>
enum class TileDirection : int8_t
{
    NoDirection = 0,

    StartUp = -1,
    StartDown = -2,
    StartRight = -3,
    StartLeft = -4,
    End = -5,
    
    Up = 1,
    Down = 2,
    Right = 3,
    Left = 4
};
enum class TileType : uint8_t
{
    GrassTile = 1,
    GrassPath1 = 2,
    GrassPath2 = 3,
    GrassPath3 = 4,
    GrassPath4 = 5
};
struct Tile
{
    Texture2D p_texture = {0, 0, 0, 0, 0};
    Vector2 p_position = {0,0};
    TileDirection p_moveDirection = TileDirection::NoDirection;
    uint16_t p_id = -1;
    TileType p_typeId = TileType(0);
};
