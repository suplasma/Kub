#include "hashkub.h"

#include <QFile>
#include <QMouseEvent>
#include <QPainter>

#include <iostream>

#include "ui_hashkub.h"

HashKub::HashKub(QWidget *parent) : QWidget(parent), ui(new Ui::HashKub)
{
    ui->setupUi(this);

    vecKey[0].resize(1);
    vecVal[0].resize(1);
    vecVal[0][0].resize(1);
}

HashKub::~HashKub()
{
    delete ui;
}

void HashKub::rotates(int n, Sectors &sectors, const QVector<int> &vec)
{
    if (vec.isEmpty()) {
        rotate(U, n, sectors, vec);
        rotate(U2, n, sectors, vec);
        rotate(U3, n, sectors, vec);

        rotate(R, n, sectors, vec);
        rotate(R2, n, sectors, vec);
        rotate(R3, n, sectors, vec);

        rotate(F, n, sectors, vec);
        rotate(F2, n, sectors, vec);
        rotate(F3, n, sectors, vec);
    } else {
        switch (vec.first()) {
            case U:
            case U2:
            case U3:
                rotate(R, n, sectors, vec);
                rotate(R2, n, sectors, vec);
                rotate(R3, n, sectors, vec);

                rotate(F, n, sectors, vec);
                rotate(F2, n, sectors, vec);
                rotate(F3, n, sectors, vec);

                break;

            case R:
            case R2:
            case R3:
                rotate(F, n, sectors, vec);
                rotate(F2, n, sectors, vec);
                rotate(F3, n, sectors, vec);

                rotate(U, n, sectors, vec);
                rotate(U2, n, sectors, vec);
                rotate(U3, n, sectors, vec);

                break;

            case F:
            case F2:
            case F3:
                rotate(R, n, sectors, vec);
                rotate(R2, n, sectors, vec);
                rotate(R3, n, sectors, vec);

                rotate(U, n, sectors, vec);
                rotate(U2, n, sectors, vec);
                rotate(U3, n, sectors, vec);

                break;
        }
    }
}

void HashKub::rotate(int r, int n, Sectors sectors, QVector<int> vec)
{
    sectors.rotate(r);

    for (int i = 0; i < n; ++i) {
        if (vecKey[i].contains(sectors)) {
            return;
        }
    }

    vec.push_front(r);

    int index = vecKey[n].indexOf(sectors);

    if (index == -1) {
        vecKey[n].append(sectors);
        index = vecVal[n].size();
        vecVal[n].resize(index + 1);
    }

    vecVal[n][index].append(vec);
}

void HashKub::on_downloadBtn_clicked()
{
    for (; size < ui->spinBox->value(); ++size) {
        for (int i = 0; i < vecKey[size].size(); ++i) {
            for (auto &vec : vecVal[size][i]) {
                rotates(size + 1, vecKey[size][i], vec);
            }
        }
    }

    int count = 0;
    for (int i = 0; i < 12; ++i) {
        count += vecKey[i].size();
    }

    std::cout << "done " << count << std::endl;
}

void HashKub::on_findBtn_clicked()
{
    ui->findBtn->setEnabled(false);
    findSolution();
    ui->findBtn->setEnabled(true);
    std::cout << std::endl;
}

void HashKub::on_resetBtn_clicked()
{
    mSectors = Sectors();
    mSelectSector = nullptr;
    repaint();
}

int HashKub::row(int index)
{
    return index == 0 ? 0 : (index == 5 ? 2 : 1);
}

int HashKub::column(int index)
{
    return (index == 0 || index == 5) ? 1 : index - 1;
}

int HashKub::index(int row, int column)
{
    switch (row) {
        case 0:
            if (column == 1) {
                return 0;
            }

            break;

        case 1:
            if (column <= 3) {
                return column + 1;
            }

            break;

        case 2:
            if (column == 1) {
                return 5;
            }

            break;
    }

    return -1;
}

void HashKub::findSolution()
{
    for (int i = 0; i <= ui->spinBox->value(); ++i) {
        int index = vecKey[i].indexOf(mSectors);
        if (index != -1) {
            for (auto &vec : vecVal[i][index]) {
                QString res;

                for (auto &el : vec) {
                    switch (el) {
                        case U: res += "U  "; break;
                        case U2: res += "U2 "; break;
                        case U3: res += "U' "; break;
                        case R: res += "R  "; break;
                        case R2: res += "R2 "; break;
                        case R3: res += "R' "; break;
                        case F: res += "F  "; break;
                        case F2: res += "F2 "; break;
                        case F3: res += "F' "; break;
                    }
                }

                std::cout << res.toStdString() << std::endl;
            }

            return;
        }
    }
}

