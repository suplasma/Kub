#include "sectors.h"

#include <QDebug>
#include <QStringList>
#include <QVector>

Sectors::Sectors()
{
    int col = -1;
    for (int index = 0; index < 6; ++index) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                matrics[index][i][j] = ++col;
            }
        }
    }
}

Sectors::Sectors(const Sectors &sec)
{
    for (int index = 0; index < 6; ++index) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                matrics[index][i][j] = sec.matrics[index][i][j];
            }
        }
    }
}

Sectors::Sectors(const QVector<int> &vec)
{
    for (int i = 0; i < 8; ++i) {
        setAngle(i, vec.value(i));
    }

    for (int i = 0; i < 12; ++i) {
        setArris(i, vec.value(i + 8));
    }

    matrics[0][1][1] = 4;
    matrics[1][1][1] = 13;
    matrics[2][1][1] = 22;
    matrics[3][1][1] = 31;
    matrics[4][1][1] = 40;
    matrics[5][1][1] = 49;
}

bool operator==(const Sectors &s1, const Sectors &s2)
{
    for (int i1 = 0; i1 < 6; ++i1) {
        for (int i2 = 0; i2 < 3; ++i2) {
            for (int i3 = 0; i3 < 3; ++i3) {
                if (s1.matrics[i1][i2][i3] != s2.matrics[i1][i2][i3]) {
                    return false;
                }
            }
        }
    }

    return true;
}

uint qHash(const Sectors &s)
{
    uint res = 0;

    for (int i1 = 0; i1 < 6; ++i1) {
        for (int i2 = 0; i2 < 3; ++i2) {
            for (int i3 = 0; i3 < 3; ++i3) {
                res *= 31;
                res += s.matrics[i1][i2][i3];
            }
        }
    }

    return res;
}

QString Sectors::toString() const
{
    QString res;

    for (int i1 = 0; i1 < 6; ++i1) {
        for (int i2 = 0; i2 < 3; ++i2) {
            for (int i3 = 0; i3 < 3; ++i3) {
                res += QString::number(matrics[i1][i2][i3]) + " ";
            }
        }
    }

    return res;
}

Sectors Sectors::fromString(const QString &str)
{
    Sectors sec;
    int index = 0;
    auto split = str.split(" ");

    for (int i1 = 0; i1 < 6; ++i1) {
        for (int i2 = 0; i2 < 3; ++i2) {
            for (int i3 = 0; i3 < 3; ++i3) {
                sec.matrics[i1][i2][i3] = split[index].toInt();
                ++index;
            }
        }
    }

    return sec;
}

