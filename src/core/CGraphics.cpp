// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/19/20

#include "core/CGraphics.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>


const int CGraphics::SCALE = 2;
const int CGraphics::WINDOW_WIDTH = 416;
const int CGraphics::WINDOW_HEIGHT = 480;
const std::string CGraphics::FONT_PATH = "assets/sprites/slkscr.ttf";

CGraphics::CGraphics(int windowWidth, int windowHeight)
{
    m_Scale = SCALE;

    // Call SDL_Quit() to destroy
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("Unable to initialize SDL.");
    }
    // Call TTF_Quit() to destroy
    if (TTF_Init() != 0) {
        throw std::runtime_error("Unable to initialize TTF.");
    }

    // Call TTF_CloseFont(m_Font) to destroy
    int fontSize = 16; // in pixels
    m_Font = TTF_OpenFont(FONT_PATH.c_str(), fontSize);
    if (!m_Font) {
        throw std::runtime_error("Unable to Bricks font from " + FONT_PATH);
    }

    // Very crude downscaling
    // The game uses 416x480 windowed mode, therefore the smallest convetional resolution the game will handle is 640x480;
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int displayWidth = DM.w;
    int displayHeight = DM.h;
    while (m_Scale && (displayWidth < m_Scale * WINDOW_WIDTH || displayHeight < m_Scale * WINDOW_HEIGHT)) {
        --m_Scale;
    }
    std::string resolution = std::to_string(displayWidth) + "x" + std::to_string(displayHeight);
    if (m_Scale < 1) {
        throw std::runtime_error("Display resolution: " + resolution + "not supported.");
    }

    // Call SDL_DestroyWindow(m_Window) & SDL_DestroyRenderer(m_Renderer) to destroy
    if (SDL_CreateWindowAndRenderer(windowWidth * m_Scale, windowHeight * m_Scale, 0 , &m_Window, &m_Renderer) < 0) {
        throw std::runtime_error("Unable to crete SDL window and renderer.");
    }
    SDL_SetWindowTitle(m_Window, "");
}

CGraphics::~CGraphics()
{
    // Freer font
    TTF_CloseFont(m_Font);
    m_Font = nullptr;

    // Free textures
    for(auto entry : m_Textures) {
        if (entry.second) {
            SDL_DestroyTexture(entry.second);
            entry.second = nullptr;
        }
    }
    m_Textures.clear();

    // Free renderer
    if (m_Renderer) {
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }

    // Free window
    if (m_Window) {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }

    // Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}

void CGraphics::Render(SDL_Rect rect, const std::string &texureFilepath)
{
    if (!m_Textures.count(texureFilepath)) {
        SDL_Surface *tmpSurface = SDL_LoadBMP(texureFilepath.c_str());
        m_Textures[texureFilepath] = SDL_CreateTextureFromSurface(m_Renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);
    }

    SDL_Rect srcRect = {0, 0, rect.w, rect.h };
    SDL_Rect dstRect = {rect.x * m_Scale, rect.y * m_Scale, rect.w * m_Scale, rect.h * m_Scale};

    SDL_RenderCopy(m_Renderer, m_Textures[texureFilepath], &srcRect, &dstRect);
}

void CGraphics::Clear()
{
    SDL_RenderClear(m_Renderer);
}

void CGraphics::Present()
{
    SDL_RenderPresent(m_Renderer);
}

void CGraphics::RenderText(const std::string &text, int x, int y, SDL_Color color)
{
    SDL_Surface *tmpSurface = TTF_RenderText_Solid(m_Font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_Renderer, tmpSurface);
    SDL_Rect dstRect = {x * m_Scale, y * m_Scale, tmpSurface->w * m_Scale, tmpSurface->h * m_Scale};

    SDL_RenderCopy(m_Renderer, texture, nullptr, &dstRect);

    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (tmpSurface) {
        SDL_FreeSurface(tmpSurface);
        tmpSurface = nullptr;
    }
}
