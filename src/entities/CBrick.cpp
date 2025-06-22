// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/4/20

#include "entities/CBrick.h"


const std::string CBrick::TEXTURE_SOURCE_1 = "assets/sprites/brick-blue.bmp";
const std::string CBrick::TEXTURE_SOURCE_2 = "assets/sprites/brick-green.bmp";
const std::string CBrick::TEXTURE_SOURCE_3 = "assets/sprites/brick-gold.bmp";
const std::string CBrick::DEFAULT_TEXTURE_PATH = "assets/sprites/brick-gray.bmp";
const int CBrick::TEXTURE_WIDTH = 32;
const int CBrick::TEXTURE_HEIGHT = 16;
const int CBrick::DEFAULT_SCORE_VALUE = 250;
const int CBrick::DEFAULT_HEALTH = 1;
const int CBrick::MAX_HEALTH = 3;

CBrick::CBrick(int x, int y, int health)
    : CGameObject(DEFAULT_TEXTURE_PATH, x, y, TEXTURE_WIDTH, TEXTURE_HEIGHT)
{
    m_ScoreValue = DEFAULT_SCORE_VALUE;

    // Enforce max health
    m_Health = health > MAX_HEALTH ? MAX_HEALTH : health;

    // Set texture according to health
    switch (m_Health) {
        case 1:
            SetTextureSource(TEXTURE_SOURCE_1);
            break;
        case 2:
            SetTextureSource(TEXTURE_SOURCE_2);
            break;
        case 3:
            SetTextureSource(TEXTURE_SOURCE_3);
            break;
    }
}

int CBrick::Value() const
{
    return m_ScoreValue;
}

void CBrick::DecreaseHealth()
{
    --m_Health;
    if (m_Health <= 0) {
        Deactivate();
    }
}
