#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H

#include <QObject>
#include <QVector>
#include <QVariantList>
#include <QList>

class WriteReadPlayersData;

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

    QVariant getCompetitionsIndexesAsVariant() const
    {
        QList<QVariant> list;
        for (auto it = competitionsParticipated.begin(); it != competitionsParticipated.end(); ++it)
        {
            QVariant variant((*it).index);
            list.append(variant);
        }
        QVariant variant(list);
        return variant;
    }

    QVariant getCompetitionsMoneyWonAsVariant() const
    {
        QList<QVariant> list;
        for (auto it = competitionsParticipated.begin(); it != competitionsParticipated.end(); ++it)
        {
            QVariant variant((*it).moneyWon);
            list.append(variant);
        }
        QVariant variant(list);
        return variant;
    }
};

class PlayersList : public QObject
{
    Q_OBJECT
public:
    explicit PlayersList(QObject *parent = nullptr);

    QVector<Player> getPlayers() const;
    Q_INVOKABLE QVariantList getPlayer(const int & index) const;
    Q_INVOKABLE QVariantList getPlayerCompetitionsInfo(int player, int index) const;
    Q_INVOKABLE int amoutOfCompetitions(int index) const;
    Q_INVOKABLE void saveData();

    bool setPlayerAt(int index, const Player &player);

signals:
    void prePlayerAppended();
    void postPlayerAppended();

    void prePlayerRemoved(int index);
    void postPlayerRemoved();

    void playerNameEdited(const int &index, const int &role, const QVariant &value);

    Q_SIGNAL void dataSaved() const;
    Q_SIGNAL void dataNotSaved() const;

public slots:
    void appendPlayer(QString name = "", unsigned int moneyPaidIn = 0, int moneyWon = 0);
    void removePlayer(int index);

private:
    QVector<Player> players;
    WriteReadPlayersData * writeReadPlayersData = nullptr;
};

#endif // PLAYERSLIST_H
