#include "harmonicplotview.h"

CHarmonicPlotView::CHarmonicPlotView(QSharedPointer<CHarmonicFunctionViewModel> model, QWidget* plotWidget)
    : m_model(model)
{
    m_plot = dynamic_cast<QCustomPlot*>(plotWidget);
    Q_ASSERT(m_plot);

    m_model->connect(m_model.get(), SIGNAL(functionUpdated()), this, SLOT(onFunctionUpdated()));
}

void CHarmonicPlotView::clearPlot()
{
     // TODO: clear
}

void CHarmonicPlotView::drawHarmonic(Trigonometric::CalculateFunction const& function)
{
    // TOOD: draw
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
