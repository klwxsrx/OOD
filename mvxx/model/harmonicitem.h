#ifndef CHARMONICITEM_H
#define CHARMONICITEM_H

#include <QString>
#include "iharmonicitem.h"

class CHarmonicItem final : public IHarmonicItem
{
public:
    CHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase);

    virtual Trigonometric::Function getFunction() const override;
    virtual double getAmplitude() const override;
    virtual double getFrequency() const override;
    virtual double getPhase() const override;
    virtual QString toString() const override;

private:
    Trigonometric::Function m_function;
    double m_amplitude;
    double m_frequency;
    double m_phase;
};

#endif // CHARMONICITEM_H
