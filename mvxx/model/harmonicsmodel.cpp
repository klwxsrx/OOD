#include "harmonicsmodel.h"

CHarmonicsModel::CHarmonicsModel(QSharedPointer<CHarmonicList> const& list)
    : m_list(list)
{
    m_list->connect(m_list.get(), SIGNAL(listChanged()), this, SIGNAL(dataUpdated()));
    m_currentSelectedItemIndex.setValue(NULL);
}

void CHarmonicsModel::setCurrentItemIndex(QVariant index)
{
    if (index.isValid() && (m_currentSelectedItemIndex != index) && index.canConvert(QVariant::Int))
    {
        m_currentSelectedItemIndex = index;
        emit currentItemIndexChanged();
    }
}

void CHarmonicsModel::addHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase)
{
    m_list->addHarmonicItem(func, ampl, freq, phase);
}

void CHarmonicsModel::removeHarmonicItem(int index)
{
    m_list->removeHarmonicItem(index);
}

QVariant CHarmonicsModel::getCurrentItemIndex() const
{
    return m_currentSelectedItemIndex;
}

QSharedPointer<CHarmonicItem> CHarmonicsModel::getHarmonicItem(int index) const
{
    return m_list->getHarmonicItem(index);
}

int CHarmonicsModel::getSize() const
{
    return m_list->getSize();
}

bool CHarmonicsModel::isEmpty() const
{
    return m_list->isEmpty();
}
