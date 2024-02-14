#include "hashkub.h"

#include <QFile>
#include <QMouseEvent>
#include <QPainter>

#include <iostream>

#include "ui_hashkub.h"

HashKub::HashKub(QWidget *parent) : QWidget(parent), ui(new Ui::HashKub)
{
    ui->setupUi(this);

    hashVec.resize(1);
    hashVec[0][Sectors()].resize(1);
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
        rotate(D, n, sectors, vec);
        rotate(D2, n, sectors, vec);
        rotate(D3, n, sectors, vec);

        rotate(R, n, sectors, vec);
        rotate(R2, n, sectors, vec);
        rotate(R3, n, sectors, vec);
        rotate(L, n, sectors, vec);
        rotate(L2, n, sectors, vec);
        rotate(L3, n, sectors, vec);

        rotate(F, n, sectors, vec);
        rotate(F2, n, sectors, vec);
        rotate(F3, n, sectors, vec);
        rotate(B, n, sectors, vec);
        rotate(B2, n, sectors, vec);
        rotate(B3, n, sectors, vec);
    } else {
        switch (vec.first()) {
            case U:
            case U2:
            case U3:
                rotate(R, n, sectors, vec);
                rotate(R2, n, sectors, vec);
                rotate(R3, n, sectors, vec);
                rotate(L, n, sectors, vec);
                rotate(L2, n, sectors, vec);
                rotate(L3, n, sectors, vec);

                rotate(F, n, sectors, vec);
                rotate(F2, n, sectors, vec);
                rotate(F3, n, sectors, vec);
                rotate(B, n, sectors, vec);
                rotate(B2, n, sectors, vec);
                rotate(B3, n, sectors, vec);

                break;

            case D:
            case D2:
            case D3:
                rotate(U, n, sectors, vec);
                rotate(U2, n, sectors, vec);
                rotate(U3, n, sectors, vec);

                rotate(R, n, sectors, vec);
                rotate(R2, n, sectors, vec);
                rotate(R3, n, sectors, vec);
                rotate(L, n, sectors, vec);
                rotate(L2, n, sectors, vec);
                rotate(L3, n, sectors, vec);

                rotate(F, n, sectors, vec);
                rotate(F2, n, sectors, vec);
                rotate(F3, n, sectors, vec);
                rotate(B, n, sectors, vec);
                rotate(B2, n, sectors, vec);
                rotate(B3, n, sectors, vec);

                break;

            case R:
            case R2:
            case R3:
                rotate(F, n, sectors, vec);
                rotate(F2, n, sectors, vec);
                rotate(F3, n, sectors, vec);
                rotate(B, n, sectors, vec);
                rotate(B2, n, sectors, vec);
                rotate(B3, n, sectors, vec);

                rotate(U, n, sectors, vec);
                rotate(U2, n, sectors, vec);
                rotate(U3, n, sectors, vec);
                rotate(D, n, sectors, vec);
                rotate(D2, n, sectors, vec);
                rotate(D3, n, sectors, vec);

                break;

            case L:
            case L2:
            case L3:
                rotate(R, n, sectors, vec);
                rotate(R2, n, sectors, vec);
                rotate(R3, n, sectors, vec);

                rotate(F, n, sectors, vec);
                rotate(F2, n, sectors, vec);
                rotate(F3, n, sectors, vec);
                rotate(B, n, sectors, vec);
                rotate(B2, n, sectors, vec);
                rotate(B3, n, sectors, vec);

                rotate(U, n, sectors, vec);
                rotate(U2, n, sectors, vec);
                rotate(U3, n, sectors, vec);
                rotate(D, n, sectors, vec);
                rotate(D2, n, sectors, vec);
                rotate(D3, n, sectors, vec);

                break;

            case F:
            case F2:
            case F3:
                rotate(R, n, sectors, vec);
                rotate(R2, n, sectors, vec);
                rotate(R3, n, sectors, vec);
                rotate(L, n, sectors, vec);
                rotate(L2, n, sectors, vec);
                rotate(L3, n, sectors, vec);

                rotate(U, n, sectors, vec);
                rotate(U2, n, sectors, vec);
                rotate(U3, n, sectors, vec);
                rotate(D, n, sectors, vec);
                rotate(D2, n, sectors, vec);
                rotate(D3, n, sectors, vec);

                break;

            case B:
            case B2:
            case B3:
                rotate(F, n, sectors, vec);
                rotate(F2, n, sectors, vec);
                rotate(F3, n, sectors, vec);

                rotate(R, n, sectors, vec);
                rotate(R2, n, sectors, vec);
                rotate(R3, n, sectors, vec);
                rotate(L, n, sectors, vec);
                rotate(L2, n, sectors, vec);
                rotate(L3, n, sectors, vec);

                rotate(U, n, sectors, vec);
                rotate(U2, n, sectors, vec);
                rotate(U3, n, sectors, vec);
                rotate(D, n, sectors, vec);
                rotate(D2, n, sectors, vec);
                rotate(D3, n, sectors, vec);

                break;
        }
    }
}

