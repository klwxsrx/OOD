#ifndef EDITHARMONICVIEWMODEL_H
#define EDITHARMONICVIEWMODEL_H

#include "iharmonicsmodel.h"
#include "iharmonicviewmodel.h"

class CEditHarmonicViewModel final : public QObject, public IHarmonicViewModel
{
    Q_OBJECT
    Q_INTERFACES(IHarmonicViewModel)
public:
    CEditHarmonicViewModel(QSharedPointer<IHarmonicsModel> const& model);
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
    QSharedPointer<IHarmonicsModel> m_model;

signals:
    void harmonicUpdated() override;
};

#endif // EDITHARMONICVIEWMODEL_H
