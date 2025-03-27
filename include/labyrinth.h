#ifndef LABYRINTH_H
#define LABYRINTH_H
#include <string>
#include <vector>
#include <bits/stdc++.h>

class Labyrinth {
public:
    Labyrinth();

    ~Labyrinth();


    void initLabyrinth(const std::string &filename);

    int importLabyrinth(const std::string &filename);

    void getHeroPos(int findNum);

    void printLabyrinth();

    void printLabyrinthWithPath();

private:
    std::vector<int> labyrinthArr;
    std::queue<int> waveQueue;

    int getCell(int row, int col) const;
    void setCell(int row, int col, int value);

    //Пускаем волны
    void goWave(int row, int col);

    //Ищем выход
    void findPath(int row, int col);

    int getMaxWave();

    // используемые размеры в массиве, в зависимости от файла
    int arrUsedRows, arrUsedCols;
};

#endif
