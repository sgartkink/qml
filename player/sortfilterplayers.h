#ifndef SORTFILTERPLAYERS_H
#define SORTFILTERPLAYERS_H

#include <QSortFilterProxyModel>

class SortFilterPlayers : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortFilterPlayers(QObject *parent = nullptr);
};

#endif // SORTFILTERPLAYERS_H
