#ifndef MAZEGENERATOR_HH
# define MAZEGENERATOR_HH

# include <vector>
# include <map>
# include <stack>
# include <ctime>
# include <QApplication>
# include <QWidget>
# include <unistd.h>

# include "cell.hh"
# include "colors.hh"


class MazeGenerator
{
    public:
        MazeGenerator(int h, int w, Colors* win);
        ~MazeGenerator();
        void Print();
        void Generate();
        void Generate2();

    private:
        std::vector<Cell*> getWalls(Cell* curr);
        Cell* getOpposite (Cell* c, Cell* w);

    private:
        int h_;
        int w_;
        std::vector<std::vector<Cell*> > maze_;
        Colors *window_;

};


#endif /* !MAZEGENERATOR_HH */
