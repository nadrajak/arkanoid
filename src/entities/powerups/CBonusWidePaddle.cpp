// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/13/20

#include "entities/powerups/CBonusWidePaddle.h"

#include "entities/CPaddle.h"

#include <iostream>


const std::string CBonusWidePaddle::TEXTURE_SOURCE = "assets/sprites/bonus-yellow.bmp";

CBonusWidePaddle::CBonusWidePaddle(int x, int y)
        : CBonus(TEXTURE_SOURCE, x, y)
{}

void CBonusWidePaddle::Apply(CPaddle &player) const
{
    player.SetState(CPaddle::EState::WIDE);
}