void HashKub::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(QBrush(Qt::black), 3.));

    for (int index = 0; index < 6; ++index) {
        for (int i = 0; i < COUNT_SECTION; ++i) {
            for (int j = 0; j < COUNT_SECTION; ++j) {
                switch (mSectors.matrics[index][i][j]) {
                    case 0:
                    case 1:
                    case 2:
                    case 3: painter.setBrush(QBrush(Qt::yellow)); break;
                    case 4:
                    case 5:
                    case 6:
                    case 7: painter.setBrush(QBrush(QColor(255, 127, 39))); break;
                    case 8:
                    case 9:
                    case 10:
                    case 11: painter.setBrush(QBrush(QColor(0, 158, 210))); break;
                    case 12:
                    case 13:
                    case 14:
                    case 15: painter.setBrush(QBrush(Qt::red)); break;
                    case 16:
                    case 17:
                    case 18:
                    case 19: painter.setBrush(QBrush(Qt::green)); break;
                    case 20:
                    case 21:
                    case 22:
                    case 23: painter.setBrush(QBrush(Qt::white)); break;
                }

                if (mSelectSector && mSectors.matrics[index][i][j] == *mSelectSector) {
                    painter.setPen(QPen(QBrush(Qt::black), 5.));

                    painter.drawRect(j * SIZE_SECTION + SHIFT +
                                         column(index) *
                                             (COUNT_SECTION * SIZE_SECTION + APERTURE),
                                     i * SIZE_SECTION + SHIFT +
                                         row(index) * (COUNT_SECTION * SIZE_SECTION + APERTURE),
                                     SIZE_SECTION, SIZE_SECTION);

                    painter.setPen(QPen(QBrush(Qt::black), 3.));
                } else {
                    painter.drawRect(j * SIZE_SECTION + SHIFT +
                                         column(index) *
                                             (COUNT_SECTION * SIZE_SECTION + APERTURE),
                                     i * SIZE_SECTION + SHIFT +
                                         row(index) * (COUNT_SECTION * SIZE_SECTION + APERTURE),
                                     SIZE_SECTION, SIZE_SECTION);
                }

                int n = mSectors.matrics[index][i][j] % 4;

                if (false) {
                    auto font = painter.font();
                    font.setPixelSize(16);
                    painter.setFont(font);

                    painter.drawText(
                        QRectF(j * SIZE_SECTION + SHIFT +
                                   column(index) * (COUNT_SECTION * SIZE_SECTION + APERTURE),
                               i * SIZE_SECTION + SHIFT +
                                   row(index) * (COUNT_SECTION * SIZE_SECTION + APERTURE),
                               SIZE_SECTION, SIZE_SECTION),
                        names[index], QTextOption(Qt::AlignCenter));
                } else {
                    auto font = painter.font();
                    font.setPixelSize(10);
                    painter.setFont(font);

                    painter.drawText(
                        QRectF(j * SIZE_SECTION + SHIFT +
                                   column(index) * (COUNT_SECTION * SIZE_SECTION + APERTURE),
                               i * SIZE_SECTION + SHIFT +
                                   row(index) * (COUNT_SECTION * SIZE_SECTION + APERTURE),
                               SIZE_SECTION, SIZE_SECTION),
                        QString::number(n), QTextOption(Qt::AlignCenter));
                }
            }
        }
    }
}

void HashKub::mousePressEvent(QMouseEvent *ev)
{
    if (ev->x() >= SHIFT && ev->y() >= SHIFT) {
        int n = index((ev->y() - SHIFT) / (COUNT_SECTION * SIZE_SECTION + APERTURE),
                      (ev->x() - SHIFT) / (COUNT_SECTION * SIZE_SECTION + APERTURE));

        if (n != -1) {
            int x = ev->x() - (SHIFT + column(n) * (COUNT_SECTION * SIZE_SECTION + APERTURE));
            int y = ev->y() - (SHIFT + row(n) * (COUNT_SECTION * SIZE_SECTION + APERTURE));
            int row = y / SIZE_SECTION;
            int column = x / SIZE_SECTION;

            if (row != 3 && column != 3) {
                switch (n) {
                    case Up:
                        switch (ev->button()) {
                            case Qt::RightButton: mSectors.rotate(U); break;
                            case Qt::LeftButton: mSectors.rotate(U3); break;
                        }

                        break;

                    case Forward:
                        switch (ev->button()) {
                            case Qt::RightButton: mSectors.rotate(F); break;
                            case Qt::LeftButton: mSectors.rotate(F3); break;
                        }

                        break;

                    case Right:
                        switch (ev->button()) {
                            case Qt::RightButton: mSectors.rotate(R); break;
                            case Qt::LeftButton: mSectors.rotate(R3); break;
                        }

                        break;
                }

                repaint();
            }
        }
    }
}
