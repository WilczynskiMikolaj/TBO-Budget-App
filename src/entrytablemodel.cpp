#include "EntryTableModel.h"

#include <QDateTime>

EntryTableModel::EntryTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int EntryTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(entries.size());
}

int EntryTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 4;
}

QVariant EntryTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() ||
        index.row() < 0 ||
        index.row() >= static_cast<int>(entries.size()))
        return {};

    if (role != Qt::DisplayRole)
        return {};

    const Entry &entry = entries[index.row()];

    switch (index.column())
    {
    case 0:
        return QString::number(entry.amount, 'f', 2);

    case 1:
        return entry.type == EntryType::expense
                   ? "Wydatek"
                   : "Zysk";

    case 2:
        return QString::fromStdString(entry.comment);

    case 3:
        return QDateTime::fromSecsSinceEpoch(
                   static_cast<qint64>(entry.date)
                   ).toString("yyyy-MM-dd HH:mm");

    default:
        return {};
    }
}

QVariant EntryTableModel::headerData(
    int section,
    Qt::Orientation orientation,
    int role) const
{
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0: return "Ilość";
        case 1: return "Typ";
        case 2: return "Komentarz";
        case 3: return "Data";
        }
    }

    return section + 1;
}

void EntryTableModel::addEntry(const Entry &entry)
{
    int row = static_cast<int>(entries.size());

    beginInsertRows(QModelIndex(), row, row);
    entries.push_back(entry);
    endInsertRows();
}

void EntryTableModel::setEntries(const std::vector<Entry> &newEntries)
{
    beginResetModel();
    entries = newEntries;
    endResetModel();
}