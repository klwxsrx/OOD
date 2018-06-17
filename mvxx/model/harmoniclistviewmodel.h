#ifndef HARMONICLISTVIEWMODEL_H
#define HARMONICLISTVIEWMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include "iharmonicsmodel.h"

class CHarmonicListViewModel final : public QAbstractListModel
{
    Q_OBJECT
public:
    CHarmonicListViewModel(QSharedPointer<IHarmonicsModel> const& model);

    void setCurrentItemIndex(QVariant index);
    void removeHarmonicItem(int index);

    QVariant getCurrentItemIndex() const;
    int rowCount(QModelIndex const&) const override;
    QVariant data(QModelIndex const& index, int role) const override;

public slots:
    void addHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase);

private:
    QSharedPointer<IHarmonicsModel> m_model;

private slots:
    void onModelDataChanged();
};

#endif // HARMONICLISTVIEWMODEL_H
