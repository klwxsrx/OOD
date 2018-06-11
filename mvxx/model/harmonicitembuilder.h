#ifndef HARMONICBUILDER_H
#define HARMONICBUILDER_H

#include "harmonicitem.h"
#include "iharmonicitembuilder.h"

class CHarmonicItemBuilder final : public IHarmonicItemBuilder
{
public:
    QSharedPointer<IHarmonicItem> build(Trigonometric::Function func, double ampl, double freq, double phase) override;
};

#endif // HARMONICBUILDER_H
