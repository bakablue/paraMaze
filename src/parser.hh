#ifndef PARSER_HH
# define PARSER_HH

# include <fstream>
# include <iostream>
# include <map>
# include <boost/algorithm/string.hpp>
# include <boost/algorithm/string/split.hpp>
# include <vector>
# include <sstream>
# include <string>
# include <QApplication>
# include <QWidget>

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

        int parse();
    private:
        char* filename_;
        std::fstream file_;
        Map *map_;
};

#endif /* !PARSER_HH */
