// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/26/20

#pragma once

#include "entities/base/CMovableObject.h"

class CGame;
class CGraphics;
class CBall;
class CBonus;
class CBrick;

#include "core/CVector2.h"
#include "core/CInput.h"
#include <SDL2/SDL.h>

#include <memory>


/** Class representing the player controlled paddle used to reflect the bouncing ball */
class CPaddle : public CMovableObject {
public:
    CPaddle(int x, int y);

    void ProcessInput(const CInput &input);

    void Move() override;

    /** Enumeration representing the various states that can set by bonuses */
    enum EState { DEFAULT, FAST, WIDE, CATCH };

    void SetState(EState state);
    EState State() const;
    void ResetState();

    /** @return the amount of lives */
    int Lives() const;
    void GainLife();
    void LoseLife();
    void SetLives(int amount);

    /**  Check to see if the paddle is attempting to fire a projectile */
    bool Shooting() const;

private:
    // Methods to call when handling the player input
    void MoveLeft();
    void MoveRight();
    void Shoot();

    EState m_State;
    int m_Lives;
    bool m_IsShooting;

    // Constants
    static const std::string DEFAULT_TEXTURE_SOURCE;
    static const std::string WIDE_TEXTURE_SOURCE;
    static const std::string FAST_TEXTURE_SOURCE;
    static const std::string CATCH_TEXTURE_SOURCE;
    static const std::string LASER_TEXTURE_SOURCE;

    static const int WIDTH;
    static const int WIDE_WIDTH;
    static const int HEIGHT;

    static const double VELOCITY;
    static const double DEFAULT_SPEED;
    static const double FAST_SPEED;

    static const int DEFAULT_LIVES;
};


