#include "player.h"

bool Player::operator==(const Player &rhs) const
{
    if (name == rhs.name && moneyPaidIn == rhs.moneyPaidIn && moneyWon == rhs.moneyWon
            && competitionsParticipated.size() == rhs.competitionsParticipated.size())
        return true;
    return false;
}

QVariant Player::getCompetitionsIndexesAsVariant() const
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

QVariant Player::getCompetitionsMoneyWonAsVariant() const
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
