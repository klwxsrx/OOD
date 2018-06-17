#include "harmonicitembuilder.h"

QSharedPointer<const CHarmonicItem> CHarmonicItemBuilder::build(Trigonometric::Function func, double ampl, double freq, double phase)
{
    QSharedPointer<CHarmonicItem> item = QSharedPointer<CHarmonicItem>::create(func, ampl, freq, phase);
    return item.constCast<const CHarmonicItem>();
}
