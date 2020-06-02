import QtQuick 2.11
import QtQuick.Controls 2.4
import SortFilterPlayers 1.0
import "../leaderboard/"

Popup {
    width: parent.width-40
    height: parent.height-40
    margins: 20
    opacity: 0.7

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
            z: 1
            Text {
                id: popup_TName
                text: popup.visible ? "NAME: " + playersList.getPlayer(indexChoosenPlayer)[0] : ""
                anchors.centerIn: parent
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
                text: popup.visible ? "MONEY PAID IN: " + playersList.getPlayer(indexChoosenPlayer)[1] : ""
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
                text: popup.visible ? "MONEY WON: " + playersList.getPlayer(indexChoosenPlayer)[2] : ""
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
                text: popup.visible ?
                          "FREQUENCY: " + playersList.getPlayer(indexChoosenPlayer)[3] + "/"
                          + competitionsList.getCompetitionsAmount()
                          + " ("
                          + parseInt(playersList.getPlayer(indexChoosenPlayer)[3]/competitionsList.getCompetitionsAmount()*100)
                          + "%)" : ""
                anchors.centerIn: parent
            }
        }

        Rectangle {
            anchors {
                top: popup_RFrequency.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            TopBarPlayerInfo { id: topBarPlayerInfo }

            ListView {
                id: list
                anchors {
                    top: topBarPlayerInfo.bottom
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }

                model: playersList.amoutOfCompetitions(indexChoosenPlayer)

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

                    Rectangle {
                        id: list_rDate
                        height: parent.height
                        width: parent.width/3

                        Text {
                            id: list_tDate
                            anchors.centerIn: parent
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
                        anchors.left: list_rDate.right

                        Text {
                            id: list_tMoneyPaidIn
                            anchors.centerIn: parent
                            text: playersList.getPlayerCompetitionsInfo(indexChoosenPlayer, index)[1]
                        }
                    }

                    Rectangle {
                        id: list_rMoneyWon
                        height: parent.height
                        width: parent.width/3
                        anchors.left: list_rMoneyPaidIn.right

                        Text {
                            id: list_tMoneyWon
                            anchors.centerIn: parent
                            text: playersList.getPlayerCompetitionsInfo(indexChoosenPlayer, index)[2]
                        }
                    }
                }
            }
        }
    }
}
