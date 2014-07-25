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

        /**
         *  \fn standard_solve_perfect maze
         *  \brief Resolve a perfect maze (not parallelized)
         */
        void standard_solve_perfect_maze();
        /**
         * \fn standard_solve_perfect_maze_rec
         * \brief Recursive function called by standard_solve_perfect_maze to
         *          solve a perfect maze
         * \param w width of the current cell
         * \param h height of the current cell
         */
        void standard_solve_perfect_maze_rec(int w, int h);
        /**
         *  \fn standard_solve_any_maze
         *  \brief Resolve any maze (not parallelized)
         */
        void standard_solve_any_maze();
        /**
         * \fn algo_flow
         * \brief Recursive function called by standard_solve_any_maze to
         *          solve a perfect maze
         * \param current Current cell used by the algorithm
         * \param cpointed Cell that will be pointed by the current cell
         */
        void algo_flow(Cell* current, Cell* cpointed);
        /**
         * \fn algo_solve_path
         * \brief Recursive function to print the path.
         * \param current Current cell used by the algorithm
         */
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
