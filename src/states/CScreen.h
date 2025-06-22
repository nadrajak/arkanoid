// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/11/20

#pragma once

#include "core/CGraphics.h"
#include "core/CInput.h"

#include <SDL2/SDL.h>

#include <memory>


/**
 * Abstract class representing an appliction "state" or a "screen",
 * where each screen has a distinct input handling, logic and rendering
 * (Such as different menus or the game screen)
 */
class CScreen {
public:
    CScreen();

    virtual ~CScreen() = default;

    /** Pure virtual method that encapsulates input handling and logic of the given screen */
    virtual void Update(const CInput &input) = 0;

    /** Pure virtual method that encapsulates the rendering of the whole screen */
    virtual void Render(CGraphics &graphics) = 0;

    /**
     * Method used to indicate that this screen is at the end of its lifetime
     * @return true if this screen should be popped from the screen stack
     */
    bool Quit();

    /**
     * Method used to specify what screen should be active in the next application loop iteration
     * @return pointer to the screen that should be pushed into the screen stack
     */
    std::shared_ptr<CScreen> NextScreen();

    /**
     * Reset the internal state of the current screen back to default
     * (at this moment its the Quit flag and NextScreen pointer)
     * */
    void Reset();

protected:
    virtual void ProcessInput(const CInput &input) = 0;

    bool m_Quit;
    std::shared_ptr<CScreen> m_NextScreen;

    // Constants
    static const int LINE_HEIGHT;
    static const int HORIZONTAL_PADDING;

    static const SDL_Color DEFAULT_TEXT_COLOR;
    static const SDL_Color SELECTED_TEXT_COLOR;
};
