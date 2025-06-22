// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/15/20

#pragma once

#include "entities/base/CGameObject.h"

#include <string>


/** Abstract class to represent a physical game object that can move */
class CMovableObject : public CGameObject {
public:
    CMovableObject(const std::string &textureFilepath, int x, int y, int width, int height, double speed, double xVelocity = 0, double yVelocity = 0);

    ~CMovableObject() override = default;

    /** Pure virtual method used to move the object on each iteration of the game loop */
    virtual void Move() = 0;

protected:
    /** Stores x, y velocity */
    CVector2 m_Velocity;

    /** Used to scale velocity vector */
    double m_Speed;
};
