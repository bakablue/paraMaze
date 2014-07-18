#include "colors.hh"
#include <QPainter>

Colors::Colors(QWidget *parent, Map* map)
    : QWidget(parent)
    , map_(map)
    , isMaze_(false)
{

}

Colors::Colors()
  : isMaze_(false)
{
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
        for (unsigned i = 0; i < maze_.size() - 1; i++)
        {
            for (unsigned j = 0; j < maze_[0].size() - 1; j++)
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
                    painter.setBrush(QBrush("#1ac500"));
                    painter.drawRect(i * width, j * height, width, height);

                    // temporary test
                    if (current->get_x() - current->get_pointed()->get_x() > 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/left.png")));
                    else if (current->get_x() - current->get_pointed()->get_x() < 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/right.png")));
                    else if (current->get_y() - current->get_pointed()->get_y() < 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/down.png")));
                    else if (current->get_y() - current->get_pointed()->get_y() > 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/up.png")));

                }

                painter.drawRect(i * width, j * height, width, height);
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
                    painter.setBrush(QBrush("#1ac500"));
                    painter.drawRect(i * width, j * height, width, height);

                    // temporary test
                    if (current->get_x() - current->get_pointed()->get_x() > 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/left.png")));
                    else if (current->get_x() - current->get_pointed()->get_x() < 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/right.png")));
                    else if (current->get_y() - current->get_pointed()->get_y() < 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/down.png")));
                    else if (current->get_y() - current->get_pointed()->get_y() > 0)
                        painter.setBrush(QBrush(QPixmap("../gui/img/up.png")));

                }

                painter.drawRect(i * width, j * height, width, height);
            }
        }
    }
    /*painter.setPen(QColor("#d4d4d4"));

      painter.setBrush(QBrush("#c56c00"));
      painter.drawRect(10, 15, 50, 50);

      painter.setBrush(QBrush("#1ac500"));
      painter.drawRect(130, 15, 50, 50);

      painter.setBrush(QBrush("#539e47"));
      painter.drawRect(250, 15, 50, 50);

      painter.setBrush(QBrush("#004fc5"));
      painter.drawRect(10, 105, 50, 50);

      painter.setBrush(QBrush("#c50024"));
      painter.drawRect(130, 105, 50, 50);

      painter.setBrush(QBrush("#9e4757"));
      painter.drawRect(250, 105, 50, 50);

      painter.setBrush(QBrush("#5f3b00"));
      painter.drawRect(10, 195, 50, 50);

      painter.setBrush(QBrush("#4c4c4c"));
      painter.drawRect(130, 195, 50, 50);

      painter.setBrush(QBrush("#785f36"));
      painter.drawRect(250, 195, 50, 50);*/
}

void Colors::set_map(Map* map)
{
    map_ = map;
}

void Colors::set_maze(std::vector<std::vector<Cell*> >  maze)
{
    maze_ = maze;
}

void Colors::set_isMaze(bool v)
{
    isMaze_ = v;
}
