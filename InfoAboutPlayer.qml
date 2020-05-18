import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Column {
    property var indexOfThisDelegate: null
    property variant items: []

    onIndexOfThisDelegateChanged: show()

    function show()
    {
        items = playersList.getPlayer(indexOfThisDelegate)
        tfName.text = items[0]
        tWins.text = qsTr("Wins: " + items[1])
        tLost.text = qsTr("Lost: " + items[2])
    }

    Row {
        width: parent.width

        Text {
            id: tName
            text: qsTr("Name:")
            anchors.verticalCenter: parent.verticalCenter
        }
        TextField {
            id: tfName
            text: ""
        }
    }

    Row {
        Text {
            id: tWins
            anchors.verticalCenter: parent.verticalCenter
            text: ""
        }
        Button {
            text: qsTr("Add win")
            onClicked: {
                playersList.addWin(indexOfThisDelegate)
                show()
            }
        }
        Button {
            text: qsTr("Remove win")
            onClicked: {
                playersList.removeWin(indexOfThisDelegate)
                show()
            }
        }
    }

    Row {
        Text {
            id: tLost
            anchors.verticalCenter: parent.verticalCenter
            text: ""
        }
        Button {
            text: qsTr("Add lost")
            onClicked: {
                playersList.addLost(indexOfThisDelegate)
                show()
            }
        }
        Button {
            text: qsTr("Remove lost")
            onClicked: {
                playersList.removeLost(indexOfThisDelegate)
                show()
            }
        }
    }

    Row {
        Button {
            text: qsTr("Save name")
            onClicked: {
                playersList.editName(tfName.text, indexOfThisDelegate, indexOfThisDelegate)
                show()
            }
        }

        Button {
            text: qsTr("Remove player")
            onClicked: {
                layout.currentIndex = 0
                playersList.removePlayer(indexOfThisDelegate)
            }
        }

        Button {
            text: qsTr("Back to menu")
            onClicked: layout.currentIndex = 0
        }
    }
}
