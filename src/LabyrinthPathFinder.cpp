#include "LabyrinthPathFinder.h"

void LabyrinthPathFinder::initSolveLabyrinth(const std::string &filename) {
    if (labyrinth.importLabyrinth(filename) == 0) {
        labyrinth.getHeroPos(2);
        if (!labyrinth.waveQueue.empty()) {
            int heroIndex = labyrinth.waveQueue.front();
            int heroRow = heroIndex / labyrinth.arrUsedCols; //i = r*c+c
            int heroCol = heroIndex % labyrinth.arrUsedCols;
            printf("Hero pos: %d:%d\n", heroRow, heroCol);
        }
        labyrinth.printLabyrinth();

        // основной цикл
        while (!labyrinth.waveQueue.empty()) {
            int index = labyrinth.waveQueue.front();
            int currRow = index / labyrinth.arrUsedCols;
            int currCol = index % labyrinth.arrUsedCols;
            goWave(currRow, currCol);
        }

        labyrinth.getHeroPos(3);
        if (!labyrinth.waveQueue.empty()) {
            int exitIndex = labyrinth.waveQueue.front();
            int exitRow = exitIndex / labyrinth.arrUsedCols;
            int exitCol = exitIndex % labyrinth.arrUsedCols;
            printf("Exit pos: %d:%d\n", exitRow, exitCol);
        }
        labyrinth.printLabyrinth();

        // восстановление от выхода к старту
        if (!labyrinth.waveQueue.empty()) {
            int exitIndex = labyrinth.waveQueue.front();
            int exitRow = exitIndex / labyrinth.arrUsedCols;
            int exitCol = exitIndex % labyrinth.arrUsedCols;
            findPath(exitRow, exitCol);
        }

        size_t steps = labyrinth.waveQueue.size();
        if (steps > 0) {
            --steps; //шагов меньше точек
        }
        printf("Exit steps: %lu\n", steps);
        labyrinth.printLabyrinthWithPath();
    }
}

void LabyrinthPathFinder::goWave(int row, int col) {
    //нашли выход - прекращаем
    if ((col + 1 < labyrinth.arrUsedCols && labyrinth.getCell(row, col + 1) == 3) ||
        (row + 1 < labyrinth.arrUsedRows && labyrinth.getCell(row + 1, col) == 3) ||
        (row - 1 >= 0 && labyrinth.getCell(row - 1, col) == 3) ||
        (col - 1 >= 0 && labyrinth.getCell(row, col - 1) == 3)) {
        while (!labyrinth.waveQueue.empty()) {
            labyrinth.waveQueue.pop();
        }
        return;
    }

    //право
    if (col + 1 < labyrinth.arrUsedCols && labyrinth.getCell(row, col + 1) == 0) {
        labyrinth.setCell(row, col + 1, labyrinth.getCell(row, col) + 2);
        labyrinth.waveQueue.push(row * labyrinth.arrUsedCols + (col + 1));
    }

    //лево
    if (col - 1 >= 0 && labyrinth.getCell(row, col - 1) == 0) {
        labyrinth.setCell(row, col - 1, labyrinth.getCell(row, col) + 2);
        labyrinth.waveQueue.push(row * labyrinth.arrUsedCols + (col - 1));
    }

    //низ
    if (row + 1 < labyrinth.arrUsedRows && labyrinth.getCell(row + 1, col) == 0) {
        labyrinth.setCell(row + 1, col, labyrinth.getCell(row, col) + 2);
        labyrinth.waveQueue.push((row + 1) * labyrinth.arrUsedCols + col);
    }

    //вверх
    if (row - 1 >= 0 && labyrinth.getCell(row - 1, col) == 0) {
        labyrinth.setCell(row - 1, col, labyrinth.getCell(row, col) + 2);
        labyrinth.waveQueue.push((row - 1) * labyrinth.arrUsedCols + col);
    }
    labyrinth.waveQueue.pop();
}


void LabyrinthPathFinder::findPath(int row, int col) {
    int posValue = labyrinth.getCell(row, col);

    //Нашли героя - выходим
    if (posValue == 2)
        return;

    if (posValue == 3)
        posValue = labyrinth.getMaxWave() + 2;

    //соседняя вниз
    if (row + 1 < labyrinth.arrUsedRows && posValue - labyrinth.getCell(row + 1, col) == 2) {
        labyrinth.waveQueue.push((row + 1) * labyrinth.arrUsedCols + col);
        findPath(row + 1, col);
        labyrinth.setCell(row, col, 2);
        return;
    }

    //вверх
    if (row - 1 >= 0 && posValue - labyrinth.getCell(row - 1, col) == 2) {
        labyrinth.waveQueue.push((row - 1) * labyrinth.arrUsedCols + col);
        findPath(row - 1, col);
        labyrinth.setCell(row, col, 2);
        return;
    }

    // вправо
    if (col + 1 < labyrinth.arrUsedCols && posValue - labyrinth.getCell(row, col + 1) == 2) {
        labyrinth.waveQueue.push(row * labyrinth.arrUsedCols + (col + 1));
        findPath(row, col + 1);
        labyrinth.setCell(row, col, 2);
        return;
    }

    //влево
    if (col - 1 >= 0 && posValue - labyrinth.getCell(row, col - 1) == 2) {
        labyrinth.waveQueue.push(row * labyrinth.arrUsedCols + (col - 1));
        findPath(row, col - 1);
        labyrinth.setCell(row, col, 2);
    }
}
