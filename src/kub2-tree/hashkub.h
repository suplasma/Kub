#pragma once

#include <QDebug>
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

    enum { None = -1, U, U2, U3, R, R2, R3, F, F2, F3 };
    enum { Note = -1, Up = 0, Right = 3, Forward = 2 };

    Tree tree;
    Sectors mSectors;
    uint size = 0;
    int mSelectAngle = -1;
    int mValSelectAngle = -1;
    QVector<int> mMovebleAngle;

    int row(int index);
    int column(int index);
    int index(int row, int column);
    void findSolution();
    void click(Qt::MouseButton button, Qt::KeyboardModifiers mod, int num, int n, int row,
               int column);

    constexpr static int SIZE_SECTION = 30;
    constexpr static int SHIFT = 50;
    constexpr static int APERTURE = 5;
    constexpr static int COUNT_SECTION = 2;

    QString names[6]{"U", "", "F", "R", "", ""};

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);

    void rotates(const Sectors &sectors, const QVector<uint8_t> &vec);
    void rotate(int r, Sectors sectors, QVector<uint8_t> vec);
};
