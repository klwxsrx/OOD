#ifndef TRIGONOMETRIC_H
#define TRIGONOMETRIC_H

#include <QString>

namespace Trigonometric {

    enum struct Function {SIN, COS};
    QString functionToString(Function func);
    QString harmonicToString(Function func, double ampl, double freq, double phase);
}

#endif // TRIGONOMETRIC_H
