#ifndef LISTCONTROLLER_H
#define LISTCONTROLLER_H

#include <QSharedPointer>
#include "view/listview.h"
#include "model/iharmonicsmodel.h"

class CListController : public QObject
{
    Q_OBJECT
public:
    CListController(QSharedPointer<CListView> const& listView, QSharedPointer<IHarmonicsModel> const& model);

private:
    QSharedPointer<CListView> m_view;
    QSharedPointer<IHarmonicsModel> m_model;

private slots:
    void addButtonClicked();
    void deleteButtonClicked();
    void onItemChange(QModelIndex const& index);
};

#endif // LISTCONTROLLER_H
