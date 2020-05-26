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
        id: rDate
        implicitWidth: (parent.width-rNr.width)/3
        height: 30
        color: "black"
        anchors.left: rNr.right
        Text {
            id: tDate
            color: "gold"
            text: qsTr("Date")
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: rPrizePool
        implicitWidth: (parent.width-rNr.width)/3
        height: 30
        color: "black"
        anchors.left: rDate.right
        Text {
            id: tPrizePool
            color: "gold"
            text: qsTr("Prize pool")
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: rJackpot
        implicitWidth: (parent.width-rNr.width)/3
        height: 30
        color: "black"
        anchors.left: rPrizePool.right
        Text {
            id: tJackpot
            color: "gold"
            text: qsTr("Jackpot")
            anchors.centerIn: parent
        }
    }
}
