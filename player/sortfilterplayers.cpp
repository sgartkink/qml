#include "sortfilterplayers.h"
#include <QtDebug>
SortFilterPlayers::SortFilterPlayers(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void SortFilterPlayers::toggleOrderSorting(bool sorting)
{
    if (sorting)
        sort(0, Qt::DescendingOrder);
    else
        sort(0, Qt::AscendingOrder);
}

bool SortFilterPlayers::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left, 2);
    QVariant rightData = sourceModel()->data(right, 2);

    return leftData.toString() < rightData.toString();
}
