#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H

#include <QObject>
#include <QVector>
#include <QVariantList>
#include <QList>

struct CompetitionsParticipatedInfo
{
    int index;
    unsigned int moneyPaidIn;
    unsigned int moneyWon;

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
    QVector<CompetitionsParticipatedInfo> competitionsParticipated;

    bool operator==(const Player& rhs) const
    {
        if (name == rhs.name && moneyPaidIn == rhs.moneyPaidIn && moneyWon == rhs.moneyWon
                && competitionsParticipated.size() == rhs.competitionsParticipated.size())
            return true;
        return false;
    }

    friend QVariantList& operator<<(QVariantList& list, const Player& p)
    {
        return list << p.name << p.moneyPaidIn << p.moneyWon << p.competitionsParticipated.size();
    }
};

class PlayersList : public QObject
{
    Q_OBJECT
public:
    explicit PlayersList(QObject *parent = nullptr);

    QVector<Player> getPlayers() const;
    Q_INVOKABLE QVariantList getPlayer(const int & index) const;
    Q_INVOKABLE QVariantList getPlayersCompetitions(int player, int index) const;
    Q_INVOKABLE int amoutOfPlayersInCompetition(int index) const;
    Q_INVOKABLE QVector<int> playersInCompetition(int index) const;
    Q_INVOKABLE QVector<int> playersIndexesCompetitions(int index) const;
    Q_INVOKABLE int amoutOfCompetitions(int index) const;

    bool setPlayerAt(int index, const Player &player);

signals:
    void prePlayerAppended();
    void postPlayerAppended();

    void prePlayerRemoved(int index);
    void postPlayerRemoved();

    void playerNameEdited(const int &index, const int &role, const QVariant &value);

public slots:
    void appendPlayer(QString name = "", unsigned int moneyPaidIn = 0, int moneyWon = 0);
    void removePlayer(int index);

private:
    QVector<Player> players;
};

#endif // PLAYERSLIST_H
