#include <algorithm>
#include <cmath>
#include <cassert>
#include "../namespaces/sprites.hpp"
#include "../namespaces/settings.hpp"
#include "../utility/debugUtil.hpp"
#include "tilemanager.hpp"

bool TileManager::IsTileHovered(Tile &tile)
{
    const Vector2 mousePosition = GetMousePosition();
    const Rectangle tileRect =
        {
            tile.p_position.x * Settings::g_gameScale + Settings::g_boundingSize * Settings::g_gameScale,  
            tile.p_position.y * Settings::g_gameScale,                                                    
            static_cast<float>(g_tileSize * Settings::g_gameScale),                                       
            static_cast<float>(g_tileSize * Settings::g_gameScale)                                        
        };
    if (!CheckCollisionPointRec(mousePosition, tileRect))
    {
        return false;
    }
    m_lastHoveredTile = &tile;
    m_currentHoveredTile = &tile;
    return true;
}
bool TileManager::IsTileClicked(Tile &tile)
{
    if (!IsTileHovered(tile))
    {
        return false;
    }
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return false;
    }
    m_lastClickedTile = &tile;
    return true;
}

Tile TileManager::GetPathStart()
{

    if (m_startPathId == -1)
    {
        for (auto &tile : m_tiles)
        {

            int16_t moveDirectionInt = (int16_t)tile.p_moveDirection;
            if (moveDirectionInt <= -1 && moveDirectionInt >= -4)
            {
                m_startPathId = static_cast<float>(tile.p_id);
                return tile;
            };
        }
    }
    else
    {
        return GetTile(m_startPathId);
    }
    assert(false && "getpathstart did not find the tile");
    return Tile{};
}
Tile TileManager::GetTile(const uint16_t id) const
{
    auto it = std::lower_bound(m_tiles.begin(), m_tiles.end(), id, [](const Tile &tile, const uint16_t id)
                               { return tile.p_id < id; });
    if (it != m_tiles.end() && it->p_id == id)
    {
        return *it;
    }
    Debug::PrintError("Incorrect Id returned");
    return Tile{};
}
const int16_t TileManager::GetMovedId(uint16_t tileid, int8_t direction) const
{
    direction = std::abs(direction);
    if (direction == (int8_t)TileDirection::Up)
    {
        tileid -= 18;
    }
    else if (direction == (int8_t)TileDirection::Down)
    {
        tileid += 18;
    }
    else if (direction == (int8_t)TileDirection::Right)
    {
        tileid += 1;
    }
    else if (direction == (int8_t)TileDirection::Left)
    {
        tileid += -1;
    }
    else if (direction == (int8_t)TileDirection::NoDirection)
    {
    }
    else
    {
        Debug::PrintError(direction, "UNKNOWN DIRECTION,DIRECTION");
        Debug::PrintError(tileid, "UNKNOWN DIRECTION,TILEID");
        // assert(false && "unknown direction was inputed into GetMovedId");
    }
    if (tileid < 0 || tileid > (18 * 18))
    {
        Debug::PrintError(direction, "OUTOFBOUNDS ID,DIRECTION");
        Debug::PrintError(tileid, "OUTOFBOUNDS ID,TILEID");
        // assert(false && "outofbounds id in GetMovedId");
        tileid = 0;
    }
    return tileid;
}
Tile *TileManager::GetLastClickedTile()
{
    return m_lastClickedTile;
}
Tile *TileManager::GetLastHoveredTile()
{
    return m_lastHoveredTile;
}
Tile *TileManager::GetCurrentHoveredTile()
{
    return m_currentHoveredTile;
}
const Vector2 TileManager::GetTileCenterPosition(const Tile &tile) const
{
    constexpr float offset = g_tileSize / 2.0f;
    return Vector2{
        tile.p_position.x + offset,
        tile.p_position.y + offset};
}
void TileManager::Update()
{
    m_currentHoveredTile = nullptr;
    for (auto &tile : m_tiles)
    {
        if (IsTileClicked(tile))
        {
        }
    }
}
void TileManager::Draw(const uint8_t screenOffset) const
{
    for (auto &&tile : m_tiles)
    {
        Color color = WHITE;
        if (Settings::g_debugView && (int8_t)tile.p_moveDirection != 0)
        {
            color = RED;
        }
        DrawTexture(tile.p_texture, floorf(tile.p_position.x + screenOffset), floorf(tile.p_position.y), color);
    }
}
void TileManager::LoadMap(const GameMap gameMap)
{
    uint16_t id = 0;
    for (size_t y = 0; y < gameMap.p_tileIdMap.size(); y++)
    {
        for (size_t x = 0; x < gameMap.p_tileIdMap[y].size(); x++)
        {
            Tile tile = {};
            tile.p_id = id;
            tile.p_typeId = gameMap.p_tileIdMap[y][x];
            tile.p_texture = Sprites::g_textures[static_cast<uint16_t>(gameMap.p_tileIdMap[y][x]) - 1];
            tile.p_position = {static_cast<float>(g_tileSize * x), static_cast<float>(g_tileSize * y)};
            tile.p_moveDirection = gameMap.p_pathDirections[y][x];
            m_tiles.push_back(tile);
            id++;
        }
    }
}
void TileManager::Init()
{
}
