#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>

#include "player/playersmodel.h"
#include "player/playerslist.h"
#include "player/sortfilterplayers.h"

#include "competition/competitionsmodel.h"
#include "competition/competitionslist.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    PlayersModel playersModel;
//    QSortFilterProxyModel * sortFilterPlayers = new QSortFilterProxyModel();
    SortFilterPlayers sortFilterPlayers;
    sortFilterPlayers.setSourceModel(&playersModel);
//    sortFilterPlayers->setSortRole(PlayersModel::WinsRole);
//    sortFilterPlayers->setDynamicSortFilter(true);
//    sortFilterPlayers->sort(0, Qt::AscendingOrder);
    engine.rootContext()->setContextProperty(QStringLiteral("playersModel"), &playersModel);

    qmlRegisterType<PlayersModel>("PlayersModel", 1, 0, "PlayersModel");
    qmlRegisterUncreatableType<PlayersList>("PlayersList", 1, 0, "PlayersList", QStringLiteral("Error"));
    PlayersList playersList;
    engine.rootContext()->setContextProperty(QStringLiteral("playersList"), &playersList);
    qmlRegisterType<SortFilterPlayers>("SortFilterPlayers", 1, 0, "SortFilterPlayers");

    qmlRegisterType<CompetitionsModel>("CompetitionsModel", 1, 0, "CompetitionsModel");
    qmlRegisterUncreatableType<CompetitionsList>("CompetitionsList", 1, 0, "CompetitionsList", QStringLiteral("Error"));
    CompetitionsList competitionsList;
    engine.rootContext()->setContextProperty(QStringLiteral("competitionsList"), &competitionsList);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
