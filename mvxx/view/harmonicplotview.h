#ifndef HARMONICPLOTVIEW_H
#define HARMONICPLOTVIEW_H

#include "lib/qcustomplot.h"
#include "model/harmonicfunctionviewmodel.h"

class CHarmonicPlotView final : public QObject
{
    Q_OBJECT
public:
    CHarmonicPlotView(QSharedPointer<CHarmonicFunctionViewModel> model, QWidget* plotWidget);

private:
    void clearPlot();
    void drawHarmonic(Trigonometric::CalculateFunction const& function);

    QCustomPlot* m_plot;
    QSharedPointer<CHarmonicFunctionViewModel> m_model;

private slots:
    void onFunctionUpdated();
};

#endif // HARMONICPLOTVIEW_H
