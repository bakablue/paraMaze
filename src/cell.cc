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

