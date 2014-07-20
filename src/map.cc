#include "map.hh"

std::vector<std::vector<int> > Map::adjacents;

Map::Map()
  : width_(0)
  , height_(0)
  , istart_(0)
  , jstart_(0)
{
  adjacents.push_back({ 1, 0 });
  adjacents.push_back({ -1, 0 });
  adjacents.push_back({ 0, 1 });
  adjacents.push_back({ 0, -1 });
  map_ = new std::map<int, Cell*>();
}

Map::Map(int width, int height)
  : width_(width)
  , height_(height)
  , istart_(0)
  , jstart_(0)
{
  map_ = new std::map<int, Cell*>();
}

Map::~Map()
{
}

Map::Map(const Map* p)
{
  map_->insert(p->get_map()->begin(), p->get_map()->end());
  width_ = p->get_width();
  height_ = p->get_height();
}

std::map<int, Cell*>* Map::get_map() const
{
  return map_;
}

int Map::get_width() const
{
  return width_;
}

int Map::get_height() const
{
  return height_;
}

void Map::set_cell(int x, int y, char type)
{
  Cell *c = new Cell(x, y);
  if (type == 'w')
    c->set_type(WALL);
  else if (type == 'f')
    c->set_type(FREE);
  else if (type == 's')
    c->set_type(START);
  else if (type == 'e')
    c->set_type(END);
  else if (type == 'p')
    c->set_type(PATH);

  map_->insert(std::pair<int, Cell*> (y * width_ + x, c));
}

Cell* Map::get_cell(int x, int y)
{
  return map_->find(y * width_ + x)->second;
}

void Map::display()
{
  int i, j = 0;

  for (j = 0; j < height_; j++)
    {
      for (i = 0; i < width_; i++)
	std::cout << *(map_->find(j * width_ + i)->second);
      std::cout << std::endl;
    }
}

void Map::standard_solve_perfect_maze_rec(int w, int h)
{
  int htemp, wtemp = 0;
  int i = 0;
  std::vector<Cell*> next_cell;

  // Checks for free cells and add them to the list next_cell
  for (i = 0; i < 4; ++i)
    {
      wtemp = w + adjacents[i][0];
      htemp = h + adjacents[i][1];

      if (wtemp >= 0 && htemp >= 0 && htemp < height_ && wtemp < width_)
	// if it exists
	if (map_->find(width_ * htemp + wtemp) != map_->end())
	  {
	    if (map_->find(width_ * htemp + wtemp)->second->get_type() == FREE)
	      next_cell.push_back(map_->find(width_ * htemp + wtemp)->second);
	  }

    }

  // The cell has 3 walls so we can eliminate it and check the only free cell
  // beside it
  if (next_cell.size() == 1)
    {
      map_->find(width_ * h + w)->second->set_type(WALL);
      standard_solve_perfect_maze_rec(next_cell[0]->get_x(),
				      next_cell[0]->get_y());
    }

}

void Map::standard_solve_perfect_maze()
{
  int i = 0;
  int h, w = 0;
  int htemp, wtemp = 0;
  int count = 0;
  std::vector<Cell*> init_cells;
  Cell *c, *ctemp;

  for (h = 0; h < height_; ++h)
    {
      for (w = 0; w < width_; ++w)
        {
	  c = map_->find(width_ * h + w)->second;
	  if ((c->get_type() != WALL && c->get_type() != END
	       && c->get_type() != START))
            {
	      count = 0;
	      for (i = 0; i < 4; ++i)
                {
		  wtemp = w + adjacents[i][0];
		  htemp = h + adjacents[i][1];

		  if (wtemp >= 0 && wtemp < width_ && htemp >= 0 && htemp < height_)
                    {
		      if (map_->find(width_ * htemp + wtemp) != map_->end())
                        {
			  ctemp = map_->find(width_ * htemp + wtemp)->second;

			  if (ctemp->get_type() == FREE
			      || ctemp->get_type() == START
			      || ctemp->get_type() == END)
			    count++;
                        }

                    }
                }
	      if (count == 1)
		init_cells.push_back(c);
            }
        }
    }

  std::cout << "=== Print cells ===" << std::endl;
  for (auto cell : init_cells)
    {
      std::cout << cell->get_x() << " " << cell->get_y() << std::endl;
      standard_solve_perfect_maze_rec(cell->get_x(), cell->get_y());
    }
}

void Map::algo_solve_path(Cell* current)
{
  if (current->get_type() != START)
    algo_solve_path(current->get_pointed());
  current->set_type(PATH);
}

void Map::algo_flow(Cell* current, Cell* cpointed)
{
  int i = 0;
  int wtemp, htemp = 0;
  std::vector<Cell*> next_cells;
  Cell* ctemp;

  if (current->get_type() == FREE)
    {
      current->set_pointed(cpointed);
      current->set_type(FLOW);

      for (i = 0; i < 4; ++i)
        {
	  wtemp = current->get_x() + adjacents[i][0];
	  htemp = current->get_y() + adjacents[i][1];

	  if (wtemp >= 0 && wtemp < width_ && htemp >= 0 && htemp < height_)
            {
	      if (map_->find(width_ * htemp + wtemp) != map_->end())
                {
		  ctemp = map_->find(width_ * htemp + wtemp)->second;
		  if (ctemp->get_type() == FREE || ctemp->get_type() == END)
		    next_cells.push_back(ctemp);

                }
            }
        }

      // Launch the algorithm on every free cell beside the current one
      for (auto c : next_cells)
	algo_flow(c, current);
    }
  if (current->get_type() == END && cpointed->get_type() == FLOW)
    {
      current->set_type(PATH);
      // Begin printing the path of the maze
      algo_solve_path(cpointed);
    }
}

void Map::standard_solve_any_maze()
{
  int i = 0;
  int wtemp, htemp = 0;
  std::vector<Cell*> init_cells;

  // We start from the start case
  Cell* cstart = map_->find(jstart_ * width_ + istart_)->second;
  Cell* ctemp;

  for (i = 0; i < 4; ++i)
    {
      wtemp = istart_ + adjacents[i][0];
      htemp = jstart_ + adjacents[i][1];

      if (wtemp >= 0 && wtemp < width_ && htemp >= 0 && htemp < height_)
        {
	  if (map_->find(width_ * htemp + wtemp) != map_->end())
            {
	      ctemp = map_->find(width_ * htemp + wtemp)->second;
	      if (ctemp->get_type() == FREE)
		init_cells.push_back(ctemp);

            }
        }
    }

  for (auto c : init_cells)
    algo_flow(c, cstart);
}

Map* Map::operator=(Map *map)
{
  // Good copy ?
  return map;
}

void Map::set_start_cell(int istart, int jstart)
{
  istart_ = istart;
  jstart_ = jstart;
}
