#include "cell.hh"

Cell::Cell()
    : x_(0)
    , y_(0)
{
}

Cell::Cell(int x, int y)
    : x_(x)
    , y_(y)
    , isInMaze_(false)
{

}

Cell::Cell(const Cell* c)
{
    type_ = c->get_type();
    x_ = c->get_x();
    y_ = c->get_y();
    pointed_ = c->get_pointed();
}

//Cell* Cell::operator=(const Cell* c)
//{
//    type_ = c->get_type();
//    x_ = c->get_x();
//    y_ = c->get_y();
//    return this;
//}

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


// std::ostream& operator<<(std::ostream& os, const Cell& obj)
// {
//     if (obj.get_type() == WALL)
//         os << "Cell("<< obj.get_x() << ", " << obj.get_y() << ", W)";
//    	else if (obj.get_type() == PATH)
//         os << "Cell("<< obj.get_x() << ", " << obj.get_y() << ", P)";
//     else if (obj.get_type() == FREE)
//         os << "Cell("<< obj.get_x() << ", " << obj.get_y() << ", F)";
//     else if (obj.get_type() == START)
//         os << "Cell("<< obj.get_x() << ", " << obj.get_y() << ", S)";
//     else if (obj.get_type() == END)
//         os << "Cell("<< obj.get_x() << ", " << obj.get_y() << ", E)";
//     else if (obj.get_type() == FLOW)
//         os << "Cell("<< obj.get_x() << ", " << obj.get_y() << ", ^)";

//     return os;
// }

std::ostream& operator<<(std::ostream& os, const Cell& obj)
{
    if (obj.get_type() == WALL)
        os << "W";
   	else if (obj.get_type() == PATH)
        os << "P";
    else if (obj.get_type() == FREE)
        os << "F";
    else if (obj.get_type() == START)
        os << "S";
    else if (obj.get_type() == END)
        os << "E";
    else if (obj.get_type() == FLOW)
        os << "^";

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
        
bool Cell::get_isInMaze()
{
	return isInMaze_;
}
