#ifndef LABYRINTHPATHFINDER_H
#define LABYRINTHPATHFINDER_H

#include "labyrinth.h"
#include <string>

class LabyrinthPathFinder{
    Labyrinth labyrinth;
public:
    void goWave(int row, int col);//Пускаем волны
    void findPath(int row, int col);//Ищем выход...
    void initSolveLabyrinth(const std::string &filename);
};
//handler, читает записывает
#endif //LABYRINTHPATHFINDER_H
