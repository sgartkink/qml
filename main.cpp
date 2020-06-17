#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>

#include "player/playersmodel.h"
#include "player/playerslist.h"
#include "player/sortfilterplayers.h"

#include "competition/competitionsmodel.h"
#include "competition/competitionslist.h"
#include "competition/sortfiltercompetition.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    PlayersModel playersModel;
    engine.rootContext()->setContextProperty(QStringLiteral("playersModel"), &playersModel);

    PlayersList playersList;
    playersModel.setPlayersList(&playersList);
    qmlRegisterUncreatableType<PlayersList>("PlayersList", 1, 0, "PlayersList", QStringLiteral("Error"));
    engine.rootContext()->setContextProperty(QStringLiteral("playersList"), &playersList);

    SortFilterPlayers sortFilterPlayers;
    sortFilterPlayers.setSourceModel(&playersModel);
    sortFilterPlayers.setDynamicSortFilter(true);
    sortFilterPlayers.sort(0, Qt::AscendingOrder);
    engine.rootContext()->setContextProperty(QStringLiteral("sortFilterPlayers"), &sortFilterPlayers);

    SortFilterCompetitions sortFilterCompetition;
    sortFilterCompetition.setSourceModel(&playersModel);
    sortFilterCompetition.setDynamicSortFilter(true);
    sortFilterPlayers.sort(0, Qt::AscendingOrder);
    engine.rootContext()->setContextProperty(QStringLiteral("sortFilterCompetition"), &sortFilterCompetition);

    CompetitionsList competitionsList { playersList };
    qmlRegisterUncreatableType<CompetitionsList>("CompetitionsList", 1, 0, "CompetitionsList", QStringLiteral("Error"));
    engine.rootContext()->setContextProperty(QStringLiteral("competitionsList"), &competitionsList);

    qmlRegisterType<CompetitionsModel>("CompetitionsModel", 1, 0, "CompetitionsModel");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
