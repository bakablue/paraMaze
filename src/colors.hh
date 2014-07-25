#ifndef COLORS_HH
# define COLORS_HH

# include <QWidget>

# include "map.hh"

typedef std::vector<std::vector<Cell*> > TMaze;

// http://stackoverflow.com/questions/14545961/modify-qt-gui-from-background-worker-thread

class Colors : public QWidget
{
    public:
        Colors(QWidget *parent, Map* map);
        Colors();
        ~Colors();

        void set_map(Map* map);
        void set_isMaze(bool v);

    public slots:
        void set_maze(TMaze maze);
        void on_update_map(int i, int j);

    private:
        Map* map_;
        std::vector<std::vector<Cell*> > maze_;
        bool isMaze_;
    protected:
        void paintEvent(QPaintEvent *event);
};

#endif /* !COLORS_HH */
