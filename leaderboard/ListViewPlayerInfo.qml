import QtQuick 2.11
import QtQuick.Controls 2.4

ListView {
    id: list
    anchors {
        top: topBarPlayerInfo.bottom
        left: parent.left
        right: parent.right
        bottom: parent.bottom
    }

    model: playersList.amoutOfPlayerCompetitions(indexChoosenPlayer)
    readonly property var indexes: playersList.getPlayerCompetitionsIndexes(indexChoosenPlayer)

    Label {
        anchors.fill: parent
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        visible: parent.count == 0
        text: qsTr("Nothing to show yet!")
        font.bold: true
    }

    delegate: Rectangle {
        width: parent.width
        height: 30
        color: mouseArea.containsMouse ? "green" : "black"

        Rectangle {
            id: list_rDate
            height: parent.height
            width: parent.width/3
            color: parent.color

            Text {
                id: list_tDate
                anchors.centerIn: parent
                color: "gold"
                readonly property date competitionDate: competitionsList.
                getCompetitionDate(playersList.getPlayerCompetitionsInfo(indexChoosenPlayer, index)[0])

                text: competitionDate.getDate() + "/" + (competitionDate.getMonth()+1 < 10 ? "0" : "")
                      + (competitionDate.getMonth()+1) + "/" +  competitionDate.getFullYear()
                      + " " + competitionDate.getHours() + ":"
                      + (competitionDate.getMinutes() < 10 ? "0" : "") + competitionDate.getMinutes()
            }
        }

        Rectangle {
            id: list_rMoneyPaidIn
            height: parent.height
            width: parent.width/3
            color: parent.color
            anchors.left: list_rDate.right

            Text {
                id: list_tMoneyPaidIn
                anchors.centerIn: parent
                color: "gold"
                text: playersList.getPlayerCompetitionsInfo(indexChoosenPlayer, list.indexes[index])[1]
            }
        }

        Rectangle {
            id: list_rMoneyWon
            height: parent.height
            width: parent.width/3
            color: parent.color
            anchors.left: list_rMoneyPaidIn.right

            Text {
                id: list_tMoneyWon
                anchors.centerIn: parent
                color: "gold"
                text: playersList.getPlayerCompetitionsInfo(indexChoosenPlayer, list.indexes[index])[2]
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
        }
    }
}
