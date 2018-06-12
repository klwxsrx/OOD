#ifndef HARMONICITEMLISTMODEL_H
#define HARMONICITEMLISTMODEL_H

#include <QList>
#include <QVariant>
#include "iharmonicitemlistmodel.h"

class CHarmonicItemListModel final : public IHarmonicItemListModel
{
    Q_OBJECT
public:
    int rowCount(QModelIndex const&) const override;
    QVariant data(QModelIndex const& index, int role) const override;

    void addHarmonicItem(QSharedPointer<IHarmonicItem> const& item) override;
    void removeHarmonicItem(int index) override;
    bool empty() const override;

private:
    QList<QSharedPointer<IHarmonicItem>> m_list;
};

#endif // HARMONICITEMLISTMODEL_H
