// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/28/20

#pragma once

#include "entities/base/CMovableObject.h"

class CGame;
class CGraphics;
class CPaddle;
class CBrick;

#include "core/CVector2.h"


/** Class representing the basic projectile fired by the player to destroy bricks */
class CBall : public CMovableObject {
public:
    CBall(int x, int y, double xVelocity = 0, double yVelocity = -1);

    void Move() override;

    /**
     * Method responsible for correctly bouncing off of a paddle, depending on the point of impact
     * @param paddle: the paddle to bounce off of
     */
    void HitPaddle(std::shared_ptr<CPaddle> paddle);

    /**
     * Method responsible for correctly bouncing off of a brick, depeneding on side of impact
     * @param brick: the brick to bounce off of
     */
    void HitBrick(std::shared_ptr<CBrick> brick);

    /** Methods for flipping the x velocity (Named to fit in) */
    void HitWall();
    /** Method for flipping the y velocity (Named to fit in) */
    void HitCeiling();

private:
    /** Paddle attachment points (used to attach to the paddle when the catch bonus is active) */
    std::shared_ptr<CPaddle> m_CaughtBy;
    int m_CaughtAt;

    // Constants
    static const int TEXTURE_WIDTH;
    static const int TEXTURE_HEIGHT;
    static const std::string TEXTURE_SOURCE;

    static const double DEFAULT_VELOCITY;
    static const double DEFAULT_SPEED;
    static const double MAX_SPEED;
};
