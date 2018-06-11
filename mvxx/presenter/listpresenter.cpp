#include "listpresenter.h"

CListPresenter::CListPresenter(QSharedPointer<IHarmonicItemListModel> const& model, QWidget* parent)
    : m_model(model)
{
    m_list = parent->findChild<QListView*>("itemList");
    Q_ASSERT(m_list);
    m_list->setModel(m_model.get());
    connect(m_list, &QListView::pressed, this, &CListPresenter::updateCurrentSelection);

    m_addButton = parent->findChild<QPushButton*>("addButton");
    Q_ASSERT(m_addButton);

    m_deleteButton = parent->findChild<QPushButton*>("deleteButton");
    Q_ASSERT(m_deleteButton);
}

void CListPresenter::updateCurrentSelection(QModelIndex const&)
{
       m_deleteButton->setEnabled(true);
}
