#ifndef HARMONICBUILDER_H
#define HARMONICBUILDER_H

#include <QSharedPointer>
#include "harmonicitem.h"

class CHarmonicBuilder final
{
public:
    static QSharedPointer<IHarmonicItem> build(Trigonometric::Function func, double ampl, double freq, double phase);
};

#endif // HARMONICBUILDER_H
