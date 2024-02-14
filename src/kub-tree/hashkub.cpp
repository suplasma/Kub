#include "hashkub.h"

#include <QDebug>
#include <QFile>
#include <QMouseEvent>
#include <QPainter>

#include <iostream>

#include "ui_hashkub.h"

HashKub::HashKub(QWidget *parent) : QWidget(parent), ui(new Ui::HashKub)
{
    ui->setupUi(this);
    tree.append(Sectors(), QVector<uint8_t>());
}

HashKub::~HashKub()
{
    delete ui;
}

void HashKub::rotates(const Sectors &sectors, const QVector<uint8_t> &vec)
{
    if (vec.isEmpty()) {
        rotate(U, sectors, vec);
        rotate(U2, sectors, vec);
        rotate(U3, sectors, vec);
        rotate(D, sectors, vec);
        rotate(D2, sectors, vec);
        rotate(D3, sectors, vec);

        rotate(R, sectors, vec);
        rotate(R2, sectors, vec);
        rotate(R3, sectors, vec);
        rotate(L, sectors, vec);
        rotate(L2, sectors, vec);
        rotate(L3, sectors, vec);

        rotate(F, sectors, vec);
        rotate(F2, sectors, vec);
        rotate(F3, sectors, vec);
        rotate(B, sectors, vec);
        rotate(B2, sectors, vec);
        rotate(B3, sectors, vec);
    } else {
        switch (vec.first()) {
            case U:
            case U2:
            case U3:
                rotate(R, sectors, vec);
                rotate(R2, sectors, vec);
                rotate(R3, sectors, vec);
                rotate(L, sectors, vec);
                rotate(L2, sectors, vec);
                rotate(L3, sectors, vec);

                rotate(F, sectors, vec);
                rotate(F2, sectors, vec);
                rotate(F3, sectors, vec);
                rotate(B, sectors, vec);
                rotate(B2, sectors, vec);
                rotate(B3, sectors, vec);

                break;

            case D:
            case D2:
            case D3:
                rotate(U, sectors, vec);
                rotate(U2, sectors, vec);
                rotate(U3, sectors, vec);

                rotate(R, sectors, vec);
                rotate(R2, sectors, vec);
                rotate(R3, sectors, vec);
                rotate(L, sectors, vec);
                rotate(L2, sectors, vec);
                rotate(L3, sectors, vec);

                rotate(F, sectors, vec);
                rotate(F2, sectors, vec);
                rotate(F3, sectors, vec);
                rotate(B, sectors, vec);
                rotate(B2, sectors, vec);
                rotate(B3, sectors, vec);

                break;

            case R:
            case R2:
            case R3:
                rotate(F, sectors, vec);
                rotate(F2, sectors, vec);
                rotate(F3, sectors, vec);
                rotate(B, sectors, vec);
                rotate(B2, sectors, vec);
                rotate(B3, sectors, vec);

                rotate(U, sectors, vec);
                rotate(U2, sectors, vec);
                rotate(U3, sectors, vec);
                rotate(D, sectors, vec);
                rotate(D2, sectors, vec);
                rotate(D3, sectors, vec);

                break;

            case L:
            case L2:
            case L3:
                rotate(R, sectors, vec);
                rotate(R2, sectors, vec);
                rotate(R3, sectors, vec);

                rotate(F, sectors, vec);
                rotate(F2, sectors, vec);
                rotate(F3, sectors, vec);
                rotate(B, sectors, vec);
                rotate(B2, sectors, vec);
                rotate(B3, sectors, vec);

                rotate(U, sectors, vec);
                rotate(U2, sectors, vec);
                rotate(U3, sectors, vec);
                rotate(D, sectors, vec);
                rotate(D2, sectors, vec);
                rotate(D3, sectors, vec);

                break;

            case F:
            case F2:
            case F3:
                rotate(R, sectors, vec);
                rotate(R2, sectors, vec);
                rotate(R3, sectors, vec);
                rotate(L, sectors, vec);
                rotate(L2, sectors, vec);
                rotate(L3, sectors, vec);

                rotate(U, sectors, vec);
                rotate(U2, sectors, vec);
                rotate(U3, sectors, vec);
                rotate(D, sectors, vec);
                rotate(D2, sectors, vec);
                rotate(D3, sectors, vec);

                break;

            case B:
            case B2:
            case B3:
                rotate(F, sectors, vec);
                rotate(F2, sectors, vec);
                rotate(F3, sectors, vec);

                rotate(R, sectors, vec);
                rotate(R2, sectors, vec);
                rotate(R3, sectors, vec);
                rotate(L, sectors, vec);
                rotate(L2, sectors, vec);
                rotate(L3, sectors, vec);

                rotate(U, sectors, vec);
                rotate(U2, sectors, vec);
                rotate(U3, sectors, vec);
                rotate(D, sectors, vec);
                rotate(D2, sectors, vec);
                rotate(D3, sectors, vec);

                break;
        }
    }
}

