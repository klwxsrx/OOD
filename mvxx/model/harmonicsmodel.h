#ifndef HARMONICSMODEL_H
#define HARMONICSMODEL_H

#include <QSharedPointer>
#include <QVariant>
#include "iharmonicsmodel.h"
#include "list/harmoniclist.h"

class CHarmonicsModel final : public IHarmonicsModel
{
    Q_OBJECT
    Q_INTERFACES(IHarmonicsModel)
public:
    CHarmonicsModel(QSharedPointer<CHarmonicList> const& list);

    void setCurrentItemIndex(QVariant index) override;
    void addHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase) override;
    void replaceHarmonicItem(int index, Trigonometric::Function func, double ampl, double freq, double phase) override;
    void removeHarmonicItem(int index) override;

    QVariant getCurrentItemIndex() const;
    QSharedPointer<CHarmonicItem> getHarmonicItem(int index) const override;
    int getSize() const override;
    bool isEmpty() const override;

private:
    QSharedPointer<CHarmonicList> m_list;
    QVariant m_currentSelectedItemIndex;

signals:
    void dataUpdated();
    void currentItemChanged();
};

#endif // HARMONICSMODEL_H
