#ifndef EVENTSLIST_H
#define EVENTSLIST_H

#include <QObject>
#include <QVariantList>
#include <QVector>

#include "competition.h"
#include "../player/playerslist.h"

class WriteReadCompetitionsData;

class CompetitionsList : public QObject
{
    Q_OBJECT
public:
    explicit CompetitionsList(const PlayersList & pL, QObject *parent = nullptr);

    Q_INVOKABLE QVariantList getCompetition(int index) const;
    Q_INVOKABLE QDateTime getCompetitionDate(int index) const;
    Q_INVOKABLE int getCompetitionsAmount() const;

    Q_INVOKABLE void saveData();
    Q_INVOKABLE void appendCompetition(QDateTime date = QDateTime(), unsigned int prizePool = 0, unsigned int jackpot = 0);
    Q_INVOKABLE void addMoneyToCompetition(int competitionIndex, unsigned int moneyPaidIn);

    const QVector<Competition>& getCompetitions() const;
    bool setCompetitionAt(int index, const Competition &competition);

signals:
    void preCompetitionAppended();
    void postCompetitionAppended();

    void preCompetitionRemoved(int index);
    void postCompetitionRemoved();

    Q_SIGNAL void dataSaved() const;
    Q_SIGNAL void dataNotSaved() const;

private:
    QVector<Competition> competitions;
    WriteReadCompetitionsData * writeReadCompetitionsData = nullptr;
};

#endif // EVENTSLIST_H
