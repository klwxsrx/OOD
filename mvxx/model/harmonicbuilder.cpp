#include "harmonicbuilder.h"

QSharedPointer<IHarmonicItem> build(Trigonometric::Function func, double ampl, double freq, double phase)
{
    return QSharedPointer<CHarmonicItem>::create(func, ampl, freq, phase);
}
