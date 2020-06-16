#include "sortfiltercompetition.h"
#include "player/playersmodel.h"
#include <QtDebug>
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

void SortFilterCompetition::setShow(bool s)
{
    show = s;
    invalidateFilter();
}

bool SortFilterCompetition::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QVariantList list = sourceModel()->data(index0, PlayersModel::CompetitionsParticipatedIndexesRole).toList();
    if (show)
    {
        for (auto it = list.begin(); it != list.end(); ++it)
            if ((*it).toInt() == competitionIndex)
                return true;
        return false;
    }
    else
    {
        for (auto it = list.begin(); it != list.end(); ++it)
            if ((*it).toInt() == competitionIndex)
                return false;
        return true;
    }
}

bool SortFilterCompetition::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    int moneyWonLeft = calcMoneyWon(left);
    int moneyWonRight = calcMoneyWon(right);

    return moneyWonLeft < moneyWonRight;
}

int SortFilterCompetition::calcMoneyWon(const QModelIndex &side) const
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
