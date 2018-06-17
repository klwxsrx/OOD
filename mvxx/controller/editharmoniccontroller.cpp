#include "editharmoniccontroller.h"

CEditHarmonicController::CEditHarmonicController(QSharedPointer<CEditHarmonicView> const& view, QSharedPointer<IHarmonicViewModel> const& model)
    : m_view(view)
    , m_model(model)
{
    m_view->connect(m_view.get(), SIGNAL(amplitudeChanged(double)), this, SLOT(onAmplitudeChanged(double)));
    m_view->connect(m_view.get(), SIGNAL(sinRadioSelected()), this, SLOT(onSinRadioSelected()));
    m_view->connect(m_view.get(), SIGNAL(cosRadioSelected()), this, SLOT(onCosRadioSelected()));
    m_view->connect(m_view.get(), SIGNAL(frequencyChanged(double)), this, SLOT(onFrequencyChanged(double)));
    m_view->connect(m_view.get(), SIGNAL(phaseChanged(double)), this, SLOT(onPhaseChanged(double)));
}

void CEditHarmonicController::onAmplitudeChanged(double value)
{
    m_model->setAmplitude(value);
}

void CEditHarmonicController::onSinRadioSelected()
{
    m_model->setFunction(Trigonometric::Function::SIN);
}

void CEditHarmonicController::onCosRadioSelected()
{
    m_model->setFunction(Trigonometric::Function::COS);
}

void CEditHarmonicController::onFrequencyChanged(double value)
{
    m_model->setFrequency(value);
}

void CEditHarmonicController::onPhaseChanged(double value)
{
    m_model->setPhase(value);
}
