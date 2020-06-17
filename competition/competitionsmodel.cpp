#include "competitionsmodel.h"
#include "competitionslist.h"

CompetitionsModel::CompetitionsModel(QObject *parent)
    : QAbstractListModel(parent), competitionsList(nullptr)
{
}

int CompetitionsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !competitionsList)
        return 0;

    return competitionsList->getCompetitions().size();
}

QVariant CompetitionsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !competitionsList)
        return QVariant();

    const Competition competition = competitionsList->getCompetitions().at(index.row());
    switch (role) {
    case DateRole:
        return QVariant(competition.date);
    case PrizePoolRole:
        return QVariant(competition.prizePool);
    case JackpotRole:
        return QVariant(competition.jackpot);
    }

    return QVariant();
}

bool CompetitionsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!competitionsList)
        return false;

    Competition competition = competitionsList->getCompetitions().at(index.row());
    switch (role) {
    case DateRole:
        competition.date = value.toDateTime();
        break;
    case PrizePoolRole:
        competition.prizePool = value.toUInt();
        break;
    case JackpotRole:
        competition.jackpot = value.toUInt();
        break;
    }

    if (data(index, role) != value) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CompetitionsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> CompetitionsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DateRole] = "date";
    names[PrizePoolRole] = "prizePool";
    names[JackpotRole] = "jackpot";
    return names;
}

CompetitionsList *CompetitionsModel::getCompetitionsList() const
{
    return competitionsList;
}

void CompetitionsModel::setCompetitionsList(CompetitionsList *competitionsList_)
{
    beginResetModel();

    if (competitionsList)
        competitionsList->disconnect(this);

    competitionsList = competitionsList_;

    if (competitionsList)
    {
        connect(competitionsList, &CompetitionsList::preCompetitionAppended, this, [=](){
            const int index = competitionsList->getCompetitions().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(competitionsList, &CompetitionsList::postCompetitionAppended, this, [=](){
            endInsertRows();
        });
        connect(competitionsList, &CompetitionsList::preCompetitionRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(competitionsList, &CompetitionsList::postCompetitionRemoved, this, [=](){
            endRemoveRows();
        });
    }

    endResetModel();
}
