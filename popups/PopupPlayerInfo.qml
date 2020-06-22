import QtQuick 2.11
import QtQuick.Controls 2.4
import "../leaderboard/"

Popup {
    id: popup
    width: parent.width-40
    height: parent.height-40
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
    }

    contentItem: Item {
        anchors.fill: parent

        Rectangle {
            id: popup_RName
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
            height: 30

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10
                z: 1
                Text {
                    id: popup_TName
                    anchors.verticalCenter: parent.verticalCenter
                    text: "NAME: "
                }
                TextField {
                    id: popup_TfName
                    height: 30
                    text: popup.visible ? playersList.getPlayer(indexChoosenPlayer)[0] : ""
                }
            }
        }

        Rectangle {
            id: popup_RMoneyPaidIn
            width: parent.width/3
            anchors {
                top: popup_RName.bottom
                left: popup_RMoneyWon.right
            }
            height: 30
            z: 1
            Text {
                id: popup_TMoneyPaidIn
                text: "MONEY PAID IN: " + playersList.getPlayer(indexChoosenPlayer)[1]
                anchors.centerIn: parent
            }
        }

        Rectangle {
            id: popup_RMoneyWon
            width: parent.width/3
            anchors {
                top: popup_RName.bottom
                left: parent.left
            }
            height: 30
            z: 1
            Text {
                id: popup_TMoneyWon
                text: "MONEY WON: " + playersList.getPlayer(indexChoosenPlayer)[2]
                anchors.centerIn: parent
            }
        }

        Rectangle {
            id: popup_RFrequency
            width: parent.width/3
            anchors {
                top: popup_RName.bottom
                left: popup_RMoneyPaidIn.right
            }
            height: 30
            z: 1
            Text {
                id: popup_TFrequency
                text: "FREQUENCY: " + playersList.getPlayer(indexChoosenPlayer)[3] + "/"
                + competitionsList.getCompetitionsAmount()
                + " (" + parseInt(playersList.getPlayer(indexChoosenPlayer)[3]/competitionsList.getCompetitionsAmount()*100) + "%)"
                anchors.centerIn: parent
            }
        }

        Rectangle {
            anchors {
                top: popup_RFrequency.bottom
                left: parent.left
                right: parent.right
                bottom: buttonsRectangle.top
            }

            TopBarPlayerInfo { id: topBarPlayerInfo }

            ListViewPlayerInfo {}
        }

        Rectangle {
            id: buttonsRectangle
            anchors {
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            height: 30
            color: "white"

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    id: btnRemovePlayer
                    text: qsTr("Remove player")
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked: {
                        popup.close()
                        playersList.removePlayer(indexChoosenPlayer)
                    }

                    contentItem: Text {
                        text: btnRemovePlayer.text
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
                    id: btnChangeName
                    text: qsTr("Change name")
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked: playersList.changeName(indexChoosenPlayer, popup_TfName.text)

                    contentItem: Text {
                        text: btnChangeName.text
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
        }
    }
}
