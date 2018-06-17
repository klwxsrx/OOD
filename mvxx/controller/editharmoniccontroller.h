#ifndef EDITHARMONICCONTROLLER_H
#define EDITHARMONICCONTROLLER_H

#include "view/editharmonicview.h"
#include "model/iharmonicviewmodel.h"

class CEditHarmonicController : public QObject
{
    Q_OBJECT
public:
    CEditHarmonicController(QSharedPointer<CEditHarmonicView> const& view, QSharedPointer<IHarmonicViewModel> const& model);

private:
    QSharedPointer<CEditHarmonicView> m_view;
    QSharedPointer<IHarmonicViewModel> m_model;

private slots:
    void onAmplitudeChanged(double);
    void onSinRadioSelected();
    void onCosRadioSelected();
    void onFrequencyChanged(double);
    void onPhaseChanged(double);
};

#endif // EDITHARMONICCONTROLLER_H
