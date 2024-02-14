#include "kubthread.h"

#include <iostream>

KubThread::KubThread(int mat[][COUNT_SECTION][COUNT_SECTION], int n, int n2, int count,
                     int countRotate, int lastRotate) :
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

    for (int i = 0; i < n2; ++i) {
        rotateLast(1);
    }

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

        case D:
            currentRotate(Down);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                               matrics[2][2][i]);
            }

            break;

        case D2:
            currentDoubleRotate(Down);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentDoubleRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                                     matrics[2][2][i]);
            }

            break;

        case D3:
            currentReversRotate(Down);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentReversRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                                     matrics[2][2][i]);
            }

            break;

        case R:
            currentRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][2 - i][2], matrics[2][2 - i][2], matrics[5][2 - i][2],
                               matrics[4][i][0]);
            }

            break;

        case R2:
            currentDoubleRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentDoubleRotate(matrics[0][2 - i][2], matrics[2][2 - i][2],
                                     matrics[5][2 - i][2], matrics[4][i][0]);
            }

            break;

        case R3:
            currentReversRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentReversRotate(matrics[0][2 - i][2], matrics[2][2 - i][2],
                                     matrics[5][2 - i][2], matrics[4][i][0]);
            }

            break;

        case L:
            currentRotate(Left);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                               matrics[2][i][0]);
            }

            break;

        case L2:
            currentDoubleRotate(Left);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentDoubleRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                                     matrics[2][i][0]);
            }

            break;

        case L3:
            currentReversRotate(Left);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentReversRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                                     matrics[2][i][0]);
            }

            break;

        case F:
            currentRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][2][i], matrics[1][2 - i][2], matrics[5][0][2 - i],
                               matrics[3][i][0]);
            }

            break;

        case F2:
            currentDoubleRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentDoubleRotate(matrics[0][2][i], matrics[1][2 - i][2],
                                     matrics[5][0][2 - i], matrics[3][i][0]);
            }

            break;

        case F3:
            currentReversRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentReversRotate(matrics[0][2][i], matrics[1][2 - i][2],
                                     matrics[5][0][2 - i], matrics[3][i][0]);
            }

            break;

        case B:
            currentRotate(Back);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][0][2 - i], matrics[3][2 - i][2], matrics[5][2][i],
                               matrics[1][i][0]);
            }

            break;

        case B2:
            currentDoubleRotate(Back);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentDoubleRotate(matrics[0][0][2 - i], matrics[3][2 - i][2],
                                     matrics[5][2][i], matrics[1][i][0]);
            }

            break;

        case B3:
            currentReversRotate(Back);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentReversRotate(matrics[0][0][2 - i], matrics[3][2 - i][2],
                                     matrics[5][2][i], matrics[1][i][0]);
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
                    rotateArr[n] = D;
                    currentRotate(Down);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                                       matrics[2][2][i]);
                    }

                    break;

                case D:
                case D2:
                case D3:
                    rotateArr[n] = R;
                    currentRotate(Right);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[0][2 - i][2], matrics[2][2 - i][2],
                                       matrics[5][2 - i][2], matrics[4][i][0]);
                    }

                    break;

                default:
                    rotateArr[n] = U;
                    currentRotate(Up);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[1][0][i], matrics[2][0][i], matrics[3][0][i],
                                       matrics[4][0][i]);
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

            rotateArr[n] = D;
            currentRotate(Down);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                               matrics[2][2][i]);
            }

            break;

        case D:
            rotateArr[n] = D2;
            currentRotate(Down);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                               matrics[2][2][i]);
            }

            break;

        case D2:
            rotateArr[n] = D3;
            currentRotate(Down);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                               matrics[2][2][i]);
            }

            break;

        case D3:
            currentRotate(Down);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[1][2][i], matrics[4][2][i], matrics[3][2][i],
                               matrics[2][2][i]);
            }
            switch (rotateArr[n - 1]) {
                case R:
                case R2:
                case R3:
                    rotateArr[n] = L;
                    currentRotate(Left);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                                       matrics[2][i][0]);
                    }

                    break;

                case L:
                case L2:
                case L3:
                    rotateArr[n] = F;
                    currentRotate(Forward);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[0][2][i], matrics[1][2 - i][2],
                                       matrics[5][0][2 - i], matrics[3][i][0]);
                    }

                    break;

                default:
                    rotateArr[n] = R;
                    currentRotate(Right);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[0][2 - i][2], matrics[2][2 - i][2],
                                       matrics[5][2 - i][2], matrics[4][i][0]);
                    }
            }

            break;

        case R:
            rotateArr[n] = R2;
            currentRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][2 - i][2], matrics[2][2 - i][2], matrics[5][2 - i][2],
                               matrics[4][i][0]);
            }

            break;

        case R2:
            rotateArr[n] = R3;
            currentRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][2 - i][2], matrics[2][2 - i][2], matrics[5][2 - i][2],
                               matrics[4][i][0]);
            }

            break;

        case R3:
            currentRotate(Right);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][2 - i][2], matrics[2][2 - i][2], matrics[5][2 - i][2],
                               matrics[4][i][0]);
            }

            rotateArr[n] = L;
            currentRotate(Left);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                               matrics[2][i][0]);
            }

            break;

        case L:
            rotateArr[n] = L2;
            currentRotate(Left);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                               matrics[2][i][0]);
            }

            break;

        case L2:
            rotateArr[n] = L3;
            currentRotate(Left);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                               matrics[2][i][0]);
            }

            break;

        case L3:
            currentRotate(Left);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][i][0], matrics[4][2 - i][2], matrics[5][i][0],
                               matrics[2][i][0]);
            }

            switch (rotateArr[n - 1]) {
                case F:
                case F2:
                case F3:
                    rotateArr[n] = B;
                    currentRotate(Back);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[0][0][2 - i], matrics[3][2 - i][2],
                                       matrics[5][2][i], matrics[1][i][0]);
                    }

                    break;

                case B:
                case B2:
                case B3: rotateArr[n] = None; break;

                default:
                    rotateArr[n] = F;
                    currentRotate(Forward);

                    for (int i = 0; i < COUNT_SECTION; ++i) {
                        adjacentRotate(matrics[0][2][i], matrics[1][2 - i][2],
                                       matrics[5][0][2 - i], matrics[3][i][0]);
                    }
            }

            break;

        case F:
            rotateArr[n] = F2;
            currentRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][2][i], matrics[1][2 - i][2], matrics[5][0][2 - i],
                               matrics[3][i][0]);
            }

            break;

        case F2:
            rotateArr[n] = F3;
            currentRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][2][i], matrics[1][2 - i][2], matrics[5][0][2 - i],
                               matrics[3][i][0]);
            }

            break;

        case F3:
            currentRotate(Forward);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][2][i], matrics[1][2 - i][2], matrics[5][0][2 - i],
                               matrics[3][i][0]);
            }

            rotateArr[n] = B;
            currentRotate(Back);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][0][2 - i], matrics[3][2 - i][2], matrics[5][2][i],
                               matrics[1][i][0]);
            }

            break;

        case B:
            rotateArr[n] = B2;
            currentRotate(Back);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][0][2 - i], matrics[3][2 - i][2], matrics[5][2][i],
                               matrics[1][i][0]);
            }

            break;

        case B2:
            rotateArr[n] = B3;
            currentRotate(Back);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][0][2 - i], matrics[3][2 - i][2], matrics[5][2][i],
                               matrics[1][i][0]);
            }

            break;

        case B3:
            currentRotate(Back);

            for (int i = 0; i < COUNT_SECTION; ++i) {
                adjacentRotate(matrics[0][0][2 - i], matrics[3][2 - i][2], matrics[5][2][i],
                               matrics[1][i][0]);
            }

            rotateArr[n] = None;

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
            case D: str += "D  "; break;
            case D2: str += "D2 "; break;
            case D3: str += "D' "; break;
            case R: str += "R  "; break;
            case R2: str += "R2 "; break;
            case R3: str += "R' "; break;
            case L: str += "L  "; break;
            case L2: str += "L2 "; break;
            case L3: str += "L' "; break;
            case F: str += "F  "; break;
            case F2: str += "F2 "; break;
            case F3: str += "F' "; break;
            case B: str += "B  "; break;
            case B2: str += "B2 "; break;
            case B3: str += "B' "; break;
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

            if (lastRotate == 1) {
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
    adjacentRotate(matrics[n][0][0], matrics[n][2][0], matrics[n][2][2], matrics[n][0][2]);
    adjacentRotate(matrics[n][0][1], matrics[n][1][0], matrics[n][2][1], matrics[n][1][2]);
}

void KubThread::currentDoubleRotate(int n)
{
    adjacentDoubleRotate(matrics[n][0][0], matrics[n][2][0], matrics[n][2][2],
                         matrics[n][0][2]);
    adjacentDoubleRotate(matrics[n][0][1], matrics[n][1][0], matrics[n][2][1],
                         matrics[n][1][2]);
}

void KubThread::currentReversRotate(int n)
{
    adjacentReversRotate(matrics[n][0][0], matrics[n][2][0], matrics[n][2][2],
                         matrics[n][0][2]);
    adjacentReversRotate(matrics[n][0][1], matrics[n][1][0], matrics[n][2][1],
                         matrics[n][1][2]);
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
