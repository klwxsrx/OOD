#include "harmonicsmodel.h"

CHarmonicsModel::CHarmonicsModel(QSharedPointer<CHarmonicList> const& list)
    : m_list(list)
{
    m_list->connect(m_list.get(), SIGNAL(listChanged()), this, SIGNAL(dataUpdated()));
}

void CHarmonicsModel::setCurrentItemIndex(QVariant index)
{
    if (m_currentSelectedItemIndex != index)
    {
        m_currentSelectedItemIndex = index;
        emit currentItemChanged();
    }
}

void CHarmonicsModel::addHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase)
{
    m_list->addHarmonicItem(func, ampl, freq, phase);
}

void CHarmonicsModel::replaceHarmonicItem(int index, Trigonometric::Function func, double ampl, double freq, double phase)
{
    m_list->replaceItem(index, func, ampl, freq, phase);
    if (m_currentSelectedItemIndex.isValid() && m_currentSelectedItemIndex.toInt() == index)
    {
        emit currentItemChanged();
    }
}

void CHarmonicsModel::removeHarmonicItem(int index)
{
    m_list->removeHarmonicItem(index);
    if (m_currentSelectedItemIndex.isValid() && m_currentSelectedItemIndex.toInt() == index)
    {
        if (m_currentSelectedItemIndex.toInt() >= m_list->getSize())
        {
            m_currentSelectedItemIndex = QVariant();
        }
        emit currentItemChanged();
    }
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
