#include "speed.hpp"
#include "../namespaces/settings.hpp"
#include "../namespaces/sprites.hpp"
#include "../managers/guimanager.hpp"
#include "../utility/colorutil.hpp"
#include "../structs/button.hpp"
#include "../enums/guitype.hpp"
#include <cassert>

void Speed::InjectDependencies(GuiManager *guiManager)
{
    mgr_gui = guiManager;
}

void Speed::InitLabels()
{
}

void Speed::InitButtons()
{
    constexpr size_t amountOfButtons = 1;
    mgr_gui->ReserveButton(amountOfButtons);

#pragma region SpeedButton
    Button &speedButton = mgr_gui->AddButton(Button{});
    speedButton.p_text = "";
    speedButton.p_onPressed = [](float deltaTime, Button &button) 
    {
        if (Settings::g_gameSpeed == 3.0f)
        {
            Settings::g_gameSpeed = 1.0f;
        }
        else
        {
            Settings::g_gameSpeed += 1.0f;
        }
    };
    speedButton.p_updateFunction = [](float deltaTime, Button &button)
    {
        switch (static_cast<int>(Settings::g_gameSpeed))
        {
        case 1:
            button.p_image = Sprites::g_textures[Sprites::TextureIndex::SpeedButton1];
            break;
        case 2:
            button.p_image = Sprites::g_textures[Sprites::TextureIndex::SpeedButton2];
            break;
        case 3:
            button.p_image = Sprites::g_textures[Sprites::TextureIndex::SpeedButton3];
            break;
        default:
            button.p_image = Sprites::g_textures[Sprites::TextureIndex::SpeedButton1];
            break;
        }
    };
    speedButton.p_image = {0, 0, 0, 0, 0};
    speedButton.p_rect = {static_cast<float>(Settings::g_boundingSize), 245, 25, 25};
    speedButton.p_elementType = GuiType::GameGui;
    speedButton.p_textPosition = {0, 0};
    speedButton.p_imagePosition = {0, 0};
    speedButton.p_color = BLANK;
    speedButton.p_boundingColor = speedButton.p_color * 0.8f;
    speedButton.p_segments = 4.0f;
    speedButton.p_roundness = 5.0f;
    speedButton.p_boundingSize = 0.0f;
    speedButton.p_id = mgr_gui->GetAmountOfButtons();
    speedButton.p_isHovered = false;
    speedButton.p_visible = true;
#pragma endregion
}

void Speed::Init()
{
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
