import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import CompetitionsModel 1.0
import "../popups/"

Item {
    id: competitionsListMain
    anchors {
        top: topBarCompetitionsQML.bottom
        left: parent.left
        right: parent.right
        bottom: btnAddCompetition.top
    }
    property int indexChoosenCompetition: 0

    ListView {
        id: list
        height: parent.height
        width: parent.width

        model: CompetitionsModel {
            list: competitionsList
        }

        delegate: Rectangle {
            width: parent.width
            color: mouseArea.containsMouse ? "green" : "black"
            height: 30

            Rectangle {
                id: rNr
                implicitWidth: topBarCompetitionsQML.rNrWidth
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
                    text: model.date.getDate() + "/" + (model.date.getMonth()+1 < 10 ? "0" : "")
                          + (model.date.getMonth()+1) + "/" +  model.date.getFullYear()
                          + " " + model.date.getHours() + ":" + (model.date.getMinutes() < 10 ? "0" : "") + model.date.getMinutes()
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
                    text: model.prizePool
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
                    text: model.jackpot
                    anchors.centerIn: parent
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    competitionsListMain.indexChoosenCompetition = index
                    sortFilterPlayers.setFilterCompetitionIndex(index)
                    popup.open()
                }
            }
        }
    }

    PopupCompetitionInfo { id: popup }
}
