#include "eventsmodel.h"
#include "eventslist.h"

EventsModel::EventsModel(QObject *parent)
    : QAbstractListModel(parent), eventsList(nullptr)
{
}

int EventsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !eventsList)
        return 0;

    return eventsList->getEvents().size();
}

QVariant EventsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !eventsList)
        return QVariant();

    const Event event = eventsList->getEvents().at(index.row());
    switch (role) {
    case DateRole:
        return QVariant(event.date);
    case WinnerRole:
        return QVariant(event.winner);
    case NameRole:
        return QVariant(event.name);
    }

    return QVariant();
}

bool EventsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!eventsList)
        return false;

    Event event = eventsList->getEvents().at(index.row());
    switch (role) {
    case DateRole:
        event.date = value.toDateTime();
        break;
    case WinnerRole:
        event.winner = value.toString();
        break;
    case NameRole:
        event.name = value.toString();
        break;
    }

    if (data(index, role) != value) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags EventsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> EventsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DateRole] = "date";
    names[WinnerRole] = "winner";
    names[NameRole] = "name";
    return names;
}

EventsList *EventsModel::getEventsList() const
{
    return eventsList;
}

void EventsModel::setEventsList(EventsList *eventsList_)
{
    beginResetModel();

    if (eventsList)
        eventsList->disconnect(this);

    eventsList = eventsList_;

    if (eventsList)
    {
        connect(eventsList, &EventsList::preEventAppended, this, [=](){
            const int index = eventsList->getEvents().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(eventsList, &EventsList::postEventAppended, this, [=](){
            endInsertRows();
        });
        connect(eventsList, &EventsList::preEventRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(eventsList, &EventsList::postEventRemoved, this, [=](){
            endRemoveRows();
        });
    }

    endResetModel();
}
