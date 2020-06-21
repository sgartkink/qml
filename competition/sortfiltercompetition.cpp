#include "sortfiltercompetition.h"
#include "player/playersmodel.h"
#include <QtDebug>
SortFilterCompetitions::SortFilterCompetitions(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

void SortFilterCompetitions::setOrderSorting(Qt::SortOrder sortOrder)
{
    if (sortOrder == Qt::AscendingOrder)
        sort(0, Qt::AscendingOrder);
    else
        sort(0, Qt::DescendingOrder);
}

void SortFilterCompetitions::setFilterCompetitionIndex(int index)
{
    competitionIndex = index;
    invalidateFilter();
}

void SortFilterCompetitions::setShowPlayersWhoIncludeIndex(bool s)
{
    showPlayersWhoIncludeIndex = s;
    invalidateFilter();
}

bool SortFilterCompetitions::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    QVariantList list = sourceModel()->data(index, PlayersModel::CompetitionsParticipatedIndexesRole).toList();
    if (showPlayersWhoIncludeIndex)
        return checkIfIndexIsContainedInList(list);
    else
        return !checkIfIndexIsContainedInList(list);
}

bool SortFilterCompetitions::checkIfIndexIsContainedInList(const QVariantList& list) const
{
    for (auto it = list.begin(); it != list.end(); ++it)
        if ((*it).toInt() == competitionIndex)
            return true;
    return false;
}

bool SortFilterCompetitions::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    int moneyWonLeft = calcMoneyWon(left);
    int moneyWonRight = calcMoneyWon(right);

    if (moneyWonLeft == moneyWonRight)
    {
        QVariant leftData = sourceModel()->data(left, PlayersModel::NameRole);
        QVariant rightData = sourceModel()->data(right, PlayersModel::NameRole);

        return leftData.toString() < rightData.toString();
    }

    return moneyWonLeft < moneyWonRight;
}

int SortFilterCompetitions::calcMoneyWon(const QModelIndex &side) const
{
    QVariantList listIndexes = sourceModel()->data(side, PlayersModel::CompetitionsParticipatedIndexesRole).toList();
    int moneyWon = 0;
    for (int i = 0; i < listIndexes.size(); i++)
        if (listIndexes[i].toInt() == competitionIndex)
        {
            QVariantList listMoney = sourceModel()->data(side, PlayersModel::CompetitionsParticipatedMoneyWonRole).toList();
            moneyWon = listMoney[i].toInt();
            break;
        }
    return moneyWon;
}
