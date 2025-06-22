// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/11/20

#include "states/CScreenGameOver.h"


CScreenGameOver::CScreenGameOver(std::shared_ptr<CScoreboard> scoreboard)
    : m_scoreboard(scoreboard)
{
    PAGE_HEADER_TEXT = "SCOREBOARD";
    YOUR_SCORE_TEXT = "YOUR SCORE";
    HIGHSCORE_ALERT_TEXT = "NEW HIGHSCORE";
    BACK_BUTTON_KEYBIND_TEXT = "ESCAPE";
    BACK_BUTTON_TEXT = "BACK TO MENU";
}

void CScreenGameOver::Update(const CInput &input)
{
    ProcessInput(input);
}

void CScreenGameOver::ProcessInput(const CInput &input)
{
    if (input.KeyDown(SDL_SCANCODE_ESCAPE) && !input.KeyHeld(SDL_SCANCODE_ESCAPE)) {
        m_Quit = true;
    }
    if (input.KeyDown(SDL_SCANCODE_RETURN) && !input.KeyHeld(SDL_SCANCODE_RETURN)) {
        m_Quit = true;
    }
}

void CScreenGameOver::Render(CGraphics &graphics)
{
    // Bricks scoreboard data
    std::vector<size_t> data = m_scoreboard->Data();

    // Render the header
    size_t x = HORIZONTAL_PADDING;
    size_t y = LINE_HEIGHT;
    graphics.RenderText(PAGE_HEADER_TEXT, x, y);
    x = 2 * HORIZONTAL_PADDING;
    y += LINE_HEIGHT;

    // Calculate how much lines of score to render
    int reservedLines = 8;
    size_t scoreLines = ((CGraphics::WINDOW_HEIGHT) / LINE_HEIGHT) - reservedLines;

    // Render scores
    for (size_t i = 0; i < scoreLines; ++i) {
        if (i < data.size()) {
            graphics.RenderText(std::to_string(data[i]), x, y);
        }
        y += LINE_HEIGHT;
    }

    // Render alert
    x = HORIZONTAL_PADDING;
    y += LINE_HEIGHT;
    if (m_scoreboard->CurrentScore() == m_scoreboard->Highscore()) {
        graphics.RenderText("! " + HIGHSCORE_ALERT_TEXT + " !", x, y);
    }

    // Render score
    x = HORIZONTAL_PADDING;
    y += LINE_HEIGHT;
    graphics.RenderText(YOUR_SCORE_TEXT + ": " + std::to_string(m_scoreboard->CurrentScore()), x, y);
    y += 2 * LINE_HEIGHT;

    // Render the back button
    graphics.RenderText("[ " + BACK_BUTTON_KEYBIND_TEXT + " ]  " + BACK_BUTTON_TEXT, x, y, SELECTED_TEXT_COLOR);
}
