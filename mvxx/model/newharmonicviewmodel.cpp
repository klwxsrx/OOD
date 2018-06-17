#include "newharmonicviewmodel.h"

void CNewHarmonicViewModel::setFunction(Trigonometric::Function func)
{
    m_item->setFunction(func);
}

void CNewHarmonicViewModel::setAmplitude(double ampl)
{
    m_item->setAmplitude(ampl);
}

void CNewHarmonicViewModel::setFrequency(double freq)
{
    m_item->setFrequency(freq);
}

void CNewHarmonicViewModel::setPhase(double phase)
{
    m_item->setPhase(phase);
}

Trigonometric::Function CNewHarmonicViewModel::getFunction() const
{
    return m_item->getFunction();
}

double CNewHarmonicViewModel::getAmplitude() const
{
    return m_item->getAmplitude();
}

double CNewHarmonicViewModel::getFrequency() const
{
    return m_item->getFrequency();
}

double CNewHarmonicViewModel::getPhase() const
{
    return m_item->getPhase();
}

QString CNewHarmonicViewModel::getString() const
{
    return Trigonometric::harmonicToString(
        m_item->getFunction(),
        m_item->getAmplitude(),
        m_item->getFrequency(),
        m_item->getPhase()
    );
}

bool CNewHarmonicViewModel::isEnabled() const
{
    return true;
}

