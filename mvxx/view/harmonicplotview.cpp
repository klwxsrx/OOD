#include "harmonicplotview.h"

const QPair<double, double> CHarmonicPlotView::X_AXIS_RANGE = {0, 5};
const double CHarmonicPlotView::PLOT_POINTS_COUNT = 500;

CHarmonicPlotView::CHarmonicPlotView(QSharedPointer<CHarmonicFunctionViewModel> model, QWidget* plotWidget)
    : m_model(model)
{
    m_plot = dynamic_cast<QCustomPlot*>(plotWidget);
    Q_ASSERT(m_plot);

    initializePlot();
    m_model->connect(m_model.get(), SIGNAL(functionUpdated()), this, SLOT(onFunctionUpdated()));
}

void CHarmonicPlotView::initializePlot()
{
    m_plot->xAxis->setLabel("x");
    m_plot->xAxis->setRange(X_AXIS_RANGE.first, X_AXIS_RANGE.second);

    m_plot->yAxis->setLabel("y");
}

void CHarmonicPlotView::clearPlot()
{
     m_plot->removeGraph(0);
     m_plot->yAxis->setRange(-1, 1);
     m_plot->replot();
}

void CHarmonicPlotView::drawHarmonic(Trigonometric::CalculateFunction const& function)
{
    m_plot->addGraph();
    m_plot->graph(0)->setAntialiasedFill(true);

    const auto data = getHarmonicData(function);
    m_plot->graph(0)->setData(data.first, data.second);

    updateYAxisRange(data.second);

    m_plot->replot();
}

void CHarmonicPlotView::updateYAxisRange(QVector<double> yCoordinates)
{
    const auto minMaxPair = std::minmax_element(yCoordinates.begin(), yCoordinates.end());
    m_plot->yAxis->setRange((*minMaxPair.first), (*minMaxPair.second));
}

QPair<QVector<double>, QVector<double>> CHarmonicPlotView::getHarmonicData(Trigonometric::CalculateFunction const& function)
{
    QVector<double> xCoordinates;
    QVector<double> yCoordinates;

    const double step = (X_AXIS_RANGE.second - X_AXIS_RANGE.first) / PLOT_POINTS_COUNT;
    double x = X_AXIS_RANGE.first;
    while (x < X_AXIS_RANGE.second)
    {
        xCoordinates.push_back(x);
        yCoordinates.push_back(function(x));
        x += step;
    }
    return {xCoordinates, yCoordinates};
}

void CHarmonicPlotView::onFunctionUpdated()
{
    clearPlot();

    Trigonometric::CalculateFunction function = m_model->getFunction();
    if (function)
    {
        drawHarmonic(function);
    }
}
