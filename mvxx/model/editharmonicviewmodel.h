#ifndef EDITHARMONICVIEWMODEL_H
#define EDITHARMONICVIEWMODEL_H

#include "iharmonicsmodel.h"
#include "iharmonicviewmodel.h"

class CEditHarmonicViewModel final : public IHarmonicViewModel
{
    Q_OBJECT
    Q_INTERFACES(IHarmonicViewModel)
public:
    CEditHarmonicViewModel(QSharedPointer<IHarmonicsModel> const& model);
    void SetFunction(Trigonometric::Function func);
    void SetAmplitude(double ampl);
    void SetFrequency(double freq);
    void SetPhase(double phase);

    Trigonometric::Function getFunction() const override;
    double getAmplitude() const override;
    double getFrequency() const override;
    double getPhase() const override;
    QString getString() const override;
    bool isEnabled() const override;

private:
    QSharedPointer<IHarmonicsModel> m_model;

signals:
    void harmonicUpdated();
};

#endif // EDITHARMONICVIEWMODEL_H
