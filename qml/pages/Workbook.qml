import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs as QuickDialogs

import "../components"

Rectangle {
    id: root
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
                text: "Skoroszyt"
                font.pixelSize: 44
                font.bold: true
                color: "#091B15"
            }

            Item {
                Layout.fillWidth: true
            }

            AppButton {
                label: "Otwórz CSV"
                symbol: "▤"
                primary: false

                onClicked: openFileDialog.open()
            }

            AppButton {
                label: "Zapisz CSV"
                symbol: "↓"
                primary: false

                onClicked: saveFileDialog.open()
            }

            AppButton {
                label: "Nowy wpis"
                symbol: "+"
                primary: true

                onClicked: {
                    errorText.text = ""
                    addWpisDialog.open()
                }
            }
        }

        TransactionsTable {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    QuickDialogs.FileDialog {
        id: openFileDialog

        title: "Otwórz plik CSV"
        fileMode: QuickDialogs.FileDialog.OpenFile
        nameFilters: ["Pliki CSV (*.csv)"]

        onAccepted: {
            let success = backend.otworzCsv(selectedFile)

            if (success) {
                csvResultDialog.title = "Otwieranie CSV"
                csvResultDialog.resultText = "Plik CSV otwarto pomyślnie."
            } else {
                csvResultDialog.title = "Błąd otwierania CSV"
                csvResultDialog.resultText = "Nie udało się otworzyć pliku CSV."
            }

            csvResultDialog.open()
        }
    }

    QuickDialogs.FileDialog {
        id: saveFileDialog

        title: "Zapisz skoroszyt"
        fileMode: QuickDialogs.FileDialog.SaveFile
        nameFilters: ["Pliki CSV (*.csv)"]
        defaultSuffix: "csv"

        onAccepted: {
            let success = backend.zapiszCsv(selectedFile)

            if (success) {
                csvResultDialog.resultText = "Zapisano plik CSV."
            } else {
                csvResultDialog.resultText = "Nie udało się zapisać pliku."
            }

            csvResultDialog.open()
        }
    }

    Dialog {
        id: csvResultDialog

        property string resultText: ""

        title: "Zapis CSV"
        modal: true
        anchors.centerIn: Overlay.overlay
        width: 350
        standardButtons: Dialog.Ok

        contentItem: Label {
            text: csvResultDialog.resultText
            padding: 18
        }
    }


    Dialog {
        id: addWpisDialog
        title: "Nowy wpis"
        modal: true
        anchors.centerIn: Overlay.overlay
        width: 430
        padding: 20

        contentItem: ColumnLayout {
            spacing: 12

            Label {
                text: "Data"
            }

            TextField {
                id: dateField
                Layout.fillWidth: true
                text: Qt.formatDate(new Date(), "dd.MM.yyyy")
                placeholderText: "dd.MM.rrrr"
            }

            Label {
                text: "Typ transakcji"
            }

            ComboBox {
                id: typeField
                Layout.fillWidth: true
                model: ["Przychód", "Wydatek"]
            }

            Label {
                text: "Kwota (zł)"
            }

            TextField {
                id: amountField
                Layout.fillWidth: true
                placeholderText: "Np. 150,50"
            }

            Label {
                text: "Komentarz"
            }

            TextField {
                id: commentField
                Layout.fillWidth: true
                placeholderText: "Np. Zakupy spożywcze"
            }

            Text {
                id: errorText
                color: "#B5131D"
                visible: text.length > 0
                Layout.fillWidth: true
                wrapMode: Text.Wrap
            }

            RowLayout {
                Layout.fillWidth: true

                Item {
                    Layout.fillWidth: true
                }

                Button {
                    text: "Anuluj"
                    onClicked: addWpisDialog.close()
                }

                Button {
                    text: "Dodaj wpis"

                    onClicked: {
                        let amountString = amountField.text.trim()
                        let amount = Number(
                            amountString.replace(",", ".")
                        )

                        if (amountString === "" ||
                            !isFinite(amount) ||
                            amount <= 0) {
                            errorText.text = "Podaj poprawną kwotę."
                            return
                        }

                        let success = backend.addWpis(
                            dateField.text,
                            typeField.currentText,
                            amount,
                            commentField.text
                        )

                        if (!success) {
                            errorText.text = "Sprawdź datę i dane wpisu."
                            return
                        }

                        amountField.text = ""
                        commentField.text = ""
                        errorText.text = ""

                        addWpisDialog.close()
                    }
                }
            }
        }
    }
}
