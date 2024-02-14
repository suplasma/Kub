#pragma once

#include <QDebug>
#include <QHash>
#include <QWidget>

#include <sectors.h>

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

    QVector<QHash<Sectors, QVector<QVector<int>>>> hashVec;
    Sectors mSectors;

    int row(int index);
    int column(int index);
    int index(int row, int column);
    void read();
    void findSolution();

    constexpr static int SIZE_SECTION = 30;
    constexpr static int SHIFT = 50;
    constexpr static int APERTURE = 5;
    constexpr static int COUNT_SECTION = 3;

    QString names[6]{"U", "L", "F", "R", "B", "D"};
    int *mSelectSector = nullptr;

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);

    void save();
    void rotates(int n, Sectors &sectors, const QVector<int> &vec);
    void rotate(int r, int n, Sectors sectors, QVector<int> vec);
};