void HashKub::rotate(int r, Sectors sectors, QVector<uint8_t> vec)
{
    sectors.rotate(r);

    if (tree.size(sectors) <= static_cast<uint>(vec.size())) {
        return;
    }

    vec.push_front(r);
    tree.append(sectors, vec);
}

void HashKub::on_downloadBtn_clicked()
{
    for (; size < ui->spinBox->value(); ++size) {
        for (auto &key : tree.keys(size)) {
            for (const auto &vec : tree.value(key)) {
                rotates(key, vec);
            }
        }
    }

    std::cout << "done" << std::endl;
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
    mSelectSector = -1;
    mValSelectSector = -1;
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
    bool flag = false;

    for (const auto &vec : tree.value(mSectors)) {
        QString res;

        for (auto &el : vec) {
            switch (el) {
                case U: res += "U  "; break;
                case U2: res += "U2 "; break;
                case U3: res += "U' "; break;
                case D: res += "D  "; break;
                case D2: res += "D2 "; break;
                case D3: res += "D' "; break;
                case R: res += "R  "; break;
                case R2: res += "R2 "; break;
                case R3: res += "R' "; break;
                case L: res += "L  "; break;
                case L2: res += "L2 "; break;
                case L3: res += "L' "; break;
                case F: res += "F  "; break;
                case F2: res += "F2 "; break;
                case F3: res += "F' "; break;
                case B: res += "B  "; break;
                case B2: res += "B2 "; break;
                case B3: res += "B' "; break;
            }
        }

        std::cout << res.toStdString() << std::endl;
        flag = true;
    }

    if (flag) {
        return;
    }

    for (int arrIndex = 1; arrIndex <= ui->spinBox->value(); ++arrIndex) {
        for (auto &key : tree.keys(arrIndex)) {
            Sectors sec = mSectors;
            int arr[54];
            int n = 0;
            for (int index = 0; index < 6; ++index) {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        arr[key.matrics[index][i][j]] = sec.matrics[index][i][j];
                    }
                }
            }

            for (int index = 0; index < 6; ++index) {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        sec.matrics[index][i][j] = arr[n];
                        ++n;
                    }
                }
            }

            if (tree.size(sec) == static_cast<uint>(ui->spinBox->value())) {
                flag = true;
                for (auto &vecHash : tree.value(sec)) {
                    for (auto &vec : tree.value(key)) {
                        switch (vec.last()) {
                            case D:
                            case D2:
                            case D3:
                                switch (vecHash.first()) {
                                    case U:
                                    case U2:
                                    case U3: continue;
                                }
                                break;

                            case B:
                            case B2:
                            case B3:
                                switch (vecHash.first()) {
                                    case F:
                                    case F2:
                                    case F3: continue;
                                }
                                break;

                            case L:
                            case L2:
                            case L3:
                                switch (vecHash.first()) {
                                    case R:
                                    case R2:
                                    case R3: continue;
                                }
                                break;
                        }

                        QString res;

                        for (auto &el : vec) {
                            switch (el) {
                                case U: res += "U  "; break;
                                case U2: res += "U2 "; break;
                                case U3: res += "U' "; break;
                                case D: res += "D  "; break;
                                case D2: res += "D2 "; break;
                                case D3: res += "D' "; break;
                                case R: res += "R  "; break;
                                case R2: res += "R2 "; break;
                                case R3: res += "R' "; break;
                                case L: res += "L  "; break;
                                case L2: res += "L2 "; break;
                                case L3: res += "L' "; break;
                                case F: res += "F  "; break;
                                case F2: res += "F2 "; break;
                                case F3: res += "F' "; break;
                                case B: res += "B  "; break;
                                case B2: res += "B2 "; break;
                                case B3: res += "B' "; break;
                            }
                        }

                        for (auto &el : vecHash) {
                            switch (el) {
                                case U: res += "U  "; break;
                                case U2: res += "U2 "; break;
                                case U3: res += "U' "; break;
                                case D: res += "D  "; break;
                                case D2: res += "D2 "; break;
                                case D3: res += "D' "; break;
                                case R: res += "R  "; break;
                                case R2: res += "R2 "; break;
                                case R3: res += "R' "; break;
                                case L: res += "L  "; break;
                                case L2: res += "L2 "; break;
                                case L3: res += "L' "; break;
                                case F: res += "F  "; break;
                                case F2: res += "F2 "; break;
                                case F3: res += "F' "; break;
                                case B: res += "B  "; break;
                                case B2: res += "B2 "; break;
                                case B3: res += "B' "; break;
                            }
                        }

                        std::cout << res.toStdString() << std::endl;
                    }
                }
            }
        }

        if (flag) {
            return;
        }
    }
}

