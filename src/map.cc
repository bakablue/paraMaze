#include "map.hh"

Map::Map()
    : width_(0)
    , height_(0)
    , istart_(0)
    , jstart_(0)
    , end_cell_(false)
{
    map_ = new tbb::concurrent_vector<Cell*>();
}

Map::Map(int width, int height)
  : width_(width)
  , height_(height)
  , istart_(0)
  , jstart_(0)
  , end_cell_(false)
{
  map_ = new tbb::concurrent_vector<Cell*>();
}

Map::~Map()
{
}

Map::Map(const Map* m)
{
    std::copy(m->get_map()->begin(), m->get_map()->end(), map_->begin());
    width_ = m->get_width();
    height_ = m->get_height();
}

tbb::concurrent_vector<Cell*>* Map::get_map() const
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

void Map::set_cell(Cell *c)
{
  (*map_)[c->get_y() * width_ + c->get_x()] = c;
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
  {
    c->set_type(END);
    end_cell_ = true;
  }
  else if (type == 'p')
    c->set_type(PATH);

  map_->push_back(c);
}

Cell* Map::get_cell(int x, int y)
{
    Cell* c = (*map_)[y * width_ + x];
    return c;
}

Cell* Map::get_start_cell() const
{
    return map_->at(jstart_ * width_ + istart_);
}

bool Map::has_cell(int x, int y)
{
    size_t s = y * width_ + x;
    return (s < map_->size());
}

void Map::display()
{
    int i, j = 0;

    for (j = 0; j < height_; j++)
    {
        for (i = 0; i < width_; i++)
            std::cout << *(map_->at(j * width_ + i));
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

bool Map::has_end_cell() const
{
    return end_cell_;
}

void Map::set_end_cell(bool end)
{
    end_cell_ = end;
}

void Map::set_map(tbb::concurrent_vector<Cell*> *map)
{
    std::copy(map->begin(), map->end(), map_->begin());
}

void Map::update_map(Map *map)
{
    Cell *pointed;
    for (int i = 0; i < width_; ++i)
    {
        for (int j = 0; j < height_; ++j)
        {
            get_cell(i, j)->set_type(map->get_cell(i, j)->get_type());
            pointed = map->get_cell(i, j)->get_pointed();
            if (pointed)
                get_cell(i, j)->set_pointed(get_cell(pointed->get_x(), pointed->get_y()));
        }
    }
}

