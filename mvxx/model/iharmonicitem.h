#ifndef IHARMONICITEM_H
#define IHARMONICITEM_H

#include "utils/trigonometric.h"

class IHarmonicItem
{
public:
    virtual Trigonometric::Function getFunction() const = 0;
    virtual double getAmplitude() const = 0;
    virtual double getFrequency() const = 0;
    virtual double getPhase() const = 0;
    virtual QString toString() const = 0;

    virtual ~IHarmonicItem() = default;
};

#endif // IHARMONICITEM_H
