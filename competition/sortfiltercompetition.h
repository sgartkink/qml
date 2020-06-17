#ifndef SORTFILTERCOMPETITION_H
#define SORTFILTERCOMPETITION_H

#include <QSortFilterProxyModel>

class SortFilterCompetitions : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortFilterCompetitions(QObject *parent = nullptr);

    Q_INVOKABLE void setOrderSorting(Qt::SortOrder sortOrder);
    Q_INVOKABLE void setFilterCompetitionIndex(int index);
    Q_INVOKABLE void setShowPlayersWhoIncludeIndex(bool s);
    Q_INVOKABLE bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    int competitionIndex = -1;
    bool showPlayersWhoIncludeIndex = true;

    bool checkIfIndexIsContainedInList(const QVariantList &list) const;
    int calcMoneyWon(const QModelIndex& side) const;
};

#endif // SORTFILTERCOMPETITION_H