void HashKub::rotate(int r, int n, Sectors sectors, QVector<int> vec)
{
    sectors.rotate(r);

    for (int i = 0; i < n; ++i) {
        if (hashVec[i].contains(sectors)) {
            return;
        }
    }

    vec.push_front(r);
    hashVec[n][sectors].append(vec);
}

void HashKub::on_downloadBtn_clicked()
{
    int sizeOld = hashVec.size();
    hashVec.resize(ui->spinBox->value() + 1);

    for (int i = sizeOld; i <= ui->spinBox->value(); ++i) {
        for (auto &key : hashVec[i - 1].keys()) {
            for (auto &vec : hashVec[i - 1].value(key)) {
                rotates(i, key, vec);
            }
        }
    }

    std::cout << "done" << std::endl;
}

void HashKub::save()
{
    for (int i = 0; i <= ui->spinBox->value(); ++i) {
        QFile file(QString("save%1.txt").arg(i));
        file.open(QFile::WriteOnly);

        for (auto &key : hashVec[i].keys()) {
            file.write(key.toString().toUtf8());
            file.write(", ");

            for (auto &vec : hashVec[i].value(key)) {
                for (auto &el : vec) {
                    file.write(QString("%1 ").arg(el).toUtf8());
                }

                file.write(", ");
            }

            file.write("\n");
        }

        file.close();
    }

    std::cout << "files save" << std::endl;
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

void HashKub::read()
{
    for (int i = 0; i <= ui->spinBox->value(); ++i) {
        QFile file(QString("save%1.txt").arg(i));
        file.open(QFile::ReadOnly);

        while (!file.atEnd()) {
            QString str = QString::fromUtf8(file.readLine());
            str.resize(str.size() - 1);
            QStringList list = str.split(", ");
            auto key = Sectors::fromString(list.takeFirst());
            list.removeLast();

            for (int j = 0; j < list.size(); ++j) {
                hashVec[i][key].append(QVector<int>());
                auto split = list[j].split(" ");
                split.removeLast();

                for (auto &str : split) {
                    hashVec[i][key][j].append(str.toInt());
                }
            }
        }

        file.close();
    }
}

void HashKub::findSolution()
{
    for (int i = 0; i <= ui->spinBox->value(); ++i) {
        if (hashVec[i].contains(mSectors)) {
            for (auto &vec : hashVec[i][mSectors]) {
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
            }

            return;
        }
    }

    for (int arrIndex = 1; arrIndex <= ui->spinBox->value(); ++arrIndex) {
        bool flag = false;

        for (auto it1 = hashVec[arrIndex].begin(); it1 != hashVec[arrIndex].end(); ++it1) {
            Sectors sec = mSectors;
            int arr[54];
            int n = 0;
            for (int index = 0; index < 6; ++index) {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        arr[it1.key().matrics[index][i][j]] = sec.matrics[index][i][j];
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

            if (hashVec[ui->spinBox->value()].contains(sec)) {
                flag = true;
                for (auto &vecHash : hashVec[ui->spinBox->value()][sec]) {
                    for (auto &vec : it1.value()) {
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

            if (row != 3 && column != 3) {
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
                    switch (ev->button()) {
                        case Qt::LeftButton:
                            if (mSelectSector) {
                                std::swap(*mSelectSector, mSectors.matrics[n][row][column]);
                                mSelectSector = nullptr;
                            } else {
                                mSelectSector = &mSectors.matrics[n][row][column];
                            }

                            break;
                    }
                }

                repaint();
            }
        }
    }
}
