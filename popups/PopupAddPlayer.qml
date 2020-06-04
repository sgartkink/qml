import QtQuick 2.11
import QtQuick.Controls 2.4

Popup {
    id: popup
    y: topBarPlayersQML.height
    width: playerListQML.width-40
    height: playerListQML.height-40
    margins: 20
    opacity: 0
    Component.onCompleted: open()

    onClosed: popupLoader.active = false

    onAboutToShow: showAnimation.running = true

    NumberAnimation {
        id: showAnimation
        target: popup
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

        states: [
            State {
                when: popup_TName.text === ""
                PropertyChanges { target: popup_btnAddPlayer; enabled: false; }
            },
            State {
                when: popup_TName.text !== ""
                PropertyChanges { target: popup_btnAddPlayer; enabled: true; }
            }
        ]

        Row {
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            height: 30
            spacing: 20

            Text {
                color: "gold"
                text: qsTr("Name:")
                anchors.verticalCenter: parent.verticalCenter
            }
            TextField {
                id: popup_TName
                height: 30
                color: "gold"
                text: popup.visible ? "" : ""
            }
        }

        Button {
            id: popup_btnAddPlayer
            anchors {
                left: parent.left
                right: parent.right
                bottom: popup_btnClose.top
            }
            text: "Add player"
            onClicked: {
                playersList.appendPlayer(popup_TName.text)
                popup.close()
            }
        }

        Button {
            id: popup_btnClose
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            text: "Close"
            onClicked: popup.close()
        }
    }
}
