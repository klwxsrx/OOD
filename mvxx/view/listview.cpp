#include "listview.h"

CListView::CListView(QSharedPointer<QAbstractListModel> const& model, QWidget* parent)
    : m_model(model)
{
    m_list = parent->findChild<QListView*>("itemList");
    Q_ASSERT(m_list);

    m_addButton = parent->findChild<QPushButton*>("addButton");
    Q_ASSERT(m_addButton);

    m_deleteButton = parent->findChild<QPushButton*>("deleteButton");
    Q_ASSERT(m_deleteButton);

    initialize();
}

void CListView::initialize()
{
    m_list->setModel(m_model.get());
    QAbstractListModel::connect(m_model.get(), SIGNAL(layoutChanged(QList<QPersistentModelIndex>,QAbstractItemModel::LayoutChangeHint)), this, SLOT(onDataChanged()));

    QListView::connect(m_list, SIGNAL(pressed(QModelIndex)), this, SLOT(onItemPressed(QModelIndex)));
    QListView::connect(m_list, SIGNAL(activated(QModelIndex)), this, SLOT(onItemPressed(QModelIndex)));
    QPushButton::connect(m_deleteButton, SIGNAL(released()), this, SIGNAL(deleteButtonClicked()));
    QPushButton::connect(m_addButton, SIGNAL(released()), this, SIGNAL(addButtonCLicked()));
}

void CListView::onItemPressed(QModelIndex const& index)
{
    m_deleteButton->setEnabled(true);
    emit itemPressed(index);
}

void CListView::onDataChanged()
{
    if (!m_list->currentIndex().isValid() || m_model->rowCount(QModelIndex()) <= m_list->currentIndex().row())
    {
        m_deleteButton->setEnabled(false);
    }
}
