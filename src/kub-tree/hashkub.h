#pragma once

#include <QWidget>

#include <sectors.h>
#include <tree.h>

namespace Ui {
class HashKub;
}

class HashKub : public QWidget {
    Q_OBJECT

public:
    explicit HashKub(QWidget *parent = 0);
    ~HashKub();

private slots:
    void on_downloadBtn_clicked();
    void on_findBtn_clicked();
    void on_resetBtn_clicked();

private:
    Ui::HashKub *ui;

    enum { None = -1, U, U2, U3, D, D2, D3, R, R2, R3, L, L2, L3, F, F2, F3, B, B2, B3 };
    enum { Note = -1, Up, Left, Forward, Right, Back, Down };

    Tree tree;
    Sectors mSectors;
    int size = 0;
    int mSelectSector = -1;
    int mValSelectSector = -1;

    int row(int index);
    int column(int index);
    int index(int row, int column);
    void findSolution();
    void click(Qt::MouseButton button, int num, int n, int row, int column);

    constexpr static int SIZE_SECTION = 30;
    constexpr static int SHIFT = 50;
    constexpr static int APERTURE = 5;
    constexpr static int COUNT_SECTION = 3;

    QString names[6]{"U", "L", "F", "R", "B", "D"};

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);

    void rotates(const Sectors &sectors, const QVector<uint8_t> &vec);
    void rotate(int r, Sectors sectors, QVector<uint8_t> vec);
};
