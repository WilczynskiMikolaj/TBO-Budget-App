#pragma once

#include <QObject>
#include <QVector>
#include "Wpis.hpp"

class WorkbookManager : public QObject
{
    Q_OBJECT

private:
    QVector<Wpis> m_wpisy;

public:
    explicit WorkbookManager(QObject *parent = nullptr);

    void addWpis(const Wpis &wpis);
    bool removeWpis(int index);
    void ustawWpisy(const QVector<Wpis> &wpisy);
    const QVector<Wpis>& wpisy() const;

signals:
    void wpisyChanged();
};