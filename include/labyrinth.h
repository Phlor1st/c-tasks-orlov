#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <string>
#include <vector>
#include <queue>
//загрузка и выгрузка лабиринта
class Labyrinth {
public:
    std::vector<int> labyrinthArr; // массив для карты
    std::queue<int> waveQueue; // очередь для волнового, алгоритма не в лабиринте
    int arrUsedRows;
    int arrUsedCols;

    int getCell(int row, int col) const;
    void setCell(int row, int col, int value);
    void getHeroPos(int findNum);

    Labyrinth() = default;

    int importLabyrinth(const std::string &filename);
    void printLabyrinth() const;
    void printLabyrinthWithPath() const;
    int getMaxWave() const;
};

#endif
