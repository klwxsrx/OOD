#include "insertdialog.h"

CInsertHarmonicDialog::CInsertHarmonicDialog()
    : m_ui(QSharedPointer<Ui::Dialog>::create())
{
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    m_ui->setupUi(this);

    m_model = QSharedPointer<CNewHarmonicViewModel>::create();
    auto view = QSharedPointer<CEditHarmonicView>::create(m_model, m_ui->editWidget);
    m_controller = QSharedPointer<CEditHarmonicController>::create(view, m_model);
}

void CInsertHarmonicDialog::accept()
{
    emit dialogAccepted(
        m_model->getFunction(),
        m_model->getAmplitude(),
        m_model->getFrequency(),
        m_model->getPhase()
    );
    QDialog::accept();
}
