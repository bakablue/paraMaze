#include "mazegenerator.hh"

MazeGenerator::MazeGenerator(int h, int w)
	: h_(h), w_(w)
{
	maze_ = std::vector<std::vector<char> >(h) ;
	for (int i = 0; i < h; ++i)
	{
		maze_[i] = std::vector<char>(w, 'w');
	}
	maze_[0][w - 1] = "e";
	maze_[h - 1][w - 1] = "s";
}



    // Start with a grid full of walls.
    // Pick a cell, mark it as part of the maze. Add the walls of the cell to the wall list.
    // While there are walls in the list:
    //     Pick a random wall from the list. If the cell on the opposite side isn't in the maze yet:
    //         Make the wall a passage and mark the cell on the opposite side as part of the maze.
    //         Add the neighboring walls of the cell to the wall list.
    //     If the cell on the opposite side already was in the maze, remove the wall from the list.


void MazeGenerator::Generate()
{
	std::stack<Cell*> cellstack;
	std::vector<Cell*> totalCells = getTotalCells();
	std::vector<Cell*> visitedCells;
	
	Cell* currentCell = totalCells[totalCells.size() - 1];

	visitedCells.push_back(currentCell); 

	while(visitedCells.size() < totalCells.size())
	{
		std::cout << "v " << visitedCells.size() << " t " << totalCells.size() << std::endl;
		std::string input ="";
		getline(std::cin, input);

		std::vector<Cell*> neighbors = getNeighbourds(currentCell, totalCells);
		for(Cell* c: neighbors)
		{
			std::cout << *c << std::endl;
		}
		if (neighbors.size() > 0)
		{
			boost::random::uniform_int_distribution<> r(0, neighbors.size() - 1);
			boost::random::mt19937 rng;
			Cell* crandom = neighbors[r(rng)];
			std::cout << *crandom << std::endl;
			makeWall(currentCell, crandom);
			Print();

			cellstack.push(currentCell);
			currentCell = crandom;
			visitedCells.push_back(crandom);
		}
		else
		{
			if (!cellstack.empty())
			{
				currentCell = cellstack.top();
				cellstack.pop();
			}
		}
		// std::string input ="";
		// getline(std::cin, input);
	}
	totalCells.clear();
}

void MazeGenerator::Print()
{
	std::cout << " ";
	for (int i = 0; i < w_; ++i)
	{
		std::cout << i;
	}
	std::cout << std::endl;
	for (int i = 0; i < h_; ++i)
	{
		std::cout << i;
		for (int j = 0; j < w_; ++j)
		{
			std::cout << maze_[i][j];
		}
		std::cout << std::endl;
	}
}

std::vector<Cell*> MazeGenerator::getTotalCells()
{
	std::vector<Cell*> tmp;
	for (int i = 0; i < h_; ++i)
	{
		for (int j = 0; j < w_; ++j)
			{
				Cell* c = new Cell(i, j);
				c->set_type(FREE);
				tmp.push_back(c);
			}	
	}
	return tmp;
}

std::vector<Cell*> MazeGenerator::getNeighbourds(Cell* current, 
												 std::vector<Cell*> totalCells)
{
	std::vector<std::vector<int> > adjacents;
	adjacents.push_back({ 1, 0 });
	adjacents.push_back({ -1, 0 });
	adjacents.push_back({ 0, 1 });
	adjacents.push_back({ 0, -1 });

	std::vector<std::vector<int> > adjacents2;
	adjacents2.push_back({ 2, 0 });
	adjacents2.push_back({ -2, 0 });
	adjacents2.push_back({ 0, 2 });
	adjacents2.push_back({ 0, -2 });
	std::vector<Cell*> tmp;


	int x = current->get_x();
	int y = current->get_y();

	for (int i = 0; i < 4; ++i)
    {
        int wtemp = x + adjacents[i][0];
        int htemp = y + adjacents[i][1];
		int wtemp2 = x + adjacents2[i][0];
        int htemp2 = y + adjacents2[i][1];

        if (wtemp >= 0 && htemp >= 0 && htemp < h_ && wtemp < w_)
        {
        	if (maze_[htemp][wtemp] != 'w')
        	{
        		if (wtemp2 >= 0 && htemp2 >= 0 && htemp2 < h_ && wtemp2 < w_)
        		{
					for(Cell* c: totalCells)
					{
						if(c->get_x() == wtemp2 && c->get_y() == htemp2)
						{	
							tmp.push_back(c);
						}
					}
        		}
        	}
        }
	}

	return tmp;
}


void MazeGenerator::makeWall(Cell* c1, 
			   				 Cell* c2)
{
	if (c1->get_x() == c2->get_x())
	{
		if (c2->get_y() > c1->get_y())
		{
			std::cout << "lol" << std::endl;
			maze_[c1->get_y() + 1][c2->get_x()] = 'w';
		}
		else
		{
			std::cout << "lol2" << std::endl;
			maze_[c2->get_y() + 1][c2->get_x()] = 'w';
		}
	}
	else
	{
		if (c2->get_x() > c1->get_x())
		{
			std::cout << "lol3" << std::endl;

			maze_[c1->get_y()][c1->get_x() + 1] = 'w';
		}
		else
		{
			std::cout << "lol4" << std::endl;

			maze_[c1->get_y()][c2->get_x() + 1] = 'w';
		}
	}
}



int main(int argc, char const *argv[])
{
	MazeGenerator maze = MazeGenerator(10, 10);
	// maze.Print();

	maze.Generate();
	maze.Print();
	return 0;
}