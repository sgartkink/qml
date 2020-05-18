import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import PlayersModel 1.0
import SortFilterPlayers 1.0

Frame {
    height: parent.height
    width: parent.width

    ListView {
        id: list
        height: parent.height
        width: parent.width

        model: SortFilterPlayers /*{
            list: playersList
        }*/

//        Connections {
//            target: list.model
//            onDataChanged: {
//                console.log("asdasda")
//            }
//        }

        delegate: Column {
            width: parent.width

            Row {
                width: parent.width

                Text {
                    id: tPlace
                    text: index+1
                    width: parent.width/5
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    id: tName
                    text: model.name
                    width: parent.width/5
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    id: tWins
                    text: model.wins
                    width: parent.width/5
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    id: tLost
                    text: model.lost
                    width: parent.width/5
                    anchors.verticalCenter: parent.verticalCenter
                }
                Button {
                    text: qsTr("Show info")
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        layout.currentIndex = 2
                        infoAboutPlayer.indexOfThisDelegate = model.index
                    }
                }
            }

            Row {
                width: parent.width
                MenuSeparator {
                    width: parent.width
                }
            }
        }
    }
}
