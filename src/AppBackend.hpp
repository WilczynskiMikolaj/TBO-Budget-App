#pragma once

#include <QObject>
#include <QString>
#include <QAbstractItemModel>
#include <QUrl>
#include <QStringList>

#include "WorkbookManager.hpp"
#include "WpisModel.hpp"
#include "CsvManager.hpp"
#include "Recents.hpp"

class AppBackend : public QObject{

    Q_OBJECT
    Q_PROPERTY(int wpisCount READ wpisCount NOTIFY wpisCountChanged)
    Q_PROPERTY(QAbstractItemModel* wpisyModel READ wpisyModel CONSTANT)
    Q_PROPERTY(QStringList recentFiles READ recentFiles NOTIFY recentFilesChanged)

    public: 
        AppBackend(QObject *parent=nullptr);

        Q_INVOKABLE int transactionCount() const;
        Q_INVOKABLE bool addWpis(const QString &date, const QString &type, double amount, const QString &comment);
        Q_INVOKABLE bool removeWpis(int id);
        Q_INVOKABLE bool zapiszCsv(const QUrl &url);
        Q_INVOKABLE bool otworzOstatniPlik(const QString &sciezka);
        Q_INVOKABLE bool otworzCsv(const QUrl &url);
        Q_INVOKABLE bool wyczyscRecentFiles();
        
        int wpisCount() const;
        QAbstractItemModel* wpisyModel();
        QStringList recentFiles() const;


    signals:
        void wpisCountChanged();
        void recentFilesChanged();
        

    private:
        WorkbookManager m_workbook;
        WpisModel m_wpisyModel;
        CsvManager m_csvManager;
        Recents m_recentFiles;
};