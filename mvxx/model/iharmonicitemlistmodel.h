#ifndef IHARMONICITEMLISTMODEL_H
#define IHARMONICITEMLISTMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include "iharmonicitem.h"

class IHarmonicItemListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    virtual void addHarmonicItem(QSharedPointer<IHarmonicItem> const& item) = 0;
    virtual void removeHarmonicItem(int index) = 0;
    virtual bool empty() const = 0;

    virtual ~IHarmonicItemListModel() = default;
};

#endif // IHARMONICITEMLISTMODEL_H
