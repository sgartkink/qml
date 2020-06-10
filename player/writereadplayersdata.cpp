#include "writereadplayersdata.h"
#include <QtDebug>
WriteReadPlayersData::WriteReadPlayersData()
{

}

bool WriteReadPlayersData::writeToFile(QVector<Player> &players) const
{
    QFile saveFile(QStringLiteral("save.json"));

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open file");
        return false;
    }

    QJsonObject jsonObject;

    QJsonArray jsonPlayers;
    for (const Player & p : players)
    {
        QJsonObject player;

        player["name"] = p.name;
        player["moneyPaidIn"] = static_cast<int>(p.moneyPaidIn);
        player["moneyWon"] = p.moneyWon;
        player["number"] = p.number;

        QJsonArray playerCompetitionsArray;
        for (const CompetitionsParticipatedInfo & c : p.competitionsParticipated)
        {
            QJsonObject playerCompetitionsObject;

            playerCompetitionsObject["index"] = c.index;
            playerCompetitionsObject["moneyPaidIn"] = static_cast<int>(c.moneyPaidIn);
            playerCompetitionsObject["moneyWon"] = static_cast<int>(c.moneyWon);

            playerCompetitionsArray.append(playerCompetitionsObject);
        }
        player["competitions"] = playerCompetitionsArray;
        jsonPlayers.append(player);
    }
    jsonObject["players"] = jsonPlayers;

    saveFile.write(QJsonDocument(jsonObject).toJson());
    return true;
}
