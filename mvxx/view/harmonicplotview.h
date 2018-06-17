#ifndef HARMONICPLOTVIEW_H
#define HARMONICPLOTVIEW_H

#include <QVector>
#include <QPair>
#include <algorithm>
#include "lib/qcustomplot.h"
#include "model/harmonicfunctionviewmodel.h"

class CHarmonicPlotView final : public QObject
{
    Q_OBJECT
public:
    CHarmonicPlotView(QSharedPointer<CHarmonicFunctionViewModel> model, QWidget* plotWidget);

private:
    void initializePlot();
    void clearPlot();
    void drawHarmonic(QVector<Trigonometric::CalculateFunction> const& functions);
    void updateYAxisRange(QVector<double> yCoordinates);

    static QPair<QVector<double>, QVector<double>> getHarmonicData(QVector<Trigonometric::CalculateFunction> const& functions);
    static QVector<double> getXCoordinateRange();

    static const QPair<double, double> X_AXIS_RANGE;
    static const double PLOT_POINTS_COUNT;

    QCustomPlot* m_plot;
    QSharedPointer<CHarmonicFunctionViewModel> m_model;

private slots:
    void onDataUpdated();
};

#endif // HARMONICPLOTVIEW_H
