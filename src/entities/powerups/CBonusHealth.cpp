// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/13/20

#include "entities/powerups/CBonusHealth.h"

#include "entities/CPaddle.h"


const std::string CBonusHealth::TEXTURE_SOURCE = "assets/sprites/bonus-gray.bmp";

CBonusHealth::CBonusHealth(int x, int y)
        : CBonus(TEXTURE_SOURCE, x, y)
{}

void CBonusHealth::Apply(CPaddle &player) const
{
    player.GainLife();
    player.SetState(CPaddle::EState::DEFAULT);
}
