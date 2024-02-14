#pragma once

#include <QString>

struct Sectors {
    Sectors();
    Sectors(const Sectors &sec);
    friend bool operator==(const Sectors &s1, const Sectors &s2);
    friend uint qHash(const Sectors &s);
    QString toString();
    static Sectors fromString(const QString &str);
    void rotate(int n);
    inline void currentRotate(int n);
    inline void currentDoubleRotate(int n);
    inline void currentReversRotate(int n);
    inline void adjacentRotate(int &n1, int &n2, int &n3, int &n4);
    inline void adjacentDoubleRotate(int &n1, int &n2, int &n3, int &n4);
    inline void adjacentReversRotate(int &n1, int &n2, int &n3, int &n4);

    int matrics[6][2][2];
};

enum { None = -1, U, U2, U3, R, R2, R3, F, F2, F3 };
enum { Note = -1, Up = 0, Right = 3, Forward = 2 };
