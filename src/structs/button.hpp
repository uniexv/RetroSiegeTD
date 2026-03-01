#pragma once
#include "../enums/guitype.hpp"
#include <cstdint>
#include <string>
#include <raylib.h>
#include <functional>

struct Button
{
    std::string p_text = "";

    std::function<void(float deltaTime,Button& button)> p_onPressed = [](float deltaTime,Button& button){};
    std::function<void(float deltaTime,Button& button)> p_updateFunction = [](float deltaTime,Button& button){};

    Texture p_image = { 0, 0, 0, 0, 0 };

    Rectangle p_rect = {0, 0, 100, 30};
    GuiType p_elementType = GuiType::GameGui;
    Vector2 p_textPosition = {0, 0};
    Vector2 p_imagePosition = {0 , 0};
    Color p_color = BLUE;
    Color p_boundingColor = BLANK;
    Color p_textColor = BLACK;
    float p_segments = 4.0f;
    float p_roundness = 5.0f;
    float p_boundingSize = 0.0f;
    uint16_t p_id = 0;
    bool p_isHovered = false;
    bool p_visible = true;
};
