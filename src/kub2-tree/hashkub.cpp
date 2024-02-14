#include "hashkub.h"

#include <QFile>
#include <QMouseEvent>
#include <QPainter>

#include <iostream>

#include "ui_hashkub.h"

HashKub::HashKub(QWidget *parent) : QWidget(parent), ui(new Ui::HashKub)
{
    ui->setupUi(this);
    Sectors sec;
    tree.append(sec, QVector<uint8_t>());
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

        rotate(R, sectors, vec);
        rotate(R2, sectors, vec);
        rotate(R3, sectors, vec);

        rotate(F, sectors, vec);
        rotate(F2, sectors, vec);
        rotate(F3, sectors, vec);
    } else {
        switch (vec.first()) {
            case U:
            case U2:
            case U3:
                rotate(R, sectors, vec);
                rotate(R2, sectors, vec);
                rotate(R3, sectors, vec);

                rotate(F, sectors, vec);
                rotate(F2, sectors, vec);
                rotate(F3, sectors, vec);

                break;

            case R:
            case R2:
            case R3:
                rotate(F, sectors, vec);
                rotate(F2, sectors, vec);
                rotate(F3, sectors, vec);

                rotate(U, sectors, vec);
                rotate(U2, sectors, vec);
                rotate(U3, sectors, vec);

                break;

            case F:
            case F2:
            case F3:
                rotate(R, sectors, vec);
                rotate(R2, sectors, vec);
                rotate(R3, sectors, vec);

                rotate(U, sectors, vec);
                rotate(U2, sectors, vec);
                rotate(U3, sectors, vec);

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
    for (; size < static_cast<uint>(ui->spinBox->value()); ++size) {
        for (auto &key : tree.keys(size)) {
            for (const auto &vec : tree.valueAll(key)) {
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
    mSelectAngle = -1;
    mValSelectAngle = -1;
    mMovebleAngle.clear();
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
    for (const auto &vec : tree.value(mSectors, mMovebleAngle)) {
        QString res;

        for (const auto &el : vec) {
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
}

void HashKub::click(Qt::MouseButton button, Qt::KeyboardModifiers mod, int num, int n, int row,
                    int column)
{
    switch (button) {
        case Qt::LeftButton:
            if (mSelectAngle != -1) {
                auto vec = mSectors.toVec();
                std::swap(vec[mSelectAngle], vec[num]);

                if (mMovebleAngle.contains(num)) {
                    if (!mMovebleAngle.contains(mSelectAngle)) {
                        mMovebleAngle.removeOne(num);
                        mMovebleAngle.append(mSelectAngle);
                    }
                } else if (mMovebleAngle.contains(mSelectAngle)) {
                    mMovebleAngle.removeOne(mSelectAngle);
                    mMovebleAngle.append(num);
                }

                mSectors = Sectors(vec);
                mSelectAngle = -1;
                mValSelectAngle = -1;
            } else {
                mSelectAngle = num;
                mValSelectAngle = mSectors.matrics[n][row][column];
            }

            break;

        case Qt::RightButton:
            switch (mod) {
                case Qt::NoModifier: {
                    auto vec = mSectors.toVec();
                    auto &res = vec[num];
                    res += ((res + 1) % 3) - (res % 3);
                    mSectors = Sectors(vec);

                    break;
                }

                case Qt::ControlModifier: {
                    auto vec = mSectors.toVec();
                    vec[num] = -3;
                    mSectors = Sectors(vec);

                    break;
                }

                case Qt::ShiftModifier: {
                    if (mMovebleAngle.contains(num)) {
                        mMovebleAngle.removeOne(num);
                    } else {
                        mMovebleAngle.append(num);
                    }

                    break;
                }
            }

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
                if (mMovebleAngle.contains(mSectors.numAngle((index << 2) + (i << 1) + j) /
                                           3)) {
                    painter.setBrush(QBrush(Qt::gray));
                } else
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
                        default: painter.setBrush(QBrush(Qt::gray));
                    }

                if (mSectors.matrics[index][i][j] == mValSelectAngle) {
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

                int n = mSectors.matrics[index][i][j];

                if (n >= 0) {
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

        auto font = painter.font();
        font.setPixelSize(16);
        painter.setFont(font);

        painter.drawText(QRectF(SIZE_SECTION + SHIFT +
                                    column(index) * (COUNT_SECTION * SIZE_SECTION + APERTURE),
                                SIZE_SECTION + SHIFT +
                                    row(index) * (COUNT_SECTION * SIZE_SECTION + APERTURE) +
                                    200,
                                SIZE_SECTION, SIZE_SECTION),
                         names[index], QTextOption(Qt::AlignCenter));
    }
}

void HashKub::mousePressEvent(QMouseEvent *ev)
{
    if (ev->x() >= SHIFT && ev->y() >= SHIFT) {
        int n = index((ev->y() - SHIFT) / (COUNT_SECTION * SIZE_SECTION + APERTURE),
                      (ev->x() - SHIFT) / (COUNT_SECTION * SIZE_SECTION + APERTURE));
        int x = ev->x() - (SHIFT + column(n) * (COUNT_SECTION * SIZE_SECTION + APERTURE));
        int y = ev->y() - (SHIFT + row(n) * (COUNT_SECTION * SIZE_SECTION + APERTURE));
        int row = y / SIZE_SECTION;
        int column = x / SIZE_SECTION;

        if (n != -1) {
            switch ((n << 2) + (row << 1) + column) {
                case 0:
                case 4:
                case 17: click(ev->button(), ev->modifiers(), 0, n, row, column); break;

                case 1:
                case 16:
                case 13: click(ev->button(), ev->modifiers(), 1, n, row, column); break;

                case 3:
                case 12:
                case 9: click(ev->button(), ev->modifiers(), 2, n, row, column); break;

                case 2:
                case 8:
                case 5: click(ev->button(), ev->modifiers(), 3, n, row, column); break;

                case 20:
                case 7:
                case 10: click(ev->button(), ev->modifiers(), 4, n, row, column); break;

                case 21:
                case 11:
                case 14: click(ev->button(), ev->modifiers(), 5, n, row, column); break;

                case 23:
                case 15:
                case 18: click(ev->button(), ev->modifiers(), 6, n, row, column); break;
            }
        } else {
            if (ev->x() >= SHIFT && ev->y() >= SHIFT + 200) {
                int but =
                    index((ev->y() - 200 - SHIFT) / (COUNT_SECTION * SIZE_SECTION + APERTURE),
                          (ev->x() - SHIFT) / (COUNT_SECTION * SIZE_SECTION + APERTURE));

                const auto &vecOld = mSectors.toVec();

                switch (ev->button()) {
                    case Qt::LeftButton:
                        switch (but) {
                            case Up: mSectors.rotate(U3); break;
                            case Forward: mSectors.rotate(F3); break;
                            case Right: mSectors.rotate(R3); break;
                        }

                        break;

                    case Qt::RightButton:
                        switch (but) {
                            case Up: mSectors.rotate(U); break;
                            case Forward: mSectors.rotate(F); break;
                            case Right: mSectors.rotate(R); break;
                        }

                        break;
                }

                const auto &vec = mSectors.toVec();

                for (auto &el : mMovebleAngle) {
                    for (int i = 0; i < vec.size(); ++i) {
                        if ((vec[i] / 3) == (vecOld[el] / 3)) {
                            el = i;

                            break;
                        }
                    }
                }
            }
        }

        repaint();
    }
}
