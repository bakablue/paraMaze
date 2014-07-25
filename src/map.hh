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
        bool has_cell(int x, int y);

        void display();

        std::map<int, Cell* >* get_map() const;
        int get_width() const;
        int get_height() const;
        void set_start_cell(int istart, int jstart);
        std::map<int, Cell* >* get_map() const;
        int get_width() const;
        int get_height() const;
        void set_start_cell(int istart, int jstart);
        Cell* get_start_cell() const;

        Map* operator=(Map *map);

    private:
        std::map<int, Cell*> *map_;
        int width_;
        int height_;
        int istart_;
        int jstart_;
};


#endif /* !MAP_HH */
