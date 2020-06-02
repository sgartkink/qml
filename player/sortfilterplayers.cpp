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

void SortFilterPlayers::toggleSortInCompetitionPopup()
{
    sortInCompetitionPopup = !sortInCompetitionPopup;
    qDebug() << "asd";
}

bool SortFilterPlayers::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (sortInCompetitionPopup)
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
    else
    {
        QVariant leftData = sourceModel()->data(left, PlayersModel::MoneyWonRole);
        QVariant rightData = sourceModel()->data(right, PlayersModel::MoneyWonRole);

        return leftData.toInt() < rightData.toInt();
    }
}
