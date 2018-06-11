#include "harmonicitem.h"

CHarmonicItem::CHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase)
    : m_function(func), m_amplitude(ampl), m_frequency(freq), m_phase(phase)
{
}

Trigonometric::Function CHarmonicItem::GetFunction() const
{
    return m_function;
}

double CHarmonicItem::GetAmplitude() const
{
    return m_amplitude;
}

double CHarmonicItem::GetFrequency() const
{
    return m_frequency;
}

double CHarmonicItem::GetPhase() const
{
    return m_phase;
}

QString CHarmonicItem::ToString() const
{
    return Trigonometric::HarmonicToString(m_function, m_amplitude, m_frequency, m_phase);
}
