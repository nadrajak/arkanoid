// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/27/20

#include "game/CGame.h"

#include "core/CGraphics.h"

#include "entities/CPaddle.h"
#include "entities/CBall.h"
#include "entities/CBrick.h"
#include "entities/powerups/CBonusWidePaddle.h"
#include "entities/powerups/CBonusFastPaddle.h"
#include "entities/powerups/CBonusHealth.h"
#include "entities/powerups/CBonusCatch.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <random>


CGame::CGame(int width, int height)
{
    // Set map dimensions
    m_Width = width;
    m_Height = height;
    if (m_Width < CGraphics::WINDOW_WIDTH || m_Height < CGraphics::WINDOW_HEIGHT) {
        m_Width = CGraphics::WINDOW_WIDTH;
        m_Height = CGraphics::WINDOW_HEIGHT;
    }

    m_Levels.push(CLevel("assets/maps/1"));
    m_Levels.push(CLevel("assets/maps/2"));
    m_Levels.push(CLevel("assets/maps/3"));
    m_Bricks = m_Levels.front().Bricks();

    // Spawn player
    int x = 32;
    int y = m_Height - 3 * 16;
    m_Paddle = std::make_shared<CPaddle>(x, y);

    // @source: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    // Initialize random engine
    m_RandomEngine = std::mt19937(std::random_device{}());
}

void CGame::NextLevel()
{
    m_Levels.pop();
    if (m_Levels.empty()) {
        return;
    }
    m_Bricks = m_Levels.front().Bricks();

    m_Balls.clear();
    m_AddedBalls.clear();
    m_Bonuses.clear();
    m_AddedBonuses.clear();

    m_Paddle->ResetState();
}

void CGame::Update(CScoreboard &scoreboard, const CInput &input)
{
    UpdateObjects(input);
    ResolveCollision(scoreboard);
}

void CGame::UpdateObjects(const CInput &input)
{
    m_Paddle->ProcessInput(input);
    m_Paddle->Move();
    if (m_Paddle->Shooting() && !ActiveBalls()) {
        std::shared_ptr<CBall> ball = std::make_shared<CBall>(m_Paddle->Rect().x, m_Paddle->Rect().y);
        // Move ball on top of the paddle and align ball center with paddle center
        // (so that we dont have to care about the size of the ball)
        ball->SetX(m_Paddle->Rect().x + (m_Paddle->Rect().w - ball->Rect().w) / 2.0);
        ball->SetY(m_Paddle->Rect().y - ball->Rect().h);
        // Add ball into play
        m_AddedBalls.push_back(ball);
    }

    for (const auto &projectile : m_Balls) {
        projectile->Move();
    }
    for (const auto &bonus : m_Bonuses) {
        bonus->Move();
    }
}

void CGame::ResolveCollision(CScoreboard &scoreboard)
{
    // Bonuses
    for (const auto &bonus : m_Bonuses) {
        if (bonus->Rect().y > m_Height) {
            bonus->Deactivate();
            continue;
        }
        if (bonus->Intersects(*m_Paddle)) {
            bonus->Apply(*m_Paddle);
            bonus->Deactivate();
        }
    }

    // Paddle
    if (m_Paddle->Rect().x < 0) {
        m_Paddle->SetX(0);
    }
    if (m_Paddle->Rect().x + m_Paddle->Rect().w > m_Width) {
        m_Paddle->SetX(m_Width - m_Paddle->Rect().w);
    }

    // Projectiles
    for (const auto &projectile : m_Balls) {
        if (projectile->Rect().y > m_Height) {
            m_Paddle->LoseLife();
            projectile->Deactivate();
            continue;
        }

        if (projectile->Rect().x < 0) {
            projectile->SetX(0);
            projectile->HitWall();
        }
        if (projectile->Rect().x + projectile->Rect().w > m_Width) {
            projectile->SetX(m_Width - projectile->Rect().w);
            projectile->HitWall();
        }
        if (projectile->Rect().y < 0) {
            projectile->SetY(0);
            projectile->HitCeiling();
        }

        std::shared_ptr<CBrick> collidingBrick = GetCollidingBrick(*projectile);
        if (collidingBrick) {
            projectile->HitBrick(collidingBrick);
            collidingBrick->DecreaseHealth();
        }

        if (projectile->Intersects(*m_Paddle)) {
            projectile->HitPaddle(m_Paddle);
        }
    }

    // If a brick was destroyed this iteration increase the score and spawn a random bonus in it's place
    for (const auto &brick : m_Bricks) {
        if (!brick->Active()) {
            std::uniform_int_distribution<> distribution(0, 3);
            if (m_Bonuses.size() + m_AddedBonuses.size() < 4 && distribution(m_RandomEngine) == 0) {
                int x = brick->Rect().x + brick->Rect().w / 2 - 32 / 2;
                int y = brick->Rect().y;
                SpawnRandomBonus(x, y);
            }
            scoreboard.IncreaseCurrentScore(brick->Value());
        }
    }

    RemoveInactive();
    FlipDoubleBuffers();
}

