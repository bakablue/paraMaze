#include "parser.hh"
#include <boost/algorithm/string.hpp>
#include<boost/algorithm/string/split.hpp>
#include <vector>
#include <sstream>
#include <string>
#include <QApplication>
#include <QWidget>

Parser::Parser()
{
}

Parser::Parser(char* file)
    : filename_(file)
{
    file_.open(filename_, std::fstream::in);
    map_ = new Map();
}

Parser::Parser(const Parser& p)
{
    filename_ = p.get_filename();
    map_ = p.get_map();
}

Parser::~Parser()
{
}

char* Parser::get_filename() const
{
    return filename_;
}

Map* Parser::get_map() const
{
    return map_;
}

int Parser::parse(int argc, char* argv[])
{
    std::string line;
    std::vector<std::string> elts;
    int i, j, width, height = 0;

    if (file_.is_open())
    {
        if (getline(file_, line))
        {
            boost::split(elts, line, boost::is_any_of("\t "));
            std::istringstream buffer(elts[0]);
            buffer >> width;
            std::istringstream buffer2(elts[1]);
            buffer2 >> height;
            map_ = new Map(width, height);
        }

        j = 0;
        while (getline(file_, line))
        {
            for (i = 0; i < width; i++)
                map_->set_cell(i, j, line[i]);
            j++;
        }
        init_gui(argc, argv);
        map_->display();
        file_.close();

        return 0;
    }
    else
        std::cout << "Cannot open file: " << filename_ << std::endl;

    return 1;
}

void Parser::init_gui(int argc, char* argv[])
{
    QApplication app(argc, argv);

    window_.set_map(map_);
    window_.resize(250, 150);
    window_.setWindowTitle("yolo");
    window_.show();

    app.exec();
}
