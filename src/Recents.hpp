#pragma once

#include <QString>
#include <QStringList>

class Recents
{
public:
    QStringList pliki() const;
    void dodajPlik(const QString &sciezka);
};