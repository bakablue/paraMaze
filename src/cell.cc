#include "cell.hh"

Cell::Cell()
    : x_(0), y_(0)
{
}

Cell::Cell(int x, int y)
    : x_(x), y_(y)
{
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


std::ostream& operator<<(std::ostream& os, const Cell& obj)
{
    if (obj.get_type() == WALL)
        os << "Cell("<< obj.get_x() << ", " << obj.get_y() << ", W)";
    else
        os << "Cell("<< obj.get_x() << ", " << obj.get_y() << ", P)";
    return os;
}