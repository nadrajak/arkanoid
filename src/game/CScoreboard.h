// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/7/20

#pragma once

#include <vector>
#include <string>


/** Class representing the game wide scoreboard */
class CScoreboard {
public:
    /** Constructor: calls CScoreboard::Bricks internally */
    explicit CScoreboard(const std::string &filename);

    /** Destructor: calls CScoreboard::Save internally */
    ~CScoreboard();

    /** Insert current score into the internal score container */
    void SaveCurrentScore();

    /** Modify methods for current score member variable */
    void IncreaseCurrentScore(size_t amount);
    void ResetCurrentScore();

    /** Access methods to score data */
    size_t Highscore() const;
    size_t CurrentScore() const;
    std::vector<size_t> Data() const;

private:
    /** Bricks scoreboard data from m_Filename */
    void Load();

    /** Save scoreboard data to m_Filename */
    void Save();

    std::string m_Filename;

    size_t m_CurrentScore;
    std::vector<size_t> m_Scores;
};
