#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(QSharedPointer<Ui::MainWindow>::create())
    , m_model(QSharedPointer<CHarmonicsModel>::create(QSharedPointer<CHarmonicList>::create()))
{
    m_ui->setupUi(this);
    initListView();
    initEditItemView();
    initHarmonicPlotView();

    m_model->addHarmonicItem(Trigonometric::Function::SIN, 4.38, 2.25, 1.5);
    m_model->addHarmonicItem(Trigonometric::Function::COS, 3, -3, 0.3);
    m_model->addHarmonicItem(Trigonometric::Function::COS, 1, 1, 5);
}

void MainWindow::initListView()
{
    auto viewModel = QSharedPointer<CHarmonicListViewModel>::create(m_model);
    auto view = QSharedPointer<CListView>::create(viewModel, m_ui->listWidget);

    m_listController = QSharedPointer<CListController>::create(view, viewModel);
}

void MainWindow::initEditItemView()
{
    auto viewModel = QSharedPointer<CEditHarmonicViewModel>::create(m_model);
    auto view = QSharedPointer<CEditHarmonicView>::create(viewModel, m_ui->editWidget);

    m_editController = QSharedPointer<CEditHarmonicController>::create(view, viewModel);
}

void MainWindow::initHarmonicPlotView()
{
    auto viewModel = QSharedPointer<CHarmonicFunctionViewModel>::create(m_model);
    m_plotView = QSharedPointer<CHarmonicPlotView>::create(viewModel, m_ui->plotWidget);
}
