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
                text: "Ostatnie pliki"
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

            Text {
                anchors.centerIn: parent
                text: "Brak ostatnio otwieranych plików"
                font.pixelSize: 20
                color: "#738078"
                visible: backend.recentFiles.length === 0
            }

            ListView {
                anchors.fill: parent
                anchors.margins: 20
                clip: true
                spacing: 10

                model: backend.recentFiles

                delegate: Rectangle {
                    id: fileRow

                    required property string modelData

                    width: ListView.view.width
                    height: 75
                    radius: 10

                    color: mouse.containsMouse
                           ? "#EDF5EE"
                           : "#FFFFFF"

                    border.color: "#DBE2DD"

                    Column {
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - 40
                        spacing: 5

                        Text {
                            text: fileRow.modelData.split("/").pop()
                            font.pixelSize: 20
                            font.bold: true
                            color: "#091B15"
                        }

                        Text {
                            text: fileRow.modelData
                            width: parent.width
                            elide: Text.ElideMiddle
                            font.pixelSize: 14
                            color: "#738078"
                        }
                    }

                    MouseArea {
                        id: mouse
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor

                        onClicked: {
                            if (backend.otworzOstatniPlik(fileRow.modelData)) {
                                root.fileOpened()
                            } else {
                                errorDialog.open()
                            }
                        }
                    }
                }
            }
        }
    }

    Dialog {
        id: errorDialog
        title: "Błąd otwierania pliku"
        modal: true
        anchors.centerIn: Overlay.overlay
        standardButtons: Dialog.Ok

        contentItem: Label {
            text: "Nie udało się otworzyć pliku CSV."
            padding: 18
        }
    }
}
