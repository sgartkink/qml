#ifndef SORTFILTERCOMPETITION_H
#define SORTFILTERCOMPETITION_H

#include <QSortFilterProxyModel>

class SortFilterCompetition : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortFilterCompetition(QObject *parent = nullptr);

    Q_INVOKABLE void setOrderSorting(Qt::SortOrder sortOrder);
    Q_INVOKABLE void setFilterCompetitionIndex(int index);
    Q_INVOKABLE bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    int competitionIndex = -1;
};

#endif // SORTFILTERCOMPETITION_H
