#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QDateTimeEdit>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    storage = new CSVStorage();
    statistics = new Statistics();
    recents = new Recents();

    recents->Load();

    ui->setupUi(this);

    tableModel = new EntryTableModel(this);

    ui->tableView->setModel(tableModel);

    // Optional table appearance
    ui->tableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch
        );

    ui->tableView->setSelectionBehavior(
        QAbstractItemView::SelectRows
        );

    ui->tableView->setEditTriggers(
        QAbstractItemView::NoEditTriggers
        );
}

MainWindow::~MainWindow()
{
    // Memory leak :)
    // delete storage;
    // delete statistics;
    // delete recents;

    delete ui;
}

void MainWindow::UpdateTable()
{
    tableModel->setEntries(storage->entries);
}


void MainWindow::on_AddEntryButton_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Dodaj wpis");
    dialog.setMinimumWidth(350);

    // Create input widgets
    QDoubleSpinBox *amountInput = new QDoubleSpinBox(&dialog);
    amountInput->setRange(0.01, 999999999.99);
    amountInput->setDecimals(2);
    amountInput->setValue(0.01);

    QComboBox *typeInput = new QComboBox(&dialog);
    typeInput->addItem("Wydatek", static_cast<int>(EntryType::expense));
    typeInput->addItem("Zysk", static_cast<int>(EntryType::income));

    QPlainTextEdit *commentInput = new QPlainTextEdit(&dialog);
    commentInput->setPlaceholderText("Wpisz komentarz...");
    commentInput->setMaximumHeight(80);

    QDateTimeEdit *dateInput = new QDateTimeEdit(QDateTime::currentDateTime(), &dialog);
    dateInput->setCalendarPopup(true);
    dateInput->setDisplayFormat("yyyy-MM-dd HH:mm:ss");

    // Create form layout
    QFormLayout *form = new QFormLayout();

    form->addRow("Ilość:", amountInput);
    form->addRow("Typ:", typeInput);
    form->addRow("Komentarz:", commentInput);
    form->addRow("Data:", dateInput);

    // Create buttons
    QDialogButtonBox *buttons = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        &dialog
        );

    connect(buttons, &QDialogButtonBox::accepted,
            &dialog, &QDialog::accept);

    connect(buttons, &QDialogButtonBox::rejected,
            &dialog, &QDialog::reject);

    // Assemble dialog
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addLayout(form);
    layout->addWidget(buttons);

    // Display dialog
    if (dialog.exec() != QDialog::Accepted)
        return;

    // Create Entry
    Entry entry{};

    entry.amount = amountInput->value();

    entry.type = static_cast<EntryType>(
        typeInput->currentData().toInt()
        );

    entry.comment = commentInput->toPlainText()
                        .trimmed()
                        .toUtf8()
                        .toStdString();

    entry.date = static_cast<decltype(entry.date)>(
        dateInput->dateTime().toSecsSinceEpoch()
        );

    storage->entries.push_back(entry);

    UpdateTable();
}

