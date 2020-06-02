#ifndef PLAYERSMODEL_H
#define PLAYERSMODEL_H

#include <QAbstractListModel>
#include "playerslist.h"
#include "sortfilterplayers.h"

class PlayersModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PlayersList *list READ getPlayersList WRITE setPlayersList NOTIFY playersListChanged)

public:
    explicit PlayersModel(QObject *parent = nullptr);

    enum {
        NameRole,
        MoneyPaidInRole,
        MoneyWonRole,
        NumberRole,
        FrequencyRole,
        CompetitionsParticipatedIndexesRole,
        CompetitionsParticipatedMoneyWonRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    PlayersList *getPlayersList() const;
    void setPlayersList(PlayersList *value);

signals:
    void playersListChanged(Player);

private:
    SortFilterPlayers * sortFilterPlayers;
    PlayersList * playersList;
};

#endif // PLAYERSMODEL_H
