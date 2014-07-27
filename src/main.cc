#include "parser.hh"
#include "mazegenerator.hh"
#include "algo_path.hh"
#include <thread>
#include <tbb/pipeline.h>

//void init_gui(int argc, char* argv[], Map *map)
//{
//}

int main(int argc, char *argv[])
{
    int parallel = 0;
    int gui = 0;
    int start = 3;
    int algo_choice = 1;

    if (argc == 1)
    {
        std::cout << "Usage : ./maze --solve [1|2] [--gui] [-p] test.txt [...]" << std::endl;
        std::cout << "        ./maze --generate hauteur largeur" << std::endl;
        return 1;
    }
    if (argc >= 1)
    {
        if (argv[1] == std::string("--solve"))
        {
            std::istringstream buffer(argv[2]);
            buffer >> algo_choice;
            if (argv[3] == std::string("--gui"))
            {
                gui = 1;
                start++;
            }
            if ((argc > 3 && argv[3] == std::string("-p")) ||
                (argc > 4 && argv[4] == std::string("-p")))
            {
                parallel = 1;
                start++;
            }
            for (int i = start; i < argc; i++)
            {
                Parser p = Parser(argv[i]);
                p.parse();

                AlgoPath *algo = new AlgoPath();
                algo->set_map(p.get_map());
                algo->set_option(algo_choice);
                algo->set_parallel(parallel);
                algo->set_gui(gui);

                QApplication app(argc, argv);
                Colors *window = new Colors();
                window->set_map(p.get_map());

                QObject::connect(algo, SIGNAL(update_gui()), window, SLOT(update_gui()), Qt::QueuedConnection);

                algo->start();
                if (gui)
                {
                    window->show();
                    app.exec();
                }
                algo->wait();
                algo->quit();
            }
        }
        else if (argv[1] == std::string("--generate"))
        {
            bool perfect = false;
            if (argc > 2 && argv[2] == std::string("--perfect"))
            {
                perfect = true;
            }
            char **argv2 = argv;
            QApplication app(argc, argv);
            Colors* window_ = new Colors();
            window_->set_isMaze(true);
            window_->resize(250, 150);
            window_->setWindowTitle("ParaMaze");

            MazeGenerator *maze = new MazeGenerator(std::stoi(argv2[3]), std::stoi(argv2[4]), perfect);
            // maze.Generate();
            // maze.Print();

            qRegisterMetaType<TMaze>("TMaze");
            QObject::connect(maze, SIGNAL(sendMaze(TMaze)), window_, SLOT(set_maze(TMaze)), Qt::QueuedConnection);

            maze->start();
            window_->show();

            app.exec();
            maze->quit();
            maze->wait();
        }
    }

    return 0;
}
