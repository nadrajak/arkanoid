// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/11/20

#include "states/CScreenGame.h"
#include "states/CScreenGameOver.h"


CScreenGame::CScreenGame(std::shared_ptr<CScoreboard> scoreboard)
    : m_Scoreboard(scoreboard)
{
    SCORE_TEXT = "SCORE";
    LIVES_TEXT = "LIVES";

    m_Scoreboard->ResetCurrentScore();
}

void CScreenGame::Update(const CInput &input)
{
    ProcessInput(input);

    m_Game.Update(*m_Scoreboard, input);

    if (m_Game.GameOver()) {
        m_Scoreboard->SaveCurrentScore();
        // set to true because we don't want to come back to a lost game anymore
        m_Quit = true;
        m_NextScreen = std::make_shared<CScreenGameOver>(m_Scoreboard);
    }
    else if (m_Game.LevelOver()) {
        m_Game.NextLevel();
    }
}

void CScreenGame::ProcessInput(const CInput &input)
{
    if (input.KeyDown(SDL_SCANCODE_ESCAPE) && !input.KeyHeld(SDL_SCANCODE_ESCAPE)) {
        m_Quit = true;
    }
}

void CScreenGame::Render(CGraphics &graphics)
{
    // Render the game
    m_Game.Render(graphics);

    // Render life counter & score
    std::string score = SCORE_TEXT + ": " + std::to_string(m_Scoreboard->CurrentScore());
    std::string lives = LIVES_TEXT + ": " + std::to_string(m_Game.Lives());
    graphics.RenderText(score, HORIZONTAL_PADDING / 2, LINE_HEIGHT / 1.5);
    graphics.RenderText(lives, HORIZONTAL_PADDING / 2, CGraphics::WINDOW_HEIGHT - LINE_HEIGHT / 1.5);
}


