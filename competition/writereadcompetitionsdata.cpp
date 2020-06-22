#include "writereadcompetitionsdata.h"

WriteReadCompetitionsData::WriteReadCompetitionsData()
{

}

QVector<Competition> WriteReadCompetitionsData::readFromFile()
{
    QFile loadFile(QStringLiteral("competitions.json"));
    QVector<Competition> competitions;

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open file");
        return competitions;
    }
    QByteArray saveData = loadFile.readAll();

    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
    QJsonObject jsonObject = jsonDocument.object();
    if (!jsonObject.contains("competitions"))
        return competitions;
    else
    {
        QJsonArray jsonCompetitionsArray = jsonObject["competitions"].toArray();
        competitions.reserve(jsonCompetitionsArray.size());

        for (int i = 0; i < jsonCompetitionsArray.size(); i++)
        {
            QJsonObject jsonCompetition = jsonCompetitionsArray[i].toObject();
            Competition c;

            QString str = jsonCompetition["date"].toString();
            QDateTime date = QDateTime::fromString(str);

            c.date = date;
            c.jackpot = static_cast<unsigned int>(jsonCompetition["jackpot"].toInt());

            competitions.append(c);
        }
    }

    return competitions;
}

bool WriteReadCompetitionsData::writeToFile(QVector<Competition> &competitions) const
{
    QFile saveFile(QStringLiteral("competitions.json"));

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open file");
        return false;
    }

    QJsonObject jsonObject;
    QJsonArray jsonCompetitionsArray;

    for (const Competition & c : competitions)
    {
        QJsonObject jsonCompetition;

        jsonCompetition["date"] = c.date.toString();
        jsonCompetition["jackpot"] = static_cast<int>(c.jackpot);
        jsonCompetitionsArray.append(jsonCompetition);
    }
    jsonObject["competitions"] = jsonCompetitionsArray;

    saveFile.write(QJsonDocument(jsonObject).toJson());
    return true;
}
