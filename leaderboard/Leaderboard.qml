import QtQuick 2.11
import QtQuick.Controls 2.4
import "../popups"

Item {
    id: leaderboardMain
    anchors.fill: parent

    TopBarPlayers { id: topBarPlayersQML }
    PlayersList { id: playerListQML }
    Row {
        id: buttonsRow
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        spacing: 10

        Button {
            id: btnAddPlayer
            text: qsTr("Add new player")
            anchors.verticalCenter: parent.verticalCenter

            onClicked: popupLoader.active = true

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
        Button {
            id: btnSave
            text: qsTr("Save")

            onClicked: playersList.saveData()

            contentItem: Text {
                text: btnSave.text
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
    }

    Connections {
        target: playersList
        onDataSaved: {
            popupDataText.text = "Data saved"
            popupDataChanged.open()
        }
        onDataNotSaved: {
            popupDataText.text = "ERROR! Data not saved"
            popupDataChanged.open()
        }
    }

    Popup {
        id: popupDataChanged
        y: parent.height/2-height/2
        x: parent.width/2-width/2
        width: 500
        height: 100

        onAboutToShow: showAnimation.running = true

        NumberAnimation {
            id: showAnimation
            target: popupDataChanged
            property: "opacity"
            to: 1
            duration: 300
            running: false
            easing.type: Easing.InOutQuad
        }

        background: Rectangle {
            anchors.fill: parent
            color: "black"
            border.color: "gold"
        }

        contentItem: Item {
            anchors.fill: parent

            Text {
                id: popupDataText
                anchors {
                    centerIn: parent
                }
                color: "gold"
                text: ""
                font.pointSize: 30
            }
        }
    }

    Loader {
        id: popupLoader
        active: false
        anchors.fill: parent
        sourceComponent: PopupAddPlayer {}
    }
}
