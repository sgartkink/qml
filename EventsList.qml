import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import EventsModel 1.0

Frame {
    id: mainFrame
    height: parent.height
    width: parent.width

    property var currentDate: new Date
    function timeChange()
    {
        currentDate = new Date
    }

    function startTimer()
    {
        timer2.running = true
    }

    Timer {
        id: timer2
        interval: 100000
        running: false
        repeat: true
        onTriggered: timeChange()

        function stopTimer()
        {
            timer2.running = false
        }
    }

    ListView {
        id: list
        height: parent.height
        width: parent.width

        model: EventsModel {
            list: eventsList
        }

        delegate: Column {
            width: parent.width
            height: 80

            Frame {
                id: frame
                width: parent.width
                height: parent.height

                Rectangle {
                    id: rectangle
                    width: parent.width
                    height: parent.height
                    color: model.date > mainFrame.currentDate ? "green" : "red"

                    Text {
                        id: tName
                        text: model.name
                        width: parent.width
                        anchors.top: parent.top
                        anchors.left: parent.left
                    }

                    Text {
                        id: tDate
                        text: model.date
                        visible: false
                        width: parent.width
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: tDate.visible = true
                        onExited: tDate.visible = false
                    }
                }
            }
        }

        Button {
            text: qsTr("Back to menu")
            anchors.bottom: parent.bottom
            onClicked: {
                timer2.stopTimer()
                layout.currentIndex = 0
            }
        }
    }
}
