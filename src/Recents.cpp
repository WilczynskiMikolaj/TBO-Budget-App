#include "Recents.hpp"

#include <QSettings>
#include <QFileInfo>

QStringList Recents::pliki() const
{
    QSettings settings("TBO", "TBO");

    return settings.value("recentFiles").toStringList();
}

void Recents::dodajPlik(const QString &sciezka)
{
    QSettings settings("TBO", "TBO");

    QStringList lista = pliki();
    QString sciezkaPliku = QFileInfo(sciezka).absoluteFilePath();

    lista.removeAll(sciezkaPliku);

    lista.prepend(sciezkaPliku);

    while (lista.size() > 8)
        lista.removeLast();

    settings.setValue("recentFiles", lista);
}
