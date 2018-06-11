#include "harmonicitemlistmodel.h"

int CHarmonicItemListModel::rowCount(QModelIndex const&) const
{
    return m_list.size();
}

QVariant CHarmonicItemListModel::data(QModelIndex const& index, int role) const
{
    if (index.row() >= m_list.size())
    {
        return QVariant();
    }

    switch (role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return m_list.at(index.row())->ToString();
    default:
        return QVariant();
    }
}

void CHarmonicItemListModel::addHarmonicItem(QSharedPointer<IHarmonicItem> const& item)
{
    emit layoutAboutToBeChanged();
    m_list.push_back(item);
    emit layoutChanged();
}

void CHarmonicItemListModel::removeHarmonicItem(size_t index)
{
    emit layoutAboutToBeChanged();
    m_list.removeAt(index);
    emit layoutChanged();
}
