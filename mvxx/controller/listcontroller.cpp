#include "listcontroller.h"

CListController::CListController(QSharedPointer<CListView> const& listView, QSharedPointer<CHarmonicListViewModel> const& model)
    : m_view(listView)
    , m_model(model)
{
    m_view->connect(m_view.get(), SIGNAL(addButtonClicked()), this, SLOT(onAddButtonClicked()));
    m_view->connect(m_view.get(), SIGNAL(deleteButtonClicked()), this, SLOT(onDeleteButtonClicked()));
    m_view->connect(m_view.get(), SIGNAL(itemPressed(QModelIndex)), this, SLOT(onItemChange(QModelIndex)));
}

void CListController::onAddButtonClicked()
{
    QSharedPointer<CInsertHarmonicDialog> dialog = QSharedPointer<CInsertHarmonicDialog>::create();
    dialog->connect(dialog.get(), SIGNAL(dialogAccepted(Trigonometric::Function,double,double,double)), m_model.get(), SLOT(addHarmonicItem(Trigonometric::Function,double,double,double)));
    dialog->exec();
}

void CListController::onDeleteButtonClicked()
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