void Sectors::rotate(int n)
{
    switch (n) {
        case U:
            currentRotate(Up);

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                               matrics[4][0][i]);
            }

            break;

        case U2:
            currentDoubleRotate(Up);

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                                     matrics[4][0][i]);
            }

            break;

        case U3:
            currentReversRotate(Up);

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                                     matrics[4][0][i]);
            }

            break;

        case D:
            currentRotate(Down);

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                               matrics[2][2][i]);
            }

            break;

        case D2:
            currentDoubleRotate(Down);

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                                     matrics[2][2][i]);
            }

            break;

        case D3:
            currentReversRotate(Down);

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                                     matrics[2][2][i]);
            }

            break;

        case E:
            currentRotate(Up);
            currentReversRotate(Down);

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                               matrics[4][0][i]);
            }

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                                     matrics[2][2][i]);
            }

            break;

        case E2:
            currentDoubleRotate(Up);
            currentDoubleRotate(Down);

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                                     matrics[4][0][i]);
            }

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                                     matrics[2][2][i]);
            }

            break;

        case E3:
            currentReversRotate(Up);
            currentRotate(Down);

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                                     matrics[4][0][i]);
            }

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                               matrics[2][2][i]);
            }

            break;

        case R:
            currentRotate(Right);

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[0][2 - i][2], matrics[2][2 - i][2], matrics[5][2 - i][2],
                               matrics[4][i][0]);
            }

            break;

        case R2:
            currentDoubleRotate(Right);

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[0][2 - i][2], matrics[2][2 - i][2],
                                     matrics[5][2 - i][2], matrics[4][i][0]);
            }

            break;

        case R3:
            currentReversRotate(Right);

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[0][2 - i][2], matrics[2][2 - i][2],
                                     matrics[5][2 - i][2], matrics[4][i][0]);
            }

            break;

        case L:
            currentRotate(Left);

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                               matrics[2][i][0]);
            }

            break;

        case L2:
            currentDoubleRotate(Left);

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                                     matrics[2][i][0]);
            }

            break;

        case L3:
            currentReversRotate(Left);

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                                     matrics[2][i][0]);
            }

            break;

        case M:
            currentRotate(Right);
            currentReversRotate(Left);

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[0][2 - i][2], matrics[2][2 - i][2], matrics[5][2 - i][2],
                               matrics[4][i][0]);
            }

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                                     matrics[2][i][0]);
            }

            break;

        case M2:
            currentDoubleRotate(Right);
            currentDoubleRotate(Left);

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[0][2 - i][2], matrics[2][2 - i][2],
                                     matrics[5][2 - i][2], matrics[4][i][0]);
            }

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                                     matrics[2][i][0]);
            }

            break;

        case M3:
            currentReversRotate(Right);
            currentRotate(Left);

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[0][2 - i][2], matrics[2][2 - i][2],
                                     matrics[5][2 - i][2], matrics[4][i][0]);
            }

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                               matrics[2][i][0]);
            }

            break;

        case F:
            currentRotate(Forward);

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[0][2][i], matrics[1][2 - i][2], matrics[5][0][2 - i],
                               matrics[3][i][0]);
            }

            break;

        case F2:
            currentDoubleRotate(Forward);

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[0][2][i], matrics[1][2 - i][2],
                                     matrics[5][0][2 - i], matrics[3][i][0]);
            }

            break;

        case F3:
            currentReversRotate(Forward);

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[0][2][i], matrics[1][2 - i][2],
                                     matrics[5][0][2 - i], matrics[3][i][0]);
            }

            break;

        case B:
            currentRotate(Back);

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[0][0][2 - i], matrics[3][2 - i][2], matrics[5][2][i],
                               matrics[1][i][0]);
            }

            break;

        case B2:
            currentDoubleRotate(Back);

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[0][0][2 - i], matrics[3][2 - i][2],
                                     matrics[5][2][i], matrics[1][i][0]);
            }

            break;

        case B3:
            currentReversRotate(Back);

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[0][0][2 - i], matrics[3][2 - i][2],
                                     matrics[5][2][i], matrics[1][i][0]);
            }

            break;

        case S:
            currentRotate(Forward);
            currentReversRotate(Back);

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[0][2][i], matrics[1][2 - i][2], matrics[5][0][2 - i],
                               matrics[3][i][0]);
            }

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[0][0][2 - i], matrics[3][2 - i][2],
                                     matrics[5][2][i], matrics[1][i][0]);
            }

            break;

        case S2:
            currentDoubleRotate(Forward);
            currentDoubleRotate(Back);

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[0][2][i], matrics[1][2 - i][2],
                                     matrics[5][0][2 - i], matrics[3][i][0]);
            }

            for (int i = 0; i < 3; ++i) {
                adjacentDoubleRotate(matrics[0][0][2 - i], matrics[3][2 - i][2],
                                     matrics[5][2][i], matrics[1][i][0]);
            }

            break;

        case S3:
            currentReversRotate(Forward);
            currentRotate(Back);

            for (int i = 0; i < 3; ++i) {
                adjacentReversRotate(matrics[0][2][i], matrics[1][2 - i][2],
                                     matrics[5][0][2 - i], matrics[3][i][0]);
            }

            for (int i = 0; i < 3; ++i) {
                adjacentRotate(matrics[0][0][2 - i], matrics[3][2 - i][2], matrics[5][2][i],
                               matrics[1][i][0]);
            }

            break;
    }
}

