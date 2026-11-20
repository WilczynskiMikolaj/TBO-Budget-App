#include <QDate>
#include <cmath>

#include "AppBackend.hpp"

AppBackend::AppBackend(QObject *parent) : QObject(parent), m_workbook(this), m_wpisyModel(&m_workbook, this) {
    
    connect(&m_workbook, &WorkbookManager::wpisyChanged, this, &AppBackend::wpisCountChanged);
}

int AppBackend::transactionCount() const{
    return m_workbook.wpisy().size();
}

int AppBackend::wpisCount() const{
    return m_workbook.wpisy().size();
}

QAbstractItemModel* AppBackend::wpisyModel(){
    return &m_wpisyModel;
}

bool AppBackend::addWpis(const QString &date, const QString &type, double amount, const QString &comment){
    
    QDate parsedDate = QDate::fromString(date.trimmed(), "dd.MM.yyyy");

    if (!parsedDate.isValid())
        return false;

    if (type != "Przychód" && type != "Wydatek")
        return false;

    if (!std::isfinite(amount) || amount <= 0)
        return false;

    Wpis wpis;
    wpis.date = parsedDate;
    wpis.type = type;
    wpis.amount = amount;
    wpis.comment = comment.trimmed();

    m_workbook.addWpis(wpis);

    return true;
}

bool AppBackend::removeWpis(int id)
{
    m_workbook.removeWpis(id);
    return true;
}

bool AppBackend::zapiszCsv(const QUrl &url){
    if (!url.isLocalFile())
        return false;

    if (!m_csvManager.zapisz(url.toLocalFile(),
                            m_workbook.wpisy()))
        return false;

    m_recentFiles.dodajPlik(url.toLocalFile());
    emit recentFilesChanged();

    return true;
}

bool AppBackend::otworzCsv(const QUrl &url){
    if (!url.isLocalFile())
        return false;

    QVector<Wpis> noweWpisy;

    if (!m_csvManager.odczytaj(url.toLocalFile(), noweWpisy))
        return false;

    m_workbook.ustawWpisy(noweWpisy);

    m_recentFiles.dodajPlik(url.toLocalFile());
    emit recentFilesChanged();

    return true;
}

QStringList AppBackend::recentFiles() const{
    return m_recentFiles.pliki();
}

bool AppBackend::wyczyscRecentFiles() {
    m_recentFiles.wyczysc();
    emit recentFilesChanged();
    return true;
}

bool AppBackend::otworzOstatniPlik(const QString &sciezka){
    return otworzCsv(QUrl::fromLocalFile(sciezka));
}