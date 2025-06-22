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


/** Class representing the scoreboard screen of the application */
class CScreenScoreboard : public CScreen {
public:
    ~CScreenScoreboard() override = default;

    explicit CScreenScoreboard(std::shared_ptr<CScoreboard> scoreboard);

    void Update(const CInput &input) override;

    void Render(CGraphics &graphics) override;

private:
    void ProcessInput(const CInput &input) override;


    std::shared_ptr<CScoreboard> m_Scoreboard;

    std::string PAGE_HEADER_TEXT;
    std::string BACK_BUTTON_KEYBIND_TEXT;
    std::string BACK_BUTTON_TEXT;
};
