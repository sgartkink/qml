#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "player/playersmodel.h"
#include "playerslist.h"

#include "player/sortfilterplayers.h"

#include "eventsmodel.h"
#include "eventslist.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    PlayersModel * playersModel = new PlayersModel;
    SortFilterPlayers * sortFilterPlayers = new SortFilterPlayers;
    sortFilterPlayers->setSourceModel(qobject_cast<QAbstractListModel *>(playersModel));
//    sortFilterPlayers->setSortRole(PlayersModel::WinsRole);
//    sortFilterPlayers->setDynamicSortFilter(true);
//    sortFilterPlayers->sort(0, Qt::AscendingOrder);
    engine.rootContext()->setContextProperty(QStringLiteral("sortFilterPlayers"), sortFilterPlayers);

    qmlRegisterType<PlayersModel>("PlayersModel", 1, 0, "PlayersModel");
    qmlRegisterUncreatableType<PlayersList>("PlayersList", 1, 0, "PlayersList", QStringLiteral("Error"));
    PlayersList playersList;
    engine.rootContext()->setContextProperty(QStringLiteral("playersList"), &playersList);
    qmlRegisterType<SortFilterPlayers>("SortFilterPlayers", 1, 0, "SortFilterPlayers");

    qmlRegisterType<EventsModel>("EventsModel", 1, 0, "EventsModel");
    qmlRegisterUncreatableType<EventsList>("EventsList", 1, 0, "EventsList", QStringLiteral("Error"));
    EventsList eventsList;
    engine.rootContext()->setContextProperty(QStringLiteral("eventsList"), &eventsList);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
