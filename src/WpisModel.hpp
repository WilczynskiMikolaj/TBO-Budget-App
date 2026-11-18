#pragma once

#include <QAbstractListModel>
#include <QVector>
#include "Wpis.hpp"

class WorkbookManager;

class WpisModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit WpisModel(WorkbookManager *manager,
                       QObject *parent = nullptr);

    enum Roles {
        DateRole = Qt::UserRole + 1,
        TypeRole,
        AmountRole,
        CommentRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<Wpis> m_wpisy;
};