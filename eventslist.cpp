#include "eventslist.h"

EventsList::EventsList(QObject *parent) : QObject(parent)
{
    QDateTime time { QDateTime::currentDateTime() };
    events.append({ time, "", "Test event" });
    QDateTime time2 = time.addDays(2);
    events.append({ time2, "", "Test event2" });
}

QVariantList EventsList::getEvent(int index) const
{
    QVariantList list;
    list << events[index];
    return list;
}

void EventsList::appendEvent(QDateTime date, QString winner, QString name)
{
    emit preEventAppended();

    Event event;
    event.date = date;
    event.winner = winner;
    event.name = name;
    events.append(event);

    emit postEventAppended();
}

void EventsList::removeEvent(int index)
{
    emit preEventRemoved(index);

    events.removeAt(index);

    emit postEventRemoved();
}

QVector<Event> EventsList::getEvents() const
{
    return events;
}

bool EventsList::setEventAt(int index, const Event &player)
{
    if (index < 0 || index >= events.size())
        return false;

    const Event & oldEvent = events.at(index);
    if (player == oldEvent)
        return false;

    events[index] = player;
    return true;
}
