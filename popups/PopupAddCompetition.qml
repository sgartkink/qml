import QtQuick 2.11
import QtQuick.Controls 2.4
import "../competition_calendar"

Popup {
    id: popup
    y: topBarCompetitionsQML.height
    width: competitionsListQML.width-40
    height: competitionsListQML.height-40
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

        Row {
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            height: 30
            spacing: 20

            Text {
                color: "gold"
                text: qsTr("Date:")
                visible: !calendar.visible
                anchors.verticalCenter: parent.verticalCenter
            }

            Text {
                text: calendar.selectedDate.getDate() + "/"
                      + (calendar.selectedDate.getMonth()+1 < 10 ? "0" : "")
                      + (calendar.selectedDate.getMonth()+1) + "/"
                      + calendar.selectedDate.getFullYear()
                color: "gold"
                visible: !calendar.visible
                anchors.verticalCenter: parent.verticalCenter
            }

            Button {
                id: btnShowCalendar
                height: parent.height
                text: "Show calendar"
                visible: !calendar.visible
                onClicked: calendar.visible = true
            }

            CalendarAddCompetition {
                id: calendar;
                visible: false
                onClicked: visible = false
            }
        }

        Button {
            id: popup_btnAddPlayer
            anchors {
                left: parent.left
                right: parent.right
                bottom: popup_btnClose.top
            }
            text: "Add competition"
            onClicked: {
                competitionsList.appendCompetition(calendar.selectedDate)
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
