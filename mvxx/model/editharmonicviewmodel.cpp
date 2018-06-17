#include "editharmonicviewmodel.h"

CEditHarmonicViewModel::CEditHarmonicViewModel(QSharedPointer<IHarmonicsModel> const& model)
    : m_model(model)
{
    m_model->connect(m_model.get(), SIGNAL(currentItemChanged()), this, SIGNAL(harmonicUpdated()));
}

void CEditHarmonicViewModel::SetFunction(Trigonometric::Function func)
{
    auto itemIndex = m_model->getCurrentItemIndex();
    if (itemIndex.isValid())
    {
        auto item = m_model->getHarmonicItem(itemIndex.toInt());
        m_model->replaceHarmonicItem(m_model->getCurrentItemIndex().toInt(),
            func,
            item->getAmplitude(),
            item->getFrequency(),
            item->getPhase()
        );
        emit harmonicUpdated();
    }
}

void CEditHarmonicViewModel::SetAmplitude(double ampl)
{
    auto itemIndex = m_model->getCurrentItemIndex();
    if (itemIndex.isValid())
    {
        auto item = m_model->getHarmonicItem(itemIndex.toInt());
        m_model->replaceHarmonicItem(m_model->getCurrentItemIndex().toInt(),
            item->getFunction(),
            ampl,
            item->getFrequency(),
            item->getPhase()
        );
        emit harmonicUpdated();
    }
}

void CEditHarmonicViewModel::SetFrequency(double freq)
{
    auto itemIndex = m_model->getCurrentItemIndex();
    if (itemIndex.isValid())
    {
        auto item = m_model->getHarmonicItem(itemIndex.toInt());
        m_model->replaceHarmonicItem(m_model->getCurrentItemIndex().toInt(),
            item->getFunction(),
            item->getAmplitude(),
            freq,
            item->getPhase()
        );
        emit harmonicUpdated();
    }
}

void CEditHarmonicViewModel::SetPhase(double phase)
{
    auto itemIndex = m_model->getCurrentItemIndex();
    if (itemIndex.isValid())
    {
        auto item = m_model->getHarmonicItem(itemIndex.toInt());
        m_model->replaceHarmonicItem(m_model->getCurrentItemIndex().toInt(),
            item->getFunction(),
            item->getAmplitude(),
            item->getFrequency(),
            phase
        );
        emit harmonicUpdated();
    }
}

Trigonometric::Function CEditHarmonicViewModel::getFunction() const
{
    auto itemIndex = m_model->getCurrentItemIndex();
    if (itemIndex.isValid())
    {
        auto item = m_model->getHarmonicItem(itemIndex.toInt());
        return item->getFunction();
    }
    return Trigonometric::Function::SIN;
}

double CEditHarmonicViewModel::getAmplitude() const
{
    auto itemIndex = m_model->getCurrentItemIndex();
    if (itemIndex.isValid())
    {
        auto item = m_model->getHarmonicItem(itemIndex.toInt());
        return item->getAmplitude();
    }
    return 0.;
}

double CEditHarmonicViewModel::getFrequency() const
{
    auto itemIndex = m_model->getCurrentItemIndex();
    if (itemIndex.isValid())
    {
        auto item = m_model->getHarmonicItem(itemIndex.toInt());
        return item->getFrequency();
    }
    return 0.;
}

double CEditHarmonicViewModel::getPhase() const
{
    auto itemIndex = m_model->getCurrentItemIndex();
    if (itemIndex.isValid())
    {
        auto item = m_model->getHarmonicItem(itemIndex.toInt());
        return item->getPhase();
    }
    return 0.;
}

QString CEditHarmonicViewModel::getString() const
{
    auto itemIndex = m_model->getCurrentItemIndex();
    if (itemIndex.isValid())
    {
        auto item = m_model->getHarmonicItem(itemIndex.toInt());
        return Trigonometric::harmonicToString(
            item->getFunction(),
            item->getAmplitude(),
            item->getFrequency(),
            item->getPhase()
        );
    }
    return "";
}

bool CEditHarmonicViewModel::isEnabled() const
{
    return m_model->getCurrentItemIndex().isValid();
}
