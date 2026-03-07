#include "mainmenu.hpp"
#include "../core/game.hpp"
#include "../utility/debugutil.hpp"
#include "../utility/colorutil.hpp"
#include "../namespaces/settings.hpp"
#include "../namespaces/music.hpp"
#include "../namespaces/sprites.hpp"
#include "../managers/guimanager.hpp"
#include <cassert>

void MainMenu::InitLabels()
{
    constexpr size_t amountOfLabels = 1;
    mgr_gui->ReserveLabel(amountOfLabels);

#pragma region TitleLabel
    Label &titleLabel = mgr_gui->AddLabel(Label{});
    titleLabel.p_text = "";
    titleLabel.p_image = Sprites::g_textures[Sprites::TextureIndex::RetroSiegeTD]; 
    titleLabel.p_updateFunction = [this](float deltaTime, Label &label) {};
    titleLabel.p_rect = {static_cast<float>(Settings::g_boundingSize), 10.0f, 270.0f, 50.0f};
    titleLabel.p_textPosition = {0, 0};
    titleLabel.p_color = BLANK;
    titleLabel.p_id = mgr_gui->GetAmountOfLabels();
    titleLabel.p_visible = true;
    titleLabel.p_elementType = GuiType::MenuGui;

#pragma endregion

}

void MainMenu::InitButtons()
{
    constexpr size_t amountOfButtons = 3;
    mgr_gui->ReserveButton(amountOfButtons);

#pragma region StartButton
    Button &startButton = mgr_gui->AddButton(Button{});
    startButton.p_text = "Play";
    startButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        if (!button.p_isHovered)
        {
            return;
        }
        m_pauseMode = true;
        mgr_game->StartGame();
    };
    startButton.p_updateFunction = [this](float deltaTime, Button &button) 
    {
        if (m_pauseMode)
        {
            button.p_text = "Press To Continue";
        }
        
    };
    startButton.p_image = {0, 0, 0, 0, 0};
    startButton.p_rect = {static_cast<float>(Settings::g_boundingSize) + 270.0f / 2.0f - 160.0f / 2.0f, 140.0f, 160.0f, 30.0f};
    startButton.p_textPosition = {0, 0};
    startButton.p_imagePosition = {0, 0};
    startButton.p_color = GREEN;
    startButton.p_id = mgr_gui->GetAmountOfButtons();
    startButton.p_isHovered = false;
    startButton.p_visible = true;
    startButton.p_elementType = GuiType::MenuGui;
    startButton.p_boundingColor = startButton.p_color * 0.8f;
    startButton.p_boundingSize = 2.0f;
#pragma endregion

#pragma region ExitButton
    Button &exitButton = mgr_gui->AddButton(Button{});
    exitButton.p_text = "Exit";
    exitButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        mgr_game->CloseGame();
    };
    exitButton.p_updateFunction = [](float deltaTime, Button &button) {};
    exitButton.p_image = {0, 0, 0, 0, 0};
    exitButton.p_rect = {static_cast<float>(Settings::g_boundingSize) + 270.0f / 2.0f - 160.0f / 2.0f, 180.0f, 160.0f, 30.0f};
    exitButton.p_textPosition = {0, 0};
    exitButton.p_imagePosition = {0, 0};
    exitButton.p_color = RED;
    exitButton.p_id = mgr_gui->GetAmountOfButtons();
    exitButton.p_isHovered = false;
    exitButton.p_visible = true;
    exitButton.p_elementType = GuiType::MenuGui;
    exitButton.p_boundingColor = exitButton.p_color * 0.8f;
    exitButton.p_boundingSize = 2.0f;
#pragma endregion

#pragma region MusicButton
    Button &musicButton = mgr_gui->AddButton(Button{});
    musicButton.p_text = "";
    musicButton.p_onPressed = [](float deltaTime, Button &button)
    {
        GameMusic::g_playMusic = !GameMusic::g_playMusic;
    };
    musicButton.p_updateFunction = [](float deltaTime, Button &button)
    {
        if (GameMusic::g_playMusic)
        {
            button.p_image = Sprites::g_textures[Sprites::TextureIndex::MusicOff];
        }
        else
        {
            button.p_image = Sprites::g_textures[Sprites::TextureIndex::MusicOn];
        }
    };
    musicButton.p_image = {0, 0, 0, 0, 0};
    musicButton.p_rect = {
        static_cast<float>(Settings::g_boundingSize) + 270.0f - 32.0f,
        270.0f - 32.0f,
        32.0f,
        32.0f
    };
    musicButton.p_textPosition = {0, 0};
    musicButton.p_imagePosition = {0, 0};
    musicButton.p_color = WHITE;
    musicButton.p_id = mgr_gui->GetAmountOfButtons();
    musicButton.p_isHovered = false;
    musicButton.p_visible = true;
    musicButton.p_elementType = GuiType::MenuGui;
    musicButton.p_boundingColor = musicButton.p_color * 0.8f;
    musicButton.p_boundingSize = 2.0f;
#pragma endregion
}

bool MainMenu::IsInPauseMode()
{
    return m_pauseMode;
}

void MainMenu::InjectDependencies(GuiManager *guiManager, Game *game)
{
    mgr_gui = guiManager;
    mgr_game = game;
}

void MainMenu::Init()
{
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
