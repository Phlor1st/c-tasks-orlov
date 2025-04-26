#include "labyrinth.h"
#include "LabyrinthPathFinder.h"
#include <iostream>
#include <fstream>
#include <sstream>

Labyrinth::Labyrinth() : arrUsedRows(0), arrUsedCols(0) {
}

Labyrinth::~Labyrinth() {
}

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
        std::cerr << "Ошибка открытия файла" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> tempArr;
    int rowCount = 0;
    int colExpect = -1;

    // файл построчно
    while (getline(file, line)) {
        std::stringstream ss(line); // используется для создания потока
        std::string cell;
        int colCount = 0;

        while (getline(ss, cell, ' ')) {
            tempArr.push_back(std::stoi(cell));
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
    labyrinthArr = std::move(tempArr);
    return 0;
}

void Labyrinth::printLabyrinth() {
    for (int row = 0; row < arrUsedRows; ++row) {
        for (int col = 0; col < arrUsedCols; ++col) {
            std::cout << std::setw(2) << getCell(row, col) << " ";
        }
        std::cout << std::endl;
    }
}

void Labyrinth::printLabyrinthWithPath() {
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


// void Labyrinth::initLabyrinth(const std::string &filename) {
//     if (importLabyrinth(filename) == 0) {
//
//         getHeroPos(2);
//         if (!waveQueue.empty()) {
//             int heroIndex = waveQueue.front();
//             int heroRow = heroIndex / arrUsedCols;
//             int heroCol = heroIndex % arrUsedCols;
//             printf("Hero pos: %d:%d\n", heroRow, heroCol);
//         }
//         printLabyrinth();
//
//         while (!waveQueue.empty()) {
//             int index = waveQueue.front();
//             int currRow = index / arrUsedCols;
//             int currCol = index % arrUsedCols;
//             goWave(currRow, currCol);
//         }
//
//         getHeroPos(3);
//         if (!waveQueue.empty()) {
//             int exitIndex = waveQueue.front();
//             int exitRow = exitIndex / arrUsedCols;
//             int exitCol = exitIndex % arrUsedCols;
//             printf("Exit pos: %d:%d\n", exitRow, exitCol);
//         }
//         printLabyrinth();
//
//         if (!waveQueue.empty()) {
//             int exitIndex = waveQueue.front();
//             int exitRow = exitIndex / arrUsedCols;
//             int exitCol = exitIndex % arrUsedCols;
//             findPath(exitRow, exitCol);
//         }
//
//         printf("Exit steps: %lu\n", waveQueue.size() > 0 ? waveQueue.size() - 1 : 0);
//         printLabyrinthWithPath();
//     }
// }


void Labyrinth::solveLabyrinth(const std::string &filename) {
    if (importLabyrinth(filename) == 0) {
        printLabyrinth();
    }
}