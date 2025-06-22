// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/11/20

#pragma once

#include "states/CScreen.h"

#include "game/CScoreboard.h"
#include "core/CInput.h"

#include <SDL2/SDL.h>

#include <string>
#include <memory>
#include <iostream>


/** Class representing the screen shown after the game is over. */
class CScreenGameOver : public CScreen {
public:
    explicit CScreenGameOver(std::shared_ptr<CScoreboard> scoreboard);

    ~CScreenGameOver() override = default;

    void Update(const CInput &input) override;

    void Render(CGraphics &graphics) override;

private:
    void ProcessInput(const CInput &input) override;

    std::shared_ptr<CScoreboard> m_scoreboard;

    // Pseudo-constants
    std::string PAGE_HEADER_TEXT;
    std::string YOUR_SCORE_TEXT;
    std::string HIGHSCORE_ALERT_TEXT;
    std::string BACK_BUTTON_KEYBIND_TEXT;
    std::string BACK_BUTTON_TEXT;
};
