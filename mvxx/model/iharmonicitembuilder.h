#ifndef IHARMONICITEMBUILDER_H
#define IHARMONICITEMBUILDER_H

#include <QSharedPointer>
#include "iharmonicitem.h"
#include "utils/trigonometric.h"

class IHarmonicItemBuilder
{
public:
    virtual QSharedPointer<IHarmonicItem> build(Trigonometric::Function func, double ampl, double freq, double phase) = 0;
    virtual ~IHarmonicItemBuilder() = default;
};

#endif // IHARMONICITEMBUILDER_H
