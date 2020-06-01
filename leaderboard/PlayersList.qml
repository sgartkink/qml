import QtQuick 2.11
import QtQuick.Controls 2.4
import PlayersModel 1.0
import SortFilterPlayers 1.0
import "../popups"

Item {
    id: playersListMain
    anchors {
        top: topBarPlayersQML.bottom
        left: parent.left
        right: parent.right
        bottom: btnAddPlayer.top
    }
    property int indexChoosenPlayer: 0

    ListView {
        id: list
        anchors.fill: parent

        Label {
            anchors.fill: parent
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            visible: parent.count == 0
            text: qsTr("Nothing to show yet!")
            font.bold: true
        }



//        model: SortFilterPlayers {}

        model: sortFilterPlayers

//        model: PlayersModel {
//            list: playersList
//        }

//        Component.onCompleted: {
//            sortFilterPlayers.setSourceModelFromQML(model)
//            model: sortFilterPlayers
//        }

//        model: PlayersModel

        delegate: Rectangle {
            width: parent.width
            color: mouseArea.containsMouse ? "green" : "black"
            height: 30

            Rectangle {
                id: rNr
                implicitWidth: topBarPlayersQML.rNrWidth
                height: 30
                color: parent.color
                Text {
                    id: tPlace
                    color: "gold"
                    text: index+1
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: rName
                implicitWidth: (parent.width-rNr.width)/3
                height: 30
                color: parent.color
                anchors.left: rNr.right
                Text {
                    id: tName
                    color: "gold"
                    text: model.name
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: rMoneyWon
                implicitWidth: (parent.width-rNr.width)/3
                height: 30
                color: parent.color
                anchors.left: rName.right
                Text {
                    id: tMoneyWon
                    color: "gold"
                    text: model.moneyWon
                    anchors.centerIn: parent
                }
            }

            Rectangle {
                id: rFrequency
                implicitWidth: (parent.width-rNr.width)/3
                height: 30
                color: parent.color
                anchors.left: rMoneyWon.right
                Text {
                    id: tFrequency
                    color: "gold"
                    text: model.frequency
                    anchors.centerIn: parent
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    playersListMain.indexChoosenPlayer = index
                    popup.open()
                }
            }
        }
    }

    PopupPlayerInfo { id: popup }
}
