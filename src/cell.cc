#include "cell.hh"

Cell::Cell()
  : x_(0)
  , y_(0)
  , type_(FREE)
  , pointed_(NULL)
{
}

Cell::Cell(int x, int y)
  : x_(x)
  , y_(y)
  , isInMaze_(false)
  , type_(FREE)
  , pointed_(NULL)
{

}

Cell::Cell(int x, int y, e_type_cell t)
  : x_(x)
  , y_(y)
  , isInMaze_(false)
  , type_(t)
  , pointed_(NULL)
{

}

Cell::Cell(const Cell* c)
{
  type_ = c->get_type();
  x_ = c->get_x();
  y_ = c->get_y();
  pointed_ = c->get_pointed();
  isInMaze_ = c->isInMaze_;
}

void Cell::set_type(e_type_cell type)
{
  type_ = type;
}

e_type_cell Cell::get_type() const
{
  return type_;
}

int Cell::get_x() const
{
  return x_;
}

int Cell::get_y() const
{
  return y_;
}

std::ostream& Cell::debug(std::ostream& os)
{
  if (this == nullptr)
    os << "NULL";
  else if (get_type() == WALL)
  {
    os << "Cell("<< get_x() << ", " << get_y() << ", W) ";
    for (bool b : *walls_)
    {
      os << b << ", ";
    }
  }
  else if (get_type() == PATH)
    os << "Cell("<< get_x() << ", " << get_y() << ", P)";
  else if (get_type() == FREE)
    {
      os << "Cell("<< get_x() << ", " << get_y() << ", F)";
      for (bool b : *walls_)
      {
        os << b << ", ";
      }
    }
  else if (get_type() == START)
    {
      os << "Cell("<< get_x() << ", " << get_y() << ", S)";
      for (bool b : *walls_)
      {
        os << b << ", ";
      }
    }
  else if (get_type() == END)
    os << "Cell("<< get_x() << ", " << get_y() << ", E)";
  else if (get_type() == FLOW)
    os << "Cell("<< get_x() << ", " << get_y() << ", ^)";
  os << std::endl;
  return os;
}

std::ostream& operator<<(std::ostream& os, const Cell& obj)
{
  if (obj.get_type() == WALL)
    os << RED << "W" << RESETCOLOR;
  else if (obj.get_type() == PATH)
    os << BLUE << "P" << RESETCOLOR;
  else if (obj.get_type() == FREE)
    os << GREEN << "F" << RESETCOLOR;
  else if (obj.get_type() == START)
    os << YELLOW << "S" << RESETCOLOR;
  else if (obj.get_type() == END)
    os << PURPLE << "E" << RESETCOLOR;
  else if (obj.get_type() == FLOW)
    os << BROWN << "R" << RESETCOLOR;

  return os;
}


Cell* Cell::get_pointed() const
{
  return pointed_;
}

void Cell::set_pointed(Cell* p)
{
  pointed_ = p;
}

void Cell::set_isInMaze(bool b)
{
  isInMaze_ = b;
}

std::vector<bool>* Cell::get_walls()
{
  return walls_;
}

void Cell::set_walls(std::vector<bool> *w)
{
  walls_ = w;
}

bool Cell::get_isInMaze()
{
  return isInMaze_;
}
