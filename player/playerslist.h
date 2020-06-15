#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H

#include <QObject>
#include <QVector>
#include <QVariantList>

#include "player.h"

class WriteReadPlayersData;

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
    Q_INVOKABLE void addCompetitionToPlayer(int playerIndex, int competitionIndex, unsigned int moneyPaidIn, int moneyWon);

    bool setPlayerAt(int index, const Player &player);

signals:
    void prePlayerAppended();
    void postPlayerAppended();

    void prePlayerRemoved(int index);
    void postPlayerRemoved();

    void playerChanged(const int &index, const int &role);

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
