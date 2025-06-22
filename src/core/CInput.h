// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/21/20

#pragma once

#include <SDL2/SDL.h>
#include <vector>


/** Class responsible for detecting input. */
class CInput {
public:
    CInput();

    /** Update keyboard state and check for window close event */
    void Update();

    /** @return true if key is pressed down */
    bool KeyDown(uint8_t key) const;

    /** @return true if key was pressed down the previous frame */
    bool KeyHeld(uint8_t key) const;

    /** @return true if the [x] on the application window was clicked */
    bool Quit() const;

private:
    std::vector<uint8_t> m_KeyboardPressed;
    std::vector<uint8_t> m_KeyboardHeld;
    int m_KeyCount;

    bool m_Quit;
};


