import QtQuick 2.11
import QtQuick.Controls 2.4
import "../popups"

Rectangle {
    anchors {
        top: parent.bottom
        left: parent.left
        right: parent.right
        bottom: parent.bottom
    }
    z: 1

    color: "green"
    states: [
        State {
            name: "hide"
            PropertyChanges { target: playersMightBeAddedToComp; anchors.top: parent.bottom; visible: false }
        },
        State {
            name: "show"
            PropertyChanges { target: playersMightBeAddedToComp; anchors.top: parent.top; visible: true }
        }
    ]
    transitions: Transition {
        AnchorAnimation { duration: 200; easing.type: Easing.Linear }
    }
    state: "hide"

    GridView {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: btnHide.top
            margins: 10
        }
        cellWidth: 110

        model: sortFilterCompetition

        delegate: Rectangle {
                width: 100
                height: txt.height*3
                color: "black"
                border.color: "gold"
                Text {
                    id: txt
                    text: model.name
                    anchors.centerIn: parent
                    color: "gold"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        popupAddPlayerToCompetition.setProperties(model.name, model.number)
                        popupAddPlayerToCompetition.open()
                    }
                }
            }
    }

    PopupAddPlayerToCompetition { id: popupAddPlayerToCompetition }

    Button {
        id: btnHide
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        text: "hide"
        height: 30
        onClicked: {
            sortFilterCompetition.setShowPlayersWhoIncludeIndex(true)
            playersMightBeAddedToComp.state = "hide"
        }
    }
}
