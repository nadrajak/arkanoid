// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/11/20

#include "states/CScreenMainMenu.h"

#include "game/CScoreboard.h"
#include "states/CScreenScoreboard.h"
#include "states/CScreenGame.h"


CScreenMainMenu::CScreenMainMenu(std::shared_ptr<CScoreboard> scoreboard)
    : m_Scoreboard(scoreboard)
{
    NEW_GAME_BUTTON_TEXT = "NEW GAME";
    SCOREBOARD_BUTTON_TEXT = "SCOREBOARD";
    QUIT_BUTTON_TEXT = "QUIT";
    QUIT_BUTTON_KEYBIND_TEXT = "ESCAPE";

    m_SelectedItem = 0;
    m_Items = {
            NEW_GAME_BUTTON_TEXT,
            SCOREBOARD_BUTTON_TEXT,
            QUIT_BUTTON_TEXT
    };
}

void CScreenMainMenu::Update(const CInput &input)
{
    ProcessInput(input);
}

void CScreenMainMenu::ProcessInput(const CInput &input)
{
    if (input.KeyDown(SDL_SCANCODE_S) && !input.KeyHeld(SDL_SCANCODE_S)) {
        NextItem();
    }
    if (input.KeyDown(SDL_SCANCODE_W) && !input.KeyHeld(SDL_SCANCODE_W)) {
        PreviousItem();
    }
    if (input.KeyDown(SDL_SCANCODE_ESCAPE) && !input.KeyHeld(SDL_SCANCODE_ESCAPE)) {
        m_Quit = true;
    }
    if (input.KeyDown(SDL_SCANCODE_RETURN) && !input.KeyHeld(SDL_SCANCODE_RETURN)) {
        ConfirmSelectedItem(m_Items[m_SelectedItem]);
    }
}

void CScreenMainMenu::NextItem()
{
    m_SelectedItem = (m_SelectedItem + 1) % m_Items.size();
}

void CScreenMainMenu::PreviousItem()
{
    m_SelectedItem = (m_SelectedItem + m_Items.size() - 1) % m_Items.size();
}

void CScreenMainMenu::ConfirmSelectedItem(const std::string &repr)
{
    if (repr == NEW_GAME_BUTTON_TEXT) {
        m_NextScreen = std::make_shared<CScreenGame>(m_Scoreboard);
    }
    else if (repr == SCOREBOARD_BUTTON_TEXT) {
        m_NextScreen = std::make_shared<CScreenScoreboard>(m_Scoreboard);
    }
    else if (repr == QUIT_BUTTON_TEXT) {
        m_Quit = true;
    }
}

void CScreenMainMenu::Render(CGraphics &graphics)
{
    size_t x = 3 * HORIZONTAL_PADDING;
    size_t y = LINE_HEIGHT;

    std::string text;
    SDL_Color color;
    for (size_t i = 0; i < m_Items.size(); ++i) {
        y += LINE_HEIGHT;

        if (i == m_SelectedItem) {
            color = SELECTED_TEXT_COLOR;
        }
        else {
            color = DEFAULT_TEXT_COLOR;
        }

        if (m_Items[i] == QUIT_BUTTON_TEXT) {
            text = m_Items[i] + "  [ " + QUIT_BUTTON_KEYBIND_TEXT + " ]";
        }
        else {
            text = m_Items[i];
        }

        graphics.RenderText(text, x, y, color);
    }
}
