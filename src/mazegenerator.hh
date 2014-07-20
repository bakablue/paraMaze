#ifndef MAZEGENERATOR_HH
# define MAZEGENERATOR_HH

# include <vector>
# include <map>
# include <stack>
# include <ctime>
# include <QtGui>
# include <QApplication>
# include <QWidget>
# include <QThread>
# include <unistd.h>

# include "cell.hh"
# include "colors.hh"

typedef std::vector<std::vector<Cell*> > TMaze;

class MazeGenerator : public QThread
{
        Q_OBJECT
    signals:
        void sendMaze(TMaze maze);
    public:
        // MazeGenerator(MazeGenerator &mg);
        MazeGenerator(int h, int w);
        ~MazeGenerator();
        void Print();
        void Generate();

    private:
        void run();
        std::vector<Cell*> getWalls(Cell* curr);
        Cell* getOpposite (Cell* c, Cell* w);

    public:
        int h_;
        int w_;
        TMaze maze_;
};


#endif /* !MAZEGENERATOR_HH */
