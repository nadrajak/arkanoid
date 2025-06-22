// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/11/20

#include <csignal>
#include "core/CApplication.h"

#include "states/CScreenMainMenu.h"
#include "game/CScoreboard.h"
#include "core/CInput.h"


void SignalHandler(int)
{
    throw std::runtime_error("Application stopped by force. (CTRL+C)");
}

CApplication::CApplication(int frameTime, const std::string &scoreboardSource)
    : m_Scoreboard(std::make_shared<CScoreboard>(scoreboardSource))
{
    m_FrameTime = frameTime;
    m_Screens.push(std::make_shared<CScreenMainMenu>(m_Scoreboard));
}

int CApplication::Run()
{
    double frameStart;
    double delay;
    std::shared_ptr<CScreen> screen;

    while (!m_Screens.empty()) {
        screen = m_Screens.top();

        frameStart = SDL_GetTicks();

        m_Input.Update();
        // If the [x] of the window was clicked
        if (m_Input.Quit()) {
            break;
        }

        screen->Update(m_Input);
        // Careful: we can pop and push in the same tick - "replace" a screen
        // That is done for screens that we dont want to come back to.
        // For example if we lose a game, the desired behaviour is to:
        //   1) pop the old Game from our screen stack
        //   2) push GameOver screen into the stack
        if (screen->Quit()) {
            m_Screens.pop();
        }
        if (screen->NextScreen()) {
            m_Screens.push(screen->NextScreen());
            screen->Reset();
        }

        m_Graphics.Clear();
        screen->Render(m_Graphics);
        m_Graphics.Present();

        // Very simple frame limiter (it can only wait - it cant play catch up)
        delay = frameStart + m_FrameTime - SDL_GetTicks();
        if (delay > 0) {
            SDL_Delay(delay);
        }

        signal(SIGTERM, SignalHandler);
        signal(SIGINT, SignalHandler);
    }

    return 1;
}


