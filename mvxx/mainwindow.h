#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include "model/harmonicsmodel.h"
#include "model/harmoniclistviewmodel.h"
#include "view/listview.h"
#include "controller/listcontroller.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private:
    void initListView();

    QSharedPointer<Ui::MainWindow> m_ui;
    QSharedPointer<IHarmonicsModel> m_model;
    QSharedPointer<CListController> m_listController;
};

#endif // MAINWINDOW_H
