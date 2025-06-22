// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/11/20

#pragma once

#include "states/CScreen.h"
#include "core/CInput.h"

class CScoreboard;

#include <SDL2/SDL.h>

#include <vector>
#include <string>
#include <iostream>


/** Class representing the main menu of the application */
class CScreenMainMenu : public CScreen {
public:
    explicit CScreenMainMenu(std::shared_ptr<CScoreboard> scoreboard);

    ~CScreenMainMenu() override = default;

    void Update(const CInput &input) override;

    void Render(CGraphics &graphics) override;

private:
    void ProcessInput(const CInput &input) override;

    /** Selects the next item in the list */
    void NextItem();

    /** Selects the previous item in the list */
    void PreviousItem();

    /** Does the action tied to the item (such as setting the next screen or quit flag) */
    void ConfirmSelectedItem(const std::string &repr);


    size_t m_SelectedItem;
    std::vector<std::string> m_Items;

    std::shared_ptr<CScoreboard> m_Scoreboard;

    // Constants
    std::string NEW_GAME_BUTTON_TEXT;
    std::string SCOREBOARD_BUTTON_TEXT;
    std::string QUIT_BUTTON_TEXT;
    std::string QUIT_BUTTON_KEYBIND_TEXT;
};
