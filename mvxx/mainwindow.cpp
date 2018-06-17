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
}

void MainWindow::initListView()
{
    auto viewModel = QSharedPointer<CHarmonicListViewModel>::create(m_model);
    auto view = QSharedPointer<CListView>::create(viewModel, m_ui->listWidget);

    m_listController = QSharedPointer<CListController>::create(view, viewModel);

    m_model->addHarmonicItem(Trigonometric::Function::SIN, 1.3, 3.14, 2.12); // TODO: delete
    m_model->addHarmonicItem(Trigonometric::Function::COS, 2.3, 4.32, 5.0);
    m_model->addHarmonicItem(Trigonometric::Function::COS, 3.14, 5.67, 9.62);
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
