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
