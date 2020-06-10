#include "writereadplayersdata.h"
#include <QtDebug>
WriteReadPlayersData::WriteReadPlayersData()
{

}

QVector<Player> WriteReadPlayersData::readFromFile()
{
    QFile loadFile(QStringLiteral("save.json"));
    QVector<Player> players;

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open file");
        return players;
    }
    QByteArray saveData = loadFile.readAll();

    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
    QJsonObject jsonObject = jsonDocument.object();
    if (!jsonObject.contains("players"))
        return players;
    else
    {
        QJsonArray jsonPlayersArray = jsonObject["players"].toArray();
        players.reserve(jsonPlayersArray.size());

        for (int i = 0; i < jsonPlayersArray.size(); i++)
        {
            QJsonObject jsonPlayer = jsonPlayersArray[i].toObject();
            Player p;

            p.name = jsonPlayer["name"].toString();
            p.number = jsonPlayer["number"].toInt();

            QVector<CompetitionsParticipatedInfo> competitions;
            QJsonArray jsonCompetitionsArray = jsonPlayer["competitions"].toArray();
            competitions.reserve(jsonCompetitionsArray.size());

            for (int j = 0; j < jsonCompetitionsArray.size(); j++)
            {
                QJsonObject jsonCompetition = jsonCompetitionsArray[j].toObject();
                CompetitionsParticipatedInfo c;

                c.index = jsonCompetition["index"].toInt();
                c.moneyPaidIn = static_cast<unsigned int>(jsonCompetition["moneyPaidIn"].toInt());
                c.moneyWon = jsonCompetition["moneyWon"].toInt();

                competitions.append(c);
            }

            p.competitionsParticipated = competitions;
            players.append(p);
        }
    }

    return players;
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
    QJsonArray jsonPlayersArray;

    for (const Player & p : players)
    {
        QJsonObject jsonPlayer;

        jsonPlayer["name"] = p.name;
        jsonPlayer["number"] = p.number;

        QJsonArray jsonCompetitionsArray;
        for (const CompetitionsParticipatedInfo & c : p.competitionsParticipated)
        {
            QJsonObject jsonCompetition;

            jsonCompetition["index"] = c.index;
            jsonCompetition["moneyPaidIn"] = static_cast<int>(c.moneyPaidIn);
            jsonCompetition["moneyWon"] = c.moneyWon;

            jsonCompetitionsArray.append(jsonCompetition);
        }
        jsonPlayer["competitions"] = jsonCompetitionsArray;
        jsonPlayersArray.append(jsonPlayer);
    }
    jsonObject["players"] = jsonPlayersArray;

    saveFile.write(QJsonDocument(jsonObject).toJson());
    return true;
}
