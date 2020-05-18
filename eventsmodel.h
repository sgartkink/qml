#ifndef EVENTSMODEL_H
#define EVENTSMODEL_H

#include <QAbstractListModel>

class EventsList;

class EventsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(EventsList *list READ getEventsList WRITE setEventsList)

public:
    explicit EventsModel(QObject *parent = nullptr);

    enum {
        DateRole,
        WinnerRole,
        NameRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    EventsList *getEventsList() const;
    void setEventsList(EventsList *eventsList_);

private:
    EventsList * eventsList;
};

#endif // EVENTSMODEL_H
