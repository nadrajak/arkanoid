// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/15/20

#include "entities/base/CMovableObject.h"


CMovableObject::CMovableObject(const std::string &textureFilepath, int x, int y, int width, int height, double speed, double xVelocity, double yVelocity)
    : CGameObject(textureFilepath, x, y, width, height)
{
    m_Velocity = {xVelocity, yVelocity};
    m_Speed = speed;
}
