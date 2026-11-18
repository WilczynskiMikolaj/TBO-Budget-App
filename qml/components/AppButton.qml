import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root
    property string label: "Button"
    property string symbol: ""
    property bool primary: false
    signal clicked()

    implicitHeight: 58
    implicitWidth: contents.implicitWidth + 48
    radius: 12
    color: area.containsMouse
           ? (primary ? "#087344" : "#EDF5EE")
           : (primary ? "#086638" : "#FAF9F6")
    border.width: primary ? 0 : 1
    border.color: "#0B6943"
    Behavior on color { ColorAnimation { duration: 140 } }

    Row {
        id: contents
        anchors.centerIn: parent
        spacing: 12
        Text {
            text: root.symbol
            visible: text.length > 0
            color: root.primary ? "white" : "#103E2B"
            font.pixelSize: 27
            font.bold: root.primary
        }
        Text {
            text: root.label
            color: root.primary ? "white" : "#10231A"
            font.pixelSize: 20
            font.bold: root.primary
        }
    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: root.clicked()
    }
}
