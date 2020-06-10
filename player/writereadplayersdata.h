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

    void readFromFile(const QJsonObject &json);
    bool writeToFile(QVector<Player> & players) const;

signals:

};

#endif // WRITEREADPLAYERDATA_H
