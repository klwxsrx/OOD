#include "editharmonicview.h"

CEditHarmonicView::CEditHarmonicView(QWidget* editWidget)
{
    m_groupBox = editWidget;

    m_amplitudeField = m_groupBox->findChild<QLineEdit*>("amplitudeField");
    Q_ASSERT(m_amplitudeField);

    m_cosRadio = m_groupBox->findChild<QRadioButton*>("cosRadio");
    Q_ASSERT(m_cosRadio);

    m_sinRadio = m_groupBox->findChild<QRadioButton*>("sinRadio");
    Q_ASSERT(m_sinRadio);

    m_frequencyField = m_groupBox->findChild<QLineEdit*>("frequencyField");
    Q_ASSERT(m_frequencyField);

    m_phaseField = m_groupBox->findChild<QLineEdit*>("phaseField");
    Q_ASSERT(m_phaseField);

    m_resultLabel = m_groupBox->findChild<QLabel*>("resultLabel");
}

void CEditHarmonicView::onItemChanged(QModelIndex const& index)
{
    bool itemExists = index.isValid();
    updateEnabledState(itemExists);
}

void CEditHarmonicView::updateEnabledState(bool enable)
{
    m_groupBox->setEnabled(enable);
    m_amplitudeField->setEnabled(enable);
    m_sinRadio->setEnabled(enable);
    m_cosRadio->setEnabled(enable);
    m_frequencyField->setEnabled(enable);
    m_phaseField->setEnabled(enable);
}
