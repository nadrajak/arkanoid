// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/27/20

#pragma once

#include "game/CScoreboard.h"
#include "core/CInput.h"
#include "game/CLevel.h"

class CGraphics;
class CGameObject;
class CPaddle;
class CBall;
class CBrick;
class CBonus;

#include <SDL2/SDL.h>

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <random>
#include <queue>


/**
 * Class representing the game instance.
 * Holds level data, containers of game objects and implements the game logic.
 */
class CGame {
public:
    /** Ctor: loads a level and spawns a player */
    explicit CGame(int width = 0, int height = 0);

    /**
     * Method to encapsulate the logic of the game
     * @param scoreboard for access to current score
     */
    void Update(CScoreboard &scoreboard, const CInput &input);
    /**
     * Method to encapsulate rendering of the whole game
     * @param graphics class responsible for rendering
     * @param xOffset, yOffset needed if the game coordinates are not the same as the window coordinates
     *  (for example when the game doesn't take up the whole screen)
     */
    void Render(CGraphics &graphics, int xOffset = 0, int yOffset = 0);

    /** Encapsulates everything that needs to be done to switch to a next level of the game */
    void NextLevel();

    /** @return true if there is at least one ball currently on screen */
    bool ActiveBalls() const;
    /** @return true if the player has no lives or finished the last level */
    bool GameOver() const;
    /** @return true if the player finished the current level */
    bool LevelOver() const;

    /** @return the amount of lives the player has */
    size_t Lives() const;

private:
    void UpdateObjects(const CInput &input);
    void ResolveCollision(CScoreboard &scoreboard);

    /**
     * Check if the object is colliding with a brick, if colliding with multiple
     * choose one, based on the the objects overlap area
     * @param game object to check against the bricks
     * @return a pointer to a brick if colliding (else nullptr)
     */
    std::shared_ptr<CBrick> GetCollidingBrick(const CGameObject &object);

    void SpawnRandomBonus(int x, int y);

    /** Removes game objects marked as inactive from internal containers */
    void RemoveInactive();

    /** Push created game objects into the internal containers */
    void FlipDoubleBuffers();

    /** @return the amound of remaining destroyable bricks on the map */
    size_t RemainingBricks() const;

    int m_Width;
    int m_Height;

    std::queue<CLevel> m_Levels;

    std::shared_ptr<CPaddle> m_Paddle;

    std::vector<std::shared_ptr<CBall> > m_Balls;
    std::vector<std::shared_ptr<CBall> > m_AddedBalls;

    std::vector<std::shared_ptr<CBrick> > m_Bricks;

    std::vector<std::shared_ptr<CBonus> > m_Bonuses;
    std::vector<std::shared_ptr<CBonus> > m_AddedBonuses;

    std::mt19937 m_RandomEngine;
};
