// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/11/20

#include "states/CScreenScoreboard.h"
#include "core/CInput.h"


CScreenScoreboard::CScreenScoreboard(std::shared_ptr<CScoreboard> scoreboard)
    : m_Scoreboard(scoreboard)
{
    PAGE_HEADER_TEXT = "SCOREBOARD";
    BACK_BUTTON_KEYBIND_TEXT = "ESCAPE";
    BACK_BUTTON_TEXT = "BACK TO MENU";
}

void CScreenScoreboard::Update(const CInput &input)
{
    ProcessInput(input);
}

void CScreenScoreboard::ProcessInput(const CInput &input)
{
    if ((input.KeyDown(SDL_SCANCODE_ESCAPE) && !input.KeyHeld(SDL_SCANCODE_ESCAPE))
            || (input.KeyDown(SDL_SCANCODE_RETURN) && !input.KeyHeld(SDL_SCANCODE_RETURN))) {
        m_Quit = true;
    }
}

void CScreenScoreboard::Render(CGraphics &graphics)
{
    // Bricks scoreboard data
    std::vector<size_t> data = m_Scoreboard->Data();

    // Render the header
    size_t x = HORIZONTAL_PADDING;
    size_t y = LINE_HEIGHT;
    graphics.RenderText(PAGE_HEADER_TEXT, x, y);

    // Calculate how much score lines to print
    int reservedLines = 5;
    size_t scoreLines = ((CGraphics::WINDOW_HEIGHT) / LINE_HEIGHT) - reservedLines;

    // Render the scores
    x = 2 * HORIZONTAL_PADDING;
    y += LINE_HEIGHT;
    for (size_t i = 0; i < scoreLines; ++i) {
        if (i < data.size()) {
            graphics.RenderText(std::to_string(data[i]), x, y);
        }
        y += LINE_HEIGHT;
    }

    // Render back button
    x = HORIZONTAL_PADDING;
    y += LINE_HEIGHT;
    graphics.RenderText("[ " + BACK_BUTTON_KEYBIND_TEXT + " ]  " + BACK_BUTTON_TEXT, x, y, SELECTED_TEXT_COLOR);
}
