#include "CsvManager.hpp"

#include <QFile>
#include <QTextStream>
#include <QStringConverter>
#include <QStringList>
#include <QDate>
#include <cmath>
#include <QSaveFile>
#include <QTextStream>
#include <QStringConverter>


namespace {

bool parsujCsv(const QString &tekst, QVector<QStringList> &wiersze)
{
    QStringList wiersz;
    QString pole;

    bool wCudzyslowie = false;
    bool zamknietyCudzyslow = false;

    for (qsizetype i = 0; i < tekst.size(); ++i)
    {
        QChar znak = tekst[i];

        if (wCudzyslowie)
        {
            if (znak == '"')
            {
                if (i + 1 < tekst.size() && tekst[i + 1] == '"')
                {
                    pole += '"';
                    ++i;
                }
                else
                {
                    wCudzyslowie = false;
                    zamknietyCudzyslow = true;
                }
            }
            else
            {
                pole += znak;
            }
        }
        else if (znak == ',' || znak == '\n' || znak == '\r')
        {
            wiersz.append(pole);
            pole.clear();
            zamknietyCudzyslow = false;

            if (znak != ',')
            {
                wiersze.append(wiersz);
                wiersz.clear();

                if (znak == '\r' &&
                    i + 1 < tekst.size() &&
                    tekst[i + 1] == '\n')
                    ++i;
            }
        }
        else if (znak == '"')
        {
            if (!pole.isEmpty() || zamknietyCudzyslow)
                return false;

            wCudzyslowie = true;
        }
        else
        {
            if (zamknietyCudzyslow)
                return false;

            pole += znak;
        }
    }

    if (wCudzyslowie)
        return false;

    if (!wiersz.isEmpty() || !pole.isEmpty() || zamknietyCudzyslow)
    {
        wiersz.append(pole);
        wiersze.append(wiersz);
    }

    return true;
}

}


QString CsvManager::escape(const QString &tekst){
    QString wynik = tekst;

    wynik.replace("\"", "\"\"");

    if (wynik.contains(',') ||
        wynik.contains('"') ||
        wynik.contains('\n') ||
        wynik.contains('\r'))
    {
        return "\"" + wynik + "\"";
    }

    return wynik;
}

bool CsvManager::zapisz(const QString &sciezka, const QVector<Wpis> &wpisy) const {
    QSaveFile plik(sciezka);

    if (!plik.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&plik);
    out.setEncoding(QStringConverter::Utf8);

    out << "data,typ,kwota,komentarz\n";

    for (const Wpis &wpis : wpisy)
    {
        out << wpis.date.toString("yyyy-MM-dd") << ","
            << escape(wpis.type) << ","
            << QString::number(wpis.amount, 'f', 2) << ","
            << escape(wpis.comment) << "\n";
    }

    out.flush();

    if (out.status() != QTextStream::Ok)
    {
        plik.cancelWriting();
        return false;
    }

    return plik.commit();
}


bool CsvManager::odczytaj(const QString &sciezka, QVector<Wpis> &wpisy) const{
    QFile plik(sciezka);

    if (!plik.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&plik);
    in.setEncoding(QStringConverter::Utf8);

    QString tekst = in.readAll();

    if (in.status() != QTextStream::Ok)
        return false;

    if (tekst.startsWith(QChar(0xFEFF)))
        tekst.remove(0, 1);

    QVector<QStringList> wiersze;

    if (!parsujCsv(tekst, wiersze) || wiersze.isEmpty())
        return false;

    if (wiersze[0] != QStringList({"data", "typ", "kwota", "komentarz"}))
        return false;

    QVector<Wpis> noweWpisy;

    for (qsizetype i = 1; i < wiersze.size(); ++i){
        const QStringList &kolumny = wiersze[i];

        if (kolumny.size() != 4)
            return false;

        Wpis wpis;

        wpis.date = QDate::fromString(
            kolumny[0], "yyyy-MM-dd"
        );

        wpis.type = kolumny[1].trimmed();

        bool ok = false;
        wpis.amount = kolumny[2].trimmed().toDouble(&ok);

        wpis.comment = kolumny[3];

        if (!wpis.date.isValid() ||
            (wpis.type != "Przychód" && wpis.type != "Wydatek") ||
            !ok || !std::isfinite(wpis.amount) ||
            wpis.amount <= 0)
        {
            return false;
        }

        noweWpisy.append(wpis);
    }

    wpisy = noweWpisy;
    return true;
}
