// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/7/20

#include "game/CScoreboard.h"

#include <fstream>
#include <iostream>
#include <algorithm>


CScoreboard::CScoreboard(const std::string &filename)
    : m_Filename(filename), m_CurrentScore(0)
{
    try {
        Load();
    }
    catch (const std::exception &e) {
        std::cout << e.what();
    }
}

void CScoreboard::IncreaseCurrentScore(size_t amount)
{
    m_CurrentScore += amount;
}

void CScoreboard::ResetCurrentScore()
{
    m_CurrentScore = 0;
}

void CScoreboard::SaveCurrentScore()
{
    // Don't litter the file with a 0 point score
    if (m_CurrentScore) {
        auto it = std::lower_bound(m_Scores.begin(), m_Scores.end(), m_CurrentScore, std::greater<int>());
        m_Scores.insert(it, m_CurrentScore);
    }
}

CScoreboard::~CScoreboard()
{
    try {
        Save();
    }
    catch (const std::exception &e) {
        std::cout << e.what();
    }
}

std::vector<size_t> CScoreboard::Data() const
{
    return m_Scores;
}

size_t CScoreboard::Highscore() const
{
    // Check if there is a highscore
    if (m_Scores.empty()) {
        return 0;
    }
    return *m_Scores.begin();
}

size_t CScoreboard::CurrentScore() const
{
    return m_CurrentScore;
}

void CScoreboard::Load()
{
    std::vector<size_t> tmp;

    std::ifstream file;
    file.open(m_Filename);
    if (!file) {
        std::cout << "File \"" + m_Filename + "\" does not exist." << std::endl;
        std::cout << "Creating \"" + m_Filename + "\"." << std::endl;
    }

    while (true) {
        std::string line;
        int score;

        if (!(file >> line >> std::ws)) {
            if (file.eof()) {
                break;
            }
            throw std::runtime_error("Error reading from \"" + m_Filename + "\".");
        }

        try {
            score = std::stoi(line);
            tmp.push_back(score);
        } catch (...) {
            std::cout << "Skipping invalid entry in " << m_Filename << std::endl;
        }
    }
    std::sort(tmp.begin(), tmp.end(), std::greater<int>());

    m_Scores = tmp;
    file.close();
}

void CScoreboard::Save()
{
    std::sort(m_Scores.begin(), m_Scores.end(), std::greater<int>());

    std::ofstream file;
    file.open(m_Filename);

    if (!file) {
        throw std::runtime_error("Error opening \"" + m_Filename + "\".");
    }
    for (auto score : m_Scores) {
        if (!(file << score << std::endl)) {
            throw std::runtime_error("Error writing to \"" + m_Filename + "\".");
        }
    }

    file.close();
}
