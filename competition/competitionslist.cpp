#include "competitionslist.h"
#include "competitionsmodel.h"
#include "writereadcompetitionsdata.h"

CompetitionsList::CompetitionsList(const PlayersList &pL, QObject *parent)
    : QObject(parent)
{
    writeReadCompetitionsData = new WriteReadCompetitionsData();
    competitions = writeReadCompetitionsData->readFromFile();

//    QDateTime time { QDateTime::currentDateTime() };
//    competitions.append({ time, 0, 5000 });
//    QDateTime time2 = time.addDays(2);
//    competitions.append({ time2, 0, 7000 });

    for (int i = 0; i < competitions.size(); i++)
        competitions[i].prizePool = pL.getPlayersMoneyPaidInCompetition(i);
}

QVariantList CompetitionsList::getCompetition(int index) const
{
    QVariantList list;
    list << competitions[index];
    return list;
}

QDateTime CompetitionsList::getCompetitionDate(int index) const
{
    return competitions[index].date;
}

int CompetitionsList::getCompetitionsAmount() const
{
    return competitions.size();
}

void CompetitionsList::saveData()
{
    if (writeReadCompetitionsData->writeToFile(competitions))
        emit dataSaved();
    else
        emit dataNotSaved();
}

void CompetitionsList::appendCompetition(QDateTime date, unsigned int prizePool, unsigned int jackpot)
{
    emit preCompetitionAppended();

    Competition competition;
    competition.date = date;
    competition.prizePool = prizePool;
    competition.jackpot = jackpot;
    competitions.append(competition);

    emit postCompetitionAppended();
}

void CompetitionsList::addMoneyToCompetition(int competitionIndex, unsigned int moneyPaidIn)
{
    competitions[competitionIndex].prizePool += moneyPaidIn;
}

void CompetitionsList::removeCompetition(int index)
{
    emit preCompetitionRemoved(index);

    competitions.removeAt(index);

    emit postCompetitionRemoved();
}

const QVector<Competition> &CompetitionsList::getCompetitions() const
{
    return competitions;
}

bool CompetitionsList::setCompetitionAt(int index, const Competition &competition)
{
    if (index < 0 || index >= competitions.size())
        return false;

    const Competition & oldCompetition = competitions.at(index);
    if (competition == oldCompetition)
        return false;

    competitions[index] = competition;
    return true;
}
