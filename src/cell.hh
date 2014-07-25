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
  int get_x() const;
  int get_y() const;
  Cell* get_pointed() const;
  void set_pointed(Cell* p);
  void set_isInMaze(bool b);
  bool get_isInMaze();

  std::ostream& debug(std::ostream& os);

  friend std::ostream& operator<<(std::ostream& os, const Cell& obj);

        
private:
  int x_;
  int y_;
  bool isInMaze_;
  e_type_cell type_;
  Cell* pointed_;
};


#endif /* !CELL_HH */
