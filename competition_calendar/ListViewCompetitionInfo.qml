import QtQuick 2.11

ListView {
    id: list
    anchors {
        top: topBarCompetitionInfo.bottom
        left: parent.left
        right: parent.right
        bottom: btnAddPlayer.top
    }

    model: sortFilterCompetition

    delegate: Rectangle {
        width: parent.width
        height: 30
        color: mouseArea.containsMouse ? "green" : "black"

        Rectangle {
            id: list_rName
            height: parent.height
            width: parent.width/3
            color: parent.color

            Text {
                id: list_tName
                anchors.centerIn: parent
                color: "gold"
                text: model.name
            }
        }

        Rectangle {
            id: list_rMoneyPaidIn
            height: parent.height
            width: parent.width/3
            color: parent.color
            anchors.left: list_rName.right

            Text {
                id: list_tMoneyPaidIn
                anchors.centerIn: parent
                color: "gold"
                text: playersList.getPlayerCompetitionsInfo(model.number, indexChoosenCompetition)[1]
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
                text: playersList.getPlayerCompetitionsInfo(model.number, indexChoosenCompetition)[2]
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
        }
    }
}
