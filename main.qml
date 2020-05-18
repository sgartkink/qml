import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.1

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    StackLayout {
        id: layout
        currentIndex: 0
        anchors.fill: parent
        implicitHeight: parent.height
        implicitWidth: parent.width

        Column {
            height: parent.height
            width: parent.width

            Row {
                width: parent.width
                height: parent.height*0.05
                TopBar {
                    id: topBar
                }
            }

            Row {
                width: parent.width
                height: parent.height*0.85
                PlayersList {
                    id: qmlPlayersList
                }
            }

            Row {
                width: parent.width
                height: parent.height*0.1
                Button {
                    text: qsTr("Add new player")
                    onClicked:  {
                        addNewPlayerLoader.source = "AddNewPlayer.qml"
                        layout.currentIndex = 1
                    }
                }

                ToolSeparator {}

                Button {
                    text: qsTr("Show events")
                    onClicked: {
                        qmlEventsList.startTimer()
                        layout.currentIndex = 3
                    }
                }
            }
        }

        Loader {
            id: addNewPlayerLoader
        }

        InfoAboutPlayer {
            id: infoAboutPlayer
            height: parent.height
            width: parent.width
        }

        EventsList {
            id: qmlEventsList
            height: parent.height
            width: parent.width
        }
    }
}
