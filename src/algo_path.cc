#include "algo_path.hh"
#include <tbb/tick_count.h>
#include <atomic>

tbb::concurrent_vector<tbb::concurrent_vector<int> > AlgoPath::adjacents;

AlgoPath::AlgoPath()
    : QThread()
    , option_(0)
    , parallel_(0)
    , gui_(0)
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

void AlgoPath::set_parallel(int parallel)
{
    parallel_ = parallel;
}

void AlgoPath::set_gui(int gui)
{
    gui_ = gui;
}

void AlgoPath::standard_solve_any_maze()
{
    algo_flow();
}

void AlgoPath::get_isolated_cells(tbb::concurrent_vector<Cell*> &init_cells,
                                  int w, int h)
{
    int htemp, wtemp = 0;
    std::atomic<int> count(0);

    Cell *c, *ctemp;

    c = map_->get_cell(w, h);
    if ((c->get_type() != WALL && c->get_type() != END
         && c->get_type() != START))
    {
        count = 0;
        for (int i = 0; i < 4; ++i)
        {
            wtemp = w + adjacents[i][0];
            htemp = h + adjacents[i][1];

            if (wtemp >= 0 && wtemp < map_->get_width()
                && htemp >= 0 && htemp < map_->get_height())
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

void AlgoPath::standard_solve_perfect_maze()
{
    perfect_path_ = true;
    Map *new_map = new Map(map_->get_width(), map_->get_height());

    // Initialization of copy
        for (int j = 0; j < map_->get_height(); ++j)
            for (int i = 0; i < map_->get_width(); ++i)
                new_map->get_map()->push_back(new Cell(i, j, map_->get_cell(i, j)->get_type()));

    while (perfect_path_)
    {
        perfect_path_ = false;
        if (parallel_)
        {
            tbb::parallel_for(tbb::blocked_range<size_t>(0, new_map->get_width() * new_map->get_height()),
                              // Lambda that works on a vector of cells
                              [&](const tbb::blocked_range<size_t> r)
                              {
                              for (size_t i = r.begin(); i != r.end(); ++i)
                                standard_solve_perfect_maze_rec((*(map_->get_map()))[i], new_map);
                              }
                             );
        }
        else
        {
            for (int j = 0; j < map_->get_height(); ++j)
                for (int i = 0; i < map_->get_width(); ++i)
                    count += standard_solve_perfect_maze_rec(map_->get_cell(i, j), new_map);
        }
        std::cout << count << std::endl;
        map_->update_map(new_map);
        if (gui_)
        {
            emit update_gui();
            usleep(50000);
        }
    }

}

void AlgoPath::algo_solve_path(Cell* current)
{
    if (current->get_type() != START)
        algo_solve_path(current->get_pointed());
    current->set_type(PATH);
    if (gui_)
    {
        emit update_gui();
        usleep(50000);
    }
}

void AlgoPath::algo_flow_cell(Cell* current, Map* map)
{
    int wtemp = 0;
    int htemp = 0;
    int i = 0;
    Cell *current_to_set = map->get_cell(current->get_x(), current->get_y());

    if (current->get_type() == FREE || current->get_type() == END)
    {
        for (i = 0; i < 4; ++i)
        {
            wtemp = current->get_x() + adjacents[i][0];
            htemp = current->get_y() + adjacents[i][1];

            if (wtemp >= 0 && wtemp < map_->get_width() &&
                htemp >= 0 && htemp < map_->get_height())
                if (map_->get_cell(wtemp, htemp)->get_type() == FLOW ||
                    map_->get_cell(wtemp, htemp)->get_type() == START)
                {
                    current_to_set->set_pointed(map->get_cell(wtemp, htemp));
                    break;
                }

        }
    }
    if (current->get_type() == PATH && current_to_set->get_pointed())
        current_to_set->get_pointed()->set_type(PATH);
    if (current->get_type() == FREE && current_to_set->get_pointed())
        current_to_set->set_type(FLOW);
    if (current->get_type() == END && current->get_pointed())
        current_to_set->set_type(PATH);

}

void AlgoPath::algo_flow2(Map *map)
{
    int h = 0;
    int w = 0;

    if (parallel_)
    {
        tbb::parallel_for(tbb::blocked_range<size_t>(0, map->get_width() * map->get_height()),
                          // Lambda that works on a vector of cells
                          [&](const tbb::blocked_range<size_t> r)
                          {
                          for (size_t i = r.begin(); i != r.end(); ++i)
                          algo_flow_cell((*(map_->get_map()))[i], map);
                          }
                         );
    }
    else
        for (h = 0; h < map_->get_height(); ++h)
            for (w = 0; w < map_->get_width(); ++w)
                algo_flow_cell(map_->get_cell(w, h),
                               map);

    map_->update_map(map);

    if (gui_)
    {
        emit update_gui();
        usleep(50000);
    }
}

void AlgoPath::algo_flow()//Cell* current, Cell* cpointed)
{
    Map *new_map = new Map(map_->get_width(), map_->get_height());
    for (int j = 0; j < map_->get_height(); ++j)
        for (int i = 0; i < map_->get_width(); ++i)
            new_map->get_map()->push_back(new Cell(i, j, map_->get_cell(i, j)->get_type()));

    while (map_->get_start_cell()->get_type() != PATH)
        algo_flow2(new_map);
}

int AlgoPath::standard_solve_perfect_maze_rec(Cell *current, Map* map)
{
    int count = 0;
    int wtemp = 0;
    int htemp = 0;
    int i = 0;

    if (current->get_type() == FREE)
    {
        // Checks for free cells besides the current one
        for (i = 0; i < 4; ++i)
        {
            wtemp = current->get_x() + adjacents[i][0];
            htemp = current->get_y() + adjacents[i][1];

            if (wtemp >= 0 && htemp >= 0 && htemp < map_->get_height()
                && wtemp < map_->get_width())
                // if it exists
                if (map_->get_cell(wtemp, htemp)->get_type() == FREE ||
                    map_->get_cell(wtemp, htemp)->get_type() == START ||
                    map_->get_cell(wtemp, htemp)->get_type() == END)
                    count++;

        }

        // The cell has 3 walls so we can eliminate it and check the only free cell
        // beside it
        if (count == 1)
        {
            map->get_cell(current->get_x(), current->get_y())->set_type(WALL);
            perfect_path_ = true;
            return count;
        }
    }

    return 0;

}

void AlgoPath::run()
{
    if (gui_ && !map_->has_end_cell())
        while (!map_->has_end_cell());
    std::cout << "=== Initial map ===" << std::endl;
    map_->display();
    tbb::tick_count t0 = tbb::tick_count::now();
    if (option_ == 1)
        standard_solve_any_maze();
    else
        standard_solve_perfect_maze();
    tbb::tick_count t1 = tbb::tick_count::now();
    std::cout << "Performance of the algorithm" << std::endl;
    std::cout << (t1 - t0).seconds() << "s" << std::endl;
    std::cout << "=== Ending map ===" << std::endl;
    map_->display();
}
