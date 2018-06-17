#include "harmoniclistviewmodel.h"

CHarmonicListViewModel::CHarmonicListViewModel(QSharedPointer<IHarmonicsModel> const& model)
    : m_model(model)
{
    m_model->connect(m_model.get(), SIGNAL(dataUpdated()), this, SLOT(onModelDataChanged()));
}

int CHarmonicListViewModel::rowCount(QModelIndex const&) const
{
    return m_model->getSize();
}

QVariant CHarmonicListViewModel::data(QModelIndex const& index, int role) const
{
    if (index.row() >= m_model->getSize())
    {
        return QVariant();
    }

    auto item = m_model->getHarmonicItem(index.row());
    switch (role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return Trigonometric::harmonicToString(
                item->getFunction(),
                item->getAmplitude(),
                item->getFrequency(),
                item->getPhase()
            );
    default:
        return QVariant();
    }
}

void CHarmonicListViewModel::onModelDataChanged()
{
    emit layoutAboutToBeChanged(); // TODO: delete if not needed
    emit layoutChanged();
}
