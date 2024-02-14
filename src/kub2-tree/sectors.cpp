#include "sectors.h"

#include <QDebug>
#include <QStringList>
#include <QVector>

Sectors::Sectors()
{
    int col = -1;
    for (int index = 0; index < 6; ++index) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                matrics[index][i][j] = ++col;
            }
        }
    }
}

Sectors::Sectors(const Sectors &sec)
{
    for (int index = 0; index < 6; ++index) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                matrics[index][i][j] = sec.matrics[index][i][j];
            }
        }
    }
}

Sectors::Sectors(const QVector<int> &vec)
{
    for (int i = 0; i < 7; ++i) {
        setAngle(i, vec.value(i));
    }

    matrics[5][1][0] = 22;
    matrics[4][1][1] = 19;
    matrics[1][1][0] = 6;
}

bool operator==(const Sectors &s1, const Sectors &s2)
{
    for (int i1 = 0; i1 < 6; ++i1) {
        for (int i2 = 0; i2 < 2; ++i2) {
            for (int i3 = 0; i3 < 2; ++i3) {
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
        for (int i2 = 0; i2 < 2; ++i2) {
            for (int i3 = 0; i3 < 2; ++i3) {
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
        for (int i2 = 0; i2 < 2; ++i2) {
            for (int i3 = 0; i3 < 2; ++i3) {
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
    const auto &split = str.split(" ");

    for (int i1 = 0; i1 < 6; ++i1) {
        for (int i2 = 0; i2 < 2; ++i2) {
            for (int i3 = 0; i3 < 2; ++i3) {
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

            for (int i = 0; i < 2; ++i) {
                adjacentRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                               matrics[4][0][i]);
            }

            break;

        case U2:
            currentDoubleRotate(Up);

            for (int i = 0; i < 2; ++i) {
                adjacentDoubleRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                                     matrics[4][0][i]);
            }

            break;

        case U3:
            currentReversRotate(Up);

            for (int i = 0; i < 2; ++i) {
                adjacentReversRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                                     matrics[4][0][i]);
            }

            break;

        case R:
            currentRotate(Right);

            for (int i = 0; i < 2; ++i) {
                adjacentRotate(matrics[0][1 - i][1], matrics[2][1 - i][1], matrics[5][1 - i][1],
                               matrics[4][i][0]);
            }

            break;

        case R2:
            currentDoubleRotate(Right);

            for (int i = 0; i < 2; ++i) {
                adjacentDoubleRotate(matrics[0][1 - i][1], matrics[2][1 - i][1],
                                     matrics[5][1 - i][1], matrics[4][i][0]);
            }

            break;

        case R3:
            currentReversRotate(Right);

            for (int i = 0; i < 2; ++i) {
                adjacentReversRotate(matrics[0][1 - i][1], matrics[2][1 - i][1],
                                     matrics[5][1 - i][1], matrics[4][i][0]);
            }

            break;

        case F:
            currentRotate(Forward);

            for (int i = 0; i < 2; ++i) {
                adjacentRotate(matrics[0][1][i], matrics[1][1 - i][1], matrics[5][0][1 - i],
                               matrics[3][i][0]);
            }

            break;

        case F2:
            currentDoubleRotate(Forward);

            for (int i = 0; i < 2; ++i) {
                adjacentDoubleRotate(matrics[0][1][i], matrics[1][1 - i][1],
                                     matrics[5][0][1 - i], matrics[3][i][0]);
            }

            break;

        case F3:
            currentReversRotate(Forward);

            for (int i = 0; i < 2; ++i) {
                adjacentReversRotate(matrics[0][1][i], matrics[1][1 - i][1],
                                     matrics[5][0][1 - i], matrics[3][i][0]);
            }

            break;
    }
}

QVector<int> Sectors::toVec() const
{
    QVector<int> vec;

    vec.append(numAngle(matrics[0][0][0]));
    vec.append(numAngle(matrics[0][0][1]));
    vec.append(numAngle(matrics[0][1][1]));
    vec.append(numAngle(matrics[0][1][0]));
    vec.append(numAngle(matrics[5][0][0]));
    vec.append(numAngle(matrics[5][0][1]));
    vec.append(numAngle(matrics[5][1][1]));

    return vec;
}

int Sectors::numAngle(int num) const
{
    switch (num) {
        case 0: return 0;
        case 4: return 1;
        case 17: return 2;

        case 1: return 3;
        case 16: return 4;
        case 13: return 5;

        case 3: return 6;
        case 12: return 7;
        case 9: return 8;

        case 2: return 9;
        case 8: return 10;
        case 5: return 11;

        case 20: return 12;
        case 7: return 13;
        case 10: return 14;

        case 21: return 15;
        case 11: return 16;
        case 14: return 17;

        case 23: return 18;
        case 15: return 19;
        case 18: return 20;
    }

    return -3;
}

void Sectors::setAngle(int ang, int res)
{
    switch (ang) {
        case 0:
            matrics[0][0][0] = angle(res);
            matrics[1][0][0] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[4][0][1] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 1:
            matrics[0][0][1] = angle(res);
            matrics[4][0][0] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[3][0][1] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 2:
            matrics[0][1][1] = angle(res);
            matrics[3][0][0] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[2][0][1] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 3:
            matrics[0][1][0] = angle(res);
            matrics[2][0][0] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[1][0][1] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 4:
            matrics[5][0][0] = angle(res);
            matrics[1][1][1] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[2][1][0] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 5:
            matrics[5][0][1] = angle(res);
            matrics[2][1][1] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[3][1][0] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        case 6:
            matrics[5][1][1] = angle(res);
            matrics[3][1][1] = angle(res - (res % 3) + ((res + 1) % 3));
            matrics[4][1][0] = angle(res - (res % 3) + ((res + 2) % 3));

            break;

        default: qDebug() << Q_FUNC_INFO << ang; throw 1;
    }
}

int Sectors::angle(int angle)
{
    switch (angle) {
        case 0: return 0;
        case 1: return 4;
        case 2: return 17;

        case 3: return 1;
        case 4: return 16;
        case 5: return 13;

        case 6: return 3;
        case 7: return 12;
        case 8: return 9;

        case 9: return 2;
        case 10: return 8;
        case 11: return 5;

        case 12: return 20;
        case 13: return 7;
        case 14: return 10;

        case 15: return 21;
        case 16: return 11;
        case 17: return 14;

        case 18: return 23;
        case 19: return 15;
        case 20: return 18;
    }

    return -3;
}

void Sectors::currentRotate(int n)
{
    adjacentRotate(matrics[n][0][0], matrics[n][1][0], matrics[n][1][1], matrics[n][0][1]);
}

void Sectors::currentDoubleRotate(int n)
{
    adjacentDoubleRotate(matrics[n][0][0], matrics[n][1][0], matrics[n][1][1],
                         matrics[n][0][1]);
}

void Sectors::currentReversRotate(int n)
{
    adjacentReversRotate(matrics[n][0][0], matrics[n][1][0], matrics[n][1][1],
                         matrics[n][0][1]);
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
