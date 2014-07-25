#include "mazegenerator.hh"

// MazeGenerator::MazeGenerator(MazeGenerator &mg)
// {

// }


MazeGenerator::MazeGenerator(int h, int w)
    : QThread()
    , h_(h)
    , w_(w)
{
    maze_ = std::vector<std::vector<Cell*> >(h);
    for (int i = 0; i < h; ++i)
    {
        maze_[i] = std::vector<Cell*>(w);
    }
    
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


MazeGenerator::~MazeGenerator()
{
    for (int i = 0; i < h_; ++i)
    {
        for (int j = 0; j < w_; ++j)
        {
            free(maze_[i][j]);
        }
    }
}

void MazeGenerator::Generate()
{
<<<<<<< HEAD
	std::vector<Cell*> walls;

	Cell* current = maze_[h_ - 1][0];
	current->set_isInMaze(true);

	walls = getWalls(current);
	Cell* opp;

	while (walls.size() > 0)
	{
		int min = 1;
		int max = walls.size();

 		std::srand(std::time(0));

		int pos = min + (std::rand() % (int)(max - min + 1)) - 1;
		
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
		std::cout << std::endl;
		Print();
		emit sendMaze(maze_);
		usleep(50000);
	}
	maze_[0][w_ - 1]->set_type(END);
=======
    std::vector<Cell*> walls;

    Cell* current = maze_[h_ - 1][0];
    current->set_isInMaze(true);

    walls = getWalls(current);
    Cell* opp;

    while (walls.size() > 0)
    {
        int min = 1;
        int max = walls.size();

        std::srand(std::time(0));

        int pos = min + (std::rand() % (int)(max - min + 1)) - 1;
        
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
>>>>>>> testgui
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

void MazeGenerator::Print()
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

void MazeGenerator::run()
{
    Generate();
}
