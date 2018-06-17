#include "harmoniclistviewmodel.h"

CHarmonicListViewModel::CHarmonicListViewModel(QSharedPointer<IHarmonicsModel> const& model)
    : m_model(model)
{
    m_model->connect(m_model.get(), SIGNAL(dataUpdated()), this, SLOT(onModelDataChanged()));
}

void CHarmonicListViewModel::setCurrentItemIndex(QVariant index)
{
    m_model->setCurrentItemIndex(index);
}

void CHarmonicListViewModel::addHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase)
{
    m_model->addHarmonicItem(func, ampl, freq, phase);
}

void CHarmonicListViewModel::removeHarmonicItem(int index)
{
    m_model->removeHarmonicItem(index);
}

QVariant CHarmonicListViewModel::getCurrentItemIndex() const
{
    return m_model->getCurrentItemIndex();
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
    emit layoutChanged();
}