void HashKub::click(Qt::MouseButton button, int num, int n, int row, int column)
{
    switch (button) {
        case Qt::LeftButton:
            if (mSelectSector != -1) {
                if ((num < 8) == (mSelectSector < 8)) {
                    auto vec = mSectors.toVec();
                    std::swap(vec[mSelectSector], vec[num]);
                    mSectors = Sectors(vec);
                    mSelectSector = -1;
                    mValSelectSector = -1;
                }
            } else {
                mSelectSector = num;
                mValSelectSector = mSectors.matrics[n][row][column];
            }

            break;

        case Qt::RightButton:
            auto vec = mSectors.toVec();
            auto &res = vec[num];

            if ((row == 1) || (column == 1)) {
                res ^= 1;
            } else {
                res += ((res + 1) % 3) - (res % 3);
            }

            mSectors = Sectors(vec);

            break;
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
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8: painter.setBrush(QBrush(Qt::yellow)); break;
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17: painter.setBrush(QBrush(QColor(255, 127, 39))); break;
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26: painter.setBrush(QBrush(QColor(0, 158, 210))); break;
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35: painter.setBrush(QBrush(Qt::red)); break;
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44: painter.setBrush(QBrush(Qt::green)); break;
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53: painter.setBrush(QBrush(Qt::white)); break;
                }

                if (mSectors.matrics[index][i][j] == mValSelectSector) {
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

                int n = mSectors.matrics[index][i][j] % 9;

                if (n == 4) {
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

            if (row == 1 && column == 1) {
                switch (n) {
                    case Up:
                        switch (ev->button()) {
                            case Qt::RightButton: mSectors.rotate(U); break;
                            case Qt::LeftButton: mSectors.rotate(U3); break;
                        }

                        break;

                    case Down:
                        switch (ev->button()) {
                            case Qt::RightButton: mSectors.rotate(D); break;
                            case Qt::LeftButton: mSectors.rotate(D3); break;
                        }

                        break;

                    case Left:
                        switch (ev->button()) {
                            case Qt::RightButton: mSectors.rotate(L); break;
                            case Qt::LeftButton: mSectors.rotate(L3); break;
                        }

                        break;

                    case Right:
                        switch (ev->button()) {
                            case Qt::RightButton: mSectors.rotate(R); break;
                            case Qt::LeftButton: mSectors.rotate(R3); break;
                        }

                        break;

                    case Forward:
                        switch (ev->button()) {
                            case Qt::RightButton: mSectors.rotate(F); break;
                            case Qt::LeftButton: mSectors.rotate(F3); break;
                        }

                        break;

                    case Back:
                        switch (ev->button()) {
                            case Qt::RightButton: mSectors.rotate(B); break;
                            case Qt::LeftButton: mSectors.rotate(B3); break;
                        }

                        break;
                }

            } else {
                switch (9 * n + 3 * row + column) {
                    case 0:
                    case 9:
                    case 38: click(ev->button(), 0, n, row, column); break;

                    case 2:
                    case 36:
                    case 29: click(ev->button(), 1, n, row, column); break;

                    case 8:
                    case 27:
                    case 20: click(ev->button(), 2, n, row, column); break;

                    case 6:
                    case 18:
                    case 11: click(ev->button(), 3, n, row, column); break;

                    case 45:
                    case 17:
                    case 24: click(ev->button(), 4, n, row, column); break;

                    case 47:
                    case 26:
                    case 33: click(ev->button(), 5, n, row, column); break;

                    case 53:
                    case 35:
                    case 42: click(ev->button(), 6, n, row, column); break;

                    case 51:
                    case 44:
                    case 15: click(ev->button(), 7, n, row, column); break;

                    case 1:
                    case 37: click(ev->button(), 8, n, row, column); break;

                    case 5:
                    case 28: click(ev->button(), 9, n, row, column); break;

                    case 7:
                    case 19: click(ev->button(), 10, n, row, column); break;

                    case 3:
                    case 10: click(ev->button(), 11, n, row, column); break;

                    case 14:
                    case 21: click(ev->button(), 12, n, row, column); break;

                    case 23:
                    case 30: click(ev->button(), 13, n, row, column); break;

                    case 32:
                    case 39: click(ev->button(), 14, n, row, column); break;

                    case 41:
                    case 12: click(ev->button(), 15, n, row, column); break;

                    case 46:
                    case 25: click(ev->button(), 16, n, row, column); break;

                    case 50:
                    case 34: click(ev->button(), 17, n, row, column); break;

                    case 52:
                    case 43: click(ev->button(), 18, n, row, column); break;

                    case 48:
                    case 16: click(ev->button(), 19, n, row, column); break;
                }
            }

            repaint();
        }
    }
}
