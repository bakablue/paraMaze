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
        void set_maze(std::vector<std::vector<Cell*> >  maze);
        void set_isMaze(bool v);
    private:
        Map* map_;
        std::vector<std::vector<Cell*> > maze_;
        bool isMaze_;
    protected:
        void paintEvent(QPaintEvent *event);
};

#endif /* !COLORS_HH */
