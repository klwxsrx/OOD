#ifndef CHARMONICITEM_H
#define CHARMONICITEM_H

#include "utils/trigonometric.h"

class CHarmonicItem final
{
public:
    CHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase);

    void setFunction(Trigonometric::Function value);
    void setAmplitude(double value);
    void setFrequency(double value);
    void setPhase(double value);

    Trigonometric::Function getFunction() const;
    double getAmplitude() const;
    double getFrequency() const;
    double getPhase() const;

private:
    Trigonometric::Function m_function;
    double m_amplitude;
    double m_frequency;
    double m_phase;
};

#endif // CHARMONICITEM_H
