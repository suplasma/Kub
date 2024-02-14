#include "kubthread.h"

#include <iostream>

KubThread::KubThread(int mat[][COUNT_SECTION][COUNT_SECTION], int n, int count, int countRotate,
                     int lastRotate) :
    count(count),
    countRotate(countRotate), lastRotate(lastRotate)
{
    for (int index = 0; index < 6; ++index) {
        for (int i = 0; i < KubThread::COUNT_SECTION; ++i) {
            for (int j = 0; j < KubThread::COUNT_SECTION; ++j) {
                matrics[index][i][j] = mat[index][i][j];
            }
        }
    }

    rotateFirst(n);

    findRotates();
}

void KubThread::rotateFirst(int n)
{
    rotateArr[0] = n;

    switch (n) {
        case U:
            currentRotate(Up);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                               matrics[4][0][i]);
            }

            break;

        case U2:
            currentDoubleRotate(Up);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentDoubleRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                                     matrics[4][0][i]);
            }

            break;

        case U3:
            currentReversRotate(Up);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentReversRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                                     matrics[4][0][i]);
            }

            break;

        case R:
            currentRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][1 - i][1], matrics[2][1 - i][1], matrics[5][1 - i][1],
                               matrics[4][i][0]);
            }

            break;

        case R2:
            currentDoubleRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentDoubleRotate(matrics[0][1 - i][1], matrics[2][1 - i][1],
                                     matrics[5][1 - i][1], matrics[4][i][0]);
            }

            break;

        case R3:
            currentReversRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentReversRotate(matrics[0][1 - i][1], matrics[2][1 - i][1],
                                     matrics[5][1 - i][1], matrics[4][i][0]);
            }

            break;

        case F:
            currentRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][1][i], matrics[1][1 - i][1], matrics[5][0][1 - i],
                               matrics[3][i][0]);
            }

            break;

        case F2:
            currentDoubleRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentDoubleRotate(matrics[0][1][i], matrics[1][1 - i][1],
                                     matrics[5][0][1 - i], matrics[3][i][0]);
            }

            break;

        case F3:
            currentReversRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentReversRotate(matrics[0][1][i], matrics[1][1 - i][1],
                                     matrics[5][0][1 - i], matrics[3][i][0]);
            }

            break;
    }
}

void KubThread::rotateLast(int n)
{
    switch (rotateArr[n]) {
        case None:
            switch (rotateArr[n - 1]) {
                case U:
                case U2:
                case U3:
                    rotateArr[n] = R;
                    currentRotate(Right);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[0][1 - i][1], matrics[2][1 - i][1],
                                       matrics[5][1 - i][1], matrics[4][i][0]);
                    }

                    break;

                default: {
                    rotateArr[n] = U;
                    currentRotate(Up);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                                       matrics[4][0][i]);
                    }
                }
            }

            break;

        case U:
            rotateArr[n] = U2;
            currentRotate(Up);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                               matrics[4][0][i]);
            }

            break;

        case U2:
            rotateArr[n] = U3;
            currentRotate(Up);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                               matrics[4][0][i]);
            }

            break;

        case U3:
            currentRotate(Up);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                               matrics[4][0][i]);
            }

            switch (rotateArr[n - 1]) {
                case R:
                case R2:
                case R3:
                    rotateArr[n] = F;
                    currentRotate(Forward);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[0][1][i], matrics[1][1 - i][1],
                                       matrics[5][0][1 - i], matrics[3][i][0]);
                    }

                    break;

                default: {
                    rotateArr[n] = R;
                    currentRotate(Right);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[0][1 - i][1], matrics[2][1 - i][1],
                                       matrics[5][1 - i][1], matrics[4][i][0]);
                    }
                }
            }

            break;

        case R:
            rotateArr[n] = R2;
            currentRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][1 - i][1], matrics[2][1 - i][1], matrics[5][1 - i][1],
                               matrics[4][i][0]);
            }

            break;

        case R2:
            rotateArr[n] = R3;
            currentRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][1 - i][1], matrics[2][1 - i][1], matrics[5][1 - i][1],
                               matrics[4][i][0]);
            }

            break;

        case R3:
            currentRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][1 - i][1], matrics[2][1 - i][1], matrics[5][1 - i][1],
                               matrics[4][i][0]);
            }

            switch (rotateArr[n - 1]) {
                case F:
                case F2:
                case F3: rotateArr[n] = None; break;

                default: {
                    rotateArr[n] = F;
                    currentRotate(Forward);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[0][1][i], matrics[1][1 - i][1],
                                       matrics[5][0][1 - i], matrics[3][i][0]);
                    }
                }
            }

            break;

        case F:
            rotateArr[n] = F2;
            currentRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][1][i], matrics[1][1 - i][1], matrics[5][0][1 - i],
                               matrics[3][i][0]);
            }

            break;

        case F2:
            rotateArr[n] = F3;
            currentRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][1][i], matrics[1][1 - i][1], matrics[5][0][1 - i],
                               matrics[3][i][0]);
            }

            break;

        case F3:
            rotateArr[n] = None;
            currentRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][1][i], matrics[1][1 - i][1], matrics[5][0][1 - i],
                               matrics[3][i][0]);
            }

            break;
    }
}

