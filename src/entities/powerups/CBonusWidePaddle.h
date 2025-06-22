// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/13/20

#pragma once

#include "entities/powerups/CBonus.h"

#include "entities/CPaddle.h"


class CBonusWidePaddle : public CBonus {
public:
    CBonusWidePaddle(int x, int y);

    void Apply(CPaddle &player) const override;

private:
    // Constants
    static const std::string TEXTURE_SOURCE;
};
