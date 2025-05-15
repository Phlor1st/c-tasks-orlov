#ifndef LABYRINTHPATHFINDER_H
#define LABYRINTHPATHFINDER_H

#include "labyrinth.h"

class LabyrinthPathFinder : public Labyrinth {
public:
    void goWave(int row, int col);//Пускаем волны
    void findPath(int row, int col);//Ищем выход
    int getMaxWave(); // для метки выхода
    void initSolveLabyrinth(const std::string &filename);
};

#endif //LABYRINTHPATHFINDER_H
