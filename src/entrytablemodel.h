#ifndef ENTRYTABLEMODEL_H
#define ENTRYTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "Entry.h"

class EntryTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit EntryTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void addEntry(const Entry &entry);
    void setEntries(const std::vector<Entry> &entries);

private:
    std::vector<Entry> entries;
};

#endif