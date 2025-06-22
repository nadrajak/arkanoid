// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/21/20

#pragma once

#include "entities/CBrick.h"

#include <string>
#include <vector>
#include <memory>
#include <istream>
#include <fstream>
#include <iostream>


class CLevel {
public:
    explicit CLevel(const std::string &filename);

    std::vector<std::shared_ptr<CBrick> > Bricks();

private:
    /** Helper enum that aids in loading level from file */
    enum TileType { BACKGROUND = 0, BRICK_1 = 1, BRICK_2 = 2, BRICK_3 = 3 };

    /**
     * Converts raw data from filename to a 2D vector
     * @param filename: file to load from
     * @return the data from filename represented in a 2D vector
     */
    std::vector<std::vector<size_t> > LoadData();

    /**
     * Build level (place brick) from the data provided
     * @param data: level data loaded by loadLevelData()
     */
    void BuildLevel(std::vector<std::vector<size_t>> &data);

    size_t m_Rows;
    size_t m_Cols;

    std::string m_LevelSource;

    std::vector<std::shared_ptr<CBrick> > m_Bricks;
};


