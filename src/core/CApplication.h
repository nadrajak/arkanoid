// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/11/20

#pragma once

#include "core/CGraphics.h"
#include "core/CInput.h"

class CScreen;
class CScoreboard;

#include <SDL2/SDL.h>

#include <stack>
#include <memory>


/**
 * Class representing the whole application.
 * Keeps a stack of screens and manages the "game loop".
 * */
class CApplication {
public:
    /** Initializes scoreboard and pushes main menu screen into the stack */
    CApplication(int frameTime, const std::string &scoreboardSource);

    /** Method encapsulating the game loop */
    int Run();

private:
    CGraphics m_Graphics;
    CInput m_Input;

    std::stack<std::shared_ptr<CScreen> > m_Screens;
    std::shared_ptr<CScoreboard> m_Scoreboard;

    int m_FrameTime;
};


