#include "competitionslist.h"

CompetitionsList::CompetitionsList(QObject *parent) : QObject(parent)
{
    QDateTime time { QDateTime::currentDateTime() };
    competitions.append({ time, 15000, 5000 });
    QDateTime time2 = time.addDays(2);
    competitions.append({ time2, 4000, 7000 });
}

QVariantList CompetitionsList::getCompetition(int index) const
{
    QVariantList list;
    list << competitions[index];
    return list;
}

void CompetitionsList::appendCompetition(QDateTime date, unsigned int prizePool, unsigned int jackpot)
{
    emit preCompetitionAppended();

    Competition event;
    event.date = date;
    event.prizePool = prizePool;
    event.jackpot = jackpot;
    competitions.append(event);

    emit postCompetitionAppended();
}

int CompetitionsList::getCompetitionsAmount() const
{
    return competitions.size();
}

QDateTime CompetitionsList::getCompetitionDate(int index) const
{
    return competitions[index].date;
}

QVector<Competition> CompetitionsList::getCompetitions() const
{
    return competitions;
}

bool CompetitionsList::setCompetitionAt(int index, const Competition &player)
{
    if (index < 0 || index >= competitions.size())
        return false;

    const Competition & oldEvent = competitions.at(index);
    if (player == oldEvent)
        return false;

    competitions[index] = player;
    return true;
}
