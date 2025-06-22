// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/5/20

#pragma once

#include "entities/powerups/CBonus.h"

#include "entities/CPaddle.h"


class CBonusFastPaddle : public CBonus {
public:
    CBonusFastPaddle(int x, int y);

    void Apply(CPaddle &player) const override;

private:
    // Constants
    static const std::string TEXTURE_SOURCE;
};