void CGame::Render(CGraphics &graphics, int xOffset, int yOffset)
{
    for (const auto &brick : m_Bricks) {
        brick->Render(graphics, brick->Rect().x + xOffset, brick->Rect().y + yOffset);
    }
    for (const auto &bonus : m_Bonuses) {
        bonus->Render(graphics, bonus->Rect().x + xOffset, bonus->Rect().y + yOffset);
    }
    for (const auto &projectile : m_Balls) {
        projectile->Render(graphics, projectile->Rect().x + xOffset, projectile->Rect().y + yOffset);
    }
    m_Paddle->Render(graphics, m_Paddle->Rect().x + xOffset, m_Paddle->Rect().y + yOffset);
}

std::shared_ptr<CBrick> CGame::GetCollidingBrick(const CGameObject &object)
{
    std::shared_ptr<CBrick> collidingBrick = nullptr;
    double overlap = 0;
    double maxOverlap = 0;

    for (const auto &brick : m_Bricks) {
        if (object.Intersects(*brick)) {
            overlap = object.CalculateOverlap(*brick);
            if (overlap > maxOverlap) {
                maxOverlap = overlap;
                collidingBrick = brick;
            }
        }
    }

    return collidingBrick;
}

bool CGame::ActiveBalls() const
{
    return !m_Balls.empty() || !m_AddedBalls.empty();
}

size_t CGame::RemainingBricks() const
{
    return m_Bricks.size() > 0;
}

bool CGame::GameOver() const
{
    return (!m_Paddle->Lives() && RemainingBricks() && !ActiveBalls())
        || (m_Levels.empty() && !RemainingBricks());
}

bool CGame::LevelOver() const
{
    return !RemainingBricks();
}

void CGame::FlipDoubleBuffers()
{
    m_Balls.insert(m_Balls.end(), m_AddedBalls.begin(), m_AddedBalls.end());
    m_Bonuses.insert(m_Bonuses.end(), m_AddedBonuses.begin(), m_AddedBonuses.end());
    m_AddedBalls.clear();
    m_AddedBonuses.clear();
}

void CGame::RemoveInactive()
{
    auto inactive = [](std::shared_ptr<CGameObject> object) { return !object->Active(); };

    m_Bricks.erase(std::remove_if(m_Bricks.begin(), m_Bricks.end(), inactive), m_Bricks.end());
    m_Bonuses.erase(std::remove_if(m_Bonuses.begin(), m_Bonuses.end(), inactive), m_Bonuses.end());
    m_Balls.erase(std::remove_if(m_Balls.begin(), m_Balls.end(), inactive), m_Balls.end());
}

void CGame::SpawnRandomBonus(int x, int y)
{
    std::uniform_int_distribution<> distrib(0, 3);
    switch (distrib(m_RandomEngine)) {
        case 0:
            m_AddedBonuses.push_back(std::make_shared<CBonusWidePaddle>(x, y));
            break;
        case 1:
            m_AddedBonuses.push_back(std::make_shared<CBonusFastPaddle>(x, y));
            break;
        case 2:
            m_AddedBonuses.push_back(std::make_shared<CBonusHealth>(x, y));
            break;
        case 3:
            m_AddedBonuses.push_back(std::make_shared<CBonusCatch>(x, y));
            break;
    }
}

size_t CGame::Lives() const
{
    return m_Paddle->Lives();
}
