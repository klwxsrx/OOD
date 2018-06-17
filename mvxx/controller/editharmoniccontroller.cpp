#include "editharmoniccontroller.h"

CEditHarmonicController::CEditHarmonicController(QSharedPointer<CEditHarmonicView> const& view, QSharedPointer<IHarmonicViewModel> const& model)
    : m_view(view)
    , m_model(model)
{
    m_view->connect(m_view.get(), SIGNAL(onAmplitudeChanged(QString)), this, SLOT(onAmplitudeChanged(QString)));
    m_view->connect(m_view.get(), SIGNAL(onSinRadioSelected()), this, SLOT(onSinRadioSelected()));
    m_view->connect(m_view.get(), SIGNAL(onCosRadioSelected()), this, SLOT(onCosRadioSelected()));
    m_view->connect(m_view.get(), SIGNAL(onFrequencyChanged(QString)), this, SLOT(onFrequencyChanged(QString)));
    m_view->connect(m_view.get(), SIGNAL(onPhaseChanged(QString)), this, SLOT(onPhaseChanged(QString)));
}

void CEditHarmonicController::onAmplitudeChanged(QString string)
{
    m_model->SetAmplitude(string.toDouble());
}

void CEditHarmonicController::onSinRadioSelected()
{
    m_model->SetFunction(Trigonometric::Function::SIN);
}

void CEditHarmonicController::onCosRadioSelected()
{
    m_model->SetFunction(Trigonometric::Function::COS);
}

void CEditHarmonicController::onFrequencyChanged(QString string)
{
    m_model->SetFrequency(string.toDouble());
}

void CEditHarmonicController::onPhaseChanged(QString string)
{
m_model->SetPhase(string.toDouble());
}
