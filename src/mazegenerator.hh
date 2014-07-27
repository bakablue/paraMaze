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
  MazeGenerator(int h, int w, bool perfect);
  ~MazeGenerator();
  void Print(bool p = true);
  void Generate();
  void Generate2();

private:
  void run();
  std::vector<Cell*> getNotVisited();
  TMaze getFullMaze();
  std::vector<Cell*> getWalls(Cell* curr);
  std::vector<Cell*> getNeigh(Cell* curr);
  Cell* getOpposite (Cell* c, Cell* w);
  void RemoveWall(Cell* c1, Cell* c2);
  int getRandom(int max);

public:
  int h_;
  int w_;
  bool perfect_;
  TMaze maze_;
};


#endif /* !MAZEGENERATOR_HH */
