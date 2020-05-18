#ifndef EVENTSLIST_H
#define EVENTSLIST_H

#include <QObject>
#include <QDateTime>
#include <QVariantList>
#include <QVector>

struct Event {
    QDateTime date;
    QString winner;
    QString name;

    bool operator==(const Event& rhs) const
    {
        if (date == rhs.date && winner == rhs.winner && name == rhs.name)
            return true;
        return false;
    }

    friend QVariantList& operator<<(QVariantList& list, const Event& e)
    {
        return list << e.date << e.winner << e.name;
    }
};

class EventsList : public QObject
{
    Q_OBJECT
public:
    explicit EventsList(QObject *parent = nullptr);

    Q_INVOKABLE QVariantList getEvent(int index) const;
    Q_INVOKABLE void appendEvent(QDateTime date = QDateTime(), QString winner = "", QString name = "");
    Q_INVOKABLE void removeEvent(int index);

    QVector<Event> getEvents() const;

    bool setEventAt(int index, const Event &player);

signals:
    void preEventAppended();
    void postEventAppended();

    void preEventRemoved(int index);
    void postEventRemoved();

public slots:

private:
    QVector<Event> events;
};

#endif // EVENTSLIST_H
