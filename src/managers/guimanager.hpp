#pragma once
#include <vector>
#include <functional>
#include "../enums/gamestate.hpp"
#include "../structs/label.hpp"
#include "../structs/button.hpp"

class GuiManager
{
private:

    GameState m_gameState = GameState::Menu;
    std::vector<Label> m_labels;
    std::vector<Button> m_buttons;

private:

    void UpdateTextPosition(Label &label);
    void UpdateTextPosition(Button &button);
    void UpdateImagePosition(Button &button);
    void UpdateImagePosition(Label &label);
    void UpdatePress(const float deltaTime,Button &button);
    void UpdateLabel(const float deltaTime,Label &label);
    void UpdateButton(const float deltaTime,Button &button);
    void DrawButton(const Button &button) const;
    void DrawLabel(const Label &label) const;
    const bool IsElementUsed(const Button &button) const;
    const bool IsElementUsed(const Label &label) const;

public:
    
    const size_t GetAmountOfLabels() const;
    const size_t GetAmountOfButtons() const;
    void ReserveButton(const size_t count);
    void ReserveLabel(const size_t count);
    Button& AddButton(const Button &button);
    Label& AddLabel(const Label &label);
    void RemoveButton(const int id);
    void RemoveLabel(const int id);
    void SyncGameState(const GameState gameState);
    void Update(const float deltaTime);
    void Draw() const;
    void Init();
    
};
