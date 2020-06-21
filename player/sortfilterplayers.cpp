#include "sortfilterplayers.h"
#include <QtDebug>
#include "playersmodel.h"
SortFilterPlayers::SortFilterPlayers(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

void SortFilterPlayers::setOrderSorting(Qt::SortOrder sortOrder)
{
    if (sortOrder == Qt::AscendingOrder)
        sort(0, Qt::AscendingOrder);
    else
        sort(0, Qt::DescendingOrder);
}

bool SortFilterPlayers::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left, PlayersModel::MoneyWonRole);
    QVariant rightData = sourceModel()->data(right, PlayersModel::MoneyWonRole);

    if (leftData == rightData)
    {
        leftData = sourceModel()->data(left, PlayersModel::NameRole);
        rightData = sourceModel()->data(right, PlayersModel::NameRole);

        return leftData.toString() < rightData.toString();
    }

    return leftData.toInt() < rightData.toInt();
}
