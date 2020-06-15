#ifndef EVENTSLIST_H
#define EVENTSLIST_H

#include <QObject>
#include <QVariantList>
#include <QVector>

#include "competition.h"

class CompetitionsList : public QObject
{
    Q_OBJECT
public:
    explicit CompetitionsList(QObject *parent = nullptr);

    Q_INVOKABLE QVariantList getCompetition(int index) const;
    Q_INVOKABLE void appendCompetition(QDateTime date = QDateTime(), unsigned int prizePool = 0, unsigned int jackpot = 0);
    Q_INVOKABLE int getCompetitionsAmount() const;
    Q_INVOKABLE QDateTime getCompetitionDate(int index) const;
    Q_INVOKABLE void addMoneyToCompetition(int competitionIndex, unsigned int moneyPaidIn);

    QVector<Competition> getCompetitions() const;

    bool setCompetitionAt(int index, const Competition &player);

signals:
    void preCompetitionAppended();
    void postCompetitionAppended();

    void preCompetitionRemoved(int index);
    void postCompetitionRemoved();

    void competitionChanged(const int &index, const int &role);

private:
    QVector<Competition> competitions;
};

#endif // EVENTSLIST_H
