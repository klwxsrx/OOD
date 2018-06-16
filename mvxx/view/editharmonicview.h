#ifndef EDITHARMONICVIEW_H
#define EDITHARMONICVIEW_H

#include <QLineEdit>
#include <QRadioButton>
#include <QLabel>
#include <QModelIndex> // TODO: delete

class CEditHarmonicView : public QObject
{
    Q_OBJECT
public:
    CEditHarmonicView(QWidget* editWidget);

public slots:
    void onItemChanged(QModelIndex const& index);

private:
    void updateEnabledState(bool enable);

    QWidget* m_groupBox;
    QLineEdit* m_amplitudeField;
    QRadioButton* m_sinRadio;
    QRadioButton* m_cosRadio;
    QLineEdit* m_frequencyField;
    QLineEdit* m_phaseField;
    QLabel* m_resultLabel;
};

#endif // EDITHARMONICVIEW_H
