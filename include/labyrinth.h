#ifndef LABYRINTH_H
#define LABYRINTH_H
#include <string>
#include <vector>
#include <bits/stdc++.h>
//загрузка и выгрузка лабиринта
class Labyrinth {
protected:
    std::vector<int> labyrinthArr;
    std::queue<int> waveQueue;
    int arrUsedRows;
    int arrUsedCols;

    int getCell(int row, int col) const;
    void setCell(int row, int col, int value);
    void getHeroPos(int findNum);

public:
    Labyrinth();
    virtual ~Labyrinth();

    int importLabyrinth(const std::string &filename);
    void printLabyrinth();
    void printLabyrinthWithPath();
    void solveLabyrinth(const std::string &filename);
};

#endif
