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

    enum { None = -1, U, U2, U3, R, R2, R3, F, F2, F3 };
    enum { Note = -1, Up = 0, Right = 3, Forward = 2 };

    QVector<Sectors> vecKey[12];
    QVector<QVector<QVector<int>>> vecVal[12];
    Sectors mSectors;
    int size = 0;

    int row(int index);
    int column(int index);
    int index(int row, int column);
    void findSolution();

    constexpr static int SIZE_SECTION = 30;
    constexpr static int SHIFT = 50;
    constexpr static int APERTURE = 5;
    constexpr static int COUNT_SECTION = 2;

    QString names[6]{"U", "L", "F", "R", "B", "D"};
    int *mSelectSector = nullptr;

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);

    void rotates(int n, Sectors &sectors, const QVector<int> &vec);
    void rotate(int r, int n, Sectors sectors, QVector<int> vec);
};
