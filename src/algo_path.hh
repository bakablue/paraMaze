#ifndef ALGO_PATH_HH
# define ALGO_PATH_HH

# include "map.hh"
# include <QThread>

class AlgoPath : public QThread
{
    Q_OBJECT
    public:
        AlgoPath();
        ~AlgoPath();

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

        Map* get_map() const;
        void set_map(Map* map);

        void set_option(int option);

    protected:
        void run();

signals:
        void update_gui();
        void update_map(int i, int j);

    private:
        Map *map_;
        static std::vector<std::vector<int> > adjacents;
        int option_;
};

#endif /* !ALGO_PATH */
