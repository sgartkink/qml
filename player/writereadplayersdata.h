#ifndef WRITEREADPLAYERDATA_H
#define WRITEREADPLAYERDATA_H

#include <QStringLiteral>
#include <QIODevice>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "playerslist.h"

class WriteReadPlayersData
{
public:
    WriteReadPlayersData();

    QVector<Player> readFromFile();
    bool writeToFile(QVector<Player> & players) const;
};

#endif // WRITEREADPLAYERDATA_H
