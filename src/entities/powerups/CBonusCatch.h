// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/14/20

#pragma once

#include "entities/powerups/CBonus.h"

#include "entities/CPaddle.h"


class CBonusCatch : public CBonus {
public:
    CBonusCatch(int x, int y);

    void Apply(CPaddle &player) const override;

private:
    // Constants
    static const std::string TEXTURE_SOURCE;
};


