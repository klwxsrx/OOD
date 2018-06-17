#ifndef LISTCONTROLLER_H
#define LISTCONTROLLER_H

#include <QSharedPointer>
#include "view/listview.h"
#include "model/harmoniclistviewmodel.h"

class CListController : public QObject
{
    Q_OBJECT
public:
    CListController(QSharedPointer<CListView> const& listView, QSharedPointer<CHarmonicListViewModel> const& model);

private:
    QSharedPointer<CListView> m_view;
    QSharedPointer<CHarmonicListViewModel> m_model;

private slots:
    void onAddButtonClicked();
    void onDeleteButtonClicked();
    void onItemChange(QModelIndex const& index);
};

#endif // LISTCONTROLLER_H
