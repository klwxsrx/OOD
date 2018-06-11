#include "trigonometric.h"

QString Trigonometric::FunctionToString(Function func)
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

QString Trigonometric::HarmonicToString(Function func, double ampl, double freq, double phase)
{
    return QString::number(ampl) + " * " +
        FunctionToString(func) + "(" +
        QString::number(freq) + " * x + " +
        QString::number(phase) + ")";
}
