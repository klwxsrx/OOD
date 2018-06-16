#include "harmoniclist.h"

void CHarmonicList::addHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase)
{
    m_list.push_back(CHarmonicItemBuilder::build(func, ampl, freq, phase));
    emit listChanged();
}

void CHarmonicList::removeHarmonicItem(int index)
{
    m_list.removeAt(index);
    emit listChanged();
}

QSharedPointer<CHarmonicItem> CHarmonicList::getHarmonicItem(int index) const
{
    return m_list.at(index);
}

int CHarmonicList::getSize() const
{
    return m_list.size();
}

bool CHarmonicList::isEmpty() const
{
    return m_list.empty();
}
