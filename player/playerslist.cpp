#include "playerslist.h"
#include "playersmodel.h"
#include <QtDebug>
PlayersList::PlayersList(QObject *parent) : QObject(parent)
{
    players.append({ "test", 1, 1 });
}

QVector<Player> PlayersList::getPlayers() const
{
    return players;
}

QVariantList PlayersList::getPlayer(int index) const
{
    QVariantList list;
    list << players[index];
    return list;
}

void PlayersList::editName(const QVariant &value, const int &index)
{
    players[index].name = value.toString();
    emit playerNameEdited(index, PlayersModel::NameRole, value);
}

void PlayersList::addWin(int index)
{
    players[index].wins++;
}

void PlayersList::removeWin(int index)
{
    players[index].wins--;
}

void PlayersList::addLost(int index)
{
    players[index].lost++;
}

void PlayersList::removeLost(int index)
{
    players[index].lost--;
}

bool PlayersList::setPlayerAt(int index, const Player &player)
{
    if (index < 0 || index >= players.size())
        return false;

    const Player & oldPlayer = players.at(index);
    if (player == oldPlayer)
        return false;

    players[index] = player;
    return true;
}

void PlayersList::appendPlayer(QString name, unsigned wins, unsigned int lost)
{
    emit prePlayerAppended();

    Player player;
    player.name = name;
    player.wins = wins;
    player.lost = lost;
    players.append(player);

    emit postPlayerAppended();
}

void PlayersList::removePlayer(int index)
{
    emit prePlayerRemoved(index);

    players.removeAt(index);

    emit postPlayerRemoved();
}
