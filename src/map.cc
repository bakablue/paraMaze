#include "map.hh"

std::vector<std::vector<int> > Map::adjacents;

Map::Map()
{
    adjacents.push_back({ 1, 1 });
    adjacents.push_back({ 1, -1 });
    adjacents.push_back({ -1, 1 });
    adjacents.push_back({ -1, -1 });
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
    Cell *c = new Cell();
    if (type == 'w')
        c->set_type(WALL);
    else if (type == 'p')
        c->set_type(FREE);

    map_->insert(std::pair<int, Cell*> (y * x + x, c));
}

Cell* Map::get_cell(int x, int y)
{
    return map_->find(y * x + x)->second;
}

void Map::display()
{
    int i, j = 0;

    for (i = 0; i < width_; i++)
    {
        for (j = 0; j < height_; j++)
            std::cout << *(map_->find(i * j + i)->second);
        std::cout << std::endl;
    }
}

void Map::standard_solve_perfect_maze()
{
    int i = 0;
    int h, w = 0;
    int htemp, wtemp = 0;
    int count = 0;

    for (h = 0; h < height_; h++)
    {
        for (w = 0; w < width_; w++)
        {
            if (map_->find(w * h + w)->second->get_type() != WALL)
            {
                count = 0;
                for (i = 0; i < 4; i++)
                {
                    wtemp = w + adjacents[i][0];
                    htemp = h + adjacents[i][1];

                    if (map_->find(wtemp * htemp + wtemp) == map_->end())
                        // WARNING
                        if (map_->find(wtemp * htemp + wtemp)->second->get_type() == FREE)
            //                count++;
                    if (count <= 1)
                        // WARNING
                        map_->find(wtemp * htemp + wtemp)->second->set_type(WALL);

                }
            }
        }
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
