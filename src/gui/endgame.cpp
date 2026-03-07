#include "endgame.hpp"
#include "../core/game.hpp"
#include "../managers/guimanager.hpp"
#include "../managers/playermanager.hpp"
#include "../namespaces/settings.hpp"
#include "../structs/label.hpp"
#include "../utility/colorutil.hpp"
#include <cassert>

void EndGame::InitLabels() {
  constexpr size_t amountOfLabels = 1;
  mgr_gui->ReserveLabel(amountOfLabels);

#pragma region EndGameLabel
  Label &endGameLabel = mgr_gui->AddLabel(Label{});
  endGameLabel.p_text = "You lost...";
  endGameLabel.p_id = mgr_gui->GetAmountOfLabels();
  endGameLabel.p_rect = {(float)Settings::g_boundingSize + 10.0f, 100.0f,
                         250.0f, 25.0f};
  endGameLabel.p_color = RED;
  endGameLabel.p_boundingSize = 2.0f;
  endGameLabel.p_boundingColor = endGameLabel.p_color * 0.8f;
  endGameLabel.p_visible = false;
  endGameLabel.p_roundness = 0.0f;
  endGameLabel.p_updateFunction = [this](float deltaTime, Label &label) {
    PlayerState playerState = mgr_player->GetPlayerState();
    label.p_visible = (playerState == PlayerState::Dead ||
                       playerState == PlayerState::Victory);

    if (playerState == PlayerState::Dead) {
      label.p_color = RED;
      label.p_text = "You lost...";
    } else if (playerState == PlayerState::Victory) {
      label.p_color = GREEN;
      label.p_text = "You won!!!, Thanks for playing RETRO SIEGE TD!";
    }

    label.p_boundingColor = label.p_color * 0.8f;
  };
#pragma endregion
}

void EndGame::InitButtons() {
  constexpr size_t amountOfButtons = 1;
  mgr_gui->ReserveButton(amountOfButtons);

#pragma region RestartButton
  Button &restartButton = mgr_gui->AddButton(Button{});
  restartButton.p_text = "Restart";
  restartButton.p_id = mgr_gui->GetAmountOfButtons();
  restartButton.p_rect = {(float)Settings::g_boundingSize + 85.0f, 130.0f,
                          100.0f, 25.0f};
  restartButton.p_color = RED;
  restartButton.p_boundingSize = 2.0f;
  restartButton.p_boundingColor = restartButton.p_color * 0.8f;
  restartButton.p_visible = false;
  restartButton.p_roundness = 0.0f;
  restartButton.p_updateFunction = [this](float deltaTime, Button &button) {
    PlayerState playerState = mgr_player->GetPlayerState();
    button.p_visible = (playerState == PlayerState::Dead ||
                        playerState == PlayerState::Victory);

    if (playerState == PlayerState::Dead) {
      button.p_color = RED;
    } else if (playerState == PlayerState::Victory) {
      button.p_color = GREEN;
    }

    button.p_boundingColor = button.p_color * 0.8f;
  };
  restartButton.p_onPressed = [this](float deltaTime, Button &button) {
    mgr_game->Restart();
  };
#pragma endregion
}

void EndGame::InjectDependencies(Game *game, PlayerManager *playerManager,
                                 GuiManager *guiManager) {
  mgr_game = game;
  mgr_player = playerManager;
  mgr_gui = guiManager;
}

void EndGame::Init() {
  assert(mgr_game != nullptr && "Game wasn't injected and its dependency");
  assert(mgr_player != nullptr &&
         "PlayerManager wasn't injected and its dependency");
  assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");

  InitLabels();
  InitButtons();
}
