#ifndef HARMONICFUNCTIONVIEWMODEL_H
#define HARMONICFUNCTIONVIEWMODEL_H

#include <QObject>
#include "iharmonicsmodel.h"

class CHarmonicFunctionViewModel : public QObject
{
    Q_OBJECT
public:
    CHarmonicFunctionViewModel(QSharedPointer<IHarmonicsModel> const& model);

    Trigonometric::CalculateFunction getFunction() const;

private:
    QSharedPointer<IHarmonicsModel> m_model;
    Trigonometric::CalculateFunction m_function;

private slots:
    void onCurrentItemChanged();

signals:
    void functionUpdated();
};

#endif // HARMONICFUNCTIONVIEWMODEL_H
