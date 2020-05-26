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
        id: rDate
        implicitWidth: parent.width/3
        height: 30
        color: "black"
        Text {
            id: tDate
            color: "gold"
            text: qsTr("Date")
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: rMoneyPaidIn
        implicitWidth: parent.width/3
        height: 30
        color: "black"
        anchors.left: rDate.right
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
