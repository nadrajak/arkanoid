// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/27/20

#include "entities/powerups/CBonus.h"

#include "entities/CPaddle.h"

#include <iostream>


const int CBonus::TEXTURE_WIDTH = 32;
const int CBonus::TEXTURE_HEIGHT = 16;

const int CBonus::DEFAULT_VELOCITY = 1;
const int CBonus::DEFAULT_SPEED = 2;

CBonus::CBonus(const std::string &textureFilepath, int x, int y)
    : CMovableObject(textureFilepath, x, y, TEXTURE_WIDTH, TEXTURE_HEIGHT, DEFAULT_SPEED, 0, DEFAULT_VELOCITY)
{}

void CBonus::Move()
{
    m_Pos += m_Velocity * m_Speed;
}
