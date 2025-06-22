// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/26/20

#include "entities/CPaddle.h"

#include "core/CGraphics.h"
#include "entities/CBall.h"
#include "core/CInput.h"

#include <iostream>


const int CPaddle::WIDTH = 64;
const int CPaddle::WIDE_WIDTH = 128;
const int CPaddle::HEIGHT = 16;

const std::string CPaddle::DEFAULT_TEXTURE_SOURCE = "assets/sprites/paddle-default.bmp";
const std::string CPaddle::WIDE_TEXTURE_SOURCE = "assets/sprites/paddle-wide.bmp";
const std::string CPaddle::FAST_TEXTURE_SOURCE = "assets/sprites/paddle-red.bmp";
const std::string CPaddle::CATCH_TEXTURE_SOURCE = "assets/sprites/paddle-blue.bmp";

const double CPaddle::VELOCITY = 1;
const double CPaddle::DEFAULT_SPEED = 5;
const double CPaddle::FAST_SPEED = 7.5;

const int CPaddle::DEFAULT_LIVES = 1;

CPaddle::CPaddle(int x, int y)
        : CMovableObject(DEFAULT_TEXTURE_SOURCE, x, y, WIDTH, HEIGHT, DEFAULT_SPEED)
{
    m_State = EState::DEFAULT;
    m_Lives = DEFAULT_LIVES;
    m_IsShooting = false;
}

void CPaddle::SetState(CPaddle::EState state)
{
    // Keep paddle centered if changing size
    if (m_State != EState::WIDE && state == EState::WIDE) {
        m_Pos.x -= WIDTH / 2.0;
    }
    else if (m_State == EState::WIDE && state != EState::WIDE) {
        m_Pos.x += WIDTH / 2.0;
    }

    // Set state
    m_State = state;

    // Set texture according to state
    switch (m_State) {
        case FAST:
            SetTextureSource(FAST_TEXTURE_SOURCE);
            break;
        case CATCH:
            SetTextureSource(CATCH_TEXTURE_SOURCE);
            break;
        case WIDE:
            SetTextureSource(WIDE_TEXTURE_SOURCE);
            break;
        default:
            SetTextureSource(DEFAULT_TEXTURE_SOURCE);
            break;
    }

    // Set width according to state
    if (m_State == EState::WIDE) {
        m_Width = WIDE_WIDTH;
    }
    else {
        m_Width = WIDTH;
    }

    // Set speed according to state
    if (m_State == FAST) {
        m_Speed = FAST_SPEED;
    }
    else {
        m_Speed = DEFAULT_SPEED;
    }
}



void CPaddle::MoveLeft()
{
    m_Velocity.x -= CPaddle::VELOCITY;
}

void CPaddle::MoveRight()
{
    m_Velocity.x += CPaddle::VELOCITY;
}

void CPaddle::Shoot()
{
    m_IsShooting = true;
}

void CPaddle::ProcessInput(const CInput &input)
{
    m_IsShooting = false;

    if (input.KeyDown(SDL_SCANCODE_SPACE) && !input.KeyHeld(SDL_SCANCODE_SPACE)) {
        Shoot();
    }
    if (input.KeyDown(SDL_SCANCODE_A)) {
        MoveLeft();
    }
    if (input.KeyDown(SDL_SCANCODE_D)) {
        MoveRight();
    }
}

void CPaddle::SetLives(int amount)
{
    m_Lives = amount;
}

int CPaddle::Lives() const
{
    return m_Lives;
}

void CPaddle::Move()
{
    m_Pos += m_Velocity * m_Speed;
    m_Velocity = {0, 0};
}

void CPaddle::ResetState()
{
    SetState(DEFAULT);
}

void CPaddle::LoseLife()
{
    --m_Lives;
    ResetState();
}

void CPaddle::GainLife()
{
    ++m_Lives;
}

bool CPaddle::Shooting() const
{
    return m_IsShooting;
}

CPaddle::EState CPaddle::State() const
{
    return m_State;
}
