// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/19/20

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <map>
#include <memory>


/** Class responsible for the graphical output of the application */
class CGraphics {
public:
    // Public Constants
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;

    /** Constructor initialized and creates an application window */
    explicit CGraphics(int windowWidth = WINDOW_WIDTH, int windowHeight = WINDOW_HEIGHT);

    /** Destroys the application window */
    ~CGraphics();

    /**
     * Renders a texture to the application window
     * @param dstRect: 4 integers representing 2D rectangle, top left coordinates, width and height
     * @param texureFilepath: path to the desired texture source
     */
    void Render(SDL_Rect dstRect, const std::string &texureFilepath);

    /**
     * Renders a text to the application window
     * @param text: assemble a texture from these letters
     * @param x, y: x, y coordinate of the top left corner of the assembled texture
     * @param color: color of the text
     */
    void RenderText(const std::string &text, int x, int y, SDL_Color color = {255, 255, 255, 0});

    /** Clears the application window */
    void Clear();

    /** Draw rendered textures on the application window */
    void Present();

private:
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
    TTF_Font *m_Font;

    /** Map for caching used textures to prevent loading same image twice */
    std::map<std::string, SDL_Texture *> m_Textures;

    int m_Scale;

    // Constants
    static const int SCALE;
    static const std::string FONT_PATH;
};
