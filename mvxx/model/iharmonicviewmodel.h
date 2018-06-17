#ifndef IHARMONICVIEWMODEL_H
#define IHARMONICVIEWMODEL_H

#include <QString>
#include <QObject>
#include "utils/trigonometric.h"

class IHarmonicViewModel : public QObject // TODO: delete
{
    Q_OBJECT
public:
    virtual void SetFunction(Trigonometric::Function func) = 0;
    virtual void SetAmplitude(double ampl) = 0;
    virtual void SetFrequency(double freq) = 0;
    virtual void SetPhase(double phase) = 0;

    virtual Trigonometric::Function getFunction() const = 0;
    virtual double getAmplitude() const = 0;
    virtual double getFrequency() const = 0;
    virtual double getPhase() const = 0;
    virtual QString getString() const = 0;
    virtual bool isEnabled() const = 0;

    virtual ~IHarmonicViewModel() = default;

signals:
    void harmonicUpdated();
};

Q_DECLARE_INTERFACE(IHarmonicViewModel, "IHarmonicViewModel")

#endif // IHARMONICVIEWMODEL_H