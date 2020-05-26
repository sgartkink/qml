import QtQuick 2.11
import QtQuick.Controls 2.4
import "../popups"

Item {
    id: competitionCalendarMain
    anchors.fill: parent

    TopBarCompetitions { id: topBarCompetitionsQML }
    CompetitionsList { id: competitionsListQML }

    Button {
        id: btnAddCompetition
        text: qsTr("Add new competition")
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }

        onClicked: popup.open()

        contentItem: Text {
            text: btnAddCompetition.text
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "gold"
        }

        background: Rectangle {
            color: "black"
            border.color: "gold"
            radius: 10
        }
    }

    PopupAddCompetition { id: popup }
}
