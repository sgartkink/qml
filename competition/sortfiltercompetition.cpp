#include "sortfiltercompetition.h"
#include "player/playersmodel.h"

SortFilterCompetition::SortFilterCompetition(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

void SortFilterCompetition::setOrderSorting(Qt::SortOrder sortOrder)
{
    if (sortOrder == Qt::AscendingOrder)
        sort(0, Qt::AscendingOrder);
    else
        sort(0, Qt::DescendingOrder);
}

void SortFilterCompetition::setFilterCompetitionIndex(int index)
{
    competitionIndex = index;
    invalidateFilter();
}

bool SortFilterCompetition::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QVariantList list = sourceModel()->data(index0, PlayersModel::CompetitionsParticipatedIndexesRole).toList();
    for (auto it = list.begin(); it != list.end(); ++it)
        if ((*it).toInt() == competitionIndex)
            return true;
    return false;
}

bool SortFilterCompetition::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariantList listLeftIndexes = sourceModel()->data(left, PlayersModel::CompetitionsParticipatedIndexesRole).toList();
    int moneyWonLeft = 0;
    int i = 0;
    for (auto it = listLeftIndexes.begin(); it != listLeftIndexes.end(); ++it)
    {
        if ((*it).toInt() == competitionIndex)
        {
            QVariantList listLeftMoney = sourceModel()->data(left, PlayersModel::CompetitionsParticipatedMoneyWonRole).toList();
            moneyWonLeft = listLeftMoney[i].toInt();
            break;
        }
        i++;
    }

    QVariantList listRightIndexes = sourceModel()->data(right, PlayersModel::CompetitionsParticipatedIndexesRole).toList();
    int moneyWonRight = 0;
    i = 0;
    for (auto it = listRightIndexes.begin(); it != listRightIndexes.end(); ++it)
    {
        if ((*it).toInt() == competitionIndex)
        {
            QVariantList listRightMoney = sourceModel()->data(right, PlayersModel::CompetitionsParticipatedMoneyWonRole)
                    .toList();
            moneyWonRight = listRightMoney[i].toInt();
            break;
        }
        i++;
    }

    return moneyWonLeft < moneyWonRight;
}
