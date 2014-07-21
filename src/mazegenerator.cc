#include "mazegenerator.hh"

MazeGenerator::MazeGenerator(int h, int w, bool perfect)
    : QThread()
    , h_(h)
    , w_(w)
    , perfect_(perfect)
{
    if (perfect)
    {
        maze_ = std::vector<std::vector<Cell*> >(h_, std::vector<Cell*>(w_));
        
        for (int i = 0; i < h_; ++i)
        {
            for (int j = 0; j < w_; ++j)
            {
                Cell* c = new Cell(j, i);
                c->set_type(FREE);
                c->set_walls(new std::vector<bool>(4, true));
                maze_[i][j] = c;
            }
        }
        maze_[h - 1][0]->set_type(START);
        emit sendMaze(getFullMaze());   
    }
    else
    {
        maze_ = std::vector<std::vector<Cell*> >(h_, std::vector<Cell*>(w_));

        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                Cell* c = new Cell(j, i);
                c->set_type(WALL);
                maze_[i][j] = c;
            }
        }
        maze_[h - 1][0]->set_type(START);
        emit sendMaze(maze_);
    }
}


MazeGenerator::~MazeGenerator()
{
    for (int i = 0; i < h_; ++i)
        for (int j = 0; j < w_; ++j)
            free(maze_[i][j]);
}

void MazeGenerator::Generate()
{
    std::vector<Cell*> walls;

    Cell* current = maze_[h_ - 1][0];
    current->set_isInMaze(true);

    walls = getWalls(current);
    Cell* opp;

    while (walls.size() > 0)
    {
        int pos = getRandom(walls.size());

        Cell* w = walls[pos];

        opp = getOpposite(current, w);

        if (opp != nullptr && !opp->get_isInMaze())
        {
            w->set_type(FREE);
            w->set_isInMaze(true);
            opp->set_type(FREE);
            opp->set_isInMaze(true);
            current = opp;
            std::vector<Cell*> tmp = getWalls(current);
            walls.erase(walls.begin() + pos);
            walls.insert(walls.end(), tmp.begin(), tmp.end());
        }
        else
        {
            walls.erase(walls.begin() + pos);
        }
        emit sendMaze(maze_);
        usleep(50000);
    }
    maze_[0][w_ - 1]->set_type(END);
    emit sendMaze(maze_);
    Print();
}


void MazeGenerator::Generate2()
{
    Cell* current = maze_[h_ - 1][0];
    current->set_isInMaze(true);

    std::vector<Cell*> nvisited = getNotVisited();
    std::vector<Cell*> neigh;
    std::stack<Cell*> cs;

    while (nvisited.size() > 0)
    {
        neigh = getNeigh(current);
        if (neigh.size() > 0)
        {
            int pos = getRandom(neigh.size());
            Cell* c = neigh[pos];
            cs.push(c);
            RemoveWall(current, c);
            c->set_isInMaze(true);
            current = c;
        }
        else if (!cs.empty())
        {
            current = cs.top();
            cs.pop();
        }
        else
        {
            nvisited = getNotVisited();
            if (nvisited.size() > 0)
            {
                std::cout << nvisited.size() << std::endl;
                int pos = getRandom(nvisited.size());
                current = nvisited[pos];
                current->set_isInMaze(true);
            }
        }
        emit sendMaze(getFullMaze());
        // std::string name;
        // getline(std::cin, name);
        usleep(100000);
    }
    maze_[0][w_ - 1]->set_type(END);
    emit sendMaze(getFullMaze());
    Print();
}

void MazeGenerator::RemoveWall(Cell* c1, Cell* c2)
{
    int xc1 = c1->get_x();
    int yc1 = c1->get_y();

    int xc2 = c2->get_x();
    int yc2 = c2->get_y();

    // axe vertical
    if(xc1 == xc2)
    {
        // c2 est au dessus de c1
        if (yc1 > yc2)
        {   
            (*c1->get_walls())[0] = false;
            (*c2->get_walls())[2] = false;
        }
        else
        {
            (*c1->get_walls())[2] = false;
            (*c2->get_walls())[0] = false;
        }
    }
    else
    {
        // c2 est à gauche de la c1
        if (xc1 > xc2)
        {
            (*c1->get_walls())[3] = false;
            (*c2->get_walls())[1] = false;
        }
        else
        {
            (*c1->get_walls())[1] = false;
            (*c2->get_walls())[3] = false;
        }
    }
}

std::vector<Cell*> MazeGenerator::getNotVisited()
{
    std::vector<Cell*> tmp;
    for (int i = 0; i < h_; ++i)
    {
        for (int j = 0; j < w_; ++j)
        {
            Cell *c = maze_[i][j];
            if (!c->get_isInMaze())
            {
                tmp.push_back(c);
            }
        }
    }
    return tmp;
}

