#include "parser.hh"


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

int Parser::parse()
{
    std::string line;
    std::vector<std::string> elts;
    int i, j, width, height, istart, jstart = 0;

    if (file_.is_open())
    {
        // get width, height
        if (getline(file_, line))
        {
            boost::split(elts, line, boost::is_any_of("\t "));
            std::istringstream buffer(elts[0]);
            buffer >> width;
            std::istringstream buffer2(elts[1]);
            buffer2 >> height;
            map_ = new Map(width, height);
        }

        // get start cell
        if (getline(file_, line))
        {
            boost::split(elts, line, boost::is_any_of("\t "));
            std::istringstream buffer(elts[0]);
            buffer >> istart;
            std::istringstream buffer2(elts[1]);
            buffer2 >> jstart;
            map_->set_start_cell(istart, jstart);
        }
        j = 0;
        while (getline(file_, line))
        {
            for (i = 0; i < width; i++)
                map_->set_cell(i, j, line[i]);
            j++;
        }
        file_.close();
        return 0;
    }
    else
        std::cout << "Cannot open file: " << filename_ << std::endl;

    return 1;
}

