#include "map.hh"

Map::Map()
    : width_(0)
    , height_(0)
    , istart_(0)
    , jstart_(0)
{
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

Map::Map(const Map* m)
{
    map_->insert(m->get_map()->begin(), m->get_map()->end());
    width_ = m->get_width();
    height_ = m->get_height();
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

Cell* Map::get_start_cell() const
{
    return map_->find(jstart_ * width_ + istart_)->second;
}

bool Map::has_cell(int x, int y)
{
    return (map_->find(y * width_ + x) != map_->end());
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

