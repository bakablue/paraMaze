#ifndef MAP_HH
# define MAP_HH

# include <map>
# include <istream>

# include "cell.hh"

class Map
{
    public:
        Map();
        Map(int width, int height);
        ~Map();
        Map(const Map* p);

        void set_cell(int x, int y, char type);
        Cell* get_cell(int x, int y);

        void display();

        std::map<int, Cell* >* get_map() const;
        int get_width() const;
        int get_height() const;
        void set_start_cell(int istart, int jstart);

        void standard_solve_perfect_maze();
        void standard_solve_perfect_maze_rec(int w, int h);
        void standard_solve_any_maze();
        void algo_flow(Cell* current, Cell* cpointed);
        void algo_solve_path(Cell* current);

        Map* operator=(Map *map);
    private:
        std::map<int, Cell*> *map_;
        int width_;
        int height_;
        int istart_;
        int jstart_;
        static std::vector<std::vector<int> > adjacents;
        static int lol;
};


#endif /* !MAP_HH */
