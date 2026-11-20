import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: "#FAF9F6"

    signal fileOpened()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 26
        spacing: 25
        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 150

            Text {
                text: "Kalkulator"
                font.pixelSize: 44
                font.bold: true
                color: "#091B15"
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true

            radius: 14
            color: "#FFFDFC"
            border.color: "#DBE2DD"
        }

        }
}
