import QtQuick 2.11
import QtQuick.Controls 2.4
import "../popups"

Item {
    id: competitionCalendarMain
    anchors.fill: parent

    TopBarCompetitions { id: topBarCompetitionsQML }
    CompetitionsList { id: competitionsListQML }

    Row {
        id: buttonsRow
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        spacing: 10

        Button {
            id: btnAddCompetition
            text: qsTr("Add new competition")
            anchors.verticalCenter: parent.verticalCenter

            onClicked: popupLoader.active = true

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
        Button {
            id: btnSave
            text: qsTr("Save")

            onClicked: competitionsList.saveData()

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
        target: competitionsList
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
        sourceComponent: PopupAddCompetition {}
    }
}
