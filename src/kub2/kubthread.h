#pragma once

class KubThread {
public:
    constexpr static int COUNT_SECTION = 2;
    constexpr static int COUNT_ROTATE = 20;

    KubThread(int mat[][COUNT_SECTION][COUNT_SECTION], int n, int count, int countRotate,
              int lastRotate);
    void rotateFirst(int n);
    void rotateLast(int n);
    inline void check() const;
    void findRotates();
    inline void currentRotate(int n);
    inline void currentDoubleRotate(int n);
    inline void currentReversRotate(int n);
    inline void adjacentRotate(int &n1, int &n2, int &n3, int &n4);
    inline void adjacentDoubleRotate(int &n1, int &n2, int &n3, int &n4);
    inline void adjacentReversRotate(int &n1, int &n2, int &n3, int &n4);

    int matrics[6][COUNT_SECTION][COUNT_SECTION];
    int rotateArr[COUNT_ROTATE]{None, None, None, None, None, None, None, None, None, None,
                                None, None, None, None, None, None, None, None, None, None};
    int count = 0;
    int lastRotate = 0;
    int countRotate;

    enum { None = -1, U, U2, U3, R, R2, R3, F, F2, F3 };
    enum { Note = -1, Up, Left, Forward, Right, Back, Down };
};
