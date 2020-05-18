import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Column {
    function resetTextFields()
    {
        tfName.text = ""
    }

    Row {
        Text {
            id: tName
            text: qsTr("Name")
            anchors.verticalCenter: parent.verticalCenter
        }
        TextField {
            id: tfName
            text: ""
        }
    }

    Row {
        Button {
            text: qsTr("Add player")
            onClicked: {
                playersList.appendPlayer(tfName.text)
                resetTextFields()
                layout.currentIndex = 0
            }
        }

        ToolSeparator {}

        Button {
            text: qsTr("Back to menu")
            onClicked: {
                resetTextFields()
                layout.currentIndex = 0
            }
        }
    }
}
