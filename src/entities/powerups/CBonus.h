// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/27/20

#pragma once

#include "entities/base/CMovableObject.h"

class CGraphics;
class CPaddle;

#include "core/CVector2.h"

#include <string>
#include <memory>


/** Abstract class representing pickupable falling bonuses that drop from bricks upon destruction */
class CBonus : public CMovableObject {
public:
    CBonus(const std::string &textureFilepath, int x, int y);

    void Move() override;

    /**
     * Pure virtual method, used to apply a bonus to the player
     * @param player: the player to apply itself to
     */
    virtual void Apply(CPaddle &player) const = 0;

private:
    // Constants
    static const int TEXTURE_WIDTH;
    static const int TEXTURE_HEIGHT;
    // no actual texture since this is an abstract class

    static const int DEFAULT_VELOCITY;
    static const int DEFAULT_SPEED;
};
