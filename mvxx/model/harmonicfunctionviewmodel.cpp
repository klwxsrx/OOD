#include "harmonicfunctionviewmodel.h"

CHarmonicFunctionViewModel::CHarmonicFunctionViewModel(QSharedPointer<IHarmonicsModel> const& model)
    : m_model(model)
{
    m_model->connect(m_model.get(), SIGNAL(dataUpdated()), this, SLOT(onItemsChanged()));
}

QVector<Trigonometric::CalculateFunction> CHarmonicFunctionViewModel::getFunctions() const
{
    return m_functions;
}

void CHarmonicFunctionViewModel::onItemsChanged()
{
    m_functions = QVector<Trigonometric::CalculateFunction>();
    int size = m_model->getSize();
    for (int index = 0; index < size; ++index)
    {
        QSharedPointer<const CHarmonicItem> item = m_model->getHarmonicItem(index);
        auto function = Trigonometric::getCalculateFunction(
            item->getFunction(),
            item->getAmplitude(),
            item->getFrequency(),
            item->getPhase()
        );
        m_functions.push_back(std::move(function));
    }
    emit dataUpdated();
}
