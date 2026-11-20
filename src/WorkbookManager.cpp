#include "WorkbookManager.hpp"

WorkbookManager::WorkbookManager(QObject *parent) : QObject(parent){
}

void WorkbookManager::addWpis(const Wpis &wpis){
    m_wpisy.append(wpis);
    emit wpisyChanged();
}

bool WorkbookManager::removeWpis(int index){
    if (index < 0 || index >= m_wpisy.size())
        return false;

    m_wpisy.removeAt(index);
    emit wpisyChanged();

    return true;
}

const QVector<Wpis>& WorkbookManager::wpisy() const{
    return m_wpisy;
}

void WorkbookManager::ustawWpisy(const QVector<Wpis> &wpisy){
    m_wpisy = wpisy;
    emit wpisyChanged();
}