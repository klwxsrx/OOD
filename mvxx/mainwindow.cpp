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
    m_ui->itemList->setModel(m_model.get());
    m_model->addHarmonicItem(m_builder->build(Trigonometric::Function::SIN, 1.5, 2.0, 3.14));
}
