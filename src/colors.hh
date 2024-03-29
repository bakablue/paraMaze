#ifndef COLORS_HH
# define COLORS_HH

# include <QWidget>
# include <QMouseEvent>

# include "map.hh"

typedef std::vector<std::vector<Cell*> > TMaze;


class Colors : public QWidget
{
    Q_OBJECT
    public:
        Colors(QWidget *parent, Map* map);
        Colors();
        ~Colors();

        void set_map(Map* map);
        void set_isMaze(bool v);

        public slots:
            void set_maze(TMaze maze);
            void update_gui();

    private:
        Map* map_;
        std::vector<std::vector<Cell*> > maze_;
        bool isMaze_;
    protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *mouse);
};

#endif /* !COLORS_HH */
