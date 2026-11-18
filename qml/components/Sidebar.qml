import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root
    property int currentIndex: 0
    signal pageSelected(int index)

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#063B2B" }
        GradientStop { position: 1.0; color: "#0B4933" }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 13
        anchors.rightMargin: 13
        anchors.topMargin: 64
        anchors.bottomMargin: 24
        spacing: 11

        RowLayout {
            Layout.leftMargin: 16
            Layout.bottomMargin: 52
            spacing: 13
            Text {
                text: "₿"
                color: "#A9E89D"
                font.pixelSize: 31
                font.bold: true
            }
            Text {
                text: "TBO"
                color: "white"
                font.pixelSize: 25
                font.bold: true
            }
        }

        Repeater {
            model: ["Skoroszyt", "Kalkulator", "Ostatnie pliki"]
            delegate: Rectangle {
                required property int index
                required property string modelData
                Layout.fillWidth: true
                Layout.preferredHeight: 62
                radius: 13
                color: root.currentIndex === index
                       ? "#2A8158"
                       : (area.containsMouse ? "#175D43" : "transparent")

                Row {
                    anchors.left: parent.left
                    anchors.leftMargin: 21
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 19
                    Text {
                        width: 29
                        text: index === 0 ? "▣" : (index === 1 ? "▦" : "◷")
                        color: "white"
                        font.pixelSize: 26
                    }
                    Text {
                        text: modelData
                        color: "white"
                        font.pixelSize: 21
                        font.bold: root.currentIndex === index
                    }
                }
                MouseArea {
                    id: area
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: root.pageSelected(index)
                }
            }
        }

        Item { Layout.fillHeight: true }

    }
}
