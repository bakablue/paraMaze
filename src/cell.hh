#ifndef CELL_HH
# define CELL_HH

# define WHITE  "\033[22;30m"
# define GREEN  "\033[22;31m"
# define RED  "\033[22;32m"
# define BLUE  "\033[22;33m"
# define PURPLE  "\033[22;34m"
# define YELLOW  "\033[22;35m"
# define BROWN  "\033[22;35m"
# define RESETCOLOR "\033[0m"

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
  std::vector<bool>* get_walls();
  bool get_isInMaze();
  Cell* get_pointed() const;
  void set_pointed(Cell* p);
  void set_isInMaze(bool b);
  void set_walls(std::vector<bool>* w);
  

  std::ostream& debug(std::ostream& os);

  friend std::ostream& operator<<(std::ostream& os, const Cell& obj);


private:
  int x_;
  int y_;
  bool isInMaze_;
  e_type_cell type_;
  Cell* pointed_;
  // (0,N) (1,E) (2,S) (3,W)
  std::vector<bool>* walls_;
};


#endif /* !CELL_HH */
