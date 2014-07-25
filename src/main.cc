#include "parser.hh"
#include "mazegenerator.hh"
#include "algo_path.hh"
#include <thread>

void init_gui(int argc, char* argv[], Map *map)
{
    QApplication app(argc, argv);

    Colors window;
    window.set_map(map);
    window.resize(250, 150);
    window.setWindowTitle("yolo");
    window.show();

    app.exec();
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "Usage : ./maze --solve test.txt [...]" << std::endl;
        std::cout << "        ./maze --generate hauteur largeur" << std::endl;
        return 1;
    }
    if (argc >= 1)
    {
        if (argv[1] == std::string("--solve"))
        {
            for (int i = 2; i < argc; i++)
            {
                Parser p = Parser(argv[i]);
                p.parse();
                std::thread gui(init_gui, argc, argv, p.get_map());
                AlgoPath algo;
                algo.set_map(p.get_map());
                algo.set_option(1);
                algo.start();
                // wait for thread
                gui.join();

            }
        }
        else if (argv[1] == std::string("--generate"))
        {
            char **argv2 = argv;
            QApplication app(argc, argv);
            Colors* window_ = new Colors();
            window_->set_isMaze(true);
            window_->resize(250, 150);
            window_->setWindowTitle("ParaMaze");

            MazeGenerator *maze = new MazeGenerator(std::stoi(argv2[2]), std::stoi(argv2[3]));
            // maze.Generate();
            // maze.Print();

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
