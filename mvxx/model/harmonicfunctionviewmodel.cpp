#include "harmonicfunctionviewmodel.h"

CHarmonicFunctionViewModel::CHarmonicFunctionViewModel(QSharedPointer<IHarmonicsModel> const& model)
    : m_model(model)
{
    m_model->connect(m_model.get(), SIGNAL(currentItemChanged()), this, SLOT(onCurrentItemChanged()));
}

Trigonometric::CalculateFunction CHarmonicFunctionViewModel::getFunction() const
{
    return m_function;
}

void CHarmonicFunctionViewModel::onCurrentItemChanged()
{
    QVariant index = m_model->getCurrentItemIndex();
    if (index.isValid())
    {
        QSharedPointer<CHarmonicItem> item = m_model->getHarmonicItem(index.toInt());
        m_function = Trigonometric::getCalculateFunction(
            item->getFunction(),
            item->getAmplitude(),
            item->getFrequency(),
            item->getPhase()
        );
    }
    else
    {
        m_function = Trigonometric::CalculateFunction();
    }
    emit functionUpdated();
}
