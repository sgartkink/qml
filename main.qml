import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "black"

    TabView {
        id: tabView
        anchors.fill: parent
        Tab {
            title: "Leaderboard"
            source: "leaderboard/Leaderboard.qml"
        }
        Tab {
            title: "Competition calendar"
            source: "competition_calendar/CompetitionCalendar.qml"
        }
        Tab {
            title: "Settings"
        }

        style: TabViewStyle {
            tab: Rectangle {
                color: styleData.selected ? "green" : "black"
                border.color: "gold"
                implicitWidth: tabView.width/3
                implicitHeight: text.height + 15
                radius: 10
                Text {
                    id: text
                    anchors.centerIn: parent
                    text: styleData.title
                    color: "gold"
                    font.bold: styleData.selected ? true : false
                }
            }
            frame: Rectangle {
                color: "black"
            }
        }
    }
}
