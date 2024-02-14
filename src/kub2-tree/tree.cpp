#include "tree.h"

#include <QDebug>

Tree::Tree() {}

QList<Sectors> Tree::keys(uint size) const
{
    QVector<int> vec;
    return mTree.keys(vec, size);
}

uint Tree::size(const Sectors &sec) const
{
    return mTree.size(sec.toVec());
}

void Tree::append(const Sectors &sec, const QVector<uint8_t> &res)
{
    auto vec = sec.toVec();
    mTree.append(vec, res);
}

QVector<QVector<uint8_t>> Tree::value(const Sectors &sec, const QVector<int> &indexVec) const
{
    return variant(indexVec, sec.toVec(), 0);
}

QVector<QVector<uint8_t>> Tree::valueAll(const Sectors &sec) const
{
    return mTree.valueAll(sec.toVec());
}

QVector<QVector<uint8_t>> Tree::variant(const QVector<int> &indexVec, QVector<int> vec,
                                        int n) const
{
    QVector<QVector<uint8_t>> res;

    if (n < indexVec.size()) {
        for (int i = 0; i < 3; ++i) {
            for (auto &el : mTree.value(vec)) {
                if (!res.contains(el)) {
                    if (res.isEmpty() || (el.size() == res.first().size())) {
                        res.append(el);
                    } else if (el.size() < res.first().size()) {
                        res.clear();
                        res.append(el);
                    }
                }
            }

            auto &el = vec[indexVec[n]];
            el += ((el + 1) % 3) - (el % 3);

            for (auto &el : variant(indexVec, vec, n + 1)) {
                if (!res.contains(el)) {
                    if (res.isEmpty() || (el.size() == res.first().size())) {
                        res.append(el);
                    } else if (el.size() < res.first().size()) {
                        res.clear();
                        res.append(el);
                    }
                }
            }
        }
    } else {
        res.append(mTree.value(vec));
    }

    return res;
}
