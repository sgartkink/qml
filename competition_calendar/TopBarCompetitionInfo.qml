import QtQuick 2.11
import QtQuick.Controls 2.4

Item {
    id: topBarMain
    height: 30
    z: 1
    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
    }

    Rectangle {
        id: rName
        implicitWidth: parent.width/3
        height: 30
        color: "black"
        Text {
            id: tName
            color: "gold"
            text: qsTr("Name")
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: rMoneyPaidIn
        implicitWidth: parent.width/3
        height: 30
        color: "black"
        anchors.left: rName.right
        Text {
            id: tMoneyPaidIn
            color: "gold"
            text: qsTr("Money paid in (zł)")
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: rMoneyWon
        implicitWidth: parent.width/3
        height: 30
        color: "black"
        anchors.left: rMoneyPaidIn.right
        Text {
            id: tMoneyWon
            color: "gold"
            text: qsTr("Money won (zł)")
            anchors.centerIn: parent
        }
    }
}
