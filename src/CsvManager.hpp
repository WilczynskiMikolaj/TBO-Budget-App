#pragma once

#include <QString>
#include <QVector>

#include "Wpis.hpp"

class CsvManager{
public:
    bool zapisz(const QString &sciezka, const QVector<Wpis> &wpisy) const;
    bool odczytaj(const QString &sciezka, QVector<Wpis> &wpisy) const;

private:
    static QString escape(const QString &tekst);
};