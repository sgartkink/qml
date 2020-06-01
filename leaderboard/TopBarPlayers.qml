import QtQuick 2.11
import QtQuick.Controls 2.4

Item {
    id: topBarMain
    height: rNr.height
    z: 1
    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
    }
    readonly property int rNrWidth: rNr.width

    Rectangle {
        id: rNr
        implicitWidth: tNr.width+10
        height: 30
        color: "black"
        Text {
            id: tNr
            color: "gold"
            text: qsTr("Nr")
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: rName
        implicitWidth: (parent.width-rNr.width)/3
        height: 30
        color: "black"
        anchors.left: rNr.right
        Text {
            id: tName
            color: "gold"
            text: qsTr("Name")
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: rMoneyWon
        implicitWidth: (parent.width-rNr.width)/3
        height: 30
        color: "black"
        anchors.left: rName.right
        Text {
            id: tMoneyWon
            color: "gold"
            text: qsTr("Money won (zł)")
            anchors.centerIn: parent
        }
        Image {
            id: arrowUp
            width: 30
            height: 10
            opacity: 1
            anchors {
                left: tMoneyWon.right
                verticalCenter: parent.verticalCenter
            }
            transform: Rotation {
                angle: 90
                origin.x: arrowUp.width/2
                origin.y: arrowUp.height/2
            }
            source: "../images/arrow.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    sortFilterPlayers.toggleOrderSorting(0)
                    arrowUp.opacity = 1
                }
            }
        }
        Image {
            id: arrowDown
            width: 30
            height: 10
            opacity: arrowUp.opacity === 1 ? 0.3 : 1
            anchors {
                left: arrowUp.right
                verticalCenter: parent.verticalCenter
            }
            transform: Rotation {
                angle: 270
                origin.x: arrowDown.width/2
                origin.y: arrowDown.height/2
            }
            source: "../images/arrow.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    sortFilterPlayers.toggleOrderSorting(1)
                    arrowUp.opacity = 0.3
                }
            }
        }
    }

    Rectangle {
        id: rFrequency
        implicitWidth: (parent.width-rNr.width)/3
        height: 30
        color: "black"
        anchors.left: rMoneyWon.right
        Text {
            id: tFrequency
            color: "gold"
            text: qsTr("Frequency")
            anchors.centerIn: parent
        }
    }
}
