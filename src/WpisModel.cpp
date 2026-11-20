#include "WpisModel.hpp"
#include "WorkbookManager.hpp"

#include <QLocale>
#include <cmath>

WpisModel::WpisModel(WorkbookManager *manager, QObject *parent)
    : QAbstractListModel(parent),
      m_wpisy(manager->wpisy())
{
    connect(manager, &WorkbookManager::wpisyChanged,
            this, [this, manager]() {
        beginResetModel();
        m_wpisy = manager->wpisy();
        endResetModel();
    });
}

int WpisModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_wpisy.size();
}

QVariant WpisModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() ||
        index.row() < 0 ||
        index.row() >= m_wpisy.size())
        return {};

    const Wpis &wpis = m_wpisy[index.row()];

    switch (role) {
    case DateRole:
        return wpis.date.toString("dd.MM.yyyy");

    case TypeRole:
        return wpis.type;

    case AmountRole: {
        QString sign = wpis.type == "Przychód" ? "+" : "−";
        QString amount = QLocale(QLocale::Polish, QLocale::Poland)
                             .toString(std::abs(wpis.amount), 'f', 2);
        return sign + amount + " zł";
    }

    case CommentRole:
        return wpis.comment;

    default:
        return {};
    }
}

QHash<int, QByteArray> WpisModel::roleNames() const
{
    return {
        {DateRole, "dateText"},
        {TypeRole, "kind"},
        {AmountRole, "amountText"},
        {CommentRole, "commentText"}
    };
}