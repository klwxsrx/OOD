#include "trigonometric.h"

QString Trigonometric::functionToString(Function func)
{
    switch (func) {
    case Function::SIN:
        return "sin";
    case Function::COS:
        return "cos";
    default:
        return "";
    }
}

QString Trigonometric::harmonicToString(Function func, double ampl, double freq, double phase)
{
    return QString::number(ampl) + " * " +
        functionToString(func) + "(" +
        QString::number(freq) + " * x + " +
        QString::number(phase) + ")";
}

Trigonometric::CalculateFunction Trigonometric::getCalculateFunction(Function func, double ampl, double freq, double phase)
{
    const CalculateFunction trigonometricFunction = (func == Trigonometric::Function::SIN)
            ? qAsin
            : qAcos;

    return [&](double x) {
        return (ampl * trigonometricFunction(freq * x + phase));
    };
}
