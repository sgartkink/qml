import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

Row {
    height: parent.height
    width: parent.width
    id: layoutqwe

//    Repeater {
//        model: {
//            columnsId: ["rPlace", "rName", "rWins", "rLost"]
//            names: ["Place", "Name", "Wins", "Lost"]
//        }

        Column {
            id: columnsId
            width: parent.width/5
            height: 30
            Text {
                id: tPlace
                text: "Place"
            }
        }
//    }

    Column {
        id: rPlace
        width: parent.width/5
        height: 30


    }

    Column {
        id: rName
        width: parent.width/5
        height: 30

        Text {
            id: tName
            text: qsTr("Name")
        }
    }

    Column {
        id: rWins
        width: parent.width/5
        height: 30

        Text {
            id: tWins
            text: qsTr("Wins")
        }
    }

    Column {
        id: rLost
        width: parent.width/5
        height: 30

        Text {
            id: tLost
            text: qsTr("Lost")
        }
    }
}
