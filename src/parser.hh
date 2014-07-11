#ifndef PARSER_HH
# define PARSER_HH

# include <fstream>
# include <iostream>
# include <map>

# include "map.hh"
# include "colors.hh"

class Parser
{
    public:
        Parser();
        Parser(char* file);
        Parser(const Parser& p);
        ~Parser();

        char* get_filename() const;
        Map* get_map() const;
        void init_gui(int argc, char* argv[]);

        int parse(int argc, char* argv[]);
    private:
        char* filename_;
        std::fstream file_;
        Map *map_;
        Colors window_;
};

#endif /* !PARSER_HH */
