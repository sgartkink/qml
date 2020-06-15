#ifndef COMPETITION_H
#define COMPETITION_H

#include <QDateTime>
#include <QVariantList>

struct Competition {
    QDateTime date;
    unsigned int prizePool;
    unsigned int jackpot;

    bool operator==(const Competition& rhs) const;

    friend QVariantList& operator<<(QVariantList& list, const Competition& c)
    {
        return list << c.date << c.prizePool << c.jackpot;
    }
};

#endif // COMPETITION_H
