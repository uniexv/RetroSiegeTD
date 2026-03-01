#include "guimanager.hpp"
#include "../namespaces/settings.hpp"
#include "../utility/debugutil.hpp"
#include "../utility/colorutil.hpp"
#include <raylib.h>
#include <cmath>
#include <format>
#include <algorithm>

void GuiManager::UpdateTextPosition(Label &label)
{
    const Vector2 textMeasurement = MeasureTextEx(Settings::g_gameFont,
                                                  label.p_text.c_str(),
                                                  Settings::g_gameFont.baseSize, 1.0f);
    label.p_textPosition =
        {
            std::round(label.p_rect.x + label.p_rect.width / 2.0f - textMeasurement.x / 2.0f), 
            std::round(label.p_rect.y + label.p_rect.height / 2.0f - textMeasurement.y / 2.0f) 
        };
}
void GuiManager::UpdateTextPosition(Button &button)
{
    const Vector2 textMeasurement = MeasureTextEx(Settings::g_gameFont,
                                                  button.p_text.c_str(),
                                                  Settings::g_gameFont.baseSize, 1.0f);
    button.p_textPosition =
        {
            std::round(button.p_rect.x + button.p_rect.width / 2.0f - textMeasurement.x / 2.0f),  
            std::round(button.p_rect.y + button.p_rect.height / 2.0f - textMeasurement.y / 2.0f)
        };
}
void GuiManager::UpdateImagePosition(Button &button)
{
    if (button.p_image.id == 0)
    {
        return;
    }

    button.p_imagePosition =
        {
            button.p_rect.x + button.p_rect.width / 2.0f - button.p_image.width / 2.0f,
            button.p_rect.y + button.p_rect.height / 2.0f - button.p_image.height / 2.0f};
}
void GuiManager::UpdateImagePosition(Label &label)
{
    if (label.p_image.id == 0)
    {
        return;
    }

    label.p_imagePosition =
        {
            label.p_rect.x + label.p_rect.width / 2.0f - label.p_image.width / 2.0f,
            label.p_rect.y + label.p_rect.height / 2.0f - label.p_image.height / 2.0f};
}
void GuiManager::UpdatePress(const float deltaTime, Button &button)
{
    const Vector2 mousePosition = GetMousePosition();
    const Rectangle scaledButtonRect =
        {
            button.p_rect.x * Settings::g_gameScale
            ,
            button.p_rect.y * Settings::g_gameScale
            ,
            button.p_rect.width * Settings::g_gameScale 
            ,
            button.p_rect.height * Settings::g_gameScale
        };
    button.p_isHovered = false;
    if (!CheckCollisionPointRec(mousePosition, scaledButtonRect))
    {
        return;
    }
    button.p_isHovered = true;
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    };

    button.p_onPressed(deltaTime, button);
}
void GuiManager::UpdateLabel(const float deltaTime, Label &label)
{
    if (!IsElementUsed(label))
    {
        return;
    }
    if (label.p_updateFunction)
    {
        label.p_updateFunction(deltaTime, label);
    }
    if (!label.p_visible)
    {
        return;
    }

    UpdateImagePosition(label);
    UpdateTextPosition(label);
}
void GuiManager::UpdateButton(const float deltaTime, Button &button)
{
    if (!IsElementUsed(button))
    {
        return;
    }
    if (button.p_updateFunction)
    {
        button.p_updateFunction(deltaTime, button);
    }
    if (!button.p_visible)
    {
        return;
    }

    UpdateTextPosition(button);
    UpdateImagePosition(button);
    UpdatePress(deltaTime, button);
}
void GuiManager::DrawButton(const Button &button) const
{
    if (!button.p_visible)
    {
        return;
    }
    if (!IsElementUsed(button))
    {
        return;
    }

    Color buttonColor = button.p_color;
    Color boundingColor = button.p_boundingColor;
    if (button.p_isHovered)
    {
        buttonColor = buttonColor * 0.8f;
        boundingColor = boundingColor * 0.8f;
    }

    Rectangle drawRect = button.p_rect;
    drawRect.x = floorf(drawRect.x);
    drawRect.y = floorf(drawRect.y);
    drawRect.width = floorf(drawRect.width);
    drawRect.height = floorf(drawRect.height);

    Vector2 drawTextPos = button.p_textPosition;
    drawTextPos.x = floorf(drawTextPos.x);
    drawTextPos.y = floorf(drawTextPos.y);

    Vector2 drawImagePos = button.p_imagePosition;
    drawImagePos.x = floorf(drawImagePos.x);
    drawImagePos.y = floorf(drawImagePos.y);

    if (button.p_roundness != 0 && button.p_segments != 0)
    {
        DrawRectangleRounded(drawRect, button.p_roundness, button.p_segments, buttonColor);
        if (button.p_boundingSize != 0.0f)
        {
            Rectangle outlineRect = drawRect;
            outlineRect.x += button.p_boundingSize * 0.5f;
            outlineRect.y += button.p_boundingSize * 0.5f;
            outlineRect.width -= button.p_boundingSize;
            outlineRect.height -= button.p_boundingSize;

            DrawRectangleRoundedLinesEx(outlineRect, button.p_roundness, button.p_segments * 2.0f, button.p_boundingSize, boundingColor);
        }
    }
    else
    {
        DrawRectangleRec(drawRect, buttonColor);
        if (button.p_boundingSize != 0.0f)
        {
            Rectangle outlineRect = drawRect;
            outlineRect.x += button.p_boundingSize * 0.5f;
            outlineRect.y += button.p_boundingSize * 0.5f;
            outlineRect.width -= button.p_boundingSize;
            outlineRect.height -= button.p_boundingSize;

            DrawRectangleLinesEx(outlineRect, button.p_boundingSize, boundingColor);
        }
    }

    if (!button.p_text.empty())
    {
        DrawTextEx(Settings::g_gameFont, button.p_text.c_str(),
                   drawTextPos, Settings::g_gameFont.baseSize, 1.0f, button.p_textColor);
    }
    if (button.p_image.id != 0)
    {
        DrawTextureV(button.p_image, drawImagePos, WHITE);
    }
}
void GuiManager::DrawLabel(const Label &label) const
{
    if (!label.p_visible)
    {
        return;
    }
    if (!IsElementUsed(label))
    {
        return;
    }

    Rectangle drawRect = label.p_rect;
    drawRect.x = floorf(drawRect.x);
    drawRect.y = floorf(drawRect.y);
    drawRect.width = floorf(drawRect.width);
    drawRect.height = floorf(drawRect.height);

    Vector2 drawTextPos = label.p_textPosition;
    drawTextPos.x = floorf(drawTextPos.x);
    drawTextPos.y = floorf(drawTextPos.y);

    Vector2 drawImagePos = label.p_imagePosition;
    drawImagePos.x = floorf(drawImagePos.x);
    drawImagePos.y = floorf(drawImagePos.y);

    if (label.p_segments != 0.0f && label.p_roundness != 0.0f)
    {
        DrawRectangleRounded(drawRect, label.p_roundness, label.p_segments, label.p_color);
        if (label.p_boundingSize != 0.0f)
        {
            Rectangle outlineRect = drawRect;
            outlineRect.x += label.p_boundingSize * 0.5f;
            outlineRect.y += label.p_boundingSize * 0.5f;
            outlineRect.width -= label.p_boundingSize;
            outlineRect.height -= label.p_boundingSize;

            DrawRectangleRoundedLinesEx(outlineRect, label.p_roundness, label.p_segments * 2.0f, label.p_boundingSize, label.p_boundingColor);
        }
    }
    else
    {
        DrawRectangleRec(drawRect, label.p_color);
        if (label.p_boundingSize != 0.0f)
        {
            Rectangle outlineRect = drawRect;
            outlineRect.x += label.p_boundingSize * 0.5f;
            outlineRect.y += label.p_boundingSize * 0.5f;
            outlineRect.width -= label.p_boundingSize;
            outlineRect.height -= label.p_boundingSize;

            DrawRectangleLinesEx(outlineRect, label.p_boundingSize, label.p_boundingColor);
        }
    }

    if (label.p_image.id != 0)
    {
        DrawTextureV(label.p_image, drawImagePos, WHITE);
    }

    if (!label.p_text.empty())
    {
        DrawTextEx(Settings::g_gameFont, label.p_text.c_str(),
                   drawTextPos, Settings::g_gameFont.baseSize, 1.0f, label.p_textColor);
    }
}
const bool GuiManager::IsElementUsed(const Button &button) const
{
    if (m_gameState == GameState::Ended)
    {
        return false;
    }
    if (!(button.p_elementType == GuiType::MenuGui) && !(m_gameState == GameState::Started))
    {
        return false;
    }
    if (button.p_elementType == GuiType::MenuGui && m_gameState == GameState::Started)
    {
        return false;
    }
    return true;
}
const bool GuiManager::IsElementUsed(const Label &label) const
{
    if (m_gameState == GameState::Ended)
    {
        return false;
    }
    if (!(label.p_elementType == GuiType::MenuGui) && m_gameState == GameState::Menu)
    {
        return false;
    }
    if (label.p_elementType == GuiType::MenuGui && m_gameState == GameState::Started)
    {
        return false;
    }
    return true;
}
const size_t GuiManager::GetAmountOfLabels() const
{
    return m_labels.size();
}
const size_t GuiManager::GetAmountOfButtons() const
{
    return m_buttons.size();
}
void GuiManager::ReserveButton(const size_t count)
{
    m_buttons.reserve(m_buttons.size() + count);
}
void GuiManager::ReserveLabel(const size_t count)
{
    m_labels.reserve(m_labels.size() + count);
}
Button &GuiManager::AddButton(const Button &button)
{
    m_buttons.push_back(button);
    UpdateTextPosition(m_buttons.back());
    return m_buttons.back();
}
Label &GuiManager::AddLabel(const Label &label)
{
    m_labels.push_back(label);
    UpdateTextPosition(m_labels.back());
    return m_labels.back();
}
void GuiManager::RemoveButton(const int id)
{
    m_buttons.erase(
        std::remove_if(m_buttons.begin(), m_buttons.end(),
                       [id](const Button &button)
                       { return button.p_id == id; }),
        m_buttons.end());
}
void GuiManager::RemoveLabel(const int id)
{
    m_labels.erase(
        std::remove_if(m_labels.begin(), m_labels.end(),
                       [id](const Label &label)
                       { return label.p_id == id; }),
        m_labels.end());
}
void GuiManager::SyncGameState(const GameState gameState)
{
    m_gameState = gameState;
}
void GuiManager::Update(const float deltaTime)
{
    for (auto &label : m_labels)
    {
        UpdateLabel(deltaTime, label);
    }

    for (auto &button : m_buttons)
    {
        UpdateButton(deltaTime, button);
    }
}
void GuiManager::Draw() const
{
    for (const auto &label : m_labels)
    {
        DrawLabel(label);
    }

    for (const auto &button : m_buttons)
    {
        DrawButton(button);
    }
}
void GuiManager::Init()
{
}
