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

private slots:
    void onAmplitudeChanged();
    void onFrequencyChanged();
    void onPhaseChanged();

signals:
    void amplitudeChanged(double);
    void sinRadioSelected();
    void cosRadioSelected();
    void frequencyChanged(double);
    void phaseChanged(double);
};

#endif // EDITHARMONICVIEW_H
