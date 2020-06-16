#include "playerslist.h"
#include "playersmodel.h"
#include "writereadplayersdata.h"
#include <QtDebug>
PlayersList::PlayersList(QObject *parent) : QObject(parent)
{
//    CompetitionsParticipatedInfo cPI { 0, 2000, 5000 };
//    CompetitionsParticipatedInfo cPI2 { 1, 3000, 50 };
//    QVector<CompetitionsParticipatedInfo> vectorOfCompetitions { cPI/*, cPI2*/ };
//    unsigned int moneyPaidIn = 0;
//    int moneyWon = 0;
//    for (auto it = vectorOfCompetitions.begin(); it != vectorOfCompetitions.end(); ++it)
//    {
//        moneyPaidIn += (*it).moneyPaidIn;
//        moneyWon += (*it).moneyWon;
//    }
//    players.append({ "test", moneyPaidIn, moneyWon, 0, vectorOfCompetitions });

//    vectorOfCompetitions.clear();
//    moneyPaidIn = 0;
//    moneyWon = 0;
//    cPI = { 0, 1000, 4000 };
//    cPI2 = { 1, 4000, 2000 };
//    vectorOfCompetitions = { cPI, cPI2 };
//    for (auto it = vectorOfCompetitions.begin(); it != vectorOfCompetitions.end(); ++it)
//    {
//        moneyPaidIn += (*it).moneyPaidIn;
//        moneyWon += (*it).moneyWon;
//    }
//    players.append({ "test2", moneyPaidIn, moneyWon, 1, vectorOfCompetitions });

    writeReadPlayersData = new WriteReadPlayersData();
    players = writeReadPlayersData->readFromFile();

    for (int i = 0; i < players.size(); i++)
    {
        Player & p = players[i];
        unsigned int moneyPaidIn = 0;
        int moneyWon = 0;

        for (const CompetitionsParticipatedInfo & c : p.competitionsParticipated)
        {
            moneyPaidIn += c.moneyPaidIn;
            moneyWon += c.moneyWon;
        }

        p.moneyPaidIn = moneyPaidIn;
        p.moneyWon = moneyWon;
        p.number = i;
    }
}

const QVector<Player> &PlayersList::getPlayers() const
{
    return players;
}

QVariantList PlayersList::getPlayer(const int & index) const
{
    QVariantList list;
    list << players[index];
    return list;
}

QVariantList PlayersList::getPlayerCompetitionsInfo(int player, int index) const
{
    QVariantList list;
    for (auto it = players[player].competitionsParticipated.begin(); it != players[player].competitionsParticipated.end(); ++it)
        if ((*it).index == index)
        {
            list << (*it);
            break;
        }
    return list;
}

int PlayersList::amoutOfCompetitions(int index) const
{
    return players[index].competitionsParticipated.size();
}

void PlayersList::saveData()
{
    if (writeReadPlayersData->writeToFile(players))
        emit dataSaved();
    else
        emit dataNotSaved();
}

void PlayersList::addCompetitionToPlayer(int playerIndex, int competitionIndex, unsigned int moneyPaidIn, int moneyWon)
{
    CompetitionsParticipatedInfo cPI { competitionIndex, moneyPaidIn, moneyWon };
    players[playerIndex].competitionsParticipated.append(cPI);
    players[playerIndex].moneyWon += moneyWon;
    players[playerIndex].moneyPaidIn += moneyPaidIn;
    emit playerChanged(playerIndex, PlayersModel::CompetitionsParticipatedIndexesRole);
    emit playerChanged(playerIndex, PlayersModel::CompetitionsParticipatedMoneyWonRole);
    emit playerChanged(playerIndex, PlayersModel::MoneyWonRole);
    emit playerChanged(playerIndex, PlayersModel::MoneyPaidInRole);
    emit playerChanged(playerIndex, PlayersModel::FrequencyRole);
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

unsigned int PlayersList::getPlayersMoneyPaidInCompetition(int &competitionIndex) const
{
    unsigned int money = 0;
    for (int i = 0; i < players.size(); i++)
        for (int j = 0; j < players[i].competitionsParticipated.size(); j++)
            if (players[i].competitionsParticipated[j].index == competitionIndex)
                money += players[i].competitionsParticipated[j].moneyPaidIn;
    return money;
}

void PlayersList::appendPlayer(QString name, unsigned int moneyPaidIn, int moneyWon)
{
    emit prePlayerAppended();

    Player player;
    player.name = name;
    player.moneyPaidIn = moneyPaidIn;
    player.moneyWon = moneyWon;
    player.number = players.size();
    players.append(player);

    emit postPlayerAppended();
}

void PlayersList::removePlayer(int index)
{
    emit prePlayerRemoved(index);

    players.removeAt(index);

    emit postPlayerRemoved();
}
