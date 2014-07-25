#include "algo_path.hh"

std::vector<std::vector<int> > AlgoPath::adjacents;

AlgoPath::AlgoPath()
    : QThread()
    , option_(0)
{
    adjacents.push_back({ 1, 0 });
    adjacents.push_back({ -1, 0 });
    adjacents.push_back({ 0, 1 });
    adjacents.push_back({ 0, -1 });
}

AlgoPath::~AlgoPath()
{
}

Map* AlgoPath::get_map() const
{
    return map_;
}

void AlgoPath::set_map(Map* map)
{
    map_ = map;
}

void AlgoPath::set_option(int option)
{
    option_ = option;
}

void AlgoPath::standard_solve_any_maze()
{
    int i = 0;
    int wtemp, htemp = 0;
    std::vector<Cell*> init_cells;

    // We start from the start case
    Cell* cstart = map_->get_start_cell();
    Cell* ctemp;

    for (i = 0; i < 4; ++i)
    {
        wtemp = cstart->get_x() + adjacents[i][0];
        htemp = cstart->get_y() + adjacents[i][1];

        if (wtemp >= 0 && wtemp < map_->get_width() && htemp >= 0 && htemp < map_->get_height())
        {
            if (map_->has_cell(wtemp, htemp))
            {
                ctemp = map_->get_cell(wtemp, htemp);
                if (ctemp->get_type() == FREE)
                    init_cells.push_back(ctemp);

            }
        }
    }

    for (auto c : init_cells)
        algo_flow(c, cstart);
}

void AlgoPath::standard_solve_perfect_maze()
{
    int i = 0;
    int h, w = 0;
    int htemp, wtemp = 0;
    int count = 0;
    std::vector<Cell*> init_cells;
    Cell *c, *ctemp;

    for (h = 0; h < map_->get_height(); ++h)
    {
        for (w = 0; w < map_->get_width(); ++w)
        {
            c = map_->get_cell(h, w);
            if ((c->get_type() != WALL && c->get_type() != END
                 && c->get_type() != START))
            {
                count = 0;
                for (i = 0; i < 4; ++i)
                {
                    wtemp = w + adjacents[i][0];
                    htemp = h + adjacents[i][1];

                    if (wtemp >= 0 && wtemp < map_->get_width() && htemp >= 0 && htemp < map_->get_height())
                    {
                        if (map_->has_cell(wtemp, htemp))
                        {
                            ctemp = map_->get_cell(wtemp, htemp);

                            if (ctemp->get_type() == FREE
                                || ctemp->get_type() == START
                                || ctemp->get_type() == END)
                                count++;
                        }

                    }
                }
                if (count == 1)
                    init_cells.push_back(c);
            }
        }
    }

    std::cout << "=== Print cells ===" << std::endl;
    for (auto cell : init_cells)
    {
        std::cout << cell->get_x() << " " << cell->get_y() << std::endl;
        standard_solve_perfect_maze_rec(cell->get_x(), cell->get_y());
    }
}

void AlgoPath::algo_solve_path(Cell* current)
{
    if (current->get_type() != START)
        algo_solve_path(current->get_pointed());
    current->set_type(PATH);
}

void AlgoPath::algo_flow(Cell* current, Cell* cpointed)
{
    int i = 0;
    int wtemp, htemp = 0;
    std::vector<Cell*> next_cells;
    Cell* ctemp;

    if (current->get_type() == FREE)
    {
        current->set_pointed(cpointed);
        current->set_type(FLOW);

        for (i = 0; i < 4; ++i)
        {
            wtemp = current->get_x() + adjacents[i][0];
            htemp = current->get_y() + adjacents[i][1];

            if (wtemp >= 0 && wtemp < map_->get_width() && htemp >= 0 && htemp < map_->get_height())
            {
                if (map_->has_cell(wtemp, htemp))
                {
                    ctemp = map_->get_cell(wtemp, htemp);
                    if (ctemp->get_type() == FREE || ctemp->get_type() == END)
                        next_cells.push_back(ctemp);

                }
            }
        }

        // Launch the algorithm on every free cell beside the current one
        for (auto c : next_cells)
            algo_flow(c, current);
    }
    if (current->get_type() == END && cpointed->get_type() == FLOW)
    {
        current->set_type(PATH);
        // Begin printing the path of the maze
        algo_solve_path(cpointed);
    }
}

void AlgoPath::standard_solve_perfect_maze_rec(int w, int h)
{
    int htemp, wtemp = 0;
    int i = 0;
    std::vector<Cell*> next_cell;

    // Checks for free cells and add them to the list next_cell
    for (i = 0; i < 4; ++i)
    {
        wtemp = w + adjacents[i][0];
        htemp = h + adjacents[i][1];

        if (wtemp >= 0 && htemp >= 0 && htemp < map_->get_height() && wtemp < map_->get_width())
            // if it exists
            if (map_->has_cell(wtemp, htemp))
            {
                if (map_->get_cell(wtemp, htemp)->get_type() == FREE)
                    next_cell.push_back(map_->get_cell(wtemp, htemp));
            }

    }

    // The cell has 3 walls so we can eliminate it and check the only free cell
    // beside it
    if (next_cell.size() == 1)
    {
        map_->set_cell(w, h, WALL);
        emit update_gui();
        standard_solve_perfect_maze_rec(next_cell[0]->get_x(),
                                        next_cell[0]->get_y());
    }

}

void AlgoPath::run()
{
    map_->display();

    if (option_ == 1)
        standard_solve_any_maze();
    else
        standard_solve_perfect_maze();

}
