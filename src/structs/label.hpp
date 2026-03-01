#pragma once
#include "../enums/guitype.hpp"
#include <cstdint>
#include <string>
#include <raylib.h>
#include <functional>

struct Label
{
    Texture p_image = {0, 0, 0, 0, 0};
    std::string p_text = "";

    std::function<void(float deltaTime, Label &label)> p_updateFunction = [](float deltaTime, Label &label) {};

    Rectangle p_rect = {0, 0};
    GuiType p_elementType = GuiType::GameGui;
    Vector2 p_textPosition = {0, 0};
    Vector2 p_imagePosition = {0, 0};
    Color p_color = WHITE;
    Color p_boundingColor = BLANK;
    Color p_textColor = BLACK;
    float p_segments = 4.0f; 
    float p_roundness = 5.0f;
    float p_boundingSize = 0.0f;

    uint16_t p_id = 0;
    bool p_visible = true;
};
