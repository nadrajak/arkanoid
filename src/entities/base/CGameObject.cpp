// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/5/20

#include "entities/base/CGameObject.h"

#include "core/CGraphics.h"

#include <iostream>


CGameObject::CGameObject(const std::string &textureSource, int x, int y, int width, int height)
        : m_TextureSource(textureSource), m_Pos({static_cast<double>(x), static_cast<double>(y)}), m_Width(width), m_Height(height), m_Active(true)
{}

void CGameObject::Render(CGraphics &graphics, int x, int y)
{
    SDL_Rect rect = Rect();
    rect.x = x;
    rect.y = y;
    graphics.Render(rect, m_TextureSource);
}

SDL_Rect CGameObject::Rect() const
{
    return {static_cast<int>(m_Pos.x), static_cast<int>(m_Pos.y), m_Width, m_Height};
}

bool CGameObject::Intersects(const CGameObject &object) const
{
    return Rect().x + Rect().w > object.Rect().x
           && object.Rect().x + object.Rect().w > Rect().x
           && Rect().y + Rect().h > object.Rect().y
           && object.Rect().y + object.Rect().h > Rect().y;
}

double CGameObject::CalculateOverlap(const CGameObject &object) const
{
    /**
     *   xLeft     xRight
     *   |         |
     *  -+---------+ --- yTop
     *   |         |
     *  -+---------+ --- yBottom
     *   |         |
     */

    int xLeftMax = std::max(object.Rect().x, Rect().x);
    int yTopMax = std::max(object.Rect().y, Rect().y);
    int xRightMin = std::min(object.Rect().x + object.Rect().w, Rect().x + Rect().w);
    int YBottomMin = std::min(object.Rect().y + object.Rect().h, Rect().y + Rect().h);

    double overlapArea = std::max(0, xRightMin - xLeftMax) * std::max(0, YBottomMin - yTopMax);
    return overlapArea;
}

void CGameObject::Deactivate()
{
    m_Active = false;
}

bool CGameObject::Active() const
{
    return m_Active;
}

void CGameObject::SetX(int x)
{
    m_Pos.x = x;
}

void CGameObject::SetY(int y)
{
    m_Pos.y = y;
}

void CGameObject::SetTextureSource(const std::string &source)
{
    m_TextureSource = source;
}
