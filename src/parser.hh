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

<<<<<<< HEAD
  char* get_filename() const;
  Map* get_map() const;
  void init_gui(int argc, char* argv[]);

  int parse(int argc, char* argv[]);
private:
  char* filename_;
  std::fstream file_;
  Map *map_;
  //Colors window_;
=======
        char* get_filename() const;
        Map* get_map() const;

        int parse();
    private:
        char* filename_;
        std::fstream file_;
        Map *map_;
>>>>>>> Separation of the algo from the class map
};

#endif /* !PARSER_HH */
