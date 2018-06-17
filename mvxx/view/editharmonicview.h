#ifndef EDITHARMONICVIEW_H
#define EDITHARMONICVIEW_H

#include <QSharedPointer>
#include <QLineEdit>
#include <QRadioButton>
#include <QLabel>
#include "model/iharmonicviewmodel.h"

class CEditHarmonicView final : public QObject
{
    Q_OBJECT
public:
    CEditHarmonicView(QSharedPointer<IHarmonicViewModel> const& model, QWidget* editWidget);

public slots:
    void onItemChanged();

private:
    void updateEnabledState(bool enable);

    QSharedPointer<IHarmonicViewModel> m_model;
    QWidget* m_groupBox;
    QLineEdit* m_amplitudeField;
    QRadioButton* m_sinRadio;
    QRadioButton* m_cosRadio;
    QLineEdit* m_frequencyField;
    QLineEdit* m_phaseField;
    QLabel* m_resultLabel;

signals:
    void onAmplitudeChanged(QString);
    void onSinRadioSelected();
    void onCosRadioSelected();
    void onFrequencyChanged(QString);
    void onPhaseChanged(QString);
};

#endif // EDITHARMONICVIEW_H
