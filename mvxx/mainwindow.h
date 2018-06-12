#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include "model/harmonicitemlistmodel.h"
#include "model/harmonicitembuilder.h"
#include "view/listview.h"
#include "view/editharmonicview.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() = default;

    void initialize();

private slots:
    void onListDeleteButtonClicked(QModelIndex const& index);

private:
    QSharedPointer<Ui::MainWindow> m_ui;
    QSharedPointer<CHarmonicItemListModel> m_model;
    QSharedPointer<CHarmonicItemBuilder> m_builder;
    QSharedPointer<CListView> m_listView;
    QSharedPointer<CEditHarmonicView> m_editHarmonicView;
};

#endif // MAINWINDOW_H
