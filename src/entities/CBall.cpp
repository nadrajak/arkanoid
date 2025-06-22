// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/28/20

#include "entities/CBall.h"

#include "entities/CPaddle.h"
#include "entities/CBrick.h"

#include <iostream>


const int CBall::TEXTURE_WIDTH = 16;
const int CBall::TEXTURE_HEIGHT = 16;
const std::string CBall::TEXTURE_SOURCE = "assets/sprites/ball.bmp";

const double CBall::DEFAULT_VELOCITY = 1;
const double CBall::DEFAULT_SPEED = 3;
const double CBall::MAX_SPEED = 8;

CBall::CBall(int x, int y, double xVelocity, double yVelocity)
    : CMovableObject(TEXTURE_SOURCE, x, y, TEXTURE_WIDTH, TEXTURE_HEIGHT, DEFAULT_SPEED, xVelocity, yVelocity)
{
    m_CaughtBy = nullptr;
    m_CaughtAt = 0;
}

void CBall::Move()
{
    if (m_CaughtBy && !m_CaughtBy->Shooting()) {
        m_Pos.x = m_CaughtBy->Rect().x - m_CaughtAt;
    }
    else {
        m_CaughtBy = nullptr;

        m_Pos.x += m_Velocity.x * m_Speed;
        m_Pos.y += m_Velocity.y * m_Speed;
    }
}

void CBall::HitPaddle(std::shared_ptr<CPaddle> paddle)
{
    // Move out of the paddle
    m_Pos.x -= m_Velocity.x * m_Speed;
    m_Pos.y -= m_Velocity.y * m_Speed;
    if (Rect().y >= paddle->Rect().y + paddle->Rect().h || Rect().y + Rect().h <= paddle->Rect().y) {
        m_Velocity.y *= -1;
        // Readjust y to make the ball flush with the paddle
        m_Pos.y = paddle->Rect().y - Rect().h;
    }
    else {
        m_Pos.x += m_Velocity.x * m_Speed;
        m_Pos.y += m_Velocity.y * m_Speed;
        return;
    }

    int ballCenter = Rect().x + Rect().w / 2;
    int paddleStart = paddle->Rect().x;
    int paddleEnd = paddle->Rect().x + paddle->Rect().w;
    int paddleQuarter = paddle->Rect().w / 4;

    // Bounce at different angles depending on part of the paddle hit
    if (ballCenter < paddleStart) {
        m_Velocity.y = -(DEFAULT_VELOCITY / 3);
        m_Velocity.x = -(DEFAULT_VELOCITY + 2 * (DEFAULT_VELOCITY / 3));
    }
    if (paddleStart + 0 * paddleQuarter < ballCenter && ballCenter <= paddleStart + 1 * paddleQuarter) {
        m_Velocity.y = -DEFAULT_VELOCITY;
        m_Velocity.x = -DEFAULT_VELOCITY;
    }
    if (paddleStart + 1 * paddleQuarter < ballCenter && ballCenter <= paddleStart + 2 * paddleQuarter) {
        m_Velocity.y = -(DEFAULT_VELOCITY + (DEFAULT_VELOCITY / 2));
        m_Velocity.x = -DEFAULT_VELOCITY / 2;
    }
    if (paddleStart + 2 * paddleQuarter < ballCenter && ballCenter <= paddleStart + 3 * paddleQuarter) {
        m_Velocity.y = -(DEFAULT_VELOCITY + (DEFAULT_VELOCITY / 2));
        m_Velocity.x = DEFAULT_VELOCITY / 2;
    }
    if (paddleStart + 3 * paddleQuarter < ballCenter && ballCenter <= paddleEnd) {
        m_Velocity.y = -DEFAULT_VELOCITY;
        m_Velocity.x = DEFAULT_VELOCITY;
    }
    if (paddleEnd < ballCenter) {
        m_Velocity.y = -(DEFAULT_VELOCITY / 3);
        m_Velocity.x = (DEFAULT_VELOCITY + 2 * (DEFAULT_VELOCITY / 3));
    }

    // Attach to paddle
    if (paddle->State() == CPaddle::EState::CATCH) {
        m_CaughtBy = paddle;
        m_CaughtAt = paddle->Rect().x - Rect().x;
    }
    else {
        m_CaughtBy = nullptr;
    }
}

void CBall::HitWall()
{
    m_Velocity.x *= -1;
}

void CBall::HitCeiling()
{
    m_Velocity.y *= -1;
}

void CBall::HitBrick(std::shared_ptr<CBrick> brick)
{
    // Move out of the brick
    m_Pos.x -= m_Velocity.x * m_Speed;
    m_Pos.y -= m_Velocity.y * m_Speed;

    // Check which side the projectile hit
    if (Rect().x >= brick->Rect().x + brick->Rect().w || Rect().x + Rect().w <= brick->Rect().x) {
        m_Velocity.x *= -1;
    }
    if (Rect().y >= brick->Rect().y + brick->Rect().h || Rect().y + Rect().h <= brick->Rect().y) {
        m_Velocity.y *= -1;
    }

    // Speed up the ball with each bounce
    if (m_Speed < MAX_SPEED) {
        //m_Speed *= 1.025;
        m_Speed += 0.05;
    } else {
        m_Speed = MAX_SPEED;
    }
}
