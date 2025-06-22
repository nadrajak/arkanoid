// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/4/20

#pragma once

#include "entities/base/CGameObject.h"

#include "entities/CBall.h"
class CGraphics;

#include <SDL2/SDL.h>

#include <memory>
#include <string>


/** Class representing the destroyable brick placed around the map */
class CBrick : public CGameObject {
public:
    CBrick(int x, int y, int health = DEFAULT_HEALTH);

    /** Method called when a projectile hits the brick */
    void DecreaseHealth();

    /** @return the score value this brick (added to players score upon destruction) */
    int Value() const;

protected:
    int m_Health;
    int m_ScoreValue;

    // Constants
    static const std::string DEFAULT_TEXTURE_PATH;
    static const int TEXTURE_WIDTH;
    static const int TEXTURE_HEIGHT;
    static const int DEFAULT_HEALTH;
    static const int MAX_HEALTH;
    static const int DEFAULT_SCORE_VALUE;

    static const std::string TEXTURE_SOURCE_1;
    static const std::string TEXTURE_SOURCE_2;
    static const std::string TEXTURE_SOURCE_3;
};
