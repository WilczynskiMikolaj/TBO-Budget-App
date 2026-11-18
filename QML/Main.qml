import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 1472
    height: 960
    minimumWidth: 1220
    minimumHeight: 720
    visible: true
    title: "TBO"
    color: "#FAF9F6"

    property int currentPage: 0
    readonly property var pageTitles: ["Skoroszyt", "Kalkulator", "Ostatnie pliki"]

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Sidebar {
            Layout.preferredWidth: 290
            Layout.fillHeight: true
            currentIndex: window.currentPage
            onPageSelected: function(index) { window.currentPage = index }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#FAF9F6"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 26
                spacing: 25

                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 150
                    spacing: 15

                    Text {
                            text: window.pageTitles[window.currentPage]
                            font.pixelSize: 44
                            font.bold: true
                            color: "#091B15"
                        }

                    Item { Layout.fillWidth: true }

                    AppButton {
                        label: "Otwórz CSV"
                        symbol: "▤"
                        primary: false
                        onClicked: demoDialog.open()
                        visible: window.currentPage === 0
                    }

                    AppButton {
                        label: "Nowy wpis"
                        symbol: "+"
                        primary: true
                        onClicked: demoDialog.open()
                        visible: window.currentPage === 0
                    }
                }

                TransactionsTable {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    visible: window.currentPage === 0
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    visible: window.currentPage !== 0
                    radius: 14
                    color: "#FFFFFF"
                    border.color: "#DAE2DC"
                    Text {
                        anchors.centerIn: parent
                        text: "Widok „" + window.pageTitles[window.currentPage] + "” TBD"
                        font.pixelSize: 22
                        color: "#738078"
                    }
                }
            }
        }
    }

    Dialog {
        id: demoDialog
        title: "TBD"
        modal: true
        anchors.centerIn: Overlay.overlay
        width: 390
        standardButtons: Dialog.Ok
        contentItem: Label {
            padding: 18
            wrapMode: Text.Wrap
            text: "TBD"
        }
    }
}
