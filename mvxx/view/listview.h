#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QSharedPointer>
#include <QListView>
#include <QPushButton>
#include "model/harmoniclistviewmodel.h"

class CListView final : public QObject
{
    Q_OBJECT
public:
    CListView(QSharedPointer<CHarmonicListViewModel> const& model, QWidget* listWidget);

private:
    void initialize();

    QSharedPointer<CHarmonicListViewModel> m_model;
    QListView* m_list;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;

private slots:
    void onItemPressed(QModelIndex const& index);
    void onDataChanged();
    void onIndexChanged(QModelIndex const& index);

signals:
    void itemPressed(QModelIndex const& index);
    void addButtonClicked();
    void deleteButtonClicked();
};

#endif // LISTVIEW_H