void KubThread::check() const
{
    for (int i = 0; i < COUNT_SECTION; ++i) {
        for (int j = 0; j < COUNT_SECTION; ++j) {
            switch (matrics[Up][i][j]) {
                case Up:
                case Note: break;
                default: return;
            }
        }
    }

    for (int i = 0; i < COUNT_SECTION; ++i) {
        for (int j = 0; j < COUNT_SECTION; ++j) {
            switch (matrics[Left][i][j]) {
                case Left:
                case Note: break;
                default: return;
            }
        }
    }

    for (int i = 0; i < COUNT_SECTION; ++i) {
        for (int j = 0; j < COUNT_SECTION; ++j) {
            switch (matrics[Forward][i][j]) {
                case Forward:
                case Note: break;
                default: return;
            }
        }
    }

    for (int i = 0; i < COUNT_SECTION; ++i) {
        for (int j = 0; j < COUNT_SECTION; ++j) {
            switch (matrics[Right][i][j]) {
                case Right:
                case Note: break;
                default: return;
            }
        }
    }

    for (int i = 0; i < COUNT_SECTION; ++i) {
        for (int j = 0; j < COUNT_SECTION; ++j) {
            switch (matrics[Back][i][j]) {
                case Back:
                case Note: break;
                default: return;
            }
        }
    }

    for (int i = 0; i < COUNT_SECTION; ++i) {
        for (int j = 0; j < COUNT_SECTION; ++j) {
            switch (matrics[Down][i][j]) {
                case Down:
                case Note: break;
                default: return;
            }
        }
    }

    std::string str;

    for (int j = 0; j < COUNT_ROTATE; ++j) {
        switch (rotateArr[j]) {
            case U: str += "U  "; break;
            case U2: str += "U2 "; break;
            case U3: str += "U' "; break;
            case R: str += "R  "; break;
            case R2: str += "R2 "; break;
            case R3: str += "R' "; break;
            case F: str += "F  "; break;
            case F2: str += "F2 "; break;
            case F3: str += "F' "; break;

            case None: j = COUNT_ROTATE; break;
        }
    }

    std::cout << str << std::endl;
}

void KubThread::findRotates()
{
    while (count) {
        check();
        rotateLast(lastRotate);

        while (rotateArr[lastRotate] == None) {
            --lastRotate;

            if (lastRotate == 0) {
                --count;
            }

            rotateLast(lastRotate);
        }

        if (lastRotate < countRotate) {
            ++lastRotate;
        }
    }
}

void KubThread::currentRotate(int n)
{
    adjacentRotate(matrics[n][0][0], matrics[n][1][0], matrics[n][1][1], matrics[n][0][1]);
}

void KubThread::currentDoubleRotate(int n)
{
    adjacentDoubleRotate(matrics[n][0][0], matrics[n][1][0], matrics[n][1][1],
                         matrics[n][0][1]);
}

void KubThread::currentReversRotate(int n)
{
    adjacentReversRotate(matrics[n][0][0], matrics[n][1][0], matrics[n][1][1],
                         matrics[n][0][1]);
}

void KubThread::adjacentRotate(int &n1, int &n2, int &n3, int &n4)
{
    std::swap(n1, n2);
    std::swap(n3, n4);
    std::swap(n2, n4);
}

void KubThread::adjacentDoubleRotate(int &n1, int &n2, int &n3, int &n4)
{
    std::swap(n1, n3);
    std::swap(n2, n4);
}

void KubThread::adjacentReversRotate(int &n1, int &n2, int &n3, int &n4)
{
    std::swap(n1, n2);
    std::swap(n3, n4);
    std::swap(n1, n3);
}
