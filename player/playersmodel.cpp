#include "playersmodel.h"
#include "playerslist.h"
#include <QtDebug>

PlayersModel::PlayersModel(QObject *parent)
    : QAbstractListModel(parent), playersList(nullptr)
{

}

void PlayersModel::sortData(bool yes)
{
    emit layoutAboutToBeChanged();

qDebug() << playersList->getPlayera(0);
    if (yes)
    sort(0);
    else
        sort(0, Qt::DescendingOrder);

    emit layoutChanged();
}

int PlayersModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !playersList)
        return 0;

    return playersList->getPlayers().size();
}

QVariant PlayersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !playersList)
        return QVariant();

    const Player player = playersList->getPlayers().at(index.row());
    switch (role) {
    case NameRole:
        return QVariant(player.name);
    case MoneyPaidInRole:
        return QVariant(player.moneyPaidIn);
    case MoneyWonRole:
        return QVariant(player.moneyWon);
    case FrequencyRole:
        return QVariant(player.competitionsParticipated.size());
    }
    return QVariant();
}

bool PlayersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!playersList)
        return false;

    Player player = playersList->getPlayers().at(index.row());
    switch (role) {
    case NameRole:
        player.name = value.toString();
        break;
    case MoneyPaidInRole:
        player.moneyPaidIn = value.toUInt();
        break;
    case MoneyWonRole:
        player.moneyWon = value.toInt();
        break;
    }
//qDebug() << "co jes" << value << data(index, role);
    if (data(index, role) != value) {
//        qDebug() << "succes";
        emit dataChanged(index, index, QVector<int>() << role);
        emit playersListChanged(player);
        return true;
    }
    return false;
}

Qt::ItemFlags PlayersModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> PlayersModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[MoneyPaidInRole] = "moneyPaidIn";
    names[MoneyWonRole] = "moneyWon";
    names[FrequencyRole] = "frequency";
    return names;
}

PlayersList *PlayersModel::getPlayersList() const
{
    return playersList;
}

void PlayersModel::setPlayersList(PlayersList *playersList_)
{
    beginResetModel();

    if (playersList)
        playersList->disconnect(this);

    playersList = playersList_;

    if (playersList)
    {
        connect(playersList, &PlayersList::prePlayerAppended, this, [=](){
            const int index = playersList->getPlayers().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(playersList, &PlayersList::postPlayerAppended, this, [=](){
            endInsertRows();
        });
        connect(playersList, &PlayersList::prePlayerRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(playersList, &PlayersList::postPlayerRemoved, this, [=](){
            endRemoveRows();
        });
        connect(playersList, &PlayersList::playerNameEdited, this, [=](int modelIndex, int role, QVariant value) {
            QModelIndex qModelIndex = index(modelIndex);
            setData(qModelIndex, value, role);
            qDebug() << qModelIndex << role << value;
        });
    }    

    endResetModel();
}
