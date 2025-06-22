// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/5/20

#include "entities/powerups/CBonusFastPaddle.h"

#include "entities/CPaddle.h"


const std::string CBonusFastPaddle::TEXTURE_SOURCE = "assets/sprites/bonus-red.bmp";

CBonusFastPaddle::CBonusFastPaddle(int x, int y)
        : CBonus(TEXTURE_SOURCE, x, y)
{}

void CBonusFastPaddle::Apply(CPaddle &player) const
{
    player.SetState(CPaddle::EState::FAST);
}

