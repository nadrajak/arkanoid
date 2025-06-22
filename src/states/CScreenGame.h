// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/11/20

#pragma once

#include "states/CScreen.h"

#include "game/CGame.h"
class CScoreboard;

#include <SDL2/SDL.h>

#include <vector>
#include <string>
#include <iostream>


/** Class representing the screen shown while playing the game */
class CScreenGame : public CScreen {
public:
    explicit CScreenGame(std::shared_ptr<CScoreboard> scoreboard);

    ~CScreenGame() override = default;

    void Update(const CInput &input) override;

    void Render(CGraphics &graphics) override;

private:
    void ProcessInput(const CInput &input) override;

    CGame m_Game;
    std::shared_ptr<CScoreboard> m_Scoreboard;

    // Pseudo constants
    std::string SCORE_TEXT;
    std::string LIVES_TEXT;
};
