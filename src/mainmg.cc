#include <QtGui>
#include <QApplication>
#include <QWidget>
#include <QThread>

#include "mazegenerator.hh"

int main(int argc, char *argv[])
{
	char **argv2 = argv;
    QApplication app(argc, argv);
    Colors* window_ = new Colors();
    window_->set_isMaze(true);
    window_->resize(250, 150);
    window_->setWindowTitle("yolo");	

	MazeGenerator *maze = new MazeGenerator(std::stoi(argv2[1]), std::stoi(argv2[2]));
	// maze.Generate();
	// maze.Print();

	QObject::connect(maze, SIGNAL(sendMaze(TMaze)), window_, SLOT(set_maze(TMaze)), Qt::QueuedConnection);

	maze->start();
    window_->show();

    app.exec();
    maze->quit();
    maze->wait();

	return 0;
}