#include "parser.hh"
#include "mazegenerator.hh"

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
		        p.parse(argc, argv);
		    }
    	}
    	else if (argv[1] == std::string("--generate"))
    	{
			char **argv2 = argv;
		    QApplication app(argc, argv);
		    Colors* window_ = new Colors();
		    window_->set_isMaze(true);
		    window_->resize(250, 150);
		    window_->setWindowTitle("yolo");	

			MazeGenerator *maze = new MazeGenerator(std::stoi(argv2[2]), std::stoi(argv2[3]));
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
