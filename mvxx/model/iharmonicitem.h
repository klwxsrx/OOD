#ifndef IHARMONICITEM_H
#define IHARMONICITEM_H

#include "utils/trigonometric.h"

class IHarmonicItem
{
public:
    virtual Trigonometric::Function GetFunction() const = 0;
    virtual double GetAmplitude() const = 0;
    virtual double GetFrequency() const = 0;
    virtual double GetPhase() const = 0;
    virtual QString ToString() const = 0;

    virtual ~IHarmonicItem() = default;
};

#endif // IHARMONICITEM_H
