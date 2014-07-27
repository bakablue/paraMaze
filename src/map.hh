#ifndef MAP_HH
# define MAP_HH

# include <map>
# include <istream>
# include <tbb/tbb.h>
# include <vector>
# include <tbb/concurrent_vector.h>

# include "cell.hh"

class Map
{
    public:
        Map();
        Map(int width, int height);
        ~Map();
        Map(const Map* p);

        void set_cell(Cell *c);
        void set_cell(int x, int y, char type);
        Cell* get_cell(int x, int y);
        bool has_cell(int x, int y);

        void display();

        tbb::concurrent_vector<Cell* >* get_map() const;
        void set_map(tbb::concurrent_vector<Cell*> *map);
        void update_map(Map *map);

        int get_width() const;
        int get_height() const;
        void set_start_cell(int istart, int jstart);
        Cell* get_start_cell() const;
        bool has_end_cell() const;
        void set_end_cell(bool end);

        Map* operator=(Map *map);

    private:
        tbb::concurrent_vector<Cell*> *map_;
        int width_;
        int height_;
        int istart_;
        int jstart_;
        bool end_cell_;
};


#endif /* !MAP_HH */
