#include "LabyrinthPathFinder.h"

void LabyrinthPathFinder::initSolveLabyrinth(const std::string &filename) {
    if (importLabyrinth(filename) == 0) {
        getHeroPos(2);
        if (!waveQueue.empty()) {
            int heroIndex = waveQueue.front();
            int heroRow = heroIndex / arrUsedCols;
            int heroCol = heroIndex % arrUsedCols;
            printf("Hero pos: %d:%d\n", heroRow, heroCol);
        }
        printLabyrinth();

        while (!waveQueue.empty()) {
            int index = waveQueue.front();
            int currRow = index / arrUsedCols;
            int currCol = index % arrUsedCols;
            goWave(currRow, currCol);
        }

        getHeroPos(3);
        if (!waveQueue.empty()) {
            int exitIndex = waveQueue.front();
            int exitRow = exitIndex / arrUsedCols;
            int exitCol = exitIndex % arrUsedCols;
            printf("Exit pos: %d:%d\n", exitRow, exitCol);
        }
        printLabyrinth();

        if (!waveQueue.empty()) {
            int exitIndex = waveQueue.front();
            int exitRow = exitIndex / arrUsedCols;
            int exitCol = exitIndex % arrUsedCols;
            findPath(exitRow, exitCol);
        }

        printf("Exit steps: %lu\n", waveQueue.size() > 0 ? waveQueue.size() - 1 : 0);
        printLabyrinthWithPath();
    }
}

void LabyrinthPathFinder::goWave(int row, int col) {
    //нашли выход - прекращаем
    if ((col + 1 < arrUsedCols && getCell(row, col + 1) == 3) || (row + 1 < arrUsedRows && getCell(row + 1, col) == 3) ||
        (row - 1 >= 0 && getCell(row - 1, col) == 3) || (col - 1 >= 0 && getCell(row, col - 1) == 3)) {
        while (!waveQueue.empty()) {
            waveQueue.pop();
        }
        return;
        }

    if (col + 1 < arrUsedCols && getCell(row, col + 1) == 0) {
        setCell(row, col + 1, getCell(row, col) + 2);
        waveQueue.push(row * arrUsedCols + (col + 1));
    }

    if (col - 1 >= 0 && getCell(row, col - 1) == 0) {
        setCell(row, col - 1, getCell(row, col) + 2);
        waveQueue.push(row * arrUsedCols + (col - 1));
    }

    if (row + 1 < arrUsedRows && getCell(row + 1, col) == 0) {
        setCell(row + 1, col, getCell(row, col) + 2);
        waveQueue.push((row + 1) * arrUsedCols + col);
    }

    if (row - 1 >= 0 && getCell(row - 1, col) == 0) {
        setCell(row - 1, col, getCell(row, col) + 2);
        waveQueue.push((row - 1) * arrUsedCols + col);
    }
    waveQueue.pop();
}


int LabyrinthPathFinder::getMaxWave() {
    int maxWave = 0;
    for (int row = 0; row < arrUsedRows; ++row)
        for (int col = 0; col < arrUsedCols; ++col) {
            if (getCell(row, col) > maxWave)
                maxWave = getCell(row, col);
        }
    return maxWave;
}

void LabyrinthPathFinder::findPath(int row, int col) {
    int posValue = getCell(row, col);

    //Нашли героя - выходим
    if (posValue == 2)
        return;;

    if (posValue == 3)
        posValue = getMaxWave() + 2;

    if (row + 1 < arrUsedRows && posValue - getCell(row + 1, col) == 2) {
        waveQueue.push((row + 1) * arrUsedCols + col);
        findPath(row + 1, col);
        setCell(row, col, 2);
        return;
    }


    if (row - 1 >= 0 && posValue - getCell(row - 1, col) == 2) {
        waveQueue.push((row - 1) * arrUsedCols + col);
        findPath(row - 1, col);
        setCell(row, col, 2);
        return;
    }
    if (col + 1 < arrUsedCols && posValue - getCell(row, col + 1) == 2) {
        waveQueue.push(row * arrUsedCols + (col + 1));
        findPath(row, col + 1);
        setCell(row, col, 2);
        return;
    }
    if (col - 1 >= 0 && posValue - getCell(row, col - 1) == 2) {
        waveQueue.push(row * arrUsedCols + (col - 1));
        findPath(row, col - 1);
        setCell(row, col, 2);
    }
}

