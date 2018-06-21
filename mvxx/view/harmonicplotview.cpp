#include "harmonicplotview.h"

const QPair<double, double> CHarmonicPlotView::X_AXIS_RANGE = {0, 5};
const double CHarmonicPlotView::PLOT_POINTS_COUNT = 500;

CHarmonicPlotView::CHarmonicPlotView(QSharedPointer<CHarmonicFunctionViewModel> model, QWidget* plotWidget)
    : m_model(model)
{
    m_plot = dynamic_cast<QCustomPlot*>(plotWidget);
    Q_ASSERT(m_plot);

    initializePlot();
    m_model->connect(m_model.get(), SIGNAL(dataUpdated()), this, SLOT(onDataUpdated()));
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

void CHarmonicPlotView::drawHarmonic(QVector<Trigonometric::CalculateFunction> const& functions)
{
    m_plot->addGraph();
    m_plot->graph(0)->setAntialiasedFill(true);

    const auto data = getHarmonicData(functions);
    m_plot->graph(0)->setData(data.first, data.second);

    updateYAxisRange(data.second);

    m_plot->replot();
}

void CHarmonicPlotView::updateYAxisRange(QVector<double> yCoordinates)
{
    const auto minMaxPair = std::minmax_element(yCoordinates.begin(), yCoordinates.end());
    double bottom = (*minMaxPair.first);
    double top = (*minMaxPair.second);
    if (top == bottom)
    {
        top += 1;
        bottom -= 1;
    }
    m_plot->yAxis->setRange(top, bottom);
}

QPair<QVector<double>, QVector<double>> CHarmonicPlotView::getHarmonicData(QVector<Trigonometric::CalculateFunction> const& functions)
{
    QVector<double> xCoordinates = getXCoordinateRange();
    QVector<double> yCoordinates(xCoordinates.size(), 0.0);

    int size = xCoordinates.size();
    for (int index = 0; index < size; ++index)
    {
        std::for_each(functions.begin(), functions.end(), [&](Trigonometric::CalculateFunction const& function){
            yCoordinates[index] += function(xCoordinates[index]);
        });
    }

    return {xCoordinates, yCoordinates};
}

QVector<double> CHarmonicPlotView::getXCoordinateRange()
{
    QVector<double> xCoordinates;
    const double step = (X_AXIS_RANGE.second - X_AXIS_RANGE.first) / PLOT_POINTS_COUNT;
    double x = X_AXIS_RANGE.first;
    while (x < X_AXIS_RANGE.second)
    {
        xCoordinates.push_back(x);
        x += step;
    }
    return xCoordinates;
}

void CHarmonicPlotView::onDataUpdated()
{
    clearPlot();

    auto functions = m_model->getFunctions();
    if (!functions.empty())
    {
        drawHarmonic(functions);
    }
}
