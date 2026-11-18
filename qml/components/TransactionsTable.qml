import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    radius: 14
    color: "#FFFDFC"
    border.color: "#DBE2DD"
    border.width: 1

    property string typeFilter: "Wszystkie typy"
    property string searchQuery: ""
    readonly property int dateWidth: 130
    readonly property int typeWidth: 158
    readonly property int amountWidth: 170

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 6
        spacing: 0

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            Layout.leftMargin: 20
            Layout.rightMargin: 12
            spacing: 14
            Text {
                text: "Wpisy"
                font.pixelSize: 34
                font.bold: true
                color: "#091B14"
            }
            Item { Layout.fillWidth: true }
            ComboBox {
                id: filterBox
                Layout.preferredWidth: 212
                Layout.preferredHeight: 48
                model: ["Wszystkie typy", "Przychody", "Wydatki"]
                onCurrentTextChanged: root.typeFilter = currentText
                background: Rectangle {
                    radius: 10
                    color: "#FFFDFC"
                    border.color: "#B6C4BA"
                }
                contentItem: Text {
                    text: filterBox.displayText
                    leftPadding: 14
                    verticalAlignment: Text.AlignVCenter
                    color: "#17231D"
                    font.pixelSize: 17
                }
                indicator: Text {
                    x: filterBox.width - width - 13
                    y: (filterBox.height - height) / 2
                    text: "⌄"
                    font.pixelSize: 25
                    color: "#526C5C"
                }
            }
            TextField {
                Layout.preferredWidth: 180
                Layout.preferredHeight: 48
                placeholderText: "Szukaj..."
                font.pixelSize: 17
                onTextChanged: root.searchQuery = text
                background: Rectangle {
                    radius: 10
                    color: "#FFFDFC"
                    border.color: "#B6C4BA"
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 58
            radius: 11
            color: "#EBEFEA"
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 20
                anchors.rightMargin: 18
                spacing: 14
                Text { text: "Data"; Layout.preferredWidth: root.dateWidth; font.pixelSize: 18; font.bold: true }
                Text { text: "Typ"; Layout.preferredWidth: root.typeWidth; font.pixelSize: 18; font.bold: true }
                Text { text: "Kwota"; Layout.preferredWidth: root.amountWidth; horizontalAlignment: Text.AlignRight; font.pixelSize: 18; font.bold: true }
                Text { text: "Komentarz"; Layout.fillWidth: true; font.pixelSize: 18; font.bold: true }
            }
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: backend.wpisyModel
            boundsBehavior: Flickable.StopAtBounds

            delegate: Item {
                id: rowItem
                required property string dateText
                required property string kind
                required property string amountText
                required property string commentText
                readonly property bool income: kind === "Przychód"
                readonly property bool matches:
                    (root.typeFilter === "Wszystkie typy" ||
                     (root.typeFilter === "Przychody" && income) ||
                     (root.typeFilter === "Wydatki" && !income)) &&
                    (root.searchQuery.trim() === "" ||
                     (dateText + " " + commentText + " " + amountText)
                         .toLowerCase().includes(root.searchQuery.trim().toLowerCase()))

                width: ListView.view.width
                height: matches ? 70 : 0
                visible: matches

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 20
                    anchors.rightMargin: 18
                    spacing: 14

                    Text {
                        text: rowItem.dateText
                        Layout.preferredWidth: root.dateWidth
                        font.pixelSize: 17
                        color: "#101A15"
                    }
                    Item {
                        Layout.preferredWidth: root.typeWidth
                        Layout.preferredHeight: 38
                        Rectangle {
                            width: rowItem.income ? 127 : 123
                            height: 38
                            radius: 13
                            color: rowItem.income ? "#E5F3E3" : "#FCE8E6"
                            Row {
                                anchors.centerIn: parent
                                spacing: 8
                                Text {
                                    text: rowItem.income ? "↑" : "↓"
                                    color: rowItem.income ? "#086428" : "#B91420"
                                    font.pixelSize: 24
                                    font.bold: true
                                }
                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: rowItem.kind
                                    font.pixelSize: 17
                                    color: "#17231D"
                                }
                            }
                        }
                    }
                    Text {
                        text: rowItem.amountText
                        Layout.preferredWidth: root.amountWidth
                        horizontalAlignment: Text.AlignRight
                        color: rowItem.income ? "#086528" : "#B5131D"
                        font.pixelSize: 19
                        font.bold: true
                    }
                    Text {
                        text: rowItem.commentText
                        Layout.fillWidth: true
                        font.pixelSize: 17
                        color: "#17201B"
                        elide: Text.ElideRight
                    }
                }
                Rectangle {
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 1
                    color: "#E4E9E5"
                }
            }
        }
    }
}
