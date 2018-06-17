#include "newharmonicviewmodel.h"

CNewHarmonicViewModel::CNewHarmonicViewModel()
    : m_item(QSharedPointer<CHarmonicItem>::create(Trigonometric::Function::SIN, 0, 0, 0))
{
}

void CNewHarmonicViewModel::setFunction(Trigonometric::Function func)
{
    m_item->setFunction(func);
    emit harmonicUpdated();
}

void CNewHarmonicViewModel::setAmplitude(double ampl)
{
    m_item->setAmplitude(ampl);
    emit harmonicUpdated();
}

void CNewHarmonicViewModel::setFrequency(double freq)
{
    m_item->setFrequency(freq);
    emit harmonicUpdated();
}

void CNewHarmonicViewModel::setPhase(double phase)
{
    m_item->setPhase(phase);
    emit harmonicUpdated();
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

