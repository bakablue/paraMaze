#include "colors.hh"
#include <QPainter>

Colors::Colors(QWidget *parent, Map* map)
    : QWidget(parent)
    , map_(map)
{

}

Colors::Colors()
{
}

Colors::~Colors()
{
}

void Colors::paintEvent(QPaintEvent *e)
{
    int i, j = 0;
    int width = 50;
    int height = 50;

    Q_UNUSED(e);

    QPainter painter(this);

    for (i = 0; i < map_->get_width(); i++)
    {
        for (j = 0; j < map_->get_height(); j++)
        {
            if (map_->get_map()->find(i * j + i)->second->get_type() == WALL)
                painter.setPen(QColor("#d4d4d4"));
            else
                painter.setPen(QColor("#1ac500"));

            painter.drawRect(i * width, j * height, width, height);
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
