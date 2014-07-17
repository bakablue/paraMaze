#ifndef CELL_HH
# define CELL_HH

# include <iostream>
# include <vector>

typedef enum type_cell
{
    FREE,
    WALL,
    START,
    END,
    PATH,
    FLOW
} e_type_cell;

class Cell
{
    public:
        Cell();
        Cell(int x, int y);
        Cell(const Cell* c);

        void set_type(e_type_cell type);
        e_type_cell get_type() const;

        friend std::ostream& operator<<(std::ostream& os, const Cell& obj)
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

        int get_x() const;
        int get_y() const;

        Cell* get_pointed() const;
        void set_pointed(Cell* p);
    private:
        int x_;
        int y_;
        e_type_cell type_;
        Cell* pointed_;
};


#endif /* !CELL_HH */
