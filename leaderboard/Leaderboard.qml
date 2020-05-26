import QtQuick 2.11
import QtQuick.Controls 2.4
import "../popups"

Item {
    id: leaderboardMain
    anchors.fill: parent

    TopBarPlayers { id: topBarPlayersQML }
    PlayersList { id: playerListQML }
    Button {
        id: btnAddPlayer
        text: qsTr("Add new player")
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }

        onClicked: popup.open()

        contentItem: Text {
            text: btnAddPlayer.text
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

    PopupAddPlayer { id: popup }
}
