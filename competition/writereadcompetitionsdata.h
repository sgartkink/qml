#ifndef WRITEREADCOMPETITIONSDATA_H
#define WRITEREADCOMPETITIONSDATA_H

#include <QStringLiteral>
#include <QIODevice>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

#include "competitionslist.h"

class WriteReadCompetitionsData
{
public:
    WriteReadCompetitionsData();

    QVector<Competition> readFromFile();
    bool writeToFile(QVector<Competition> & competitions) const;
};

#endif // WRITEREADCOMPETITIONSDATA_H
