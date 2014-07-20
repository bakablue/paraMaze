#include "colors.hh"
#include <QPainter>
#include <unistd.h>

Colors::Colors(QWidget *parent, Map* map)
  : QWidget(parent)
  , map_(map)
  , isMaze_(false)
{
    setMouseTracking(true); 
    resize(250, 150);
    setWindowTitle("ParaMaze");
}

Colors::Colors()
    : QWidget()
    , isMaze_(false)
{
    setMouseTracking(true); 
    resize(250, 150);
    setWindowTitle("ParaMaze");
}

Colors::~Colors()
{
}

void Colors::paintEvent(QPaintEvent *e)
{
    int i, j = 0;
    int width = 10;
    int height = 10;
    e_type_cell t;
    Cell *current;

    Q_UNUSED(e);

    QPainter painter(this);

    painter.setPen(QColor("#d4d4d4"));
    if (isMaze_)
    {
        for (unsigned i = 0; i < maze_.size(); i++)
        {
            for (unsigned j = 0; j < maze_[0].size(); j++)
            {
                current = maze_[i][j];
                t = current->get_type();
                if (t == WALL)
                    painter.setBrush(QBrush("#c56c00"));
                else if (t == FREE)
                    painter.setBrush(QBrush("#1ac500"));
                else if (t == PATH)
                    painter.setBrush(QBrush("#005AA4"));
                else if (t == END)
                    painter.setBrush(QBrush("#FF0000"));
                else if (t == START)
                    painter.setBrush(QBrush("#FF0000"));
                else if (t == FLOW)
                {
                    painter.setBrush(QBrush("#555555"));
                    painter.drawRect(j * width, i * height, width, height);

                    //// temporary test
                    if (current->get_x() - current->get_pointed()->get_x() > 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/left.png")));
                    else if (current->get_x() - current->get_pointed()->get_x() < 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/right.png")));
                    else if (current->get_y() - current->get_pointed()->get_y() < 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/down.png")));
                    else if (current->get_y() - current->get_pointed()->get_y() > 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/up.png")));

                }

                painter.drawRect(j * width, i * height, width, height);
            }
        } 
    }
    else
    {
        for (i = 0; i < map_->get_width(); i++)
        {
            for (j = 0; j < map_->get_height(); j++)
            {
                current = map_->get_map()->find(j * map_->get_width() + i)->second;
                t = current->get_type();
                if (t == WALL)
                    painter.setBrush(QBrush("#c56c00"));
                else if (t == FREE)
                    painter.setBrush(QBrush("#1ac500"));
                else if (t == PATH)
                    painter.setBrush(QBrush("#005AA4"));
                else if (t == END)
                    painter.setBrush(QBrush("#FF0000"));
                else if (t == START)
                    painter.setBrush(QBrush("#FF0000"));
                else if (t == FLOW)
                {
                    painter.setBrush(QBrush("#66FFCC"));
                    painter.drawRect(i * width, j * height, width, height);

                    // temporary test
                    if (current->get_x() - current->get_pointed()->get_x() > 0)
                        painter.setBrush(QBrush(QPixmap("../gui/left.png")));
                    else if (current->get_x() - current->get_pointed()->get_x() < 0)
                        painter.setBrush(QBrush(QPixmap("../gui/right.png")));
                    else if (current->get_y() - current->get_pointed()->get_y() < 0)
                        painter.setBrush(QBrush(QPixmap("../gui/down.png")));
                    else if (current->get_y() - current->get_pointed()->get_y() > 0)
                        painter.setBrush(QBrush(QPixmap("../gui/up.png")));

                }

                painter.drawRect(i * width, j * height, width, height);
            }
        }
    }
}

void Colors::mousePressEvent(QMouseEvent *mouse)
{
    // set end cell
    map_->get_cell(mouse->x() / 10, mouse->y() / 10)->set_type(END);
    map_->set_end_cell(true);
}

void Colors::set_map(Map* map)
{
    map_ = map;
    update();
}

void Colors::set_maze(std::vector<std::vector<Cell*> >  maze)
{
    maze_ = maze;
    update();
}

void Colors::set_isMaze(bool v)
{
    isMaze_ = v;
}

void Colors::update_gui()
{
    update();
}
