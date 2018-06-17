#include "editharmonicview.h"

CEditHarmonicView::CEditHarmonicView(QSharedPointer<IHarmonicViewModel> const& model, QWidget* editWidget)
    : m_model(model)
{
    m_model->connect(m_model.get(), SIGNAL(harmonicUpdated()), this, SLOT(onItemChanged()));
    m_groupBox = editWidget;

    m_amplitudeField = m_groupBox->findChild<QLineEdit*>("amplitudeField");
    Q_ASSERT(m_amplitudeField);
    m_amplitudeField->connect(m_amplitudeField, SIGNAL(textEdited(QString)), this, SIGNAL(onAmplitudeChanged(QString)));

    m_cosRadio = m_groupBox->findChild<QRadioButton*>("cosRadio");
    Q_ASSERT(m_cosRadio);
    m_cosRadio->connect(m_cosRadio, SIGNAL(released()), this, SIGNAL(onCosRadioSelected()));

    m_sinRadio = m_groupBox->findChild<QRadioButton*>("sinRadio");
    Q_ASSERT(m_sinRadio);
    m_sinRadio->connect(m_sinRadio, SIGNAL(released()), this, SIGNAL(onSinRadioSelected()));

    m_frequencyField = m_groupBox->findChild<QLineEdit*>("frequencyField");
    Q_ASSERT(m_frequencyField);
    m_frequencyField->connect(m_frequencyField, SIGNAL(textEdited(QString)), this, SIGNAL(onFrequencyChanged(QString)));

    m_phaseField = m_groupBox->findChild<QLineEdit*>("phaseField");
    Q_ASSERT(m_phaseField);
    m_phaseField->connect(m_phaseField, SIGNAL(textEdited(QString)), this, SIGNAL(onPhaseChanged(QString)));

    m_resultLabel = m_groupBox->findChild<QLabel*>("resultLabel");
    Q_ASSERT(m_resultLabel);
}

void CEditHarmonicView::onItemChanged()
{
    bool isEnabled = m_model->isEnabled();
    updateEnabledState(isEnabled);
    if (isEnabled)
    {
        m_amplitudeField->setText(QString::number(m_model->getAmplitude()));
        m_frequencyField->setText(QString::number(m_model->getFrequency()));
        m_phaseField->setText(QString::number(m_model->getPhase()));
        auto function = m_model->getFunction();
        if (function == Trigonometric::Function::SIN)
        {
            m_sinRadio->setChecked(true);
        }
        else
        {
            m_cosRadio->setChecked(true);
        }
        m_resultLabel->setText(m_model->getString());
    }
}

void CEditHarmonicView::updateEnabledState(bool enable)
{
    m_groupBox->setEnabled(enable);
    m_amplitudeField->setEnabled(enable);
    m_sinRadio->setCheckable(enable);
    m_cosRadio->setCheckable(enable);
    m_frequencyField->setEnabled(enable);
    m_phaseField->setEnabled(enable);
    m_resultLabel->clear();
    if (!enable)
    {
        m_amplitudeField->clear();
        m_frequencyField->clear();
        m_phaseField->clear();
    }
}
