#pragma once

#include <QDebug>
#include <QVector>

#include <sectors.h>

#define SIZE 21

template <int N>
struct TreeStruct {
    QList<Sectors> keysHelper(QVector<int> key, int n, uint size) const
    {
        QList<Sectors> keys;

        if (points[n]) {
            key.append(n);
            keys.append(points[n]->keys(key, size));
        }

        return keys;
    }

    QList<Sectors> keys(QVector<int> &key, uint size) const
    {
        QList<Sectors> keys;

        for (int i = 0; i < SIZE; ++i) {
            keys.append(keysHelper(key, i, size));
        }

        return keys;
    }

    uint size(QVector<int> key) const
    {
        uint size = -1;

        int k = key.takeFirst();

        if (k < 0) {
            for (int i = 0; i < SIZE; ++i) {
                if (points[i]) {
                    uint s = points[i]->size(key);

                    if (s < size) {
                        size = s;
                    }
                }
            }
        } else if (points[k]) {
            uint s = points[k]->size(key);

            if (s < size) {
                size = s;
            }
        }

        return size;
    }

    QVector<QVector<uint8_t>> value(QVector<int> key) const
    {
        int k = key.takeFirst();
        QVector<QVector<uint8_t>> res;

        if (k < 0) {
            int min = 0xFF;

            for (int i = 0; i < SIZE; ++i) {
                if (points[i]) {
                    const auto &vec = points[i]->value(key);

                    if (!vec.isEmpty()) {
                        if (vec.first().size() == min) {
                            res.append(vec);
                        } else if (vec.first().size() < min) {
                            res.clear();
                            res.append(vec);
                            min = res.first().size();
                        }
                    }
                }
            }
        } else if (points[k]) {
            res.append(points[k]->value(key));
        }

        return res;
    }

    QVector<QVector<uint8_t>> valueAll(QVector<int> key) const
    {
        QVector<QVector<uint8_t>> res;
        int k = key.takeFirst();

        if (points[k]) {
            res.append(points[k]->valueAll(key));
        }

        return res;
    }

    void append(QVector<int> &key, const QVector<uint8_t> &res)
    {
        int k = key.takeFirst();

        if (points[k] == nullptr) {
            points[k] = new TreeStruct<N - 1>;
        }

        points[k]->append(key, res);
    }

    ~TreeStruct()
    {
        for (int i = 0; i < SIZE; ++i) {
            if (points[i]) {
                delete points[i];
            }
        }
    }

private:
    TreeStruct<N - 1> *points[SIZE]{nullptr};
};

template <>
struct TreeStruct<0> {
    uint8_t mSize = 0xFF;

    QList<Sectors> keys(QVector<int> &key, uint size) const
    {
        QList<Sectors> res;

        if (mSize == size) {
            res.append(Sectors(key));
        }

        return res;
    }

    uint size(QVector<int>) const { return mSize; }

    QVector<QVector<uint8_t>> value(QVector<int>) const
    {
        QVector<QVector<uint8_t>> res;

        if (mSize) {
            for (int i = 0; i < vec.size(); i += mSize) {
                res.append(vec.mid(i, mSize));
            }
        } else {
            res.append(vec);
        }

        return res;
    }

    QVector<QVector<uint8_t>> valueAll(QVector<int>) const
    {
        QVector<QVector<uint8_t>> res;

        if (mSize) {
            for (int i = 0; i < vec.size(); i += mSize) {
                res.append(vec.mid(i, mSize));
            }
        } else {
            res.append(vec);
        }

        return res;
    }

    void append(QVector<int> &, const QVector<uint8_t> &res)
    {
        mSize = res.size();
        vec.append(res);
    }

private:
    QVector<uint8_t> vec;
};

class Tree {
public:
    Tree();
    QList<Sectors> keys(uint size) const;
    uint size(const Sectors &sec) const;
    void append(const Sectors &sec, const QVector<uint8_t> &res);
    QVector<QVector<uint8_t>> value(const Sectors &sec, const QVector<int> &indexVec) const;
    QVector<QVector<uint8_t>> valueAll(const Sectors &sec) const;

private:
    TreeStruct<7> mTree;

    QVector<QVector<uint8_t>> variant(const QVector<int> &indexVec, QVector<int> vec,
                                      int n) const;
};
