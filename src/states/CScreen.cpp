// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/12/20

#include "states/CScreen.h"


const int CScreen::LINE_HEIGHT = 32;
const int CScreen::HORIZONTAL_PADDING = 32;

const SDL_Color CScreen::DEFAULT_TEXT_COLOR = {255, 255, 255, 0};
const SDL_Color CScreen::SELECTED_TEXT_COLOR = {224, 215, 90, 0};

CScreen::CScreen()
    : m_Quit(false), m_NextScreen(nullptr)
{}

bool CScreen::Quit()
{
    return m_Quit;
}

std::shared_ptr<CScreen> CScreen::NextScreen()
{
    return m_NextScreen;
}

void CScreen::Reset()
{
    m_Quit = false;
    m_NextScreen = nullptr;
}
