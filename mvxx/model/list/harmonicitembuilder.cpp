#include "harmonicitembuilder.h"

QSharedPointer<CHarmonicItem> CHarmonicItemBuilder::build(Trigonometric::Function func, double ampl, double freq, double phase)
{
    return QSharedPointer<CHarmonicItem>::create(func, ampl, freq, phase);
}
