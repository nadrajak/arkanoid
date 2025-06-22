// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 6/21/20

#include "game/CLevel.h"


CLevel::CLevel(const std::string &filename)
    : m_Rows(18), m_Cols(13), m_LevelSource(filename)
{
    std::vector<std::vector<size_t> > data = LoadData();
    BuildLevel(data);
}

std::vector<std::vector<size_t> > CLevel::LoadData()
{
    std::vector<std::vector<size_t> > level;
    level.resize(m_Rows , std::vector<size_t>(m_Cols, static_cast<size_t>(TileType::BACKGROUND)));

    std::ifstream file;
    std::string line;

    file.open(m_LevelSource);
    if (!file) {
        throw std::runtime_error("Error opening \"" + m_LevelSource + "\".");
    }

    size_t x = 0;
    size_t y = 0;
    while (true) {
        std::string line;

        if (!(file >> line >> std::ws)) {
            if (file.eof()) {
                break;
            }
            throw std::runtime_error("Error reading from \"" + m_LevelSource + "\".");
        }

        if (y >= m_Rows) {
            std::cout << "Invalid map format from \"" + m_LevelSource + "\" source." << std::endl;
            std::cout << "Ignoring extra rows..." << std::endl;
            break;
        }

        for(auto c : line) {
            if (x >= m_Cols) {
                std::cout << "Invalid map format from \"" + m_LevelSource + "\" source." << std::endl;
                std::cout << "Ignoring extra columns..." << std::endl;
                break;
            }

            if (!std::isdigit(c)) {
                throw std::runtime_error("Error loading level - invalid character in \"" + m_LevelSource + "\" level source.");
            }
            level[y][x] = c - '0';
            ++x;
        }
        ++y;
        x = 0;
    }

    return level;
}

void CLevel::BuildLevel(std::vector<std::vector<size_t>> &data)
{
    int brickWidth = 32; //CBrick::TEXTURE_WIDTH;
    int brickHeight = 16; // CBrick::HEIGHT;
    int x = 0;
    int y = 0;

    for(auto row : data) {
        for (auto brick : row) {
            switch (static_cast<TileType>(brick)) {
                case BRICK_1:
                    m_Bricks.emplace_back(std::make_shared<CBrick>(x, y, 1));
                    break;
                case BRICK_2:
                    m_Bricks.emplace_back(std::make_shared<CBrick>(x, y, 2));
                    break;
                case BRICK_3:
                    m_Bricks.emplace_back(std::make_shared<CBrick>(x, y, 3));
                    break;
                default:
                    break;
            }
            x += brickWidth;
        }
        x = 0;
        y += brickHeight;
    }

    if (m_Bricks.empty()) {
        throw std::runtime_error("Invalid level - zero bricks.");
    }
}

std::vector<std::shared_ptr<CBrick> > CLevel::Bricks()
{
    return m_Bricks;
}
