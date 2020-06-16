import QtQuick 2.11
import QtQuick.Controls 2.4

Popup {
    width: 200
    height: 200
    x: parent.width/2 - width/2
    y: parent.height/2 - height/2

    property string name: ""
    property int number: 0

    function setProperties(name_, number_)
    {
        name = name_
        number = number_
    }

    contentItem: Item {
        anchors.fill: parent
        clip: true

        Text {
            id: tName
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }

            text: name
        }

        Row {
            id: rMoneyPaidIn
            anchors {
                top: tName.bottom
                right: parent.right
                left: parent.left
            }

            Text {
                id: tMoneyPaidIn
                text: qsTr("Money paid in: ")
                anchors.verticalCenter: parent.verticalCenter
                padding: 5
            }
            TextField {
                id: tfMoneyPaidIn
                validator: IntValidator { bottom: 1 }
                width: popupAddPlayerToCompetition.width - tMoneyPaidIn.width - tMoneyPaidIn.padding - padding
                placeholderText: "Enter value"
                padding: 5
            }
        }

        Row {
            id: rMoneyWon
            anchors {
                top: rMoneyPaidIn.bottom
                right: parent.right
                left: parent.left
            }

            Text {
                id: tMoneyWon
                text: qsTr("Money won: ")
                anchors.verticalCenter: parent.verticalCenter
                padding: 5
            }
            TextField {
                id: tfMoneyWon
                validator: IntValidator { bottom: 0 }
                width: popupAddPlayerToCompetition.width - tMoneyWon.width - tMoneyWon.padding - padding
                placeholderText: "Enter value"
                padding: 5
            }
        }
        Text {
            id: tErrorMoneyPaidInEquals0
            anchors {
                top: rMoneyWon.bottom
                horizontalCenter: parent.horizontalCenter
            }
            color: "red"
            text: "Money paid in can not equals to 0!"
            visible: false
        }

        Text {
            id: tErrorUnfilled
            anchors {
                top: tErrorMoneyPaidInEquals0.bottom
                horizontalCenter: parent.horizontalCenter
            }
            color: "red"
            text: "Set money in both fields!"
            visible: false
        }

        Row {
            id: rButton
            anchors {
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }

            Button {
                text: "Add"
                onClicked: {
                    if (tfMoneyPaidIn.text == "0")
                        tErrorMoneyPaidInEquals0.visible = true
                    else if (!tfMoneyPaidIn.acceptableInput || !tfMoneyWon.acceptableInput)
                        tErrorUnfilled.visible = true
                    else
                    {
                        playersList.addCompetitionToPlayer(number, indexChoosenCompetition, tfMoneyPaidIn.text, tfMoneyWon.text)
                        competitionsList.addMoneyToCompetition(indexChoosenCompetition, tfMoneyPaidIn.text)
                        popupAddPlayerToCompetition.close()
                    }
                }
            }
            Button {
                text: "Cancel"
                onClicked: {
                    tErrorMoneyPaidInEquals0.visible = false
                    tErrorUnfilled.visible = false
                    popupAddPlayerToCompetition.close()
                }
            }
        }
    }
}
