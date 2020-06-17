#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QVariant>
#include <QVector>

struct CompetitionsParticipatedInfo
{
    int index;
    unsigned int moneyPaidIn;
    int moneyWon;

    friend QVariantList& operator<<(QVariantList& list, const CompetitionsParticipatedInfo& cpi)
    {
        return list << cpi.index << cpi.moneyPaidIn << cpi.moneyWon;
    }
};

struct Player
{
    QString name;
    unsigned int moneyPaidIn;
    int moneyWon;
    int number;
    QVector<CompetitionsParticipatedInfo> competitionsParticipated;

    bool operator==(const Player& rhs) const;

    friend QVariantList& operator<<(QVariantList& list, const Player& p)
    {
        return list << p.name << p.moneyPaidIn << p.moneyWon << p.competitionsParticipated.size();
    }

    QVariant getCompetitionsIndexesAsVariant() const;
    QVariant getCompetitionsMoneyWonAsVariant() const;
};

#endif // PLAYER_H
