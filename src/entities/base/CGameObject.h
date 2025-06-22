// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/27/20

#pragma once

class CGraphics;
class CGame;

class CPaddle;
class CBrick;
class CBall;
class CBonus;

#include "core/CVector2.h"
#include <SDL2/SDL_rect.h>

#include <memory>
#include <string>



/** Abstract class to represent a physical object in the game */
class CGameObject {
public:
    CGameObject(const std::string &textureSource, int x, int y, int width, int height);

    virtual ~CGameObject() = default;

    /** Render the game object to the application window using @param graphics class */
    virtual void Render(CGraphics &graphics, int x, int y);

    /** Set x coordinate of the object to @param */
    void SetX(int x);

    /** Set y coordinate of the object to @param */
    void SetY(int y);

    void SetTextureSource(const std::string &source);

    /** @return a struct of 4 integers, representing coords in 2D, width and height of the object */
    SDL_Rect Rect() const;

    /** @return true if the two objects are intersecting each other */
    bool Intersects(const CGameObject &object) const;

    /** @return the area of overlap between 2 objects */
    double CalculateOverlap(const CGameObject &object) const;

    /** Set a flag that tells the game that it no longer needs to keep track of this item (That it should be despawned) */
    void Deactivate();

    /** @return true if the game objects is active (should be kept in play) */
    bool Active() const;

protected:
    std::string m_TextureSource;

    CVector2 m_Pos;
    int m_Width;
    int m_Height;

    bool m_Active;
};