std::vector<Cell*> MazeGenerator::getNeigh(Cell* curr)
{
    std::vector<std::vector<int> > adjacents;
    adjacents.push_back({ 1, 0 });
    adjacents.push_back({ -1, 0 });
    adjacents.push_back({ 0, 1 });
    adjacents.push_back({ 0, -1 });

    std::vector<Cell*> tmp;
    
    int x = curr->get_x();
    int y = curr->get_y();


    for (int i = 0; i < 4; ++i)
    {
        int wtemp = x + adjacents[i][0];
        int htemp = y + adjacents[i][1];

        if (wtemp >= 0 && htemp >= 0 && htemp < h_ && wtemp < w_)
        {
            if (!maze_[htemp][wtemp]->get_isInMaze())
            {
                tmp.push_back(maze_[htemp][wtemp]);
            }
        }
    }
    return tmp;
}

std::vector<Cell*> MazeGenerator::getWalls(Cell* curr)
{
    std::vector<std::vector<int> > adjacents;
    adjacents.push_back({ 1, 0 });
    adjacents.push_back({ -1, 0 });
    adjacents.push_back({ 0, 1 });
    adjacents.push_back({ 0, -1 });

    std::vector<Cell*> tmp;
    int x = curr->get_x();
    int y = curr->get_y();


    for (int i = 0; i < 4; ++i)
    {
        int wtemp = x + adjacents[i][0];
        int htemp = y + adjacents[i][1];

        if (wtemp >= 0 && htemp >= 0 && htemp < h_ && wtemp < w_)
        {
            if (maze_[htemp][wtemp]->get_type() == WALL)
            {
                tmp.push_back(maze_[htemp][wtemp]);
            }
        }
    }
    return tmp;
}

Cell* MazeGenerator::getOpposite (Cell* c, Cell* w)
{
    int xc = c->get_x();
    int yc = c->get_y();

    int xw = w->get_x();
    int yw = w->get_y();

    Cell* res = nullptr;
    // axe vertical
    if(xc == xw)
    {
        // le wall est au dessus de la case
        if (yc > yw)
        {   
            if (yw - 1 >= 0)
            {
                res = maze_[yw - 1][xw];
            }
        }
        else
        {
            if (yw + 1 < h_)
            {
                res = maze_[yw + 1][xw];
            }
        }
    }
    else
    {
        // le wall est à gauche de la case
        if (xc > xw)
        {
            if (xw - 1 >= 0)
            {
                res  = maze_[yw][xw - 1];
            }
        }
        else
        {
            if (xw + 1 < w_)
            {
                res = maze_[yw][xw + 1];
            }
        }
    }
    return res;
}

void MazeGenerator::Print(bool p)
{
    if (perfect_ && p)
    {
        TMaze m = getFullMaze();
        int h = m.size();
        int w = m[0].size();

        std::cout << w << " " << h << std::endl;
        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                Cell *c = m[i][j];
                if (c->get_type() == WALL)
                    std::cout << "w";
                else if (c->get_type() == PATH)
                    std::cout << "p";
                else if (c->get_type() == FREE)
                    std::cout << "f";
                else if (c->get_type() == START)
                    std::cout << "s";
                else if (c->get_type() == END)
                    std::cout << "e";
                else if (c->get_type() == FLOW)
                    std::cout << "^";
            }
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << w_ << " " << h_ << std::endl;
        for (int i = 0; i < h_; ++i)
        {
            for (int j = 0; j < w_; ++j)
            {
                Cell *c = maze_[i][j];
                if (c->get_type() == WALL)
                    std::cout << "w";
                else if (c->get_type() == PATH)
                    std::cout << "p";
                else if (c->get_type() == FREE)
                    std::cout << "f";
                else if (c->get_type() == START)
                    std::cout << "s";
                else if (c->get_type() == END)
                    std::cout << "e";
                else if (c->get_type() == FLOW)
                    std::cout << "^";
            }
            std::cout << std::endl;
        }    
    }
}

void MazeGenerator::run()
{
    if (perfect_)
    {
        Generate2();
    }
    else
        Generate();
}

TMaze MazeGenerator::getFullMaze()
{
    TMaze fm = std::vector<std::vector<Cell*> >(2 * h_ + 1, 
        std::vector<Cell*>(2 * w_ + 1));

    for (unsigned int i = 0; i < fm.size(); ++i)
    {
        for (unsigned int j = 0; j < fm[0].size(); ++j)
        {
            Cell *c = new Cell(j, i);
            c->set_type(WALL);
            fm[i][j] = c;
        }
    }


    for (int i = 0; i < h_; ++i)
    {
        for (int j = 0; j < w_; ++j)
        {
            Cell* curr = maze_[i][j];

            fm[2 * i + 1][2 * j + 1]->set_type(curr->get_type());
            
            Cell* tmp = fm[2 * i][2 * j + 1];
            (*curr->get_walls())[0] ? tmp->set_type(WALL) : tmp->set_type(FREE);

            tmp = fm[2 * i + 1][2 * j + 2];
            (*curr->get_walls())[1] ? tmp->set_type(WALL) : tmp->set_type(FREE);

            tmp = fm[2 * i + 2][2 * j + 1];
            (*curr->get_walls())[2] ? tmp->set_type(WALL) : tmp->set_type(FREE);

            tmp = fm[2 * i + 1][2 * j];
            (*curr->get_walls())[3] ? tmp->set_type(WALL) : tmp->set_type(FREE);
        }
    }
    return fm;
}

int MazeGenerator::getRandom(int max)
{
    std::srand(std::time(0));
    return std::rand() % (int)(max);
}
