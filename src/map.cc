#include "map.hh"

std::vector<std::vector<int> > Map::adjacents;

Map::Map()
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
    //Cell* temp;

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
    Cell *c;
    Cell *ctemp;

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

                    if (map_->find(width_ * htemp + wtemp) != map_->end())
                    {
                        ctemp = map_->find(width_ * htemp + wtemp)->second;

                        if (ctemp->get_type() == FREE
                            || ctemp->get_type() == START
                            || ctemp->get_type() == END)
                            count++;
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

void Map::standard_solve_any_maze()
{
    int h, w = 0;

    for (h = 0; h < height_; h++)
    {
        for (w = 0; w < width_; w++)
        {
            //if (map_->find(w * h + w) != WALL && map_->find(w * h + w) != PATH)
            //{
            //}
        }
    }
}

Map* Map::operator=(Map *map)
{
    // Good copy ?
    return map;
}
