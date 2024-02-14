#include "tree.h"

#include <QDebug>

Tree::Tree() {}

QList<Sectors> Tree::keys(uint8_t size) const
{
    QVector<int> vec;
    return mTree.keys(vec, size);
}

uint Tree::size(const Sectors &sec) const
{
    auto vec = sec.toVec();
    return mTree.size(vec);
}

void Tree::append(const Sectors &sec, const QVector<uint8_t> &res)
{
    auto vec = sec.toVec();
    mTree.append(vec, res);
}

QVector<QVector<uint8_t>> Tree::value(const Sectors &sec) const
{
    auto vec = sec.toVec();
    return mTree.value(vec);
}
