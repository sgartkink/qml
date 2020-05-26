#ifndef EVENTSLIST_H
#define EVENTSLIST_H

#include <QObject>
#include <QDateTime>
#include <QVariantList>
#include <QVector>

struct Competition {
    QDateTime date;
    unsigned int prizePool;
    unsigned int jackpot;

    bool operator==(const Competition& rhs) const
    {
        if (date == rhs.date && prizePool == rhs.prizePool && jackpot == rhs.jackpot)
            return true;
        return false;
    }

    friend QVariantList& operator<<(QVariantList& list, const Competition& c)
    {
        return list << c.date << c.prizePool << c.jackpot;
    }
};

class CompetitionsList : public QObject
{
    Q_OBJECT
public:
    explicit CompetitionsList(QObject *parent = nullptr);

    Q_INVOKABLE QVariantList getCompetition(int index) const;
    Q_INVOKABLE void appendCompetition(QDateTime date = QDateTime(), unsigned int prizePool = 0, unsigned int jackpot = 0);
    Q_INVOKABLE int getCompetitionsAmount() const;
    Q_INVOKABLE QDateTime getCompetitionDate(int index) const;

    QVector<Competition> getCompetitions() const;

    bool setCompetitionAt(int index, const Competition &player);

signals:
    void preCompetitionAppended();
    void postCompetitionAppended();

    void preCompetitionRemoved(int index);
    void postCompetitionRemoved();

public slots:

private:
    QVector<Competition> competitions;
};

#endif // EVENTSLIST_H
