#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(QSharedPointer<Ui::MainWindow>::create())
    , m_model(QSharedPointer<CHarmonicItemListModel>::create())
    , m_builder(QSharedPointer<CHarmonicItemBuilder>::create())
{
    m_ui->setupUi(this);
    initialize();
}

void MainWindow::initialize()
{
    m_listView = QSharedPointer<CListView>::create(m_model, m_ui->listWidget);
    CListView::connect(m_listView.get(), SIGNAL(deleteButtonClicked(QModelIndex)), this, SLOT(onListDeleteButtonClicked(QModelIndex)));

    m_editHarmonicView = QSharedPointer<CEditHarmonicView>::create(m_model, m_ui->viewGroupBox);
    CListView::connect(m_listView.get(), SIGNAL(itemChanged(QModelIndex)), m_editHarmonicView.get(), SLOT(onItemChanged(QModelIndex)));

    m_model->addHarmonicItem(m_builder->build(Trigonometric::Function::SIN, 1.5, 2.0, 3.14)); // TODO: delete
    m_model->addHarmonicItem(m_builder->build(Trigonometric::Function::SIN, 1.34, 5.25, 0)); // TODO: delete
}

void MainWindow::onListDeleteButtonClicked(QModelIndex const& index)
{
    if (index.isValid())
    {
        m_model->removeHarmonicItem(index.row());
    }
}
