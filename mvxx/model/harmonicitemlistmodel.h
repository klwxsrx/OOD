#ifndef HARMONICITEMLISTMODEL_H
#define HARMONICITEMLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include <QSharedPointer>
#include "iharmonicitem.h"

class CHarmonicItemListModel final : public QAbstractListModel
{
    Q_OBJECT
public:
    int rowCount(QModelIndex const&) const override;
    QVariant data(QModelIndex const& index, int role) const override;

    void addHarmonicItem(QSharedPointer<IHarmonicItem> const& item);
    void removeHarmonicItem(size_t index);

private:
    QList<QSharedPointer<IHarmonicItem>> m_list;
};

#endif // HARMONICITEMLISTMODEL_H
