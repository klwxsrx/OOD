#ifndef HARMONICFUNCTIONVIEWMODEL_H
#define HARMONICFUNCTIONVIEWMODEL_H

#include <QObject>
#include <QVector>
#include "iharmonicsmodel.h"

class CHarmonicFunctionViewModel final : public QObject
{
    Q_OBJECT
public:
    CHarmonicFunctionViewModel(QSharedPointer<IHarmonicsModel> const& model);

    QVector<Trigonometric::CalculateFunction> getFunctions() const;

private:
    QSharedPointer<IHarmonicsModel> m_model;
    QVector<Trigonometric::CalculateFunction> m_functions;

private slots:
    void onItemsChanged();

signals:
    void dataUpdated();
};

#endif // HARMONICFUNCTIONVIEWMODEL_H
