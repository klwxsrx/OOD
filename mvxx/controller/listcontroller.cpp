#include "listcontroller.h"

CListController::CListController(QSharedPointer<CListView> const& listView, QSharedPointer<IHarmonicsModel> const& model)
    : m_view(listView)
    , m_model(model)
{
    m_view->connect(m_view.get(), SIGNAL(addButtonCLicked()), this, SLOT(addButtonClicked()));
    m_view->connect(m_view.get(), SIGNAL(deleteButtonClicked()), this, SLOT(deleteButtonClicked()));
    m_view->connect(m_view.get(), SIGNAL(itemPressed(QModelIndex)), this, SLOT(onItemChange(QModelIndex)));
}

void CListController::addButtonClicked()
{
    // TODO:
}

void CListController::deleteButtonClicked()
{
    auto currentItemIndex = m_model->getCurrentItemIndex();
    if (currentItemIndex.isValid())
    {
        m_model->removeHarmonicItem(currentItemIndex.toInt());
    }
}

void CListController::onItemChange(QModelIndex const& index)
{
    QVariant listIndex = index.isValid() ? QVariant(index.row()) : QVariant();
    m_model->setCurrentItemIndex(listIndex);
}