QVector<int> Sectors::toVec() const
{
    QVector<int> vec;

    vec.append(numAngle(matrics[0][0][0]));
    vec.append(numAngle(matrics[0][0][2]));
    vec.append(numAngle(matrics[0][2][2]));
    vec.append(numAngle(matrics[0][2][0]));
    vec.append(numAngle(matrics[5][0][0]));
    vec.append(numAngle(matrics[5][0][2]));
    vec.append(numAngle(matrics[5][2][2]));
    vec.append(numAngle(matrics[5][2][0]));

    vec.append(numArris(matrics[0][0][1]));
    vec.append(numArris(matrics[0][1][2]));
    vec.append(numArris(matrics[0][2][1]));
    vec.append(numArris(matrics[0][1][0]));
    vec.append(numArris(matrics[1][1][2]));
    vec.append(numArris(matrics[2][1][2]));
    vec.append(numArris(matrics[3][1][2]));
    vec.append(numArris(matrics[4][1][2]));
    vec.append(numArris(matrics[5][0][1]));
    vec.append(numArris(matrics[5][1][2]));
    vec.append(numArris(matrics[5][2][1]));
    vec.append(numArris(matrics[5][1][0]));

    return vec;
}

int Sectors::numAngle(int num) const
{
    switch (num) {
        case 0: return 0;
        case 9: return 1;
        case 38: return 2;

        case 2: return 3;
        case 36: return 4;
        case 29: return 5;

        case 8: return 6;
        case 27: return 7;
        case 20: return 8;

        case 6: return 9;
        case 18: return 10;
        case 11: return 11;

        case 45: return 12;
        case 17: return 13;
        case 24: return 14;

        case 47: return 15;
        case 26: return 16;
        case 33: return 17;

        case 53: return 18;
        case 35: return 19;
        case 42: return 20;

        case 51: return 21;
        case 44: return 22;
        case 15: return 23;
    }

    qDebug() << Q_FUNC_INFO << num;

    throw 1;
}

int Sectors::numArris(int num) const
{
    switch (num) {
        case 1: return 0;
        case 37: return 1;

        case 5: return 2;
        case 28: return 3;

        case 7: return 4;
        case 19: return 5;

        case 3: return 6;
        case 10: return 7;

        case 14: return 8;
        case 21: return 9;

        case 23: return 10;
        case 30: return 11;

        case 32: return 12;
        case 39: return 13;

        case 41: return 14;
        case 12: return 15;

        case 46: return 16;
        case 25: return 17;

        case 50: return 18;
        case 34: return 19;

        case 52: return 20;
        case 43: return 21;

        case 48: return 22;
        case 16: return 23;
    }

    qDebug() << Q_FUNC_INFO << num;

    throw 1;
}

void Sectors::setAngle(int ang, int res)
{
    switch (ang) {
        case 0:
            matrics[0][0][0] = angle(res);
            matrics[1][0][0] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[4][0][2] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 1:
            matrics[0][0][2] = angle(res);
            matrics[4][0][0] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[3][0][2] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 2:
            matrics[0][2][2] = angle(res);
            matrics[3][0][0] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[2][0][2] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 3:
            matrics[0][2][0] = angle(res);
            matrics[2][0][0] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[1][0][2] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 4:
            matrics[5][0][0] = angle(res);
            matrics[1][2][2] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[2][2][0] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 5:
            matrics[5][0][2] = angle(res);
            matrics[2][2][2] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[3][2][0] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 6:
            matrics[5][2][2] = angle(res);
            matrics[3][2][2] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[4][2][0] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 7:
            matrics[5][2][0] = angle(res);
            matrics[4][2][2] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[1][2][0] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        default: qDebug() << Q_FUNC_INFO << ang; throw 1;
    }
}

int Sectors::angle(int angle)
{
    switch (angle) {
        case 0: return 0;
        case 1: return 9;
        case 2: return 38;

        case 3: return 2;
        case 4: return 36;
        case 5: return 29;

        case 6: return 8;
        case 7: return 27;
        case 8: return 20;

        case 9: return 6;
        case 10: return 18;
        case 11: return 11;

        case 12: return 45;
        case 13: return 17;
        case 14: return 24;

        case 15: return 47;
        case 16: return 26;
        case 17: return 33;

        case 18: return 53;
        case 19: return 35;
        case 20: return 42;

        case 21: return 51;
        case 22: return 44;
        case 23: return 15;
    }

    qDebug() << Q_FUNC_INFO << angle;
    throw 1;
}

