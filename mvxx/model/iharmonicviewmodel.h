#ifndef IHARMONICVIEWMODEL_H
#define IHARMONICVIEWMODEL_H

#include <QString>
#include "utils/trigonometric.h"

class IHarmonicViewModel
{
public:
    virtual void setFunction(Trigonometric::Function func) = 0;
    virtual void setAmplitude(double ampl) = 0;
    virtual void setFrequency(double freq) = 0;
    virtual void setPhase(double phase) = 0;

    virtual Trigonometric::Function getFunction() const = 0;
    virtual double getAmplitude() const = 0;
    virtual double getFrequency() const = 0;
    virtual double getPhase() const = 0;
    virtual QString getString() const = 0;
    virtual bool isEnabled() const = 0;

    virtual ~IHarmonicViewModel() = default;

signals:
    virtual void harmonicUpdated() = 0;
};

Q_DECLARE_INTERFACE(IHarmonicViewModel, "IHarmonicViewModel")

#endif // IHARMONICVIEWMODEL_H
