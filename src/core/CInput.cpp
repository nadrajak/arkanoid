// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/21/20

#include "core/CInput.h"


CInput::CInput()
{
    m_Quit = false;

    //SDL_PumpEvents();
    SDL_GetKeyboardState(&m_KeyCount);

    m_KeyboardPressed.resize(m_KeyCount, false);
    m_KeyboardHeld.resize(m_KeyCount, false);
}

void CInput::Update()
{
    // Poll events and check for quit event
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            m_Quit = true;
        }
    }
    // SDL_PumpEvents();
    const uint8_t *tmp = SDL_GetKeyboardState(&m_KeyCount);

    // Copy pressed into held
    m_KeyboardHeld = m_KeyboardPressed;
    // Update pressed
    m_KeyboardPressed = std::vector<uint8_t>(tmp, tmp + m_KeyCount);
}

bool CInput::KeyDown(uint8_t key) const
{
    return m_KeyboardPressed[key];
}

bool CInput::KeyHeld(uint8_t key) const
{
    return m_KeyboardHeld[key];
}

bool CInput::Quit() const
{
    return m_Quit;
}
