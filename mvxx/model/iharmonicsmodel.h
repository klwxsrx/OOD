#ifndef IHARMONICSMODEL_H
#define IHARMONICSMODEL_H

#include <QVariant>
#include <QSharedPointer>
#include "utils/trigonometric.h"
#include "list/harmonicitem.h"

class IHarmonicsModel : public QObject // TODO: delete
{
    Q_OBJECT
public:
    virtual void setCurrentItemIndex(QVariant index) = 0;
    virtual void addHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase) = 0;
    virtual void replaceHarmonicItem(int index, Trigonometric::Function func, double ampl, double freq, double phase) = 0;
    virtual void removeHarmonicItem(int index) = 0;

    virtual QVariant getCurrentItemIndex() const = 0;
    virtual QSharedPointer<const CHarmonicItem> getHarmonicItem(int index) const = 0;
    virtual int getSize() const = 0;
    virtual bool isEmpty() const = 0;

    virtual ~IHarmonicsModel() = default;

signals:
    void dataUpdated();
    void currentItemChanged();
};

Q_DECLARE_INTERFACE(IHarmonicsModel, "IHarmonicsModel")

#endif // IHARMONICSMODEL_H
