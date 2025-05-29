#include "labyrinth.h"
#include "LabyrinthPathFinder.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

int Labyrinth::getCell(int row, int col) const {
    return labyrinthArr[row * arrUsedCols + col];
}

void Labyrinth::setCell(int row, int col, int val) {
    labyrinthArr[row * arrUsedCols + col] = val;
}

void Labyrinth::getHeroPos(int findNum) {
    for (int row = 0; row < arrUsedRows; ++row) {
        for (int col = 0; col < arrUsedCols; ++col) {
            if (getCell(row, col) == findNum) {
                waveQueue.push(row * arrUsedCols + col);
                return;
            }
        }
    }
}


int Labyrinth::importLabyrinth(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "fail open file" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> tempArr;
    int rowCount = 0;
    int colExpect = -1;

    // файл построчно
    while (std::getline(file, line)) {
        std::stringstream ss(line); // используется для создания потока
        std::string cell;
        int colCount = 0;

        while (std::getline(ss, cell, ' ')) {
            tempArr.push_back(std::stoi(cell));//строка в целое число
            ++colCount;
        }
        if (colCount > 0) {
            if (colExpect == -1) {
                colExpect = colCount;
            }
            ++rowCount;
        }
    }
    file.close();

    arrUsedRows = rowCount;
    arrUsedCols = colExpect;
    labyrinthArr = tempArr;
    return 0;
}

void Labyrinth::printLabyrinth() const {
    for (int row = 0; row < arrUsedRows; ++row) {
        for (int col = 0; col < arrUsedCols; ++col) {
            std::cout << std::setw(2) << getCell(row, col) << " ";
        }
        std::cout << std::endl;
    }
}

void Labyrinth::printLabyrinthWithPath() const {
    for (int row = 0; row < arrUsedRows; ++row) {
        for (int col = 0; col < arrUsedCols; ++col) {
            int posValue = getCell(row, col);
            if (posValue == 2)
                std::cout << "\033[1;32m" << std::setw(2) << posValue << "\033[0m ";
            else if (posValue == 1)
                std::cout << "\033[1;31m" << std::setw(2) << posValue << "\033[0m ";
            else {
                posValue = 0;
                std::cout << std::setw(2) << posValue << " ";
            }
        }
        std::cout << std::endl;
    }
}

int Labyrinth::getMaxWave() const {
    int maxWave = 0;
    for (int row = 0; row < arrUsedRows; ++row)
        for (int col = 0; col < arrUsedCols; ++col) {
            if (getCell(row, col) > maxWave)
                maxWave = getCell(row, col);
        }
    return maxWave;
}