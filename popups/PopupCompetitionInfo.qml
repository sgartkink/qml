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
    onAboutToHide: sortFilterCompetition.setShowPlayersWhoIncludeIndex(true)

    NumberAnimation {
        id: showAnimation
        target: popup
        property: "opacity"
        to: 1
        duration: 300
        running: false
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

            ListViewCompetitionInfo {}

            Button {
                id: btnAddPlayer
                height: 30
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                text: qsTr("Add player in this competition")
                onClicked: {
                    sortFilterCompetition.setShowPlayersWhoIncludeIndex(false)
                    playersMightBeAddedToComp.state = "show"
                }
            }

            PlayersMightBeAddedToComp { id: playersMightBeAddedToComp }
        }
    }
}
