#ifndef EDITHARMONICVIEW_H
#define EDITHARMONICVIEW_H

#include <QLineEdit>
#include <QRadioButton>
#include <QLabel>
#include "model/iharmonicitemlistmodel.h"

class CEditHarmonicView : public QObject
{
    Q_OBJECT
public:
    CEditHarmonicView(QSharedPointer<IHarmonicItemListModel> const& model, QWidget* editWidget);

public slots:
    void onItemChanged(QModelIndex const& index);

private:
    void updateEnabledState(bool enable);

    QSharedPointer<IHarmonicItemListModel> m_model;
    QWidget* m_groupBox;
    QLineEdit* m_amplitudeField;
    QRadioButton* m_sinRadio;
    QRadioButton* m_cosRadio;
    QLineEdit* m_frequencyField;
    QLineEdit* m_phaseField;
    QLabel* m_resultLabel;
};

#endif // EDITHARMONICVIEW_H
