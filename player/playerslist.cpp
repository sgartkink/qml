#include "playerslist.h"
#include "playersmodel.h"
#include <QtDebug>
PlayersList::PlayersList(QObject *parent) : QObject(parent)
{
    CompetitionsParticipatedInfo cPI { 0, 2000, 5000 };
    CompetitionsParticipatedInfo cPI2 { 1, 3000, 50 };
    QVector<CompetitionsParticipatedInfo> vectorOfCompetitions { cPI, cPI2 };
    unsigned int moneyPaidIn = 0;
    int moneyWon = 0;
    for (auto it = vectorOfCompetitions.begin(); it != vectorOfCompetitions.end(); ++it)
    {
        moneyPaidIn += (*it).moneyPaidIn;
        moneyWon += (*it).moneyWon;
    }
    players.append({ "test", moneyPaidIn, moneyWon, vectorOfCompetitions });

    vectorOfCompetitions.clear();
    moneyPaidIn = 0;
    moneyWon = 0;
    cPI = { 0, 1000, 4000 };
    cPI2 = { 1, 4000, 2000 };
    vectorOfCompetitions = { cPI, cPI2 };
    for (auto it = vectorOfCompetitions.begin(); it != vectorOfCompetitions.end(); ++it)
    {
        moneyPaidIn += (*it).moneyPaidIn;
        moneyWon += (*it).moneyWon;
    }
    players.append({ "test2", moneyPaidIn, moneyWon, vectorOfCompetitions });
}

QVector<Player> PlayersList::getPlayers() const
{
    return players;
}

QVariantList PlayersList::getPlayer(const int & index) const
{
    QVariantList list;
    list << players[index];
    return list;
}

QString PlayersList::getPlayera(const int &index)
{
    return players[index].name;
}

QVariantList PlayersList::getPlayersCompetitions(int player, int index) const
{
    QVariantList list;
    list << players[player].competitionsParticipated[index];
    return list;
}

QVector<int> PlayersList::playersInCompetition(int index) const
{
    QVector<int> playersIndexes;
    for (int i = 0; i < players.size(); i++)
        for (auto it = players[i].competitionsParticipated.begin(); it != players[i].competitionsParticipated.end(); ++it)
            if ((*it).index == index)
                playersIndexes.append(i);
    return playersIndexes;
}

QVector<int> PlayersList::playersIndexesCompetitions(int index) const
{
    QVector<int> playersIndexes;
    for (int i = 0; i < players.size(); i++)
        for (auto it = players[i].competitionsParticipated.begin(); it != players[i].competitionsParticipated.end(); ++it)
            if ((*it).index == index)
                playersIndexes.append((*it).index);
    return playersIndexes;
}

int PlayersList::amoutOfPlayersInCompetition(int index) const
{
    int sum = 0;
    for (int i = 0; i < players.size(); i++)
        for (auto it = players[i].competitionsParticipated.begin(); it != players[i].competitionsParticipated.end(); ++it)
            if ((*it).index == index)
                sum++;
    return sum;
}

int PlayersList::amoutOfCompetitions(int index) const
{
    return players[index].competitionsParticipated.size();
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

void PlayersList::appendPlayer(QString name, unsigned int moneyPaidIn, int moneyWon)
{
    emit prePlayerAppended();

    Player player;
    player.name = name;
    player.moneyPaidIn = moneyPaidIn;
    player.moneyWon = moneyWon;
    players.append(player);

    emit postPlayerAppended();
}

void PlayersList::removePlayer(int index)
{
    emit prePlayerRemoved(index);

    players.removeAt(index);

    emit postPlayerRemoved();
}
