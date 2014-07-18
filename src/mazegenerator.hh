#ifndef MAZEGENERATOR_HH
# define MAZEGENERATOR_HH

# include <vector>
# include <map>
# include <stack>
# include <boost/random.hpp>

# include "cell.hh"
// # include "mystack.hh"


class MazeGenerator
{
    public:
        MazeGenerator(int h, int w);
        void Print();
        void Generate();

    private:
        std::vector<Cell*> getTotalCells();
        std::vector<Cell*> getNeighbourds(Cell* current, 
                                          std::vector<Cell*> totalCells);
        void makeWall(Cell* c1, Cell* c2);

    private:
        int h_;
        int w_;
        std::vector<std::vector<char> > maze_;
};


#endif /* !MAZEGENERATOR_HH */
