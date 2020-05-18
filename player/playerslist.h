#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H

#include <QObject>
#include <QVector>
#include <QVariantList>

struct Player {
    QString name;
    unsigned int wins;
    unsigned int lost;

    bool operator==(const Player& rhs) const
    {
        if (name == rhs.name && wins == rhs.wins && lost == rhs.lost)
            return true;
        return false;
    }

    friend QVariantList& operator<<(QVariantList& list, const Player& p)
    {
        return list << p.name << p.wins << p.lost;
    }
};

class PlayersList : public QObject
{
    Q_OBJECT
public:
    explicit PlayersList(QObject *parent = nullptr);

    QVector<Player> getPlayers() const;
    Q_INVOKABLE QVariantList getPlayer(int index) const;
    Q_INVOKABLE void editName(const QVariant &value, const int &index);
    Q_INVOKABLE void addWin(int index);
    Q_INVOKABLE void removeWin(int index);
    Q_INVOKABLE void addLost(int index);
    Q_INVOKABLE void removeLost(int index);

    bool setPlayerAt(int index, const Player &player);

signals:
    void prePlayerAppended();
    void postPlayerAppended();

    void prePlayerRemoved(int index);
    void postPlayerRemoved();

    void playerNameEdited(const int &index, const int &role, const QVariant &value);

public slots:
    void appendPlayer(QString name = "", unsigned wins = 0, unsigned int lost = 0);
    void removePlayer(int index);

private:
    QVector<Player> players;
};

#endif // PLAYERSLIST_H
