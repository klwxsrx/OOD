#include "harmonicitem.h"

CHarmonicItem::CHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase)
    : m_function(func), m_amplitude(ampl), m_frequency(freq), m_phase(phase)
{
}

void CHarmonicItem::setFunction(Trigonometric::Function value)
{
    m_function = value;
}

void CHarmonicItem::setAmplitude(double value)
{
    m_amplitude = value;
}

void CHarmonicItem::setFrequency(double value)
{
    m_frequency = value;
}

void CHarmonicItem::setPhase(double value)
{
    m_phase = value;
}

Trigonometric::Function CHarmonicItem::getFunction() const
{
    return m_function;
}

double CHarmonicItem::getAmplitude() const
{
    return m_amplitude;
}

double CHarmonicItem::getFrequency() const
{
    return m_frequency;
}

double CHarmonicItem::getPhase() const
{
    return m_phase;
}
