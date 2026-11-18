#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CSVStorage.h"
#include "Statistics.h"
#include "Recents.h"
#include "entrytablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AddEntryButton_clicked();
    void UpdateTable();

private:
    Ui::MainWindow *ui;
    CSVStorage *storage;
    Statistics *statistics;
    Recents *recents;
    EntryTableModel *tableModel;
};

#endif