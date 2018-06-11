#include "harmonicitem.h"

CHarmonicItem::CHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase)
    : m_function(func), m_amplitude(ampl), m_frequency(freq), m_phase(phase)
{
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

QString CHarmonicItem::toString() const
{
    return Trigonometric::harmonicToString(m_function, m_amplitude, m_frequency, m_phase);
}
