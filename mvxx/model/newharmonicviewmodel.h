#ifndef NEWHARMONICVIEWMODEL_H
#define NEWHARMONICVIEWMODEL_H

#include <QSharedPointer>
#include "iharmonicviewmodel.h"
#include "list/harmonicitem.h"

class CNewHarmonicViewModel final : public QObject, public IHarmonicViewModel
{
    Q_OBJECT
    Q_INTERFACES(IHarmonicViewModel)
public:
    CNewHarmonicViewModel();

    void setFunction(Trigonometric::Function func) override;
    void setAmplitude(double ampl) override;
    void setFrequency(double freq) override;
    void setPhase(double phase) override;

    Trigonometric::Function getFunction() const override;
    double getAmplitude() const override;
    double getFrequency() const override;
    double getPhase() const override;
    QString getString() const override;
    bool isEnabled() const override;

private:
    QSharedPointer<CHarmonicItem> m_item;

signals:
    void harmonicUpdated() override;
};

#endif // NEWHARMONICVIEWMODEL_H
