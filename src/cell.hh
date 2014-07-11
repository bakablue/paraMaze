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
    PATH
} e_type_cell;

class Cell
{
    public:
        Cell();
        Cell(int x, int y);

        void set_type(e_type_cell type);
        e_type_cell get_type() const;

        friend std::ostream& operator<<(std::ostream& os, const Cell& obj)
        {
            if (obj.get_type() == WALL)
                os << "W";
            else
                os << "P";
            return os;
        }
    private:
        int x_;
        int y_;
        e_type_cell type_;
};


#endif /* !CELL_HH */
