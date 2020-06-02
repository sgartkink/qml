#include "sortfilterplayers.h"
#include <QtDebug>
#include "playersmodel.h"
SortFilterPlayers::SortFilterPlayers(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

void SortFilterPlayers::setOrderSorting(bool sorting)
{
    if (sorting)
        sort(0, Qt::DescendingOrder);
    else
        sort(0, Qt::AscendingOrder);
}

void SortFilterPlayers::setFilterCompetitionIndex(int index)
{
    competitionIndex = index;
    invalidateFilter();
}

bool SortFilterPlayers::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);

    if (competitionIndex != -1)
    {
        QVariantList list = sourceModel()->data(index0, PlayersModel::CompetitionsParticipatedIndexesRole).toList();
        for (auto it = list.begin(); it != list.end(); ++it)
            if ((*it).toInt() == competitionIndex)
                return true;
        return false;
    }

    return true;
}

bool SortFilterPlayers::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left, PlayersModel::CompetitionsParticipatedMoneyWonRole);
    QVariant rightData = sourceModel()->data(right, PlayersModel::CompetitionsParticipatedMoneyWonRole);

    return leftData.toString() < rightData.toString();
}
