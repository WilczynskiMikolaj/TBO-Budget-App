#pragma once

#include <QString>
#include <QDate>

struct Wpis
{
    QDate date;
    QString type;
    double amount;
    QString comment;
};