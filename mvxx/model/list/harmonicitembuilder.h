#ifndef HARMONICITEMBUILDER_H
#define HARMONICITEMBUILDER_H

#include "QSharedPointer"
#include "harmonicitem.h"

class CHarmonicItemBuilder final
{
public:
    static QSharedPointer<const CHarmonicItem> build(Trigonometric::Function func, double ampl, double freq, double phase);
};

#endif // HARMONICITEMBUILDER_H
