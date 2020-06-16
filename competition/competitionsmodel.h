#ifndef EVENTSMODEL_H
#define EVENTSMODEL_H

#include <QAbstractListModel>

class CompetitionsList;

class CompetitionsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(CompetitionsList *list READ getCompetitionsList WRITE setCompetitionsList NOTIFY competitionChanged)

public:
    explicit CompetitionsModel(QObject *parent = nullptr);

    enum {
        DateRole,
        PrizePoolRole,
        JackpotRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    CompetitionsList *getCompetitionsList() const;
    void setCompetitionsList(CompetitionsList *competitionsList_);

signals:
    void competitionChanged();

private:
    CompetitionsList * competitionsList;
};

#endif // EVENTSMODEL_H
