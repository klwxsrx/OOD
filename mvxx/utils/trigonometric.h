#ifndef TRIGONOMETRIC_H
#define TRIGONOMETRIC_H

#include <QString>
#include <QtMath>
#include <functional>

namespace Trigonometric {
    typedef std::function<double(double)> CalculateFunction;


    enum struct Function {SIN, COS};
    QString functionToString(Function func);
    QString harmonicToString(Function func, double ampl, double freq, double phase);
    CalculateFunction getCalculateFunction(Function func, double ampl, double freq, double phase);
}

#endif // TRIGONOMETRIC_H