void Sectors::setArris(int arr, int res)
{
    switch (arr) {
        case 0:
            matrics[0][0][1] = arris(res);
            matrics[4][0][1] = arris(res ^ 1);

            break;

        case 1:
            matrics[0][1][2] = arris(res);
            matrics[3][0][1] = arris(res ^ 1);

            break;

        case 2:
            matrics[0][2][1] = arris(res);
            matrics[2][0][1] = arris(res ^ 1);

            break;

        case 3:
            matrics[0][1][0] = arris(res);
            matrics[1][0][1] = arris(res ^ 1);

            break;

        case 4:
            matrics[1][1][2] = arris(res);
            matrics[2][1][0] = arris(res ^ 1);

            break;

        case 5:
            matrics[2][1][2] = arris(res);
            matrics[3][1][0] = arris(res ^ 1);

            break;

        case 6:
            matrics[3][1][2] = arris(res);
            matrics[4][1][0] = arris(res ^ 1);

            break;

        case 7:
            matrics[4][1][2] = arris(res);
            matrics[1][1][0] = arris(res ^ 1);

            break;

        case 8:
            matrics[5][0][1] = arris(res);
            matrics[2][2][1] = arris(res ^ 1);

            break;

        case 9:
            matrics[5][1][2] = arris(res);
            matrics[3][2][1] = arris(res ^ 1);

            break;

        case 10:
            matrics[5][2][1] = arris(res);
            matrics[4][2][1] = arris(res ^ 1);

            break;

        case 11:
            matrics[5][1][0] = arris(res);
            matrics[1][2][1] = arris(res ^ 1);

            break;

        default: qDebug() << Q_FUNC_INFO << arr; throw 1;
    }
}

int Sectors::arris(int arris)
{
    switch (arris) {
        case 0: return 1;
        case 1: return 37;

        case 2: return 5;
        case 3: return 28;

        case 4: return 7;
        case 5: return 19;

        case 6: return 3;
        case 7: return 10;

        case 8: return 14;
        case 9: return 21;

        case 10: return 23;
        case 11: return 30;

        case 12: return 32;
        case 13: return 39;

        case 14: return 41;
        case 15: return 12;

        case 16: return 46;
        case 17: return 25;

        case 18: return 50;
        case 19: return 34;

        case 20: return 52;
        case 21: return 43;

        case 22: return 48;
        case 23: return 16;
    }

    qDebug() << Q_FUNC_INFO << arris;
    throw 1;
}

void Sectors::currentRotate(int n)
{
    adjacentRotate(matrics[n][0][0], matrics[n][2][0], matrics[n][2][2], matrics[n][0][2]);
    adjacentRotate(matrics[n][0][1], matrics[n][1][0], matrics[n][2][1], matrics[n][1][2]);
}

void Sectors::currentDoubleRotate(int n)
{
    adjacentDoubleRotate(matrics[n][0][0], matrics[n][2][0], matrics[n][2][2],
                         matrics[n][0][2]);
    adjacentDoubleRotate(matrics[n][0][1], matrics[n][1][0], matrics[n][2][1],
                         matrics[n][1][2]);
}

void Sectors::currentReversRotate(int n)
{
    adjacentReversRotate(matrics[n][0][0], matrics[n][2][0], matrics[n][2][2],
                         matrics[n][0][2]);
    adjacentReversRotate(matrics[n][0][1], matrics[n][1][0], matrics[n][2][1],
                         matrics[n][1][2]);
}

void Sectors::adjacentRotate(int &n1, int &n2, int &n3, int &n4)
{
    std::swap(n1, n2);
    std::swap(n3, n4);
    std::swap(n1, n3);
}

void Sectors::adjacentDoubleRotate(int &n1, int &n2, int &n3, int &n4)
{
    std::swap(n1, n3);
    std::swap(n2, n4);
}

void Sectors::adjacentReversRotate(int &n1, int &n2, int &n3, int &n4)
{
    std::swap(n1, n2);
    std::swap(n3, n4);
    std::swap(n2, n4);
}
