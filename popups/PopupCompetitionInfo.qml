import QtQuick 2.11
import QtQuick.Controls 2.4
import "../competition_calendar/"

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
            id: popup_RDate
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
            height: 30
            Text {
                readonly property date competitionDate: competitionsList.getCompetition(indexChoosenCompetition)[0]
                id: popup_TDate
                text: popup.visible ? "DATE: " + competitionDate.getDate() + "/"
                                      + (competitionDate.getMonth()+1 < 10 ? "0" : "") + (competitionDate.getMonth()+1) + "/"
                                      +  competitionDate.getFullYear()
                                      + (competitionDate.getHours() < 10 ? "0" : "") + " " + competitionDate.getHours() + ":"
                                      + (competitionDate.getMinutes() < 10 ? "0" : "") + competitionDate.getMinutes() : ""
                anchors.centerIn: parent
            }
        }
        Rectangle {
            id: popup_RPrizePool
            width: parent.width/2
            anchors {
                top: popup_RDate.bottom
                left: parent.left
            }
            height: 30
            Text {
                id: popup_TPrizePool
                text: popup.visible ? "PRIZE POOL: " + competitionsList.getCompetition(indexChoosenCompetition)[1] : ""
                anchors.centerIn: parent
            }
        }
        Rectangle {
            id: popup_RJackpot
            width: parent.width/2
            anchors {
                top: popup_RDate.bottom
                left: popup_RPrizePool.right
            }
            height: 30
            Text {
                id: popup_TJackpot
                text: popup.visible ? "JACKPOT: " + competitionsList.getCompetition(indexChoosenCompetition)[2] : ""
                anchors.centerIn: parent
            }
        }

        Rectangle {
            id: rPLayersList
            anchors {
                top: popup_RJackpot.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            TopBarCompetitionInfo { id: topBarCompetitionInfo }

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

            Button {
                id: btnAddPlayer
                height: 30
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                text: qsTr("Add player in this competition")
                onClicked: rectangle.state = "show"
            }

            Rectangle {
                id: rectangle
                anchors.fill: parent
                color: "green"
                states: [
                    State {
                        name: "hide"
                        PropertyChanges { target: rectangle; y: 0; z: -1 }
                    },
                    State {
                        name: "show"
                        PropertyChanges { target: rectangle; y: btnAddPlayer.y; z: 1 }
                    }
                ]
                transitions: [
                    Transition {
                        from: "hide"
                        to: "show"
                        PropertyAnimation {
                            target: rectangle
                            property: "y"
                            duration: 500
                        }
                    },
                    Transition {
                        from: "show"
                        to: "hide"
                        PropertyAnimation {
                            target: rectangle
                            property: "y"
                            duration: 500
                        }
                    }
                ]
                state: "hide"

                GridView {
                    anchors.fill: parent
                    width: parent.width
                    model: playersModel

                    delegate: Column {
                        spacing: 20

                        Rectangle {
                            width: 200
                            height: 100
                            color: "black"
                            border.color: "gold"
                            Text {
                                text: model.name
                                anchors.centerIn: parent
                                color: "gold"
                            }
                        }
                    }
                }

                Button {
                    anchors {
                        left: parent.left
                        right: parent.right
                        bottom: parent.bottom
                    }
                    text: "hide"
                    onClicked: rectangle.state = "hide"
                }
            }
        }
    }
}
