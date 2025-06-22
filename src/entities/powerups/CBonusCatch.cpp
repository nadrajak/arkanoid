// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/14/20

#include "entities/powerups/CBonusCatch.h"

#include "entities/CPaddle.h"


const std::string CBonusCatch::TEXTURE_SOURCE = "assets/sprites/bonus-blue.bmp";

CBonusCatch::CBonusCatch(int x, int y)
    : CBonus(TEXTURE_SOURCE, x, y)
{}

void CBonusCatch::Apply(CPaddle &player) const
{
    player.SetState(CPaddle::EState::CATCH);
}
