#ifndef SORTFILTERPLAYERS_H
#define SORTFILTERPLAYERS_H

#include <QSortFilterProxyModel>

class SortFilterPlayers : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortFilterPlayers(QObject *parent = nullptr);

    Q_INVOKABLE void setOrderSorting(Qt::SortOrder sortOrder);

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
};

#endif // SORTFILTERPLAYERS_H
