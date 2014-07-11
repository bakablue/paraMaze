#include <QApplication>
#include <QWidget>

#include "colors.hh"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Colors window;

    window.resize(250, 150);
    window.setWindowTitle("Simple example");
    window.show();

    return app.exec();
}
