#ifndef SORTFILTERPLAYERS_H
#define SORTFILTERPLAYERS_H

#include <QSortFilterProxyModel>

class SortFilterPlayers : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortFilterPlayers(QObject *parent = nullptr);

    Q_INVOKABLE void setOrderSorting(bool sorting);
    Q_INVOKABLE void setFilterCompetitionIndex(int index);
    Q_INVOKABLE bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    int competitionIndex = -1;
};

#endif // SORTFILTERPLAYERS_H
