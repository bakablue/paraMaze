#ifndef COLORS_HH
# define COLORS_HH

# include <QWidget>

# include "map.hh"

class Colors : public QWidget
{
    public:
        Colors(QWidget *parent, Map* map);
        Colors();
        ~Colors();

        void set_map(Map* map);
    private:
        Map* map_;
    protected:
        void paintEvent(QPaintEvent *event);
};

#endif /* !COLORS_HH */
