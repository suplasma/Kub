#pragma once

#include <QWidget>

#include <kubthread.h>

namespace Ui {
class KubLonWindow;
}

class KubLonWindow : public QWidget {
    Q_OBJECT

public:
    explicit KubLonWindow(QWidget *parent = 0);
    ~KubLonWindow();

private slots:
    void on_findBtn_clicked();
    void on_resetBtn_clicked();

private:
    Ui::KubLonWindow *ui;
    int row(int index);
    int column(int index);
    int index(int row, int column);
    void addThread(int n1, int n2, int countRotate);
    void rotate(int n);
    void reset();

    constexpr static int SIZE_SECTION = 30;
    constexpr static int SHIFT = 50;
    constexpr static int APERTURE = 5;

    int matrics[6][KubThread::COUNT_SECTION][KubThread::COUNT_SECTION];
    QString names[6]{"U", "L", "F", "R", "B", "D"};
    std::atomic<int> countThread;

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
};
